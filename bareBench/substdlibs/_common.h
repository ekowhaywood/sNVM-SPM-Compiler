
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define IOFILE FILE*


#define _fprintf simple_fprintf
#define _printf simple_printf
#define _fflush fflush

#ifdef ShowDebugMsg
#include <time.h>
extern FILE * _debugFILE ;
#define _debugf _debugFILE
#define _debug(format)		fprintf (_debugFILE , format ) ;  fflush( _debugFILE );
#define _debug1(format,a)		fprintf (_debugFILE , format , a ) ;  fflush( _debugFILE );
#define _debug2(format,a,b)	fprintf (_debugFILE , format , a ,b ) ; fflush( _debugFILE );
#else
#define _debug(format)		{}
#define _debug1(format,a)		{}
#define _debug2(format,a,b)	{}
#endif

struct globalArguments{
	int  argc ;
	char ** argv  ;
	char ** env ;
	int returnV ;
	IOFILE inputStream ;
	IOFILE outputStream ;
	
}globalArgument;
extern struct globalArguments _gArgs;

extern FILE * filess;

extern size_t _getInputStreamLength();
extern size_t _readInputStream (char * dstbufferPtr , size_t size, size_t count );
extern size_t _writeOutputStream(const char *srcbufferPtr, size_t size , size_t count);
//extern int _writeOutputStreamf( const char * format, ... );




