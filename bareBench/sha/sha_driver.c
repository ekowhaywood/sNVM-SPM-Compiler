/* NIST Secure Hash Algorithm */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "sha.h"

SHA_INFO sha_info;
BYTE *inData ;

int Entry()
{
    //FILE *fin;
    //SHA_INFO sha_info;

	fprintf( stdout , "\n1 stdout : %p , _gArgs.outputStream : %p ", stdout , filess );

	
	size_t lSize=0;//_getInputStreamLength();
	//inData = (BYTE *)_malloc(lSize);
//	_readInputStream((char *)inData,1,lSize);
	
	fprintf( stdout , "\n2 stdout:%p(%p) , filess:%p(%p) , inData:%p(%p) , inData_end:%p ", &stdout ,stdout , &filess , filess , &inData, inData , (inData +lSize ) );

	
    //if (argc < 2) {
	//fin = stdin;
	//sha_stream(&sha_info,inData, lSize); 
	sha_stream(&sha_info,stdin);
	
	fprintf( stdout , "\n3 stdout:%p(%p) , filess:%p(%p) , inData:%p(%p) , inData_end:%p ", &stdout ,stdout , &filess , filess , &inData, inData , (inData +lSize ) );

	
	//fprintf( stdout , "\n3 stdout : %p , _gArgs.outputStream : %p ", stdout ,filess );

	
	sha_print(&sha_info);
//    } else {
//	while (--argc) {
//	    fin = fopen(*(++argv), "rb");
//	    if (fin == NULL) {
//		printf("error opening %s for reading\n", *argv);
//	    } else {
//		sha_stream(&sha_info, fin);
//		sha_print(&sha_info);
//		fclose(fin);
//			exit(0);
//	    }
//	}
//    }

	_free(inData);
    return(0);
}
