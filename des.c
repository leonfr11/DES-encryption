#include "des.h"

int main(int argc, char *argv[]){
	unsigned char block[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	unsigned char ipblock[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	unsigned char finalblock[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	unsigned char password[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	unsigned char key1[7] = {0, 0, 0, 0, 0, 0, 0};
	unsigned char roundkey[6] = {0, 0, 0, 0, 0, 0};
	unsigned char expanded[6] = {0, 0, 0, 0, 0, 0};
	unsigned char xorout[6] = {0, 0, 0, 0, 0, 0};
	unsigned char left[4] = {0, 0, 0, 0};
	unsigned char right[4] = {0, 0, 0, 0};
	unsigned char sout[4] = {0, 0, 0, 0};
	unsigned char newsout[4] = {0, 0, 0, 0};
	
	int i,j;
	bool endflag=false;
	FILE *fs,*fn;
	fs=fopen(argv[1],"r");
	fn=fopen(argv[2],"w");
	if(fs==NULL){
		printf("File not found\n");
		exit(0);
	}
	printf("Enter password(8 characters): ");
	scanf("%8c",password);
	//printf("PASSWORD-> ");printbin(password,8);
	do{
		int x = fread(block, 1, 8, fs);
		if(x!=8){
			endflag=true;
			for(j=x;j<8;j++){
				block[j]=0;
			}
		}
	//	printf("BLOCK-> ");printbin(block,8);
		permutatedchoice1(password,key1);
		initialpermutation(block,ipblock);
	//	printf("IPBLOCK-> ");printbin(ipblock,8);
	//	printf("KEY BF-> ");printbin(key1,7);
		for(i=1;i<=16;i++){
			left[0]=ipblock[0];
			left[1]=ipblock[1];
			left[2]=ipblock[2];
			left[3]=ipblock[3];
			right[0]=ipblock[4];
			right[1]=ipblock[5];
			right[2]=ipblock[6];
			right[3]=ipblock[7];
			if(i==1 || i==2 || i==9 || i==16){
				leftshft(key1);
			}
			else{
				leftshft(key1);
				leftshft(key1);
			}
	//		printf("KEY LS-> ");printbin(key1,7);
			permutatedchoice2(key1,roundkey);
	//		printf("ROUNDKEY{%d}-> ",i);printbin(roundkey,6);
			expansion(right,expanded);
	//		printf("RIGHT EXPANSION-> ");printbin(expanded,6);
			xorout[0]=roundkey[0]^expanded[0];
			xorout[1]=roundkey[1]^expanded[1];
			xorout[2]=roundkey[2]^expanded[2];
			xorout[3]=roundkey[3]^expanded[3];
			xorout[4]=roundkey[4]^expanded[4];
			xorout[5]=roundkey[5]^expanded[5];
	//		printf("XOR-> ");printbin(xorout,6);
			substitution(xorout,sout);
	//		printf("SBOX-> ");printbin(sout,4);
			permutation(sout,newsout);
	//		printf("PERMUTATION-> ");printbin(newsout,4);
			ipblock[0]=right[0];
			ipblock[1]=right[1];
			ipblock[2]=right[2];
			ipblock[3]=right[3];
			ipblock[4]=newsout[0]^left[0];
			ipblock[5]=newsout[1]^left[1];
			ipblock[6]=newsout[2]^left[2];
			ipblock[7]=newsout[3]^left[3];
	//		printf("NEW IPBLOCK-> ");printbin(ipblock,8);
		}
		reversepermutation(ipblock,finalblock);
	//	printf("FINALBLOCK-> ");printbin(finalblock,8);
		fwrite(finalblock,8,1,fn);
		zero(block,8,ipblock,8,finalblock,8,roundkey,6,expanded,6,xorout,6,left,4,right,4,sout,4,newsout,4,key1,7);
		
	}while(!endflag);
	fclose(fn);
	fclose(fs);
}
