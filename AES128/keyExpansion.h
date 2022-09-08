/*   ��Կ��չsome sector in keyExpansion   */ 
#include"variables.h"
//��ѭ�� 
word rotWord(word w){
	int i;
	word temp;
	for(i=0; i<4; i++){
		temp.wordKey[(i+3) % 4] = w.wordKey[i];
	}
	return temp;
}
//�ִ��� 
word subWord(word w){
	int i;
	byte L, R;
	for(i=0; i<4; i++){
		L = w.wordKey[i] >> 4;
		R = w.wordKey[i] & 0x0f;
		w.wordKey[i] = SBox[L][R];
	}
	return w;
}
//����� 
word wordXOR(word w1, word w2){
	int i;
	word temp;
	for(i=0; i<4; i++){
		temp.wordKey[i] = w1.wordKey[i] ^ w2.wordKey[i];
	}
	return temp;
}
