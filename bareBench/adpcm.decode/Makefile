

Program = adpcm.decode
Program.Obj:= rawdaudio adpcm
Program.iStream=data/small.pcm
Program.oStream=outputSmall.adpcm
Program.option=
Program.Arg= $(Program.iStream) $(Program.oStream)
stdlibs= mem malloc fwriteErr

#fwriteO

#fwriteErr

include ../Makefile.bareBench

#prints 0
#simple_outputi 0
#_fwriteErrStream 0



# spm benchmarking options

spm.code.space = 500
spm.stack.space = 50
#spm.stack.space = 11856
#spm.stack.space = 11768

spm.heap.space = 24000
heap.block.size =
heap.assoc =

include ../Makefile.SpmSecureNvmm



outputformat=binary

#FASTSIM.Arg =  < data/large.pcm > output.adpcm
#SLOWSIM.Arg =  --input="data/small.pcm" --
#output="output_small.adpcm" --options=""
