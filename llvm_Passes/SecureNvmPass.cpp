
#include "SecureNvmPass.hpp"


DataLayout * TD ;
std::vector<std::string> LibraryFunctions ;
std::vector<std::string > UserFunctions ;
std::vector<MemAccessInst *> AllMemAccessInst;
std::map<CallInst * , int > CallInstList ;
std::vector<Instruction *> deleteList;

Function * mainWrapper = NULL ;

std::map<CallInst * , int > wrapInstListForCodeMgt   ;
std::map<CallInst * , int > wrapInstListForStackMgt ;

Value * MemAccessInst::getPointerOperand(){

	if (type == MemAccessInst::store){
		StoreInst * st = dyn_cast<StoreInst>(Inst);
		return st->getPointerOperand();
	}else if (type == MemAccessInst::load){
		LoadInst * ld = dyn_cast<LoadInst>(Inst);
		return ld->getPointerOperand();
	}
	return NULL;
}

bool MemAccessInst::setPointerOperand(Value * newAddr){
	
	if (type == MemAccessInst::store){
		StoreInst * st = dyn_cast<StoreInst>(Inst);
		StoreInst * newStore  = new StoreInst(st->getValueOperand (), newAddr,Inst);
		newStore->setAlignment(st->getAlignment());
		st->replaceAllUsesWith(newStore);
		Inst->eraseFromParent();
		Inst = dyn_cast<Instruction>(newStore) ;
	}else if (type == MemAccessInst::load){
		LoadInst * ld = dyn_cast<LoadInst>(Inst);
		LoadInst * newLoad  = new LoadInst( newAddr, "" ,Inst);
		newLoad->setAlignment(ld->getAlignment());
		ld->replaceAllUsesWith(newLoad);
		Inst->eraseFromParent();
		Inst = dyn_cast<Instruction>(newLoad);
	}
	return true ;
}

MemAccessInst *	 MemAccessInst::get(Instruction *I) {
	
	MemAccessInst * mInst = nullptr ;
	Value *v ;
	
	if (LoadInst * ld = dyn_cast<LoadInst >(I)){
		mInst = new MemAccessInst();
		v = ld->getPointerOperand();
		mInst->type = MemAccessInst::load ;
	}
	else if (StoreInst * st = dyn_cast<StoreInst >(I)){
		mInst = new MemAccessInst();
		v = st->getPointerOperand();
		mInst->type = MemAccessInst::store ;
	}
	else { return  nullptr ;}
	
	// check if addrOperand is static value
	if (GetElementPtrInst *GEPoptr = dyn_cast<GetElementPtrInst>(v)){
		Value * v = GEPoptr->getPointerOperand ();
	}
	if(GlobalVariable::classof(v))	{ mInst->operandType = MemAccessInst::global ; }
	else if(AllocaInst::classof(v))	{ mInst->operandType = MemAccessInst::stack  ; }
	else								{ mInst->operandType = MemAccessInst::dynamic ; }
	
	mInst->Inst = I ;
	return mInst;
}



// Check if a function is code management function
bool isLibraryFunction(Function *func)
{
	if (strcmp(func->getSection(),"sec_staticCode") == 0 ) return true ;
	if (strcmp(func->getSection(),"sec_mgtCode_0" ) == 0 ) return true ;
	
	return false ;
	 
}
 

void InsertExitFtnCall(Module &mod)
{
	Function * endExecution  = mod.getFunction( "endExecution") ;
	Function * _Exit = mod.getFunction("_Exit") ;
	Function * system_exit = mod.getFunction( "exit" );
	
		for (Value::user_iterator Iu = system_exit->user_begin(); Iu != system_exit->user_end(); ++Iu)
		{
			if ((CallInst::classof(*Iu)) && (((CallInst *)(*Iu))->getCalledFunction()  == system_exit )  )
			{
				CallInst * callinst = dyn_cast<CallInst>(*Iu);
				if(callinst->getParent()->getParent() == _Exit ){
				
					//errs() << * _Exit ;
					
					IRBuilder<> builder(mod.getContext()) ;
					builder.SetInsertPoint(callinst);
					builder.CreateCall(endExecution);
					
					//errs() << * _Exit ;
					
					
				}
 			}
		}
		
	
	
	
}

 

void InsertDebugMsg(Module &mod , Function * f )
{
	// c_call_args.push_back(*ai);
	
	IRBuilder<> builder (mod.getContext());
	builder.SetInsertPoint( f->getEntryBlock().getFirstNonPHI());
	
	//yyyy(mod);
	
	//GlobalVariable* std_fList = mod.getGlobalVariable("std_functions");
	//errs() << * std_fList ;
	
	//errs() << "\n    " << * stdcall ;
	//IRBuilder<> builder(stdcall->getParent()) ;
	//builder.SetInsertPoint(stdcall);
	Value * str = builder.CreateGlobalStringPtr(  " in " + f->getName().str() );
//	Value * Fstr = builder.CreateGlobalStringPtr( f->getName().str() );
//	
//	
//	Value * ld = builder. CreateLoad(std_fList,"load_stdfunctionptr");
//	Constant * constant  = builder.getInt32(FPRINTF);
//	Value * idx = builder.CreateInBoundsGEP(ld,constant ) ;
//	Value * ld2 = builder.CreateLoad(idx);
//	CastInst* castinst  = cast <CastInst> (builder.CreateBitCast(ld2, printf__->getType() ));
//	
//	std::vector<Value *>fprintfArgs;
//	fprintfArgs.push_back(formatstr);
//	fprintfArgs.push_back(Fstr );
//	builder.CreateCall (castinst , fprintfArgs , "call_fprintf");
	
	
	builder.CreateCall(mod.getFunction("debugMsg") , {str} );
	
	//errs() << "\n ======= " <<   f->getEntryBlock() << "\n +++++++ \n" ;

	return;
}


unsigned long
getAllMemAccessInst(Module &mod){
	
	MemAccessInst * mInst ; unsigned long count = 0;

	for (auto Fname : UserFunctions ){
		Function * F = mod.getFunction(Fname);
		for (auto BI = F->begin(); BI != F->end(); ++BI){
			for (auto I = BI->begin(); I != BI->end(); ++I){
				mInst = MemAccessInst::get(I);
				if (mInst){ AllMemAccessInst.push_back(mInst); count++; }
			}
		}
	}
	return count ;
}

unsigned int
getAllCallInst(Module &mod){
	
	unsigned long count = 0;
	for (auto Fname : UserFunctions ){
		Function *F= mod.getFunction(Fname);
		for (auto BI = F->begin(); BI != F->end(); ++BI){
			for (auto I = BI->begin(); I != BI->end(); ++I){
				if(CallInst* call = dyn_cast<CallInst>(I)){
					//exclude system function
					if(call->getCalledFunction()->getBasicBlockList().size() == 0){
						errs() << "\n  skip call to : " << call->getCalledFunction()->getName().str() ;
						continue;
					}
					//if (call->getCalledFunction() == mod.getFunction("exit"))continue ;
					//if (call->getCalledFunction() == mod.getFunction("_IO_putc"))continue;
					CallInstList[call] = 0;
	}}}}
	
	return count ;
}


int VariableArgumentPass(Module &mod){
	
	int count = 0;
	for (auto Fname : UserFunctions ){
		Function *F = mod.getFunction(Fname);
		if (F->isVarArg())
		{
			count++;
			errs() << "\n is Varg : " << F->getName().str() << " , " << *F->getType() ;
			// find all calls to this
			for (auto c: CallInstList){
				if(c.first->getCalledFunction() == F ){
					errs() << "\n    " << *c.first ;
				}
			}
				
		}
	}
	
	
	//Function * f1 = mod.getFunction("_fwriteErrStream__");
	//Function * f2 = mod.getFunction("_fwriteErrStream");
	
	errs() << "\n\n" ;
	
	return count;
}



int
getUserfunctions(Module &mod){
	int fcount = 0;
	
	std::ifstream ifs;
	
	
	/* Get functions information: begin */
	ifs.open("_func_names", std::fstream::in);
	//assert(ifs.good());
	
	errs() << "{" ;
	
	while (ifs.good()) {
		
		
		std::string func_name;
		ifs >> func_name ;
		
		// Ignore white spaces after the last line
		if (func_name.empty()) continue;
	
		Function * f = mod.getFunction(func_name);
		if(!f){
			errs() << "\n Error : \"" << func_name << "\" not present " ;
			return 0;
		}
		fcount++;
		UserFunctions.push_back(func_name);
		errs() << f->getName() << ", " ;
	}
	errs() << "}" ;
	return fcount;
}

namespace
{
	struct SecureNVMPass : public ModulePass
	{
		static char ID; // Pass identification, replacement for typeid
		
		SecureNVMPass() : ModulePass(ID) {}
		
		virtual void getAnalysisUsage(AnalysisUsage &AU) const
		{	AU.addRequired<CallGraphWrapperPass>(); }
		
		
		virtual bool runOnModule(Module &mod)
		{
			mod.materializeAll();
			TD = new DataLayout( &mod );
			LLVMContext &context = mod.getContext();
			CreateSpAsmFtnType(mod );
			
			if(!getUserfunctions(mod)){return false;}
			
			getAllMemAccessInst(mod);
			errs() << "\n MemAccessInstCount : " << AllMemAccessInst.size() ;
			getAllCallInst(mod);
			errs() << "\n CallInstList : " << CallInstList.size() ;
			
			//VariableArgumentPass(mod);
			
			//return false ;
			
			// Call Graph
			CallGraph &cg = getAnalysis<CallGraphWrapperPass>().getCallGraph();
			
			runCodeMgtPass(mod,cg);
			for(auto c : CallInstList){ CallInstList[c.first] += 2 ;}
			//runStackMgtPass(mod ,cg );
			for(auto c : CallInstList){ CallInstList[c.first] += 1 ;}
			
			//runHeapMgtPass(mod ,cg );
			insertAddrTrans(mod,cg);
			
			// swap the main function
			Function * user_main = mod.getFunction("main");
			Function * spmMgtInit = mod.getFunction("spmMgtInit");
			user_main->setName("userEntry");
			spmMgtInit->setName("main");
			// call runtime lib end of execution function in user exit function
			InsertExitFtnCall(mod);
			
			errs() << "\n CallInstList : " << CallInstList.size() << "\n" ; 
			errs() << "\n Call inst list for " ; 
			errs() << "\n   Only Stack managements: " ;
			for (auto c : CallInstList ) { if(c.second == 1){errs()<<"\n     "<<*c.first;}}
			errs() << "\n   Only Code managements: " ;
			for (auto c : CallInstList ) { if(c.second == 2){errs()<<"\n     "<<*c.first;}}
			errs() << "\n   Both Stack andO Code managements: " ;
			for (auto c : CallInstList ) { if(c.second == 3){errs()<<"\n     "<<*c.first;}}
			errs() << "\n" ;
			// create the call instructions
			for (auto c : CallInstList ) { if(c.second == 3){ CCC(mod,c.first,c.second);}}
				
			//CreateWrapToFtnWithCodeMgtStackMgt(mod , c);
			//CreateWrapToFtnWithStackMgt(mod , c);
			//CreateWrapToFtnWithCodeMgt(mod , c);
				
			errs() << "\n" ;
			for(auto I : deleteList){I->eraseFromParent();}
			return true ;
			 			
		}		
	};
}
char SecureNVMPass::ID = 0; //Id the pass.
static RegisterPass<SecureNVMPass> S("SecureNVMPass", "Make spm based application with secured NVM"); //Register the pass.

	
	
	
