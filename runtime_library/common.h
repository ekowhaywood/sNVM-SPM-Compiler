
#include <string.h>
#include <stddef.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdarg.h>

#ifdef WITH_ENC_DEC
#include "enc_lib/sodium.h"
#include "enc_lib/aes.h"
#endif

#define getSP(sp) { __asm __volatile("mov %[result], r13 " : [result] "=r" (sp) );}
#define putSP(sp) { __asm __volatile("mov r13 , %[result] " : :[result] "r" (sp ) ); }

#define StaticCode __attribute__((section("sec_staticCode")))
#define StaticData __attribute__((section("sec_staticData")))
#define InitCode __attribute__ ((section("sec_mgtCode_0")))

#define KB * 1024
#define MB * 1048576
#define PTRCAST uint32_t


//int dmaNvmm2Spm (unsigned int * dst, unsigned int * src, size_t cc)
#define dmaNvmm2SpmNonAlign(dstAddr, srcAddr, count , copied)  {\
int ix ; \
char * dst = (char  *)dstAddr ; \
char * src = (char  *)srcAddr ; \
size_t cc = count ; \
for (ix=0; ix<cc; ix++){ dst[ix] = src[ix]; } \
copied = ix ; \
}


extern int main(int argc , char ** argv);
extern char * nvmmMalloc(size_t size);

extern char * systemStackPtr ;
extern char * spmStackUbound ;
extern  int  stackMgtInit(void);
extern  int  stackMgtEnd(void);

extern char *codeMgtInit(void);
extern int  codeMgtEnd  (void);
extern char *getMgtCode (unsigned int);

extern void heapMgtInit(void);
extern void heapMgtEnd(void);
extern void init_spm_malloc();
extern int isHeapAddr(char * gAddr);
// get the block address of the given memory address
//static inline unsigned long get_blk_addr(unsigned long addr);
extern unsigned long get_blk_addr(unsigned long addr);



// report printing declarations

#ifdef ShowExecutionReport

typedef struct StatsCounter {uint32_t high ; uint32_t low; uint32_t showInCsv ; char desc [256] ;} StatsC;
#define _statColumn1 15
#define _statColumn2 32
extern FILE * _reportFile ;
extern char csvStr[4096];
extern char csvStr1[4096];
extern char csvStr2[4096];
extern char csvStr3[4096];
extern void InitStatsFile();
extern void printStatistics( StatsC * stat , const char * vname );
extern __attribute__ ((always_inline)) void Increament(StatsC *var) ;
extern __attribute__ ((always_inline)) void  IncreamentBy(StatsC *var , uint32_t value);

#define InitStats() InitStatsFile()
#define decStats(var,desc) __attribute__ ((weak)) StatsC var ## _Stats = {0x00000000,0x00000000, 1, desc } 
#define decStats2(var,desc) __attribute__ ((weak)) StatsC var ## _Stats = {0x00000000,0x00000000, 0, desc } 

#define addone(var)  Increament(& var ## _Stats ) ;
#define addstat(var , value) IncreamentBy(& var ## _Stats , value) ;
#define setstat(var,value) {var ## _Stats .low = value ;}
#define printstat(var) printStatistics ( & var ## _Stats , #var ) ;

#define _report(format)		fprintf (_reportFile , format ) ;  fflush( _reportFile );
#define _report1(format,a)		fprintf (_reportFile , format , a ) ;  fflush( _reportFile );
#define _report2(format,a,b)	fprintf (_reportFile , format , a ,b ) ; fflush( _reportFile );
#define _report3(format,a,b,c)	fprintf (_reportFile , format , a ,b ,c) ; fflush( _reportFile );
#define _report4(format,a,b,c,d)	fprintf (_reportFile , format , a ,b ,c,d) ; fflush( _reportFile );
#define _report5(format,a,b,c,d,e)	fprintf (_reportFile , format , a ,b,c,d,e ) ; fflush( _reportFile );

// heap allocation
decStats(mallocCalls, "No of calls to Malloc");
decStats(freeCalls, "No. of calls to Free") ;

// heap mgt
decStats(addrTrans, "No. of address translation attempts");
decStats(not_heap_addr, "No. of addresses not located in heap allocations");
decStats(in_heap_addr, "No. of addresses located in heap allocations, requiring translation");
decStats(miss, "No. of miss in spm heap mgt, causes eviction and fetch") ;
decStats(hit , "");
decStats(victim_buffer_hit, "");
decStats(BlockFetch, "") ;
decStats(Evictions, "") ;
decStats(Dirty, "");
decStats2(NotDirty,"");
decStats2(NotValid,"");
decStats(heapbit_flips , "");
decStats2(Writes ,"");
decStats2( MoveToVB ,"");

decStats2( DataOverFlows,"");

//stack mgt
decStats(stack2mem , "No. of times whole stack in SPM is dumped to NVMM") ;
decStats(mem2stack , "No. of times saved stack data is restored back to SPM") ;
decStats(MemUpdate,"Total bytes written to NVMM");
decStats2(min_sp ,"Min. size of whole stack dumped to NVMM");
decStats2(max_sp , "Max. size of whole stack dumped to NVMM");
decStats(stackbit_flips , "");

//code mgt
decStats(CodeFetch,"No. of times code is fetched from NVMM to SPM" ) ;
decStats(InstCount , "No. of Instructions read from NVMM to SPM");

#else
#define InitStats() {}
#define addone(var) {}
#define addstat(var , value) {}
#define setstat(var,value) {}
#define printstat(var) {}
#define _report(format)		{}
#define _report1(format,a)		{}
#define _report2(format,a,b)	{}
#define _report3(format,a,b,c)	{} 
#define _report4(format,a,b,c,d)	{}
#define _report5(format,a,b,c,d,e) {}

#endif


#ifdef ShowSpmDebugMsg
#include <time.h>
extern FILE * _debugFILE ;
#define _debugf _debugFILE
#define _debug(format)		fprintf (_debugFILE , format ) ;  fflush( _debugFILE );
#define _debug1(format,a)		fprintf (_debugFILE , format , a ) ;  fflush( _debugFILE );
#define _debug2(format,a,b)	fprintf (_debugFILE , format , a ,b ) ; fflush( _debugFILE );
#define _debug3(format,a,b,c)	fprintf (_debugFILE , format , a ,b ,c) ; fflush( _debugFILE );
#define _debug4(format,a,b,c,d)	fprintf (_debugFILE , format , a ,b ,c,d) ; fflush( _debugFILE );
#define _debug5(format,a,b,c,d,e)	fprintf (_debugFILE , format , a ,b,c,d,e ) ; fflush( _debugFILE );
#else
#define _debug(format)		{}
#define _debug1(format,a)		{}
#define _debug2(format,a,b)	{}
#define _debug3(format,a,b,c)	{}
#define _debug4(format,a,b,c,d)	{}
#define _debug5(format,a,b,c,d,e){}
#endif




