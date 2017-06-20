; ModuleID = 'printf.c'
target datalayout = "e-m:e-p:32:32-i64:64-v128:64:128-a:0:32-n32-S64"
target triple = "thumbv7--linux-gnueabihf"

%struct.__va_list = type { i8* }
%union.anon = type { i8* }

@main.shortstr = internal global [5 x i8] c"Test\00", align 1
@.str = private unnamed_addr constant [31 x i8] c" Hello %s world day is %d %u  \00", align 1
@.str1 = private unnamed_addr constant [5 x i8] c"guys\00", align 1
@.str2 = private unnamed_addr constant [30 x i8] c"percent:                \22%%\22\0A\00", align 1
@.str3 = private unnamed_addr constant [30 x i8] c"bad format:             \22%z\22\0A\00", align 1
@.str4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str5 = private unnamed_addr constant [30 x i8] c"decimal:                \22%d\22\0A\00", align 1
@.str6 = private unnamed_addr constant [30 x i8] c"decimal negative:       \22%d\22\0A\00", align 1
@.str7 = private unnamed_addr constant [30 x i8] c"unsigned:               \22%u\22\0A\00", align 1
@.str8 = private unnamed_addr constant [30 x i8] c"unsigned negative:      \22%u\22\0A\00", align 1
@.str9 = private unnamed_addr constant [30 x i8] c"hex:                    \22%x\22\0A\00", align 1
@.str10 = private unnamed_addr constant [30 x i8] c"hex negative:           \22%x\22\0A\00", align 1
@.str11 = private unnamed_addr constant [31 x i8] c"long decimal:           \22%ld\22\0A\00", align 1
@.str12 = private unnamed_addr constant [31 x i8] c"long decimal negative:  \22%ld\22\0A\00", align 1
@.str13 = private unnamed_addr constant [31 x i8] c"long unsigned:          \22%lu\22\0A\00", align 1
@.str14 = private unnamed_addr constant [31 x i8] c"long unsigned negative: \22%lu\22\0A\00", align 1
@.str15 = private unnamed_addr constant [30 x i8] c"long hex:               \22%x\22\0A\00", align 1
@.str16 = private unnamed_addr constant [30 x i8] c"long hex negative:      \22%x\22\0A\00", align 1
@.str17 = private unnamed_addr constant [34 x i8] c"zero-padded LD:         \22%010ld\22\0A\00", align 1
@.str18 = private unnamed_addr constant [34 x i8] c"zero-padded LDN:        \22%010ld\22\0A\00", align 1
@.str19 = private unnamed_addr constant [35 x i8] c"left-adjusted ZLDN:     \22%-010ld\22\0A\00", align 1
@.str20 = private unnamed_addr constant [33 x i8] c"space-padded LDN:       \22%10ld\22\0A\00", align 1
@.str21 = private unnamed_addr constant [34 x i8] c"left-adjusted SLDN:     \22%-10ld\22\0A\00", align 1
@.str22 = private unnamed_addr constant [32 x i8] c"variable pad width:     \22%0*d\22\0A\00", align 1
@.str23 = private unnamed_addr constant [36 x i8] c"char:                   \22%c%c%c%c\22\0A\00", align 1
@.str24 = private unnamed_addr constant [33 x i8] c"zero-padded string:     \22%010s\22\0A\00", align 1
@.str25 = private unnamed_addr constant [34 x i8] c"left-adjusted Z string: \22%-010s\22\0A\00", align 1
@.str26 = private unnamed_addr constant [32 x i8] c"space-padded string:    \22%10s\22\0A\00", align 1
@.str27 = private unnamed_addr constant [33 x i8] c"left-adjusted S string: \22%-10s\22\0A\00", align 1
@.str28 = private unnamed_addr constant [30 x i8] c"null string:            \22%s\22\0A\00", align 1
@.str29 = private unnamed_addr constant [15 x i8] c"decimal:\09\22%d\22\0A\00", align 1
@.str30 = private unnamed_addr constant [12 x i8] c"sprintf: %s\00", align 1
@.str31 = private unnamed_addr constant [7 x i8] c"(null)\00", align 1

; Function Attrs: nounwind
define i32 @simple_printf(i8* %fmt, ...) #0 {
entry:
  %fmt.addr = alloca i8*, align 4
  %ap = alloca %struct.__va_list, align 4
  %r = alloca i32, align 4
  store i8* %fmt, i8** %fmt.addr, align 4
  %ap1 = bitcast %struct.__va_list* %ap to i8*
  call void @llvm.va_start(i8* %ap1)
  %0 = load i8** %fmt.addr, align 4
  %coerce.dive = getelementptr %struct.__va_list* %ap, i32 0, i32 0
  %1 = bitcast i8** %coerce.dive to { [1 x i32] }*
  %2 = load { [1 x i32] }* %1, align 1
  %call = call i32 @simple_vsprintf(i8** null, i8* %0, { [1 x i32] } %2)
  store i32 %call, i32* %r, align 4
  %ap2 = bitcast %struct.__va_list* %ap to i8*
  call void @llvm.va_end(i8* %ap2)
  %3 = load i32* %r, align 4
  ret i32 %3
}

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #1

; Function Attrs: nounwind
define internal i32 @simple_vsprintf(i8** %out, i8* %format, { [1 x i32] } %ap.coerce) #0 {
entry:
  %ap = alloca %struct.__va_list, align 4
  %out.addr = alloca i8**, align 4
  %format.addr = alloca i8*, align 4
  %width = alloca i32, align 4
  %flags = alloca i32, align 4
  %pc = alloca i32, align 4
  %scr = alloca [2 x i8], align 1
  %u = alloca %union.anon, align 4
  %coerce.dive = getelementptr %struct.__va_list* %ap, i32 0, i32 0
  %0 = bitcast i8** %coerce.dive to { [1 x i32] }*
  %1 = getelementptr { [1 x i32] }* %0, i32 0, i32 0
  %2 = extractvalue { [1 x i32] } %ap.coerce, 0
  store [1 x i32] %2, [1 x i32]* %1, align 1
  store i8** %out, i8*** %out.addr, align 4
  store i8* %format, i8** %format.addr, align 4
  store i32 0, i32* %pc, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc91, %entry
  %3 = load i8** %format.addr, align 4
  %4 = load i8* %3, align 1
  %conv = zext i8 %4 to i32
  %cmp = icmp ne i32 %conv, 0
  br i1 %cmp, label %for.body, label %for.end93

for.body:                                         ; preds = %for.cond
  %5 = load i8** %format.addr, align 4
  %6 = load i8* %5, align 1
  %conv2 = zext i8 %6 to i32
  %cmp3 = icmp eq i32 %conv2, 37
  br i1 %cmp3, label %if.then, label %if.else88

if.then:                                          ; preds = %for.body
  %7 = load i8** %format.addr, align 4
  %incdec.ptr = getelementptr inbounds i8* %7, i32 1
  store i8* %incdec.ptr, i8** %format.addr, align 4
  store i32 0, i32* %flags, align 4
  store i32 0, i32* %width, align 4
  %8 = load i8** %format.addr, align 4
  %9 = load i8* %8, align 1
  %conv5 = zext i8 %9 to i32
  %cmp6 = icmp eq i32 %conv5, 0
  br i1 %cmp6, label %if.then8, label %if.end

if.then8:                                         ; preds = %if.then
  br label %for.end93

if.end:                                           ; preds = %if.then
  %10 = load i8** %format.addr, align 4
  %11 = load i8* %10, align 1
  %conv9 = zext i8 %11 to i32
  %cmp10 = icmp eq i32 %conv9, 37
  br i1 %cmp10, label %if.then12, label %if.end13

if.then12:                                        ; preds = %if.end
  br label %out89

if.end13:                                         ; preds = %if.end
  %12 = load i8** %format.addr, align 4
  %13 = load i8* %12, align 1
  %conv14 = zext i8 %13 to i32
  %cmp15 = icmp eq i32 %conv14, 45
  br i1 %cmp15, label %if.then17, label %if.end19

if.then17:                                        ; preds = %if.end13
  %14 = load i8** %format.addr, align 4
  %incdec.ptr18 = getelementptr inbounds i8* %14, i32 1
  store i8* %incdec.ptr18, i8** %format.addr, align 4
  store i32 2, i32* %flags, align 4
  br label %if.end19

if.end19:                                         ; preds = %if.then17, %if.end13
  br label %while.cond

while.cond:                                       ; preds = %while.body, %if.end19
  %15 = load i8** %format.addr, align 4
  %16 = load i8* %15, align 1
  %conv20 = zext i8 %16 to i32
  %cmp21 = icmp eq i32 %conv20, 48
  br i1 %cmp21, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %17 = load i8** %format.addr, align 4
  %incdec.ptr23 = getelementptr inbounds i8* %17, i32 1
  store i8* %incdec.ptr23, i8** %format.addr, align 4
  %18 = load i32* %flags, align 4
  %or = or i32 %18, 1
  store i32 %or, i32* %flags, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %19 = load i8** %format.addr, align 4
  %20 = load i8* %19, align 1
  %conv24 = zext i8 %20 to i32
  %cmp25 = icmp eq i32 %conv24, 42
  br i1 %cmp25, label %if.then27, label %if.else

if.then27:                                        ; preds = %while.end
  %ap28 = bitcast %struct.__va_list* %ap to i8**
  %ap.cur = load i8** %ap28
  %ap.next = getelementptr i8* %ap.cur, i32 4
  store i8* %ap.next, i8** %ap28
  %21 = bitcast i8* %ap.cur to i32*
  %22 = load i32* %21
  store i32 %22, i32* %width, align 4
  %23 = load i8** %format.addr, align 4
  %incdec.ptr29 = getelementptr inbounds i8* %23, i32 1
  store i8* %incdec.ptr29, i8** %format.addr, align 4
  br label %if.end40

if.else:                                          ; preds = %while.end
  br label %for.cond30

for.cond30:                                       ; preds = %for.inc, %if.else
  %24 = load i8** %format.addr, align 4
  %25 = load i8* %24, align 1
  %conv31 = zext i8 %25 to i32
  %cmp32 = icmp sge i32 %conv31, 48
  br i1 %cmp32, label %land.rhs, label %land.end

land.rhs:                                         ; preds = %for.cond30
  %26 = load i8** %format.addr, align 4
  %27 = load i8* %26, align 1
  %conv34 = zext i8 %27 to i32
  %cmp35 = icmp sle i32 %conv34, 57
  br label %land.end

land.end:                                         ; preds = %land.rhs, %for.cond30
  %28 = phi i1 [ false, %for.cond30 ], [ %cmp35, %land.rhs ]
  br i1 %28, label %for.body37, label %for.end

for.body37:                                       ; preds = %land.end
  %29 = load i32* %width, align 4
  %mul = mul nsw i32 %29, 10
  store i32 %mul, i32* %width, align 4
  %30 = load i8** %format.addr, align 4
  %31 = load i8* %30, align 1
  %conv38 = zext i8 %31 to i32
  %sub = sub nsw i32 %conv38, 48
  %32 = load i32* %width, align 4
  %add = add nsw i32 %32, %sub
  store i32 %add, i32* %width, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body37
  %33 = load i8** %format.addr, align 4
  %incdec.ptr39 = getelementptr inbounds i8* %33, i32 1
  store i8* %incdec.ptr39, i8** %format.addr, align 4
  br label %for.cond30

for.end:                                          ; preds = %land.end
  br label %if.end40

if.end40:                                         ; preds = %for.end, %if.then27
  %34 = load i8** %format.addr, align 4
  %35 = load i8* %34, align 1
  %conv41 = zext i8 %35 to i32
  switch i32 %conv41, label %sw.default [
    i32 100, label %sw.bb
    i32 117, label %sw.bb47
    i32 120, label %sw.bb55
    i32 88, label %sw.bb63
    i32 99, label %sw.bb71
    i32 115, label %sw.bb80
  ]

sw.bb:                                            ; preds = %if.end40
  %ap42 = bitcast %struct.__va_list* %ap to i8**
  %ap.cur43 = load i8** %ap42
  %ap.next44 = getelementptr i8* %ap.cur43, i32 4
  store i8* %ap.next44, i8** %ap42
  %36 = bitcast i8* %ap.cur43 to i32*
  %37 = load i32* %36
  %i = bitcast %union.anon* %u to i32*
  store i32 %37, i32* %i, align 4
  %38 = load i8*** %out.addr, align 4
  %i45 = bitcast %union.anon* %u to i32*
  %39 = load i32* %i45, align 4
  %40 = load i32* %width, align 4
  %41 = load i32* %flags, align 4
  %call = call i32 @simple_outputi(i8** %38, i32 %39, i32 10, i32 1, i32 %40, i32 %41, i32 97)
  %42 = load i32* %pc, align 4
  %add46 = add nsw i32 %42, %call
  store i32 %add46, i32* %pc, align 4
  br label %sw.epilog

sw.bb47:                                          ; preds = %if.end40
  %ap48 = bitcast %struct.__va_list* %ap to i8**
  %ap.cur49 = load i8** %ap48
  %ap.next50 = getelementptr i8* %ap.cur49, i32 4
  store i8* %ap.next50, i8** %ap48
  %43 = bitcast i8* %ap.cur49 to i32*
  %44 = load i32* %43
  %u51 = bitcast %union.anon* %u to i32*
  store i32 %44, i32* %u51, align 4
  %45 = load i8*** %out.addr, align 4
  %u52 = bitcast %union.anon* %u to i32*
  %46 = load i32* %u52, align 4
  %47 = load i32* %width, align 4
  %48 = load i32* %flags, align 4
  %call53 = call i32 @simple_outputi(i8** %45, i32 %46, i32 10, i32 0, i32 %47, i32 %48, i32 97)
  %49 = load i32* %pc, align 4
  %add54 = add nsw i32 %49, %call53
  store i32 %add54, i32* %pc, align 4
  br label %sw.epilog

sw.bb55:                                          ; preds = %if.end40
  %ap56 = bitcast %struct.__va_list* %ap to i8**
  %ap.cur57 = load i8** %ap56
  %ap.next58 = getelementptr i8* %ap.cur57, i32 4
  store i8* %ap.next58, i8** %ap56
  %50 = bitcast i8* %ap.cur57 to i32*
  %51 = load i32* %50
  %u59 = bitcast %union.anon* %u to i32*
  store i32 %51, i32* %u59, align 4
  %52 = load i8*** %out.addr, align 4
  %u60 = bitcast %union.anon* %u to i32*
  %53 = load i32* %u60, align 4
  %54 = load i32* %width, align 4
  %55 = load i32* %flags, align 4
  %call61 = call i32 @simple_outputi(i8** %52, i32 %53, i32 16, i32 0, i32 %54, i32 %55, i32 97)
  %56 = load i32* %pc, align 4
  %add62 = add nsw i32 %56, %call61
  store i32 %add62, i32* %pc, align 4
  br label %sw.epilog

sw.bb63:                                          ; preds = %if.end40
  %ap64 = bitcast %struct.__va_list* %ap to i8**
  %ap.cur65 = load i8** %ap64
  %ap.next66 = getelementptr i8* %ap.cur65, i32 4
  store i8* %ap.next66, i8** %ap64
  %57 = bitcast i8* %ap.cur65 to i32*
  %58 = load i32* %57
  %u67 = bitcast %union.anon* %u to i32*
  store i32 %58, i32* %u67, align 4
  %59 = load i8*** %out.addr, align 4
  %u68 = bitcast %union.anon* %u to i32*
  %60 = load i32* %u68, align 4
  %61 = load i32* %width, align 4
  %62 = load i32* %flags, align 4
  %call69 = call i32 @simple_outputi(i8** %59, i32 %60, i32 16, i32 0, i32 %61, i32 %62, i32 65)
  %63 = load i32* %pc, align 4
  %add70 = add nsw i32 %63, %call69
  store i32 %add70, i32* %pc, align 4
  br label %sw.epilog

sw.bb71:                                          ; preds = %if.end40
  %ap72 = bitcast %struct.__va_list* %ap to i8**
  %ap.cur73 = load i8** %ap72
  %ap.next74 = getelementptr i8* %ap.cur73, i32 4
  store i8* %ap.next74, i8** %ap72
  %64 = bitcast i8* %ap.cur73 to i32*
  %65 = load i32* %64
  %conv75 = trunc i32 %65 to i8
  %c = bitcast %union.anon* %u to i8*
  store i8 %conv75, i8* %c, align 1
  %c76 = bitcast %union.anon* %u to i8*
  %66 = load i8* %c76, align 1
  %arrayidx = getelementptr inbounds [2 x i8]* %scr, i32 0, i32 0
  store i8 %66, i8* %arrayidx, align 1
  %arrayidx77 = getelementptr inbounds [2 x i8]* %scr, i32 0, i32 1
  store i8 0, i8* %arrayidx77, align 1
  %67 = load i8*** %out.addr, align 4
  %arraydecay = getelementptr inbounds [2 x i8]* %scr, i32 0, i32 0
  %68 = load i32* %width, align 4
  %69 = load i32* %flags, align 4
  %call78 = call i32 @prints(i8** %67, i8* %arraydecay, i32 %68, i32 %69)
  %70 = load i32* %pc, align 4
  %add79 = add nsw i32 %70, %call78
  store i32 %add79, i32* %pc, align 4
  br label %sw.epilog

sw.bb80:                                          ; preds = %if.end40
  %ap81 = bitcast %struct.__va_list* %ap to i8**
  %ap.cur82 = load i8** %ap81
  %ap.next83 = getelementptr i8* %ap.cur82, i32 4
  store i8* %ap.next83, i8** %ap81
  %71 = bitcast i8* %ap.cur82 to i8**
  %72 = load i8** %71
  %s = bitcast %union.anon* %u to i8**
  store i8* %72, i8** %s, align 4
  %73 = load i8*** %out.addr, align 4
  %s84 = bitcast %union.anon* %u to i8**
  %74 = load i8** %s84, align 4
  %tobool = icmp ne i8* %74, null
  br i1 %tobool, label %cond.true, label %cond.false

cond.true:                                        ; preds = %sw.bb80
  %s85 = bitcast %union.anon* %u to i8**
  %75 = load i8** %s85, align 4
  br label %cond.end

cond.false:                                       ; preds = %sw.bb80
  br label %cond.end

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i8* [ %75, %cond.true ], [ getelementptr inbounds ([7 x i8]* @.str31, i32 0, i32 0), %cond.false ]
  %76 = load i32* %width, align 4
  %77 = load i32* %flags, align 4
  %call86 = call i32 @prints(i8** %73, i8* %cond, i32 %76, i32 %77)
  %78 = load i32* %pc, align 4
  %add87 = add nsw i32 %78, %call86
  store i32 %add87, i32* %pc, align 4
  br label %sw.epilog

sw.default:                                       ; preds = %if.end40
  br label %sw.epilog

sw.epilog:                                        ; preds = %sw.default, %cond.end, %sw.bb71, %sw.bb63, %sw.bb55, %sw.bb47, %sw.bb
  br label %if.end90

if.else88:                                        ; preds = %for.body
  br label %out89

out89:                                            ; preds = %if.else88, %if.then12
  %79 = load i8*** %out.addr, align 4
  %80 = load i8** %format.addr, align 4
  %81 = load i8* %80, align 1
  call void @simple_outputchar(i8** %79, i8 zeroext %81)
  %82 = load i32* %pc, align 4
  %inc = add nsw i32 %82, 1
  store i32 %inc, i32* %pc, align 4
  br label %if.end90

if.end90:                                         ; preds = %out89, %sw.epilog
  br label %for.inc91

for.inc91:                                        ; preds = %if.end90
  %83 = load i8** %format.addr, align 4
  %incdec.ptr92 = getelementptr inbounds i8* %83, i32 1
  store i8* %incdec.ptr92, i8** %format.addr, align 4
  br label %for.cond

for.end93:                                        ; preds = %if.then8, %for.cond
  %84 = load i8*** %out.addr, align 4
  %tobool94 = icmp ne i8** %84, null
  br i1 %tobool94, label %if.then95, label %if.end96

if.then95:                                        ; preds = %for.end93
  %85 = load i8*** %out.addr, align 4
  %86 = load i8** %85, align 4
  store i8 0, i8* %86, align 1
  br label %if.end96

if.end96:                                         ; preds = %if.then95, %for.end93
  %87 = load i32* %pc, align 4
  ret i32 %87
}

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #1

; Function Attrs: nounwind
define i32 @simple_sprintf(i8* %buf, i8* %fmt, ...) #0 {
entry:
  %buf.addr = alloca i8*, align 4
  %fmt.addr = alloca i8*, align 4
  %ap = alloca %struct.__va_list, align 4
  %r = alloca i32, align 4
  store i8* %buf, i8** %buf.addr, align 4
  store i8* %fmt, i8** %fmt.addr, align 4
  %ap1 = bitcast %struct.__va_list* %ap to i8*
  call void @llvm.va_start(i8* %ap1)
  %0 = load i8** %fmt.addr, align 4
  %coerce.dive = getelementptr %struct.__va_list* %ap, i32 0, i32 0
  %1 = bitcast i8** %coerce.dive to { [1 x i32] }*
  %2 = load { [1 x i32] }* %1, align 1
  %call = call i32 @simple_vsprintf(i8** %buf.addr, i8* %0, { [1 x i32] } %2)
  store i32 %call, i32* %r, align 4
  %ap2 = bitcast %struct.__va_list* %ap to i8*
  call void @llvm.va_end(i8* %ap2)
  %3 = load i32* %r, align 4
  ret i32 %3
}

; Function Attrs: nounwind
define i32 @main(i32 %argc, i8** %argv) #0 {
entry:
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 4
  %buf = alloca [256 x i8], align 1
  store i32 %argc, i32* %argc.addr, align 4
  store i8** %argv, i8*** %argv.addr, align 4
  %call = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([31 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8]* @.str1, i32 0, i32 0), i32 17, i32 3)
  %call1 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([30 x i8]* @.str2, i32 0, i32 0))
  %call2 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([30 x i8]* @.str3, i32 0, i32 0))
  %call3 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([2 x i8]* @.str4, i32 0, i32 0))
  %call4 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([30 x i8]* @.str5, i32 0, i32 0), i32 12345)
  %call5 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([30 x i8]* @.str6, i32 0, i32 0), i32 -2345)
  %call6 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([2 x i8]* @.str4, i32 0, i32 0))
  %call7 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([30 x i8]* @.str7, i32 0, i32 0), i32 12345)
  %call8 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([30 x i8]* @.str8, i32 0, i32 0), i32 -2345)
  %call9 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([2 x i8]* @.str4, i32 0, i32 0))
  %call10 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([30 x i8]* @.str9, i32 0, i32 0), i32 74565)
  %call11 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([30 x i8]* @.str10, i32 0, i32 0), i32 -74565)
  %call12 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([2 x i8]* @.str4, i32 0, i32 0))
  %call13 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([31 x i8]* @.str11, i32 0, i32 0), i32 123456)
  %call14 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([31 x i8]* @.str12, i32 0, i32 0), i32 -23456)
  %call15 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([2 x i8]* @.str4, i32 0, i32 0))
  %call16 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([31 x i8]* @.str13, i32 0, i32 0), i32 123456)
  %call17 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([31 x i8]* @.str14, i32 0, i32 0), i32 -123456)
  %call18 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([2 x i8]* @.str4, i32 0, i32 0))
  %call19 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([30 x i8]* @.str15, i32 0, i32 0), i32 74565)
  %call20 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([30 x i8]* @.str16, i32 0, i32 0), i32 -74565)
  %call21 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([2 x i8]* @.str4, i32 0, i32 0))
  %call22 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([34 x i8]* @.str17, i32 0, i32 0), i32 123456)
  %call23 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([34 x i8]* @.str18, i32 0, i32 0), i32 -123456)
  %call24 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([35 x i8]* @.str19, i32 0, i32 0), i32 -123456)
  %call25 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([33 x i8]* @.str20, i32 0, i32 0), i32 -123456)
  %call26 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([34 x i8]* @.str21, i32 0, i32 0), i32 -123456)
  %call27 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([2 x i8]* @.str4, i32 0, i32 0))
  %call28 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([32 x i8]* @.str22, i32 0, i32 0), i32 15, i32 -2345)
  %call29 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([2 x i8]* @.str4, i32 0, i32 0))
  %call30 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([36 x i8]* @.str23, i32 0, i32 0), i32 84, i32 101, i32 115, i32 116)
  %call31 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([2 x i8]* @.str4, i32 0, i32 0))
  %call32 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([33 x i8]* @.str24, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8]* @main.shortstr, i32 0, i32 0))
  %call33 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([34 x i8]* @.str25, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8]* @main.shortstr, i32 0, i32 0))
  %call34 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([32 x i8]* @.str26, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8]* @main.shortstr, i32 0, i32 0))
  %call35 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([33 x i8]* @.str27, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8]* @main.shortstr, i32 0, i32 0))
  %call36 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([30 x i8]* @.str28, i32 0, i32 0), i8* null)
  %arraydecay = getelementptr inbounds [256 x i8]* %buf, i32 0, i32 0
  %call37 = call i32 (i8*, i8*, ...)* @simple_sprintf(i8* %arraydecay, i8* getelementptr inbounds ([15 x i8]* @.str29, i32 0, i32 0), i32 -2345)
  %arraydecay38 = getelementptr inbounds [256 x i8]* %buf, i32 0, i32 0
  %call39 = call i32 (i8*, ...)* @simple_printf(i8* getelementptr inbounds ([12 x i8]* @.str30, i32 0, i32 0), i8* %arraydecay38)
  ret i32 0
}

; Function Attrs: nounwind
define internal i32 @simple_outputi(i8** %out, i32 %i, i32 %base, i32 %sign, i32 %width, i32 %flags, i32 %letbase) #0 {
entry:
  %retval = alloca i32, align 4
  %out.addr = alloca i8**, align 4
  %i.addr = alloca i32, align 4
  %base.addr = alloca i32, align 4
  %sign.addr = alloca i32, align 4
  %width.addr = alloca i32, align 4
  %flags.addr = alloca i32, align 4
  %letbase.addr = alloca i32, align 4
  %print_buf = alloca [64 x i8], align 1
  %s = alloca i8*, align 4
  %t = alloca i32, align 4
  %neg = alloca i32, align 4
  %pc = alloca i32, align 4
  %u = alloca i32, align 4
  store i8** %out, i8*** %out.addr, align 4
  store i32 %i, i32* %i.addr, align 4
  store i32 %base, i32* %base.addr, align 4
  store i32 %sign, i32* %sign.addr, align 4
  store i32 %width, i32* %width.addr, align 4
  store i32 %flags, i32* %flags.addr, align 4
  store i32 %letbase, i32* %letbase.addr, align 4
  store i32 0, i32* %neg, align 4
  store i32 0, i32* %pc, align 4
  %0 = load i32* %i.addr, align 4
  store i32 %0, i32* %u, align 4
  %1 = load i32* %i.addr, align 4
  %cmp = icmp eq i32 %1, 0
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %arrayidx = getelementptr inbounds [64 x i8]* %print_buf, i32 0, i32 0
  store i8 48, i8* %arrayidx, align 1
  %arrayidx1 = getelementptr inbounds [64 x i8]* %print_buf, i32 0, i32 1
  store i8 0, i8* %arrayidx1, align 1
  %2 = load i8*** %out.addr, align 4
  %arraydecay = getelementptr inbounds [64 x i8]* %print_buf, i32 0, i32 0
  %3 = load i32* %width.addr, align 4
  %4 = load i32* %flags.addr, align 4
  %call = call i32 @prints(i8** %2, i8* %arraydecay, i32 %3, i32 %4)
  store i32 %call, i32* %retval
  br label %return

if.end:                                           ; preds = %entry
  %5 = load i32* %sign.addr, align 4
  %tobool = icmp ne i32 %5, 0
  br i1 %tobool, label %land.lhs.true, label %if.end6

land.lhs.true:                                    ; preds = %if.end
  %6 = load i32* %base.addr, align 4
  %cmp2 = icmp eq i32 %6, 10
  br i1 %cmp2, label %land.lhs.true3, label %if.end6

land.lhs.true3:                                   ; preds = %land.lhs.true
  %7 = load i32* %i.addr, align 4
  %cmp4 = icmp slt i32 %7, 0
  br i1 %cmp4, label %if.then5, label %if.end6

if.then5:                                         ; preds = %land.lhs.true3
  store i32 1, i32* %neg, align 4
  %8 = load i32* %i.addr, align 4
  %sub = sub nsw i32 0, %8
  store i32 %sub, i32* %u, align 4
  br label %if.end6

if.end6:                                          ; preds = %if.then5, %land.lhs.true3, %land.lhs.true, %if.end
  %arraydecay7 = getelementptr inbounds [64 x i8]* %print_buf, i32 0, i32 0
  %add.ptr = getelementptr inbounds i8* %arraydecay7, i32 64
  %add.ptr8 = getelementptr inbounds i8* %add.ptr, i32 -1
  store i8* %add.ptr8, i8** %s, align 4
  %9 = load i8** %s, align 4
  store i8 0, i8* %9, align 1
  br label %while.cond

while.cond:                                       ; preds = %if.end14, %if.end6
  %10 = load i32* %u, align 4
  %tobool9 = icmp ne i32 %10, 0
  br i1 %tobool9, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %11 = load i32* %u, align 4
  %12 = load i32* %base.addr, align 4
  %rem = urem i32 %11, %12
  store i32 %rem, i32* %t, align 4
  %13 = load i32* %t, align 4
  %cmp10 = icmp sge i32 %13, 10
  br i1 %cmp10, label %if.then11, label %if.end14

if.then11:                                        ; preds = %while.body
  %14 = load i32* %letbase.addr, align 4
  %sub12 = sub nsw i32 %14, 48
  %sub13 = sub nsw i32 %sub12, 10
  %15 = load i32* %t, align 4
  %add = add nsw i32 %15, %sub13
  store i32 %add, i32* %t, align 4
  br label %if.end14

if.end14:                                         ; preds = %if.then11, %while.body
  %16 = load i32* %t, align 4
  %add15 = add nsw i32 %16, 48
  %conv = trunc i32 %add15 to i8
  %17 = load i8** %s, align 4
  %incdec.ptr = getelementptr inbounds i8* %17, i32 -1
  store i8* %incdec.ptr, i8** %s, align 4
  store i8 %conv, i8* %incdec.ptr, align 1
  %18 = load i32* %base.addr, align 4
  %19 = load i32* %u, align 4
  %div = udiv i32 %19, %18
  store i32 %div, i32* %u, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %20 = load i32* %neg, align 4
  %tobool16 = icmp ne i32 %20, 0
  br i1 %tobool16, label %if.then17, label %if.end24

if.then17:                                        ; preds = %while.end
  %21 = load i32* %width.addr, align 4
  %tobool18 = icmp ne i32 %21, 0
  br i1 %tobool18, label %land.lhs.true19, label %if.else

land.lhs.true19:                                  ; preds = %if.then17
  %22 = load i32* %flags.addr, align 4
  %and = and i32 %22, 1
  %tobool20 = icmp ne i32 %and, 0
  br i1 %tobool20, label %if.then21, label %if.else

if.then21:                                        ; preds = %land.lhs.true19
  %23 = load i8*** %out.addr, align 4
  call void @simple_outputchar(i8** %23, i8 zeroext 45)
  %24 = load i32* %pc, align 4
  %inc = add nsw i32 %24, 1
  store i32 %inc, i32* %pc, align 4
  %25 = load i32* %width.addr, align 4
  %dec = add nsw i32 %25, -1
  store i32 %dec, i32* %width.addr, align 4
  br label %if.end23

if.else:                                          ; preds = %land.lhs.true19, %if.then17
  %26 = load i8** %s, align 4
  %incdec.ptr22 = getelementptr inbounds i8* %26, i32 -1
  store i8* %incdec.ptr22, i8** %s, align 4
  store i8 45, i8* %incdec.ptr22, align 1
  br label %if.end23

if.end23:                                         ; preds = %if.else, %if.then21
  br label %if.end24

if.end24:                                         ; preds = %if.end23, %while.end
  %27 = load i32* %pc, align 4
  %28 = load i8*** %out.addr, align 4
  %29 = load i8** %s, align 4
  %30 = load i32* %width.addr, align 4
  %31 = load i32* %flags.addr, align 4
  %call25 = call i32 @prints(i8** %28, i8* %29, i32 %30, i32 %31)
  %add26 = add nsw i32 %27, %call25
  store i32 %add26, i32* %retval
  br label %return

return:                                           ; preds = %if.end24, %if.then
  %32 = load i32* %retval
  ret i32 %32
}

; Function Attrs: nounwind
define internal i32 @prints(i8** %out, i8* %string, i32 %width, i32 %flags) #0 {
entry:
  %out.addr = alloca i8**, align 4
  %string.addr = alloca i8*, align 4
  %width.addr = alloca i32, align 4
  %flags.addr = alloca i32, align 4
  %pc = alloca i32, align 4
  %padchar = alloca i32, align 4
  %len = alloca i32, align 4
  %ptr = alloca i8*, align 4
  store i8** %out, i8*** %out.addr, align 4
  store i8* %string, i8** %string.addr, align 4
  store i32 %width, i32* %width.addr, align 4
  store i32 %flags, i32* %flags.addr, align 4
  store i32 0, i32* %pc, align 4
  store i32 32, i32* %padchar, align 4
  %0 = load i32* %width.addr, align 4
  %cmp = icmp sgt i32 %0, 0
  br i1 %cmp, label %if.then, label %if.end6

if.then:                                          ; preds = %entry
  store i32 0, i32* %len, align 4
  %1 = load i8** %string.addr, align 4
  store i8* %1, i8** %ptr, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %if.then
  %2 = load i8** %ptr, align 4
  %3 = load i8* %2, align 1
  %tobool = icmp ne i8 %3, 0
  br i1 %tobool, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %4 = load i32* %len, align 4
  %inc = add nsw i32 %4, 1
  store i32 %inc, i32* %len, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %5 = load i8** %ptr, align 4
  %incdec.ptr = getelementptr inbounds i8* %5, i32 1
  store i8* %incdec.ptr, i8** %ptr, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %6 = load i32* %len, align 4
  %7 = load i32* %width.addr, align 4
  %cmp1 = icmp sge i32 %6, %7
  br i1 %cmp1, label %if.then2, label %if.else

if.then2:                                         ; preds = %for.end
  store i32 0, i32* %width.addr, align 4
  br label %if.end

if.else:                                          ; preds = %for.end
  %8 = load i32* %len, align 4
  %9 = load i32* %width.addr, align 4
  %sub = sub nsw i32 %9, %8
  store i32 %sub, i32* %width.addr, align 4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then2
  %10 = load i32* %flags.addr, align 4
  %and = and i32 %10, 1
  %tobool3 = icmp ne i32 %and, 0
  br i1 %tobool3, label %if.then4, label %if.end5

if.then4:                                         ; preds = %if.end
  store i32 48, i32* %padchar, align 4
  br label %if.end5

if.end5:                                          ; preds = %if.then4, %if.end
  br label %if.end6

if.end6:                                          ; preds = %if.end5, %entry
  %11 = load i32* %flags.addr, align 4
  %and7 = and i32 %11, 2
  %tobool8 = icmp ne i32 %and7, 0
  br i1 %tobool8, label %if.end16, label %if.then9

if.then9:                                         ; preds = %if.end6
  br label %for.cond10

for.cond10:                                       ; preds = %for.inc14, %if.then9
  %12 = load i32* %width.addr, align 4
  %cmp11 = icmp sgt i32 %12, 0
  br i1 %cmp11, label %for.body12, label %for.end15

for.body12:                                       ; preds = %for.cond10
  %13 = load i8*** %out.addr, align 4
  %14 = load i32* %padchar, align 4
  %conv = trunc i32 %14 to i8
  call void @simple_outputchar(i8** %13, i8 zeroext %conv)
  %15 = load i32* %pc, align 4
  %inc13 = add nsw i32 %15, 1
  store i32 %inc13, i32* %pc, align 4
  br label %for.inc14

for.inc14:                                        ; preds = %for.body12
  %16 = load i32* %width.addr, align 4
  %dec = add nsw i32 %16, -1
  store i32 %dec, i32* %width.addr, align 4
  br label %for.cond10

for.end15:                                        ; preds = %for.cond10
  br label %if.end16

if.end16:                                         ; preds = %for.end15, %if.end6
  br label %for.cond17

for.cond17:                                       ; preds = %for.inc21, %if.end16
  %17 = load i8** %string.addr, align 4
  %18 = load i8* %17, align 1
  %tobool18 = icmp ne i8 %18, 0
  br i1 %tobool18, label %for.body19, label %for.end23

for.body19:                                       ; preds = %for.cond17
  %19 = load i8*** %out.addr, align 4
  %20 = load i8** %string.addr, align 4
  %21 = load i8* %20, align 1
  call void @simple_outputchar(i8** %19, i8 zeroext %21)
  %22 = load i32* %pc, align 4
  %inc20 = add nsw i32 %22, 1
  store i32 %inc20, i32* %pc, align 4
  br label %for.inc21

for.inc21:                                        ; preds = %for.body19
  %23 = load i8** %string.addr, align 4
  %incdec.ptr22 = getelementptr inbounds i8* %23, i32 1
  store i8* %incdec.ptr22, i8** %string.addr, align 4
  br label %for.cond17

for.end23:                                        ; preds = %for.cond17
  br label %for.cond24

for.cond24:                                       ; preds = %for.inc30, %for.end23
  %24 = load i32* %width.addr, align 4
  %cmp25 = icmp sgt i32 %24, 0
  br i1 %cmp25, label %for.body27, label %for.end32

for.body27:                                       ; preds = %for.cond24
  %25 = load i8*** %out.addr, align 4
  %26 = load i32* %padchar, align 4
  %conv28 = trunc i32 %26 to i8
  call void @simple_outputchar(i8** %25, i8 zeroext %conv28)
  %27 = load i32* %pc, align 4
  %inc29 = add nsw i32 %27, 1
  store i32 %inc29, i32* %pc, align 4
  br label %for.inc30

for.inc30:                                        ; preds = %for.body27
  %28 = load i32* %width.addr, align 4
  %dec31 = add nsw i32 %28, -1
  store i32 %dec31, i32* %width.addr, align 4
  br label %for.cond24

for.end32:                                        ; preds = %for.cond24
  %29 = load i32* %pc, align 4
  ret i32 %29
}

; Function Attrs: nounwind
define internal void @simple_outputchar(i8** %str, i8 zeroext %c) #0 {
entry:
  %str.addr = alloca i8**, align 4
  %c.addr = alloca i8, align 1
  store i8** %str, i8*** %str.addr, align 4
  store i8 %c, i8* %c.addr, align 1
  %0 = load i8*** %str.addr, align 4
  %tobool = icmp ne i8** %0, null
  br i1 %tobool, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %1 = load i8* %c.addr, align 1
  %2 = load i8*** %str.addr, align 4
  %3 = load i8** %2, align 4
  store i8 %1, i8* %3, align 1
  %4 = load i8*** %str.addr, align 4
  %5 = load i8** %4, align 4
  %incdec.ptr = getelementptr inbounds i8* %5, i32 1
  store i8* %incdec.ptr, i8** %4, align 4
  br label %if.end

if.else:                                          ; preds = %entry
  %6 = load i8* %c.addr, align 1
  %conv = zext i8 %6 to i32
  %call = call i32 @putchar(i32 %conv)
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void
}

declare i32 @putchar(i32) #2

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind }
attributes #2 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = metadata !{i32 1, metadata !"wchar_size", i32 4}
!1 = metadata !{i32 1, metadata !"min_enum_size", i32 4}
!2 = metadata !{metadata !"clang version 3.6.0 (trunk)"}
