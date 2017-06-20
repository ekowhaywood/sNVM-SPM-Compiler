
#include "mem.h"


void * _memcpy (void * destination, const void * source, size_t num ){
	int ix ;
	char * dst = (char  *)destination ;
	char * src = (char  *)source  ;
	//size_t cc = count ;
	for (ix=0; ix<num; ix++){
		dst[ix] = src[ix];
	}
	return destination ;
}

void  *  _memset ( void * ptr, int value, size_t num ){
	int ix ;
	char * dst = (char  *)ptr ;
	for (ix=0; ix<num; ix++){
		dst[ix] = value;
	}
	return ptr ;
} 

