; ModuleID = '../../runtime_library/RuntimeLibrary.bc'
target datalayout = "e-m:e-p:32:32-i64:64-v128:64:128-a:0:32-n32-S64"
target triple = "armv5--linux-gnueabi"

%struct.StatsCounter = type { i32, i32, i32, [256 x i8] }
%struct._Region = type { i32 }
%struct.Mgt_code_meta = type { i32, i8*, i8*, i32, i32, i32, %struct._Region*, i8* }
%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i32, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i32, i32, [40 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.STACK_ENTRY = type { i8*, i8*, i32, i32 }
%struct._cache_t = type { i32, i32, i32, i32, i32, i32, i32, %struct._set_t* }
%struct._set_t = type { %struct._blk_t*, i32 }
%struct._blk_t = type { i32, i32, i8*, i8*, i32, i32 }

@mallocCalls_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 1, [256 x i8] c"No of calls to Malloc\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@freeCalls_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 1, [256 x i8] c"No. of calls to Free\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@addrTrans_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 1, [256 x i8] c"No. of address translation attempts\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@not_heap_addr_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 1, [256 x i8] c"No. of addresses not located in heap allocations\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@in_heap_addr_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 1, [256 x i8] c"No. of addresses located in heap allocations, requiring translation\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@miss_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 1, [256 x i8] c"No. of miss in spm heap mgt, causes eviction and fetch\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@hit_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 1, [256 x i8] zeroinitializer }, align 4
@victim_buffer_hit_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 1, [256 x i8] zeroinitializer }, align 4
@BlockFetch_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 1, [256 x i8] zeroinitializer }, align 4
@Evictions_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 1, [256 x i8] zeroinitializer }, align 4
@Dirty_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 1, [256 x i8] zeroinitializer }, align 4
@NotDirty_Stats = weak global %struct.StatsCounter zeroinitializer, align 4
@NotValid_Stats = weak global %struct.StatsCounter zeroinitializer, align 4
@heapbit_flips_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 1, [256 x i8] zeroinitializer }, align 4
@Writes_Stats = weak global %struct.StatsCounter zeroinitializer, align 4
@MoveToVB_Stats = weak global %struct.StatsCounter zeroinitializer, align 4
@DataOverFlows_Stats = weak global %struct.StatsCounter zeroinitializer, align 4
@stack2mem_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 1, [256 x i8] c"No. of times whole stack in SPM is dumped to NVMM\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@mem2stack_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 1, [256 x i8] c"No. of times saved stack data is restored back to SPM\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@MemUpdate_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 1, [256 x i8] c"Total bytes written to NVMM\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@min_sp_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 0, [256 x i8] c"Min. size of whole stack dumped to NVMM\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@max_sp_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 0, [256 x i8] c"Max. size of whole stack dumped to NVMM\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@stackbit_flips_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 1, [256 x i8] zeroinitializer }, align 4
@CodeFetch_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 1, [256 x i8] c"No. of times code is fetched from NVMM to SPM\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@InstCount_Stats = weak global %struct.StatsCounter { i32 0, i32 0, i32 1, [256 x i8] c"No. of Instructions read from NVMM to SPM\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@mapping_table_size = global i32 0, align 4
@region_table_size = global i32 0, align 4
@.str = private unnamed_addr constant [5 x i8] c"main\00", align 1
@__load_start_sec_mgtCode_1 = external global i8*
@__load_stop_sec_mgtCode_1 = external global i8*
@.str1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str2 = private unnamed_addr constant [19 x i8] c"\0A\0A Code Managment \00", align 1
@.str3 = private unnamed_addr constant [10 x i8] c"CodeFetch\00", align 1
@.str4 = private unnamed_addr constant [10 x i8] c"InstCount\00", align 1
@_region_table = common global [10 x %struct._Region] zeroinitializer, align 4
@mgtCodeMeta = global [50 x %struct.Mgt_code_meta] zeroinitializer, section "sec_staticData", align 4
@Mgt_code_meta = common global %struct.Mgt_code_meta zeroinitializer, align 4
@nvmmMallocNextPtr = global i32 0, section "sec_staticData", align 4
@main_argc = common global i32 0, align 4
@main_argv = common global i8** null, align 4
@nvmm_region = global i8* null, section "sec_staticData", align 4
@.str5 = private unnamed_addr constant [24 x i8] c"Can't allocate memory \0A\00", align 1
@_reportFile = common global %struct._IO_FILE* null, align 4
@.str18 = private unnamed_addr constant [25 x i8] c"\0A\0A---Begin execution---\0A\00", align 1
@systemStackPtr = common global i8* null, align 4
@.str29 = private unnamed_addr constant [24 x i8] c"\0A---End of execution---\00", align 1
@csvStr = common global [4096 x i8] zeroinitializer, align 1
@csvStr1 = common global [4096 x i8] zeroinitializer, align 1
@.str310 = private unnamed_addr constant [2 x i8] c",\00", align 1
@.str411 = private unnamed_addr constant [3 x i8] c",,\00", align 1
@csvStr2 = common global [4096 x i8] zeroinitializer, align 1
@csvStr3 = common global [4096 x i8] zeroinitializer, align 1
@.str514 = private unnamed_addr constant [3 x i8] c"\0A\0A\00", align 1
@.str6 = private unnamed_addr constant [15 x i8] c"../reports.csv\00", align 1
@.str7 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@.str8 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@currentVargFrame = global i32* null, align 4
@VarArg = common global [1024 x i8] zeroinitializer, align 1
@.str9 = private unnamed_addr constant [13 x i8] c"adpcm.decode\00", align 1
@stderr = external global %struct._IO_FILE*
@.str10 = private unnamed_addr constant [7 x i8] c"%-120s\00", align 1
@.str11 = private unnamed_addr constant [21 x i8] c"%u  +(%u*0xffffffff)\00", align 1
@.str12 = private unnamed_addr constant [3 x i8] c"%u\00", align 1
@.str13 = private unnamed_addr constant [7 x i8] c"%-100s\00", align 1
@.str14 = private unnamed_addr constant [22 x i8] c"\0A    %-.*s :%-.*s %s \00", align 1
@spmStackBase = common global i8* null, align 4
@main_rtn = common global i32 0, align 4
@spm2mem = global i32 0, align 4
@mem2spm = global i32 0, align 4
@max_sp = global i32 0, align 4
@min_sp = global i32 200000000, align 4
@spm_stack_access = global i32 0, align 4
@mem_stack_access = global i32 0, align 4
@not_stack_access = global i32 0, align 4
@access_calls = global i32 0, align 4
@totalMemUpdate = global i32 0, align 4
@_stack_depth = global i32 0, align 4
@currentstackPtr = global i8* null, section "sec_staticData", align 4
@_stack = common global [100 x %struct.STACK_ENTRY] zeroinitializer, align 4
@spmStackUbound = global i8* null, section "sec_staticData", align 4
@nvmmStackUbound = global i8* null, section "sec_staticData", align 4
@spmStackSection = common global [32768 x i8] zeroinitializer, align 1
@spmStackLbound = global i8* null, section "sec_staticData", align 4
@nvmmStackLbound = global i8* null, section "sec_staticData", align 4
@.str25 = private unnamed_addr constant [80 x i8] c"\0A Stack Area \0A    SPM: { 0x%p ~~ 0x%p [%u] }, \0A    NVMM: { 0x%p ~~ 0x%p [%u]} \0A\00", align 1
@.str126 = private unnamed_addr constant [3 x i8] c"%u\00", align 1
@.str227 = private unnamed_addr constant [20 x i8] c"\0A\0A Stack Management\00", align 1
@.str328 = private unnamed_addr constant [10 x i8] c"stack2mem\00", align 1
@.str429 = private unnamed_addr constant [10 x i8] c"mem2stack\00", align 1
@.str530 = private unnamed_addr constant [10 x i8] c"MemUpdate\00", align 1
@.str631 = private unnamed_addr constant [15 x i8] c"stackbit_flips\00", align 1
@.str732 = private unnamed_addr constant [7 x i8] c"min_sp\00", align 1
@.str833 = private unnamed_addr constant [7 x i8] c"max_sp\00", align 1
@victimBlks = constant i32 4, align 4
@nextVictimBlk = global i32 0, align 4
@_hcache = common global %struct._cache_t zeroinitializer, align 4
@.str38 = private unnamed_addr constant [19 x i8] c"\0A\0A Heap Management\00", align 1
@.str139 = private unnamed_addr constant [12 x i8] c"mallocCalls\00", align 1
@.str240 = private unnamed_addr constant [10 x i8] c"freeCalls\00", align 1
@.str341 = private unnamed_addr constant [10 x i8] c"addrTrans\00", align 1
@.str442 = private unnamed_addr constant [7 x i8] c"Writes\00", align 1
@.str543 = private unnamed_addr constant [14 x i8] c"not_heap_addr\00", align 1
@.str644 = private unnamed_addr constant [13 x i8] c"in_heap_addr\00", align 1
@.str745 = private unnamed_addr constant [4 x i8] c"hit\00", align 1
@.str846 = private unnamed_addr constant [18 x i8] c"victim_buffer_hit\00", align 1
@.str947 = private unnamed_addr constant [5 x i8] c"miss\00", align 1
@.str1048 = private unnamed_addr constant [6 x i8] c"Dirty\00", align 1
@.str1149 = private unnamed_addr constant [9 x i8] c"NotDirty\00", align 1
@.str1250 = private unnamed_addr constant [9 x i8] c"NotValid\00", align 1
@.str1351 = private unnamed_addr constant [10 x i8] c"Evictions\00", align 1
@.str1452 = private unnamed_addr constant [14 x i8] c"heapbit_flips\00", align 1
@.str15 = private unnamed_addr constant [11 x i8] c"BlockFetch\00", align 1
@.str16 = private unnamed_addr constant [9 x i8] c"MoveToVB\00", align 1
@.str17 = private unnamed_addr constant [14 x i8] c"DataOverFlows\00", align 1
@GV_hcache_metadata_sets = common global [1048576 x i8] zeroinitializer, align 1
@GV_hcache_metadata_sets_end = common global i8* null, align 4
@GV_blks_startAddr = common global i8* null, align 4
@spmHeapBlocks = common global [20 x [260 x i8]] zeroinitializer, align 1
@victim_buffer_blks = common global [4 x %struct._blk_t] zeroinitializer, align 4
@.str1853 = private unnamed_addr constant [45 x i8] c"\0A Heap Area \0A    SPM: { 0x%p ~~ 0x%p [%u] }\0A\00", align 1
@.str19 = private unnamed_addr constant [292 x i8] c"         { capacity = %ld , blk_size = %ld } \09\09\09\0A         { assoc = %ld , num_sets = %ld , num_blks = %ld , victim_blks= %u }\09\09\09\0A         { tag_len = %ld , idx_len = %ld , blk_ofs_len = %ld } \09\09\09\0A         { GV_blks_startAddr = %u , GV_hcache_metadata_sets_end = %u  last_spm_blk_addr = %u } \00", align 1
@.str20 = private unnamed_addr constant [20 x i8] c"%ld,%ld,%ld,%ld,%ld\00", align 1
@.str21 = private unnamed_addr constant [34 x i8] c"\0A %p , %d , %p , %p , overflow:%u\00", align 1
@InitHeapAddr = common global i8* null, align 4
@first_mem_blk = common global i8* null, align 4
@last_mem_blk = common global i8* null, align 4
@mem_blks_allocated = common global i32 0, align 4

; Function Attrs: nounwind
define i8* @codeMgtInit() #0 section "sec_mgtCode_0" {
entry:
  %buf = alloca [512 x i8], align 1
  call void @setMgtFuncMeta(i32 1, i8* getelementptr inbounds ([5 x i8]* @.str, i32 0, i32 0), i32 0, i32 ptrtoint (i32 (i32, i8**)* @main to i32), i32 ptrtoint (i8** @__load_start_sec_mgtCode_1 to i32), i32 sdiv exact (i32 sub (i32 ptrtoint (i8** @__load_stop_sec_mgtCode_1 to i32), i32 ptrtoint (i8** @__load_start_sec_mgtCode_1 to i32)), i32 4))
  %arraydecay = getelementptr inbounds [512 x i8]* %buf, i32 0, i32 0
  %0 = load i32* @region_table_size, align 4
  %call = call i32 (i8*, i32, i8*, ...)* @snprintf(i8* %arraydecay, i32 512, i8* getelementptr inbounds ([3 x i8]* @.str1, i32 0, i32 0), i32 %0) #4
  %arraydecay1 = getelementptr inbounds [512 x i8]* %buf, i32 0, i32 0
  %call2 = call i8* @strcat(i8* getelementptr inbounds ([4096 x i8]* @csvStr3, i32 0, i32 0), i8* %arraydecay1) #4
  ret i8* null
}

; Function Attrs: nounwind
define void @setMgtFuncMeta(i32 %func_idx, i8* %fname, i32 %Region, i32 %vma, i32 %lma, i32 %size) #0 section "sec_mgtCode_0" {
entry:
  %func_idx.addr = alloca i32, align 4
  %fname.addr = alloca i8*, align 4
  %Region.addr = alloca i32, align 4
  %vma.addr = alloca i32, align 4
  %lma.addr = alloca i32, align 4
  %size.addr = alloca i32, align 4
  %dst = alloca i32*, align 4
  %src = alloca i32*, align 4
  %cc = alloca i32, align 4
  %ix = alloca i32, align 4
  store i32 %func_idx, i32* %func_idx.addr, align 4
  store i8* %fname, i8** %fname.addr, align 4
  store i32 %Region, i32* %Region.addr, align 4
  store i32 %vma, i32* %vma.addr, align 4
  store i32 %lma, i32* %lma.addr, align 4
  store i32 %size, i32* %size.addr, align 4
  %0 = load i8** %fname.addr, align 4
  %1 = load i32* %func_idx.addr, align 4
  %arrayidx = getelementptr inbounds [50 x %struct.Mgt_code_meta]* @mgtCodeMeta, i32 0, i32 %1
  %name_string = getelementptr inbounds %struct.Mgt_code_meta* %arrayidx, i32 0, i32 7
  store i8* %0, i8** %name_string, align 4
  %2 = load i32* %Region.addr, align 4
  %3 = load i32* %func_idx.addr, align 4
  %arrayidx1 = getelementptr inbounds [50 x %struct.Mgt_code_meta]* @mgtCodeMeta, i32 0, i32 %3
  %idx_region = getelementptr inbounds %struct.Mgt_code_meta* %arrayidx1, i32 0, i32 5
  store i32 %2, i32* %idx_region, align 4
  %4 = load i32* %Region.addr, align 4
  %arrayidx2 = getelementptr inbounds [10 x %struct._Region]* @_region_table, i32 0, i32 %4
  %5 = load i32* %func_idx.addr, align 4
  %arrayidx3 = getelementptr inbounds [50 x %struct.Mgt_code_meta]* @mgtCodeMeta, i32 0, i32 %5
  %region = getelementptr inbounds %struct.Mgt_code_meta* %arrayidx3, i32 0, i32 6
  store %struct._Region* %arrayidx2, %struct._Region** %region, align 4
  %6 = load i32* %lma.addr, align 4
  %7 = inttoptr i32 %6 to i8*
  %8 = load i32* %func_idx.addr, align 4
  %arrayidx4 = getelementptr inbounds [50 x %struct.Mgt_code_meta]* @mgtCodeMeta, i32 0, i32 %8
  %nvm_addr = getelementptr inbounds %struct.Mgt_code_meta* %arrayidx4, i32 0, i32 2
  store i8* %7, i8** %nvm_addr, align 4
  %9 = load i32* %vma.addr, align 4
  %10 = inttoptr i32 %9 to i8*
  %11 = load i32* %func_idx.addr, align 4
  %arrayidx5 = getelementptr inbounds [50 x %struct.Mgt_code_meta]* @mgtCodeMeta, i32 0, i32 %11
  %spm_addr = getelementptr inbounds %struct.Mgt_code_meta* %arrayidx5, i32 0, i32 1
  store i8* %10, i8** %spm_addr, align 4
  %12 = load i32* %size.addr, align 4
  %div = udiv i32 %12, 4
  %13 = load i32* %func_idx.addr, align 4
  %arrayidx6 = getelementptr inbounds [50 x %struct.Mgt_code_meta]* @mgtCodeMeta, i32 0, i32 %13
  %instCount = getelementptr inbounds %struct.Mgt_code_meta* %arrayidx6, i32 0, i32 3
  store i32 %div, i32* %instCount, align 4
  %14 = load i32* %func_idx.addr, align 4
  %arrayidx7 = getelementptr inbounds [50 x %struct.Mgt_code_meta]* @mgtCodeMeta, i32 0, i32 %14
  %isEnc = getelementptr inbounds %struct.Mgt_code_meta* %arrayidx7, i32 0, i32 4
  store i32 1, i32* %isEnc, align 4
  %15 = load i32* %size.addr, align 4
  %call = call i8* @nvmmMalloc(i32 %15)
  %16 = bitcast i8* %call to i32*
  store i32* %16, i32** %dst, align 4
  %17 = load i32* %func_idx.addr, align 4
  %arrayidx8 = getelementptr inbounds [50 x %struct.Mgt_code_meta]* @mgtCodeMeta, i32 0, i32 %17
  %spm_addr9 = getelementptr inbounds %struct.Mgt_code_meta* %arrayidx8, i32 0, i32 1
  %18 = load i8** %spm_addr9, align 4
  %19 = bitcast i8* %18 to i32*
  store i32* %19, i32** %src, align 4
  %20 = load i32* %func_idx.addr, align 4
  %arrayidx10 = getelementptr inbounds [50 x %struct.Mgt_code_meta]* @mgtCodeMeta, i32 0, i32 %20
  %instCount11 = getelementptr inbounds %struct.Mgt_code_meta* %arrayidx10, i32 0, i32 3
  %21 = load i32* %instCount11, align 4
  store i32 %21, i32* %cc, align 4
  store i32 0, i32* %ix, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %22 = load i32* %ix, align 4
  %23 = load i32* %cc, align 4
  %cmp = icmp ult i32 %22, %23
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %24 = load i32* %ix, align 4
  %25 = load i32** %src, align 4
  %arrayidx12 = getelementptr inbounds i32* %25, i32 %24
  %26 = load i32* %arrayidx12, align 4
  %27 = load i32* %ix, align 4
  %28 = load i32** %dst, align 4
  %arrayidx13 = getelementptr inbounds i32* %28, i32 %27
  store i32 %26, i32* %arrayidx13, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %29 = load i32* %ix, align 4
  %inc = add nsw i32 %29, 1
  store i32 %inc, i32* %ix, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %30 = load i32** %dst, align 4
  %31 = bitcast i32* %30 to i8*
  %32 = load i32* %func_idx.addr, align 4
  %arrayidx14 = getelementptr inbounds [50 x %struct.Mgt_code_meta]* @mgtCodeMeta, i32 0, i32 %32
  %nvm_addr15 = getelementptr inbounds %struct.Mgt_code_meta* %arrayidx14, i32 0, i32 2
  store i8* %31, i8** %nvm_addr15, align 4
  ret void
}

declare i32 @main(i32, i8**) #1

; Function Attrs: nounwind
declare i32 @snprintf(i8*, i32, i8*, ...) #0

; Function Attrs: nounwind
declare i8* @strcat(i8*, i8*) #0

; Function Attrs: nounwind
define i32 @codeMgtEnd() #0 section "sec_mgtCode_0" {
entry:
  %0 = load %struct._IO_FILE** @_reportFile, align 4
  %call = call i32 (%struct._IO_FILE*, i8*, ...)* @fprintf(%struct._IO_FILE* %0, i8* getelementptr inbounds ([19 x i8]* @.str2, i32 0, i32 0))
  %1 = load %struct._IO_FILE** @_reportFile, align 4
  %call1 = call i32 @fflush(%struct._IO_FILE* %1)
  call void @printStatistics(%struct.StatsCounter* @CodeFetch_Stats, i8* getelementptr inbounds ([10 x i8]* @.str3, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @InstCount_Stats, i8* getelementptr inbounds ([10 x i8]* @.str4, i32 0, i32 0))
  ret i32 0
}

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #1

declare i32 @fflush(%struct._IO_FILE*) #1

; Function Attrs: nounwind
define i32 @setRegion(i32 %num) #0 section "sec_mgtCode_0" {
entry:
  %num.addr = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 %num, i32* %num.addr, align 4
  %0 = load i32* %num.addr, align 4
  store i32 %0, i32* @region_table_size, align 4
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %1 = load i32* %i, align 4
  %2 = load i32* %num.addr, align 4
  %cmp = icmp slt i32 %1, %2
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %3 = load i32* %i, align 4
  %arrayidx = getelementptr inbounds [10 x %struct._Region]* @_region_table, i32 0, i32 %3
  %func_index = getelementptr inbounds %struct._Region* %arrayidx, i32 0, i32 0
  store i32 0, i32* %func_index, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %4 = load i32* %i, align 4
  %inc = add nsw i32 %4, 1
  store i32 %inc, i32* %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret i32 0
}

; Function Attrs: nounwind
define i8* @getMgtCode(i32 %func_index) #0 section "sec_staticCode" {
entry:
  %retval = alloca i8*, align 4
  %func_index.addr = alloca i32, align 4
  %instC = alloca i32, align 4
  %ix = alloca i32, align 4
  %dst = alloca i32*, align 4
  %src = alloca i32*, align 4
  %cc = alloca i32, align 4
  store i32 %func_index, i32* %func_index.addr, align 4
  %0 = load i32* %func_index.addr, align 4
  %cmp = icmp eq i32 %0, 0
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval
  br label %return

if.end:                                           ; preds = %entry
  %1 = load i32* %func_index.addr, align 4
  %2 = load i32* %func_index.addr, align 4
  %arrayidx = getelementptr inbounds [50 x %struct.Mgt_code_meta]* @mgtCodeMeta, i32 0, i32 %2
  %region = getelementptr inbounds %struct.Mgt_code_meta* %arrayidx, i32 0, i32 6
  %3 = load %struct._Region** %region, align 4
  %func_index1 = getelementptr inbounds %struct._Region* %3, i32 0, i32 0
  %4 = load i32* %func_index1, align 4
  %cmp2 = icmp ne i32 %1, %4
  br i1 %cmp2, label %if.then3, label %if.end13

if.then3:                                         ; preds = %if.end
  store i32 0, i32* %instC, align 4
  call void @Increament(%struct.StatsCounter* @CodeFetch_Stats)
  %5 = load i32* %func_index.addr, align 4
  %arrayidx4 = getelementptr inbounds [50 x %struct.Mgt_code_meta]* @mgtCodeMeta, i32 0, i32 %5
  %spm_addr = getelementptr inbounds %struct.Mgt_code_meta* %arrayidx4, i32 0, i32 1
  %6 = load i8** %spm_addr, align 4
  %7 = bitcast i8* %6 to i32*
  store i32* %7, i32** %dst, align 4
  %8 = load i32* %func_index.addr, align 4
  %arrayidx5 = getelementptr inbounds [50 x %struct.Mgt_code_meta]* @mgtCodeMeta, i32 0, i32 %8
  %nvm_addr = getelementptr inbounds %struct.Mgt_code_meta* %arrayidx5, i32 0, i32 2
  %9 = load i8** %nvm_addr, align 4
  %10 = bitcast i8* %9 to i32*
  store i32* %10, i32** %src, align 4
  %11 = load i32* %func_index.addr, align 4
  %arrayidx6 = getelementptr inbounds [50 x %struct.Mgt_code_meta]* @mgtCodeMeta, i32 0, i32 %11
  %instCount = getelementptr inbounds %struct.Mgt_code_meta* %arrayidx6, i32 0, i32 3
  %12 = load i32* %instCount, align 4
  store i32 %12, i32* %cc, align 4
  store i32 0, i32* %ix, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %if.then3
  %13 = load i32* %ix, align 4
  %14 = load i32* %cc, align 4
  %cmp7 = icmp ult i32 %13, %14
  br i1 %cmp7, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %15 = load i32* %ix, align 4
  %16 = load i32** %src, align 4
  %arrayidx8 = getelementptr inbounds i32* %16, i32 %15
  %17 = load i32* %arrayidx8, align 4
  %18 = load i32* %ix, align 4
  %19 = load i32** %dst, align 4
  %arrayidx9 = getelementptr inbounds i32* %19, i32 %18
  store i32 %17, i32* %arrayidx9, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %20 = load i32* %ix, align 4
  %inc = add nsw i32 %20, 1
  store i32 %inc, i32* %ix, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %21 = load i32* %ix, align 4
  store i32 %21, i32* %instC, align 4
  %22 = load i32* %instC, align 4
  call void @IncreamentBy(%struct.StatsCounter* @InstCount_Stats, i32 %22)
  %23 = load i32* %func_index.addr, align 4
  %24 = load i32* %func_index.addr, align 4
  %arrayidx10 = getelementptr inbounds [50 x %struct.Mgt_code_meta]* @mgtCodeMeta, i32 0, i32 %24
  %region11 = getelementptr inbounds %struct.Mgt_code_meta* %arrayidx10, i32 0, i32 6
  %25 = load %struct._Region** %region11, align 4
  %func_index12 = getelementptr inbounds %struct._Region* %25, i32 0, i32 0
  store i32 %23, i32* %func_index12, align 4
  br label %if.end13

if.end13:                                         ; preds = %for.end, %if.end
  %26 = load i32* %func_index.addr, align 4
  %arrayidx14 = getelementptr inbounds [50 x %struct.Mgt_code_meta]* @mgtCodeMeta, i32 0, i32 %26
  %spm_addr15 = getelementptr inbounds %struct.Mgt_code_meta* %arrayidx14, i32 0, i32 1
  %27 = load i8** %spm_addr15, align 4
  store i8* %27, i8** %retval
  br label %return

return:                                           ; preds = %if.end13, %if.then
  %28 = load i8** %retval
  ret i8* %28
}

; Function Attrs: nounwind
define i32 @spmMgtInit(i32 %argc, i8** %argv) #0 section "sec_staticCode" {
entry:
  %retval = alloca i32, align 4
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 4
  store i32 %argc, i32* %argc.addr, align 4
  store i8** %argv, i8*** %argv.addr, align 4
  %0 = load i32* %argc.addr, align 4
  store i32 %0, i32* @main_argc, align 4
  %1 = load i8*** %argv.addr, align 4
  store i8** %1, i8*** @main_argv, align 4
  call void @InitStatsFile()
  %call = call noalias i8* @malloc(i32 67108864) #4
  store i8* %call, i8** @nvmm_region, align 4
  %2 = load i8** @nvmm_region, align 4
  %cmp = icmp eq i8* %2, null
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %call1 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([24 x i8]* @.str5, i32 0, i32 0))
  store i32 1, i32* %retval
  br label %return

if.end:                                           ; preds = %entry
  %call2 = call i8* @codeMgtInit()
  %call3 = call i32 @stackMgtInit()
  call void @heapMgtInit()
  %call4 = call i8* @getMgtCode(i32 1)
  %3 = load %struct._IO_FILE** @_reportFile, align 4
  %call5 = call i32 (%struct._IO_FILE*, i8*, ...)* @fprintf(%struct._IO_FILE* %3, i8* getelementptr inbounds ([25 x i8]* @.str18, i32 0, i32 0))
  %4 = load %struct._IO_FILE** @_reportFile, align 4
  %call6 = call i32 @fflush(%struct._IO_FILE* %4)
  %5 = call i8* asm sideeffect "mov $0, r13 ", "=r"() #4, !srcloc !3
  store i8* %5, i8** @systemStackPtr, align 4
  %6 = load i8** @spmStackUbound, align 4
  call void asm sideeffect "mov r13 , $0 ", "r"(i8* %6) #4, !srcloc !4
  %7 = load i32* @main_argc, align 4
  %8 = load i8*** @main_argv, align 4
  %call7 = call i32 @main(i32 %7, i8** %8)
  store i32 0, i32* %retval
  br label %return

return:                                           ; preds = %if.end, %if.then
  %9 = load i32* %retval
  ret i32 %9
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i32) #0

declare i32 @printf(i8*, ...) #1

; Function Attrs: nounwind
define void @endExecution() #0 section "sec_staticCode" {
entry:
  %csv = alloca %struct._IO_FILE*, align 4
  %0 = load %struct._IO_FILE** @_reportFile, align 4
  %call = call i32 (%struct._IO_FILE*, i8*, ...)* @fprintf(%struct._IO_FILE* %0, i8* getelementptr inbounds ([24 x i8]* @.str29, i32 0, i32 0))
  %1 = load %struct._IO_FILE** @_reportFile, align 4
  %call1 = call i32 @fflush(%struct._IO_FILE* %1)
  %call2 = call i8* @strcat(i8* getelementptr inbounds ([4096 x i8]* @csvStr, i32 0, i32 0), i8* getelementptr inbounds ([4096 x i8]* @csvStr1, i32 0, i32 0)) #4
  %call3 = call i8* @strcat(i8* getelementptr inbounds ([4096 x i8]* @csvStr, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8]* @.str310, i32 0, i32 0)) #4
  call void @heapMgtEnd()
  %call4 = call i8* @strcat(i8* getelementptr inbounds ([4096 x i8]* @csvStr, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8]* @.str411, i32 0, i32 0)) #4
  %call5 = call i8* @strcat(i8* getelementptr inbounds ([4096 x i8]* @csvStr, i32 0, i32 0), i8* getelementptr inbounds ([4096 x i8]* @csvStr2, i32 0, i32 0)) #4
  %call6 = call i32 @stackMgtEnd()
  %call7 = call i8* @strcat(i8* getelementptr inbounds ([4096 x i8]* @csvStr, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8]* @.str411, i32 0, i32 0)) #4
  %call8 = call i8* @strcat(i8* getelementptr inbounds ([4096 x i8]* @csvStr, i32 0, i32 0), i8* getelementptr inbounds ([4096 x i8]* @csvStr3, i32 0, i32 0)) #4
  %call9 = call i32 @codeMgtEnd()
  %2 = load %struct._IO_FILE** @_reportFile, align 4
  %call10 = call i32 (%struct._IO_FILE*, i8*, ...)* @fprintf(%struct._IO_FILE* %2, i8* getelementptr inbounds ([3 x i8]* @.str514, i32 0, i32 0))
  %3 = load %struct._IO_FILE** @_reportFile, align 4
  %call11 = call i32 @fflush(%struct._IO_FILE* %3)
  %call12 = call %struct._IO_FILE* @fopen(i8* getelementptr inbounds ([15 x i8]* @.str6, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8]* @.str7, i32 0, i32 0))
  store %struct._IO_FILE* %call12, %struct._IO_FILE** %csv, align 4
  %4 = load %struct._IO_FILE** %csv, align 4
  %call13 = call i32 (%struct._IO_FILE*, i8*, ...)* @fprintf(%struct._IO_FILE* %4, i8* getelementptr inbounds ([4 x i8]* @.str8, i32 0, i32 0), i8* getelementptr inbounds ([4096 x i8]* @csvStr, i32 0, i32 0))
  %5 = load %struct._IO_FILE** %csv, align 4
  %call14 = call i32 @fclose(%struct._IO_FILE* %5)
  ret void
}

declare %struct._IO_FILE* @fopen(i8*, i8*) #1

declare i32 @fclose(%struct._IO_FILE*) #1

; Function Attrs: nounwind
define i8* @nvmmMalloc(i32 %size) #0 section "sec_staticCode" {
entry:
  %size.addr = alloca i32, align 4
  %ptr = alloca i8*, align 4
  store i32 %size, i32* %size.addr, align 4
  %0 = load i32* @nvmmMallocNextPtr, align 4
  %1 = load i8** @nvmm_region, align 4
  %arrayidx = getelementptr inbounds i8* %1, i32 %0
  store i8* %arrayidx, i8** %ptr, align 4
  %2 = load i32* %size.addr, align 4
  %3 = load i32* @nvmmMallocNextPtr, align 4
  %add = add i32 %3, %2
  store i32 %add, i32* @nvmmMallocNextPtr, align 4
  %4 = load i8** %ptr, align 4
  ret i8* %4
}

; Function Attrs: nounwind
define void @debugMsg(i8* %msg) #0 section "sec_staticCode" {
entry:
  %msg.addr = alloca i8*, align 4
  store i8* %msg, i8** %msg.addr, align 4
  ret void
}

; Function Attrs: nounwind
define void @debugMsgAddr(i8* %f, i8* %addr) #0 section "sec_staticCode" {
entry:
  %f.addr = alloca i8*, align 4
  %addr.addr = alloca i8*, align 4
  store i8* %f, i8** %f.addr, align 4
  store i8* %addr, i8** %addr.addr, align 4
  ret void
}

; Function Attrs: nounwind
define i32* @startVargFrame() #0 {
entry:
  %ptr = alloca i32*, align 4
  %dataStartAddr = alloca i32*, align 4
  %datalength = alloca i32, align 4
  %previousFrameDataAddr = alloca i32**, align 4
  %previousFrameDataAddr7 = alloca i32**, align 4
  %dataStartAddr10 = alloca i32*, align 4
  %0 = load i32** @currentVargFrame, align 4
  %tobool = icmp ne i32* %0, null
  br i1 %tobool, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %1 = load i32** @currentVargFrame, align 4
  %add.ptr = getelementptr inbounds i32* %1, i32 3
  store i32* %add.ptr, i32** %dataStartAddr, align 4
  %2 = load i32** @currentVargFrame, align 4
  %arrayidx = getelementptr inbounds i32* %2, i32 2
  %3 = load i32* %arrayidx, align 4
  store i32 %3, i32* %datalength, align 4
  %4 = load i32** %dataStartAddr, align 4
  %5 = load i32* %datalength, align 4
  %add.ptr1 = getelementptr inbounds i32* %4, i32 %5
  store i32* %add.ptr1, i32** %ptr, align 4
  %6 = load i32** %ptr, align 4
  %add.ptr2 = getelementptr inbounds i32* %6, i32 1
  %7 = bitcast i32* %add.ptr2 to i32**
  store i32** %7, i32*** %previousFrameDataAddr, align 4
  %8 = load i32** @currentVargFrame, align 4
  %9 = load i32*** %previousFrameDataAddr, align 4
  %arrayidx3 = getelementptr inbounds i32** %9, i32 0
  store i32* %8, i32** %arrayidx3, align 4
  %10 = load i32** %ptr, align 4
  store i32* %10, i32** @currentVargFrame, align 4
  %11 = load i32** %ptr, align 4
  %add.ptr4 = getelementptr inbounds i32* %11, i32 3
  store i32* %add.ptr4, i32** %dataStartAddr, align 4
  %12 = load i32** %dataStartAddr, align 4
  %13 = ptrtoint i32* %12 to i32
  %14 = load i32** %ptr, align 4
  %arrayidx5 = getelementptr inbounds i32* %14, i32 0
  store i32 %13, i32* %arrayidx5, align 4
  %15 = load i32** @currentVargFrame, align 4
  %arrayidx6 = getelementptr inbounds i32* %15, i32 2
  store i32 0, i32* %arrayidx6, align 4
  br label %if.end

if.else:                                          ; preds = %entry
  store i32* bitcast ([1024 x i8]* @VarArg to i32*), i32** %ptr, align 4
  %16 = load i32** %ptr, align 4
  %add.ptr8 = getelementptr inbounds i32* %16, i32 1
  %17 = bitcast i32* %add.ptr8 to i32**
  store i32** %17, i32*** %previousFrameDataAddr7, align 4
  %18 = load i32*** %previousFrameDataAddr7, align 4
  %arrayidx9 = getelementptr inbounds i32** %18, i32 0
  store i32* null, i32** %arrayidx9, align 4
  %19 = load i32** %ptr, align 4
  store i32* %19, i32** @currentVargFrame, align 4
  %20 = load i32** %ptr, align 4
  %add.ptr11 = getelementptr inbounds i32* %20, i32 3
  store i32* %add.ptr11, i32** %dataStartAddr10, align 4
  %21 = load i32** %dataStartAddr10, align 4
  %22 = ptrtoint i32* %21 to i32
  %23 = load i32** %ptr, align 4
  %arrayidx12 = getelementptr inbounds i32* %23, i32 0
  store i32 %22, i32* %arrayidx12, align 4
  %24 = load i32** @currentVargFrame, align 4
  %arrayidx13 = getelementptr inbounds i32* %24, i32 2
  store i32 0, i32* %arrayidx13, align 4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %25 = load i32** %ptr, align 4
  ret i32* %25
}

; Function Attrs: nounwind
define void @append(i32* %VargFramePtr, i32 %data) #0 {
entry:
  %VargFramePtr.addr = alloca i32*, align 4
  %data.addr = alloca i32, align 4
  %dataStartAddr = alloca i32*, align 4
  %datalength = alloca i32, align 4
  %dataAddr = alloca i32*, align 4
  store i32* %VargFramePtr, i32** %VargFramePtr.addr, align 4
  store i32 %data, i32* %data.addr, align 4
  %0 = load i32** %VargFramePtr.addr, align 4
  %add.ptr = getelementptr inbounds i32* %0, i32 3
  store i32* %add.ptr, i32** %dataStartAddr, align 4
  %1 = load i32** %VargFramePtr.addr, align 4
  %arrayidx = getelementptr inbounds i32* %1, i32 2
  %2 = load i32* %arrayidx, align 4
  store i32 %2, i32* %datalength, align 4
  %3 = load i32** %dataStartAddr, align 4
  %4 = load i32* %datalength, align 4
  %add.ptr1 = getelementptr inbounds i32* %3, i32 %4
  store i32* %add.ptr1, i32** %dataAddr, align 4
  %5 = load i32* %data.addr, align 4
  %6 = load i32** %dataAddr, align 4
  %arrayidx2 = getelementptr inbounds i32* %6, i32 0
  store i32 %5, i32* %arrayidx2, align 4
  %7 = load i32* %datalength, align 4
  %add = add i32 %7, 4
  %8 = load i32** %VargFramePtr.addr, align 4
  %arrayidx3 = getelementptr inbounds i32* %8, i32 2
  store i32 %add, i32* %arrayidx3, align 4
  ret void
}

; Function Attrs: nounwind
define i32 @getNext(i32* %VargPtr, i32 %dataSize) #0 {
entry:
  %VargPtr.addr = alloca i32*, align 4
  %dataSize.addr = alloca i32, align 4
  %dataAddr = alloca i32*, align 4
  %data = alloca i32, align 4
  %nextDataAddr = alloca i32*, align 4
  store i32* %VargPtr, i32** %VargPtr.addr, align 4
  store i32 %dataSize, i32* %dataSize.addr, align 4
  %0 = load i32** %VargPtr.addr, align 4
  %arrayidx = getelementptr inbounds i32* %0, i32 0
  %1 = load i32* %arrayidx, align 4
  %2 = inttoptr i32 %1 to i32*
  store i32* %2, i32** %dataAddr, align 4
  %3 = load i32** %dataAddr, align 4
  %4 = load i32* %3, align 4
  store i32 %4, i32* %data, align 4
  %5 = load i32** %dataAddr, align 4
  %6 = load i32* %dataSize.addr, align 4
  %add.ptr = getelementptr inbounds i32* %5, i32 %6
  %7 = ptrtoint i32* %add.ptr to i32
  %8 = load i32** %VargPtr.addr, align 4
  %arrayidx1 = getelementptr inbounds i32* %8, i32 0
  store i32 %7, i32* %arrayidx1, align 4
  %9 = load i32** %VargPtr.addr, align 4
  %arrayidx2 = getelementptr inbounds i32* %9, i32 0
  %10 = load i32* %arrayidx2, align 4
  %11 = inttoptr i32 %10 to i32*
  store i32* %11, i32** %nextDataAddr, align 4
  %12 = load i32* %data, align 4
  ret i32 %12
}

; Function Attrs: nounwind
define void @restorePreviousFrame(i32* %VargFramePtr) #0 {
entry:
  %VargFramePtr.addr = alloca i32*, align 4
  %previousFrameDataAddr = alloca i32**, align 4
  store i32* %VargFramePtr, i32** %VargFramePtr.addr, align 4
  %0 = load i32** %VargFramePtr.addr, align 4
  %add.ptr = getelementptr inbounds i32* %0, i32 1
  %1 = bitcast i32* %add.ptr to i32**
  store i32** %1, i32*** %previousFrameDataAddr, align 4
  %2 = load i32*** %previousFrameDataAddr, align 4
  %arrayidx = getelementptr inbounds i32** %2, i32 0
  %3 = load i32** %arrayidx, align 4
  store i32* %3, i32** @currentVargFrame, align 4
  ret void
}

; Function Attrs: nounwind
define void @InitStatsFile() #0 {
entry:
  %call = call i8* @strcat(i8* getelementptr inbounds ([4096 x i8]* @csvStr, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8]* @.str9, i32 0, i32 0)) #4
  %call1 = call i8* @strcat(i8* getelementptr inbounds ([4096 x i8]* @csvStr, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8]* @.str310, i32 0, i32 0)) #4
  %0 = load %struct._IO_FILE** @stderr, align 4
  store %struct._IO_FILE* %0, %struct._IO_FILE** @_reportFile, align 4
  ret void
}

; Function Attrs: nounwind
define void @printStatistics(%struct.StatsCounter* %stat, i8* %vname) #0 {
entry:
  %stat.addr = alloca %struct.StatsCounter*, align 4
  %vname.addr = alloca i8*, align 4
  %buf1 = alloca [512 x i8], align 1
  %buf2 = alloca [512 x i8], align 1
  %buf3 = alloca [512 x i8], align 1
  store %struct.StatsCounter* %stat, %struct.StatsCounter** %stat.addr, align 4
  store i8* %vname, i8** %vname.addr, align 4
  %arraydecay = getelementptr inbounds [512 x i8]* %buf1, i32 0, i32 0
  %0 = load i8** %vname.addr, align 4
  %call = call i32 (i8*, i32, i8*, ...)* @snprintf(i8* %arraydecay, i32 512, i8* getelementptr inbounds ([7 x i8]* @.str10, i32 0, i32 0), i8* %0) #4
  %1 = load %struct.StatsCounter** %stat.addr, align 4
  %high = getelementptr inbounds %struct.StatsCounter* %1, i32 0, i32 0
  %2 = load i32* %high, align 4
  %cmp = icmp ugt i32 %2, 0
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %arraydecay1 = getelementptr inbounds [512 x i8]* %buf2, i32 0, i32 0
  %3 = load %struct.StatsCounter** %stat.addr, align 4
  %low = getelementptr inbounds %struct.StatsCounter* %3, i32 0, i32 1
  %4 = load i32* %low, align 4
  %5 = load %struct.StatsCounter** %stat.addr, align 4
  %high2 = getelementptr inbounds %struct.StatsCounter* %5, i32 0, i32 0
  %6 = load i32* %high2, align 4
  %call3 = call i32 (i8*, i32, i8*, ...)* @snprintf(i8* %arraydecay1, i32 512, i8* getelementptr inbounds ([21 x i8]* @.str11, i32 0, i32 0), i32 %4, i32 %6) #4
  br label %if.end

if.else:                                          ; preds = %entry
  %arraydecay4 = getelementptr inbounds [512 x i8]* %buf2, i32 0, i32 0
  %7 = load %struct.StatsCounter** %stat.addr, align 4
  %low5 = getelementptr inbounds %struct.StatsCounter* %7, i32 0, i32 1
  %8 = load i32* %low5, align 4
  %call6 = call i32 (i8*, i32, i8*, ...)* @snprintf(i8* %arraydecay4, i32 512, i8* getelementptr inbounds ([3 x i8]* @.str12, i32 0, i32 0), i32 %8) #4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %arraydecay7 = getelementptr inbounds [512 x i8]* %buf3, i32 0, i32 0
  %arraydecay8 = getelementptr inbounds [512 x i8]* %buf2, i32 0, i32 0
  %call9 = call i32 (i8*, i32, i8*, ...)* @snprintf(i8* %arraydecay7, i32 512, i8* getelementptr inbounds ([7 x i8]* @.str13, i32 0, i32 0), i8* %arraydecay8) #4
  %9 = load %struct._IO_FILE** @_reportFile, align 4
  %arraydecay10 = getelementptr inbounds [512 x i8]* %buf1, i32 0, i32 0
  %arraydecay11 = getelementptr inbounds [512 x i8]* %buf3, i32 0, i32 0
  %10 = load %struct.StatsCounter** %stat.addr, align 4
  %desc = getelementptr inbounds %struct.StatsCounter* %10, i32 0, i32 3
  %arraydecay12 = getelementptr inbounds [256 x i8]* %desc, i32 0, i32 0
  %call13 = call i32 (%struct._IO_FILE*, i8*, ...)* @fprintf(%struct._IO_FILE* %9, i8* getelementptr inbounds ([22 x i8]* @.str14, i32 0, i32 0), i32 15, i8* %arraydecay10, i32 32, i8* %arraydecay11, i8* %arraydecay12)
  %11 = load %struct.StatsCounter** %stat.addr, align 4
  %showInCsv = getelementptr inbounds %struct.StatsCounter* %11, i32 0, i32 2
  %12 = load i32* %showInCsv, align 4
  %tobool = icmp ne i32 %12, 0
  br i1 %tobool, label %if.then14, label %if.end18

if.then14:                                        ; preds = %if.end
  %call15 = call i8* @strcat(i8* getelementptr inbounds ([4096 x i8]* @csvStr, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8]* @.str310, i32 0, i32 0)) #4
  %arraydecay16 = getelementptr inbounds [512 x i8]* %buf2, i32 0, i32 0
  %call17 = call i8* @strcat(i8* getelementptr inbounds ([4096 x i8]* @csvStr, i32 0, i32 0), i8* %arraydecay16) #4
  br label %if.end18

if.end18:                                         ; preds = %if.then14, %if.end
  ret void
}

; Function Attrs: alwaysinline nounwind
define void @Increament(%struct.StatsCounter* %var) #2 {
entry:
  %var.addr = alloca %struct.StatsCounter*, align 4
  store %struct.StatsCounter* %var, %struct.StatsCounter** %var.addr, align 4
  %0 = load %struct.StatsCounter** %var.addr, align 4
  %low = getelementptr inbounds %struct.StatsCounter* %0, i32 0, i32 1
  %1 = load i32* %low, align 4
  %cmp = icmp eq i32 %1, -1
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %2 = load %struct.StatsCounter** %var.addr, align 4
  %high = getelementptr inbounds %struct.StatsCounter* %2, i32 0, i32 0
  %3 = load i32* %high, align 4
  %inc = add i32 %3, 1
  store i32 %inc, i32* %high, align 4
  %4 = load %struct.StatsCounter** %var.addr, align 4
  %low1 = getelementptr inbounds %struct.StatsCounter* %4, i32 0, i32 1
  store i32 0, i32* %low1, align 4
  br label %if.end

if.end:                                           ; preds = %if.then, %entry
  %5 = load %struct.StatsCounter** %var.addr, align 4
  %low2 = getelementptr inbounds %struct.StatsCounter* %5, i32 0, i32 1
  %6 = load i32* %low2, align 4
  %inc3 = add i32 %6, 1
  store i32 %inc3, i32* %low2, align 4
  ret void
}

; Function Attrs: alwaysinline nounwind
define void @IncreamentBy(%struct.StatsCounter* %var, i32 %value) #2 {
entry:
  %var.addr = alloca %struct.StatsCounter*, align 4
  %value.addr = alloca i32, align 4
  %a = alloca i32, align 4
  store %struct.StatsCounter* %var, %struct.StatsCounter** %var.addr, align 4
  store i32 %value, i32* %value.addr, align 4
  %0 = load %struct.StatsCounter** %var.addr, align 4
  %low = getelementptr inbounds %struct.StatsCounter* %0, i32 0, i32 1
  %1 = load i32* %low, align 4
  %sub = sub i32 -1, %1
  store i32 %sub, i32* %a, align 4
  %2 = load i32* %a, align 4
  %3 = load i32* %value.addr, align 4
  %cmp = icmp ult i32 %2, %3
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %4 = load %struct.StatsCounter** %var.addr, align 4
  %high = getelementptr inbounds %struct.StatsCounter* %4, i32 0, i32 0
  %5 = load i32* %high, align 4
  %inc = add i32 %5, 1
  store i32 %inc, i32* %high, align 4
  %6 = load i32* %value.addr, align 4
  %7 = load i32* %a, align 4
  %sub1 = sub i32 %6, %7
  %8 = load %struct.StatsCounter** %var.addr, align 4
  %low2 = getelementptr inbounds %struct.StatsCounter* %8, i32 0, i32 1
  store i32 %sub1, i32* %low2, align 4
  br label %if.end

if.else:                                          ; preds = %entry
  %9 = load i32* %value.addr, align 4
  %10 = load %struct.StatsCounter** %var.addr, align 4
  %low3 = getelementptr inbounds %struct.StatsCounter* %10, i32 0, i32 1
  %11 = load i32* %low3, align 4
  %add = add i32 %11, %9
  store i32 %add, i32* %low3, align 4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void
}

; Function Attrs: noinline nounwind
define void @_sstore() #3 section "sec_staticCode" {
entry:
  %_spm__used = alloca i32, align 4
  %0 = load i8** @currentstackPtr, align 4
  %1 = load i32* @_stack_depth, align 4
  %arrayidx = getelementptr inbounds [100 x %struct.STACK_ENTRY]* @_stack, i32 0, i32 %1
  %spm_addr = getelementptr inbounds %struct.STACK_ENTRY* %arrayidx, i32 0, i32 0
  store i8* %0, i8** %spm_addr, align 4
  %2 = load i8** @spmStackUbound, align 4
  %3 = load i32* @_stack_depth, align 4
  %arrayidx1 = getelementptr inbounds [100 x %struct.STACK_ENTRY]* @_stack, i32 0, i32 %3
  %spm_addr2 = getelementptr inbounds %struct.STACK_ENTRY* %arrayidx1, i32 0, i32 0
  %4 = load i8** %spm_addr2, align 4
  %sub.ptr.lhs.cast = ptrtoint i8* %2 to i32
  %sub.ptr.rhs.cast = ptrtoint i8* %4 to i32
  %sub.ptr.sub = sub i32 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast
  %5 = load i32* @_stack_depth, align 4
  %arrayidx3 = getelementptr inbounds [100 x %struct.STACK_ENTRY]* @_stack, i32 0, i32 %5
  %ssize = getelementptr inbounds %struct.STACK_ENTRY* %arrayidx3, i32 0, i32 2
  store i32 %sub.ptr.sub, i32* %ssize, align 4
  %6 = load i32* @_stack_depth, align 4
  %arrayidx4 = getelementptr inbounds [100 x %struct.STACK_ENTRY]* @_stack, i32 0, i32 %6
  %ssize5 = getelementptr inbounds %struct.STACK_ENTRY* %arrayidx4, i32 0, i32 2
  %7 = load i32* %ssize5, align 4
  store i32 %7, i32* %_spm__used, align 4
  %8 = load i32* @_stack_depth, align 4
  %cmp = icmp eq i32 %8, 0
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %9 = load i8** @nvmmStackUbound, align 4
  %10 = load i32* @_stack_depth, align 4
  %arrayidx6 = getelementptr inbounds [100 x %struct.STACK_ENTRY]* @_stack, i32 0, i32 %10
  %ssize7 = getelementptr inbounds %struct.STACK_ENTRY* %arrayidx6, i32 0, i32 2
  %11 = load i32* %ssize7, align 4
  %idx.neg = sub i32 0, %11
  %add.ptr = getelementptr inbounds i8* %9, i32 %idx.neg
  %12 = load i32* @_stack_depth, align 4
  %arrayidx8 = getelementptr inbounds [100 x %struct.STACK_ENTRY]* @_stack, i32 0, i32 %12
  %mem_addr = getelementptr inbounds %struct.STACK_ENTRY* %arrayidx8, i32 0, i32 1
  store i8* %add.ptr, i8** %mem_addr, align 4
  br label %if.end

if.else:                                          ; preds = %entry
  %13 = load i32* @_stack_depth, align 4
  %sub = sub nsw i32 %13, 1
  %arrayidx9 = getelementptr inbounds [100 x %struct.STACK_ENTRY]* @_stack, i32 0, i32 %sub
  %mem_addr10 = getelementptr inbounds %struct.STACK_ENTRY* %arrayidx9, i32 0, i32 1
  %14 = load i8** %mem_addr10, align 4
  %15 = load i32* @_stack_depth, align 4
  %arrayidx11 = getelementptr inbounds [100 x %struct.STACK_ENTRY]* @_stack, i32 0, i32 %15
  %ssize12 = getelementptr inbounds %struct.STACK_ENTRY* %arrayidx11, i32 0, i32 2
  %16 = load i32* %ssize12, align 4
  %idx.neg13 = sub i32 0, %16
  %add.ptr14 = getelementptr inbounds i8* %14, i32 %idx.neg13
  %17 = load i32* @_stack_depth, align 4
  %arrayidx15 = getelementptr inbounds [100 x %struct.STACK_ENTRY]* @_stack, i32 0, i32 %17
  %mem_addr16 = getelementptr inbounds %struct.STACK_ENTRY* %arrayidx15, i32 0, i32 1
  store i8* %add.ptr14, i8** %mem_addr16, align 4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %18 = load i32* @_stack_depth, align 4
  %arrayidx17 = getelementptr inbounds [100 x %struct.STACK_ENTRY]* @_stack, i32 0, i32 %18
  %status = getelementptr inbounds %struct.STACK_ENTRY* %arrayidx17, i32 0, i32 3
  store i32 0, i32* %status, align 4
  %19 = load i32* @_stack_depth, align 4
  %arrayidx18 = getelementptr inbounds [100 x %struct.STACK_ENTRY]* @_stack, i32 0, i32 %19
  %spm_addr19 = getelementptr inbounds %struct.STACK_ENTRY* %arrayidx18, i32 0, i32 0
  %20 = load i8** %spm_addr19, align 4
  %21 = load i32* @_stack_depth, align 4
  %arrayidx20 = getelementptr inbounds [100 x %struct.STACK_ENTRY]* @_stack, i32 0, i32 %21
  %mem_addr21 = getelementptr inbounds %struct.STACK_ENTRY* %arrayidx20, i32 0, i32 1
  %22 = load i8** %mem_addr21, align 4
  %23 = load i32* @_stack_depth, align 4
  %arrayidx22 = getelementptr inbounds [100 x %struct.STACK_ENTRY]* @_stack, i32 0, i32 %23
  %ssize23 = getelementptr inbounds %struct.STACK_ENTRY* %arrayidx22, i32 0, i32 2
  %24 = load i32* %ssize23, align 4
  %25 = load i32* @_stack_depth, align 4
  %call = call i32 @spm_to_mem(i8* %20, i8* %22, i32 %24, i32 %25)
  call void @Increament(%struct.StatsCounter* @stack2mem_Stats)
  %26 = load i32* %_spm__used, align 4
  %27 = load i32* @min_sp, align 4
  %cmp24 = icmp ult i32 %26, %27
  br i1 %cmp24, label %if.then25, label %if.end26

if.then25:                                        ; preds = %if.end
  %28 = load i32* %_spm__used, align 4
  store i32 %28, i32* getelementptr inbounds (%struct.StatsCounter* @min_sp_Stats, i32 0, i32 1), align 4
  br label %if.end26

if.end26:                                         ; preds = %if.then25, %if.end
  %29 = load i32* %_spm__used, align 4
  %30 = load i32* @max_sp, align 4
  %cmp27 = icmp ugt i32 %29, %30
  br i1 %cmp27, label %if.then28, label %if.end29

if.then28:                                        ; preds = %if.end26
  %31 = load i32* %_spm__used, align 4
  store i32 %31, i32* getelementptr inbounds (%struct.StatsCounter* @max_sp_Stats, i32 0, i32 1), align 4
  br label %if.end29

if.end29:                                         ; preds = %if.then28, %if.end26
  %32 = load i32* @_stack_depth, align 4
  %inc = add nsw i32 %32, 1
  store i32 %inc, i32* @_stack_depth, align 4
  ret void
}

; Function Attrs: nounwind
define i32 @spm_to_mem(i8* %spmAddr, i8* %memAddr, i32 %ssize, i32 %_stack_depth) #0 {
entry:
  %spmAddr.addr = alloca i8*, align 4
  %memAddr.addr = alloca i8*, align 4
  %ssize.addr = alloca i32, align 4
  %_stack_depth.addr = alloca i32, align 4
  %copyCount = alloca i32, align 4
  %ix = alloca i32, align 4
  %dst = alloca i8*, align 4
  %src = alloca i8*, align 4
  %cc = alloca i32, align 4
  store i8* %spmAddr, i8** %spmAddr.addr, align 4
  store i8* %memAddr, i8** %memAddr.addr, align 4
  store i32 %ssize, i32* %ssize.addr, align 4
  store i32 %_stack_depth, i32* %_stack_depth.addr, align 4
  %0 = load i32* %ssize.addr, align 4
  call void @IncreamentBy(%struct.StatsCounter* @MemUpdate_Stats, i32 %0)
  %1 = load i8** %memAddr.addr, align 4
  store i8* %1, i8** %dst, align 4
  %2 = load i8** %spmAddr.addr, align 4
  store i8* %2, i8** %src, align 4
  %3 = load i32* %ssize.addr, align 4
  store i32 %3, i32* %cc, align 4
  store i32 0, i32* %ix, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %4 = load i32* %ix, align 4
  %5 = load i32* %cc, align 4
  %cmp = icmp ult i32 %4, %5
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %6 = load i32* %ix, align 4
  %7 = load i8** %src, align 4
  %arrayidx = getelementptr inbounds i8* %7, i32 %6
  %8 = load i8* %arrayidx, align 1
  %9 = load i32* %ix, align 4
  %10 = load i8** %dst, align 4
  %arrayidx1 = getelementptr inbounds i8* %10, i32 %9
  store i8 %8, i8* %arrayidx1, align 1
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %11 = load i32* %ix, align 4
  %inc = add nsw i32 %11, 1
  store i32 %inc, i32* %ix, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %12 = load i32* %ix, align 4
  store i32 %12, i32* %copyCount, align 4
  %13 = load i32* %copyCount, align 4
  ret i32 %13
}

; Function Attrs: noinline nounwind
define void @_sload() #3 section "sec_staticCode" {
entry:
  %0 = load i32* @_stack_depth, align 4
  %dec = add nsw i32 %0, -1
  store i32 %dec, i32* @_stack_depth, align 4
  %1 = load i32* @_stack_depth, align 4
  %arrayidx = getelementptr inbounds [100 x %struct.STACK_ENTRY]* @_stack, i32 0, i32 %1
  %spm_addr = getelementptr inbounds %struct.STACK_ENTRY* %arrayidx, i32 0, i32 0
  %2 = load i8** %spm_addr, align 4
  store i8* %2, i8** @currentstackPtr, align 4
  %3 = load i32* @_stack_depth, align 4
  %arrayidx1 = getelementptr inbounds [100 x %struct.STACK_ENTRY]* @_stack, i32 0, i32 %3
  %spm_addr2 = getelementptr inbounds %struct.STACK_ENTRY* %arrayidx1, i32 0, i32 0
  %4 = load i8** %spm_addr2, align 4
  %5 = load i32* @_stack_depth, align 4
  %arrayidx3 = getelementptr inbounds [100 x %struct.STACK_ENTRY]* @_stack, i32 0, i32 %5
  %mem_addr = getelementptr inbounds %struct.STACK_ENTRY* %arrayidx3, i32 0, i32 1
  %6 = load i8** %mem_addr, align 4
  %7 = load i32* @_stack_depth, align 4
  %arrayidx4 = getelementptr inbounds [100 x %struct.STACK_ENTRY]* @_stack, i32 0, i32 %7
  %ssize = getelementptr inbounds %struct.STACK_ENTRY* %arrayidx4, i32 0, i32 2
  %8 = load i32* %ssize, align 4
  %9 = load i32* @_stack_depth, align 4
  %call = call i32 @mem_to_spm(i8* %4, i8* %6, i32 %8, i32 %9)
  call void @Increament(%struct.StatsCounter* @mem2stack_Stats)
  ret void
}

; Function Attrs: nounwind
define i32 @mem_to_spm(i8* %spmAddr, i8* %memAddr, i32 %ssize, i32 %_stack_depth) #0 {
entry:
  %spmAddr.addr = alloca i8*, align 4
  %memAddr.addr = alloca i8*, align 4
  %ssize.addr = alloca i32, align 4
  %_stack_depth.addr = alloca i32, align 4
  %copyCount = alloca i32, align 4
  %ix = alloca i32, align 4
  %dst = alloca i8*, align 4
  %src = alloca i8*, align 4
  %cc = alloca i32, align 4
  store i8* %spmAddr, i8** %spmAddr.addr, align 4
  store i8* %memAddr, i8** %memAddr.addr, align 4
  store i32 %ssize, i32* %ssize.addr, align 4
  store i32 %_stack_depth, i32* %_stack_depth.addr, align 4
  %0 = load i8** %spmAddr.addr, align 4
  store i8* %0, i8** %dst, align 4
  %1 = load i8** %memAddr.addr, align 4
  store i8* %1, i8** %src, align 4
  %2 = load i32* %ssize.addr, align 4
  store i32 %2, i32* %cc, align 4
  store i32 0, i32* %ix, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %3 = load i32* %ix, align 4
  %4 = load i32* %cc, align 4
  %cmp = icmp ult i32 %3, %4
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %5 = load i32* %ix, align 4
  %6 = load i8** %src, align 4
  %arrayidx = getelementptr inbounds i8* %6, i32 %5
  %7 = load i8* %arrayidx, align 1
  %8 = load i32* %ix, align 4
  %9 = load i8** %dst, align 4
  %arrayidx1 = getelementptr inbounds i8* %9, i32 %8
  store i8 %7, i8* %arrayidx1, align 1
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %10 = load i32* %ix, align 4
  %inc = add nsw i32 %10, 1
  store i32 %inc, i32* %ix, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %11 = load i32* %ix, align 4
  store i32 %11, i32* %copyCount, align 4
  %12 = load i32* %copyCount, align 4
  ret i32 %12
}

; Function Attrs: nounwind
define i8* @AddressTrans_mem2spm(i8* %memAddr, i32 %InstructionType) #0 {
entry:
  %memAddr.addr = alloca i8*, align 4
  %InstructionType.addr = alloca i32, align 4
  store i8* %memAddr, i8** %memAddr.addr, align 4
  store i32 %InstructionType, i32* %InstructionType.addr, align 4
  %0 = load i8** %memAddr.addr, align 4
  ret i8* %0
}

; Function Attrs: nounwind
define i32 @stackMgtInit() #0 section "sec_mgtCode_0" {
entry:
  %buf = alloca [512 x i8], align 1
  store i8* getelementptr inbounds ([32768 x i8]* @spmStackSection, i32 0, i32 0), i8** @spmStackLbound, align 4
  store i8* getelementptr inbounds ([32768 x i8]* @spmStackSection, i32 0, i32 32767), i8** @spmStackUbound, align 4
  %call = call i8* @nvmmMalloc(i32 262144)
  store i8* %call, i8** @nvmmStackLbound, align 4
  %0 = load i8** @nvmmStackLbound, align 4
  %add.ptr = getelementptr inbounds i8* %0, i32 262144
  store i8* %add.ptr, i8** @nvmmStackUbound, align 4
  %1 = load %struct._IO_FILE** @_reportFile, align 4
  %2 = load i8** @spmStackLbound, align 4
  %3 = load i8** @spmStackUbound, align 4
  %4 = load i8** @spmStackUbound, align 4
  %5 = load i8** @spmStackLbound, align 4
  %sub.ptr.lhs.cast = ptrtoint i8* %4 to i32
  %sub.ptr.rhs.cast = ptrtoint i8* %5 to i32
  %sub.ptr.sub = sub i32 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast
  %6 = load i8** @nvmmStackLbound, align 4
  %7 = load i8** @nvmmStackUbound, align 4
  %8 = load i8** @nvmmStackUbound, align 4
  %9 = load i8** @nvmmStackLbound, align 4
  %sub.ptr.lhs.cast1 = ptrtoint i8* %8 to i32
  %sub.ptr.rhs.cast2 = ptrtoint i8* %9 to i32
  %sub.ptr.sub3 = sub i32 %sub.ptr.lhs.cast1, %sub.ptr.rhs.cast2
  %call4 = call i32 (%struct._IO_FILE*, i8*, ...)* @fprintf(%struct._IO_FILE* %1, i8* getelementptr inbounds ([80 x i8]* @.str25, i32 0, i32 0), i8* %2, i8* %3, i32 %sub.ptr.sub, i8* %6, i8* %7, i32 %sub.ptr.sub3)
  %10 = load %struct._IO_FILE** @_reportFile, align 4
  %call5 = call i32 @fflush(%struct._IO_FILE* %10)
  %arraydecay = getelementptr inbounds [512 x i8]* %buf, i32 0, i32 0
  %11 = load i8** @spmStackUbound, align 4
  %12 = load i8** @spmStackLbound, align 4
  %sub.ptr.lhs.cast6 = ptrtoint i8* %11 to i32
  %sub.ptr.rhs.cast7 = ptrtoint i8* %12 to i32
  %sub.ptr.sub8 = sub i32 %sub.ptr.lhs.cast6, %sub.ptr.rhs.cast7
  %call9 = call i32 (i8*, i32, i8*, ...)* @snprintf(i8* %arraydecay, i32 512, i8* getelementptr inbounds ([3 x i8]* @.str126, i32 0, i32 0), i32 %sub.ptr.sub8) #4
  %arraydecay10 = getelementptr inbounds [512 x i8]* %buf, i32 0, i32 0
  %call11 = call i8* @strcat(i8* getelementptr inbounds ([4096 x i8]* @csvStr2, i32 0, i32 0), i8* %arraydecay10) #4
  ret i32 0
}

; Function Attrs: nounwind
define i32 @stackMgtEnd() #0 section "sec_mgtCode_0" {
entry:
  %0 = load %struct._IO_FILE** @_reportFile, align 4
  %call = call i32 (%struct._IO_FILE*, i8*, ...)* @fprintf(%struct._IO_FILE* %0, i8* getelementptr inbounds ([20 x i8]* @.str227, i32 0, i32 0))
  %1 = load %struct._IO_FILE** @_reportFile, align 4
  %call1 = call i32 @fflush(%struct._IO_FILE* %1)
  call void @printStatistics(%struct.StatsCounter* @stack2mem_Stats, i8* getelementptr inbounds ([10 x i8]* @.str328, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @mem2stack_Stats, i8* getelementptr inbounds ([10 x i8]* @.str429, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @MemUpdate_Stats, i8* getelementptr inbounds ([10 x i8]* @.str530, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @stackbit_flips_Stats, i8* getelementptr inbounds ([15 x i8]* @.str631, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @min_sp_Stats, i8* getelementptr inbounds ([7 x i8]* @.str732, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @max_sp_Stats, i8* getelementptr inbounds ([7 x i8]* @.str833, i32 0, i32 0))
  ret i32 0
}

; Function Attrs: nounwind
define i32 @get_blk_addr(i32 %addr) #0 {
entry:
  %addr.addr = alloca i32, align 4
  store i32 %addr, i32* %addr.addr, align 4
  %0 = load i32* %addr.addr, align 4
  %1 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 6), align 4
  %shr = lshr i32 %0, %1
  %2 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 6), align 4
  %shl = shl i32 %shr, %2
  ret i32 %shl
}

; Function Attrs: nounwind
define void @heapMgtEnd() #0 section "sec_mgtCode_0" {
entry:
  %0 = load %struct._IO_FILE** @_reportFile, align 4
  %call = call i32 (%struct._IO_FILE*, i8*, ...)* @fprintf(%struct._IO_FILE* %0, i8* getelementptr inbounds ([19 x i8]* @.str38, i32 0, i32 0))
  %1 = load %struct._IO_FILE** @_reportFile, align 4
  %call1 = call i32 @fflush(%struct._IO_FILE* %1)
  call void @printStatistics(%struct.StatsCounter* @mallocCalls_Stats, i8* getelementptr inbounds ([12 x i8]* @.str139, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @freeCalls_Stats, i8* getelementptr inbounds ([10 x i8]* @.str240, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @addrTrans_Stats, i8* getelementptr inbounds ([10 x i8]* @.str341, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @Writes_Stats, i8* getelementptr inbounds ([7 x i8]* @.str442, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @not_heap_addr_Stats, i8* getelementptr inbounds ([14 x i8]* @.str543, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @in_heap_addr_Stats, i8* getelementptr inbounds ([13 x i8]* @.str644, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @hit_Stats, i8* getelementptr inbounds ([4 x i8]* @.str745, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @victim_buffer_hit_Stats, i8* getelementptr inbounds ([18 x i8]* @.str846, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @miss_Stats, i8* getelementptr inbounds ([5 x i8]* @.str947, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @Dirty_Stats, i8* getelementptr inbounds ([6 x i8]* @.str1048, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @NotDirty_Stats, i8* getelementptr inbounds ([9 x i8]* @.str1149, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @NotValid_Stats, i8* getelementptr inbounds ([9 x i8]* @.str1250, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @Evictions_Stats, i8* getelementptr inbounds ([10 x i8]* @.str1351, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @heapbit_flips_Stats, i8* getelementptr inbounds ([14 x i8]* @.str1452, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @BlockFetch_Stats, i8* getelementptr inbounds ([11 x i8]* @.str15, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @MoveToVB_Stats, i8* getelementptr inbounds ([9 x i8]* @.str16, i32 0, i32 0))
  call void @printStatistics(%struct.StatsCounter* @DataOverFlows_Stats, i8* getelementptr inbounds ([14 x i8]* @.str17, i32 0, i32 0))
  ret void
}

; Function Attrs: nounwind
define i32 @fetch_ftn(i8* %spmAddr_, i8* %memAddr_) #0 section "sec_staticCode" {
entry:
  %spmAddr_.addr = alloca i8*, align 4
  %memAddr_.addr = alloca i8*, align 4
  store i8* %spmAddr_, i8** %spmAddr_.addr, align 4
  store i8* %memAddr_, i8** %memAddr_.addr, align 4
  call void @Increament(%struct.StatsCounter* @BlockFetch_Stats)
  %0 = load i8** %spmAddr_.addr, align 4
  %1 = load i8** %memAddr_.addr, align 4
  call void @llvm.memcpy.p0i8.p0i8.i32(i8* %0, i8* %1, i32 260, i32 1, i1 false)
  ret i32 256
}

; Function Attrs: nounwind
declare void @llvm.memcpy.p0i8.p0i8.i32(i8* nocapture, i8* nocapture readonly, i32, i32, i1) #4

; Function Attrs: nounwind
define i32 @eviction_ftn(i8* %spmAddr_, i8* %memAddr_) #0 section "sec_staticCode" {
entry:
  %spmAddr_.addr = alloca i8*, align 4
  %memAddr_.addr = alloca i8*, align 4
  store i8* %spmAddr_, i8** %spmAddr_.addr, align 4
  store i8* %memAddr_, i8** %memAddr_.addr, align 4
  call void @Increament(%struct.StatsCounter* @Evictions_Stats)
  %0 = load i8** %memAddr_.addr, align 4
  %1 = load i8** %spmAddr_.addr, align 4
  call void @llvm.memcpy.p0i8.p0i8.i32(i8* %0, i8* %1, i32 260, i32 1, i1 false)
  ret i32 256
}

; Function Attrs: nounwind
define void @heapMgtInit() #0 section "sec_mgtCode_0" {
entry:
  %capacity = alloca i32, align 4
  %assoc = alloca i32, align 4
  %blk_size = alloca i32, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %assoc_len = alloca i32, align 4
  %_hcache_metadata_sets = alloca i8*, align 4
  %_hcache_metadata_blks = alloca i8*, align 4
  %_hcache_data = alloca i8*, align 4
  %last_spm_blk_addr = alloca i8*, align 4
  %getblkindex = alloca i32, align 4
  %buf = alloca [512 x i8], align 1
  store i32 4096, i32* %capacity, align 4
  store i32 4, i32* %assoc, align 4
  store i32 256, i32* %blk_size, align 4
  store i32 0, i32* %j, align 4
  %0 = load i32* %assoc, align 4
  %call = call i32 @next_power_of_2(i32 %0)
  store i32 %call, i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 0), align 4
  %1 = load i32* %blk_size, align 4
  %call1 = call i32 @next_power_of_2(i32 %1)
  store i32 %call1, i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 1), align 4
  %2 = load i32* %capacity, align 4
  %call2 = call i32 @next_power_of_2(i32 %2)
  %3 = load i32* %blk_size, align 4
  %div = udiv i32 %call2, %3
  store i32 %div, i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 3), align 4
  %4 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 3), align 4
  %5 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 0), align 4
  %div3 = udiv i32 %4, %5
  store i32 %div3, i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 2), align 4
  %6 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 1), align 4
  %conv = uitofp i32 %6 to double
  %call4 = call double @log2(double %conv) #4
  %conv5 = fptoui double %call4 to i32
  store i32 %conv5, i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 6), align 4
  %7 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 2), align 4
  %conv6 = uitofp i32 %7 to double
  %call7 = call double @log2(double %conv6) #4
  %conv8 = fptoui double %call7 to i32
  store i32 %conv8, i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 5), align 4
  %8 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 5), align 4
  %sub = sub i32 32, %8
  %9 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 6), align 4
  %sub9 = sub i32 %sub, %9
  store i32 %sub9, i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 4), align 4
  %call10 = call i32 @next_power_of_2(i32 32)
  %add.ptr = getelementptr inbounds i8* getelementptr inbounds ([1048576 x i8]* @GV_hcache_metadata_sets, i32 0, i32 0), i32 %call10
  store i8* %add.ptr, i8** %_hcache_metadata_sets, align 4
  %10 = load i8** %_hcache_metadata_sets, align 4
  %11 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 2), align 4
  %mul = mul i32 %11, 8
  %call11 = call i32 @next_power_of_2(i32 %mul)
  %add.ptr12 = getelementptr inbounds i8* %10, i32 %call11
  store i8* %add.ptr12, i8** %_hcache_metadata_blks, align 4
  %12 = load i8** %_hcache_metadata_blks, align 4
  %13 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 3), align 4
  %mul13 = mul i32 %13, 24
  %call14 = call i32 @next_power_of_2(i32 %mul13)
  %add.ptr15 = getelementptr inbounds i8* %12, i32 %call14
  store i8* %add.ptr15, i8** %_hcache_data, align 4
  %14 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 0), align 4
  %conv16 = uitofp i32 %14 to double
  %call17 = call double @log2(double %conv16) #4
  %conv18 = fptoui double %call17 to i32
  store i32 %conv18, i32* %assoc_len, align 4
  store i8* getelementptr inbounds ([1048576 x i8]* @GV_hcache_metadata_sets, i32 0, i32 1048575), i8** @GV_hcache_metadata_sets_end, align 4
  %15 = load i8** %_hcache_data, align 4
  store i8* %15, i8** @GV_blks_startAddr, align 4
  %16 = load i8** %_hcache_metadata_sets, align 4
  %17 = bitcast i8* %16 to %struct._set_t*
  store %struct._set_t* %17, %struct._set_t** getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 7), align 4
  store i8* null, i8** %last_spm_blk_addr, align 4
  store i32 0, i32* %getblkindex, align 4
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc48, %entry
  %18 = load i32* %i, align 4
  %19 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 2), align 4
  %cmp = icmp ult i32 %18, %19
  br i1 %cmp, label %for.body, label %for.end50

for.body:                                         ; preds = %for.cond
  %20 = load i8** %_hcache_metadata_blks, align 4
  %21 = load i32* %i, align 4
  %22 = load i32* %assoc_len, align 4
  %shl = shl i32 %21, %22
  %mul20 = mul i32 %shl, 24
  %add.ptr21 = getelementptr inbounds i8* %20, i32 %mul20
  %23 = bitcast i8* %add.ptr21 to %struct._blk_t*
  %24 = load i32* %i, align 4
  %25 = load %struct._set_t** getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 7), align 4
  %arrayidx = getelementptr inbounds %struct._set_t* %25, i32 %24
  %blks = getelementptr inbounds %struct._set_t* %arrayidx, i32 0, i32 0
  store %struct._blk_t* %23, %struct._blk_t** %blks, align 4
  store i32 0, i32* %j, align 4
  br label %for.cond22

for.cond22:                                       ; preds = %for.inc, %for.body
  %26 = load i32* %j, align 4
  %27 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 0), align 4
  %cmp23 = icmp ult i32 %26, %27
  br i1 %cmp23, label %for.body25, label %for.end

for.body25:                                       ; preds = %for.cond22
  %28 = load i32* %j, align 4
  %29 = load i32* %i, align 4
  %30 = load %struct._set_t** getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 7), align 4
  %arrayidx26 = getelementptr inbounds %struct._set_t* %30, i32 %29
  %blks27 = getelementptr inbounds %struct._set_t* %arrayidx26, i32 0, i32 0
  %31 = load %struct._blk_t** %blks27, align 4
  %arrayidx28 = getelementptr inbounds %struct._blk_t* %31, i32 %28
  %status = getelementptr inbounds %struct._blk_t* %arrayidx28, i32 0, i32 0
  store i32 1, i32* %status, align 4
  %32 = load i32* %j, align 4
  %33 = load i32* %i, align 4
  %34 = load %struct._set_t** getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 7), align 4
  %arrayidx29 = getelementptr inbounds %struct._set_t* %34, i32 %33
  %blks30 = getelementptr inbounds %struct._set_t* %arrayidx29, i32 0, i32 0
  %35 = load %struct._blk_t** %blks30, align 4
  %arrayidx31 = getelementptr inbounds %struct._blk_t* %35, i32 %32
  %tag = getelementptr inbounds %struct._blk_t* %arrayidx31, i32 0, i32 1
  store i32 0, i32* %tag, align 4
  %36 = load i32* %i, align 4
  %37 = load i32* %j, align 4
  %38 = load i32* %i, align 4
  %39 = load %struct._set_t** getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 7), align 4
  %arrayidx32 = getelementptr inbounds %struct._set_t* %39, i32 %38
  %blks33 = getelementptr inbounds %struct._set_t* %arrayidx32, i32 0, i32 0
  %40 = load %struct._blk_t** %blks33, align 4
  %arrayidx34 = getelementptr inbounds %struct._blk_t* %40, i32 %37
  %set_index = getelementptr inbounds %struct._blk_t* %arrayidx34, i32 0, i32 4
  store i32 %36, i32* %set_index, align 4
  %41 = load i32* %j, align 4
  %42 = load i32* %j, align 4
  %43 = load i32* %i, align 4
  %44 = load %struct._set_t** getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 7), align 4
  %arrayidx35 = getelementptr inbounds %struct._set_t* %44, i32 %43
  %blks36 = getelementptr inbounds %struct._set_t* %arrayidx35, i32 0, i32 0
  %45 = load %struct._blk_t** %blks36, align 4
  %arrayidx37 = getelementptr inbounds %struct._blk_t* %45, i32 %42
  %index = getelementptr inbounds %struct._blk_t* %arrayidx37, i32 0, i32 5
  store i32 %41, i32* %index, align 4
  %46 = load i32* %getblkindex, align 4
  %inc = add i32 %46, 1
  store i32 %inc, i32* %getblkindex, align 4
  %arrayidx38 = getelementptr inbounds [20 x [260 x i8]]* @spmHeapBlocks, i32 0, i32 %46
  %arrayidx39 = getelementptr inbounds [260 x i8]* %arrayidx38, i32 0, i32 0
  %47 = load i32* %j, align 4
  %48 = load i32* %i, align 4
  %49 = load %struct._set_t** getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 7), align 4
  %arrayidx40 = getelementptr inbounds %struct._set_t* %49, i32 %48
  %blks41 = getelementptr inbounds %struct._set_t* %arrayidx40, i32 0, i32 0
  %50 = load %struct._blk_t** %blks41, align 4
  %arrayidx42 = getelementptr inbounds %struct._blk_t* %50, i32 %47
  %data = getelementptr inbounds %struct._blk_t* %arrayidx42, i32 0, i32 2
  store i8* %arrayidx39, i8** %data, align 4
  %51 = load i32* %j, align 4
  %52 = load i32* %i, align 4
  %53 = load %struct._set_t** getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 7), align 4
  %arrayidx43 = getelementptr inbounds %struct._set_t* %53, i32 %52
  %blks44 = getelementptr inbounds %struct._set_t* %arrayidx43, i32 0, i32 0
  %54 = load %struct._blk_t** %blks44, align 4
  %arrayidx45 = getelementptr inbounds %struct._blk_t* %54, i32 %51
  %data46 = getelementptr inbounds %struct._blk_t* %arrayidx45, i32 0, i32 2
  %55 = load i8** %data46, align 4
  store i8* %55, i8** %last_spm_blk_addr, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body25
  %56 = load i32* %j, align 4
  %inc47 = add i32 %56, 1
  store i32 %inc47, i32* %j, align 4
  br label %for.cond22

for.end:                                          ; preds = %for.cond22
  br label %for.inc48

for.inc48:                                        ; preds = %for.end
  %57 = load i32* %i, align 4
  %inc49 = add i32 %57, 1
  store i32 %inc49, i32* %i, align 4
  br label %for.cond

for.end50:                                        ; preds = %for.cond
  store i32 0, i32* %i, align 4
  br label %for.cond51

for.cond51:                                       ; preds = %for.inc65, %for.end50
  %58 = load i32* %i, align 4
  %cmp52 = icmp ult i32 %58, 4
  br i1 %cmp52, label %for.body54, label %for.end67

for.body54:                                       ; preds = %for.cond51
  %59 = load i32* %i, align 4
  %arrayidx55 = getelementptr inbounds [4 x %struct._blk_t]* @victim_buffer_blks, i32 0, i32 %59
  %tag56 = getelementptr inbounds %struct._blk_t* %arrayidx55, i32 0, i32 1
  store i32 0, i32* %tag56, align 4
  %60 = load i32* %i, align 4
  %arrayidx57 = getelementptr inbounds [4 x %struct._blk_t]* @victim_buffer_blks, i32 0, i32 %60
  %mem_blk_addr = getelementptr inbounds %struct._blk_t* %arrayidx57, i32 0, i32 3
  store i8* null, i8** %mem_blk_addr, align 4
  %61 = load i32* %i, align 4
  %arrayidx58 = getelementptr inbounds [4 x %struct._blk_t]* @victim_buffer_blks, i32 0, i32 %61
  %status59 = getelementptr inbounds %struct._blk_t* %arrayidx58, i32 0, i32 0
  store i32 1, i32* %status59, align 4
  %62 = load i32* %getblkindex, align 4
  %inc60 = add i32 %62, 1
  store i32 %inc60, i32* %getblkindex, align 4
  %arrayidx61 = getelementptr inbounds [20 x [260 x i8]]* @spmHeapBlocks, i32 0, i32 %62
  %arrayidx62 = getelementptr inbounds [260 x i8]* %arrayidx61, i32 0, i32 0
  %63 = load i32* %i, align 4
  %arrayidx63 = getelementptr inbounds [4 x %struct._blk_t]* @victim_buffer_blks, i32 0, i32 %63
  %data64 = getelementptr inbounds %struct._blk_t* %arrayidx63, i32 0, i32 2
  store i8* %arrayidx62, i8** %data64, align 4
  br label %for.inc65

for.inc65:                                        ; preds = %for.body54
  %64 = load i32* %i, align 4
  %inc66 = add i32 %64, 1
  store i32 %inc66, i32* %i, align 4
  br label %for.cond51

for.end67:                                        ; preds = %for.cond51
  %65 = load %struct._IO_FILE** @_reportFile, align 4
  %call68 = call i32 (%struct._IO_FILE*, i8*, ...)* @fprintf(%struct._IO_FILE* %65, i8* getelementptr inbounds ([45 x i8]* @.str1853, i32 0, i32 0), i8* getelementptr inbounds ([1048576 x i8]* @GV_hcache_metadata_sets, i32 0, i32 0), i8* getelementptr inbounds ([1048576 x i8]* @GV_hcache_metadata_sets, i32 0, i32 1048575), i32 1048576)
  %66 = load %struct._IO_FILE** @_reportFile, align 4
  %call69 = call i32 @fflush(%struct._IO_FILE* %66)
  %67 = load %struct._IO_FILE** @_reportFile, align 4
  %68 = load i32* %capacity, align 4
  %call70 = call i32 @next_power_of_2(i32 %68)
  %69 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 1), align 4
  %70 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 0), align 4
  %71 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 2), align 4
  %72 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 3), align 4
  %73 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 4), align 4
  %74 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 5), align 4
  %75 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 6), align 4
  %76 = load i8** @GV_blks_startAddr, align 4
  %77 = ptrtoint i8* %76 to i32
  %78 = load i8** @GV_hcache_metadata_sets_end, align 4
  %79 = ptrtoint i8* %78 to i32
  %80 = load i8** %last_spm_blk_addr, align 4
  %81 = ptrtoint i8* %80 to i32
  %call71 = call i32 (%struct._IO_FILE*, i8*, ...)* @fprintf(%struct._IO_FILE* %67, i8* getelementptr inbounds ([292 x i8]* @.str19, i32 0, i32 0), i32 %call70, i32 %69, i32 %70, i32 %71, i32 %72, i32 4, i32 %73, i32 %74, i32 %75, i32 %77, i32 %79, i32 %81)
  %82 = load %struct._IO_FILE** @_reportFile, align 4
  %call72 = call i32 @fflush(%struct._IO_FILE* %82)
  %arraydecay = getelementptr inbounds [512 x i8]* %buf, i32 0, i32 0
  %83 = load i32* %capacity, align 4
  %call73 = call i32 @next_power_of_2(i32 %83)
  %84 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 1), align 4
  %85 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 0), align 4
  %86 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 2), align 4
  %87 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 3), align 4
  %call74 = call i32 (i8*, i32, i8*, ...)* @snprintf(i8* %arraydecay, i32 512, i8* getelementptr inbounds ([20 x i8]* @.str20, i32 0, i32 0), i32 %call73, i32 %84, i32 %85, i32 %86, i32 %87) #4
  %arraydecay75 = getelementptr inbounds [512 x i8]* %buf, i32 0, i32 0
  %call76 = call i8* @strcat(i8* getelementptr inbounds ([4096 x i8]* @csvStr1, i32 0, i32 0), i8* %arraydecay75) #4
  call void bitcast (void (...)* @init_spm_malloc to void ()*)()
  ret void
}

; Function Attrs: nounwind
declare double @log2(double) #0

declare void @init_spm_malloc(...) #1

; Function Attrs: nounwind
define i32* @addrTranslation(i32* %gaddr__, i32 %opcode, i32 %dataSize) #0 section "sec_staticCode" {
entry:
  %retval = alloca i32*, align 4
  %gaddr__.addr = alloca i32*, align 4
  %opcode.addr = alloca i32, align 4
  %dataSize.addr = alloca i32, align 4
  %gaddr = alloca i8*, align 4
  %i = alloca i32, align 4
  %addr = alloca i32, align 4
  %tag = alloca i32, align 4
  %idx = alloca i32, align 4
  %offset = alloca i32, align 4
  %victim_counter = alloca i32, align 4
  %sp = alloca i8*, align 4
  %laddr = alloca i8*, align 4
  %blk = alloca %struct._blk_t*, align 4
  %set = alloca %struct._set_t*, align 4
  %mem_blk_addr = alloca i8*, align 4
  %evict_blk = alloca %struct._blk_t*, align 4
  %rtnptr = alloca i8*, align 4
  %p = alloca i8*, align 4
  %bEnd = alloca i8*, align 4
  store i32* %gaddr__, i32** %gaddr__.addr, align 4
  store i32 %opcode, i32* %opcode.addr, align 4
  store i32 %dataSize, i32* %dataSize.addr, align 4
  call void @Increament(%struct.StatsCounter* @addrTrans_Stats)
  %0 = load i32** %gaddr__.addr, align 4
  %1 = bitcast i32* %0 to i8*
  store i8* %1, i8** %gaddr, align 4
  store %struct._blk_t* null, %struct._blk_t** %blk, align 4
  %2 = load i8** %gaddr, align 4
  %call = call i32 @isHeapAddr(i8* %2)
  %tobool = icmp ne i32 %call, 0
  br i1 %tobool, label %if.end, label %if.then

if.then:                                          ; preds = %entry
  call void @Increament(%struct.StatsCounter* @not_heap_addr_Stats)
  %3 = load i32** %gaddr__.addr, align 4
  store i32* %3, i32** %retval
  br label %return

if.end:                                           ; preds = %entry
  call void @Increament(%struct.StatsCounter* @in_heap_addr_Stats)
  %4 = load i8** %gaddr, align 4
  %5 = ptrtoint i8* %4 to i32
  store i32 %5, i32* %addr, align 4
  %6 = load i32* %addr, align 4
  %call1 = call i32 @get_tag(i32 %6)
  store i32 %call1, i32* %tag, align 4
  %7 = load i32* %addr, align 4
  %call2 = call i32 @get_index(i32 %7)
  store i32 %call2, i32* %idx, align 4
  %8 = load i32* %addr, align 4
  %call3 = call i32 @get_offset(i32 %8)
  store i32 %call3, i32* %offset, align 4
  %9 = load i32* %idx, align 4
  %10 = load %struct._set_t** getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 7), align 4
  %arrayidx = getelementptr inbounds %struct._set_t* %10, i32 %9
  store %struct._set_t* %arrayidx, %struct._set_t** %set, align 4
  %11 = load %struct._set_t** %set, align 4
  %victim_counter4 = getelementptr inbounds %struct._set_t* %11, i32 0, i32 1
  %12 = load i32* %victim_counter4, align 4
  store i32 %12, i32* %victim_counter, align 4
  %13 = load i32* %addr, align 4
  %call5 = call i32 @get_blk_addr(i32 %13)
  %14 = inttoptr i32 %call5 to i8*
  store i8* %14, i8** %mem_blk_addr, align 4
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %if.end
  %15 = load i32* %i, align 4
  %16 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 0), align 4
  %cmp = icmp ult i32 %15, %16
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %17 = load i32* %i, align 4
  %18 = load %struct._set_t** %set, align 4
  %blks = getelementptr inbounds %struct._set_t* %18, i32 0, i32 0
  %19 = load %struct._blk_t** %blks, align 4
  %arrayidx6 = getelementptr inbounds %struct._blk_t* %19, i32 %17
  %tag7 = getelementptr inbounds %struct._blk_t* %arrayidx6, i32 0, i32 1
  %20 = load i32* %tag7, align 4
  %21 = load i32* %tag, align 4
  %cmp8 = icmp eq i32 %20, %21
  br i1 %cmp8, label %if.then9, label %if.end12

if.then9:                                         ; preds = %for.body
  call void @Increament(%struct.StatsCounter* @hit_Stats)
  %22 = load i32* %i, align 4
  %23 = load %struct._set_t** %set, align 4
  %blks10 = getelementptr inbounds %struct._set_t* %23, i32 0, i32 0
  %24 = load %struct._blk_t** %blks10, align 4
  %arrayidx11 = getelementptr inbounds %struct._blk_t* %24, i32 %22
  store %struct._blk_t* %arrayidx11, %struct._blk_t** %blk, align 4
  br label %for.end

if.end12:                                         ; preds = %for.body
  br label %for.inc

for.inc:                                          ; preds = %if.end12
  %25 = load i32* %i, align 4
  %inc = add i32 %25, 1
  store i32 %inc, i32* %i, align 4
  br label %for.cond

for.end:                                          ; preds = %if.then9, %for.cond
  %26 = load %struct._blk_t** %blk, align 4
  %tobool13 = icmp ne %struct._blk_t* %26, null
  br i1 %tobool13, label %if.end27, label %if.then14

if.then14:                                        ; preds = %for.end
  store i32 0, i32* %i, align 4
  br label %for.cond15

for.cond15:                                       ; preds = %for.inc24, %if.then14
  %27 = load i32* %i, align 4
  %cmp16 = icmp ult i32 %27, 1024
  br i1 %cmp16, label %for.body17, label %for.end26

for.body17:                                       ; preds = %for.cond15
  %28 = load i32* %i, align 4
  %arrayidx18 = getelementptr inbounds [4 x %struct._blk_t]* @victim_buffer_blks, i32 0, i32 %28
  %mem_blk_addr19 = getelementptr inbounds %struct._blk_t* %arrayidx18, i32 0, i32 3
  %29 = load i8** %mem_blk_addr19, align 4
  %30 = load i8** %mem_blk_addr, align 4
  %cmp20 = icmp eq i8* %29, %30
  br i1 %cmp20, label %if.then21, label %if.end23

if.then21:                                        ; preds = %for.body17
  call void @Increament(%struct.StatsCounter* @victim_buffer_hit_Stats)
  %31 = load i32* %i, align 4
  %arrayidx22 = getelementptr inbounds [4 x %struct._blk_t]* @victim_buffer_blks, i32 0, i32 %31
  store %struct._blk_t* %arrayidx22, %struct._blk_t** %blk, align 4
  br label %for.end26

if.end23:                                         ; preds = %for.body17
  br label %for.inc24

for.inc24:                                        ; preds = %if.end23
  %32 = load i32* %i, align 4
  %inc25 = add i32 %32, 1
  store i32 %inc25, i32* %i, align 4
  br label %for.cond15

for.end26:                                        ; preds = %if.then21, %for.cond15
  br label %if.end27

if.end27:                                         ; preds = %for.end26, %for.end
  %33 = load %struct._blk_t** %blk, align 4
  %tobool28 = icmp ne %struct._blk_t* %33, null
  br i1 %tobool28, label %if.end67, label %if.then29

if.then29:                                        ; preds = %if.end27
  call void @Increament(%struct.StatsCounter* @miss_Stats)
  %34 = load i32* @nextVictimBlk, align 4
  %arrayidx30 = getelementptr inbounds [4 x %struct._blk_t]* @victim_buffer_blks, i32 0, i32 %34
  store %struct._blk_t* %arrayidx30, %struct._blk_t** %evict_blk, align 4
  %35 = load %struct._blk_t** %evict_blk, align 4
  %status = getelementptr inbounds %struct._blk_t* %35, i32 0, i32 0
  %36 = load i32* %status, align 4
  %cmp31 = icmp eq i32 %36, 4
  br i1 %cmp31, label %if.then32, label %if.else

if.then32:                                        ; preds = %if.then29
  call void @Increament(%struct.StatsCounter* @Dirty_Stats)
  %37 = load %struct._blk_t** %evict_blk, align 4
  %data = getelementptr inbounds %struct._blk_t* %37, i32 0, i32 2
  %38 = load i8** %data, align 4
  %39 = load %struct._blk_t** %evict_blk, align 4
  %mem_blk_addr33 = getelementptr inbounds %struct._blk_t* %39, i32 0, i32 3
  %40 = load i8** %mem_blk_addr33, align 4
  %call34 = call i32 @eviction_ftn(i8* %38, i8* %40)
  br label %if.end44

if.else:                                          ; preds = %if.then29
  %41 = load %struct._blk_t** %evict_blk, align 4
  %status35 = getelementptr inbounds %struct._blk_t* %41, i32 0, i32 0
  %42 = load i32* %status35, align 4
  %cmp36 = icmp eq i32 %42, 2
  br i1 %cmp36, label %if.then37, label %if.else38

if.then37:                                        ; preds = %if.else
  call void @Increament(%struct.StatsCounter* @NotDirty_Stats)
  br label %if.end43

if.else38:                                        ; preds = %if.else
  %43 = load %struct._blk_t** %evict_blk, align 4
  %status39 = getelementptr inbounds %struct._blk_t* %43, i32 0, i32 0
  %44 = load i32* %status39, align 4
  %cmp40 = icmp eq i32 %44, 1
  br i1 %cmp40, label %if.then41, label %if.end42

if.then41:                                        ; preds = %if.else38
  call void @Increament(%struct.StatsCounter* @NotValid_Stats)
  br label %if.end42

if.end42:                                         ; preds = %if.then41, %if.else38
  br label %if.end43

if.end43:                                         ; preds = %if.end42, %if.then37
  br label %if.end44

if.end44:                                         ; preds = %if.end43, %if.then32
  %45 = load i32* %victim_counter, align 4
  %46 = load %struct._set_t** %set, align 4
  %blks45 = getelementptr inbounds %struct._set_t* %46, i32 0, i32 0
  %47 = load %struct._blk_t** %blks45, align 4
  %arrayidx46 = getelementptr inbounds %struct._blk_t* %47, i32 %45
  store %struct._blk_t* %arrayidx46, %struct._blk_t** %blk, align 4
  %48 = load %struct._blk_t** %blk, align 4
  %status47 = getelementptr inbounds %struct._blk_t* %48, i32 0, i32 0
  %49 = load i32* %status47, align 4
  %cmp48 = icmp ne i32 %49, 1
  br i1 %cmp48, label %if.then49, label %if.end58

if.then49:                                        ; preds = %if.end44
  %50 = load %struct._blk_t** %evict_blk, align 4
  %data50 = getelementptr inbounds %struct._blk_t* %50, i32 0, i32 2
  %51 = load i8** %data50, align 4
  %52 = load %struct._blk_t** %blk, align 4
  %data51 = getelementptr inbounds %struct._blk_t* %52, i32 0, i32 2
  %53 = load i8** %data51, align 4
  call void @llvm.memcpy.p0i8.p0i8.i32(i8* %51, i8* %53, i32 256, i32 1, i1 false)
  %54 = load %struct._blk_t** %blk, align 4
  %status52 = getelementptr inbounds %struct._blk_t* %54, i32 0, i32 0
  %55 = load i32* %status52, align 4
  %56 = load %struct._blk_t** %evict_blk, align 4
  %status53 = getelementptr inbounds %struct._blk_t* %56, i32 0, i32 0
  store i32 %55, i32* %status53, align 4
  %57 = load %struct._blk_t** %blk, align 4
  %mem_blk_addr54 = getelementptr inbounds %struct._blk_t* %57, i32 0, i32 3
  %58 = load i8** %mem_blk_addr54, align 4
  %59 = load %struct._blk_t** %evict_blk, align 4
  %mem_blk_addr55 = getelementptr inbounds %struct._blk_t* %59, i32 0, i32 3
  store i8* %58, i8** %mem_blk_addr55, align 4
  %60 = load %struct._blk_t** %blk, align 4
  %tag56 = getelementptr inbounds %struct._blk_t* %60, i32 0, i32 1
  %61 = load i32* %tag56, align 4
  %62 = load %struct._blk_t** %evict_blk, align 4
  %tag57 = getelementptr inbounds %struct._blk_t* %62, i32 0, i32 1
  store i32 %61, i32* %tag57, align 4
  call void @Increament(%struct.StatsCounter* @MoveToVB_Stats)
  %63 = load i32* @nextVictimBlk, align 4
  %add = add i32 %63, 1
  %rem = urem i32 %add, 4
  store i32 %rem, i32* @nextVictimBlk, align 4
  br label %if.end58

if.end58:                                         ; preds = %if.then49, %if.end44
  %64 = load i32* %tag, align 4
  %65 = load %struct._blk_t** %blk, align 4
  %tag59 = getelementptr inbounds %struct._blk_t* %65, i32 0, i32 1
  store i32 %64, i32* %tag59, align 4
  %66 = load i8** %mem_blk_addr, align 4
  %67 = load %struct._blk_t** %blk, align 4
  %mem_blk_addr60 = getelementptr inbounds %struct._blk_t* %67, i32 0, i32 3
  store i8* %66, i8** %mem_blk_addr60, align 4
  %68 = load %struct._blk_t** %blk, align 4
  %data61 = getelementptr inbounds %struct._blk_t* %68, i32 0, i32 2
  %69 = load i8** %data61, align 4
  %70 = load i8** %mem_blk_addr, align 4
  %call62 = call i32 @fetch_ftn(i8* %69, i8* %70)
  %71 = load %struct._blk_t** %blk, align 4
  %status63 = getelementptr inbounds %struct._blk_t* %71, i32 0, i32 0
  store i32 2, i32* %status63, align 4
  %72 = load i32* %victim_counter, align 4
  %add64 = add i32 %72, 1
  %73 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 0), align 4
  %rem65 = urem i32 %add64, %73
  %74 = load %struct._set_t** %set, align 4
  %victim_counter66 = getelementptr inbounds %struct._set_t* %74, i32 0, i32 1
  store i32 %rem65, i32* %victim_counter66, align 4
  br label %if.end67

if.end67:                                         ; preds = %if.end58, %if.end27
  %75 = load i32* %opcode.addr, align 4
  %cmp68 = icmp eq i32 %75, 2
  br i1 %cmp68, label %if.then69, label %if.end71

if.then69:                                        ; preds = %if.end67
  %76 = load %struct._blk_t** %blk, align 4
  %status70 = getelementptr inbounds %struct._blk_t* %76, i32 0, i32 0
  store i32 4, i32* %status70, align 4
  call void @Increament(%struct.StatsCounter* @Writes_Stats)
  br label %if.end71

if.end71:                                         ; preds = %if.then69, %if.end67
  %77 = load %struct._blk_t** %blk, align 4
  %data72 = getelementptr inbounds %struct._blk_t* %77, i32 0, i32 2
  %78 = load i8** %data72, align 4
  %79 = load i32* %offset, align 4
  %add.ptr = getelementptr inbounds i8* %78, i32 %79
  store i8* %add.ptr, i8** %rtnptr, align 4
  %80 = load i8** %rtnptr, align 4
  %81 = load i32* %dataSize.addr, align 4
  %add.ptr73 = getelementptr inbounds i8* %80, i32 %81
  store i8* %add.ptr73, i8** %p, align 4
  %82 = load %struct._blk_t** %blk, align 4
  %data74 = getelementptr inbounds %struct._blk_t* %82, i32 0, i32 2
  %83 = load i8** %data74, align 4
  %add.ptr75 = getelementptr inbounds i8* %83, i32 256
  store i8* %add.ptr75, i8** %bEnd, align 4
  %84 = load i8** %p, align 4
  %85 = load i8** %bEnd, align 4
  %cmp76 = icmp ugt i8* %84, %85
  br i1 %cmp76, label %if.then77, label %if.end80

if.then77:                                        ; preds = %if.end71
  %86 = load %struct._IO_FILE** @_reportFile, align 4
  %87 = load i8** %rtnptr, align 4
  %88 = load i32* %dataSize.addr, align 4
  %89 = load i8** %bEnd, align 4
  %90 = load i8** %p, align 4
  %91 = load i8** %p, align 4
  %92 = load i8** %bEnd, align 4
  %sub.ptr.lhs.cast = ptrtoint i8* %91 to i32
  %sub.ptr.rhs.cast = ptrtoint i8* %92 to i32
  %sub.ptr.sub = sub i32 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast
  %call78 = call i32 (%struct._IO_FILE*, i8*, ...)* @fprintf(%struct._IO_FILE* %86, i8* getelementptr inbounds ([34 x i8]* @.str21, i32 0, i32 0), i8* %87, i32 %88, i8* %89, i8* %90, i32 %sub.ptr.sub)
  %93 = load %struct._IO_FILE** @_reportFile, align 4
  %call79 = call i32 @fflush(%struct._IO_FILE* %93)
  call void @Increament(%struct.StatsCounter* @DataOverFlows_Stats)
  br label %if.end80

if.end80:                                         ; preds = %if.then77, %if.end71
  %94 = load i8** %rtnptr, align 4
  %95 = bitcast i8* %94 to i32*
  store i32* %95, i32** %retval
  br label %return

return:                                           ; preds = %if.end80, %if.then
  %96 = load i32** %retval
  ret i32* %96
}

declare i32 @isHeapAddr(i8*) #1

; Function Attrs: nounwind
declare double @pow(double, double) #0

; Function Attrs: nounwind readnone
declare double @ceil(double) #5

; Function Attrs: inlinehint nounwind
define internal i32 @next_power_of_2(i32 %num) #6 {
entry:
  %num.addr = alloca i32, align 4
  store i32 %num, i32* %num.addr, align 4
  %0 = load i32* %num.addr, align 4
  %conv = uitofp i32 %0 to double
  %call = call double @log2(double %conv) #4
  %call1 = call double @ceil(double %call) #7
  %call2 = call double @pow(double 2.000000e+00, double %call1) #4
  %conv3 = fptoui double %call2 to i32
  ret i32 %conv3
}

; Function Attrs: inlinehint nounwind
define internal i32 @get_tag(i32 %addr) #6 {
entry:
  %addr.addr = alloca i32, align 4
  store i32 %addr, i32* %addr.addr, align 4
  %0 = load i32* %addr.addr, align 4
  %1 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 6), align 4
  %2 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 5), align 4
  %add = add i32 %1, %2
  %shr = lshr i32 %0, %add
  ret i32 %shr
}

; Function Attrs: inlinehint nounwind
define internal i32 @get_index(i32 %addr) #6 {
entry:
  %addr.addr = alloca i32, align 4
  store i32 %addr, i32* %addr.addr, align 4
  %0 = load i32* %addr.addr, align 4
  %1 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 4), align 4
  %shl = shl i32 %0, %1
  %2 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 4), align 4
  %3 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 6), align 4
  %add = add i32 %2, %3
  %shr = lshr i32 %shl, %add
  ret i32 %shr
}

; Function Attrs: inlinehint nounwind
define internal i32 @get_offset(i32 %addr) #6 {
entry:
  %addr.addr = alloca i32, align 4
  %len = alloca i32, align 4
  store i32 %addr, i32* %addr.addr, align 4
  %0 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 4), align 4
  %1 = load i32* getelementptr inbounds (%struct._cache_t* @_hcache, i32 0, i32 5), align 4
  %add = add i32 %0, %1
  store i32 %add, i32* %len, align 4
  %2 = load i32* %addr.addr, align 4
  %3 = load i32* %len, align 4
  %shl = shl i32 %2, %3
  %4 = load i32* %len, align 4
  %shr = lshr i32 %shl, %4
  ret i32 %shr
}

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="true" }
attributes #1 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="true" }
attributes #2 = { alwaysinline nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="true" }
attributes #3 = { noinline nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="true" }
attributes #4 = { nounwind }
attributes #5 = { nounwind readnone "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="true" }
attributes #6 = { inlinehint nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="true" }
attributes #7 = { nounwind readnone }

!llvm.ident = !{!0, !0, !0, !0}
!llvm.module.flags = !{!1, !2}

!0 = metadata !{metadata !"clang version 3.6.0 (trunk)"}
!1 = metadata !{i32 1, metadata !"wchar_size", i32 4}
!2 = metadata !{i32 1, metadata !"min_enum_size", i32 4}
!3 = metadata !{i32 -2147025809}
!4 = metadata !{i32 -2147025722}
