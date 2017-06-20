/* testd - Test adpcm decoder */

#include "adpcm.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct adpcm_state state;

#define NSAMPLES 1000

//char	abuf[NSAMPLES/2]; short	sbuf[NSAMPLES];
char	*abuf; short	*sbuf;

//int main(int argc , char ** argv) {
int Entry(){
    int n;
	
	abuf = (char *)_malloc(sizeof(char) * (NSAMPLES/2));
	sbuf = (short*)_malloc(sizeof(short) * NSAMPLES);
	
    while(1) {
		//n = read(0, abuf, NSAMPLES/2);
		n = _readInputStream(abuf, 1,NSAMPLES/2);
		if ( n < 0 ) {
			perror("input file");
			exit(1);
		}
	
		if ( n == 0 ) break;
		adpcm_decoder(abuf, sbuf, n*2, &state);
		//write(1, sbuf, n*4);
		_writeOutputStream((const char *)sbuf,1,n*4);
    }
	
    //_fwriteErrStream(  "\nFinal valprev=%d, index=%d\n", \
	    state.valprev, state.index);
	
	_fwriteErrStream("\nFinal valprev=%d, " , (unsigned int) state.valprev );
	_fwriteErrStream(" index=%d\n", (unsigned int) state.index );

	
	
	_free(abuf); _free(sbuf);
	//exit(0);
	//_gArgs.returnV = 0;
	return 0;
}
