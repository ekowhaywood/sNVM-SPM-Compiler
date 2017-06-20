
#include "common.h"

#define nvmmSize (64 MB)
StaticData char  *nvmm_region;
StaticData size_t nvmmMallocNextPtr=0;

char * systemStackPtr;
char * spmStackBase;
int main_argc ; char ** main_argv; int main_rtn ;

StaticCode int
spmMgtInit(int argc , char ** argv)
{
	
#ifdef ShowSpmDebugMsg
#ifdef UseDebugFile
	char filename[128];
	time_t rawtime; time ( &rawtime );
	struct tm * timeptr = localtime ( &rawtime );
	snprintf(filename,sizeof(filename),"debugSpm_%2d.%.2d.%.2d.%.2d.txt",
			 timeptr->tm_mday, timeptr->tm_hour,
			 timeptr->tm_min, timeptr->tm_sec);
	
	_debugFILE = fopen(filename,"w");
#else
	_debugFILE = stderr;
#endif
#endif
	
	
	_debug("\n Running SPM Application ")
	main_argc = argc; main_argv = argv ;
	
	InitStats() ;
	
#ifdef UsePhyNvmm
#define NVM_PDDR 0x0C0000000
	int fd2 = open("/dev/mem",O_RDWR|O_SYNC);
	if(fd2 < 0){
		printf("2 Can't open /dev/mem\n"  );return 1;}
	nvmm_region = (char *) mmap (\
								(void *)(0x76ffe000), nvmmSize, \
								PROT_READ|PROT_WRITE|PROT_EXEC, MAP_SHARED, \
								fd2, NVM_PDDR );
	if(nvmm_region == NULL) {
		printf("Can't mmap\n" ) ; return 1;
	}
	else {
		_debug1("\n Map successful {Vaddr=0x%p , expected 0x76ffe000}",nvmm_region);
	} //Address=0x76ffe000 0x76ffe000 [0x76FFF000]
#else
	
	nvmm_region = (char *)malloc( nvmmSize);
	if(nvmm_region == NULL) { printf("Can't allocate memory \n" ) ; return 1;}
	
#endif
	
	//getMgtCode(0); // initialization functions section index is always 0
	
#ifdef WITH_ENC_DEC
	// initialize enc/dec data used by all mgt
	//initEncDec();
 
	if (sodium_init() == -1)
	{
		printf ("libsodium Error");
		return ;
	}
 

#endif
 
 	codeMgtInit();
	stackMgtInit();
	heapMgtInit();
	
	getMgtCode(1); // cache user main function , user main function index is always 1
	_debug1 ( "\n Entering user code @addr:0x0%p " , &main )
	_report("\n\n---Begin execution---\n")
	//system ("m5 resetstats"); // reset gem5 stats
	//system ("m5 dumpstats");

	getSP(systemStackPtr); // save the system stack pointer 
	
	_debug1 ("\n  systemStackPtr :0x%p" , systemStackPtr);
	_debug1 ("\n  spmStackUbound :0x%p" , spmStackUbound);
	
	putSP(spmStackUbound); // set stack pointer to upper bound of spm stack space
	main( main_argc , main_argv);
	
	return 0 ;
}

StaticCode void
endExecution(){
	//TODO place this before the system exit call using compiler pass
	//putSP(systemStackPtr); // restore system stack pointer , 
	//system ("m5 dumpstats");
	_report("\n---End of execution---")

	
#ifdef ShowExecutionReport
	strcat(csvStr,csvStr1);
	strcat(csvStr,",");
#endif
	heapMgtEnd();

	
#ifdef ShowExecutionReport
	strcat(csvStr,",,");
	strcat(csvStr,csvStr2);
	//strcat(csvStr,",");
#endif
	stackMgtEnd();

	
#ifdef ShowExecutionReport
	strcat(csvStr,",,");
	strcat(csvStr,csvStr3);
	//strcat(csvStr,",");
#endif
	codeMgtEnd();
	
	
	
#ifdef ShowExecutionReport
	
	//_report1("\n csv { %s } ", csvStr );
	_report("\n\n" );
	
	FILE *csv = fopen("../reports.csv","a");
	fprintf(csv , "%s\n",csvStr);
	fclose(csv);
#endif
	
}
 
StaticCode char *
nvmmMalloc(size_t size){
	
	char * ptr  = &(nvmm_region[nvmmMallocNextPtr]) ;
	nvmmMallocNextPtr += size ;
	return ptr ;
}

StaticCode void debugMsg (const char * msg ) { _debug1 ("\n_DebugMsg{%s}",msg) }
StaticCode void debugMsgAddr (const char * f , char * addr  ) { _debug1 (f,addr) }


// variable function argument handling
unsigned int * currentVargFrame = NULL;
char VarArg[1024] ;
unsigned int * startVargFrame(){
	
	unsigned int *ptr ;
	if (currentVargFrame){
		_debug1 ("\n\n new frame : current frame:%p \n\t", currentVargFrame)
		unsigned int * dataStartAddr = currentVargFrame + 3;
		unsigned int datalength = currentVargFrame[2];
		ptr = dataStartAddr + datalength ;
		unsigned int ** previousFrameDataAddr = (unsigned int **)(ptr + 1);
		previousFrameDataAddr[0] = currentVargFrame;
		
		currentVargFrame = ptr;
		dataStartAddr = ptr + 3;
		ptr[0] = (unsigned int)dataStartAddr ;
		currentVargFrame[2] = 0;
		_debug3(" new ptr:%p , prevoiusPtr:%p , dataStartAddr:%x ", ptr , (unsigned int *)ptr[1] ,  ptr[0] )

	}else{
		_debug ("\n first : ")
		ptr = (unsigned int *)VarArg;
		unsigned int ** previousFrameDataAddr = (unsigned int **)(ptr + 1);
		previousFrameDataAddr[0] = NULL;
		
		currentVargFrame = ptr;
		unsigned int * dataStartAddr = ptr + 3;
		ptr[0] = (unsigned int)dataStartAddr ;
		currentVargFrame[2] = 0;
		_debug3 ( " new ptr:%p , prevoiusPtr:%p , dataStartAddr:%x ", ptr , (unsigned int *)ptr[1] ,  ptr[0] )
	}
	return ptr;
}

void append(unsigned int * VargFramePtr, unsigned int data){
	unsigned int *dataStartAddr = VargFramePtr + 3;
	unsigned int datalength = VargFramePtr[2];
	unsigned int * dataAddr = dataStartAddr + datalength ;
	dataAddr[0] = data;
	VargFramePtr[2] = datalength + 4;
	
	_debug5("\n append ptr:%p , prevoiusptr:%x , datalength:%u , dataStartAddr:%p , dataAddr:%p ", VargFramePtr , VargFramePtr[1], VargFramePtr[2] , dataStartAddr , dataAddr )
	
	_debug1 (" (%u) ", (dataAddr - dataStartAddr)) 
			 
}
			 
unsigned int getNext(unsigned int * VargPtr , unsigned int dataSize ){
	
	unsigned int * dataAddr =  (unsigned int *)VargPtr[0] ;
	_debug3 ("\n get data , ptr:%p  , size:%u , dataAddr:%p" , VargPtr , dataSize , dataAddr)
	
	unsigned int data = *(dataAddr);
	VargPtr[0] = (unsigned int) (dataAddr + dataSize)  ;
	unsigned int * nextDataAddr = (unsigned int *)VargPtr[0];
	_debug3 ( " , data:%u  , nextDataAddr:%x (%u)"  , data , VargPtr[0] , ( nextDataAddr - dataAddr) )
	return data ;
}

#define my_va_arg_32bit( var, ptr ,type )  var = (type) getNext(VargPtr , 4) ;

void restorePreviousFrame(unsigned int * VargFramePtr){
	unsigned int ** previousFrameDataAddr = (unsigned int **)(VargFramePtr + 1);
	currentVargFrame =  previousFrameDataAddr[0];
	_debug2( "\n restore ptr:%p , prevoiusPtr:%p \n\n", VargFramePtr , currentVargFrame  )
}


// report printing functions
 
#ifdef ShowExecutionReport
#include <time.h>
FILE * _reportFile;
char csvStr[4096];
 char csvStr1[4096];
 char csvStr2[4096];
 char csvStr3[4096];
void InitStatsFile(){

	strcat(csvStr,AppName);
	strcat(csvStr,",");
	
#ifdef UseReportFile
	char filename[128];
	time_t rawtime; time ( &rawtime );
	struct tm * timeptr = localtime ( &rawtime );
	snprintf(filename,sizeof(filename),"report_%2d.%.2d.%.2d.%.2d.txt",
			 timeptr->tm_mday, timeptr->tm_hour,
			 timeptr->tm_min, timeptr->tm_sec);
	
	_reportFile = fopen(filename,"w");
#else
	_reportFile = stderr;
#endif
}

void printStatistics( StatsC * stat , const char * vname ) {
	
	char buf1[512]; char buf2[512]; char buf3[512];
	
	snprintf (buf1,sizeof(buf1), "%-120s",vname );
	
	if(stat->high > 0x00000000) snprintf( buf2,sizeof(buf2), "%u  +(%u*0xffffffff)" , stat->low ,stat->high);
	else  snprintf(buf2,sizeof(buf2) ,"%u" , stat->low ) ;
	snprintf(buf3 , sizeof(buf3), "%-100s",buf2 );
	
	fprintf (_reportFile , "\n    %-.*s :%-.*s %s ", _statColumn1 ,buf1,_statColumn2, buf3, stat->desc);
	
	if(stat->showInCsv ){strcat(csvStr,","); strcat(csvStr,buf2); }
}

__attribute__ ((always_inline)) void Increament(StatsC *var) {
 
	if(var->low == 0xffffffff){
		var->high ++; 
		var->low = 0x00000000;
	}
	var->low++ ;  
}

__attribute__ ((always_inline)) void  IncreamentBy(StatsC *var , uint32_t value){

	uint32_t a = 0xffffffff - var->low; 
	if (a < value){ 
		var->high ++; 
		var->low = value - a ; 
	}else{ 
		var->low+= value ; 
	} 
}
 
#endif


#ifdef ShowSpmDebugMsg
FILE * _debugFILE ;
#endif




