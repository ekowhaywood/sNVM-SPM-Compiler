/*
 * Copyright (c) 2016, Matt Redfearn
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stddef.h>
#include <stdarg.h>

#include <stdio.h>

extern int putc ( int character, FILE * stream );

#define  simple_outputchar(str, c)	putc((int)c,stderr)

//static void simple_outputchar(char **str, char c)
//{
//	if (str) {
//		**str = c;
//		++(*str);
//	} else {
//		putc((int)c,stdout);//putchar(c);
//	}
//}


enum flags {
	PAD_ZERO	= 1,
	PAD_RIGHT	= 2,
};

static int prints(  const char *string, int width, int flags)
{
	int pc = 0, padchar = ' ';

	if (width > 0) {
		int len = 0;
		const char *ptr;
		for (ptr = string; *ptr; ++ptr) ++len;
		if (len >= width) width = 0;
		else width -= len;
		if (flags & PAD_ZERO)
			padchar = '0';
	}
	if (!(flags & PAD_RIGHT)) {
		for ( ; width > 0; --width) {
			simple_outputchar(out, padchar);
			++pc;
		}
	}
	for ( ; *string ; ++string) {
		simple_outputchar(out, *string);
		++pc;
	}
	for ( ; width > 0; --width) {
		simple_outputchar(out, padchar);
		++pc;
	}

	return pc;
}

#define PRINT_BUF_LEN 64

static int simple_outputi( int i, int base, int sign, int width, int flags, int letbase)
{
	char print_buf[PRINT_BUF_LEN];
	char *s;
	int t, neg = 0, pc = 0;
	unsigned int u = i;

	if (i == 0) {
		print_buf[0] = '0';
		print_buf[1] = '\0';
		return prints(  print_buf, width, flags);
	}

	if (sign && base == 10 && i < 0) {
		neg = 1;
		u = -i;
	}

	s = print_buf + PRINT_BUF_LEN-1;
	*s = '\0';

	while (u) {
		t = u % base;
		if( t >= 10 )
			t += letbase - '0' - 10;
		*--s = t + '0';
		u /= base;
	}

	if (neg) {
		if( width && (flags & PAD_ZERO) ) {
			simple_outputchar (out, '-');
			++pc;
			--width;
		}
		else {
			*--s = '-';
		}
	}

	return pc + prints (  s, width, flags);
}

#include <string.h>
 
//typedef unsigned char *va_list;
//#define va_start(list, param) (list = (((va_list)&param) + sizeof(param)))
//#define va_arg(list, type)    (*(type *)((list += sizeof(type)) - sizeof(type)))
//#define my_va_arg_32bit( var, ap ,type )  var = *((type *)(ap)) ; ap = ap + 4 ;
//(*(type *)((list += sizeof(type)) - 4)) }

//static int simple_vsprintf(char **out, char *format, va_list ap)

//#define my_va_arg_32bit( var, ap ,type )  var = *((type *)ap) ; ap ++  ;

//unsigned int fwriteErrVarArg[200] ;
unsigned int * currentVargFrame = NULL;
char fwriteErrVarArg[1024] ;

//void initVarg(){
//	//fwriteErrVarArg[0] = NULL;
//	//fwriteErrVarArg[1] = &fwriteErrVarArg[2];
//	
//}

unsigned int * startVargFrame(){
	
	
	unsigned int *ptr ;
	if (currentVargFrame){
		
		
		//_report1 ("\n\n new frame : current frame:%p \n\t", currentVargFrame)
			
		
		unsigned int * dataStartAddr = currentVargFrame + 3;
		unsigned int datalength = currentVargFrame[2];
		ptr = dataStartAddr + datalength ;
		
		unsigned int ** previousFrameDataAddr = (unsigned int **)(ptr + 1);
		previousFrameDataAddr[0] = currentVargFrame;
		
		
		
		currentVargFrame = ptr;
		
		dataStartAddr = ptr + 3;
		ptr[0] = (unsigned int)dataStartAddr ;
		
		
		//_report3(" new ptr:%p , prevoiusPtr:%p , dataStartAddr:%x ", ptr , (unsigned int *)ptr[1] ,  ptr[0] )
		
		
		currentVargFrame[2] = 0;
		
		
		
	}else{
		
		//_report2( "\n fwriteErrVarArg addr : %p  %p" , fwriteErrVarArg , &fwriteErrVarArg[0])
			
		//_report ("\n first : ")
		
		
		ptr = (unsigned int *)fwriteErrVarArg;
		
		unsigned int ** previousFrameDataAddr = (unsigned int **)(ptr + 1);
		previousFrameDataAddr[0] = NULL;
		
		
		currentVargFrame = ptr;
		
		unsigned int * dataStartAddr = ptr + 3;
		ptr[0] = (unsigned int)dataStartAddr ;
		
		
		//_report3( " new ptr:%p , prevoiusPtr:%p , dataStartAddr:%x ", ptr , (unsigned int *)ptr[1] ,  ptr[0] )
		
		
		currentVargFrame[2] = 0;
	}
	
	 
	return ptr;
}

void append(unsigned int * VargFramePtr, unsigned int data){
	unsigned int *dataStartAddr = VargFramePtr + 3;
	unsigned int datalength = VargFramePtr[2];
	unsigned int * dataAddr = dataStartAddr + datalength ;
	dataAddr[0] = data;
	VargFramePtr[2] = datalength + 4;
	_report5("\n append ptr:%p , prevoiusptr:%x , datalength:%u , dataStartAddr:%p , dataAddr:%p ", VargFramePtr , VargFramePtr[1], VargFramePtr[2] , dataStartAddr , dataAddr )
	_report1 (" (%u) " (dataAddr - dataStartAddr) 

}

//void EndVarg(unsigned int * ptr){
//	// set previous frame 
//	ptr[2 + ptr[1]] = ptr ;
//	fwriteErrVarArg[1] = ptr[3 + ptr[1]] ;
//	
//}

unsigned int getNext(unsigned int * VargPtr , unsigned int dataSize ){
	
	unsigned int * dataAddr =  (unsigned int *)VargPtr[0] ;
	
	//_report3 ("\n get data , ptr:%p  , size:%u , dataAddr:%p" , VargPtr , dataSize , dataAddr)
	
	unsigned int data = *(dataAddr);
  //VargPtr
	VargPtr[0] = (unsigned int) (dataAddr + dataSize)  ;
	
	unsigned int * nextDataAddr = (unsigned int *)VargPtr[0];
	
	//_report3( " , data:%u  , nextDataAddr:%x (%u)"  , data , VargPtr[0] , ( nextDataAddr - dataAddr) )
	 
	return data ;
}

//#define my_va_arg_32bit( var, ptr ,type )  var = *((type *)VargPtr[0]) ; VargPtr[0]++  ;
#define my_va_arg_32bit( var, ptr ,type )  var = (type) getNext(VargPtr , 4) ;

//*((type *)VargPtr[0]) ; VargPtr[0]++  ;



void restore(unsigned int * VargFramePtr){
	unsigned int ** previousFrameDataAddr = (unsigned int **)(VargFramePtr + 1);
	currentVargFrame =  previousFrameDataAddr[0];
	
	//_report1( "\n restore ptr:%p , prevoiusPtr:%p \n\n", VargFramePtr , currentVargFrame  )
	
}

 
int _fwriteErrStream__(char *format, unsigned int * VargPtr)
{
	
	//fStream = _gArgs.outputStream;
	//	va_list ap;
	//	int r;
	//	
	//	va_start(ap, fmt);
	//	r = simple_vsprintf(NULL, fmt, ap);
	//	va_end(ap);
	//	
	//	return r;
	
	//char **out = NULL ; 
	
	//unsigned int * ap = fwriteErrVarArg;
	
	//va_list ap;
	//va_start(ap, format);
	
//	unsigned char * ap;
//	ap = (unsigned char *)&format;
//	//ap = ap  ;
//	
//	//int num1 = *((int *)ap+1); 
//	//int num2 = *((int *)ap+2);
//	int num3 = *((int *)ap+3);
//	int num4 = *((int *)ap+4);
//	int num5 = *((int *)ap+5);
//	int num6 = *((int *)ap);
	
	//printf(" lets see %p %s ,   %p , %d , %d, %d, %d, %d , %d" , &format , format , ap , num1 ,num2 ,num3,num4,num5 ,num6 );
	
	//fflush(stdout);
	
	//return 0;
	
	int width, flags;
	int pc = 0;
	char scr[2];
	union {
		char c;
		char *s;
		int i;
		unsigned int u;
		void *p;
	} u;

	
	
	 
	
	for (; *format != 0; ++format) {
		if (*format == '%') {
			++format;
			width = flags = 0;
			if (*format == '\0')
				break;
			if (*format == '%')
				goto out;
			if (*format == '-') {
				++format;
				flags = PAD_RIGHT;
			}
			while (*format == '0') {
				++format;
				flags |= PAD_ZERO;
			}
			if (*format == '*') {
				my_va_arg_32bit(width, ap, int) //width = va_arg(ap, int);
				format++;
			} else {
				for ( ; *format >= '0' && *format <= '9'; ++format) {
					width *= 10;
					width += *format - '0';
				}
			}
			switch (*format) {
				case('d'):
					my_va_arg_32bit(u.i, ap, int) //u.i = va_arg(ap, int);
					pc += simple_outputi(  u.i, 10, 1, width, flags, 'a');
					break;

				case('u'):
					my_va_arg_32bit(u.u, ap,unsigned int) //u.u = va_arg(ap, unsigned int);
					pc += simple_outputi(  u.u, 10, 0, width, flags, 'a');
					break;

				case('x'):
					my_va_arg_32bit(u.u, ap, unsigned int) //u.u = va_arg(ap, unsigned int);
					pc += simple_outputi(  u.u, 16, 0, width, flags, 'a');
					break;

				case('X'):
					my_va_arg_32bit(u.u, ap, unsigned int) //u.u = va_arg(ap, unsigned int);
					pc += simple_outputi(  u.u, 16, 0, width, flags, 'A');
					break;

				case('c'):
					my_va_arg_32bit(u.c, ap, int) //u.c = va_arg(ap, int);
					scr[0] = u.c;
					scr[1] = '\0';
					pc += prints(  scr, width, flags);
					break;

				case('s'):
					my_va_arg_32bit(u.s, ap, char*) // u.s = va_arg(ap, char *);
					pc += prints(  u.s ? u.s : "(null)", width, flags);
					break;
				default:
					break;
			}
		}
		else {
out:
			simple_outputchar (out, *format);
			++pc;
		}
	}
	//if (out) **out = '\0';
	//va_end(ap);
	return pc;
}

//int simple_fprintf(FILE * f , char *fmt, ...)
//{
//	fStream = f;
//	va_list ap;
//	int r;
//
//	va_start(ap, fmt);
//	r = simple_vsprintf(NULL, fmt, ap);
//	va_end(ap);
//
//	return r;
//}
//
//int simple_printf( char *fmt, ...)
//{
//	fStream = _gArgs.outputStream;
//	va_list ap;
//	int r;
//	
//	va_start(ap, fmt);
//	r = simple_vsprintf(NULL, fmt, ap);
//	va_end(ap);
//	
//	return r;
//}

//int simple_sprintf(char *buf, char *fmt, ...)
//{
//	va_list ap;
//	int r;
//
//	va_start(ap, fmt);
//	r = simple_vsprintf(&buf, fmt, ap);
//	va_end(ap);
//
//	return r;
//}


#ifdef TEST

#define Myprintf _fwriteErrStream__
#define sprintf simple_sprintf

int main(int argc, char *argv[])
{
	static char shortstr[] = "Test";
	char buf[256];

	//Myprintf("percent:                \"%%\"\n");
	//Myprintf("bad format:             \"%z\"\n");
	//Myprintf("\n");
	//fwriteErrVarArg[0]=(unsigned int)((int)12345);
	//Myprintf("decimal:                \"%d\"\n" );
	//fwriteErrVarArg[1]=(unsigned int)((int)-8989); 
 	
	
	unsigned int * vp = startVargFrame();
	append(vp , 12345); append(vp , 12345);
	Myprintf("\ndecimal:                \"%u\"\ndecimal negative:       \"%u\"\n" , vp );
	restore(vp);
	
	vp = startVargFrame();
	append(vp , 434); append(vp , 2222);
	Myprintf("\ndecimal:                \"%u\"\ndecimal negative:       \"%u\"\n" , vp );
	restore(vp);
	
	
	
	return 0 ;
	
	//	Myprintf("\n");
//	Myprintf("unsigned:               \"%u\"\n", 12345);
//	Myprintf("unsigned negative:      \"%u\"\n", -2345);
//	Myprintf("\n");
//	Myprintf("hex:                    \"%x\"\n", 0x12345);
//	Myprintf("hex negative:           \"%x\"\n", -0x12345);
//	Myprintf("\n");
//	Myprintf("long decimal:           \"%ld\"\n", 123456L);
//	Myprintf("long decimal negative:  \"%ld\"\n", -23456L);
//	Myprintf("\n");
//	Myprintf("long unsigned:          \"%lu\"\n", 123456L);
//	Myprintf("long unsigned negative: \"%lu\"\n", -123456L);
//	Myprintf("\n");
//	Myprintf("long hex:               \"%x\"\n", 0x12345L);
//	Myprintf("long hex negative:      \"%x\"\n", -0x12345L);
//	Myprintf("\n");
//	Myprintf("zero-padded LD:         \"%010ld\"\n", 123456);
//	Myprintf("zero-padded LDN:        \"%010ld\"\n", -123456);
//	Myprintf("left-adjusted ZLDN:     \"%-010ld\"\n", -123456);
//	Myprintf("space-padded LDN:       \"%10ld\"\n", -123456);
//	Myprintf("left-adjusted SLDN:     \"%-10ld\"\n", -123456);
//	Myprintf("\n");
//	Myprintf("variable pad width:     \"%0*d\"\n", 15, -2345);
//	Myprintf("\n");
//	Myprintf("char:                   \"%c%c%c%c\"\n", 'T', 'e', 's', 't');
//	Myprintf("\n");
//	Myprintf("zero-padded string:     \"%010s\"\n", shortstr);
//	Myprintf("left-adjusted Z string: \"%-010s\"\n", shortstr);
//	Myprintf("space-padded string:    \"%10s\"\n", shortstr);
//	Myprintf("left-adjusted S string: \"%-10s\"\n", shortstr);
//	Myprintf("null string:            \"%s\"\n", (char *)NULL);

	//sprintf(buf, "decimal:\t\"%d\"\n", -2345);
	//Myprintf("sprintf: %s", buf);
}



#endif /* TEST */
