
#include "malloc.h"

// simple inefficient malloc implementation
#define heapSize (4096 * 4096)
char simpleMallocArea[heapSize];
size_t usedPtr = 0;
void * _malloc(size_t size){
	char * rtn = &simpleMallocArea[usedPtr];
	usedPtr+=size;
	if(usedPtr > sizeof(simpleMallocArea) ){ _debug( " Error : Malloc space exceeded ") exit(-1); }
	_debug2("\n [malloc {ptr:%p , size:%u} ] " , rtn , size)
	return (void *)rtn;
}
void _free (void * ptr){}






