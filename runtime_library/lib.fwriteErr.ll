; ModuleID = 'fwriteErr.c'
target datalayout = "e-m:e-p:32:32-i64:64-v128:64:128-a:0:32-n32-S64"
target triple = "thumbv7--linux-gnueabihf"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i32, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i32, i32, [40 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%union.anon = type { i8* }

@currentVargFrame = global i32* null, align 4
@fwriteErrVarArg = common global [1024 x i8] zeroinitializer, align 1
@.str = private unnamed_addr constant [7 x i8] c"(null)\00", align 1
@stderr = external global %struct._IO_FILE*

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
  store i32* bitcast ([1024 x i8]* @fwriteErrVarArg to i32*), i32** %ptr, align 4
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
define void @restore(i32* %VargFramePtr) #0 {
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
define i32 @_fwriteErrStream__(i8* %format, i32* %VargPtr) #0 {
entry:
  %format.addr = alloca i8*, align 4
  %VargPtr.addr = alloca i32*, align 4
  %width = alloca i32, align 4
  %flags = alloca i32, align 4
  %pc = alloca i32, align 4
  %scr = alloca [2 x i8], align 1
  %u = alloca %union.anon, align 4
  store i8* %format, i8** %format.addr, align 4
  store i32* %VargPtr, i32** %VargPtr.addr, align 4
  store i32 0, i32* %pc, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc80, %entry
  %0 = load i8** %format.addr, align 4
  %1 = load i8* %0, align 1
  %conv = zext i8 %1 to i32
  %cmp = icmp ne i32 %conv, 0
  br i1 %cmp, label %for.body, label %for.end82

for.body:                                         ; preds = %for.cond
  %2 = load i8** %format.addr, align 4
  %3 = load i8* %2, align 1
  %conv2 = zext i8 %3 to i32
  %cmp3 = icmp eq i32 %conv2, 37
  br i1 %cmp3, label %if.then, label %if.else76

if.then:                                          ; preds = %for.body
  %4 = load i8** %format.addr, align 4
  %incdec.ptr = getelementptr inbounds i8* %4, i32 1
  store i8* %incdec.ptr, i8** %format.addr, align 4
  store i32 0, i32* %flags, align 4
  store i32 0, i32* %width, align 4
  %5 = load i8** %format.addr, align 4
  %6 = load i8* %5, align 1
  %conv5 = zext i8 %6 to i32
  %cmp6 = icmp eq i32 %conv5, 0
  br i1 %cmp6, label %if.then8, label %if.end

if.then8:                                         ; preds = %if.then
  br label %for.end82

if.end:                                           ; preds = %if.then
  %7 = load i8** %format.addr, align 4
  %8 = load i8* %7, align 1
  %conv9 = zext i8 %8 to i32
  %cmp10 = icmp eq i32 %conv9, 37
  br i1 %cmp10, label %if.then12, label %if.end13

if.then12:                                        ; preds = %if.end
  br label %out

if.end13:                                         ; preds = %if.end
  %9 = load i8** %format.addr, align 4
  %10 = load i8* %9, align 1
  %conv14 = zext i8 %10 to i32
  %cmp15 = icmp eq i32 %conv14, 45
  br i1 %cmp15, label %if.then17, label %if.end19

if.then17:                                        ; preds = %if.end13
  %11 = load i8** %format.addr, align 4
  %incdec.ptr18 = getelementptr inbounds i8* %11, i32 1
  store i8* %incdec.ptr18, i8** %format.addr, align 4
  store i32 2, i32* %flags, align 4
  br label %if.end19

if.end19:                                         ; preds = %if.then17, %if.end13
  br label %while.cond

while.cond:                                       ; preds = %while.body, %if.end19
  %12 = load i8** %format.addr, align 4
  %13 = load i8* %12, align 1
  %conv20 = zext i8 %13 to i32
  %cmp21 = icmp eq i32 %conv20, 48
  br i1 %cmp21, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %14 = load i8** %format.addr, align 4
  %incdec.ptr23 = getelementptr inbounds i8* %14, i32 1
  store i8* %incdec.ptr23, i8** %format.addr, align 4
  %15 = load i32* %flags, align 4
  %or = or i32 %15, 1
  store i32 %or, i32* %flags, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %16 = load i8** %format.addr, align 4
  %17 = load i8* %16, align 1
  %conv24 = zext i8 %17 to i32
  %cmp25 = icmp eq i32 %conv24, 42
  br i1 %cmp25, label %if.then27, label %if.else

if.then27:                                        ; preds = %while.end
  %18 = load i32** %VargPtr.addr, align 4
  %call = call i32 @getNext(i32* %18, i32 4)
  store i32 %call, i32* %width, align 4
  %19 = load i8** %format.addr, align 4
  %incdec.ptr28 = getelementptr inbounds i8* %19, i32 1
  store i8* %incdec.ptr28, i8** %format.addr, align 4
  br label %if.end39

if.else:                                          ; preds = %while.end
  br label %for.cond29

for.cond29:                                       ; preds = %for.inc, %if.else
  %20 = load i8** %format.addr, align 4
  %21 = load i8* %20, align 1
  %conv30 = zext i8 %21 to i32
  %cmp31 = icmp sge i32 %conv30, 48
  br i1 %cmp31, label %land.rhs, label %land.end

land.rhs:                                         ; preds = %for.cond29
  %22 = load i8** %format.addr, align 4
  %23 = load i8* %22, align 1
  %conv33 = zext i8 %23 to i32
  %cmp34 = icmp sle i32 %conv33, 57
  br label %land.end

land.end:                                         ; preds = %land.rhs, %for.cond29
  %24 = phi i1 [ false, %for.cond29 ], [ %cmp34, %land.rhs ]
  br i1 %24, label %for.body36, label %for.end

for.body36:                                       ; preds = %land.end
  %25 = load i32* %width, align 4
  %mul = mul nsw i32 %25, 10
  store i32 %mul, i32* %width, align 4
  %26 = load i8** %format.addr, align 4
  %27 = load i8* %26, align 1
  %conv37 = zext i8 %27 to i32
  %sub = sub nsw i32 %conv37, 48
  %28 = load i32* %width, align 4
  %add = add nsw i32 %28, %sub
  store i32 %add, i32* %width, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body36
  %29 = load i8** %format.addr, align 4
  %incdec.ptr38 = getelementptr inbounds i8* %29, i32 1
  store i8* %incdec.ptr38, i8** %format.addr, align 4
  br label %for.cond29

for.end:                                          ; preds = %land.end
  br label %if.end39

if.end39:                                         ; preds = %for.end, %if.then27
  %30 = load i8** %format.addr, align 4
  %31 = load i8* %30, align 1
  %conv40 = zext i8 %31 to i32
  switch i32 %conv40, label %sw.default [
    i32 100, label %sw.bb
    i32 117, label %sw.bb45
    i32 120, label %sw.bb51
    i32 88, label %sw.bb57
    i32 99, label %sw.bb63
    i32 115, label %sw.bb70
  ]

sw.bb:                                            ; preds = %if.end39
  %32 = load i32** %VargPtr.addr, align 4
  %call41 = call i32 @getNext(i32* %32, i32 4)
  %i = bitcast %union.anon* %u to i32*
  store i32 %call41, i32* %i, align 4
  %i42 = bitcast %union.anon* %u to i32*
  %33 = load i32* %i42, align 4
  %34 = load i32* %width, align 4
  %35 = load i32* %flags, align 4
  %call43 = call i32 @simple_outputi(i32 %33, i32 10, i32 1, i32 %34, i32 %35, i32 97)
  %36 = load i32* %pc, align 4
  %add44 = add nsw i32 %36, %call43
  store i32 %add44, i32* %pc, align 4
  br label %sw.epilog

sw.bb45:                                          ; preds = %if.end39
  %37 = load i32** %VargPtr.addr, align 4
  %call46 = call i32 @getNext(i32* %37, i32 4)
  %u47 = bitcast %union.anon* %u to i32*
  store i32 %call46, i32* %u47, align 4
  %u48 = bitcast %union.anon* %u to i32*
  %38 = load i32* %u48, align 4
  %39 = load i32* %width, align 4
  %40 = load i32* %flags, align 4
  %call49 = call i32 @simple_outputi(i32 %38, i32 10, i32 0, i32 %39, i32 %40, i32 97)
  %41 = load i32* %pc, align 4
  %add50 = add nsw i32 %41, %call49
  store i32 %add50, i32* %pc, align 4
  br label %sw.epilog

sw.bb51:                                          ; preds = %if.end39
  %42 = load i32** %VargPtr.addr, align 4
  %call52 = call i32 @getNext(i32* %42, i32 4)
  %u53 = bitcast %union.anon* %u to i32*
  store i32 %call52, i32* %u53, align 4
  %u54 = bitcast %union.anon* %u to i32*
  %43 = load i32* %u54, align 4
  %44 = load i32* %width, align 4
  %45 = load i32* %flags, align 4
  %call55 = call i32 @simple_outputi(i32 %43, i32 16, i32 0, i32 %44, i32 %45, i32 97)
  %46 = load i32* %pc, align 4
  %add56 = add nsw i32 %46, %call55
  store i32 %add56, i32* %pc, align 4
  br label %sw.epilog

sw.bb57:                                          ; preds = %if.end39
  %47 = load i32** %VargPtr.addr, align 4
  %call58 = call i32 @getNext(i32* %47, i32 4)
  %u59 = bitcast %union.anon* %u to i32*
  store i32 %call58, i32* %u59, align 4
  %u60 = bitcast %union.anon* %u to i32*
  %48 = load i32* %u60, align 4
  %49 = load i32* %width, align 4
  %50 = load i32* %flags, align 4
  %call61 = call i32 @simple_outputi(i32 %48, i32 16, i32 0, i32 %49, i32 %50, i32 65)
  %51 = load i32* %pc, align 4
  %add62 = add nsw i32 %51, %call61
  store i32 %add62, i32* %pc, align 4
  br label %sw.epilog

sw.bb63:                                          ; preds = %if.end39
  %52 = load i32** %VargPtr.addr, align 4
  %call64 = call i32 @getNext(i32* %52, i32 4)
  %conv65 = trunc i32 %call64 to i8
  %c = bitcast %union.anon* %u to i8*
  store i8 %conv65, i8* %c, align 1
  %c66 = bitcast %union.anon* %u to i8*
  %53 = load i8* %c66, align 1
  %arrayidx = getelementptr inbounds [2 x i8]* %scr, i32 0, i32 0
  store i8 %53, i8* %arrayidx, align 1
  %arrayidx67 = getelementptr inbounds [2 x i8]* %scr, i32 0, i32 1
  store i8 0, i8* %arrayidx67, align 1
  %arraydecay = getelementptr inbounds [2 x i8]* %scr, i32 0, i32 0
  %54 = load i32* %width, align 4
  %55 = load i32* %flags, align 4
  %call68 = call i32 @prints(i8* %arraydecay, i32 %54, i32 %55)
  %56 = load i32* %pc, align 4
  %add69 = add nsw i32 %56, %call68
  store i32 %add69, i32* %pc, align 4
  br label %sw.epilog

sw.bb70:                                          ; preds = %if.end39
  %57 = load i32** %VargPtr.addr, align 4
  %call71 = call i32 @getNext(i32* %57, i32 4)
  %58 = inttoptr i32 %call71 to i8*
  %s = bitcast %union.anon* %u to i8**
  store i8* %58, i8** %s, align 4
  %s72 = bitcast %union.anon* %u to i8**
  %59 = load i8** %s72, align 4
  %tobool = icmp ne i8* %59, null
  br i1 %tobool, label %cond.true, label %cond.false

cond.true:                                        ; preds = %sw.bb70
  %s73 = bitcast %union.anon* %u to i8**
  %60 = load i8** %s73, align 4
  br label %cond.end

cond.false:                                       ; preds = %sw.bb70
  br label %cond.end

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i8* [ %60, %cond.true ], [ getelementptr inbounds ([7 x i8]* @.str, i32 0, i32 0), %cond.false ]
  %61 = load i32* %width, align 4
  %62 = load i32* %flags, align 4
  %call74 = call i32 @prints(i8* %cond, i32 %61, i32 %62)
  %63 = load i32* %pc, align 4
  %add75 = add nsw i32 %63, %call74
  store i32 %add75, i32* %pc, align 4
  br label %sw.epilog

sw.default:                                       ; preds = %if.end39
  br label %sw.epilog

sw.epilog:                                        ; preds = %sw.default, %cond.end, %sw.bb63, %sw.bb57, %sw.bb51, %sw.bb45, %sw.bb
  br label %if.end79

if.else76:                                        ; preds = %for.body
  br label %out

out:                                              ; preds = %if.else76, %if.then12
  %64 = load i8** %format.addr, align 4
  %65 = load i8* %64, align 1
  %conv77 = zext i8 %65 to i32
  %66 = load %struct._IO_FILE** @stderr, align 4
  %call78 = call i32 @_IO_putc(i32 %conv77, %struct._IO_FILE* %66)
  %67 = load i32* %pc, align 4
  %inc = add nsw i32 %67, 1
  store i32 %inc, i32* %pc, align 4
  br label %if.end79

if.end79:                                         ; preds = %out, %sw.epilog
  br label %for.inc80

for.inc80:                                        ; preds = %if.end79
  %68 = load i8** %format.addr, align 4
  %incdec.ptr81 = getelementptr inbounds i8* %68, i32 1
  store i8* %incdec.ptr81, i8** %format.addr, align 4
  br label %for.cond

for.end82:                                        ; preds = %if.then8, %for.cond
  %69 = load i32* %pc, align 4
  ret i32 %69
}

; Function Attrs: nounwind
define internal i32 @simple_outputi(i32 %i, i32 %base, i32 %sign, i32 %width, i32 %flags, i32 %letbase) #0 {
entry:
  %retval = alloca i32, align 4
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
  %arraydecay = getelementptr inbounds [64 x i8]* %print_buf, i32 0, i32 0
  %2 = load i32* %width.addr, align 4
  %3 = load i32* %flags.addr, align 4
  %call = call i32 @prints(i8* %arraydecay, i32 %2, i32 %3)
  store i32 %call, i32* %retval
  br label %return

if.end:                                           ; preds = %entry
  %4 = load i32* %sign.addr, align 4
  %tobool = icmp ne i32 %4, 0
  br i1 %tobool, label %land.lhs.true, label %if.end6

land.lhs.true:                                    ; preds = %if.end
  %5 = load i32* %base.addr, align 4
  %cmp2 = icmp eq i32 %5, 10
  br i1 %cmp2, label %land.lhs.true3, label %if.end6

land.lhs.true3:                                   ; preds = %land.lhs.true
  %6 = load i32* %i.addr, align 4
  %cmp4 = icmp slt i32 %6, 0
  br i1 %cmp4, label %if.then5, label %if.end6

if.then5:                                         ; preds = %land.lhs.true3
  store i32 1, i32* %neg, align 4
  %7 = load i32* %i.addr, align 4
  %sub = sub nsw i32 0, %7
  store i32 %sub, i32* %u, align 4
  br label %if.end6

if.end6:                                          ; preds = %if.then5, %land.lhs.true3, %land.lhs.true, %if.end
  %arraydecay7 = getelementptr inbounds [64 x i8]* %print_buf, i32 0, i32 0
  %add.ptr = getelementptr inbounds i8* %arraydecay7, i32 64
  %add.ptr8 = getelementptr inbounds i8* %add.ptr, i32 -1
  store i8* %add.ptr8, i8** %s, align 4
  %8 = load i8** %s, align 4
  store i8 0, i8* %8, align 1
  br label %while.cond

while.cond:                                       ; preds = %if.end14, %if.end6
  %9 = load i32* %u, align 4
  %tobool9 = icmp ne i32 %9, 0
  br i1 %tobool9, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %10 = load i32* %u, align 4
  %11 = load i32* %base.addr, align 4
  %rem = urem i32 %10, %11
  store i32 %rem, i32* %t, align 4
  %12 = load i32* %t, align 4
  %cmp10 = icmp sge i32 %12, 10
  br i1 %cmp10, label %if.then11, label %if.end14

if.then11:                                        ; preds = %while.body
  %13 = load i32* %letbase.addr, align 4
  %sub12 = sub nsw i32 %13, 48
  %sub13 = sub nsw i32 %sub12, 10
  %14 = load i32* %t, align 4
  %add = add nsw i32 %14, %sub13
  store i32 %add, i32* %t, align 4
  br label %if.end14

if.end14:                                         ; preds = %if.then11, %while.body
  %15 = load i32* %t, align 4
  %add15 = add nsw i32 %15, 48
  %conv = trunc i32 %add15 to i8
  %16 = load i8** %s, align 4
  %incdec.ptr = getelementptr inbounds i8* %16, i32 -1
  store i8* %incdec.ptr, i8** %s, align 4
  store i8 %conv, i8* %incdec.ptr, align 1
  %17 = load i32* %base.addr, align 4
  %18 = load i32* %u, align 4
  %div = udiv i32 %18, %17
  store i32 %div, i32* %u, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %19 = load i32* %neg, align 4
  %tobool16 = icmp ne i32 %19, 0
  br i1 %tobool16, label %if.then17, label %if.end25

if.then17:                                        ; preds = %while.end
  %20 = load i32* %width.addr, align 4
  %tobool18 = icmp ne i32 %20, 0
  br i1 %tobool18, label %land.lhs.true19, label %if.else

land.lhs.true19:                                  ; preds = %if.then17
  %21 = load i32* %flags.addr, align 4
  %and = and i32 %21, 1
  %tobool20 = icmp ne i32 %and, 0
  br i1 %tobool20, label %if.then21, label %if.else

if.then21:                                        ; preds = %land.lhs.true19
  %22 = load %struct._IO_FILE** @stderr, align 4
  %call22 = call i32 @_IO_putc(i32 45, %struct._IO_FILE* %22)
  %23 = load i32* %pc, align 4
  %inc = add nsw i32 %23, 1
  store i32 %inc, i32* %pc, align 4
  %24 = load i32* %width.addr, align 4
  %dec = add nsw i32 %24, -1
  store i32 %dec, i32* %width.addr, align 4
  br label %if.end24

if.else:                                          ; preds = %land.lhs.true19, %if.then17
  %25 = load i8** %s, align 4
  %incdec.ptr23 = getelementptr inbounds i8* %25, i32 -1
  store i8* %incdec.ptr23, i8** %s, align 4
  store i8 45, i8* %incdec.ptr23, align 1
  br label %if.end24

if.end24:                                         ; preds = %if.else, %if.then21
  br label %if.end25

if.end25:                                         ; preds = %if.end24, %while.end
  %26 = load i32* %pc, align 4
  %27 = load i8** %s, align 4
  %28 = load i32* %width.addr, align 4
  %29 = load i32* %flags.addr, align 4
  %call26 = call i32 @prints(i8* %27, i32 %28, i32 %29)
  %add27 = add nsw i32 %26, %call26
  store i32 %add27, i32* %retval
  br label %return

return:                                           ; preds = %if.end25, %if.then
  %30 = load i32* %retval
  ret i32 %30
}

; Function Attrs: nounwind
define internal i32 @prints(i8* %string, i32 %width, i32 %flags) #0 {
entry:
  %string.addr = alloca i8*, align 4
  %width.addr = alloca i32, align 4
  %flags.addr = alloca i32, align 4
  %pc = alloca i32, align 4
  %padchar = alloca i32, align 4
  %len = alloca i32, align 4
  %ptr = alloca i8*, align 4
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
  %13 = load i32* %padchar, align 4
  %14 = load %struct._IO_FILE** @stderr, align 4
  %call = call i32 @_IO_putc(i32 %13, %struct._IO_FILE* %14)
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

for.cond17:                                       ; preds = %for.inc22, %if.end16
  %17 = load i8** %string.addr, align 4
  %18 = load i8* %17, align 1
  %tobool18 = icmp ne i8 %18, 0
  br i1 %tobool18, label %for.body19, label %for.end24

for.body19:                                       ; preds = %for.cond17
  %19 = load i8** %string.addr, align 4
  %20 = load i8* %19, align 1
  %conv = zext i8 %20 to i32
  %21 = load %struct._IO_FILE** @stderr, align 4
  %call20 = call i32 @_IO_putc(i32 %conv, %struct._IO_FILE* %21)
  %22 = load i32* %pc, align 4
  %inc21 = add nsw i32 %22, 1
  store i32 %inc21, i32* %pc, align 4
  br label %for.inc22

for.inc22:                                        ; preds = %for.body19
  %23 = load i8** %string.addr, align 4
  %incdec.ptr23 = getelementptr inbounds i8* %23, i32 1
  store i8* %incdec.ptr23, i8** %string.addr, align 4
  br label %for.cond17

for.end24:                                        ; preds = %for.cond17
  br label %for.cond25

for.cond25:                                       ; preds = %for.inc31, %for.end24
  %24 = load i32* %width.addr, align 4
  %cmp26 = icmp sgt i32 %24, 0
  br i1 %cmp26, label %for.body28, label %for.end33

for.body28:                                       ; preds = %for.cond25
  %25 = load i32* %padchar, align 4
  %26 = load %struct._IO_FILE** @stderr, align 4
  %call29 = call i32 @_IO_putc(i32 %25, %struct._IO_FILE* %26)
  %27 = load i32* %pc, align 4
  %inc30 = add nsw i32 %27, 1
  store i32 %inc30, i32* %pc, align 4
  br label %for.inc31

for.inc31:                                        ; preds = %for.body28
  %28 = load i32* %width.addr, align 4
  %dec32 = add nsw i32 %28, -1
  store i32 %dec32, i32* %width.addr, align 4
  br label %for.cond25

for.end33:                                        ; preds = %for.cond25
  %29 = load i32* %pc, align 4
  ret i32 %29
}

declare i32 @_IO_putc(i32, %struct._IO_FILE*) #1

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = metadata !{i32 1, metadata !"wchar_size", i32 4}
!1 = metadata !{i32 1, metadata !"min_enum_size", i32 4}
!2 = metadata !{metadata !"clang version 3.6.0 (trunk)"}
