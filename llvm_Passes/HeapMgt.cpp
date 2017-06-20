
#include "SecureNvmPass.hpp"


bool insertAddrTrans(  Module &mod , CallGraph &cg)
{
	
	Function * transf = mod.getFunction("addrTranslation");
	
	errs() << " \n addrTranslation type :" << *transf->getType() << "\n" ;
	
	for(auto mInst : AllMemAccessInst ){
		
		if (mInst->operandType != MemAccessInst::dynamic ) continue ;
		
		IRBuilder<> builder (mod.getContext());
		builder.SetInsertPoint(mInst->Inst);
		
		
		PointerType * ptrT = Type::getInt32PtrTy(mod.getContext());
		PointerType * addrTy = dyn_cast<PointerType>( mInst->getPointerOperand()->getType()) ;
		 
		
		errs() << " \n translate  " << *  mInst->Inst  << "\n  currnt addr type : " << *addrTy  << " ,  elementType : " << *addrTy->getElementType() << "  , " << *ptrT  ;
		
		Value * newAddr ;
		if(addrTy->getElementType()->isIntegerTy(32)){
			errs() << " \n no addr cast :" << *mInst->getPointerOperand() ;
			std::vector<Value *>arg ;
			arg.push_back(mInst->getPointerOperand());
			arg.push_back(builder.getInt32(mInst->type));
			arg.push_back(builder.getInt32(TD->getTypeAllocSize(addrTy->getElementType())));
			newAddr = builder.CreateCall(transf, arg);
			errs() << "\n trans Call : " << *newAddr ;
		}else{
			errs() << " \n cast addr :" << *mInst->getPointerOperand() ;
			std::vector<Value *>arg ;
			arg.push_back
			(builder.CreateBitCast
			 (mInst->getPointerOperand(),
			  ptrT ));
			
			arg.push_back(builder.getInt32(mInst->type));
			arg.push_back(builder.getInt32(TD->getTypeAllocSize(addrTy->getElementType() )));
			newAddr = builder.CreateCall(transf, arg);
			errs() << "\n trans Call : " << *newAddr ;
			newAddr = builder.CreateBitCast(newAddr, addrTy);
		}
		
		mInst->setPointerOperand(newAddr);
		
		errs() << " \n new addr : " << *newAddr  << "\n" ;
		
	
	}
	
	return true;
}

void replaceMallocAndFree (Module &mod)
{
	
	errs() << "\n ReplaceMallocFree\n" ;
	Function * RTlib_malloc = mod.getFunction("RTlib_malloc" );
	Function * RTlib_calloc = mod.getFunction("RTlib_calloc" );
	Function * RTlib_free = mod.getFunction("RTlib_free" );
	Function * malloc = mod.getFunction("malloc" );
	Function * calloc = mod.getFunction("calloc" );
	Function * free = mod.getFunction("free" );
	
	
	if(malloc) {
		int cc;
		for (auto U :malloc->users () ){cc++;}
		malloc->replaceAllUsesWith(RTlib_malloc);
		errs() << " Malloc calls : "<< cc ;
	}
	
	
	
	if(calloc) {
		int cc;
		for (auto U :calloc->users () ){cc++;}
		calloc->replaceAllUsesWith(RTlib_calloc);
		errs() << " calloc calls : "<< cc ;
	}
	
	if(free) {
		int cc;
		for (auto U :free->users () ){cc++;}
		free->replaceAllUsesWith(RTlib_free);
		errs() << " free calls : "<< cc ;
	}

	
}



