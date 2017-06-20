#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <elf.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
//#include <libelf.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>


#include "common.h"


enum TRANSDIR {SPM2MEM, MEM2SPM};

typedef struct _Region {
	unsigned int func_index;
} Region;

struct Mgt_code_meta {
	unsigned int idx ;
	char * spm_addr;
	char * nvm_addr;
	unsigned int instCount ;
	unsigned int isEnc ;
	unsigned int idx_region;
	Region * region ;
	const char * name_string ;
}Mgt_code_meta;

StaticData
struct Mgt_code_meta mgtCodeMeta[50];

extern char * __load_start_sec_mgtCode_1 ;
extern char * __load_stop_sec_mgtCode_1 ;
Region _region_table[10] ;
int mapping_table_size = 0;
int region_table_size = 0;


void setMgtFuncMeta(unsigned int func_idx,char * fname, unsigned int Region,unsigned int vma, unsigned int lma, unsigned int size);


//int dmaNvmm2Spm (unsigned int * dst, unsigned int * src, size_t cc)
#define dmaNvmm2Spm(dstAddr, srcAddr, count , copied)  {\
	int ix ; \
	unsigned int * dst = (unsigned int *)dstAddr ; \
	unsigned int * src = (unsigned int *)srcAddr ; \
	size_t cc = count ; \
	for (ix=0; ix<cc; ix++){ dst[ix] = src[ix]; } \
	copied = ix ; \
	}


InitCode char *
codeMgtInit (void ){
	
	setMgtFuncMeta(1,"main",0,(unsigned int ) &main ,(unsigned int)&__load_start_sec_mgtCode_1 ,(unsigned int) (&__load_stop_sec_mgtCode_1 - &__load_start_sec_mgtCode_1)  );
	
	
#ifdef ENCRYPT_CODE
	initCodeMgtEncDec();
#endif
	
#ifdef ShowExecutionReport
	//fprintf( _reportFile ,"\n Stack Area \n    SPM: { 0x%p ~~ 0x%p [%u] }, \n    NVMM: { 0x%p ~~ 0x%p [%u]} \n",
	//		spmStackLbound, spmStackUbound,(uint32_t)(spmStackUbound - spmStackLbound),
	//		nvmmStackLbound, nvmmStackUbound, (uint32_t)(nvmmStackUbound - nvmmStackLbound));
	//fflush(_reportFile);
	
	char buf[512];
	snprintf(buf , sizeof(buf), "%d" ,region_table_size );
	strcat(csvStr3,buf);
	
#endif
	return (char *)0 ;
}

InitCode int
codeMgtEnd(void){
	
	_report("\n\n Code Managment ")
	printstat(CodeFetch)
	printstat(InstCount)	
	return 0;
}


InitCode int
setRegion(int num){
	
	_debug2( "\n setRegion {num of regions:%d , _region_table: %p }" , num , &_region_table   )
	
	region_table_size = num;
	for(int i=0; i<num; i++) {
		_region_table[i].func_index = 0;
	}
	
	return 0;
}

InitCode void
setMgtFuncMeta(unsigned int func_idx,char * fname, unsigned int Region,unsigned int vma, unsigned int lma, unsigned int size){
	
	mgtCodeMeta[func_idx].name_string  = fname;
	mgtCodeMeta[func_idx].idx_region = Region ;
	mgtCodeMeta[func_idx].region = & _region_table [Region]  ;
	
	mgtCodeMeta[func_idx].nvm_addr = (char *)lma ;
	mgtCodeMeta[func_idx].spm_addr = (char *)vma ;
	mgtCodeMeta[func_idx].instCount = size / 4 ;
	mgtCodeMeta[func_idx].isEnc = 1;
	
	// for now, system loader is not loading overlayed code correctly
	// we copy code to nvmm manually
	{
		unsigned int * dst = (unsigned int *)nvmmMalloc(size) ;
		unsigned int * src = (unsigned int *)mgtCodeMeta[func_idx].spm_addr ;
		_debug ("\n  Copy code to nvmm")
		_debug2 ( " { 0x%p to 0x%p }" , src , dst )
		size_t cc = mgtCodeMeta[func_idx].instCount ;
		for (int ix=0; ix<cc; ix++){ dst[ix] = src[ix]; }
		// Set the new nvmm addr
		mgtCodeMeta[func_idx].nvm_addr = (char *)dst;
	}
	
	
#ifdef ShowSpmDebugMsg
	fprintf(_debugf , "\n  F:%u nvmm:%u , vma:%u , instCount:%u , RegionIdx:%u, %s" ,
			 func_idx,
			 (unsigned int  )mgtCodeMeta[func_idx].nvm_addr ,
			 (unsigned int  )mgtCodeMeta[func_idx].spm_addr  ,
			 mgtCodeMeta[func_idx].instCount ,
			 mgtCodeMeta[func_idx].idx_region ,
			 mgtCodeMeta[func_idx].name_string) ;
	fflush( _debugf ) ;

#endif
	
	
	
}



StaticCode char *
getMgtCode(unsigned int func_index){
	
	if (func_index == 0){ _debug1("\n func index:%u , return nill " , func_index) return 0;}
	
	
	if(func_index != mgtCodeMeta[func_index].region->func_index){
		size_t instC = 0;

		addone(CodeFetch) ;
		
#ifdef ShowSpmDebugMsg
		static unsigned long dmaCount__;
		++dmaCount__;
		fprintf (_debugf,
				  "\n  Get Code %lu\t{ idx=%u, region->funcIdx=%u, spmAddr=0x%p, NvmmAddr=0x%p, InstCount=%u , \"%s\" }",
				  dmaCount__, func_index ,
				  mgtCodeMeta[func_index].region->func_index,
				  mgtCodeMeta[func_index].spm_addr ,
				  mgtCodeMeta[func_index].nvm_addr ,
				  mgtCodeMeta[func_index].instCount,
				  mgtCodeMeta[func_index].name_string
				  );
		fflush(_debugf);
#endif
		
		dmaNvmm2Spm(mgtCodeMeta[func_index].spm_addr, mgtCodeMeta[func_index].nvm_addr ,mgtCodeMeta[func_index].instCount , instC)
		
		addstat(InstCount,instC)
		
		mgtCodeMeta[func_index].region->func_index = func_index;
	
		_debug1 ("\n  Get Code  \t{ inst copied=%u }", instC)
	}

	_debug1("\n return addr:%p" , mgtCodeMeta[func_index].spm_addr)
	return mgtCodeMeta[func_index].spm_addr ;
	
}






