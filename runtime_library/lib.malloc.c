

//#include "RTlib.h"

//#include "RTLMalloc1.h"

#include "common.h"


// simple inefficient malloc implementation
#define heapSize (16 MB)
char * nvmmHeapSpace ;
char * nvmmHeapSpace_break;
size_t usedPtr = 0;

//char * InitHeapAddr ;
char * first_mem_blk;
char * last_mem_blk;
PTRCAST mem_blks_allocated ;


void init_spm_malloc()
{
	
	nvmmHeapSpace = nvmmMalloc(heapSize);
	nvmmHeapSpace_break = nvmmHeapSpace + (heapSize - 1);
	
	first_mem_blk = (char *)(get_blk_addr((unsigned long)nvmmHeapSpace)) + BlockSize;
	//InitHeapAddr = first_mem_blk ;
	//system_break = first_mem_blk;
	//last_mem_blk = first_mem_blk;
	//mem_blks_allocated = 0;
	usedPtr+= (first_mem_blk - nvmmHeapSpace) ;
	
#ifdef ShowExecutionReport
	fprintf (_reportFile, "\n    NVMM { 0x%p ~~ 0x%p [%u] , First_blk:%p, padSize:%u }",
			  nvmmHeapSpace, nvmmHeapSpace_break, heapSize,
			  first_mem_blk,(first_mem_blk - nvmmHeapSpace)
			  );
	fflush(_reportFile);
#endif
}



void * _malloc(size_t size){

	addone( mallocCalls)

	char * rtn = &nvmmHeapSpace[usedPtr];
	usedPtr+=size;
	if(usedPtr > heapSize ){ _debug( " Error : Malloc space exceeded ") exit(-1); }
	_debug2("\n[malloc {ptr:%p , size:%u} ] " , rtn , size)
	return (void *)rtn;
}
void _free (void * ptr){
	addone( freeCalls)
}

int isHeapAddr(char * gAddr)
{
	if (first_mem_blk < gAddr && gAddr < nvmmHeapSpace_break)
	{
		
#ifdef ShowSpmDebugMsg
		//printf("\n isHeapAddr gAddr:%u",(PTRCAST) gAddr);fflush(stdout);
#endif
		return 1;
	}
	
	
#ifdef ShowSpmDebugMsg
	//printf("\n Not HeapAddr gAddr:%u",(PTRCAST) gAddr);fflush(stdout);
#endif
	
	return 0;
}











	




















