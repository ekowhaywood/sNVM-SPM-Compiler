
//#include "substdlib.h"

struct globalArguments _gArgs;

FILE * filess ;

extern int Entry();

#ifdef ShowDebugMsg
FILE * _debugFILE;
#endif

int main(int argc , char ** argv ){
		
#ifdef ShowDebugMsg
#ifdef UseDebugFile
	char filename[128];
	time_t rawtime; time ( &rawtime );
	struct tm * timeptr = localtime ( &rawtime );
	snprintf(filename,sizeof(filename),"debug_%2d.%.2d.%.2d.%.2d.txt",
			 timeptr->tm_mday, timeptr->tm_hour,
			 timeptr->tm_min, timeptr->tm_sec);
	
	_debugFILE = fopen(filename,"w");
#else
	_debugFILE = stderr;
#endif
#endif
	
	_gArgs.argc = argc ;
	_gArgs.argv = argv ;
	
	_gArgs.inputStream = stdin ;
	_gArgs.outputStream = stdout ;
	
	system ("m5 resetstats");
	_Exit(Entry());
	system ("m5 dumpstats");
	
	return 0;
}


void _Exit(int status){
	
	system ("m5 dumpstats");
	_debug1("\nreturned value:%d\n",status)
	
	//_debug2("\n compare stdout , _gArgs.outputStream (%p:%p)\n", stdout , _gArgs.outputStream )	
	//fflush(_gArgs.outputStream);
	
	exit(status);
}

size_t
_getInputStreamLength(){
	fseek (_gArgs.inputStream , 0 , SEEK_END);
	size_t lSize = ftell (_gArgs.inputStream);
	rewind (_gArgs.inputStream);
	_debug1("\n input size :%u", lSize);
	return lSize;
}

size_t
_readInputStream (char * dstbufferPtr , size_t size, size_t count ){
	//_debug2("\n read buf:%p size:%u" , dstbufferPtr , size * count);
	size_t rtn = fread (dstbufferPtr,size,count,_gArgs.inputStream);
	//_debug1(" done size:%u \n" , rtn);
	return rtn ;
}

size_t
_writeOutputStream(const char *srcbufferPtr, size_t size , size_t count){
	
	return fwrite (srcbufferPtr, size , count ,_gArgs.outputStream  );
}



