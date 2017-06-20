
#include "SecureNvmPass.hpp"


FunctionType* FuncTy_GetSp ;
FunctionType* FuncTy_PutSp ;

void CreateSpAsmFtnType(Module &mod )
{
		std::vector<Type*>FuncTy_10_args;
		FuncTy_GetSp  = FunctionType::get(PointerType::get(IntegerType::get(mod.getContext(), 8), 0), FuncTy_10_args,false);
	
		std::vector<Type*>FuncTy_5_args;
		FuncTy_5_args.push_back(PointerType::get(IntegerType::get(mod.getContext(), 8), 0));
		FuncTy_PutSp = FunctionType::get(Type::getVoidTy(mod.getContext()),FuncTy_5_args,false);
	
}

Instruction * InsertGetStackRegisterValue(Module &mod, Value * var , Instruction * Position  ,bool AfterPosition  )
{
	
	InlineAsm* Asm_1  = InlineAsm::get(FuncTy_GetSp , "mov $0, r13 ", "=r",true);
	CallInst* callAsm = CallInst::Create(Asm_1, "", Position->getParent() );
	callAsm->setCallingConv(CallingConv::C);
	callAsm->setTailCall(true);
	AttributeSet _PAL;
	{
		SmallVector<AttributeSet, 4> Attrs;
		AttributeSet PAS;
		{
			AttrBuilder B;
			B.addAttribute(Attribute::NoUnwind);
			PAS = AttributeSet::get(mod.getContext(), ~0U, B);
		}
		
		Attrs.push_back(PAS);
		_PAL = AttributeSet::get(mod.getContext(), Attrs);
		
	}
	callAsm->setAttributes(_PAL);
	
	StoreInst* storeInst_1 = new StoreInst(callAsm, var , false, Position->getParent());
	storeInst_1->setAlignment(4);
	
	callAsm->moveBefore(Position);
	storeInst_1->moveBefore(Position);
	
	if(AfterPosition)
	{
		Position->moveBefore(callAsm);
		return storeInst_1 ;
	}
	
	return Position ;
}

Instruction * InsertGetStackRegisterValue(Module &mod, Value * var , IRBuilder<> &builder)
//Instruction * Position  ,bool AfterPosition  )
{
	
	InlineAsm* Asm_1  = InlineAsm::get(FuncTy_GetSp , "mov $0, r13 ", "=r",true);
	CallInst* callAsm = builder.CreateCall(Asm_1,"") ; // CallInst::Create(Asm_1, "", Position->getParent() );
	callAsm->setCallingConv(CallingConv::C);
	callAsm->setTailCall(true);
	AttributeSet _PAL;
	{
		SmallVector<AttributeSet, 4> Attrs;
		AttributeSet PAS;
		{
			AttrBuilder B;
			B.addAttribute(Attribute::NoUnwind);
			PAS = AttributeSet::get(mod.getContext(), ~0U, B);
		}
		
		Attrs.push_back(PAS);
		_PAL = AttributeSet::get(mod.getContext(), Attrs);
		
	}
	callAsm->setAttributes(_PAL);
	
	StoreInst* storeInst_1 = builder.CreateStore(callAsm,var) ;// new StoreInst(callAsm, var , false, Position->getParent());
	storeInst_1->setAlignment(4);
	
	
	
	return storeInst_1 ;
}



Instruction * InsertPutStackRegisterValue(Module &mod , Value* var , Instruction * Position , bool AfterPosition  )
{
	
	LoadInst* loadInst_1 = new LoadInst(var, "", false, Position);
	loadInst_1->setAlignment(4);
	InlineAsm* Asm_1 = InlineAsm::get(FuncTy_PutSp, "mov r13 , $0 ", "r",true);
	CallInst* callAsm  = CallInst::Create(Asm_1, loadInst_1, "", Position);
	callAsm->setCallingConv(CallingConv::C);
	callAsm->setTailCall(false);
	AttributeSet _PAL  ;
	{
		SmallVector<AttributeSet, 4> Attrs;
		AttributeSet PAS;
		{
			AttrBuilder B;
			B.addAttribute(Attribute::NoUnwind);
			PAS = AttributeSet::get(mod.getContext(), ~0U, B);
		}
		
		Attrs.push_back(PAS);
		_PAL = AttributeSet::get(mod.getContext(), Attrs);
		
	}
	callAsm->setAttributes(_PAL);
	
	
	loadInst_1->moveBefore(Position);
	callAsm->moveBefore(Position);
	
	if(AfterPosition)
	{
		Position->moveBefore(loadInst_1);
		return callAsm ;
	}

	return Position ;
}

Instruction * InsertPutStackRegisterValue(Module &mod , Value* var , IRBuilder<> &builder  )
{
	
	LoadInst* loadInst_1 = builder.CreateLoad(var , "") ;// new LoadInst(var, "", false, Position);
	loadInst_1->setAlignment(4);
	InlineAsm* Asm_1 = InlineAsm::get(FuncTy_PutSp, "mov r13 , $0 ", "r",true);
	CallInst* callAsm  = builder.CreateCall (Asm_1,loadInst_1,"") ;// CallInst::Create(Asm_1, loadInst_1, "", Position);
	callAsm->setCallingConv(CallingConv::C);
	callAsm->setTailCall(false);
	AttributeSet _PAL  ;
	{
		SmallVector<AttributeSet, 4> Attrs;
		AttributeSet PAS;
		{
			AttrBuilder B;
			B.addAttribute(Attribute::NoUnwind);
			PAS = AttributeSet::get(mod.getContext(), ~0U, B);
		}
		
		Attrs.push_back(PAS);
		_PAL = AttributeSet::get(mod.getContext(), Attrs);
		
	}
	callAsm->setAttributes(_PAL);
	
	return callAsm ;
	
}


// insert stack mgt code for a function call by creating a wrapper function
//
// TODO
//		1. optimization
//		2. avoid creating and using too many global variables
//
int ic = 0 ;



bool runStackMgtPass(const Module &mod,CallGraph &cg)
{
	LLVMContext &context = mod.getContext();
	
	
	
	CallGraphNode *cgn_main = cg[mod.getFunction("main")];
	CallGraphNode::CallRecord *root;
	std::vector<std::vector<CallGraphNode::CallRecord *> > paths;
	std::unordered_set <CallGraphNode *> undecidable_cgns;
	
	//Step 0: extract all the paths from original call graph
	// Initialize root node by main function
	for (CallGraphNode::iterator cgni = cg.begin()->second->begin(),
		 cgne = cg.begin()->second->end();
		 cgni != cgne; cgni++)
	{
		if (cgni->second == cgn_main) {
			root = &*cgni;
			break;
		}
	}
	assert(CallGraphNode::iterator(root) != cg.begin()->second->end());
	
	// Step 0: Extarct all the paths from call graph rooted at main function
	auto res = extractPaths(root);
	paths = res.first;
	undecidable_cgns = res.second;
	
	DEBUG(errs() <<  "Extract paths {\n");
	// Print out all the paths
	for (size_t i = 0; i < paths.size(); i++) {
		for (size_t j = 0; j < paths[i].size(); j++) {
			if (paths[i][j]->second->getFunction())
			{
				DEBUG(errs() << "\t" << paths[i][j]->first << " " << paths[i][j]->second->getFunction()->getName() << "\t");
			}
			else
			{
				DEBUG(errs() << "\t" << paths[i][j]->first << " " << "externalNode" << "\t");
			}
		}
		DEBUG(errs() << "\n");
	}
	DEBUG(errs() << "}\n\n");
	
	// Step 1: get SSMD cuts
	std::unordered_map <unsigned, std::vector <std::pair<unsigned, std::string> > > cuts;
	// Read SSDM output file
	std::ifstream ifs;
	ifs.open("wcg_cuts.txt", std::fstream::in);
	assert(ifs.good());
	// Read function stack sizes
	DEBUG(errs() << "Reading SSDM output file...\n");
	DEBUG(errs() << "{\n");
	while (ifs.good()) {
		unsigned i, j;
		std::string func_name;
		ifs >> i >> j >> func_name;
		// Ignore white spaces after the last line
		if (func_name != "") {
			DEBUG(errs() << "\t" << i << " " << j << " " << func_name << "\n");
			cuts[i-1].push_back( std::make_pair(j-1, func_name) );
		}
	}
	ifs.close();
	
	DEBUG(errs() << "}\n\n\n");
	DEBUG(errs() << "Sorting SSDM cuts according to paths...\n");
	DEBUG(errs() << "{\n");
	
	// Sort cuts acoording to paths
	for (auto cutsi = cuts.begin(), cutse = cuts.end(); cutsi != cutse; cutsi++)
	{
		std::sort(cutsi->second.begin(), cutsi->second.end());
		DEBUG(errs() << "\tpath " << cutsi->first << " : ");
		for (size_t i = 0; i < cutsi->second.size(); i++) {
			DEBUG(errs() << cutsi->second[i].first << " " << cutsi->second[i].second << "  ");
		}
		DEBUG(errs() << "\n");
	}
	DEBUG(errs() << "}\n\n\n");
	
	
	DEBUG(errs() << "Inserting management functions according to SSDM cuts: {\n");
	
	// Step 4: Insert stack frame management functions
	// Decide the insertion points of stack frame management function according to SSDM output
	std::unordered_set <CallInst *> stack_frame_management_insert_pts;
	for (auto cuti = cuts.begin(), cute = cuts.end(); cuti != cute; cuti++) {
		for (size_t vi = 0; vi < cuti->second.size(); vi++) {
			unsigned i, j;
			std::string func_name;
			i = cuti->first;
			j = cuti->second[vi].first;
			func_name = cuti->second[vi].second;
			assert(paths[i][j]->first && paths[i][j]->second);
			CallInst *call_inst = dyn_cast<CallInst> (paths[i][j]->first);
			assert(call_inst);
			stack_frame_management_insert_pts.insert(call_inst);
		}
	}
	
	// Insert stack frame management functions according to SSDM cuts
	for (auto si = stack_frame_management_insert_pts.begin(), se = stack_frame_management_insert_pts.end(); si != se; si++) {
		CallInst *call_inst = *si;
		wrapInstListForStackMgt[call_inst] = 1;
	}
	
	DEBUG(errs() << "}\n");
	
	
	// Step 4: Insert frame management functions at self-recursive calls
	DEBUG(errs() << "Inserting frame management functions around recursive calls... {\n");
	for (std::unordered_set <CallGraphNode *>::iterator si = undecidable_cgns.begin(), se = undecidable_cgns.end(); si != se; si++) {
		CallGraphNode * cgn = *si;
		// Skip external nodes
		if (!cgn->getFunction())
		continue;
		DEBUG(errs() << cgn->getFunction()->getName() << "\n");
		for (CallGraphNode::iterator cgni = cgn->begin(), cgne = cgn->end(); cgni != cgne; cgni++) {
			// Skip non-self-recursive calls
			if (cgni->second != cgn)
			continue;
			CallInst *call_inst = dyn_cast<CallInst> (cgni->first);
			assert(call_inst);
			wrapInstListForStackMgt[call_inst] = 1 ;
		}
	}
	
	DEBUG(errs() << "}\n");
	
	
	
	
	
	DEBUG(errs() << "\n\n") ;
	return true;
}



void CreateWrapToFtnWithStackMgt (Module &mod , CallInst * call_inst)
{
	ic++;
	
	errs () << "\n 0000000 \n" ;
	
	
	GlobalVariable* gvar_spm_stack_base = mod.getGlobalVariable("_spm_stack_base");
	GlobalVariable* gvar_spm_depth = mod.getGlobalVariable("_stack_depth");
	GlobalVariable* gvar_stack = mod.getGlobalVariable("_stack");
	GlobalVariable* gvar_spm__2 = mod.getGlobalVariable("_spm__2");
	GlobalVariable* gvar_spm__1 = mod.getGlobalVariable("_spm__1");
	GlobalVariable* gvar__set_spm_   = mod.getGlobalVariable("_set_spm_");
	
	
	// Functions
	Function *func_l2g   = mod.getFunction("_l2g");
	Function *func_sstore = mod.getFunction("_sstore");
	Function *func_sload = mod.getFunction("_sload");
	
	// wrap function call
	Function * F = call_inst->getCalledFunction();
	Function * newF ;
	{
		std::stringstream inststring;
		inststring << "WrapftnCall_" << ic << "_" << call_inst->getCalledFunction()->getName().str();
		//std::string nn = inststring.str() ;
		
#define _current_sp 300
#define _return_ 200
		std::map<int , GlobalVariable*> gvars ;
		std::map<int , Type *> operand_types ;
		
		// create gv to store current sp
		{
			std::stringstream gv_spm_name  ;
			gv_spm_name << inststring.str() << "_current_sp";
			
			GlobalVariable *  gvar_currrent_spm = new
			GlobalVariable(mod, Type::getInt8PtrTy(mod.getContext()) ,false,
						   GlobalValue::ExternalLinkage,0, gv_spm_name.str());
			
			gvar_currrent_spm->setAlignment(4);
			ConstantPointerNull* const_ptr_100 = ConstantPointerNull::get( Type::getInt8PtrTy(mod.getContext()) ) ;
			gvar_currrent_spm->setInitializer(const_ptr_100);
			
			gvars[_current_sp] = gvar_currrent_spm;
		}
		
		//create FunctionType base on call inst instead of called function arg
		FunctionType* FuncTy_ ;
		{
			std::vector<Type*>FuncTy__args;
			
			for (unsigned int i = 0, n = call_inst->getNumArgOperands(); i < n; i++)
			{
				Value *operand = call_inst->getArgOperand(i);
				FuncTy__args.push_back(operand->getType() );
			}
			FuncTy_ = FunctionType::get(F->getReturnType(), FuncTy__args,false );
		}
		
		newF = Function::Create(FuncTy_,F->getLinkage() ,inststring.str() ,&mod);
		
		
		// make gv to store passed arguments
		{
			for (unsigned int i = 0, n = call_inst->getNumArgOperands(); i < n; i++)
			{
				Value *operand = call_inst->getArgOperand(i);
				operand_types[i] = operand->getType() ;
				
				if (operand->getType()->isPointerTy() )
				{
					std::stringstream gvar_name ;
					gvar_name << inststring.str() << "_" << i << "_ptr" ;
					
					PointerType* PointerTy_0 = dyn_cast<PointerType>(operand->getType());
					
					GlobalVariable* gvar_ptr_gvar = new
					GlobalVariable(mod,PointerTy_0 ,false,GlobalValue::ExternalLinkage,0,gvar_name.str());
					
					gvar_ptr_gvar->setAlignment(4);
					ConstantPointerNull* const_ptr_10 = ConstantPointerNull::get(PointerTy_0);
					gvar_ptr_gvar->setInitializer(const_ptr_10);
					
					gvars[i] = gvar_ptr_gvar;
					
				}
				else if (operand->getType()->isIntegerTy () )
				{
					std::stringstream gvar_name ;
					gvar_name << inststring.str() << "_" << i << "_int_" ;
					
					IntegerType * iType = dyn_cast<IntegerType>(operand->getType()) ;
					int bits = iType->getBitWidth ();
					GlobalVariable* gvar_int_gvar = new GlobalVariable(mod,
																	   IntegerType::get(mod.getContext(), bits)
																	   ,false, GlobalValue::ExternalLinkage,0,
																	   gvar_name.str() );
					
					gvar_int_gvar->setAlignment(bits / 8);
					ConstantInt* const_int32_11 = ConstantInt::get(mod.getContext(), APInt(bits, StringRef("0"), 10));
					gvar_int_gvar->setInitializer(const_int32_11);
					gvars[i] = gvar_int_gvar;
				}
				else if (operand->getType()->isDoubleTy () )
				{
					std::stringstream gvar_name ;
					gvar_name << inststring.str() << "_" << i << "_Double_" ;
					
					GlobalVariable* gvar_ = new GlobalVariable( mod,
															   Type::getDoubleTy(mod.getContext()),false,
															   GlobalValue::ExternalLinkage,0,
															   gvar_name.str());
					
					gvar_->setAlignment(8);
					
					ConstantFP* const_double_19 = ConstantFP::get(mod.getContext(), APFloat(0.000000e+00));
					gvar_ ->setInitializer(const_double_19);
					gvars[i] = gvar_;
				}
				
				else
				{
					errs() << "\n\n\t TODO , other types " ;
					getwchar();
				}
			}
			
			if (! F->getReturnType()->isVoidTy())
			{
				
				if (F->getReturnType()->isPointerTy() )
				{
					std::stringstream gvar_name ;
					gvar_name << "_GV__" << ic << "_RTN_ptr" ;
					
					PointerType* PointerTy_0 = dyn_cast<PointerType>(F->getReturnType()  );
					
					GlobalVariable* gvar = new
					GlobalVariable(mod,PointerTy_0 ,false,GlobalValue::ExternalLinkage,0, gvar_name.str());
					
					gvar->setAlignment(4);
					ConstantPointerNull* const_ptr_10 = ConstantPointerNull::get(PointerTy_0);
					gvar->setInitializer(const_ptr_10);
					
					gvars[ _return_ ] = gvar;
					
				}
				else if (F->getReturnType()->isIntegerTy () )
				{
					std::stringstream gvar_name ;
					gvar_name << "_GV__" << ic << "_RTN_int" ;
					
					IntegerType * iType = dyn_cast<IntegerType>(F->getReturnType()) ;
					int bits = iType->getBitWidth ();
					GlobalVariable* gvar   = new
					GlobalVariable(mod,IntegerType::get(mod.getContext(), bits),false,GlobalValue::ExternalLinkage,0,gvar_name.str() );
					
					gvar->setAlignment(bits / 8);
					ConstantInt* const_int32_11 = ConstantInt::get(mod.getContext(), APInt(bits, StringRef("0"), 10));
					gvar->setInitializer(const_int32_11);
					gvars[_return_ ] = gvar;
					
				}
				else
				{
					errs() << "\n\n\t TODO , other types " ;
					getwchar();
				}
				
				
			}
		}
		
		//for(auto gv : gvars) { errs() << "\n " << gv.first << " : " << *(gvars[gv.first])  ; }
		
		
		// build code for newF
		{
			newF->setCallingConv(CallingConv::C);
			AttributeSet   _PAL;
			{
				SmallVector<AttributeSet, 4> Attrs;
				AttributeSet PAS;
				{
					AttrBuilder B;
					B.addAttribute(Attribute::NoUnwind);
					B.addAttribute(Attribute::NoInline);
					PAS = AttributeSet::get(mod.getContext(), ~0U, B);
				}
				
				Attrs.push_back(PAS);
				_PAL = AttributeSet::get(mod.getContext(), Attrs);
				
			}
			newF->setAttributes(  _PAL);
			
			std::map<int , Value* > arg_ptr_map ;
			std::map<int , AllocaInst  * > allocaMap   ;
			
			GlobalVariable* ptr_rtn ;
			
			BasicBlock* label_entry = BasicBlock::Create(mod.getContext(), "entry",newF,0);
			IRBuilder<> B_builder(label_entry);
			
			Function::arg_iterator args = newF->arg_begin();
			for (unsigned int i = 0, n = call_inst->getNumArgOperands(); i < n; i++)
			{
				Value* arg_ptr = args++ ;
				std::string name = "arg_" ;
				name.append (std::to_string(i));
				arg_ptr->setName(name.c_str() );
				arg_ptr_map[i] = arg_ptr ;
				
			}
			
			
			for (auto v : arg_ptr_map)
			{
				std::string str =  v.second->getName().str() ; str.append (".addr");
				AllocaInst* alloca  = new AllocaInst(v.second->getType()  , str , label_entry);
				alloca->setAlignment(TD->getTypeAllocSize(v.second->getType()));
				allocaMap[v.first] = alloca ;
			}
			
			
			Instruction * inin   ;
			for (auto v : arg_ptr_map)
			{
				AllocaInst * alloca = allocaMap[v.first];
				StoreInst* void_23 = new StoreInst(v.second, alloca, false, label_entry);
				void_23->setAlignment(TD->getTypeAllocSize(v.second->getType()));
				inin = void_23 ;
			}
			
			
			LoadInst* ll_ptr_25 = new LoadInst(gvars[_current_sp ], "", false, label_entry);
			StoreInst* st_void_23 = new StoreInst(ll_ptr_25, gvar_spm__1, false, label_entry);
			InsertGetStackRegisterValue(mod,gvars[_current_sp], ll_ptr_25   );
			
			
			Instruction * iiiii ;
			
			
			for (auto v : arg_ptr_map)
			{
				AllocaInst * alloca = allocaMap[v.first];
				LoadInst* ptr_25 = new LoadInst(alloca, "", false, label_entry);
				ptr_25->setAlignment(TD->getTypeAllocSize(v.second->getType()));
				
				
				Value * vvv = ptr_25;
				
				//errs() << *  gvars[v.first] ;
				
				//errs() << "\n\tType : " <<  *  operand_types[v.first] ;
				
				
				
				if (operand_types[v.first]->isPointerTy() )
				{
					
					//Type * tt =  operand_types[v.first]->getPointerElementType () ;
					//errs() << "\n\t  cast : "  << * tt  ;
					
					if (operand_types[v.first]->getPointerElementType ()->isIntegerTy(8))
					{
						//errs() << "  no use cast : "  ;
						IRBuilder<> B_builder2(label_entry);
						//Value *l2g_arg = B_builder2.CreatePointerCast(vvv, Type::getInt8PtrTy(mod.getContext()), "l2g_arg");
						
						int DataSize = 4 ; // TD->getTypeAllocSize();
						ConstantInt* const_int32__DataSize  = ConstantInt::get(mod.getContext(),APInt(32,DataSize,true ));
						ConstantInt* const_int32__TypeKnown = ConstantInt::get(mod.getContext(),APInt(32,0,true ));
						LoadInst * ld_stack_depth = B_builder2.CreateLoad( gvar_spm_depth);
						
						// Call l2g
						
						// with the l2g mgt
						CallInst *func_l2g_call = B_builder2.CreateCall(func_l2g, {vvv , const_int32__DataSize , const_int32__TypeKnown , ld_stack_depth }  , "l2g_ret");
						
						// without the l2g mgt
						//CallInst *func_l2g_call = B_builder2.CreateCall(func_l2g, {vvv , const_int32__}  , "l2g_ret");
						
						
						
						func_l2g_call->setCallingConv(CallingConv::C);
						func_l2g_call->setTailCall(false);
						//Value *l2g_ret__ = B_builder2.CreatePointerCast(func_l2g_call, vvv->getType() , "l2g_arg2");
						vvv = func_l2g_call ;
					}
					else
					{
						//errs() << "  use cast : "  ;
						IRBuilder<> B_builder2(label_entry);
						Value *l2g_arg = B_builder2.CreatePointerCast(vvv, Type::getInt8PtrTy(mod.getContext()), "l2g_arg");
						
						
						
						
						int DataSize =  TD->getTypeAllocSize( operand_types[v.first]->getPointerElementType ());
						
						
						ConstantInt* const_int32__DataSize  = ConstantInt::get(mod.getContext(),APInt(32,DataSize,true ));
						ConstantInt* const_int32__TypeKnown = ConstantInt::get(mod.getContext(),APInt(32,1,true ));
						LoadInst * ld_stack_depth = B_builder2.CreateLoad( gvar_spm_depth);
						
						// Call l2g
						
						//errs() << "\n\tData Size:" << DataSize << " : " << *operand_types[v.first]->getPointerElementType () ;
						//<< "\n\t" <<  *vvv << "\n\t" <<  *ld_stack_depth ; // <<  "\n\t" <<  vvv;
						//errs() << "\n\t l2g: " << *func_l2g ;
						
						// with the l2g mgt
						CallInst *func_l2g_call = B_builder2.CreateCall(func_l2g, {l2g_arg , const_int32__DataSize , const_int32__TypeKnown , ld_stack_depth }  , "l2g_ret");
						
						// without the l2g mgt
						//CallInst *func_l2g_call = B_builder2.CreateCall(func_l2g, {l2g_arg , const_int32__}  , "l2g_ret");
						
						
						
						//CallInst *func_l2g_call = B_builder2.CreateCall(func_l2g, {l2g_arg , const_int32__ }, "l2g_ret");
						
						
						
						func_l2g_call->setCallingConv(CallingConv::C);
						func_l2g_call->setTailCall(false);
						Value *l2g_ret__ = B_builder2.CreatePointerCast(func_l2g_call, vvv->getType() , "l2g_arg2");
						vvv = l2g_ret__ ;
					}
					
					//errs() << * newF ;
				}
				
				
				StoreInst* void_26 = new StoreInst(vvv, gvars[v.first]  , false, label_entry);
				void_26->setAlignment(TD->getTypeAllocSize(v.second->getType()));
				
				iiiii = void_26 ;
				
			}
			
			std::vector<Value*> _call_params;
			
			
			CallInst * cccc = CallInst::Create  (func_sstore, "", iiiii );
			iiiii->moveBefore(cccc);
			
			
			InsertPutStackRegisterValue(mod,gvar_spm__2, cccc , true);
			
			
			
			for (auto v : arg_ptr_map)
			{
				LoadInst* int32_30 = new LoadInst(gvars[v.first], "", false, label_entry);
				int32_30->setAlignment(TD->getTypeAllocSize(v.second->getType()));
				_call_params.push_back(int32_30);
			}
			
			
			CallInst* _call = CallInst::Create(F, _call_params, "", label_entry);
			_call->setCallingConv(CallingConv::C);
			_call->setTailCall(false);
			
			
			if (F->getReturnType()->isVoidTy() )
			{
				CallInst * ccccc = CallInst::Create(func_sload, "", label_entry);
				InsertPutStackRegisterValue(mod,gvars[_current_sp],ccccc  );
				ReturnInst::Create(mod.getContext(),  label_entry);
			}
			else
			{
				
				StoreInst* void_31 = new StoreInst(_call, gvars[_return_], false, label_entry);
				void_31->setAlignment( TD->getTypeAllocSize(F->getReturnType()));
				
				CallInst * ccccc = CallInst::Create(func_sload, "",label_entry);
				InsertPutStackRegisterValue(mod,gvars[_current_sp],ccccc);
				
				LoadInst* int32_33 = new LoadInst(gvars[_return_], "", false, label_entry);
				int32_33->setAlignment(TD->getTypeAllocSize(F->getReturnType()));
				ReturnInst::Create(mod.getContext(), int32_33, label_entry);
			}
			
			//errs() << " " << *newF ;
		}
		
		ic ++;
	}
	
	call_inst->setCalledFunction(newF);
	
	errs() << *newF ;
	
}

Function *getOrInsertCCall(CallInst *call_inst)
{
	errs() << "ddddd" << "\n" ;
	// Get the caller
	Function* caller = call_inst->getParent()->getParent();
	// Get the called function
	Function* callee = call_inst->getCalledFunction();
	Module *mod = caller->getParent();
	LLVMContext &context = mod->getContext();
	IRBuilder <> builder(context);
	
	FunctionType* calleeTy = NULL;
	Type *retTy = NULL;
	std::vector<Type*>calleeArgTy;
	// Get the type of the called function
	calleeTy = callee->getFunctionType();
	// Get arguments types of the called function (if there are any)
	for (unsigned int i = 0, num = call_inst->getNumArgOperands(); i < num; i++) {
		calleeArgTy.push_back(call_inst->getArgOperand(i)->getType());
	}
	// Get the return type of the called function
	retTy = callee->getReturnType();
	
	// Create a pointer type to char
	PointerType *ptrTy_int8 = PointerType::get(IntegerType::get(context, 8), 0);
	
	// Create a int32 type
	IntegerType *	Int32Type = IntegerType::get(context,32);
	
	// Create a pointer type to callee type
	PointerType *calleeTyPtr = PointerType::get(calleeTy, 0);
	// Get the pointer to c_get function
	Function* func_c_get = mod->getFunction("getMgtCode");
	assert(func_c_get);
	
	Function* func_c_call =  nullptr;
	
	// Go through all the exsiting wrapper functions and check if there is any one can be used directly
	for (Module::iterator fi = mod->begin(), fe = mod->end(); fi != fe; ++fi)
	{
		if (fi->getName().count("c_call_complete") == 1) {
			//int num_args_before = 2;
			int num_args_before = 3;
			FunctionType *fiTy = fi->getFunctionType();
			// Compare the return types
			FunctionType *fiCalleeTy = (FunctionType *)(((PointerType *)fiTy->getParamType(num_args_before-1))->getElementType());
			//DEBUG(errs() << *fiCalleeTy->getReturnType() <<"\n");
			Type *fiCalleeRetTy = fiCalleeTy->getReturnType();
			if (retTy != fiCalleeRetTy ) {
				continue;
			}
			
			// Compare number of arguments
			unsigned int fiNumCalleeParams = fiTy->getNumParams() - num_args_before;
			if(calleeArgTy.size() != fiNumCalleeParams)
			continue;
			// Compare argument types
			unsigned int i = num_args_before;
			std::vector<Type*>::iterator ai = calleeArgTy.begin(), ae = calleeArgTy.end();
			while( ai!=ae) {
				if(*ai != fiTy->getParamType(i))
				break;
				ai++;
				i++;
			}
			if (ai!=ae)
			continue;
			// If all the above tests pass, then return the wrapper function
			func_c_call = fi;
			return func_c_call;
		}
	}
	
	// Create a function type for c_call it has not been created for corresponding function type
	if (!func_c_call)
	{
		std::vector<Type*> c_call_args;
		// The first parameter should be a char pointer to caller name
		c_call_args.push_back(Int32Type); // c_call_args.push_back(ptrTy_int8);
		// The second parameter should be a char pointer to callee name
		c_call_args.push_back(Int32Type) ; //	c_call_args.push_back(ptrTy_int8);
		// The third parameter should be a callee function type pointer to callee address
		c_call_args.push_back(calleeTyPtr);
		// The following parameters should be the callee arguments if passed in
		for (std::vector<Type*>::iterator ai = calleeArgTy.begin(), ae = calleeArgTy.end(); ai!=ae; ++ai)
		c_call_args.push_back(*ai);
		FunctionType* funcTy = FunctionType::get(
												 retTy,
												 c_call_args,
												 false);
		
		func_c_call = Function::Create(
									   funcTy,
									   GlobalValue::LinkOnceODRLinkage ,
									   "c_call_complete", mod);
	}
	
	assert(func_c_call);
	
	// Get arguments for c_call
	Function::arg_iterator ai = func_c_call->arg_begin();
	// Get caller name from first argument
	Value* caller_index  = ai++;
	caller_index->setName("callerIndex") ; // caller_name->setName("callername");
	// Get callee name from second argument
	Value* callee_index = ai++;
	callee_index->setName("calleeIndex") ; //	callee_name->setName("calleename");
	// Skip callee type from the third argument
	//Value* callee = ai++;
	//callee->setName("callee");
	ai++;
	// Get addresses of callee arguments from following arguments if passed in
	std::vector<Value*>callee_arg;
	for (Function::arg_iterator ae = func_c_call->arg_end(); ai!=ae; ai++) {
		static int i = 0;
		Value* arg = ai;
		arg->setName("arg" + std::to_string(i++));
		callee_arg.push_back(arg);
	}
	
	// Create the entry basic block
	BasicBlock* c_call_entry = BasicBlock::Create(context, "entry",func_c_call, 0);
	// Set insert point as the end of entry block
	builder.SetInsertPoint(c_call_entry);
	
	// Create local variables for callee arugments if passed in
	std::vector<AllocaInst*> callee_arg_addr;
	for (std::vector<Type*>::size_type i = 0; i < calleeArgTy.size(); i++)
	{
		AllocaInst* arg_addr = builder.CreateAlloca(calleeArgTy[i], nullptr, "callee_arg" + std::to_string(i));
		callee_arg_addr.push_back(arg_addr);
	}
	
	// Allocate space for return value if its type is not void
	AllocaInst* ret_val;
	if (!retTy->isVoidTy())
	{
		ret_val = builder.CreateAlloca(retTy, nullptr, "ret_val");
	}
	
	// Copy the callee arguments to the local variables if passed in
	for (std::vector<Value*>::size_type i = 0; i < callee_arg.size(); i++) {
		builder.CreateStore(callee_arg[i], callee_arg_addr[i], false);
	}
	
	// Find out the SPM address for callee
	////CallInst* callee_vma_int8 = CallInst::Create(func_c_get, callee_name, "callee_vma_int8", c_call_entry);
	CallInst * callee_vma_int8 = CallInst::Create(func_c_get, callee_index , "callee_vma_int8" , c_call_entry);
	//CallInst* callee_vma_int8 = builder.CreateCall(func_c_get, callee_name, "callee_vma_int8");
	// Cast the type of the SPM address to the function type of the callee
	CastInst* callee_vma = cast <CastInst> (builder.CreateBitCast(callee_vma_int8, calleeTyPtr, "callee_vma"));
	
	// Read callee arguments and get their values if passed in
	std::vector<Value*>callee_arg_vals;
	for (std::vector<AllocaInst*>::iterator ai = callee_arg_addr.begin(), ae = callee_arg_addr.end(); ai != ae; ai++) {
		LoadInst* arg_val = builder.CreateLoad(*ai);
		callee_arg_vals.push_back(arg_val);
	}
	
	// Call the callee
	CallInst* callee_ret;
	
	// Get return value if its type is not void
	if (!retTy->isVoidTy()) {
		callee_ret = builder.CreateCall(callee_vma, callee_arg_vals, "callee_ret_val");
		builder.CreateStore(callee_ret, ret_val, false);
	} else
	callee_ret = builder.CreateCall(callee_vma, callee_arg_vals);
	
	// Ensure the caller is present after the callee returns
	////CallInst::Create(func_c_get, caller_name, "caller_vma", c_call_entry);
	CallInst::Create (func_c_get , caller_index, "caller_vma", c_call_entry);
	
	
	//builder.CreateCall(func_c_get, caller_name, "caller_vma");
	
	// Read return value and return it if its type is not void
	if (!retTy->isVoidTy()) {
		LoadInst *ld_ret_val = builder.CreateLoad(ret_val);
		ReturnInst::Create(context, ld_ret_val, c_call_entry);
		//builder.CreateRet(ld_ret_val);
	} else {
		ReturnInst::Create(context, c_call_entry);
		//builder.CreateRetVoid();
	}
	
	errs() << *func_c_call;
	
	return func_c_call;
}

 

Function *getOrInsertCCallWithStackmgt(Module &mod, CallInst *call_inst)
{
	ic++;
	
	errs() << "\n create wrap function for : " << *call_inst << "\n";
	
	GlobalVariable* gvar_spm_stack_base = mod.getGlobalVariable("spmStackUbound");
	GlobalVariable* gvar_spm_depth = mod.getGlobalVariable("_stack_depth");
	GlobalVariable* gvar_stack = mod.getGlobalVariable("_stack");
	GlobalVariable* gvar_spm__2 = mod.getGlobalVariable("currentstackPtr");
	GlobalVariable* gvar_spm__1 = mod.getGlobalVariable("currentstackPtr");
	GlobalVariable* gvar__set_spm_   = mod.getGlobalVariable("currentstackPtr");
	
	std::stringstream inststring;
	inststring << "WrapftnCall_" << ic << "_" << call_inst->getCalledFunction()->getName().str();
	
	// Functions
	Function *func_l2g ;//  = mod.getFunction("_l2g");
	Function *func_sstore = mod.getFunction("_sstore");
	Function *func_sload = mod.getFunction("_sload");
	

	// Get the caller
	Function* caller = call_inst->getParent()->getParent();
	// Get the called function
	Function* callee = call_inst->getCalledFunction();
	LLVMContext &context = mod.getContext();
	IRBuilder <> builder(context);
	
	FunctionType* calleeTy = NULL;
	Type *retTy = NULL;
	std::vector<Type*>calleeArgTy;
	// Get the type of the called function
	calleeTy = callee->getFunctionType();
	// Get arguments types of the called function (if there are any)
	for (unsigned int i = 0, num = call_inst->getNumArgOperands(); i < num; i++)
	{
		calleeArgTy.push_back(call_inst->getArgOperand(i)->getType());
	}
	// Get the return type of the called function
	retTy = callee->getReturnType();
	
	// Create a pointer type to char
	PointerType *ptrTy_int8 = PointerType::get(IntegerType::get(context, 8), 0);
	
	// Create a int32 type
	IntegerType *	Int32Type = IntegerType::get(context,32);
	
	// Create a pointer type to callee type
	PointerType *calleeTyPtr = PointerType::get(calleeTy, 0);
	// Get the pointer to c_get function
	Function* func_c_get = mod.getFunction("getMgtCode");
	assert(func_c_get);
	
	
	////errs() << "\n" << callee->getName().str() << " : " << * calleeTy ;
	
	

#define _current_sp 300
#define _return_ 200
#define _callee_vma_ 400 
#define _caller_index_ 500
	
	std::map<int , GlobalVariable*> gvars ;

	// create gv to store current sp , callee_vma , caller_index
	{
		std::stringstream gv_spm_name  ;
		gv_spm_name << inststring.str() << "_current_sp";
		
		GlobalVariable *  gvar_currrent_spm = new
		GlobalVariable(mod, Type::getInt8PtrTy(mod.getContext()) ,false,
					   GlobalValue::ExternalLinkage,0, gv_spm_name.str());
		
		gvar_currrent_spm->setAlignment(4);
		ConstantPointerNull* const_ptr_100 = ConstantPointerNull::get( Type::getInt8PtrTy(mod.getContext()) ) ;
		gvar_currrent_spm->setInitializer(const_ptr_100);
		
		gvars[_current_sp] = gvar_currrent_spm;
		
		
		
		
		std::stringstream gv_vma_name  ;
		gv_vma_name << inststring.str() << "_callee_vma_";
		
		
		GlobalVariable *  gvar_vma  = new
		GlobalVariable(mod, Type::getInt8PtrTy(mod.getContext()) ,false,
					   GlobalValue::ExternalLinkage,0, gv_vma_name.str());
		
		gvar_vma->setAlignment(4);
		ConstantPointerNull* const_ptr_10011 = ConstantPointerNull::get( Type::getInt8PtrTy(mod.getContext()) ) ;
		//Constant  * contsss11 = ConstantPointer::get( Type::getInt8Ty(mod.getContext()) , APInt(32 ,  0) ) ;
		
		gvar_vma->setInitializer( const_ptr_10011);
		
		gvars[_callee_vma_] = gvar_vma;

		
		
		
		std::stringstream gv_index_str     ;
		gv_index_str   << inststring.str() << "_caller_index_";
		
		
		GlobalVariable *  gv_index  = new
		GlobalVariable(mod, Type::getInt32Ty(mod.getContext()) ,false,
					   GlobalValue::ExternalLinkage,0, gv_index_str.str());
		
		gv_index->setAlignment(4);
		Constant  * contsss = ConstantInt::get( Type::getInt32Ty(mod.getContext()) , APInt(32 ,  0) ) ;
		
		gv_index->setInitializer(contsss);
		
		gvars[_caller_index_] = gv_index;

		
	}
	
	
	// Create local variables for callee arugments if passed in
	//we will use gv
	//std::vector<AllocaInst*> callee_arg_addr;
	
	for (int i = 0; i < calleeArgTy.size(); i++)
	{
	//	AllocaInst* arg_addr = builder.CreateAlloca(calleeArgTy[i], nullptr, "callee_arg" + std::to_string(i));
	//	callee_arg_addr.push_back(arg_addr);
		//we will use gv
		
			//Value *operand = call_inst->getArgOperand(i);
			//operand_types[i] = operand->getType() ;
			
			
			Type * Ty = calleeArgTy[i];
			
			if (Ty->isPointerTy() )
			{
				std::stringstream gvar_name ;
				gvar_name << inststring.str() << "_" << i << "_ptr" ;
				
				PointerType* PointerTy_0 = dyn_cast<PointerType>(Ty );
				
				GlobalVariable* gvar_ptr_gvar = new
				GlobalVariable(mod,PointerTy_0 ,false,GlobalValue::ExternalLinkage,0,gvar_name.str());
				
				gvar_ptr_gvar->setAlignment(4);
				ConstantPointerNull* const_ptr_10 = ConstantPointerNull::get(PointerTy_0);
				gvar_ptr_gvar->setInitializer(const_ptr_10);
				
				gvars[i] = gvar_ptr_gvar;
				
			}
			else if (Ty->isIntegerTy () )
			{
				std::stringstream gvar_name ;
				gvar_name << inststring.str() << "_" << i << "_int_" ;
				
				IntegerType * iType = dyn_cast<IntegerType>(Ty ) ;
				int bits = iType->getBitWidth ();
				GlobalVariable* gvar_int_gvar = new GlobalVariable(mod,
																   IntegerType::get(mod.getContext(), bits)
																   ,false, GlobalValue::ExternalLinkage,0,
																   gvar_name.str() );
				
				gvar_int_gvar->setAlignment(bits / 8);
				ConstantInt* const_int32_11 = ConstantInt::get(mod.getContext(), APInt(bits, StringRef("0"), 10));
				gvar_int_gvar->setInitializer(const_int32_11);
				gvars[i] = gvar_int_gvar;
			}
			else if (Ty->isDoubleTy () )
			{
				std::stringstream gvar_name ;
				gvar_name << inststring.str() << "_" << i << "_Double_" ;
				
				GlobalVariable* gvar_ = new GlobalVariable( mod,
														   Type::getDoubleTy(mod.getContext()),false,
														   GlobalValue::ExternalLinkage,0,
														   gvar_name.str());
				
				gvar_->setAlignment(8);
				
				ConstantFP* const_double_19 = ConstantFP::get(mod.getContext(), APFloat(0.000000e+00));
				gvar_ ->setInitializer(const_double_19);
				gvars[i] = gvar_;
			}
			else if (Ty->isStructTy ()){
				
				StructType *T = dyn_cast<StructType>(Ty) ;
				
				int sizeInByte   = TD->getTypeAllocSize(T) ;
				errs() << "\n\n\t TODO 122, other types " << *T <<"(" << *Ty << ")"<< "  size :" << sizeInByte << "\n" ;
				
				std::stringstream gvar_name ;
				gvar_name << inststring.str() << "_" << i << "_Struct_" ;
				
				GlobalVariable* gvar_ = new GlobalVariable( mod,
														   T,false,
														   GlobalValue::CommonLinkage ,0,
														   gvar_name.str());
				
				
				//gvar_->setAlignment(sizeInByte );
				
				
				// contruct array of zero constants for initializer
				//std::vector<Constant *> contantsA ;
				
				
			
				//Constant* ContInitializer = ConstantStruct::get(T);
				//mod.getContext(), APInt(sizeInByte * 8 , StringRef("0"), 10));
				
				 
				//gvar_ ->setInitializer(ContInitializer);
				gvars[i] = gvar_;

				
				getwchar();

				
			}else 
			{
				errs() << "\n\n\t TODO 125, other types " << *Ty  ;
				
				
				
				getwchar();
			}

		
	
	}
	
	if (! retTy->isVoidTy())
	{
		
		if (retTy->isPointerTy() )
		{
			std::stringstream gvar_name ;
			gvar_name << "_GV__" << ic << "_RTN_ptr" ;
			
			PointerType* PointerTy_0 = dyn_cast<PointerType>(retTy    );
			
			GlobalVariable* gvar = new
			GlobalVariable(mod,PointerTy_0 ,false,GlobalValue::ExternalLinkage,0, gvar_name.str());
			
			gvar->setAlignment(4);
			ConstantPointerNull* const_ptr_10 = ConstantPointerNull::get(PointerTy_0);
			gvar->setInitializer(const_ptr_10);
			
			gvars[ _return_ ] = gvar;
			
		}
		else if (retTy->isIntegerTy () )
		{
			std::stringstream gvar_name ;
			gvar_name << "_GV__" << ic << "_RTN_int" ;
			
			IntegerType * iType = dyn_cast<IntegerType>(retTy ) ;
			int bits = iType->getBitWidth ();
			GlobalVariable* gvar   = new
			GlobalVariable(mod,IntegerType::get(mod.getContext(), bits),false,GlobalValue::ExternalLinkage,0,gvar_name.str() );
			
			gvar->setAlignment(bits / 8);
			ConstantInt* const_int32_11 = ConstantInt::get(mod.getContext(), APInt(bits, StringRef("0"), 10));
			gvar->setInitializer(const_int32_11);
			gvars[_return_ ] = gvar;
			
		}
		else
		{
			errs() << "\n\n\t TODO 123, other types " << *retTy  ;
			getwchar();
		}
		
		
	}

	
	
	// Create a function type for c_call it has not been created for corresponding function type
	Function* func_c_call =  nullptr;
	std::map<int , Value *> New_func_callee_arg ;
	Value* caller_index;
	Value* callee_index ;
	
	
	//if (!func_c_call)
	{
		std::vector<Type*> c_call_args;
		// The first parameter should be a char pointer to caller name
		c_call_args.push_back(Int32Type); // c_call_args.push_back(ptrTy_int8);
		// The second parameter should be a char pointer to callee name
		c_call_args.push_back(Int32Type) ; //	c_call_args.push_back(ptrTy_int8);
		// The third parameter should be a callee function type pointer to callee address
		c_call_args.push_back(calleeTyPtr);
		// The following parameters should be the callee arguments if passed in
		for (std::vector<Type*>::iterator ai = calleeArgTy.begin(), ae = calleeArgTy.end(); ai!=ae; ++ai)
		c_call_args.push_back(*ai);
		FunctionType* funcTy = FunctionType::get(
												 retTy,
												 c_call_args,
												 false);
		std::stringstream inststring;
		inststring << "c_call_code_stack_" << ic ;
		
		func_c_call = Function::Create(
									   funcTy,
									   GlobalValue::LinkOnceODRLinkage ,
									   inststring.str().c_str() , &mod);
		
		func_c_call->setCallingConv(CallingConv::C);
		AttributeSet   _PAL;
		{
			SmallVector<AttributeSet, 4> Attrs;
			AttributeSet PAS;
			{
				AttrBuilder B;
				B.addAttribute(Attribute::NoUnwind);
				B.addAttribute(Attribute::NoInline);
				PAS = AttributeSet::get(mod.getContext(), ~0U, B);
			}
			
			Attrs.push_back(PAS);
			_PAL = AttributeSet::get(mod.getContext(), Attrs);
			
		}
		func_c_call->setAttributes(  _PAL);
		
		
		
	////	errs() << "\n ======= " << * func_c_call << "\n +++++++ \n" ;
		
		// set name of arg
		
		Function::arg_iterator args = func_c_call->arg_begin();
		
		
			// Get arguments for c_call
			//Function::arg_iterator ai = func_c_call->arg_begin();
			// Get caller name from first argument
			caller_index  = args++;
			caller_index->setName("callerIndex") ; // caller_name->setName("callername");
			// Get callee name from second argument
			 callee_index = args++;
			callee_index->setName("calleeIndex") ; //	callee_name->setName("calleename");
		
			args++;

		for (int i = 0; i < calleeArgTy.size(); i++)
		//for (unsigned int i = 0, n = call_inst->getNumArgOperands(); i < n; i++)
		{
			Value* arg_ptr = args++ ;
			std::string name = "arg_" ;
			name.append (std::to_string(i));
			arg_ptr->setName(name.c_str() );
			New_func_callee_arg[i] = arg_ptr ;
			
		}
	}
	
	assert(func_c_call);
	
	//// errs() << "\n ======= " << * func_c_call << "\n +++++++ \n" ;
	
	// Create the entry basic block
	BasicBlock* c_call_entry = BasicBlock::Create(context, "entry",func_c_call, 0);
	// Set insert point as the end of entry block
	builder.SetInsertPoint(c_call_entry);
	
	//// errs() << "\n ======= " << * func_c_call << "\n +++++++ \n" ;
	

	// store passed in arg to the gv
	for (int  i = 0; i < calleeArgTy.size(); i++)
	{
		Type * Ty = calleeArgTy[i];
		//AllocaInst * alloca = allocaMap[v.first];
		
		errs() << "\n  -- " << * New_func_callee_arg[i] ;
		errs() << "\n  -- " << *  gvars[i]  ;
		
		
		StoreInst* void_23 = builder.CreateStore(New_func_callee_arg[i], gvars[i] );
		void_23->setAlignment(TD->getTypeAllocSize(Ty));
		//inin = void_23 ;
	}
	
	// store caller_index
	(builder.CreateStore(caller_index , gvars[_caller_index_] ))->setAlignment(4);
	
	////errs() << "\n ======= " << * func_c_call << "\n +++++++ \n" ;
	
	{
		// c_call_args.push_back(*ai);
//		
//		yyyyyy(mod);
//		
//		GlobalVariable* std_fList = mod.getGlobalVariable("std_functions");
//		errs() << * std_fList ;
//		
//		//errs() << "\n    " << * stdcall ;
//		//IRBuilder<> builder(stdcall->getParent()) ;
//		//builder.SetInsertPoint(stdcall);
//		Value * formatstr = builder.CreateGlobalStringPtr( "\n get code %u \n" );
//		
//		Value * ld = builder. CreateLoad(std_fList,"load_stdfunctionptr");
//		Constant * constant  = builder.getInt32(FPRINTF);
//		Value * idx = builder.CreateInBoundsGEP(ld,constant ) ;
//		Value * ld2 = builder.CreateLoad(idx);
//		CastInst* castinst  = cast <CastInst> (builder.CreateBitCast(ld2, printf____->getType() ));
//		
//		std::vector<Value *>fprintfArgs;
//		fprintfArgs.push_back(formatstr);
//		fprintfArgs.push_back(callee_index);
//		builder.CreateCall (castinst , fprintfArgs , "call_fprintf");
//		errs() << "\n ======= " << * func_c_call << "\n +++++++ \n" ;
		
	}
	
	
	// get the stack pointer
	InsertGetStackRegisterValue(mod,gvars[_current_sp], builder   );
	LoadInst* ll_ptr_25 = builder.CreateLoad (gvars[_current_sp ]);
	StoreInst* st_void_23 = builder.CreateStore (ll_ptr_25, gvar_spm__1);
	
	
	////errs() << "\n ======= " << * func_c_call << "\n +++++++ \n" ;
	
	
	
	
	
	// Find out the SPM address for callee
	////CallInst* callee_vma_int8 = CallInst::Create(func_c_get, callee_name, "callee_vma_int8", c_call_entry);
	CallInst * callee_vma_int8 = builder.CreateCall(func_c_get, callee_index , "callee_vma_int8" ) ; //, c_call_entry);
	//CallInst* callee_vma_int8 = builder.CreateCall(func_c_get, callee_name, "callee_vma_int8");
	// Cast the type of the SPM address to the function type of the callee
	(builder.CreateStore(callee_vma_int8 , gvars[_callee_vma_] ))->setAlignment(4);
	
	
	
	//// errs() << "\n ======= " << * func_c_call << "\n +++++++ \n" ;
	
	
	// resolve passed in arg that are pointer types with l2g mgt function
	for (int  i = 0; i < calleeArgTy.size(); i++)
	{
		Type * Ty = calleeArgTy[i];
	//for (auto v : arg_ptr_map)
	//{
	//	AllocaInst * alloca = allocaMap[v.first];
	//	LoadInst* ptr_25 = new LoadInst(alloca, "", false, label_entry);
	//	ptr_25->setAlignment(TD->getTypeAllocSize(v.second->getType()));
		
		
	//	Value * vvv = ptr_25;
		
		//errs() << *  gvars[v.first] ;
		
		//errs() << "\n\tType : " <<  *  operand_types[v.first] ;
		
		
		
	//	if (operand_types[v.first]->isPointerTy() )
		//if (Ty->isPointerTy())
		while (0)
		{
			
			//Type * tt =  operand_types[v.first]->getPointerElementType () ;
			//errs() << "\n\t  cast : "  << * tt  ;
			
			Value * passed_in_value ;
			//= builder.CreateLoad(gvars[i]);
			
			//if (operand_types[v.first]->getPointerElementType ()->isIntegerTy(8))
			if (Ty->getPointerElementType()->isIntegerTy(8))
			{
				//errs() << "  no use cast : "  ;
				////IRBuilder<> B_builder2(label_entry);
				//Value *l2g_arg = B_builder2.CreatePointerCast(vvv, Type::getInt8PtrTy(mod.getContext()), "l2g_arg");
				
				 passed_in_value = builder.CreateLoad(gvars[i]);
				
				int DataSize = 4 ; // TD->getTypeAllocSize();
				ConstantInt* const_int32__DataSize  = builder.getInt32(DataSize);// ConstantInt::get(mod.getContext(),APInt(32,DataSize,true ));
				ConstantInt* const_int32__TypeKnown = builder.getInt32(0) ; // ConstantInt::get(mod.getContext(),APInt(32,0,true ));
				LoadInst * ld_stack_depth = builder.CreateLoad( gvar_spm_depth);
				
				// Call l2g
				
				// with the l2g mgt
				CallInst *func_l2g_call = builder.CreateCall(func_l2g, {passed_in_value , const_int32__DataSize , const_int32__TypeKnown , ld_stack_depth }  , "l2g_ret");
				
				// without the l2g mgt
				//CallInst *func_l2g_call = B_builder2.CreateCall(func_l2g, {vvv , const_int32__}  , "l2g_ret");
				
				
				
				func_l2g_call->setCallingConv(CallingConv::C);
				func_l2g_call->setTailCall(false);
				//Value *l2g_ret__ = B_builder2.CreatePointerCast(func_l2g_call, vvv->getType() , "l2g_arg2");
				//vvv = func_l2g_call ;
				passed_in_value = func_l2g_call;
				
				//// errs() << "\n ======= " << * func_c_call << "\n +++++++ \n" ;
				
			}
			else
			{
				 passed_in_value = builder.CreateLoad(gvars[i]);
				
				
				//errs() << "  use cast : "  ;
				//IRBuilder<> B_builder2(label_entry);
				Value *l2g_arg = builder.CreatePointerCast(passed_in_value, Type::getInt8PtrTy(mod.getContext()), "l2g_arg");
				
				
				
				
				int DataSize =  TD->getTypeAllocSize(Ty->getPointerElementType ());
				
				
				ConstantInt* const_int32__DataSize  = builder.getInt32(DataSize); //ConstantInt::get(mod.getContext(),APInt(32,DataSize,true ));
				ConstantInt* const_int32__TypeKnown = builder.getInt32(1) ;// ConstantInt::get(mod.getContext(),APInt(32,1,true ));
				LoadInst * ld_stack_depth = builder.CreateLoad( gvar_spm_depth);
				
				// Call l2g
				
				//errs() << "\n\tData Size:" << DataSize << " : " << *operand_types[v.first]->getPointerElementType () ;
				//<< "\n\t" <<  *vvv << "\n\t" <<  *ld_stack_depth ; // <<  "\n\t" <<  vvv;
				//errs() << "\n\t l2g: " << *func_l2g ;
				
				// with the l2g mgt
				CallInst *func_l2g_call = builder.CreateCall(func_l2g, {l2g_arg , const_int32__DataSize , const_int32__TypeKnown , ld_stack_depth }  , "l2g_ret");
				
				// without the l2g mgt
				//CallInst *func_l2g_call = B_builder2.CreateCall(func_l2g, {l2g_arg , const_int32__}  , "l2g_ret");
				
				
				
				//CallInst *func_l2g_call = B_builder2.CreateCall(func_l2g, {l2g_arg , const_int32__ }, "l2g_ret");
				
				
				
				func_l2g_call->setCallingConv(CallingConv::C);
				func_l2g_call->setTailCall(false);
				Value *l2g_ret__ = builder.CreatePointerCast(func_l2g_call, Ty , "l2g_arg2");
				
				passed_in_value = l2g_ret__ ;
				
				//// errs() << "\n ======= " << * func_c_call << "\n +++++++ \n" ;
				
				//vvv = l2g_ret__ ;
			}
			
			//errs() << * newF ;
		
		
		
		StoreInst* void_26 = builder.CreateStore(passed_in_value , gvars[i] ); //, false, label_entry);
		void_26->setAlignment(TD->getTypeAllocSize(Ty));
		
		//iiiii = void_26 ;
		
			//// errs() << "\n ======= " << * func_c_call << "\n +++++++ \n" ;
			
		}
		
	}
							  
	//// errs() << "\n ======= " << * func_c_call << "\n +++++++ \n" ;
	
	
	//Value * str = builder.CreateGlobalStringPtr(  " after _l2g " );
	//builder.CreateCall(mod.getFunction("__dummy__fflushStdout") , {str} );
	
	
	
	builder.CreateCall(	func_sstore);
	
	{
	Value * formatstr = builder.CreateGlobalStringPtr( "\n gvar_spm__2:0x%p" );
	LoadInst * addr  = builder.CreateLoad (gvar_spm__2);
	builder.CreateCall(mod.getFunction("debugMsgAddr") ,{ formatstr , addr });
	}
	
	
	InsertPutStackRegisterValue(mod,gvar_spm__2, builder) ;// cccc , true);
	
	
	////errs() << "\n ======= " << * func_c_call << "\n +++++++ \n" ;
	
	std::vector<Value*> _call_params;
	
	
	for (int  i = 0; i < calleeArgTy.size(); i++)
	{
		Type * Ty = calleeArgTy[i];
		
	//for (auto v : arg_ptr_map)
	//{
		LoadInst* int32_30 = builder.CreateLoad(gvars[i]); // new LoadInst(gvars[i] , "", false, label_entry);
		int32_30->setAlignment(TD->getTypeAllocSize(Ty)) ;// v.second->getType()));
		_call_params.push_back(int32_30);
	}
	
	//// errs() << "\n ======= " << * func_c_call << "\n +++++++ \n" ;
	
	
	Value * callee_vma__ = builder.CreateLoad(gvars[_callee_vma_]);
	
	CastInst* callee_vma = cast <CastInst> (builder.CreateBitCast(callee_vma__, calleeTyPtr, "callee_vma"));
	
	
	////errs() << "\n ======= " << * func_c_call << "\n +++++++ \n" ;
	
	
	CallInst* _call = builder.CreateCall(callee_vma , _call_params,""); // CallInst::Create(callee_vma, _call_params, "", label_entry);
	_call->setCallingConv(CallingConv::C);
	_call->setTailCall(false);

	//// errs() << "\n ======= " << * func_c_call << "\n +++++++ \n" ;
	
	
	if ( func_c_call ->getReturnType()->isVoidTy() )
	{
		Value * lddd =  builder.CreateLoad(gvars[_caller_index_]);
		builder.CreateCall(func_c_get , lddd, "caller_vma");// CallInst::Create (func_c_get , caller_index, "caller_vma", c_call_entry);
		
		InsertPutStackRegisterValue(mod,gvars[_current_sp],builder) ;// ccccc  );
		CallInst * ccccc = builder.CreateCall(func_sload); // CallInst::Create(func_sload, "", label_entry);
		builder.CreateRetVoid(); //		ReturnInst::Create(mod.getContext(),  label_entry);
		
		//// errs() << "\n ======= " << * func_c_call << "\n +++++++ \n" ;
		
	}
	else
	{
		
		
		
		StoreInst* void_31 = builder.CreateStore(_call ,gvars[_return_]) ;// new StoreInst(_call, gvars[_return_], false, label_entry);
		void_31->setAlignment( TD->getTypeAllocSize(func_c_call  ->getReturnType()));
		
		Value * lddd =  builder.CreateLoad(gvars[_caller_index_]);
		builder.CreateCall(func_c_get , lddd, "caller_vma");// CallInst::Create (func_c_get , caller_index, "caller_vma", c_call_entry);
		
		//// errs() << "\n ======= " << * func_c_call << "\n +++++++ \n" ;
		
		
		
		InsertPutStackRegisterValue(mod,gvars[_current_sp],builder) ;// ccccc  );
		CallInst * ccccc = builder.CreateCall(func_sload); // CallInst::Create(func_sload, "", label_entry);
		LoadInst * ld =  builder.CreateLoad(gvars[_return_]);
		builder.CreateRet(ld); //
		
		//// errs() << "\n ======= " << * func_c_call << "\n +++++++ \n" ;
		
		
//		CallInst * ccccc =   CallInst::Create(func_sload, "",label_entry);
//		InsertPutStackRegisterValue(mod,gvars[_current_sp],ccccc);
//		
//		LoadInst* int32_33 = new LoadInst(gvars[_return_], "", false, label_entry);
//		int32_33->setAlignment(TD->getTypeAllocSize(F->getReturnType()));
//		ReturnInst::Create(mod.getContext(), int32_33, label_entry);
	}
	
	
	
	//// errs()<< "\n END ======= " << * func_c_call << "\n +++++++ \n" ;
	
	
	//errs() << *func_c_call;
	
	return func_c_call;
}



void CCC (Module &mod , CallInst * c , int mgtFlag)
{
	std::vector<Value*> call_args;
	
	// LLVM context
	LLVMContext &context = mod.getContext();
	// IR builder
	
	
	
	
	//for (auto I : wrapInstListForCodeMgt   )
	{
		IRBuilder<> builder(context);
		// Call graph
		//CallGraph &cg = getAnalysis<CallGraphWrapperPass>().getCallGraph();
		
		// Types
		IntegerType *ty_int8 = builder.getInt8Ty();
		
		CallInst *call_inst = c ; // I.first;
		BasicBlock::iterator it(call_inst);
		//AnalysisResult calleeAnalysis = ii->second.first;
		//AnalysisResult callerAnalysis = ii->second.second;
		BasicBlock *bb = call_inst->getParent();
		
		Function *caller = bb->getParent();
		Function *callee = call_inst->getCalledFunction();
		
		assert(bb && caller && callee);
		
		errs() <<  caller->getName().str() ;
		errs() <<  callee->getName().str() ;
		assert(referredFuncs.find(caller) != referredFuncs.end());
		
		
		// IRBuilder::SetInsertPoint must be called before builder can be used(?)
		builder.SetInsertPoint(call_inst);
		Value *caller_name = funcNameStr[caller];
		Value *callee_name = funcNameStr[callee];
		
		unsigned int callee_index = funcIndex[callee];
		unsigned int caller_index = funcIndex[caller];
		
		if (callee_index == 0 || caller_index == 0 )
		{
			errs() << "\n Fail \n    " << * call_inst << "\n    caller:"<< caller_index << ": " << caller->getName().str() << "\n    callee:" << callee_index << ": " << callee->getName().str() ;
			assert(false);
		}
		
		{
			//DEBUG(errs() << "\tcalls " << callee->getName() <<" (U)\n");
			// Create a wrapper function for callee
			Function *func_c_call ;
			if (mgtFlag == 1 || mgtFlag == 3) 
				func_c_call = getOrInsertCCallWithStackmgt(mod ,call_inst);
			else 
				func_c_call = getOrInsertCCall(call_inst);
			
			//errs() << " \n New function " <<  func_c_call->getName().str() << * func_c_call->getType() ;
			
			// Pass arguments to the pointer to the wraper function
			std::vector<Value*> call_args;
			
			// Pass caller name with char* type as the first argument
			call_args.push_back(builder.getInt32(caller_index)); // call_args.push_back(caller_name);
			// Pass callee name as the second argument
			call_args.push_back(builder.getInt32(callee_index)); // call_args.push_back(callee_name);
			// Pass callee address as the third argument
			call_args.push_back(callee);
			// Pass callee arguments if there are any as the following arguments
			for (unsigned int i = 0, num = call_inst->getNumArgOperands(); i < num; i++) {
				call_args.push_back(call_inst->getArgOperand(i));
			}
			// Create a new call instruction to the wrapper function
			CallInst* call_c_call = CallInst::Create(func_c_call, call_args);
			// Replace all the uses of the original call instruction with the new call instruction
			ReplaceInstWithInst(call_inst->getParent()->getInstList(), it, call_c_call);
			
			InsertDebugMsg(mod , func_c_call);
			
		}
		
		
		
		
		
		
		
		
		
		
		//CreateWrapperFtn(mod , I.first);
	}
	
	
	
	
}






//
//void CreateWrapToFtnWithStackMgt (Module &mod , CallInst * call_inst)
//{
//	ic++;
//	
//	GlobalVariable* gvar_spm_stack_base = mod.getGlobalVariable("_spm_stack_base");
//	GlobalVariable* gvar_spm_depth = mod.getGlobalVariable("_stack_depth");
//	GlobalVariable* gvar_stack = mod.getGlobalVariable("_stack");
//	GlobalVariable* gvar_spm__2 = mod.getGlobalVariable("_spm__2");
//	GlobalVariable* gvar_spm__1 = mod.getGlobalVariable("_spm__1");
//	GlobalVariable* gvar__set_spm_   = mod.getGlobalVariable("_set_spm_");
//	
//	
//	// Functions
//	Function *func_l2g   = mod.getFunction("_l2g");
//	Function *func_sstore = mod.getFunction("_sstore");
//	Function *func_sload = mod.getFunction("_sload");
//	
//	// wrap function call
//	Function * F = call_inst->getCalledFunction();
//	Function * newF ;
//	{
//		std::stringstream inststring;
//		inststring << "WrapftnCall_" << ic << "_" << call_inst->getCalledFunction()->getName().str();
//		//std::string nn = inststring.str() ;
//		
//#define _current_sp 300
//#define _return_ 200
//		std::map<int , GlobalVariable*> gvars ;
//		std::map<int , Type *> operand_types ;
//		
//		// create gv to store current sp
//		{
//			std::stringstream gv_spm_name  ;
//			gv_spm_name << inststring.str() << "_current_sp";
//			
//			GlobalVariable *  gvar_currrent_spm = new
//			GlobalVariable(mod, Type::getInt8PtrTy(mod.getContext()) ,false,
//						   GlobalValue::ExternalLinkage,0, gv_spm_name.str());
//			
//			gvar_currrent_spm->setAlignment(4);
//			ConstantPointerNull* const_ptr_100 = ConstantPointerNull::get( Type::getInt8PtrTy(mod.getContext()) ) ;
//			gvar_currrent_spm->setInitializer(const_ptr_100);
//			
//			gvars[_current_sp] = gvar_currrent_spm;
//		}
//		
//		//create FunctionType base on call inst instead of called function arg
//		FunctionType* FuncTy_ ;
//		{
//			std::vector<Type*>FuncTy__args;
//			
//			for (unsigned int i = 0, n = call_inst->getNumArgOperands(); i < n; i++)
//			{
//				Value *operand = call_inst->getArgOperand(i);
//				FuncTy__args.push_back(operand->getType() );
//			}
//			FuncTy_ = FunctionType::get(F->getReturnType(), FuncTy__args,false );
//		}
//		
//		newF = Function::Create(FuncTy_,F->getLinkage() ,inststring.str() ,&mod);
//		
//		
//		// make gv to store passed arguments
//		{
//			for (unsigned int i = 0, n = call_inst->getNumArgOperands(); i < n; i++)
//			{
//				Value *operand = call_inst->getArgOperand(i);
//				operand_types[i] = operand->getType() ;
//				
//				if (operand->getType()->isPointerTy() )
//				{
//					std::stringstream gvar_name ;
//					gvar_name << inststring.str() << "_" << i << "_ptr" ;
//					
//					PointerType* PointerTy_0 = dyn_cast<PointerType>(operand->getType());
//					
//					GlobalVariable* gvar_ptr_gvar = new
//					GlobalVariable(mod,PointerTy_0 ,false,GlobalValue::ExternalLinkage,0,gvar_name.str());
//					
//					gvar_ptr_gvar->setAlignment(4);
//					ConstantPointerNull* const_ptr_10 = ConstantPointerNull::get(PointerTy_0);
//					gvar_ptr_gvar->setInitializer(const_ptr_10);
//					
//					gvars[i] = gvar_ptr_gvar;
//					
//				}
//				else if (operand->getType()->isIntegerTy () )
//				{
//					std::stringstream gvar_name ;
//					gvar_name << inststring.str() << "_" << i << "_int_" ;
//					
//					IntegerType * iType = dyn_cast<IntegerType>(operand->getType()) ;
//					int bits = iType->getBitWidth ();
//					GlobalVariable* gvar_int_gvar = new GlobalVariable(mod,
//																	   IntegerType::get(mod.getContext(), bits)
//																	   ,false, GlobalValue::ExternalLinkage,0,
//																	   gvar_name.str() );
//					
//					gvar_int_gvar->setAlignment(bits / 8);
//					ConstantInt* const_int32_11 = ConstantInt::get(mod.getContext(), APInt(bits, StringRef("0"), 10));
//					gvar_int_gvar->setInitializer(const_int32_11);
//					gvars[i] = gvar_int_gvar;
//				}
//				else if (operand->getType()->isDoubleTy () )
//				{
//					std::stringstream gvar_name ;
//					gvar_name << inststring.str() << "_" << i << "_Double_" ;
//					
//					GlobalVariable* gvar_ = new GlobalVariable( mod,
//															   Type::getDoubleTy(mod.getContext()),false,
//															   GlobalValue::ExternalLinkage,0,
//															   gvar_name.str());
//					
//					gvar_->setAlignment(8);
//					
//					ConstantFP* const_double_19 = ConstantFP::get(mod.getContext(), APFloat(0.000000e+00));
//					gvar_ ->setInitializer(const_double_19);
//					gvars[i] = gvar_;
//				}
//				
//				else
//				{
//					errs() << "\n\n\t TODO , other types " ;
//					getwchar();
//				}
//			}
//			
//			if (! F->getReturnType()->isVoidTy())
//			{
//				
//				if (F->getReturnType()->isPointerTy() )
//				{
//					std::stringstream gvar_name ;
//					gvar_name << "_GV__" << ic << "_RTN_ptr" ;
//					
//					PointerType* PointerTy_0 = dyn_cast<PointerType>(F->getReturnType()  );
//					
//					GlobalVariable* gvar = new
//					GlobalVariable(mod,PointerTy_0 ,false,GlobalValue::ExternalLinkage,0, gvar_name.str());
//					
//					gvar->setAlignment(4);
//					ConstantPointerNull* const_ptr_10 = ConstantPointerNull::get(PointerTy_0);
//					gvar->setInitializer(const_ptr_10);
//					
//					gvars[ _return_ ] = gvar;
//					
//				}
//				else if (F->getReturnType()->isIntegerTy () )
//				{
//					std::stringstream gvar_name ;
//					gvar_name << "_GV__" << ic << "_RTN_int" ;
//					
//					IntegerType * iType = dyn_cast<IntegerType>(F->getReturnType()) ;
//					int bits = iType->getBitWidth ();
//					GlobalVariable* gvar   = new
//					GlobalVariable(mod,IntegerType::get(mod.getContext(), bits),false,GlobalValue::ExternalLinkage,0,gvar_name.str() );
//					
//					gvar->setAlignment(bits / 8);
//					ConstantInt* const_int32_11 = ConstantInt::get(mod.getContext(), APInt(bits, StringRef("0"), 10));
//					gvar->setInitializer(const_int32_11);
//					gvars[_return_ ] = gvar;
//					
//				}
//				else
//				{
//					errs() << "\n\n\t TODO , other types " ;
//					getwchar();
//				}
//				
//				
//			}
//		}
//		
//		//for(auto gv : gvars) { errs() << "\n " << gv.first << " : " << *(gvars[gv.first])  ; }
//		
//		
//		// build code for newF
//		{
//			newF->setCallingConv(CallingConv::C);
//			AttributeSet   _PAL;
//			{
//				SmallVector<AttributeSet, 4> Attrs;
//				AttributeSet PAS;
//				{
//					AttrBuilder B;
//					B.addAttribute(Attribute::NoUnwind);
//					B.addAttribute(Attribute::NoInline);
//					PAS = AttributeSet::get(mod.getContext(), ~0U, B);
//				}
//				
//				Attrs.push_back(PAS);
//				_PAL = AttributeSet::get(mod.getContext(), Attrs);
//				
//			}
//			newF->setAttributes(  _PAL);
//			
//			std::map<int , Value* > arg_ptr_map ;
//			std::map<int , AllocaInst  * > allocaMap   ;
//			
//			GlobalVariable* ptr_rtn ;
//			
//			BasicBlock* label_entry = BasicBlock::Create(mod.getContext(), "entry",newF,0);
//			IRBuilder<> B_builder(label_entry);
//			
//			Function::arg_iterator args = newF->arg_begin();
//			for (unsigned int i = 0, n = call_inst->getNumArgOperands(); i < n; i++)
//			{
//				Value* arg_ptr = args++ ;
//				std::string name = "arg_" ;
//				name.append (std::to_string(i));
//				arg_ptr->setName(name.c_str() );
//				arg_ptr_map[i] = arg_ptr ;
//				
//			}
//			
//			
//			for (auto v : arg_ptr_map)
//			{
//				std::string str =  v.second->getName().str() ; str.append (".addr");
//				AllocaInst* alloca  = new AllocaInst(v.second->getType()  , str , label_entry);
//				alloca->setAlignment(TD->getTypeAllocSize(v.second->getType()));
//				allocaMap[v.first] = alloca ;
//			}
//			
//			
//			Instruction * inin   ;
//			for (auto v : arg_ptr_map)
//			{
//				AllocaInst * alloca = allocaMap[v.first];
//				StoreInst* void_23 = new StoreInst(v.second, alloca, false, label_entry);
//				void_23->setAlignment(TD->getTypeAllocSize(v.second->getType()));
//				inin = void_23 ;
//			}
//			
//			
//			LoadInst* ll_ptr_25 = new LoadInst(gvars[_current_sp ], "", false, label_entry);
//			StoreInst* st_void_23 = new StoreInst(ll_ptr_25, gvar_spm__1, false, label_entry);
//			InsertGetStackRegisterValue(mod,gvars[_current_sp], ll_ptr_25   );
//			
//			
//			Instruction * iiiii ;
//			
//			
//			for (auto v : arg_ptr_map)
//			{
//				AllocaInst * alloca = allocaMap[v.first];
//				LoadInst* ptr_25 = new LoadInst(alloca, "", false, label_entry);
//				ptr_25->setAlignment(TD->getTypeAllocSize(v.second->getType()));
//				
//				
//				Value * vvv = ptr_25;
//				
//				//errs() << *  gvars[v.first] ;
//				
//				//errs() << "\n\tType : " <<  *  operand_types[v.first] ;
//				
//				
//				
//				if (operand_types[v.first]->isPointerTy() )
//				{
//					
//					//Type * tt =  operand_types[v.first]->getPointerElementType () ;
//					//errs() << "\n\t  cast : "  << * tt  ;
//					
//					if (operand_types[v.first]->getPointerElementType ()->isIntegerTy(8))
//					{
//						//errs() << "  no use cast : "  ;
//						IRBuilder<> B_builder2(label_entry);
//						//Value *l2g_arg = B_builder2.CreatePointerCast(vvv, Type::getInt8PtrTy(mod.getContext()), "l2g_arg");
//						
//						int DataSize = 4 ; // TD->getTypeAllocSize();
//						ConstantInt* const_int32__DataSize  = ConstantInt::get(mod.getContext(),APInt(32,DataSize,true ));
//						ConstantInt* const_int32__TypeKnown = ConstantInt::get(mod.getContext(),APInt(32,0,true ));
//						LoadInst * ld_stack_depth = B_builder2.CreateLoad( gvar_spm_depth);
//						
//						// Call l2g
//						
//						// with the l2g mgt
//						CallInst *func_l2g_call = B_builder2.CreateCall(func_l2g, {vvv , const_int32__DataSize , const_int32__TypeKnown , ld_stack_depth }  , "l2g_ret");
//						
//						// without the l2g mgt
//						//CallInst *func_l2g_call = B_builder2.CreateCall(func_l2g, {vvv , const_int32__}  , "l2g_ret");
//						
//						
//						
//						func_l2g_call->setCallingConv(CallingConv::C);
//						func_l2g_call->setTailCall(false);
//						//Value *l2g_ret__ = B_builder2.CreatePointerCast(func_l2g_call, vvv->getType() , "l2g_arg2");
//						vvv = func_l2g_call ;
//					}
//					else
//					{
//						//errs() << "  use cast : "  ;
//						IRBuilder<> B_builder2(label_entry);
//						Value *l2g_arg = B_builder2.CreatePointerCast(vvv, Type::getInt8PtrTy(mod.getContext()), "l2g_arg");
//						
//						
//						
//						
//						int DataSize =  TD->getTypeAllocSize( operand_types[v.first]->getPointerElementType ());
//						
//						
//						ConstantInt* const_int32__DataSize  = ConstantInt::get(mod.getContext(),APInt(32,DataSize,true ));
//						ConstantInt* const_int32__TypeKnown = ConstantInt::get(mod.getContext(),APInt(32,1,true ));
//						LoadInst * ld_stack_depth = B_builder2.CreateLoad( gvar_spm_depth);
//						
//						// Call l2g
//						
//						//errs() << "\n\tData Size:" << DataSize << " : " << *operand_types[v.first]->getPointerElementType () ;
//						//<< "\n\t" <<  *vvv << "\n\t" <<  *ld_stack_depth ; // <<  "\n\t" <<  vvv;
//						//errs() << "\n\t l2g: " << *func_l2g ;
//						
//						// with the l2g mgt
//						CallInst *func_l2g_call = B_builder2.CreateCall(func_l2g, {l2g_arg , const_int32__DataSize , const_int32__TypeKnown , ld_stack_depth }  , "l2g_ret");
//						
//						// without the l2g mgt
//						//CallInst *func_l2g_call = B_builder2.CreateCall(func_l2g, {l2g_arg , const_int32__}  , "l2g_ret");
//						
//						
//						
//						//CallInst *func_l2g_call = B_builder2.CreateCall(func_l2g, {l2g_arg , const_int32__ }, "l2g_ret");
//						
//						
//						
//						func_l2g_call->setCallingConv(CallingConv::C);
//						func_l2g_call->setTailCall(false);
//						Value *l2g_ret__ = B_builder2.CreatePointerCast(func_l2g_call, vvv->getType() , "l2g_arg2");
//						vvv = l2g_ret__ ;
//					}
//					
//					//errs() << * newF ;
//				}
//				
//				
//				StoreInst* void_26 = new StoreInst(vvv, gvars[v.first]  , false, label_entry);
//				void_26->setAlignment(TD->getTypeAllocSize(v.second->getType()));
//				
//				iiiii = void_26 ;
//				
//			}
//			
//			std::vector<Value*> _call_params;
//			
//			
//			CallInst * cccc = CallInst::Create  (func_sstore, "", iiiii );
//			iiiii->moveBefore(cccc);
//			
//			
//			InsertPutStackRegisterValue(mod,gvar_spm__2, cccc , true);
//			
//			
//			
//			for (auto v : arg_ptr_map)
//			{
//				LoadInst* int32_30 = new LoadInst(gvars[v.first], "", false, label_entry);
//				int32_30->setAlignment(TD->getTypeAllocSize(v.second->getType()));
//				_call_params.push_back(int32_30);
//			}
//			
//			
//			CallInst* _call = CallInst::Create(F, _call_params, "", label_entry);
//			_call->setCallingConv(CallingConv::C);
//			_call->setTailCall(false);
//			
//			
//			if (F->getReturnType()->isVoidTy() )
//			{
//				CallInst * ccccc = CallInst::Create(func_sload, "", label_entry);
//				InsertPutStackRegisterValue(mod,gvars[_current_sp],ccccc  );
//				ReturnInst::Create(mod.getContext(),  label_entry);
//			}
//			else
//			{
//				
//				StoreInst* void_31 = new StoreInst(_call, gvars[_return_], false, label_entry);
//				void_31->setAlignment( TD->getTypeAllocSize(F->getReturnType()));
//				
//				CallInst * ccccc = CallInst::Create(func_sload, "",label_entry);
//				InsertPutStackRegisterValue(mod,gvars[_current_sp],ccccc);
//				
//				LoadInst* int32_33 = new LoadInst(gvars[_return_], "", false, label_entry);
//				int32_33->setAlignment(TD->getTypeAllocSize(F->getReturnType()));
//				ReturnInst::Create(mod.getContext(), int32_33, label_entry);
//			}
//			
//			//errs() << " " << *newF ;
//		}
//		
//		ic ++;
//	}
//	
//	call_inst->setCalledFunction(newF);
//	
//	
//}
//
//
//void CreateWrapToFtnWithCodeMgtStackMgt (Module &mod , CallInst * call_inst)
//{
//	ic++;
//
//	GlobalVariable* gvar_spm_stack_base = mod.getGlobalVariable("_spm_stack_base");
//	GlobalVariable* gvar_spm_depth = mod.getGlobalVariable("_stack_depth");
//	GlobalVariable* gvar_stack = mod.getGlobalVariable("_stack");
//	GlobalVariable* gvar_spm__2 = mod.getGlobalVariable("_spm__2");
//	GlobalVariable* gvar_spm__1 = mod.getGlobalVariable("_spm__1");
//	GlobalVariable* gvar__set_spm_   = mod.getGlobalVariable("_set_spm_");
//	
//	
//	// Functions
//	Function *func_l2g   = mod.getFunction("_l2g");
//	Function *func_sstore = mod.getFunction("_sstore");
//	Function *func_sload = mod.getFunction("_sload");
//	
//	// wrap function call
//	Function * F = call_inst->getCalledFunction();
//	Function * newF ;
//	{
//		std::stringstream inststring;
//		inststring << "WrapftnCall_" << ic << "_" << call_inst->getCalledFunction()->getName().str();
//		//std::string nn = inststring.str() ;
//		
//		#define _current_sp 300
//		#define _return_ 200
//		std::map<int , GlobalVariable*> gvars ;
//		std::map<int , Type *> operand_types ;
//		
//		// create gv to store current sp
//		{
//			std::stringstream gv_spm_name  ;
//			gv_spm_name << inststring.str() << "_current_sp";
//			
//			GlobalVariable *  gvar_currrent_spm = new
//			GlobalVariable(mod, Type::getInt8PtrTy(mod.getContext()) ,false,
//						   GlobalValue::ExternalLinkage,0, gv_spm_name.str());
//			
//			gvar_currrent_spm->setAlignment(4);
//			ConstantPointerNull* const_ptr_100 = ConstantPointerNull::get( Type::getInt8PtrTy(mod.getContext()) ) ;
//			gvar_currrent_spm->setInitializer(const_ptr_100);
//			
//			gvars[_current_sp] = gvar_currrent_spm;
//		}
//		
//		//create FunctionType base on call inst instead of called function arg
//		FunctionType* FuncTy_ ;
//		{
//			std::vector<Type*>FuncTy__args;
//			
//			for (unsigned int i = 0, n = call_inst->getNumArgOperands(); i < n; i++)
//			{
//				Value *operand = call_inst->getArgOperand(i);
//				FuncTy__args.push_back(operand->getType() );
//			}
//			FuncTy_ = FunctionType::get(F->getReturnType(), FuncTy__args,false );
//		}
//		
//		newF = Function::Create(FuncTy_,F->getLinkage() ,inststring.str() ,&mod);
//		
//		
//		// make gv to store passed arguments
//		{
//			for (unsigned int i = 0, n = call_inst->getNumArgOperands(); i < n; i++)
//			{
//				Value *operand = call_inst->getArgOperand(i);
//				operand_types[i] = operand->getType() ;
//				
//				if (operand->getType()->isPointerTy() )
//				{
//					std::stringstream gvar_name ;
//					gvar_name << inststring.str() << "_" << i << "_ptr" ;
//					
//					PointerType* PointerTy_0 = dyn_cast<PointerType>(operand->getType());
//					
//					GlobalVariable* gvar_ptr_gvar = new
//					GlobalVariable(mod,PointerTy_0 ,false,GlobalValue::ExternalLinkage,0,gvar_name.str());
//					
//					gvar_ptr_gvar->setAlignment(4);
//					ConstantPointerNull* const_ptr_10 = ConstantPointerNull::get(PointerTy_0);
//					gvar_ptr_gvar->setInitializer(const_ptr_10);
//					
//					gvars[i] = gvar_ptr_gvar;
//					
//				}
//				else if (operand->getType()->isIntegerTy () )
//				{
//					std::stringstream gvar_name ;
//					gvar_name << inststring.str() << "_" << i << "_int_" ;
//					
//					IntegerType * iType = dyn_cast<IntegerType>(operand->getType()) ;
//					int bits = iType->getBitWidth ();
//					GlobalVariable* gvar_int_gvar = new GlobalVariable(mod,
//																	   IntegerType::get(mod.getContext(), bits)
//																	   ,false, GlobalValue::ExternalLinkage,0,
//																	   gvar_name.str() );
//					
//					gvar_int_gvar->setAlignment(bits / 8);
//					ConstantInt* const_int32_11 = ConstantInt::get(mod.getContext(), APInt(bits, StringRef("0"), 10));
//					gvar_int_gvar->setInitializer(const_int32_11);
//					gvars[i] = gvar_int_gvar;
//				}
//				else if (operand->getType()->isDoubleTy () )
//				{
//					std::stringstream gvar_name ;
//					gvar_name << inststring.str() << "_" << i << "_Double_" ;
//					
//					GlobalVariable* gvar_ = new GlobalVariable( mod,
//															   Type::getDoubleTy(mod.getContext()),false,
//															   GlobalValue::ExternalLinkage,0,
//															   gvar_name.str());
//					
//					gvar_->setAlignment(8);
//					
//					ConstantFP* const_double_19 = ConstantFP::get(mod.getContext(), APFloat(0.000000e+00));
//					gvar_ ->setInitializer(const_double_19);
//					gvars[i] = gvar_;
//				}
//				
//				else
//				{
//					errs() << "\n\n\t TODO , other types " ;
//					getwchar();
//				}
//			}
//			
//			if (! F->getReturnType()->isVoidTy())
//			{
//				
//				if (F->getReturnType()->isPointerTy() )
//				{
//					std::stringstream gvar_name ;
//					gvar_name << "_GV__" << ic << "_RTN_ptr" ;
//					
//					PointerType* PointerTy_0 = dyn_cast<PointerType>(F->getReturnType()  );
//					
//					GlobalVariable* gvar = new
//					GlobalVariable(mod,PointerTy_0 ,false,GlobalValue::ExternalLinkage,0, gvar_name.str());
//					
//					gvar->setAlignment(4);
//					ConstantPointerNull* const_ptr_10 = ConstantPointerNull::get(PointerTy_0);
//					gvar->setInitializer(const_ptr_10);
//					
//					gvars[ _return_ ] = gvar;
//					
//				}
//				else if (F->getReturnType()->isIntegerTy () )
//				{
//					std::stringstream gvar_name ;
//					gvar_name << "_GV__" << ic << "_RTN_int" ;
//					
//					IntegerType * iType = dyn_cast<IntegerType>(F->getReturnType()) ;
//					int bits = iType->getBitWidth ();
//					GlobalVariable* gvar   = new
//					GlobalVariable(mod,IntegerType::get(mod.getContext(), bits),false,GlobalValue::ExternalLinkage,0,gvar_name.str() );
//					
//					gvar->setAlignment(bits / 8);
//					ConstantInt* const_int32_11 = ConstantInt::get(mod.getContext(), APInt(bits, StringRef("0"), 10));
//					gvar->setInitializer(const_int32_11);
//					gvars[_return_ ] = gvar;
//					
//				}
//				else
//				{
//					errs() << "\n\n\t TODO , other types " ;
//					getwchar();
//				}
//				
//				
//			}
//		}
//		
//		//for(auto gv : gvars) { errs() << "\n " << gv.first << " : " << *(gvars[gv.first])  ; }
//		
//		
//		// build code for newF
//		{
//			newF->setCallingConv(CallingConv::C);
//			AttributeSet   _PAL;
//			{
//				SmallVector<AttributeSet, 4> Attrs;
//				AttributeSet PAS;
//				{
//					AttrBuilder B;
//					B.addAttribute(Attribute::NoUnwind);
//					B.addAttribute(Attribute::NoInline);
//					PAS = AttributeSet::get(mod.getContext(), ~0U, B);
//				}
//				
//				Attrs.push_back(PAS);
//				_PAL = AttributeSet::get(mod.getContext(), Attrs);
//				
//			}
//			newF->setAttributes(  _PAL);
//			
//			std::map<int , Value* > arg_ptr_map ;
//			std::map<int , AllocaInst  * > allocaMap   ;
//			
//			GlobalVariable* ptr_rtn ;
//			
//			BasicBlock* label_entry = BasicBlock::Create(mod.getContext(), "entry",newF,0);
//			IRBuilder<> B_builder(label_entry);
//			
//			Function::arg_iterator args = newF->arg_begin();
//			for (unsigned int i = 0, n = call_inst->getNumArgOperands(); i < n; i++)
//			{
//				Value* arg_ptr = args++ ;
//				std::string name = "arg_" ;
//				name.append (std::to_string(i));
//				arg_ptr->setName(name.c_str() );
//				arg_ptr_map[i] = arg_ptr ;
//				
//			}
//			
//			
//			for (auto v : arg_ptr_map)
//			{
//				std::string str =  v.second->getName().str() ; str.append (".addr");
//				AllocaInst* alloca  = new AllocaInst(v.second->getType()  , str , label_entry);
//				alloca->setAlignment(TD->getTypeAllocSize(v.second->getType()));
//				allocaMap[v.first] = alloca ;
//			}
//			
//			
//			Instruction * inin   ;
//			for (auto v : arg_ptr_map)
//			{
//				AllocaInst * alloca = allocaMap[v.first];
//				StoreInst* void_23 = new StoreInst(v.second, alloca, false, label_entry);
//				void_23->setAlignment(TD->getTypeAllocSize(v.second->getType()));
//				inin = void_23 ;
//			}
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			LoadInst* ll_ptr_25 = new LoadInst(gvars[_current_sp ], "", false, label_entry);
//			StoreInst* st_void_23 = new StoreInst(ll_ptr_25, gvar_spm__1, false, label_entry);
//			InsertGetStackRegisterValue(mod,gvars[_current_sp], ll_ptr_25   );
//			
//			
//			Instruction * iiiii ;
//			
//			
//			for (auto v : arg_ptr_map)
//			{
//				AllocaInst * alloca = allocaMap[v.first];
//				LoadInst* ptr_25 = new LoadInst(alloca, "", false, label_entry);
//				ptr_25->setAlignment(TD->getTypeAllocSize(v.second->getType()));
//				
//				
//				Value * vvv = ptr_25;
//				
//				//errs() << *  gvars[v.first] ;
//				
//				//errs() << "\n\tType : " <<  *  operand_types[v.first] ;
//				
//				
//				
//				if (operand_types[v.first]->isPointerTy() )
//				{
//					
//					//Type * tt =  operand_types[v.first]->getPointerElementType () ;
//					//errs() << "\n\t  cast : "  << * tt  ;
//					
//					if (operand_types[v.first]->getPointerElementType ()->isIntegerTy(8))
//					{
//						//errs() << "  no use cast : "  ;
//						IRBuilder<> B_builder2(label_entry);
//						//Value *l2g_arg = B_builder2.CreatePointerCast(vvv, Type::getInt8PtrTy(mod.getContext()), "l2g_arg");
//						
//						int DataSize = 4 ; // TD->getTypeAllocSize();
//						ConstantInt* const_int32__DataSize  = ConstantInt::get(mod.getContext(),APInt(32,DataSize,true ));
//						ConstantInt* const_int32__TypeKnown = ConstantInt::get(mod.getContext(),APInt(32,0,true ));
//						LoadInst * ld_stack_depth = B_builder2.CreateLoad( gvar_spm_depth);
//						
//						// Call l2g
//						
//						// with the l2g mgt
//						CallInst *func_l2g_call = B_builder2.CreateCall(func_l2g, {vvv , const_int32__DataSize , const_int32__TypeKnown , ld_stack_depth }  , "l2g_ret");
//						
//						// without the l2g mgt
//						//CallInst *func_l2g_call = B_builder2.CreateCall(func_l2g, {vvv , const_int32__}  , "l2g_ret");
//						
//						
//						
//						func_l2g_call->setCallingConv(CallingConv::C);
//						func_l2g_call->setTailCall(false);
//						//Value *l2g_ret__ = B_builder2.CreatePointerCast(func_l2g_call, vvv->getType() , "l2g_arg2");
//						vvv = func_l2g_call ;
//					}
//					else
//					{
//						//errs() << "  use cast : "  ;
//						IRBuilder<> B_builder2(label_entry);
//						Value *l2g_arg = B_builder2.CreatePointerCast(vvv, Type::getInt8PtrTy(mod.getContext()), "l2g_arg");
//						
//						
//						
//						
//						int DataSize =  TD->getTypeAllocSize( operand_types[v.first]->getPointerElementType ());
//						
//						
//						ConstantInt* const_int32__DataSize  = ConstantInt::get(mod.getContext(),APInt(32,DataSize,true ));
//						ConstantInt* const_int32__TypeKnown = ConstantInt::get(mod.getContext(),APInt(32,1,true ));
//						LoadInst * ld_stack_depth = B_builder2.CreateLoad( gvar_spm_depth);
//						
//						// Call l2g
//						
//						//errs() << "\n\tData Size:" << DataSize << " : " << *operand_types[v.first]->getPointerElementType () ;
//						//<< "\n\t" <<  *vvv << "\n\t" <<  *ld_stack_depth ; // <<  "\n\t" <<  vvv;
//						//errs() << "\n\t l2g: " << *func_l2g ;
//						
//						// with the l2g mgt
//						CallInst *func_l2g_call = B_builder2.CreateCall(func_l2g, {l2g_arg , const_int32__DataSize , const_int32__TypeKnown , ld_stack_depth }  , "l2g_ret");
//						
//						// without the l2g mgt
//						//CallInst *func_l2g_call = B_builder2.CreateCall(func_l2g, {l2g_arg , const_int32__}  , "l2g_ret");
//						
//						
//						
//						//CallInst *func_l2g_call = B_builder2.CreateCall(func_l2g, {l2g_arg , const_int32__ }, "l2g_ret");
//						
//						
//						
//						func_l2g_call->setCallingConv(CallingConv::C);
//						func_l2g_call->setTailCall(false);
//						Value *l2g_ret__ = B_builder2.CreatePointerCast(func_l2g_call, vvv->getType() , "l2g_arg2");
//						vvv = l2g_ret__ ;
//					}
//					
//					//errs() << * newF ;
//				}
//				
//				
//				StoreInst* void_26 = new StoreInst(vvv, gvars[v.first]  , false, label_entry);
//				void_26->setAlignment(TD->getTypeAllocSize(v.second->getType()));
//				
//				iiiii = void_26 ;
//				
//			}
//			
//			
//			
//			
//			
//			IRBuilder<> builder22(mod.getContext()) ;
//			builder22.SetInsertPoint(iiiii);
//			
//			Value *  CalleeIdx   = builder22.getInt32( funcs[  call_inst->getCalledFunction() ]->idx  );
//			
//			
//			Value *  CallerIdx = NULL ;
//			if (funcs[  call_inst->getCalledFunction() ]->idx == 1)
//			{
//				CallerIdx   = builder22.getInt32(0);
//				
//			}else
//			{
//				CallerIdx   = builder22.getInt32(funcs   [ call_inst->getParent()->getParent()]->idx );
//			}
//			
//			
//			std::vector<Value*> fetchFunctionToSPM_arg ;
//			//BitCastInst * bcast = new  BitCastInst(call_inst->getCalledFunction(),funcLoadAddr_start[call_inst->getCalledFunction()]->getType(),"",label_entry);
//			//fetchFunctionToSPM_arg.push_back (bcast);
//			//fetchFunctionToSPM_arg.push_back ( funcLoadAddr_start[call_inst->getCalledFunction()]   );
//			//fetchFunctionToSPM_arg.push_back ( funcLoadAddr_stop [call_inst->getCalledFunction()]   );
//			fetchFunctionToSPM_arg.push_back(CalleeIdx);
//			fetchFunctionToSPM_arg.push_back(CallerIdx);
//			
//			
//			
//			CallInst* _call_dma = CallInst::Create(mod.getFunction("fetch_callee_code") , fetchFunctionToSPM_arg, "", iiiii );
//			
//
//			
//			
//			
//			std::vector<Value*> _call_params;
//			
//			
//			CallInst * cccc = CallInst::Create  (func_sstore, "", iiiii );
//			iiiii->moveBefore(cccc);
//			
//			
//			InsertPutStackRegisterValue(mod,gvar_spm__2, cccc , true);
//			
//			
//			
//			
//			
//			
//			for (auto v : arg_ptr_map)
//			{
//				LoadInst* int32_30 = new LoadInst(gvars[v.first], "", false, label_entry);
//				int32_30->setAlignment(TD->getTypeAllocSize(v.second->getType()));
//				_call_params.push_back(int32_30);
//			}
//			
//			
//			CallInst* _call = CallInst::Create(F, _call_params, "", label_entry);
//			_call->setCallingConv(CallingConv::C);
//			_call->setTailCall(false);
//			
//			ReturnInst * Iret ;
//			
//			if (F->getReturnType()->isVoidTy() )
//			{
//				CallInst * ccccc = CallInst::Create(func_sload, "", label_entry);
//				InsertPutStackRegisterValue(mod,gvars[_current_sp],ccccc  );
//				Iret = ReturnInst::Create(mod.getContext(),  label_entry);
//			}
//			else
//			{
//				
//				StoreInst* void_31 = new StoreInst(_call, gvars[_return_], false, label_entry);
//				void_31->setAlignment( TD->getTypeAllocSize(F->getReturnType()));
//				
//				CallInst * ccccc = CallInst::Create(func_sload, "",label_entry);
//				InsertPutStackRegisterValue(mod,gvars[_current_sp],ccccc);
//				
//				LoadInst* int32_33 = new LoadInst(gvars[_return_], "", false, label_entry);
//				int32_33->setAlignment(TD->getTypeAllocSize(F->getReturnType()));
//				Iret = ReturnInst::Create(mod.getContext(), int32_33, label_entry);
//			}
//			
//			
//			std::vector<Value*> fetchFunctionToSPM_arg2 ;
//			//BitCastInst * bcast = new  BitCastInst(call_inst->getCalledFunction(),funcLoadAddr_start[call_inst->getCalledFunction()]->getType(),"",label_entry);
//			//fetchFunctionToSPM_arg.push_back (bcast);
//			//fetchFunctionToSPM_arg.push_back ( funcLoadAddr_start[call_inst->getCalledFunction()]   );
//			//fetchFunctionToSPM_arg.push_back ( funcLoadAddr_stop [call_inst->getCalledFunction()]   );
//			fetchFunctionToSPM_arg2.push_back(CallerIdx);
//			
//			
//			CallInst* _call_dma2 = CallInst::Create(mod.getFunction("fetch_caller_code") , fetchFunctionToSPM_arg2, "", Iret);
//			
//			
//			//errs() << " " << *newF ;
//		}
//		
//		ic ++;
//	}
//	
//	call_inst->setCalledFunction(newF);
//	
//
//}
//
//
//void CreateWrapToFtnWithCodeMgt(Module &mod , CallInst * call_inst)
//{
//	ic++;
//	
//	//errs() << "\n Caller : " << *call_inst ;
//	
//	
//	// wrap function call
//	Function * F = call_inst->getCalledFunction();
//	Function * newF ;
//	{
//		std::stringstream inststring;
//		inststring << "WrapftnCall_" << ic << "_" << call_inst->getCalledFunction()->getName().str();
//		//std::string nn = inststring.str() ;
//		
//#define _current_sp 300
//#define _return_ 200
//		std::map<int , GlobalVariable*> gvars ;
//		std::map<int , Type *> operand_types ;
//		
//		
//		
//		//create FunctionType base on call inst instead of called function arg
//		FunctionType* FuncTy_ ;
//		{
//			std::vector<Type*>FuncTy__args;
//			
//			for (unsigned int i = 0, n = call_inst->getNumArgOperands(); i < n; i++)
//			{
//				Value *operand = call_inst->getArgOperand(i);
//				FuncTy__args.push_back(operand->getType() );
//			}
//			FuncTy_ = FunctionType::get(F->getReturnType(), FuncTy__args,false );
//		}
//		
//		newF = Function::Create(FuncTy_,F->getLinkage() ,inststring.str() ,&mod);
//		
//		
//		// make gv to store passed arguments
//		{
//			for (unsigned int i = 0, n = call_inst->getNumArgOperands(); i < n; i++)
//			{
//				Value *operand = call_inst->getArgOperand(i);
//				operand_types[i] = operand->getType() ;
//				
//				if (operand->getType()->isPointerTy() )
//				{
//					std::stringstream gvar_name ;
//					gvar_name << inststring.str() << "_" << i << "_ptr" ;
//					
//					PointerType* PointerTy_0 = dyn_cast<PointerType>(operand->getType());
//					
//					GlobalVariable* gvar_ptr_gvar = new
//					GlobalVariable(mod,PointerTy_0 ,false,GlobalValue::ExternalLinkage,0,gvar_name.str());
//					
//					gvar_ptr_gvar->setAlignment(4);
//					ConstantPointerNull* const_ptr_10 = ConstantPointerNull::get(PointerTy_0);
//					gvar_ptr_gvar->setInitializer(const_ptr_10);
//					
//					gvars[i] = gvar_ptr_gvar;
//					
//				}
//				else if (operand->getType()->isIntegerTy () )
//				{
//					std::stringstream gvar_name ;
//					gvar_name << inststring.str() << "_" << i << "_int_" ;
//					
//					IntegerType * iType = dyn_cast<IntegerType>(operand->getType()) ;
//					int bits = iType->getBitWidth ();
//					GlobalVariable* gvar_int_gvar = new GlobalVariable(mod,
//																	   IntegerType::get(mod.getContext(), bits)
//																	   ,false, GlobalValue::ExternalLinkage,0,
//																	   gvar_name.str() );
//					
//					gvar_int_gvar->setAlignment(bits / 8);
//					ConstantInt* const_int32_11 = ConstantInt::get(mod.getContext(), APInt(bits, StringRef("0"), 10));
//					gvar_int_gvar->setInitializer(const_int32_11);
//					gvars[i] = gvar_int_gvar;
//				}
//				else if (operand->getType()->isDoubleTy () )
//				{
//					std::stringstream gvar_name ;
//					gvar_name << inststring.str() << "_" << i << "_Double_" ;
//					
//					GlobalVariable* gvar_ = new GlobalVariable( mod,
//															   Type::getDoubleTy(mod.getContext()),false,
//															   GlobalValue::ExternalLinkage,0,
//															   gvar_name.str());
//					
//					gvar_->setAlignment(8);
//					
//					ConstantFP* const_double_19 = ConstantFP::get(mod.getContext(), APFloat(0.000000e+00));
//					gvar_ ->setInitializer(const_double_19);
//					gvars[i] = gvar_;
//				}
//				
//				else
//				{
//					errs() << "\n\n\t TODO , other types " ;
//					getwchar();
//				}
//			}
//			
//			if (! F->getReturnType()->isVoidTy())
//			{
//				
//				if (F->getReturnType()->isPointerTy() )
//				{
//					std::stringstream gvar_name ;
//					gvar_name << "_GV__" << ic << "_RTN_ptr" ;
//					
//					PointerType* PointerTy_0 = dyn_cast<PointerType>(F->getReturnType()  );
//					
//					GlobalVariable* gvar = new
//					GlobalVariable(mod,PointerTy_0 ,false,GlobalValue::ExternalLinkage,0, gvar_name.str());
//					
//					gvar->setAlignment(4);
//					ConstantPointerNull* const_ptr_10 = ConstantPointerNull::get(PointerTy_0);
//					gvar->setInitializer(const_ptr_10);
//					
//					gvars[ _return_ ] = gvar;
//					
//				}
//				else if (F->getReturnType()->isIntegerTy () )
//				{
//					std::stringstream gvar_name ;
//					gvar_name << "_GV__" << ic << "_RTN_int" ;
//					
//					IntegerType * iType = dyn_cast<IntegerType>(F->getReturnType()) ;
//					int bits = iType->getBitWidth ();
//					GlobalVariable* gvar   = new
//					GlobalVariable(mod,IntegerType::get(mod.getContext(), bits),false,GlobalValue::ExternalLinkage,0,gvar_name.str() );
//					
//					gvar->setAlignment(bits / 8);
//					ConstantInt* const_int32_11 = ConstantInt::get(mod.getContext(), APInt(bits, StringRef("0"), 10));
//					gvar->setInitializer(const_int32_11);
//					gvars[_return_ ] = gvar;
//					
//				}
//				else
//				{
//					errs() << "\n\n\t TODO , other types " ;
//					getwchar();
//				}
//				
//				
//			}
//		}
//		
//		//for(auto gv : gvars) { errs() << "\n " << gv.first << " : " << *(gvars[gv.first])  ; }
//		
//		
//		// build code for newF
//		{
//			newF->setCallingConv(CallingConv::C);
//			AttributeSet   _PAL;
//			{
//				SmallVector<AttributeSet, 4> Attrs;
//				AttributeSet PAS;
//				{
//					AttrBuilder B;
//					B.addAttribute(Attribute::NoUnwind);
//					B.addAttribute(Attribute::NoInline);
//					PAS = AttributeSet::get(mod.getContext(), ~0U, B);
//				}
//				
//				Attrs.push_back(PAS);
//				_PAL = AttributeSet::get(mod.getContext(), Attrs);
//				
//			}
//			newF->setAttributes(  _PAL);
//			
//			std::map<int , Value* > arg_ptr_map ;
//			std::map<int , AllocaInst  * > allocaMap   ;
//			
//			GlobalVariable* ptr_rtn ;
//			
//			BasicBlock* label_entry = BasicBlock::Create(mod.getContext(), "entry",newF,0);
//			IRBuilder<> B_builder(label_entry);
//			
//			Function::arg_iterator args = newF->arg_begin();
//			for (unsigned int i = 0, n = call_inst->getNumArgOperands(); i < n; i++)
//			{
//				Value* arg_ptr = args++ ;
//				std::string name = "arg_" ;
//				name.append (std::to_string(i));
//				arg_ptr->setName(name.c_str() );
//				arg_ptr_map[i] = arg_ptr ;
//				
//			}
//			
//			
//			for (auto v : arg_ptr_map)
//			{
//				std::string str =  v.second->getName().str() ; str.append (".addr");
//				AllocaInst* alloca  = new AllocaInst(v.second->getType()  , str , label_entry);
//				alloca->setAlignment(TD->getTypeAllocSize(v.second->getType()));
//				allocaMap[v.first] = alloca ;
//			}
//			
//			
//			Instruction * inin   ;
//			for (auto v : arg_ptr_map)
//			{
//				AllocaInst * alloca = allocaMap[v.first];
//				StoreInst* void_23 = new StoreInst(v.second, alloca, false, label_entry);
//				void_23->setAlignment(TD->getTypeAllocSize(v.second->getType()));
//				inin = void_23 ;
//			}
//			
//			
//			
//			Instruction * iiiii ;
//			
//			
//			for (auto v : arg_ptr_map)
//			{
//				AllocaInst * alloca = allocaMap[v.first];
//				LoadInst* ptr_25 = new LoadInst(alloca, "", false, label_entry);
//				ptr_25->setAlignment(TD->getTypeAllocSize(v.second->getType()));
//				
//				
//				Value * vvv = ptr_25;
//				
//				//errs() << *  gvars[v.first] ;
//				
//				//errs() << "\n\tType : " <<  *  operand_types[v.first] ;
//				
//				
//				
//				
//				
//				StoreInst* void_26 = new StoreInst(vvv, gvars[v.first]  , false, label_entry);
//				void_26->setAlignment(TD->getTypeAllocSize(v.second->getType()));
//				
//				iiiii = void_26 ;
//				
//			}
//			
//			std::vector<Value*> _call_params;
//			
//			
//			//	CallInst * cccc = CallInst::Create  (func_sstore, "", iiiii );
//			//	iiiii->moveBefore(cccc);
//			
//			
//			//	InsertPutStackRegisterValue(mod,gvar_spm__2, cccc , true);
//			
//			
//			IRBuilder<> builder(mod.getContext()) ;
//			builder.SetInsertPoint(label_entry);
//			
//			Value *  CalleeIdx   = builder.getInt32( funcs[  call_inst->getCalledFunction() ]->idx  );
//			
//			
//			Value *  CallerIdx = NULL ;
//			if (funcs[  call_inst->getCalledFunction() ]->idx == 1)
//			{
//				CallerIdx   = builder.getInt32(0);
//				
//			}else
//			{
//				CallerIdx   = builder.getInt32(funcs   [ call_inst->getParent()->getParent()]->idx );
//			}
//			
//			
//			std::vector<Value*> fetchFunctionToSPM_arg ;
//			//BitCastInst * bcast = new  BitCastInst(call_inst->getCalledFunction(),funcLoadAddr_start[call_inst->getCalledFunction()]->getType(),"",label_entry);
//			//fetchFunctionToSPM_arg.push_back (bcast);
//			//fetchFunctionToSPM_arg.push_back ( funcLoadAddr_start[call_inst->getCalledFunction()]   );
//			//fetchFunctionToSPM_arg.push_back ( funcLoadAddr_stop [call_inst->getCalledFunction()]   );
//			fetchFunctionToSPM_arg.push_back(CalleeIdx);
//			fetchFunctionToSPM_arg.push_back(CallerIdx);
//			
//			
//			
//			CallInst* _call_dma = CallInst::Create(mod.getFunction("fetch_callee_code") , fetchFunctionToSPM_arg, "", label_entry);
//			
//			
//			
//			for (auto v : arg_ptr_map)
//			{
//				LoadInst* int32_30 = new LoadInst(gvars[v.first], "", false, label_entry);
//				int32_30->setAlignment(TD->getTypeAllocSize(v.second->getType()));
//				_call_params.push_back(int32_30);
//			}
//			
//			
//			
//			
//			
//			CallInst* _call = CallInst::Create(F, _call_params, "", label_entry);
//			_call->setCallingConv(CallingConv::C);
//			_call->setTailCall(false);
//			
//			
//			
//			ReturnInst * Iret ;
//			
//			if (F->getReturnType()->isVoidTy() )
//			{
//				//CallInst * ccccc = CallInst::Create(func_sload, "", label_entry);
//				//InsertPutStackRegisterValue(mod,gvars[_current_sp],ccccc  );
//				Iret = ReturnInst::Create(mod.getContext(),  label_entry);
//			}
//			else
//			{
//				
//				StoreInst* void_31 = new StoreInst(_call, gvars[_return_], false, label_entry);
//				void_31->setAlignment( TD->getTypeAllocSize(F->getReturnType()));
//				
//				//CallInst * ccccc = CallInst::Create(func_sload, "",label_entry);
//				//InsertPutStackRegisterValue(mod,gvars[_current_sp],ccccc);
//				
//				LoadInst* int32_33 = new LoadInst(gvars[_return_], "", false, label_entry);
//				int32_33->setAlignment(TD->getTypeAllocSize(F->getReturnType()));
//				Iret = ReturnInst::Create(mod.getContext(), int32_33, label_entry);
//			}
//			
//			
//			std::vector<Value*> fetchFunctionToSPM_arg2 ;
//			//BitCastInst * bcast = new  BitCastInst(call_inst->getCalledFunction(),funcLoadAddr_start[call_inst->getCalledFunction()]->getType(),"",label_entry);
//			//fetchFunctionToSPM_arg.push_back (bcast);
//			//fetchFunctionToSPM_arg.push_back ( funcLoadAddr_start[call_inst->getCalledFunction()]   );
//			//fetchFunctionToSPM_arg.push_back ( funcLoadAddr_stop [call_inst->getCalledFunction()]   );
//			fetchFunctionToSPM_arg2.push_back(CallerIdx);
//			
//			
//			CallInst* _call_dma2 = CallInst::Create(mod.getFunction("fetch_caller_code") , fetchFunctionToSPM_arg2, "", Iret);
//			
//			
//			
//			
//			
//			//errs() << " " << *newF ;
//		}
//		
//		ic ++;
//	}
//	
//	
//	call_inst->setCalledFunction(newF);
//	//errs() << "\n        : " << *call_inst ;
//	//errs() << "\n" << *newF << "\n";
//	
//	
//}



//// Build the wrapper function: retTy c_call_complete(char *callerName, char *calleeName, calleeTy calleeAddr, ...)
// Build the wrapper function: retTy c_call_complete( int32 callerIndex , int32  calleeIndex , calleeTy calleeAddr, ...)





//
//
//namespace {
//	
//	struct StackManagementPass : public ModulePass {
//		static char ID; // Pass identification, replacement for typeid
//		
//		StackManagementPass() : ModulePass(ID) {}
//		
//		virtual void getAnalysisUsage(AnalysisUsage &AU) const
//		{	AU.addRequired<CallGraphWrapperPass>(); }
//		
//		
//		virtual bool runOnModule(Module &mod)
//		{
//			mod.materializeAll();
//			SetLibraryFunctions();
//			TD = new DataLayout( &mod );
//			LLVMContext &context = mod.getContext();
//			CreateSpAsmFtnType(mod);
//			
//			std::map<CallInst * , int > stack_frame_management_insert_points ;
//			
//			// Call Graph
//			CallGraph &cg = getAnalysis<CallGraphWrapperPass>().getCallGraph(); // call graph
//			CallGraphNode *cgn_main = cg[mod.getFunction("main")];
//			CallGraphNode::CallRecord *root;
//			std::vector<std::vector<CallGraphNode::CallRecord *> > paths;
//			std::unordered_set <CallGraphNode *> undecidable_cgns;
//			
//			//Step 0: extract all the paths from original call graph
//			// Initialize root node by main function
//			for (CallGraphNode::iterator cgni = cg.begin()->second->begin(),
//				 cgne = cg.begin()->second->end();
//				 cgni != cgne; cgni++)
//			{
//				if (cgni->second == cgn_main) {
//					root = &*cgni;
//					break;
//				}
//			}
//			assert(CallGraphNode::iterator(root) != cg.begin()->second->end());
//			
//			// Step 0: Extarct all the paths from call graph rooted at main function
//			auto res = extractPaths(root);
//			paths = res.first;
//			undecidable_cgns = res.second;
//			
//			DEBUG(errs() <<  "Extract paths {\n");
//			// Print out all the paths
//			for (size_t i = 0; i < paths.size(); i++) {
//				for (size_t j = 0; j < paths[i].size(); j++) {
//					if (paths[i][j]->second->getFunction())
//					{
//						DEBUG(errs() << "\t" << paths[i][j]->first << " " << paths[i][j]->second->getFunction()->getName() << "\t");
//					}
//					else
//					{
//						DEBUG(errs() << "\t" << paths[i][j]->first << " " << "externalNode" << "\t");
//					}
//				}
//				DEBUG(errs() << "\n");
//			}
//			DEBUG(errs() << "}\n\n");
//			
//			// Step 1: get SSMD cuts
//			std::unordered_map <unsigned, std::vector <std::pair<unsigned, std::string> > > cuts;
//			// Read SSDM output file
//			std::ifstream ifs;
//			ifs.open("wcg_cuts.txt", std::fstream::in);
//			assert(ifs.good());
//			// Read function stack sizes
//			DEBUG(errs() << "Reading SSDM output file...\n");
//			DEBUG(errs() << "{\n");
//			while (ifs.good()) {
//				unsigned i, j;
//				std::string func_name;
//				ifs >> i >> j >> func_name;
//				// Ignore white spaces after the last line
//				if (func_name != "") {
//					DEBUG(errs() << "\t" << i << " " << j << " " << func_name << "\n");
//					cuts[i-1].push_back( std::make_pair(j-1, func_name) );
//				}
//			}
//			ifs.close();
//			
//			DEBUG(errs() << "}\n\n\n");
//			DEBUG(errs() << "Sorting SSDM cuts according to paths...\n");
//			DEBUG(errs() << "{\n");
//			
//			// Sort cuts acoording to paths
//			for (auto cutsi = cuts.begin(), cutse = cuts.end(); cutsi != cutse; cutsi++)
//			{
//				std::sort(cutsi->second.begin(), cutsi->second.end());
//				DEBUG(errs() << "\tpath " << cutsi->first << " : ");
//				for (size_t i = 0; i < cutsi->second.size(); i++) {
//					DEBUG(errs() << cutsi->second[i].first << " " << cutsi->second[i].second << "  ");
//				}
//				DEBUG(errs() << "\n");
//			}
//			DEBUG(errs() << "}\n\n\n");
//			
//	
//			DEBUG(errs() << "Inserting management functions according to SSDM cuts: {\n");
//			
//			// Step 4: Insert stack frame management functions
//			// Decide the insertion points of stack frame management function according to SSDM output
//			std::unordered_set <CallInst *> stack_frame_management_insert_pts;
//			for (auto cuti = cuts.begin(), cute = cuts.end(); cuti != cute; cuti++) {
//				for (size_t vi = 0; vi < cuti->second.size(); vi++) {
//					unsigned i, j;
//					std::string func_name;
//					i = cuti->first;
//					j = cuti->second[vi].first;
//					func_name = cuti->second[vi].second;
//					assert(paths[i][j]->first && paths[i][j]->second);
//					CallInst *call_inst = dyn_cast<CallInst> (paths[i][j]->first);
//					assert(call_inst);
//					stack_frame_management_insert_pts.insert(call_inst);
//				}
//			}
//			
//			// Insert stack frame management functions according to SSDM cuts
//			for (auto si = stack_frame_management_insert_pts.begin(), se = stack_frame_management_insert_pts.end(); si != se; si++) {
//				CallInst *call_inst = *si;
//				stack_frame_management_insert_points[call_inst] = 1;
//			}
//			
//			DEBUG(errs() << "}\n");
//			
// 		
//			// Step 4: Insert frame management functions at self-recursive calls
//			DEBUG(errs() << "Inserting frame management functions around recursive calls... {\n");
//			for (std::unordered_set <CallGraphNode *>::iterator si = undecidable_cgns.begin(), se = undecidable_cgns.end(); si != se; si++) {
//				CallGraphNode * cgn = *si;
//				// Skip external nodes
//				if (!cgn->getFunction())
//					continue;
//				DEBUG(errs() << cgn->getFunction()->getName() << "\n");
//				for (CallGraphNode::iterator cgni = cgn->begin(), cgne = cgn->end(); cgni != cgne; cgni++) {
//					// Skip non-self-recursive calls
//					if (cgni->second != cgn)
//						continue;
//					CallInst *call_inst = dyn_cast<CallInst> (cgni->first);
//					assert(call_inst);
//					stack_frame_management_insert_points[call_inst] = 1 ;
//				}
//			}
//			
//			DEBUG(errs() << "}\n");
//			
//		
//			// insert stack mgt
//			for (auto I : stack_frame_management_insert_points)
//			{
//				// ignore some system functions
//				if ( I.first->getCalledFunction()->getName().str() == "exit") continue;
//				if ( I.first->getCalledFunction()->getName().str() == "free") continue;
//				if ( I.first->getCalledFunction()->getName().str() == "malloc") continue;
//				
//				DEBUG(errs() << "\n\t" << *I.first << " in ftn: " << I.first->getParent()->getParent()->getName().str() );
//				CreateWrapperFtn(mod , I.first);
//			}
//			
//			
//			WrapApplicationMainFtn(mod );
//			ReplaceExitFtnCalls(mod);
//			
//			DEBUG(errs() << "\n\n") ;
//			return true;
//		}
//		
//		
//	};
//}
//
//char StackManagementPass::ID = 0; //Id the pass.
//static RegisterPass<StackManagementPass> X("securenvm_pass1", "Smart Stack Management Pass"); //Register the pass.
//

