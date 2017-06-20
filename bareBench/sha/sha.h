#ifndef SHA_H
#define SHA_H

/* NIST Secure Hash Algorithm */
/* heavily modified from Peter C. Gutmann's implementation */

/* Useful defines & typedefs */

typedef unsigned char BYTE;
//typedef unsigned long LONG;
typedef uint32_t LONG;

#define SHA_BLOCKSIZE		128
#define SHA_DIGESTSIZE		20

typedef struct {
    LONG digest[5];		/* message digest */
    LONG count_lo, count_hi;	/* 64-bit bit count */
    LONG data[16];		/* SHA data buffer */
} SHA_INFO;

void sha_init(SHA_INFO *);
void sha_update(SHA_INFO *, BYTE *, int);
void sha_final(SHA_INFO *);

//void sha_stream(SHA_INFO *, BYTE *,size_t);//, FILE *);
void sha_stream(SHA_INFO *, FILE *);

void sha_print(SHA_INFO *);

#endif /* SHA_H */


// 1be9e9a9f684a1ba cd06dd5b080e9b2f eda87b614c9dc8f6 5372003fe949827 f843cdf10942bc06
// 1be9e9a9f684a1ba cd06dd5b080e9b2f eda87b614c9dc8f6 5372003fe949827 f843cdf10942bc06

// f684a1ba 80e9b2f 4c9dc8f6 fe949827 942bc06

// 1b92d593 32574a89 050c256f 18f14c43 1be780b3
// 1b92d593 32574a89 50c256f 18f14c43 1be780b3
// 1b92d593 32574a89 50c256f 18f14c43 1be780b3
