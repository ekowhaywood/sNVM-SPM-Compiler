

i think sha has a problem

it writes outside boundary of buffers



Program = SHA
Program.Obj:= sha sha_driver
Program.iStream=input_small.asc
#Program.iStream=input_large.asc
Program.oStream=output.txt
Program.option=
Program.Arg= <$(Program.iStream) >$(Program.oStream)
stdlibs =malloc printf

include ../Makefile.bareBench


#PROGRAM = SHA
#OBJECTS = sha.bc sha_driver.bc


#FASTSIM.Arg = input_small.asc
#SLOWSIM.Arg =  --input="" --output="output.txt" --options="input_small.asc"

#LIBS = -lm


#spm.code.space = 596
spm.code.space = 1032
#spm.code.space = 1468


spm.stack.space = 11944
#spm.stack.space = 11856
#spm.stack.space = 11768

spm.heap.space = 24000
heap.block.size =
heap.assoc =


include ../Makefile.SpmSecureNvmm

