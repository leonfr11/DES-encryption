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
void zero(unsigned char* z1, int s1, unsigned char* z2, int s2, unsigned char* z3, int s3, unsigned char* z4, int s4, unsigned char* z5, int s5, unsigned char* z6, int s6, unsigned char* z7, int s7, unsigned char* z8, int s8, unsigned char* z9, int s9, unsigned char* z10, int s10, unsigned char* z11, int s11);
void printbin(unsigned char *var, int size);
