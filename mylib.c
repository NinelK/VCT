// file: mylib.c
// Ronald Ruimerman 22 november 2000

#include "functions.h"

// myitostr: convert n to characters in s
void myitostr(int n, char s[])
{
	int i, sign;

	if ((sign=n) < 0) 			// record sign
		n=-n;					// make n positive
	i = 0;
	do {						// generate digits in reverse order
		s[i++] = n % 10 + '0';	// get next digit
	} while ((n/=10) > 0);		// delete it
	if (sign < 0)
		s[i++] = '-';
	s[i]='\0';
	myreverse(s);
}

// myreverse: reverse string s in place
void myreverse(char s[])
{
	int c,i,j;
	for (i=0,j=mystrlen(s)-1; i<j; i++,j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

// mystrlen
unsigned mystrlen(const char *s)
{
	register int n;

	for(n=0; *s!='\0'; ++s)
		++n;
	return n;
}


