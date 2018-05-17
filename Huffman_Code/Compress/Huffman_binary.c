#include "Huffman_binary.h"

unsigned char set (unsigned char c, int i) {
	unsigned char mask = 1 << i;
	return mask | c;
}

bool isBitiSet(unsigned char byte, int i) {
  unsigned int mask = 1 << i;
  return(mask & byte);
}

//trasnforma de inteiro pra bin
void reverse(char string[]){
	char string2[256] = "0";
	int i, j;
	for(i = 0, j = strlen(string)-1; i < strlen(string); i++, j--){
		string2[i] = string[j];
	}
	for(i = 0; i <= strlen(string2); i++){
		string[i] = string2[i];
	}
}

void to_binary (int x, char string[],int k){
	char y = (x % 2) + 48;
	string[k] = y;
	if(x < 2){
		return;
	}
	to_binary(x / 2,string, k + 1);
	if(k == 0){
		reverse(string);
	}
	return;
}