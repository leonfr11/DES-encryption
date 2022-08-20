#include "des.h"

void initialpermutation(unsigned char* block, unsigned char* ipblock){
	unsigned char ipmatrix[] = {58,50,42,34,26,18,10, 2,
				    60,52,44,36,28,20,12, 4,
				    62,54,46,38,30,22,14, 6,
				    64,56,48,40,32,24,16, 8,
				    57,49,41,33,25,17, 9, 1,
				    59,51,43,35,27,19,11, 3,
				    61,53,45,37,29,21,13, 5,
				    63,55,47,39,31,23,15, 7};
	int i,part,pos,part8;
	unsigned char op;
	for(i=0;i<=64;i++){
		part = (ipmatrix[i-1]%8==0) ? (ipmatrix[i-1]/8)-1 : ipmatrix[i-1]/8;
		pos = ipmatrix[i-1]-((ipmatrix[i-1]/8)*8);
		pos = (pos==0) ? 8 : pos;
		op=128;
		op>>=(pos-1);
		op&=block[part];
		part8= ((i)%8==0) ? ((i)/8)-1 : (i)/8;
		ipblock[part8]|=op;
	}
}

void reversepermutation(unsigned char* ipblock, unsigned char* finalblock){
	unsigned char reversematrix[] = {40, 8,48,16,56,24,64,32,
					 39, 7,47,15,55,23,63,31,
				 	 38, 6,46,14,54,22,62,30,
					 37, 5,45,13,53,21,61,29,
					 36, 4,44,12,52,20,60,28,
					 35, 3,43,11,51,19,59,27,
					 34, 2,42,10,50,18,58,26,
					 33, 1,41, 9,49,17,57,25};
	int i,part,pos,part8;
	unsigned char op;
	for(i=0;i<=64;i++){
		part = (reversematrix[i-1]%8==0) ? (reversematrix[i-1]/8)-1 : reversematrix[i-1]/8;
		pos = reversematrix[i-1]-((reversematrix[i-1]/8)*8);
		pos = (pos==0) ? 8 : pos;
		op=128;
		op>>=(pos-1);
		op&=ipblock[part];
		part8= ((i)%8==0) ? ((i)/8)-1 : (i)/8;
		finalblock[part8]|=op;
	}
}

void expansion(unsigned char* half, unsigned char* expanded){
	unsigned char expmatrix[] = {32, 1, 2, 3, 4, 5,
				      4, 5, 6, 7, 8, 9,
				      8, 9,10,11,12,13,
				     12,13,14,15,16,17,
				     16,17,18,19,20,21,
				     20,21,22,23,24,25,
				     24,25,26,27,28,29,
				     28,29,30,31,32, 1};
	int i,part,pos,part6;
	unsigned char op;
	for(i=0;i<=48;i++){
		part = (expmatrix[i-1]%8==0) ? (expmatrix[i-1]/8)-1 : expmatrix[i-1]/8;
		pos = expmatrix[i-1]-((expmatrix[i-1]/8)*8);
		pos = (pos==0) ? 8 : pos;
		op=128;
		op>>=(pos-1);
		op&=half[part];
		part6= ((i)%8==0) ? ((i)/8)-1 : (i)/8;
		expanded[part6]|=op;
	}
}

void permutation(unsigned char* sout, unsigned char* newsout){
	unsigned char pmatrix[] = {16, 7,20,21,29,12,28,17,
				    1,15,23,26, 5,18,31,10,
				    2, 8,24,14,32,27, 3, 9,
				   19,13,30, 6,22,11, 4,25};
	int i,part,pos,part4;
	unsigned char op;
	for(i=0;i<=32;i++){
		part = (pmatrix[i-1]%8==0) ? (pmatrix[i-1]/8)-1 : pmatrix[i-1]/8;
		pos = pmatrix[i-1]-((pmatrix[i-1]/8)*8);
		pos = (pos==0) ? 8 : pos;
		op=128;
		op>>=(pos-1);
		op&=sout[part];
		part4= ((i)%8==0) ? ((i)/8)-1 : (i)/8;
		newsout[part4]|=op;
	}
}		      

void substitution(unsigned char* in, unsigned char* out){
	unsigned char s1[4][16] = {{14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7},
 			           { 0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8}, 
 			           { 4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0}, 
			           {15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13}};
			      
	unsigned char s2[4][16] = {{15, 1, 8,14, 6,11, 3, 4, 9, 7, 2,13,12, 0, 5,10}, 
			           { 3,13, 4, 7,15, 2, 8,14,12, 0, 1,10, 6, 9,11, 5},
			           { 0,14, 7,11,10, 4,13, 1, 5, 8,12, 6, 9, 3, 2,15}, 
			           {13, 8,10, 1, 3,15, 4, 2,11, 6, 7,12, 0, 5,14, 9}};
			      
	unsigned char s3[4][16] = {{10, 0, 9,14, 6, 3,15, 5, 1,13,12, 7,11, 4, 2, 8},
			           {13, 7, 0, 9, 3, 4, 6,10, 2, 8, 5,14,12,11,15, 1},
			           {13, 6, 4, 9, 8,15, 3, 0,11, 1, 2,12, 5,10,14, 7}, 
			           { 1,10,13, 0, 6, 9, 8, 7, 4,15,14, 3,11, 5, 2,12}};
			       
	unsigned char s4[4][16] = {{ 7,13,14, 3, 0, 6, 9,10, 1, 2, 8, 5,11,12, 4,15},
			           {13, 8,11, 5, 6,15, 0, 3, 4, 7, 2,12, 1,10,14, 9},
			           {10, 6, 9, 0,12,11, 7,13,15, 1, 3,14, 5, 2, 8, 4},
			           { 3,15, 0, 6,10, 1,13, 8, 9, 4, 5,11,12, 7, 2,14}};
			       
	unsigned char s5[4][16] = {{ 2,12, 4, 1, 7,10,11, 6, 8, 5, 3,15,13, 0,14, 9},
			           {14,11, 2,12, 4, 7,13, 1, 5, 0,15,10, 3, 9, 8, 6},
			           { 4, 2, 1,11,10,13, 7, 8,15, 9,12, 5, 6, 3, 0,14},
			           {11, 8,12, 7, 1,14, 2,13, 6,15, 0, 9,10, 4, 5, 3}};
			      
	unsigned char s6[4][16] = {{12, 1,10,15, 9, 2, 6, 8, 0,13, 3, 4,14, 7, 5,11},
			           {10,15, 4, 2, 7,12, 9, 5, 6, 1,13,14, 0,11, 3, 8},
			           { 9,14,15, 5, 2, 8,12, 3, 7, 0, 4,10, 1,13,11, 6},
			           { 4, 3, 2,12, 9, 5,15,10,11,14, 1, 7, 6, 0, 8,13}};
			       
	unsigned char s7[4][16] = {{ 4,11, 2,14,15, 0, 8,13, 3,12, 9, 7, 5,10, 6, 1},
			           {13, 0,11, 7, 4, 9, 1,10,14, 3, 5,12, 2,15, 8, 6},
			           { 1, 4,11,13,12, 3, 7,14,10,15, 6, 8, 0, 5, 9, 2},
			           { 6,11,13, 8, 1, 4,10, 7, 9, 5, 0,15,14, 2, 3,12}};
			       
	unsigned char s8[4][16] = {{13, 2, 8, 4, 6,15,11, 1,10, 9, 3,14, 5, 0,12, 7},
			           { 1,15,13, 8,10, 3, 7, 4,12, 5, 6,11, 0,14, 9, 2},
			           { 7,11, 4, 1, 9,12,14, 2, 0, 6,10,13,15, 3, 5, 8},
			           { 2, 1,14, 7, 4,10, 8,13,15,12, 9, 0, 3, 5, 6,11}}; 
	unsigned char row,col,op;
	//s1
	op=4;
	op&=in[0];
	row=in[0]>>7;
	row<<=3;
	row|=op;
	row>>=2;
	col=in[0]<<1;
	col>>=4;
	unsigned char s1num=s1[row][col];
	//s2
	op=2;
	op&=in[0];
	row=in[1]<<3;
	row>>=7;
	row|=op;
	op=1;
	op&=in[0];
	col=in[1]>>5;
	op<<=3;
	col|=op;
	unsigned char s2num=s2[row][col];
	//s3
	op=8;
	op&=in[1];
	row=in[2]<<1;
	row>>=7;
	op>>=2;
	row|=op;
	op=128;
	op&=in[2];
	col=in[1]<<5;
	col>>=4;
	col|=op;
	unsigned char s3num=s3[row][col];
	//s4
	op=32;
	op&=in[2];
	row=in[2]<<7;
	row>>=7;
	op>>=4;
	row|=op;
	col=in[2]<<3;
	col>>=4;
	unsigned char s4num=s4[row][col];
	//s5
	op=4;
	op&=in[3];
	row=in[3]>>7;
	row<<=3;
	row|=op;
	row>>=2;
	col=in[3]<<1;
	col>>=4;
	unsigned char s5num=s5[row][col];
	//s6
	op=2;
	op&=in[3];
	row=in[4]<<3;
	row>>=7;
	row|=op;
	op=1;
	op&=in[3];
	col=in[4]>>5;
	op<<=3;
	col|=op;
	unsigned char s6num=s6[row][col];
	//s7
	op=8;
	op&=in[4];
	row=in[5]<<1;
	row>>=7;
	op>>=2;
	row|=op;
	op=128;
	op&=in[5];
	col=in[4]<<5;
	col>>=4;
	col|=op;
	unsigned char s7num=s7[row][col];
	//s8	
	op=32;
	op&=in[5];
	row=in[5]<<7;
	row>>=7;
	op>>=4;
	row|=op;
	col=in[5]<<3;
	col>>=4;
	unsigned char s8num=s8[row][col];      
	//union
	out[0]=s1num<<4;
	out[0]|=s2num;
	
	out[1]=s3num<<4;
	out[1]|=s4num;
	
	out[2]=s5num<<4;
	out[2]|=s6num;
	
	out[3]=s7num<<4;
	out[3]|=s8num;
}	

void zero(unsigned char* z1, unsigned char* z2, unsigned char* z3, unsigned char* z4, unsigned char* z5, unsigned char* z6, unsigned char* z7, unsigned char* z8, unsigned char* z9, unsigned char* z10){
	int i,x;
	x=sizeof(z1);
	for(i=0;i<x;i++){
		z1[i]='\0';
	}
	x=sizeof(z2);
	for(i=0;i<x;i++){
		z2[i]='\0';
	}
	x=sizeof(z3);
	for(i=0;i<x;i++){
		z3[i]='\0';
	}
	x=sizeof(z4);
	for(i=0;i<x;i++){
		z4[i]='\0';
	}
	x=sizeof(z5);
	for(i=0;i<x;i++){
		z5[i]='\0';
	}
	x=sizeof(z6);
	for(i=0;i<x;i++){
		z6[i]='\0';
	}
	x=sizeof(z7);
	for(i=0;i<x;i++){
		z7[i]='\0';
	}
	x=sizeof(z8);
	for(i=0;i<x;i++){
		z8[i]='\0';
	}
	x=sizeof(z9);
	for(i=0;i<x;i++){
		z9[i]='\0';
	}
	x=sizeof(z10);
	for(i=0;i<x;i++){
		z10[i]='\0';
	}
}
