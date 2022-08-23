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
	int i,part,pos,part7,newpos;
	unsigned char op;
	for(i=1;i<=56;i++){
		part = (pc1matrix[i-1]%8==0) ? (pc1matrix[i-1]/8)-1 : pc1matrix[i-1]/8;
		pos = pc1matrix[i-1]-((pc1matrix[i-1]/8)*8);
		pos = (pos==0) ? 8 : pos;
		op=128;
		op>>=(pos-1);
		op&=password[part];
		op>>=(8-pos);
		newpos= i-(i/8)*8;
		newpos = (newpos==0) ? 8 : newpos;
		op<<=(8-newpos);
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
	int i,part,pos,part6,newpos;
	unsigned char op;
	for(i=1;i<=48;i++){
		part = (pc2matrix[i-1]%8==0) ? (pc2matrix[i-1]/8)-1 : pc2matrix[i-1]/8;
		pos = pc2matrix[i-1]-((pc2matrix[i-1]/8)*8);
		pos = (pos==0) ? 8 : pos;
		op=128;
		op>>=(pos-1);
		op&=key[part];
		op>>=(8-pos);
		newpos= i-(i/8)*8;
		newpos = (newpos==0) ? 8 : newpos;
		op<<=(8-newpos);
		part6= ((i)%8==0) ? ((i)/8)-1 : (i)/8;
		out[part6]|=op;
	}
}

void leftshft(unsigned char* key){
	unsigned char left0=128, left1=128, left2=128, left3=128, right4=128, right5=128 , right6=128, op, op2;
	
	left0&=key[0];
	left0>>=3;
	left1&=key[1];
	left1>>=7;
	left2&=key[2];
	left2>>=7;
	left3&=key[3];
	left3>>=7;
	right4&=key[4];
	right4>>=7;
	right5&=key[5];
	right5>>=7;
	right6&=key[6];
	right6>>=7;
	key[0]<<=1;
	key[0]|=left1;
	key[1]<<=1;
	key[1]|=left2;
	key[2]<<=1;
	key[2]|=left3;
	key[3]<<=1;
	op2=16;
	op2&=key[3];
	op=238;
	key[3]&=op;
	key[3]|=left0;
	key[3]|=right4;
	key[4]<<=1;
	key[4]|=right5;
	key[5]<<=1;
	key[5]|=right6;
	key[6]<<=1;
	op2>>=4;
	key[6]|=op2;
}
