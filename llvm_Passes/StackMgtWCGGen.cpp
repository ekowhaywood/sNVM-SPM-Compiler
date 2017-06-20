
#include "SecureNvmPass.hpp"


namespace {
	
	struct StackManagementHelperPass : public ModulePass {
		static char ID; // Pass identification, replacement for typeid
		
		StackManagementHelperPass() : ModulePass(ID) {}
		
		virtual void getAnalysisUsage(AnalysisUsage &AU) const
		{	AU.addRequired<CallGraphWrapperPass>(); }
 
		// Instrument the program specified by mod
		// with stack management helper functions
		// that will collect the stack size of each function
		bool getWcgNodeWeights(Module &mod)
		{
			mod.materializeAll();
			//SetLibraryFunctions();
			LLVMContext &context = mod.getContext();
			
			// Global variables
			GlobalVariable* gvar_sp_calling = mod.getGlobalVariable("_sp_calling");
			assert(gvar_sp_calling);
			GlobalVariable* gvar_func_name = mod.getGlobalVariable("_func_name");
			assert(gvar_func_name);
			
			// Functions
			//Function *func_main = mod.getFunction("main");
			Function *func_get_func_stack_size = mod.getFunction("_get_func_stack_size");
			Function *func_dump_func_stack_sizes = mod.getFunction("_dump_func_stack_sizes");
			
			
			// Call graph
			CallGraph &cg = getAnalysis<CallGraphWrapperPass>().getCallGraph();
			
			// Get the pointer to the global variable which saves format string
			ConstantInt* const_int64_0 = ConstantInt::get(context, APInt(64, StringRef("0"), 10));
			std::vector<Constant*> const_ptr_indices;
			const_ptr_indices.push_back(const_int64_0);
			const_ptr_indices.push_back(const_int64_0);
			
			
			std::map<Function * , unsigned int > idxs ; unsigned int idx = 1 ;
			
			// Step 1: Insert management helper functions
			for (CallGraph::iterator cgi = cg.begin(), cge = cg.end(); cgi != cge; cgi++)
			{
			
				CallGraphNode *cgn = dyn_cast<CallGraphNode>(cgi->second);
				
				Function *fi = cgn->getFunction();
				
				
				
				// Skip external nodes
				if (!fi){ errs() << "\n fff: nil " ; continue;}
				
				
				idxs[fi] = idx++;
				
				errs() << "\n fff:" << fi->getName().str() << " idx:" <<idxs[fi] ;
				
				// Skip library functions
				if (isLibraryFunction(fi)){errs() << "\n   lib:" << fi->getName().str() ; continue;}
				// Skip external functions
				if (fi->getBasicBlockList().size() == 0 ) {	continue ; }
				
				// Process user-defined functions
				
				errs() << "\n   process : " << fi->getName().str() << " idx:" <<idxs[fi] ;
				
				
				// Get or build a gloabal variable which saves the name of current function
				GlobalVariable* gvar_curfuncname = mod.getGlobalVariable("__func__." + fi->getName().str(), true);
				Constant* const_ptr_curfuncname;
				if (!gvar_curfuncname)
				{
					ArrayType* arrayty_curfuncname =ArrayType::get(IntegerType::get(context, 8), fi->getName().size()+1);
					Constant *const_curfuncname = ConstantDataArray::getString(context, fi->getName(), true);
					gvar_curfuncname = new GlobalVariable(mod, arrayty_curfuncname,true,GlobalValue::PrivateLinkage,
														  0, "__func__." + fi->getName());
					
					gvar_curfuncname->setAlignment(1);
					const_ptr_curfuncname = ConstantExpr::getGetElementPtr(gvar_curfuncname, const_ptr_indices);
					gvar_curfuncname->setInitializer(const_curfuncname);
				}
				else
				{
					const_ptr_curfuncname = ConstantExpr::getGetElementPtr(gvar_curfuncname, const_ptr_indices);
				}
				
				
				GlobalVariable* gvar_func_index   = mod.getGlobalVariable("_func_index");
				assert(gvar_func_index);

				
				// Insert _get_stack_size() function before the first non-phi instruction in each app function
				Instruction *first_non_phi = fi->begin()->getFirstNonPHI();
				new StoreInst(const_ptr_curfuncname, gvar_func_name, false, first_non_phi);
				
				IRBuilder<> builder(mod.getContext()) ;
				builder.SetInsertPoint(first_non_phi);
				Constant * const_index = builder.getInt32(idxs[fi]);
				builder.CreateStore(const_index , gvar_func_index);
				
				InsertGetStackRegisterValue(mod, mod.getGlobalVariable("_sp_called") , first_non_phi);
				CallInst::Create(func_get_func_stack_size, "", first_non_phi);
				
				//errs() << *first_non_phi->getParent() ;
				
				for (CallGraphNode::iterator cgni = cgn->begin(), cgne = cgn->end(); cgni != cgne; cgni++)
				{
					// If we find a function call, read the current SP value and print out the caller's name
					if ( cgni->first == nullptr) { continue ; }
					
					if (CallInst * call_func = dyn_cast<CallInst>(cgni->first))
					{
						// Skip inline assembly
						if (call_func->isInlineAsm()) { continue; }
						
						Function *callee = call_func->getCalledFunction();
						// SKip if callee is a function pointer or a library function
						if(!callee) { continue ;}
						if( isLibraryFunction(callee)){	continue; }
						
						// Read the current SP value
						InsertGetStackRegisterValue(mod,gvar_sp_calling,call_func);
					}
				}
			}
			
			
			//WrapApplicationMainFtn(mod);
			//ReplaceExitFtnCalls(mod);
			
			return true;
		}
		
		bool extractAnnotatedWcgPaths(Module &mod, std::unordered_map <std::string, long> wcg_nodes)
		{
			mod.materializeAll();
			//SetLibraryFunctions();
			long ssize;
			std::string func_name;
			std::ofstream ofs;
			std::ifstream ifs;
			//std::unordered_map <std::string, long> wcg_nodes;
			std::vector<std::vector<CallGraphNode::CallRecord *> > paths;
			std::unordered_set <CallGraphNode *> uncertain_functions;
			CallGraph &cg = getAnalysis<CallGraphWrapperPass>().getCallGraph(); // call graph
			CallGraphNode *cgn_main = cg[mod.getFunction("main")];
			CallGraphNode::CallRecord *root;
			
			// Initialize root node by main function
			for (CallGraphNode::iterator cgni = cg.begin()->second->begin(), cgne = cg.begin()->second->end(); cgni != cgne; cgni++) {
				if (cgni->second == cgn_main) {
					root = &*cgni;
					break;
				}
			}
			assert(CallGraphNode::iterator(root) != cg.begin()->second->end());
			
			// Get all the paths from the call graph rooted at main
			auto res = extractPaths(root);
			paths = res.first;
			uncertain_functions = res.second;
			
		
			// Print out all the edges
			ofs.open("wcg_paths.txt", std::fstream::out) ;
			bfsPrint(root, paths, ofs);
			
			ofs << "#\n";
			
			// Print out annotated WCG paths
			for (size_t i = 0; i < paths.size(); i++) {
				//ofs << "path" << i << " : ";
				for (size_t j = 0; j < paths[i].size(); j++)
				{
					if (paths[i][j]->second->getFunction())
					{
						std::string func_name = paths[i][j]->second->getFunction()->getName().str();
						// Print node name (function name)
						ofs << func_name << " ";
						// Print node weight (function stack size)
						if (wcg_nodes.find(func_name) != wcg_nodes.end())
						{
							ofs << wcg_nodes[func_name];
							
							ofs << " ";
							// Print edge weight (number of function calls)
							if (j < paths[i].size()-1)
								ofs << "1";
							else
								ofs << "0";
						}
						else
						{
							// TODO Get library function stack sizes
							//errs() << func_name << "\n";
							ofs << std::numeric_limits<int>::max();
							
							ofs << " 0";
							
						}
						
				
						ofs << " ";
					}
					
				}
				ofs << "\n";
			}
			
			ofs << "#\n";
			
			// Print out uncertain function names
			for (auto ii = uncertain_functions.begin(), ie = uncertain_functions.end(); ii != ie; ii++)
			{
				if ((*ii)->getFunction())
				{
					ofs << (*ii)->getFunction()->getName().str() << "\n";
				}
			}
			
			ofs.close();
			
			return false;
		}
		
		virtual bool runOnModule(Module &mod)
		{
			mod.materializeAll();
			//SetLibraryFunctions();
			
			//mainWrapper = mod.getFunction("mainWrapper");
			
			//return true ;
			
			std::ifstream ifs;
			std::ofstream ofs;
			
			CallGraph &cg = getAnalysis<CallGraphWrapperPass>().getCallGraph();
			
			
			// Print out the names of library functions
			ofs.open("lib_funcs.txt", std::fstream::out);
			for (CallGraph::iterator cgi = cg.begin(), cge = cg.end(); cgi != cge; cgi++)
			{
				CallGraphNode *cgn = dyn_cast<CallGraphNode>(cgi->second);
				Function *fi = cgn->getFunction();
				
				cgn->dump() ;
				
				cgn->print(errs());
				
				std::string sss = fi->getName().str() ;
				
				errs() << * mod.getFunction("getEntryFunction") ;
				
				//continue ;
				//errs() << *cgn ;
				//errs() << " function poiunter : " << fi ;
				
				// Skip external nodes
				if (!fi)
					continue;
				
				errs() << "\n function poiunter --: " << fi << " \n " << fi->getBasicBlockList().size() ;
				// Skip library functions
				if (isLibraryFunction(fi))
					continue ;
				if (fi->getBasicBlockList().size() == 0)
					ofs << fi->getName().str() << "\n";
			}
			ofs.close();
			
			CreateSpAsmFtnType(mod);
			
			// Get stack frame sizes of user-defined functions
			ifs.open("_strErr.txt", std::fstream::in);
			if (!ifs.good())
			{
				errs() << "Dumping node weights of WCG to wcg_nodes.txt...\n";
				ifs.close();
				getWcgNodeWeights(mod);
				return true ;
			}
			
			std::unordered_map <std::string, long> wcg_nodes ;
			
			// extract wcg nodes from stderr output
			if ( ifs.good() )
			{
			 
				std::string word ;
				
				bool _extract_wcg_from_stderr = false ;
				
				std::string func_name ; long  ssize  ;
				std::ofstream wcg_nodes_ofs ;
				wcg_nodes_ofs.open("wcg_nodes.txt", std::fstream::out);
				
				
				while (ifs.good())
				{
					
					if (_extract_wcg_from_stderr)
					{
						ifs >> func_name ;
						ifs >> ssize ;
						wcg_nodes_ofs << func_name  << " " << ssize  << "\n" ;
						wcg_nodes[func_name]  = ssize ;
					}
					else
					{
						ifs >> word ;
						if ( word == "--DUMP_WCG_NODES--")
						{
							_extract_wcg_from_stderr = true ;
						}
					}
				}
				
				wcg_nodes_ofs.close() ;
				
				extractAnnotatedWcgPaths(mod , wcg_nodes);
				return true ;
			}
			
			return true;
		}
	};
}

char StackManagementHelperPass::ID = 0; //Id the pass.
static RegisterPass<StackManagementHelperPass> X("smmsmh", "Stack Management Helper Pass"); //Register the pass.

