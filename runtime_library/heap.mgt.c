//============================== RTlob.c ===================================//
//																			//
//						Scratch Pad Management with Enc/Dec					//
//																			//
//              Developed by System Design Methodology Laboratory			//
//                   Hanyang University, Seoul, South Korea					//
//																			//
//							By: Thomas Haywood Dadzie						//
//																			//
//==========================================================================//


/*
 Re design malloc to include :
	- memory breaks at multiples pf blk size
	- encypt new blocks
	- find and use a better Management scheme
 */

//#define VICTIMBUFFERSIZE 16
//#define BLKSIZE 1024
//#define ASSOC 4
//#define spmHeapSize  65536



#include "common.h"

#include <wchar.h>
#include <string.h>
#include <math.h>
//#include <locale.h>

//#include "RTlib.h"

enum TRANSDIR {SPM2MEM, MEM2SPM};
enum cache_line_state {INVALID =1, VALID = 2, DIRTY = 4};
#define LOAD 1
#define STORE 2

typedef struct _blk_t blk_t;
typedef struct _set_t set_t;
typedef struct _cache_t cache_t;

struct _blk_t
{
	int status;
	unsigned long tag;
	char *data;
	char * mem_blk_addr ;
	int set_index;
	int index ;
};

struct _set_t
{
	blk_t *blks;
	unsigned long victim_counter;
};

struct _cache_t
{
	unsigned long assoc;
	unsigned long blk_size;
	unsigned long num_sets;
	unsigned long num_blks;
	unsigned long tag_len;
	unsigned long idx_len;
	unsigned long blk_ofs_len;
	set_t * sets;
};

char GV_hcache_metadata_sets[1048576];
char * GV_hcache_metadata_sets_end ;
char * GV_blks_startAddr  ;
cache_t _hcache;

char * InitHeapAddr ;
char * first_mem_blk;
char * last_mem_blk;
uint32_t mem_blks_allocated ;

blk_t victim_buffer_blks[VictimBuffSize / BlockSize ];
//char victim_buffer [VICTIMBUFFERSIZE][BlockSize];
const unsigned int victimBlks = VictimBuffSize / BlockSize ;
unsigned int nextVictimBlk = 0; // index of next blk to evict from victim buffer

char spmHeapBlocks[(spmHeapSize + VictimBuffSize) / BlockSize ][BlockSize + 4];


#ifdef ShowSpmDebugMsg
static inline uint32_t GET_MEM_BLK_INDEX(char * a, char * b)
{
	uint32_t m , f ;
	m = (PTRCAST)a ;
	f = (PTRCAST) b ;
	//printf ("\nmem : %u , fmem %u, diff : %u , cc : %u" ,(PTRCAST)m , f , (m-f), (m-f)/BLKSIZE ) ;
	fflush(stdout);
	
	return (m  - f)/ BlockSize ;
}
#else
#define GET_MEM_BLK_INDEX(a,b) (a - b)/ BLKSIZE
//#define GET_MEM_BLK_INDEX(a,b) (((uint32_t)(((((float)((PTRCAST)a))) - (((float)((PTRCAST)b))))/ ((float)BLKSIZE) )));
#endif

#define Period(c)  (c/10)



static inline unsigned long next_power_of_2(unsigned long num)
{
	return (unsigned long)pow(2.0, ceil(log2((double)num)));
}
// return the tag of the given memory address
static inline unsigned long get_tag(unsigned long addr)
{
	return addr >> (_hcache.blk_ofs_len + _hcache.idx_len);
}
// return the set index of the given memory address
static inline unsigned long get_index(unsigned long addr)
{
	return addr << _hcache.tag_len >> (_hcache.tag_len + _hcache.blk_ofs_len);
}
// return the block offset of the given memory address
static inline unsigned long get_offset(unsigned long addr)
{
	unsigned len = _hcache.tag_len + _hcache.idx_len;
	return addr << len >> len;
}
//static inline
unsigned long get_blk_addr(unsigned long addr)
{
	return addr >> _hcache.blk_ofs_len << _hcache.blk_ofs_len;
}



InitCode void
heapMgtEnd(){
	
	_report("\n\n Heap Management");
	printstat(mallocCalls)
	printstat(freeCalls)
	
	printstat( addrTrans)
	printstat( Writes)
	printstat( not_heap_addr)
	printstat( in_heap_addr)
	printstat( hit)
	printstat( victim_buffer_hit)
	printstat( miss)
	printstat( Dirty)
	printstat( NotDirty)
	printstat( NotValid)
	printstat( Evictions)
	printstat( heapbit_flips)
	printstat( BlockFetch)
	printstat( MoveToVB)	
	
	printstat( DataOverFlows)
	
}



StaticCode int
fetch_ftn(char  *spmAddr_, char *memAddr_){
	
#ifdef ShowSpmDebugMsg
	uint32_t blk_ix = GET_MEM_BLK_INDEX(memAddr_,first_mem_blk);
	printf("\n fetch [blk:%u, spmblk(%u,%u), count:%u, period:%u, memAddr:%u spmAddr:%u ] ", \
		   blk_ix , 0, 0, 0, 0 , (PTRCAST)memAddr_, (PTRCAST)spmAddr_ ); fflush(stdout);
#endif
	
	addone(BlockFetch)
	
	memcpy ( spmAddr_  , memAddr_, BlockSize  +4 );
	return BlockSize;
}


StaticCode int
eviction_ftn(char  *spmAddr_, char *memAddr_ ){
	
	addone(Evictions)
	
#ifdef ShowSpmDebugMsg
	uint32_t blk_ix = GET_MEM_BLK_INDEX(memAddr_,first_mem_blk);
	printf("\n Eviction [blk:%u, spmblk(%u,%u), count:%u, period:%u, memAddr:%u spmAddr:%u ] ", \
		   blk_ix , 0, 0, 0, 0 , (PTRCAST)memAddr_, (PTRCAST)spmAddr_ ); fflush(stdout);
#endif
	
	
#ifdef ShowBitFlips
	int ix,ixx ; 
	uint8_t diff; uint32_t bit_flips =0;
	for (ix = 0 ; ix < BlockSize ; ix ++)
	{
		diff = memAddr_[ix] ^  spmAddr_[ix] ;
		for(ixx = 0; ixx < 8; ixx++)
		{
			bit_flips += (diff >> ixx) & 1;
		}
	}
	addstat(heapbit_flips,bit_flips)
#endif
	
	memcpy ( memAddr_  , spmAddr_ , BlockSize +4);
	return BlockSize;	
}




InitCode void
heapMgtInit(void){
	
	unsigned long capacity = spmHeapSize;
	unsigned long assoc = Assoc ;
	unsigned long blk_size = BlockSize ;
	unsigned long i, j = 0;
	unsigned long assoc_len;
	char *_hcache_metadata_sets, *_hcache_metadata_blks, *_hcache_data;
	
	// set up the cache semantics
	_hcache.assoc = next_power_of_2(assoc);
	_hcache.blk_size = next_power_of_2(blk_size);
	_hcache.num_blks = next_power_of_2(capacity) / blk_size;
	_hcache.num_sets = _hcache.num_blks / _hcache.assoc;
	
	_hcache.blk_ofs_len = (unsigned long)log2(_hcache.blk_size);
	_hcache.idx_len = (unsigned long)log2(_hcache.num_sets);
	_hcache.tag_len = sizeof(char *) * 8 - _hcache.idx_len - _hcache.blk_ofs_len;
	
	//_hcache_metadata_sets = (char *)&_hcache + next_power_of_2(sizeof(cache_t));
	_hcache_metadata_sets = (char *)&GV_hcache_metadata_sets + next_power_of_2(sizeof(cache_t));
	_hcache_metadata_blks = _hcache_metadata_sets + next_power_of_2(_hcache.num_sets * sizeof(set_t));
	_hcache_data = _hcache_metadata_blks + next_power_of_2(_hcache.num_blks * sizeof(blk_t));
	assoc_len = (unsigned long)log2(_hcache.assoc);
	
	GV_hcache_metadata_sets_end  = &GV_hcache_metadata_sets[1048576 - 1  ];
	GV_blks_startAddr = _hcache_data ;
	
 
	_hcache.sets = (set_t *)_hcache_metadata_sets;
	
	char * last_spm_blk_addr = 0;
	
	unsigned int getblkindex = 0;
	
	for (i = 0; i < _hcache.num_sets; ++i)
	{
		_hcache.sets[i].blks = (blk_t *)(_hcache_metadata_blks + (i << assoc_len) * sizeof(blk_t));
		//printf("\t_hcache.sets[%ju].blks=0x%lx\n", i, (unsigned long)_hcache.sets[i].blks);
		for (j = 0; j < _hcache.assoc; ++j) {
			
			_hcache.sets[i].blks[j].status = INVALID;
			_hcache.sets[i].blks[j].tag = 0;
			_hcache.sets[i].blks[j].set_index = i ;
			_hcache.sets[i].blks[j].index = j ;
			_hcache.sets[i].blks[j].data = &spmHeapBlocks[getblkindex++][0] ;//_hcache_data + (((i << assoc_len) + j) << _hcache.blk_ofs_len);
			last_spm_blk_addr = _hcache.sets[i].blks[j].data ;
		}
	}
	
	
	//memset ( &(victim_buffer[0][0]), 0, BlockSize * VICTIMBUFFERSIZE);
	for (i = 0 ; i < victimBlks ; i++)
	{
		victim_buffer_blks[i].tag = 0 ;
		victim_buffer_blks[i].mem_blk_addr = 0 ;
		victim_buffer_blks[i].status = INVALID ;
		victim_buffer_blks[i].data = &spmHeapBlocks[getblkindex++][0] ;//&( victim_buffer[i][0]) ;
		//printf ("VB:%ju,%d " ,i, (PTRCAST)(victim_buffer_blks[i].data));
	}
	
	
	
#ifdef ShowExecutionReport
	fprintf(_reportFile,"\n Heap Area \n    SPM: { 0x%p ~~ 0x%p [%u] }\n",
			&GV_hcache_metadata_sets[0], &GV_hcache_metadata_sets[sizeof(GV_hcache_metadata_sets) - 1],
			(uint32_t)(sizeof (GV_hcache_metadata_sets)));
	fflush(_reportFile);
	
	fprintf(_reportFile,
			"         { capacity = %ld , blk_size = %ld } \
			\n         { assoc = %ld , num_sets = %ld , num_blks = %ld , victim_blks= %u }\
			\n         { tag_len = %ld , idx_len = %ld , blk_ofs_len = %ld } \
			\n         { GV_blks_startAddr = %u , GV_hcache_metadata_sets_end = %u  last_spm_blk_addr = %u } ",
			next_power_of_2(capacity),	_hcache. blk_size,
			_hcache.assoc,
			_hcache.num_sets,
			_hcache.num_blks, victimBlks ,
			_hcache. tag_len,
			_hcache.idx_len,
			_hcache.blk_ofs_len,
			(PTRCAST)GV_blks_startAddr,
			(PTRCAST)GV_hcache_metadata_sets_end,
			(PTRCAST)last_spm_blk_addr
			) ;
	fflush(_reportFile);
	
	char buf[512];
	snprintf(buf , sizeof(buf), "%ld,%ld,%ld,%ld,%ld" ,
			 next_power_of_2(capacity),
			 _hcache. blk_size,
			 _hcache.assoc,
			 _hcache.num_sets,
			 _hcache.num_blks);
	strcat(csvStr1,buf);
	
#endif
	
	init_spm_malloc();
	
}



StaticCode unsigned int *
addrTranslation (unsigned int *gaddr__, unsigned int opcode , unsigned int dataSize ){ //type , int datasize){
	
	//_debug2 ("\n addrTranslation { 0x%p , %d }" , gaddr__ , opcode);
	
	
	addone( addrTrans)
	
	char * gaddr = (char *)gaddr__ ;
	
	unsigned long i;
	unsigned long addr, tag, idx, offset;
	unsigned long victim_counter;
	char *sp;
	char *laddr;
	blk_t *blk = NULL;
	set_t *set;
	
	if(!isHeapAddr(gaddr))
	{
		addone( not_heap_addr)
		return gaddr__;
		
	}
	
	
	addone( in_heap_addr)
	
	addr = (unsigned long)gaddr;
	tag = get_tag(addr);
	idx = get_index(addr);
	offset = get_offset(addr);
	
	// Get the set
	set = &_hcache.sets[idx];
	victim_counter = set->victim_counter;
	
	char *mem_blk_addr;
	mem_blk_addr = (char *)get_blk_addr(addr);
	
	// Look for the required memory block in the set
	for (i = 0; i < _hcache.assoc; ++i)
	{
		if (set->blks[i].tag == tag)
		{
			//printf("\ncache hit");
			addone( hit)
			
			blk = &set->blks[i];
			break;
		}
	}
	
	
	if (!blk) // Cache miss ,find in victim buffer
	{
		for (i = 0 ; i < VictimBuffSize ; i ++)
		{
			if (victim_buffer_blks[i].mem_blk_addr == mem_blk_addr)
			{
				//printf("\n victim buffer hit");
				addone( victim_buffer_hit);
				
				blk = &victim_buffer_blks[i] ;
				break;
			}
		}
	}
	
	
	if (!blk) // Cache miss and victim buffer miss, fetch from main memory
	{
		//printf("\ncache miss ");
		addone(miss)
		
		// evict victim buffer blk to main memory
		blk_t * evict_blk = &victim_buffer_blks[nextVictimBlk];
		if (evict_blk->status == DIRTY )
		{
			addone(Dirty)
			// evict existing victim buffer blk
			eviction_ftn (evict_blk->data, evict_blk->mem_blk_addr);
			
			
		}
		else if (evict_blk->status == VALID)
		{
			addone(NotDirty)
		}
		else if (evict_blk->status == INVALID)
		{
			addone(NotValid)
		}
		
		
		blk = &set->blks[victim_counter];
		// copy from cache to victim buffer
		//if (blk->status == VALID || blk->status == DIRTY)
		if (blk->status != INVALID)
		{
			memcpy(evict_blk->data , blk->data,BlockSize);
			evict_blk->status = blk->status;
			evict_blk->mem_blk_addr = blk->mem_blk_addr;
			evict_blk->tag = blk->tag;
			
			addone(MoveToVB)
			
			nextVictimBlk = (nextVictimBlk +1) %  victimBlks ;
		}
		
		
		
		//fprintf(stderr, ",%d", victim_buffer_evict);
		
		// copy from main memory to cache
		blk->tag = tag;
		blk->mem_blk_addr = mem_blk_addr;
		
		fetch_ftn(blk->data, mem_blk_addr);
		
		
		//addone( dma_MEM2SPM)
		
		blk->status = VALID;
		set->victim_counter = (victim_counter+1) % _hcache.assoc;
		
		
	}
	
	if (opcode == STORE)
	{blk->status = DIRTY ; addone(Writes) }
	
	  char  * rtnptr = blk->data + offset ;
	  char * p = rtnptr + dataSize; 
	  char * bEnd =blk->data + BlockSize ;
	
	if (p > bEnd )
	{
		_report5("\n %p , %d , %p , %p , overflow:%u" , rtnptr , dataSize , bEnd, p , (p - bEnd) )
		addone(DataOverFlows)
	}

	return (unsigned int *)rtnptr;
	
//	return (unsigned int *)(blk->data + offset);
	
}



