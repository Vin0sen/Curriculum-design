#include <iostream>
#include<fstream> 
#include "variables.h"   //相关变量常量
#include"keyExpansion.h" //密钥扩展算法用到的一些函数
#include <cstdlib>
#include <stdio.h>
using namespace std;

class AES{
public:
	AES(){
		initRcon();  //初始化轮常量
	};
	void setCipherKey(byte key[]);
	void setPlainText(byte plain[]);
	
	//密钥扩展算法
	void keyExpansion(byte key[], word w[]);
	
	//functions in encryption and decryption
	void encryption();         //加密
	void processEncryption();
	void addRoundKey(word in[], int round);                //轮密钥加 
	void subByte(word in[],bool is_inverse);               //字节代换 
	void shiftRows(word in[],bool is_inverse);   		   //行位移 
	void mixColumn(word in[],bool is_inverse);  		   //列混淆
	byte GFMultiplyByte(byte L, byte R);
	void decryption();         //解密 
	void processDecryption();
	
	void initRcon(); //初始化轮常量
	void showWord(word w[], int len);//打印矩阵
	void showMesage();//打印加解密信息
private:
	byte cipherKey[16]; //密钥
	word plainText[4];  //明文分组矩阵 
	word cipherText[4]; //密文分组 
	word deCipherText[4];//解密后的结果 
	static const int Nb=4, Nk=4, Nr=10;
	word Rcon[11];       //轮常量
	word wordKey[44];    //轮密钥 
};


// initialize the plainText--trans plaintext from vector to state_matrix
void AES::setPlainText(byte plain[]){
	int i;
	for(i=0; i<16; i++){
		plainText[i/4].wordKey[i%4] = plain[i];
	}
}

//initialize the key--from vector to state_matrix
void AES::setCipherKey(byte key[]){
	int i;
	for(i=0; i<16; i++){
		cipherKey[i] = key[i];
	}
	keyExpansion(cipherKey, wordKey);
}

//initialize the Rcon
void AES::initRcon(){
	int i,j;
	for(i=0; i<4; i++)
		for(j=0; j<4; j++){
		Rcon[i].wordKey[j] = 0x0;
	}
	Rcon[1].wordKey[0] = 0x01;
	Rcon[2].wordKey[0] = 0x02;
	Rcon[3].wordKey[0] = 0x04;
	Rcon[4].wordKey[0] = 0x08;
	Rcon[5].wordKey[0] = 0x10;
	Rcon[6].wordKey[0] = 0x20;
	Rcon[7].wordKey[0] = 0x40;
	Rcon[8].wordKey[0] = 0x80;
	Rcon[9].wordKey[0] = 0x1b;
	Rcon[10].wordKey[0] = 0x36;
}


//密钥扩展算法,keyExpansion-get the round key
void AES::keyExpansion(byte key[], word w[]){
	int i=0,j;
	word temp;
	while(i < Nk){
		for(j=0; j<4; j++){
			w[j].wordKey[i] = key[j+4*i];
		}
		i++;
	}
	i = Nk;
	while(i < Nb*(Nr+1)){
		temp = w[i-1];
		if((i%Nk) == 0){
			temp = rotWord(temp);
			temp = subWord(temp);
			temp = wordXOR(temp, Rcon[i / Nk]);
		}
		else if(Nk > 6 && (i%Nk) == 4){
			temp = subWord(temp);
		}
		w[i] = wordXOR(w[i - Nk], temp);
		i++;
	}
}


//加密
void AES::encryption(){
	int i, j ;
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			cipherText[i].wordKey[j] = plainText[i].wordKey[j];
		}
	}
	// round function
	addRoundKey(cipherText, 0);
	for(i=1; i<10; i++){
		subByte(cipherText,0);
		shiftRows(cipherText,0);
		mixColumn(cipherText,0);
		addRoundKey(cipherText, i);
	}
	subByte(cipherText,0);
	shiftRows(cipherText,0);
	addRoundKey(cipherText, 10);
}
//字节代换, is_inverse为0是正向，为1是负向 
void AES::subByte(word in[],bool is_inverse){
	int i,j;  byte L, R;
	if(is_inverse==0){	
		for(i=0; i<4; i++){
			for(j=0; j<4; j++){
				L = in[i].wordKey[j] >> 4;
				R = in[i].wordKey[j] & 0x0f;
				in[i].wordKey[j] = SBox[L][R];
			}
		}
	}else{
		for(i=0; i<4; i++){
			for(j=0; j<4; j++){
				L = in[i].wordKey[j] >> 4;
				R = in[i].wordKey[j] & 0x0f;
				in[i].wordKey[j] = invSBox[L][R];
			}
		}
	}
}

//行位移
void AES::shiftRows(word in[],bool is_inverse){
	int i,j;
	word temp[4];
	if(is_inverse==0){
		for(i=0; i<4; i++){
			for(j=0; j<4; j++){
				temp[i].wordKey[j] = in[(i+j)%4].wordKey[j];
			}
		}
	}else{
		for(i=0; i<4; i++){
			for(j=0; j<4; j++){
				temp[i].wordKey[j] = in[(i-j+4)%4].wordKey[j];
			}
		}
	}
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			in[i].wordKey[j] = temp[i].wordKey[j];
		}
	}
}


//列混淆
void AES::mixColumn(word in[],bool is_inverse){
	word result[4];
	int i, j, k;
	if(is_inverse==0){
		for(i=0; i<4; i++){
			for(j=0; j<4; j++){
				result[i].wordKey[j] = GFMultiplyByte(mixColumnMatrix[j][0], in[i].wordKey[0]);
				for(k=1; k<4; k++){
					result[i].wordKey[j] ^= GFMultiplyByte(mixColumnMatrix[j][k], in[i].wordKey[k]);
				}
			}
		}
	}else{
		for(i=0; i<4; i++){
			for(j=0; j<4; j++){
				result[i].wordKey[j] = GFMultiplyByte(invmixColumnMatrix[j][0], in[i].wordKey[0]);
				for(k=1; k<4; k++){
					result[i].wordKey[j] ^= GFMultiplyByte(invmixColumnMatrix[j][k], in[i].wordKey[k]);
				}
			}
		}
	}
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			in[i].wordKey[j] = result[i].wordKey[j];
		}
	}
}


//forexample: 0xaf * 0x25
byte AES::GFMultiplyByte(byte L, byte R){
	byte temp[8];
	byte result = 0x00;
	temp[0] = L;
	int i;
	// temp[0] = L, temp[1] = L*x(modm(x)), temp[2] = L*x^2(mod(m(x))), temp[3] = L*x^3(mod(m(x)))...
	//先计算，再存起来，后面根据R的实际情况选用需要的
	for(i=1; i<8; i++){
		if(temp[i-1] >= 0x80){
			temp[i] = (temp[i-1] << 1) ^ 0x1b;
		}else{
			temp[i] = temp[i-1] << 1;
		}
	}
	for(i=0; i<8; i++){
		if(int((R >> i) & 0x01) == 1){
			result ^= temp[i];
		}
	}
	return result;
}
//轮密钥加 
void AES::addRoundKey(word in[], int round){
	int i, j;
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			in[i].wordKey[j] ^= wordKey[i+4*round].wordKey[j];
		}
	}
}

//解密
void AES::decryption(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			deCipherText[i].wordKey[j] = cipherText[i].wordKey[j];
		}
	}
	addRoundKey(deCipherText, 10);
	for(int i=9; i>0; i--){
		shiftRows(deCipherText,1);//0为正向, 1为逆向
		subByte(deCipherText,1);
		addRoundKey(deCipherText, i);
		mixColumn(deCipherText,1);
	}
	shiftRows(deCipherText,1);
	subByte(deCipherText,1);
	addRoundKey(deCipherText, 0);
}
void AES::showWord(word w[], int len){
	int i,j;
	for(i=0; i<len; i++){
		for(j=0; j<4; j++){
			printf("%-3x ", w[i].wordKey[j]);
		}cout<<endl;
	}
	cout<<endl;
}
void rotateMatrix(word w[],int row,int cols){ 
	for(int i=0;i<cols;i++){
		for(int j=0;j<row;j++){
			if(w[j].wordKey[cols-i-1]<16){
				printf("0%-2x",w[j].wordKey[cols-i-1]);
			}else
				printf("%-3x", w[j].wordKey[cols-i-1]);
		}
		cout<<endl;
	}
}

void AES::showMesage(){
	cout<<"\n明文矩阵:"<<endl;
	showWord(plainText, 4);			//打印明文矩阵
	cout<<"轮密钥:"<<endl;
	rotateMatrix(wordKey,Nb*(Nr+1),4);//打印轮密钥44*4
	cout<<"\ncipherText:"<<endl;
	showWord(cipherText, 4);    	//打印密文分组矩阵
	cout<<"deCipherText:"<<endl;
	showWord(deCipherText, 4);		//打印解密结果
}

int main(){
	int i=0;
	byte plain[16], key[16];

	ifstream file;
	file.open("../plain.txt", ios::in);
	if (!file.is_open()){
		cout << "文件打开失败!" << endl;
		return 0;
	}
	char c;
	cout<<"明文: ";
	while ((c=file.get())!=EOF){
		plain[i++]=c;
		cout<<plain[i-1];
	}
	while(i<16){
		plain[i++]=byte(i);//字节填充 
	} 
	for(int i=0; i<16; i++){
		//  plain[i] = byte(i);
		key[i] = 0x01;
		//  cout<<plain[i];
	}
	AES aes;
	aes.setPlainText(plain); //将明文转为16进制的明文矩阵
	aes.setCipherKey(key);   //设置密钥
	aes.encryption();        //加密
	aes.decryption();        //解密
	aes.showMesage();       
	return 0;
}
