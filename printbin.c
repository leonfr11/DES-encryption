#include "des.h"

void printbin(unsigned char *var, int size){
	int i;
	for(i=0;i<size;i++){
		printf("%d",(var[i]&128)>>7);
		printf("%d",(var[i]&64)>>6);
		printf("%d",(var[i]&32)>>5);
		printf("%d",(var[i]&16)>>4);
		printf("%d",(var[i]&8)>>3);
		printf("%d",(var[i]&4)>>2);
		printf("%d",(var[i]&2)>>1);
		printf("%d ",(var[i]&1));
	}
	printf("\n");
}
