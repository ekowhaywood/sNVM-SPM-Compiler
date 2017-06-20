
clang -target arm-linux-gnueabihf -march=armv7-a -mfloat-abi=hard -mfpu=vfpv3-d16 -mthumb -I/mnt/hgfs/sNVM/gcc-4.6/usr/lib/gcc/arm-linux-gnueabihf/4.6/include -I/mnt/hgfs/sNVM/gcc-4.6/usr/lib/gcc/arm-linux-gnueabihf/4.6/include-fixed -I/mnt/hgfs/sNVM/gcc-4.6/usr/arm-linux-gnueabihf/include -I/mnt/hgfs/sNVM/gcc-4.6/usr/arm-linux-gnueabihf/include/linux -I/mnt/hgfs/sNVM/gcc-4.6/usr/arm-linux-gnueabihf/include -emit-llvm -DspmHeapSize=4096 -DAssoc=4 -DBlockSize=512  -DspmStackSize=32768 -DnvmmStackSize=262144 -DShowExecutionReport -DUseReportFile -DShowSpmDebugMsg -DUseDebugFile -S -include fwriteErr.h fwriteErr.c -o lib.fwriteErr.ll -O0

clang -target arm-linux-gnueabihf -march=armv7-a -mfloat-abi=hard -mfpu=vfpv3-d16 -mthumb -I/mnt/hgfs/sNVM/gcc-4.6/usr/lib/gcc/arm-linux-gnueabihf/4.6/include -I/mnt/hgfs/sNVM/gcc-4.6/usr/lib/gcc/arm-linux-gnueabihf/4.6/include-fixed -I/mnt/hgfs/sNVM/gcc-4.6/usr/arm-linux-gnueabihf/include -I/mnt/hgfs/sNVM/gcc-4.6/usr/arm-linux-gnueabihf/include/linux -I/mnt/hgfs/sNVM/gcc-4.6/usr/arm-linux-gnueabihf/include -emit-llvm -DspmHeapSize=4096 -DAssoc=4 -DBlockSize=512  -DspmStackSize=32768 -DnvmmStackSize=262144 -DShowExecutionReport -DUseReportFile -DShowSpmDebugMsg -DUseDebugFile -S -include malloc.h malloc.c -o lib.malloc.ll -O0


#llc -filetype=obj fwriteErr.ll -o pp.o
#arm-linux-gnueabihf-gcc pp.o -o pp -static 
#./pp


