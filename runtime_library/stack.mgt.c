
#include "common.h"


//#define _spm_stack_space_size ((   20 * 1024) / 4)
#define BLKSIZE _spm_stack_space_size
//#define _mem_stack_space_size ((100 * 1024) / 4)

typedef struct
{
	char *spm_addr; // location when present in SPM
	char *mem_addr; // location if evicted to memory
	unsigned int ssize; // size of stack frame
	int status; // --1: resides in SPM; --0 : resides in memory
} STACK_ENTRY;


// pointer threats resolution
//#define BUFF_SIZE 30
//typedef struct struct_l2g_mgt_buff
//{
//	uint64_t buff [ 128 / 8] ;
//	char * laddr ;
//	char * ptr ;
//	uint32_t inuse;
//	uint32_t _stack_depth ;
//	uint32_t DataTypeSize ;
//}
//struct_l2g_mgt_buff;
//struct struct_l2g_mgt_buff bufflist[BUFF_SIZE] ;
//

#ifdef WITH_ENC_DEC
void initStackMgtEncDec  (void) ;
#endif

#ifdef ShowExecutionReport
uint32_t spm2mem = 0;
uint32_t mem2spm = 0;
uint32_t max_sp = 0;
uint32_t min_sp = 200000000 ;

uint32_t spm_stack_access = 0;
uint32_t mem_stack_access = 0;
uint32_t not_stack_access = 0 ;
uint32_t access_calls = 0 ;
unsigned long totalMemUpdate = 0;
#endif

#ifdef ShowBitFlips
unsigned long bit_flips = 0 ;
//uint32_t enc_bit_flip = 0;

//unsigned int new_mem_stack_debug [ _mem_stack_space_size ] ;
#endif




int _stack_depth = 0;
STACK_ENTRY _stack[100];


//__attribute__ ( (section ("sec__spm_mgt_stack")))
//char __spm_mgt_stack[24 * 1024 ] ;

//__attribute__ ( (section ("sec__spm_mgt_stack")))
char spmStackSection [ spmStackSize ];
//unsigned int new_mem_stack [ nvmmStackSize ];


StaticData char * spmStackLbound;
StaticData char * spmStackUbound;
StaticData char * nvmmStackLbound;
StaticData char * nvmmStackUbound;
StaticData char * currentstackPtr;

//
//char * _spm_begin;
//char * _spm_end;
//char * _mem_stack_begin ;
//char * _mem_stack_end ;
//
//
//char *_spm__1 ;
//char *_spm__2;
//char * _spm__3;
//




void _sstore() __attribute__((noinline));
void _sload() __attribute__((noinline));
unsigned int spm_to_mem (char * spmAddr , char * memAddr , unsigned int ssize , int _stack_depth) ;
unsigned int mem_to_spm (char * spmAddr , char * memAddr , unsigned int ssize , int _stack_depth) ;




// evict oldest stack frames to make space for callee
StaticCode void
_sstore()
{
	//__dummy_fflushStdout(" in _sstore");
	
	_stack[_stack_depth].spm_addr = currentstackPtr ;
	_stack[_stack_depth].ssize = spmStackUbound - _stack[_stack_depth].spm_addr; // calculate the size of the caller stack frame
	
	uint32_t _spm__used =  _stack[_stack_depth].ssize ; // for stats
	
	////printf(" \n _stack[_stack_depth].ssize :%u",  (uint32_t )_stack[_stack_depth].ssize);
	
	////printf(" \n _stack_depth :%u", (uint32_t )_stack_depth);
	if (_stack_depth == 0)
	{ // call stack is empty
		_stack[_stack_depth].mem_addr = nvmmStackUbound - _stack[_stack_depth].ssize; // reserve space for caller stack frame in memory
		////printf(" \n _stack_depth].mem_addr :%u", (uint32_t )_stack[_stack_depth].mem_addr  );
	}
	else
	{ // call stack is not empty
		_stack[_stack_depth].mem_addr = _stack[_stack_depth-1].mem_addr - _stack[_stack_depth].ssize; // calculate the size of the caller stack frame
		////printf(" \n _stack[_stack_depth].mem_addr :%u",  (uint32_t )_stack[_stack_depth].mem_addr);
	}
	_stack[_stack_depth].status = 0; // update status of function stack to indicate it is in memory
	
	
	
	spm_to_mem(_stack[_stack_depth].spm_addr , _stack[_stack_depth]. mem_addr , _stack[_stack_depth].ssize , _stack_depth );
	
	
#ifdef ShowExecutionReport
	addone(stack2mem)
	if (_spm__used < min_sp)
	{
		setstat( min_sp , _spm__used);
		//		printf("N  _spm__3: %u  ,  _spm__1: %u , base: %u" ,(uint32_t) _spm__3 ,  (uint32_t)_spm__1,(uint32_t)_spm_stack_base );
		//		printf (" , depth: %u", ___depth);
		//		printf (" , call: %u", store_calls);
		//
		//		printf (" , new min : %u ", _spm__used) ;
		//		printf ("\n");
	}
	if (_spm__used > max_sp)
	{
		setstat( max_sp , _spm__used);
		//		printf("X  _spm__3: %u  ,  _spm__1: %u , base: %u" ,  (uint32_t) _spm__3,  (uint32_t)_spm__1,(uint32_t) _spm_stack_base );
		//		printf (" , depth: %u", ___depth);
		//
		//		printf (" , call: %u", store_calls);
		//		printf (" , new max : %u ", _spm__used) ;
		//		printf ("\n");
	}
	
#endif
	
	
	
	
	_stack_depth++; // increase stack depth counter
	
	//_spm__2 = _spm_end ; // (&(new_spm_stack_2[___depth][sss - 1]));
	
}

// ensure the caller stack frame is in SPM
StaticCode void
_sload() {
	//__dummy_fflushStdout(" in _sload");
	////printf(" \n  sload  "  );
	////printf(" \n   _stack_depth  :%u",  (uint32_t ) _stack_depth);
	
	// bring back caller stack frame from memory to SPM
	
	_stack_depth--; // decrease stack depth counter
	currentstackPtr = _stack[_stack_depth].spm_addr ;
	
	
	mem_to_spm (_stack[_stack_depth].spm_addr , _stack[_stack_depth].mem_addr , _stack[_stack_depth].ssize , _stack_depth);
	

	addone(mem2stack)
	
	////printf ("\n end load _spm_1 %u \n", (uint32_t)_spm__1 ); fflush (stdout) ;
	
}


//// pointer threats resolution
//char * get_new_buff (char * laddr, uint32_t DataTypeSize ,uint32_t _stack_depth)
//{
//	//__dummy_fflushStdout(" in get_new_buff");
//	//printf (" .10_%u,%u,%u", (uint32_t)laddr , (uint32_t)DataTypeSize , (uint32_t)_stack_depth ) ; fflush(stdout);
//	int ix ;
//	for ( ix  = 0 ; ix < BUFF_SIZE ; ix ++)
//	{
//		//printf (" .11_") ; fflush(stdout);
//		if ( bufflist[ix].inuse  == 0 )
//		{
//			//printf (" .12_") ; fflush(stdout);
//			//printf (" .12_%u_" ,(uint32_t) bufflist[ix].ptr ) ; fflush(stdout);
//			_memcpy (bufflist[ix].ptr , laddr , DataTypeSize );
//			//printf (" .13_") ; fflush(stdout);
//			bufflist[ix].laddr = laddr;
//			bufflist[ix]._stack_depth = _stack_depth ;
//			bufflist[ix].inuse = 1 ;
//			bufflist[ix].DataTypeSize = DataTypeSize ;
//			return bufflist[ix].ptr ;
//		}
//		
//	}
//	
//	_fprintf (_debugf, "\n\tNeed more Buffer");
//	
//	return 0;
//	
//}

//char * _l2g(char *laddr , uint32_t DataTypeSize , uint32_t TypeKnown , uint32_t _stack_depth )
//{
//	//__dummy_fflushStdout(" in _l2g");
//	//printf("\n l2g : laddr : %u" , (uint32_t)laddr); fflush(stdout);
//	
//	char * gaddr = laddr; // set return value to the passed in address by default
//	
//	char * sp = _spm__1 ;
//	
//	//printf(" sp :%u",  (uint32_t ) sp);fflush(stdout);
//	
//	//printf(" _stack_depth  :%u",  (uint32_t )_stack_depth );fflush(stdout);
//	
//	// calculate the offset from the beginning of the current stack frame to the address
//	
//	
//	//__dummy__showAddr((char *)  _spm_end);
//	//__dummy__showAddr((char *)  laddr);
//	//__dummy__showAddr((char *)  sp);
//	
//	
//	if ( laddr >= sp && laddr < _spm_end)
//	{
//		
//		if (TypeKnown == 1)
//		{
//			//printf ("\n\t l2g : Type known , size : %u",DataTypeSize);fflush(stdout);
//			
//			//__dummy_fflushStdout(" at 1.1");
//			
//			if (_stack_depth == 0)
//			{
//				if (laddr >= sp && laddr < _spm_end    )
//				{
//					//__dummy_fflushStdout(" at 1.0");
//					// get new buff
//					//printf (" .1_") ; fflush(stdout);
//					gaddr = get_new_buff (laddr, DataTypeSize , _stack_depth);
//					//printf (" .200_") ; fflush(stdout);
//					
//					//gaddr = _mem_stack_end - (_spm_end - laddr);
//					//printf("  gaddr  1:%u",  (uint32_t ) gaddr);fflush(stdout);
//				}
//				else
//				{
//					//__dummy_fflushStdout(" not spm addr ");
//					//printf ( " not spm addr");fflush(stdout);
//				}
//			}
//			else
//			{
//				if (laddr >= sp && laddr < _spm_end  )
//				{
//					
//					//__dummy_fflushStdout(" at 1.2");
//					
//					gaddr = get_new_buff (laddr, DataTypeSize , _stack_depth) ;
//					
//					//gaddr = _stack[_stack_depth-1].mem_addr - (_spm_end - laddr);
//					//printf(" \n gaddr   2:%u",  (uint32_t )gaddr );fflush(stdout);
//				}
//				else
//				{
//					//printf (" not spm addr");fflush(stdout);
//				}
//			}
//			
//		}
//		
//		else
//		{
//			//__dummy_fflushStdout(" at 1.4");
//			//printf ("\n\t l2g : Type unknown ");fflush(stdout);
//		}
//	}
//	else
//	{
//		_debug(" at 1.5");
//		//printf ( " not spm addr ");fflush(stdout);
//	}
//	
//	//printf(" , rtn gaddr :%u",  (uint32_t )gaddr );fflush(stdout);
//	//__dummy_fflushStdout(" at exit");
//	//__dummy__showAddr(gaddr);
//	
//	return gaddr;
//}


// Address Translation from memory to spm address
char * AddressTrans_mem2spm(char * memAddr , int  InstructionType)
{
//#ifdef SHOW_EXECUTION_REPORT
//	access_calls ++;
//#endif
//	
//	//__dummy_fflushStdout(" in ADT");
//	
//	if ( memAddr >= _spm_begin && memAddr <= _spm_end)
//	{
//#ifdef SHOW_EXECUTION_REPORT
//		spm_stack_access++;
//#endif
//		
//	}
//	else if ( memAddr >= _mem_stack_begin && memAddr <= _mem_stack_end)
//	{
//#ifdef SHOW_EXECUTION_REPORT
//		mem_stack_access++;
//#endif
//		
//	}
//	else
//	{
//#ifdef SHOW_EXECUTION_REPORT
//		not_stack_access ++;
//#endif
//		
//	}
//	
	return memAddr ;
}

#ifndef WITH_ENC_DEC
unsigned int spm_to_mem (char *  spmAddr , char *  memAddr  , unsigned int ssize , int  _stack_depth)
{
	addstat(MemUpdate,ssize) 
	
#ifdef ShowBitFlips
	int ix,ixx ;  uint8_t diff; uint32_t bit_flips = 0;
	for (ix = 0 ; ix < ssize ; ix ++)
	{
		diff = spmAddr[ix] ^  memAddr[ix] ;
		
		for(ixx = 0; ixx < 8; ixx++)
		{
			bit_flips += (diff >> ixx) & 1;
		}
	}
	
	addstat(stackbit_flips,bit_flips) ;
	
#endif
	
	// copy spm to NVM
	unsigned int copyCount ;
	dmaNvmm2SpmNonAlign (  memAddr , spmAddr   , ssize ,copyCount );
	
	return copyCount ;
}
unsigned int mem_to_spm (char * spmAddr, char * memAddr, unsigned int ssize  , int _stack_depth)
{
	unsigned int copyCount ;
	dmaNvmm2SpmNonAlign( spmAddr  , memAddr   , ssize, copyCount);
	
	
//	// restore l2g buff
//	int ix ;
//	for ( ix  = 0 ; ix < BUFF_SIZE ; ix ++)
//	{
//		if ( bufflist[ix].inuse  == 1 && bufflist[ix]._stack_depth == _stack_depth)
//		{
//			__memcpy ( bufflist[ix].laddr , bufflist[ix].ptr , bufflist[ix].DataTypeSize);
//			bufflist[ix].inuse = 0 ;
//			bufflist[ix].laddr = 0 ;
//			bufflist[ix]._stack_depth = 0 ;
//			bufflist[ix].DataTypeSize = 0;
//		}
//	}
	
	return copyCount;
}
#endif



InitCode int
stackMgtInit(void){
	
	_debug  ( "\n stack init "   )
	
	// Set managed stack spaces
	spmStackLbound = spmStackSection  ;
	spmStackUbound = &spmStackSection[sizeof(spmStackSection)-1];
 
	nvmmStackLbound  = nvmmMalloc(nvmmStackSize);
	nvmmStackUbound  = nvmmStackLbound + nvmmStackSize ;
	
	//(char *) (&(nvmmStackSize[ 0 ]));
	//_mem_stack_end  = (char *) (&(new_mem_stack[ _mem_stack_space_size - 1 ]));
	
//	// initialize buffer for pointer threats resolution
//	int ix ;
//	for (ix = 0 ; ix < BUFF_SIZE ; ix ++)
//	{
//		bufflist[ix].inuse = 0 ;
//		bufflist[ix].laddr = 0 ;
//		bufflist[ix].ptr = (char *)(&(bufflist[ix].buff[0])) ;
//		bufflist[ix]._stack_depth = 0 ;
//		bufflist[ix].DataTypeSize = 0;
//	}
//	
	//_fprintf(_debugf , "\n --stack init 3--"   ) ;
	//_fflush(_debugf);
	
	
	
#ifdef WITH_ENC_DEC
	initStackMgtEncDec();
#endif
	
#ifdef ShowExecutionReport
	fprintf( _reportFile ,"\n Stack Area \n    SPM: { 0x%p ~~ 0x%p [%u] }, \n    NVMM: { 0x%p ~~ 0x%p [%u]} \n",
			 spmStackLbound, spmStackUbound,(uint32_t)(spmStackUbound - spmStackLbound),
			 nvmmStackLbound, nvmmStackUbound, (uint32_t)(nvmmStackUbound - nvmmStackLbound));
	fflush(_reportFile);
	
	char buf[512];
	snprintf(buf , sizeof(buf), "%u" ,(uint32_t)(spmStackUbound - spmStackLbound) );
	strcat(csvStr2,buf);
	
#endif
	_debug( "\n stack init end "   ) ;
	
	return 0;
}

InitCode int
stackMgtEnd(void){
	
	_report("\n\n Stack Management") 
	printstat(stack2mem)
	printstat(mem2stack)
	printstat(MemUpdate)
	printstat(stackbit_flips) 
	printstat(min_sp)
	printstat(max_sp)
	
	return 0;
}







