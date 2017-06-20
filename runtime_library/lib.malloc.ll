; ModuleID = 'malloc.c'
target datalayout = "e-m:e-p:32:32-i64:64-v128:64:128-a:0:32-n32-S64"
target triple = "thumbv7--linux-gnueabihf"

%struct.StatsCounter = type { i32, i32, [256 x i8] }
%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i32, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i32, i32, [40 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }

@mallocCalls_Stats = weak global %struct.StatsCounter { i32 0, i32 0, [256 x i8] c"No of calls to Malloc\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@freeCalls_Stats = weak global %struct.StatsCounter { i32 0, i32 0, [256 x i8] c"No. of calls to Free\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@addrTrans_Stats = weak global %struct.StatsCounter { i32 0, i32 0, [256 x i8] c"No. of address translation attempts\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@not_heap_addr_Stats = weak global %struct.StatsCounter { i32 0, i32 0, [256 x i8] c"No. of addresses not located in heap allocations\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@in_heap_addr_Stats = weak global %struct.StatsCounter { i32 0, i32 0, [256 x i8] c"No. of addresses located in heap allocations, requiring translation\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@miss_Stats = weak global %struct.StatsCounter { i32 0, i32 0, [256 x i8] c"No. of miss in spm heap mgt, causes eviction and fetch\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@hit_Stats = weak global %struct.StatsCounter zeroinitializer, align 4
@victim_buffer_hit_Stats = weak global %struct.StatsCounter zeroinitializer, align 4
@dma_MEM2SPM_Stats = weak global %struct.StatsCounter zeroinitializer, align 4
@Evictions_Stats = weak global %struct.StatsCounter zeroinitializer, align 4
@NotDirty_Stats = weak global %struct.StatsCounter zeroinitializer, align 4
@heapbit_flips_Stats = weak global %struct.StatsCounter zeroinitializer, align 4
@stack2mem_Stats = weak global %struct.StatsCounter { i32 0, i32 0, [256 x i8] c"No. of times whole stack in SPM is dumped to NVMM\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@mem2stack_Stats = weak global %struct.StatsCounter { i32 0, i32 0, [256 x i8] c"No. of times saved stack data is restored back to SPM\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@MemUpdate_Stats = weak global %struct.StatsCounter { i32 0, i32 0, [256 x i8] c"Total bytes written to NVMM\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@min_sp_Stats = weak global %struct.StatsCounter { i32 0, i32 0, [256 x i8] c"Min. size of whole stack dumped to NVMM\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@max_sp_Stats = weak global %struct.StatsCounter { i32 0, i32 0, [256 x i8] c"Max. size of whole stack dumped to NVMM\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@stackbit_flips_Stats = weak global %struct.StatsCounter zeroinitializer, align 4
@CodeFetch_Stats = weak global %struct.StatsCounter { i32 0, i32 0, [256 x i8] c"No. of times code is fetched from NVMM to SPM\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@InstCount_Stats = weak global %struct.StatsCounter { i32 0, i32 0, [256 x i8] c"No. of Instructions read from NVMM to SPM\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00" }, align 4
@usedPtr = global i32 0, align 4
@nvmmHeapSpace = common global i8* null, align 4
@nvmmHeapSpace_break = common global i8* null, align 4
@first_mem_blk = common global i8* null, align 4
@_reportFile = external global %struct._IO_FILE*
@.str = private unnamed_addr constant [59 x i8] c"\0A    NVMM { 0x%p ~~ 0x%p [%u] , First_blk:%p, padSize:%u }\00", align 1
@_debugFILE = external global %struct._IO_FILE*
@.str1 = private unnamed_addr constant [32 x i8] c" Error : Malloc space exceeded \00", align 1
@.str2 = private unnamed_addr constant [31 x i8] c"\0A[malloc {ptr:%p , size:%u} ] \00", align 1
@last_mem_blk = common global i8* null, align 4
@mem_blks_allocated = common global i32 0, align 4

; Function Attrs: nounwind
define void @init_spm_malloc() #0 {
entry:
  %call = call i8* @nvmmMalloc(i32 16777216)
  store i8* %call, i8** @nvmmHeapSpace, align 4
  %0 = load i8** @nvmmHeapSpace, align 4
  %add.ptr = getelementptr inbounds i8* %0, i32 16777215
  store i8* %add.ptr, i8** @nvmmHeapSpace_break, align 4
  %1 = load i8** @nvmmHeapSpace, align 4
  %2 = ptrtoint i8* %1 to i32
  %call1 = call i32 @get_blk_addr(i32 %2)
  %3 = inttoptr i32 %call1 to i8*
  %add.ptr2 = getelementptr inbounds i8* %3, i32 512
  store i8* %add.ptr2, i8** @first_mem_blk, align 4
  %4 = load i8** @first_mem_blk, align 4
  %5 = load i8** @nvmmHeapSpace, align 4
  %sub.ptr.lhs.cast = ptrtoint i8* %4 to i32
  %sub.ptr.rhs.cast = ptrtoint i8* %5 to i32
  %sub.ptr.sub = sub i32 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast
  %6 = load i32* @usedPtr, align 4
  %add = add i32 %6, %sub.ptr.sub
  store i32 %add, i32* @usedPtr, align 4
  %7 = load %struct._IO_FILE** @_reportFile, align 4
  %8 = load i8** @nvmmHeapSpace, align 4
  %9 = load i8** @nvmmHeapSpace_break, align 4
  %10 = load i8** @first_mem_blk, align 4
  %11 = load i8** @first_mem_blk, align 4
  %12 = load i8** @nvmmHeapSpace, align 4
  %sub.ptr.lhs.cast3 = ptrtoint i8* %11 to i32
  %sub.ptr.rhs.cast4 = ptrtoint i8* %12 to i32
  %sub.ptr.sub5 = sub i32 %sub.ptr.lhs.cast3, %sub.ptr.rhs.cast4
  %call6 = call i32 (%struct._IO_FILE*, i8*, ...)* @fprintf(%struct._IO_FILE* %7, i8* getelementptr inbounds ([59 x i8]* @.str, i32 0, i32 0), i8* %8, i8* %9, i32 16777216, i8* %10, i32 %sub.ptr.sub5)
  %13 = load %struct._IO_FILE** @_reportFile, align 4
  %call7 = call i32 @fflush(%struct._IO_FILE* %13)
  ret void
}

declare i8* @nvmmMalloc(i32) #1

declare i32 @get_blk_addr(i32) #1

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #1

declare i32 @fflush(%struct._IO_FILE*) #1

; Function Attrs: nounwind
define i8* @_malloc(i32 %size) #0 {
entry:
  %size.addr = alloca i32, align 4
  %rtn = alloca i8*, align 4
  store i32 %size, i32* %size.addr, align 4
  call void @Increament(%struct.StatsCounter* @mallocCalls_Stats)
  %0 = load i32* @usedPtr, align 4
  %1 = load i8** @nvmmHeapSpace, align 4
  %arrayidx = getelementptr inbounds i8* %1, i32 %0
  store i8* %arrayidx, i8** %rtn, align 4
  %2 = load i32* %size.addr, align 4
  %3 = load i32* @usedPtr, align 4
  %add = add i32 %3, %2
  store i32 %add, i32* @usedPtr, align 4
  %4 = load i32* @usedPtr, align 4
  %cmp = icmp ugt i32 %4, 16777216
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %5 = load %struct._IO_FILE** @_debugFILE, align 4
  %call = call i32 (%struct._IO_FILE*, i8*, ...)* @fprintf(%struct._IO_FILE* %5, i8* getelementptr inbounds ([32 x i8]* @.str1, i32 0, i32 0))
  %6 = load %struct._IO_FILE** @_debugFILE, align 4
  %call1 = call i32 @fflush(%struct._IO_FILE* %6)
  call void @exit(i32 -1) #3
  unreachable

if.end:                                           ; preds = %entry
  %7 = load %struct._IO_FILE** @_debugFILE, align 4
  %8 = load i8** %rtn, align 4
  %9 = load i32* %size.addr, align 4
  %call2 = call i32 (%struct._IO_FILE*, i8*, ...)* @fprintf(%struct._IO_FILE* %7, i8* getelementptr inbounds ([31 x i8]* @.str2, i32 0, i32 0), i8* %8, i32 %9)
  %10 = load %struct._IO_FILE** @_debugFILE, align 4
  %call3 = call i32 @fflush(%struct._IO_FILE* %10)
  %11 = load i8** %rtn, align 4
  ret i8* %11
}

declare void @Increament(%struct.StatsCounter*) #1

; Function Attrs: noreturn nounwind
declare void @exit(i32) #2

; Function Attrs: nounwind
define void @_free(i8* %ptr) #0 {
entry:
  %ptr.addr = alloca i8*, align 4
  store i8* %ptr, i8** %ptr.addr, align 4
  call void @Increament(%struct.StatsCounter* @freeCalls_Stats)
  ret void
}

; Function Attrs: nounwind
define i32 @isHeapAddr(i8* %gAddr) #0 {
entry:
  %retval = alloca i32, align 4
  %gAddr.addr = alloca i8*, align 4
  store i8* %gAddr, i8** %gAddr.addr, align 4
  %0 = load i8** @first_mem_blk, align 4
  %1 = load i8** %gAddr.addr, align 4
  %cmp = icmp ult i8* %0, %1
  br i1 %cmp, label %land.lhs.true, label %if.end

land.lhs.true:                                    ; preds = %entry
  %2 = load i8** %gAddr.addr, align 4
  %3 = load i8** @nvmmHeapSpace_break, align 4
  %cmp1 = icmp ult i8* %2, %3
  br i1 %cmp1, label %if.then, label %if.end

if.then:                                          ; preds = %land.lhs.true
  store i32 1, i32* %retval
  br label %return

if.end:                                           ; preds = %land.lhs.true, %entry
  store i32 0, i32* %retval
  br label %return

return:                                           ; preds = %if.end, %if.then
  %4 = load i32* %retval
  ret i32 %4
}

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { noreturn nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = metadata !{i32 1, metadata !"wchar_size", i32 4}
!1 = metadata !{i32 1, metadata !"min_enum_size", i32 4}
!2 = metadata !{metadata !"clang version 3.6.0 (trunk)"}
