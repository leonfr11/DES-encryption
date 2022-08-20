#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void permutatedchoice1(unsigned char* password, unsigned char* key);
void permutatedchoice2(unsigned char* key, unsigned char* out);
void leftshft(unsigned char* key);
void initialpermutation(unsigned char* block, unsigned char* ipblock);
void expansion(unsigned char* half, unsigned char* expanded);
void substitution(unsigned char* in, unsigned char* out);
void permutation(unsigned char* sout, unsigned char* newsout);
void reversepermutation(unsigned char* ipblock, unsigned char* finalblock);
void zero(unsigned char* z1, unsigned char* z2, unsigned char* z3, unsigned char* z4, unsigned char* z5, unsigned char* z6, unsigned char* z7, unsigned char* z8, unsigned char* z9, unsigned char* z10);
