
Program = dijkstra
Program.Obj:= dijkstra_small
Program.iStream=input.dat
#Program.iStream=input_large.asc
Program.oStream=output.txt
Program.option=
Program.Arg= $(Program.iStream) $(Program.oStream)
stdlibs =malloc

include ../Makefile.bareBench



 


#PROGRAM = dijkstra

#OBJECTS = dijkstra_small.bc


#FASTSIM.Arg =  input.dat > out.txt


#SLOWSIM.Arg =


#LIBS = -lm




spm.code.space = 320


spm.stack.space = 11944
#spm.stack.space = 11856
#spm.stack.space = 11768

spm.heap.space = 24000
heap.block.size =
heap.assoc =


include ../Makefile.SpmSecureNvmm

#include ../Makefile.common


