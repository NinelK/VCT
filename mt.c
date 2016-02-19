/* This program implements the Mersenne twister algorithm for generation of pseudorandom numbers.
The program returns random integers in the range 0 to 2^32-1 (this holds even if a long int is
larger than 32 bits). Timing with gcc indicates that it is about twice as fast as the built in
rand function. The original code was written by Michael Brundage and has been placed in the
public domain. There are a three minor changes here:
(1) This comment has been added to the program.
(2) Type specifiers (ul) have been appended to constants.
(3) A commented out block near the end has been removed. */

#define MT_LEN 624
#include <stdlib.h>

int mt_index;
unsigned long mt_buffer[MT_LEN];

void mt_init()
{
    int i;
    for (i=0; i<MT_LEN; i++)
        mt_buffer[i] = rand();
    mt_index = 0;
}

#define MT_IA           397 //397
#define MT_IB           (MT_LEN - MT_IA)
#define UPPER_MASK      0x80000000
#define LOWER_MASK      0x7FFFFFFF
#define MATRIX_A        0x9908B0DF
#define TWIST(b,i,j)    ((b)[i] & UPPER_MASK) | ((b)[j] & LOWER_MASK)
#define MAGIC(s)        (((s)&1)*MATRIX_A)

unsigned long mt_random()
{
    unsigned long * b = mt_buffer;
    int idx = mt_index;
    unsigned long s;
    int i;

    if (idx == MT_LEN*sizeof(unsigned long))
    {
        idx = 0;
        i = 0;
        for (; i < MT_IB; i++)
		{
            s = TWIST(b, i, i+1);
            b[i] = b[i + MT_IA] ^ (s >> 1) ^ MAGIC(s);
        }
        for (; i < MT_LEN-1; i++)
		{
            s = TWIST(b, i, i+1);
            b[i] = b[i - MT_IB] ^ (s >> 1) ^ MAGIC(s);
        }

        s = TWIST(b, MT_LEN-1, 0);
        b[MT_LEN-1] = b[MT_IA-1] ^ (s >> 1) ^ MAGIC(s);
    }
    mt_index = idx + sizeof(unsigned long);
    return *(unsigned long *)((unsigned char *)b + idx);
}
