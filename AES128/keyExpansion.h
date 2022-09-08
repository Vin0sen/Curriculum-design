/*   密钥扩展算法用到的一些函数some sector in keyExpansion   */ 
#include"variables.h"
//字循环
word rotWord(word w){
	int i;
	word temp;
	for(i=0; i<4; i++){
		temp.wordKey[(i+3) % 4] = w.wordKey[i];
	}
	return temp;
}
//字替换
word subWord(word w){
	int i;
	unsigned char L, R;
	for(i=0; i<4; i++){
		L = w.wordKey[i] >> 4;
		R = w.wordKey[i] & 0x0f;
		w.wordKey[i] = SBox[L][R];
	}
	return w;
}
//字异或
word wordXOR(word w1, word w2){
	int i;
	word temp;
	for(i=0; i<4; i++){
		temp.wordKey[i] = w1.wordKey[i] ^ w2.wordKey[i];
	}
	return temp;
}
