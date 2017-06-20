
#include "SecureNvmPass.hpp"

std::map< Function * , unsigned int > funcIndex ;
std::unordered_map <Function *, Value *> funcNameStr;
std::unordered_map <Function *, int> funcOverlay;
std::unordered_map <Function *, std::pair <Value *, Value *>> funcLoadAddr;
std::unordered_set<Function *> referredFuncs;

std::map < int , std::vector<Function * >  > regions_ ;


bool runCodeMgtPass(  Module &mod , CallGraph &cg)
{

	std::stringstream string  ;
	int num_regions;
	
	LLVMContext &context = mod.getContext();
	IRBuilder<> builder(context);
	// Call graph
	//CallGraph &cg = getAnalysis<CallGraphWrapperPass>().getCallGraph();
	
	IntegerType *ty_int8 = builder.getInt8Ty();
	
	// External variables
//	GlobalVariable* gvar_spm_begin = mod.getGlobalVariable("_spm_begin");
//	if (!gvar_spm_begin)
//	gvar_spm_begin = new GlobalVariable(mod, // Module
//										ty_int8,
//										false, //isConstant
//										GlobalValue::ExternalLinkage, // Linkage
//										0, // Initializer
//										"_spm_begin");
	
	// Functions
	Function *func_main = mod.getFunction("main");
	//Function *func_smm_main = Function::Create(cast<FunctionType>(func_main->getType()->getElementType()), func_main->getLinkage(), "smm_main", &mod);
	Function* func_c_init_reg = mod.getFunction("setRegion");
	Function* func_c_init_map = mod.getFunction("setMgtFuncMeta");
	Function* func_c_get = mod.getFunction("getMgtCode");
	assert(func_c_get);
	
	// Code management related
	GlobalVariable* gvar_ptr_region_table = mod.getGlobalVariable("_region_table");
	//assert(gvar_ptr_region_table);
	ConstantInt * const_num_regions = NULL;
	ConstantInt * const_num_mappings = NULL;
	std::ifstream ifs;
	
	
	/* Get functions information: begin */
	ifs.open("_mapping", std::fstream::in);
	//assert(ifs.good());
	
	ifs >> num_regions;
	errs() << "\n number of region :" << num_regions << "\n" ;
	for (int ir = 0 ; ir< num_regions ; ir++){ regions_[(ir+1)] ; }
	
	builder.SetInsertPoint(func_main->getEntryBlock().getFirstNonPHI());
	
	errs() << "\n" ;
	
	unsigned int findex = 1;
	
	while (ifs.good()) {
		
		int region_id;
		std::string func_name;
		ifs >> func_name >> region_id;
		
		// Ignore white spaces after the last line
		if (func_name.empty()) continue;
		
		//DEBUG(
		//errs() << "\t" << func_name << " " << region_id << "\n" ; //);
		
		Function *func = mod.getFunction(func_name);
		referredFuncs.insert(func);
		
		// Create a global string of this function name
		funcNameStr[func] = builder.CreateGlobalStringPtr(func_name, func_name +".name");
		
		// Get the overlay ID of this function
		funcOverlay[func] = region_id;
		regions_[(region_id + 1)].push_back(func);
		
		// set function index
		if (func_name != "main")
		{
			// assign index
			funcIndex[func] = ++findex;
			
			for (auto u : func->users())
			{
				if( CallInst * c = dyn_cast<CallInst>(u))
				if (c->getCalledFunction() == func )
				{
					//errs() << "\n  caller " << *c ;
					wrapInstListForCodeMgt [c] = 1;
				}
			}
			
		}
		else
		{
			funcIndex[func] = 1;
		}
		
		// Create a seperate section for this function and record its load address except for the main function
		{
			string.str("") ;
			string << "sec_mgtCode_" << funcIndex[func] ;
			func->setSection(string.str());
			
			//DEBUG(errs() << fi->getSection() << "\n");
			std::string _startAddr = "__load_start_" ; _startAddr.append(func->getSection());
			std::string _stopAddr = "__load_stop_" ; _stopAddr.append(func->getSection());
			
			GlobalVariable* startAddr = mod.getGlobalVariable(_startAddr);
			if (!startAddr){
				startAddr = new
				GlobalVariable(
							   mod,
							   IntegerType::get(context, 8),
							   true, //isConstant
							   GlobalValue::ExternalLinkage,
							   0, // Initializer
							   // "__load_start_" + func_name);
							   _startAddr
							   );
			}

			GlobalVariable* stopAddr = mod.getGlobalVariable(_stopAddr);
			if (!stopAddr){
				stopAddr = new
				GlobalVariable(
							   mod,
							   IntegerType::get(context, 8), //Type
							   true, //isConstant
							   GlobalValue::ExternalLinkage, // Linkage
							   0, // Initializer
							   //"__load_stop_" + func_name);
							   _stopAddr
							   );
			}
			
			funcLoadAddr[func] = std::make_pair(startAddr, stopAddr);
		}
		
		
		errs() << "\n\t " << funcIndex[func] << " " << func_name << "  sec:" << func->getSection() << " reg:" << funcOverlay[func] ;
		//errs() << "\n\t startAddr:" << *funcLoadAddr[func].first ;
		//errs() << "\n\t stopAddr:" << *funcLoadAddr[func].second ;
		
	}
	
	errs() << "\n" ;
	
	
	
	// make linkerscript
	{
		std::stringstream ld ;
		
		//ld << "\n\n" ;
		//ld << ". = ALIGN(0x20);" << "\n" ;
		//ld << "_spm_code_area_begin = .;" << "\n" ;
		//ld << ". = . + 0x30000 ;" << "\n" ;
		//ld << "_spm_code_area_end = .;" << "\n" ;
		//ld << ". = ALIGN(0x20);" << "\n" ;
		//ld << "_LMA_ = . ;" << "\n\n" ;
		
		
		//		ld << ". = ALIGN(0x20); " << "\n" ;
		//		ld << "_spm_code_area_begin = .;" << "\n" ;
		//		ld << "._spm_alloc_sec_begin _spm_code_area_begin : AT (_spm_code_area_begin) { FILL(0x0) QUAD(0x0) QUAD(0x0) }" << "\n" ;
		//		ld << "_spm_alloc   =  . + 0x30000  ;" << "\n" ;
		//		ld << "._spm_alloc_sec_end _spm_alloc : AT (_spm_alloc) { FILL(0x0) QUAD(0x0) QUAD(0x0) }" << "\n" ;
		//		ld << "_spm_code_area_end = .;" << "\n" ;
		//		ld << ". = ALIGN(0x20);" << "\n" ;
		//		ld << "_LMA_ = . ;" << "\n"  << "\n" ;
		//
		
		ld << " LMA_0 =  . ;  \n" ;
		ld << " VMA_0 = . ;  \n\n"; //ld << " VMA_0 = ADDR(sec__spm_mgt_code) ; \n\n";
		
		//std::string nextlma = "_LMA_" ;
		std::string nextlma = "AT (LMA_0)" ;
		//std::string nextvma = "_spm_code_area_begin" ;
		std::string nextvma = " (VMA_0) " ;
		
		std::string last_section  ;
		
		
		for (auto ir : regions_)
		{
			std::stringstream oo  ;
			//errs() << "\n Region : " << ir.first ;
			
			//ld << "OVERLAY " << nextvma << " : " << nextlma << " {\n" ;
			
			for (auto func : ir.second)
			{
				//_FunctionData * fdata = funcs[func];
				
				//std::string sectionname = fdata->sectionname ;
				ld << "\n" << func->getSection() <<  " : { *(" << func->getSection() << ") } \n" ; // \
					ld << func->getSection() <<  " { *(" << func->getSection() << ") } \n" ;
				
				ld << "PROVIDE(" << funcLoadAddr[func].first->getName().str() << " = LOADADDR(" << func->getSection() << ")) ; \n" ;
				ld << "PROVIDE(" << funcLoadAddr[func].second->getName().str() << " = LOADADDR(" << func->getSection() << ") + SIZEOF(" << func->getSection() << ") ) ; \n" ;
				
				last_section = func->getSection() ; // sectionname ;
			}
			
			
			//ld << "} \n" ;
			
			
			
			
			//nextvma = "_Next_region_VMA_"  ;
			nextlma = "" ;
			nextvma = "" ;
		}
		
		
		ld << "\n\n. = LOADADDR(" <<  last_section << ") + SIZEOF(" << last_section << "); " ;
		ld << "\n_realign_addr = ALIGN(0x20); " ;
		ld << "\n.realign _realign_addr : AT (_realign_addr) { FILL(0x0) QUAD(0x0) QUAD(0x0) } \n\n";
		
		
		
		//errs() << "\n\n" << ld.str() ;
		
		
		std::string strReplace = "/* insert overlay script */";
		std::string strNew = ld.str() ;
		std::ifstream filein("../../program.ld"); //std::ifstream filein("../../util/programLoaderClient.ld");	// default script
		std::ofstream fileout("sNVM.ld");			// modified script
		if(!filein || !fileout){	 errs()   << "Error opening files! \n" ;}
		
		std::string strTemp;
		while(getline(filein,strTemp))
		{
			if(strTemp == strReplace){ fileout << strNew ; }
			else{fileout << strTemp;}
			fileout << "\n" ;
		}
		
		//errs() << "\n" ;
	}

	ifs.close();
	
	  	
	Function * code_mgt_begin = mod.getFunction("codeMgtInit");
	//Function * posi_inst  = mod.getFunction("c_get");
	Function * posi_inst_function   = mod.getFunction("setMgtFuncMeta");
	//Function * posi_inst_function   = mod.getFunction("c_init_reg");
	
	// find "c_get(1);"
	CallInst * call_posi_inst_function   ;
	for (auto ui_ret : posi_inst_function->users())
	{
		if (CallInst *c = dyn_cast<CallInst>(ui_ret) )
		{
			if (c->getParent()->getParent() == code_mgt_begin)
			{
				call_posi_inst_function = c ;
				//errs() << * call_posi_inst_function   ;
				break ;
			}
		}
	}
	
	
	//IRBuilder<> builder(mod.getContext());
	builder.SetInsertPoint(call_posi_inst_function  );
	
	
	// Initalize regions
	const_num_regions = builder.getInt32(num_regions);
	//const_num_mappings = builder.getInt32(funcLoadAddr.size());
	
	builder.CreateCall(func_c_init_reg, const_num_regions, "");
	
	// Initialize mappings
	//LoadInst* region_table = builder.CreateLoad(gvar_ptr_region_table);
	
//		std::vector <Value *> regions;
//		for (int i = 0; i < num_regions; ++i) {
//			regions.push_back(builder.CreateGEP(region_table, builder.getInt32(i)));
//		}
	
	//Function * fm = mod.getFunction("__dummy__init_func_map");
	Function * fm = mod.getFunction("setMgtFuncMeta");
	
	
	//call_args.clear();
	//call_args.push_back(const_num_mappings);
	
//		
	//for (auto ii = funcLoadAddr.begin(), ie = funcLoadAddr.end(); ii != ie; ii++) {
	for (auto ii : funcLoadAddr) {
	//for (auto ii : funcNameStr){
	//DEBUG(
		
		//errs() << ii.first->getName() << " string " << * ii.second ;
	
		Function *func = ii.first;
		
		//errs() << "\n " << func->getName() ;
		
	//	errs() << "\n\t startAddr:" << *ii.second.first ;
	//	errs() << "\n\t stopAddr:" <<  *ii.second.second ;
		
		
		
		std::vector<Value*> call_args;
		
		call_args.push_back(builder.getInt32(funcIndex[func] ));
		call_args.push_back(funcNameStr[func]);
		call_args.push_back(builder.getInt32(funcOverlay[func]));
		
		
		////Value * lma_stop_int = builder.getInt32(0) ;// builder.CreatePtrToInt(ii->second.second, builder.getInt32Ty());
		////Value * lma_start_int = builder.getInt32(0) ; // builder.CreatePtrToInt(ii->second.first, builder.getInt32Ty()) ;
		////Value * vma_int = builder.getInt32(0) ;// builder.CreatePtrToInt( func, builder.getInt32Ty());
		
		Value * lma_start_int =  builder.CreatePtrToInt(ii.second.first, builder.getInt32Ty()) ;
		Value * lma_stop_int = builder.CreatePtrToInt(ii.second.second, builder.getInt32Ty());
		Value * vma_int = builder.CreatePtrToInt( func, builder.getInt32Ty());
		
		
		
		
		//if (func == func_main)
		//call_args.push_back(func_smm_main);
		//else
		call_args.push_back(vma_int) ;
		//call_args.push_back(func);
		
		
		
		call_args.push_back(lma_start_int) ;
		//call_args.push_back(ii.second.first);
		
		
		// calculate size
		Value * subInst =  builder.CreateSub( lma_stop_int, lma_start_int );
		call_args.push_back(subInst);
		
		
		//errs() << "\n\t passed arguments" ;
		for (auto vl : call_args)
		{
		//	errs() << "\n\t    " << *vl->getType()  ;
		}
		
		builder.CreateCall(fm , call_args );
		
		
		
	}

	//errs() << * code_mgt_begin ;
	 
	return true;


}



  
