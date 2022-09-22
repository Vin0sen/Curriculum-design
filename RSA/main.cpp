#include<iostream>
#include"PrimeTest.h" //Miller素性检测
#include"Euclid.h"    //欧几里得，求最大公因数 
#include"exEuclid.h"  //扩展欧几里得，求乘法逆元
#include"multiMod.h"  //大数幂模运算 a^b mod n
using namespace std;
/* 选取两个大素数p，q ;n=p*q
 * φ(n)=(p-1)(q-1)
 * 选择整数e，使得gcd(e,φ(n)) =1
 * ed mod φ(n)=1;即求e模φ(n)的乘法逆元 d 
 * PU(e,n) PR(d,n)
 * Encrypt: C=M^e mod n   ;   Decrypt: M=C^d mod n
 * RSA是一种分组密码，明文M和密文C都是小于n的正整数，通常n是1024位二进制值
*/
int main(){
	long long p,q,n,fain,e,d;
	long long M,C;

	do{
		p=rand()+10000;
		q=rand()+10000;
	}while(!PrimeTest(p)|!PrimeTest(q));//大素数p、q随机生成
	n=p*q;
	fain=(p-1)*(q-1);
	
	for(int i=2;i<fain;i++){
		if(gcd(fain,i)==1){
			// d=exEuclid(fain,i);
			// if(d>0){
			// 	e=i;
			// 	break;
			// }
			e=i;break;
		}
	}
	d=exEuclid(fain,e);
	if(d<0)d+=fain; //保证d为正数
	printf("p和q的值分别为: %d\t%d\n",p,q);
	printf("n:%d\tφ(n):%d\ne:%d\td:%d\n",n,fain,e,d);
	printf("公钥 PU=(%d,%d)\t私钥 PR(%d,%d)\n",e,n,d,n);
	cout<<"请输入要明文M (0<M<n) :\n";
	cin>>M;
	while(M>n|M==n){
		cout<<"Warning:RSA是一种分组密码,明文和密文必须小于n\n请重新输入M:";
		cin>>M;
	}
	C=multiMod(M,e,n);
	cout<<"加密: "<<C<<endl;
	cout<<"解密: "<<multiMod(C,d,n);
}
