#include "des.h"

void permutatedchoice1(unsigned char* password, unsigned char* key){
	unsigned char pc1matrix[] = {57,49,41,33,25,17,9,
				    1,58,50,42,34,26,18,
				   10, 2,59,51,43,35,27,
				   19,11, 3,60,52,44,36,
				   63,55,47,39,31,23,15,
				    7,62,54,46,38,30,22,
				   14, 6,61,53,45,37,29,
				   21,13, 5,28,20,12, 4};
	int i,part,pos,part7;
	unsigned char op;
	for(i=1;i<=56;i++){
		part = (pc1matrix[i-1]%8==0) ? (pc1matrix[i-1]/8)-1 : pc1matrix[i-1]/8;
		pos = pc1matrix[i-1]-((pc1matrix[i-1]/8)*8);
		pos = (pos==0) ? 8 : pos;
		op=128;
		op>>=(pos-1);
		op&=password[part];
		part7= ((i)%8==0) ? ((i)/8)-1 : (i)/8;
		key[part7]|=op;
	}
}

void permutatedchoice2(unsigned char* key, unsigned char* out){
	unsigned char pc2matrix[] = {14,17,11,24, 1, 5,
				      3,28,15, 6,21,10,
				     23,19,12, 4,26, 8,
				     16, 7,27,20,13, 2,
				     41,52,31,37,47,55,
				     30,40,51,45,33,48,
				     44,49,39,56,34,53,
				     46,42,50,36,29,32};
	int i,part,pos,part6;
	unsigned char op;
	for(i=1;i<=48;i++){
		part = (pc2matrix[i-1]%8==0) ? (pc2matrix[i-1]/8)-1 : pc2matrix[i-1]/8;
		pos = pc2matrix[i-1]-((pc2matrix[i-1]/8)*8);
		pos = (pos==0) ? 8 : pos;
		op=128;
		op>>=(pos-1);
		op&=key[part];
		part6= ((i)%8==0) ? ((i)/8)-1 : (i)/8;
		out[part6]|=op;
	}
}

void leftshft(unsigned char* key){
	unsigned char mid = key[3];
	unsigned char left=128, right=8;
	
	left&=key[0];
	right&=key[3];
	key[0]<<=1;
	key[1]<<=1;
	key[2]<<=1;
	key[3]<<=1;
	key[4]<<=1;
	key[5]<<=1;
	key[6]<<=1;
	left>>=3;
	right>>=3;
	key[3]&=239;
	key[6]&=254;
	key[3]|=left;
	key[6]|=right;
}
