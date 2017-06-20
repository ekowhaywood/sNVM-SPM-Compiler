; ModuleID = '../substdlibs/mem.c'
target datalayout = "e-m:e-p:32:32-i64:64-v128:64:128-a:0:32-n32-S64"
target triple = "thumbv7--linux-gnueabihf"


; Function Attrs: nounwind
define i8* @_memcpy(i8* %destination, i8* %source, i32 %num) #0 {
entry:
  %destination.addr = alloca i8*, align 4
  %source.addr = alloca i8*, align 4
  %num.addr = alloca i32, align 4
  %ix = alloca i32, align 4
  %dst = alloca i8*, align 4
  %src = alloca i8*, align 4
  store i8* %destination, i8** %destination.addr, align 4
  store i8* %source, i8** %source.addr, align 4
  store i32 %num, i32* %num.addr, align 4
  %0 = load i8** %destination.addr, align 4
  store i8* %0, i8** %dst, align 4
  %1 = load i8** %source.addr, align 4
  store i8* %1, i8** %src, align 4
  store i32 0, i32* %ix, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %2 = load i32* %ix, align 4
  %3 = load i32* %num.addr, align 4
  %cmp = icmp ult i32 %2, %3
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %4 = load i32* %ix, align 4
  %5 = load i8** %src, align 4
  %arrayidx = getelementptr inbounds i8* %5, i32 %4
  %6 = load i8* %arrayidx, align 1
  %7 = load i32* %ix, align 4
  %8 = load i8** %dst, align 4
  %arrayidx1 = getelementptr inbounds i8* %8, i32 %7
  store i8 %6, i8* %arrayidx1, align 1
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %9 = load i32* %ix, align 4
  %inc = add nsw i32 %9, 1
  store i32 %inc, i32* %ix, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %10 = load i8** %destination.addr, align 4
  ret i8* %10
}

; Function Attrs: nounwind
define i8* @_memset(i8* %ptr, i32 %value, i32 %num) #0 {
entry:
  %ptr.addr = alloca i8*, align 4
  %value.addr = alloca i32, align 4
  %num.addr = alloca i32, align 4
  %ix = alloca i32, align 4
  %dst = alloca i8*, align 4
  store i8* %ptr, i8** %ptr.addr, align 4
  store i32 %value, i32* %value.addr, align 4
  store i32 %num, i32* %num.addr, align 4
  %0 = load i8** %ptr.addr, align 4
  store i8* %0, i8** %dst, align 4
  store i32 0, i32* %ix, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %1 = load i32* %ix, align 4
  %2 = load i32* %num.addr, align 4
  %cmp = icmp ult i32 %1, %2
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %3 = load i32* %value.addr, align 4
  %conv = trunc i32 %3 to i8
  %4 = load i32* %ix, align 4
  %5 = load i8** %dst, align 4
  %arrayidx = getelementptr inbounds i8* %5, i32 %4
  store i8 %conv, i8* %arrayidx, align 1
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %6 = load i32* %ix, align 4
  %inc = add nsw i32 %6, 1
  store i32 %inc, i32* %ix, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %7 = load i8** %ptr.addr, align 4
  ret i8* %7
}

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = metadata !{i32 1, metadata !"wchar_size", i32 4}
!1 = metadata !{i32 1, metadata !"min_enum_size", i32 4}
!2 = metadata !{metadata !"clang version 3.6.0 (trunk)"}
