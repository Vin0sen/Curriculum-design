#include<iostream>
#include"PrimeTest.h" //Miller���Լ��
#include"Euclid.h"    //ŷ����ã���������� 
#include"exEuclid.h"  //��չŷ����ã���˷���Ԫ
#include"multiMod.h"  //������ģ���� a^b mod n
using namespace std;
/* ѡȡ����������p��q ;n=p*q
 * ��(n)=(p-1)(q-1)
 * ѡ������e��ʹ��gcd(e,��(n)) =1
 * ed mod ��(n)=1;����eģ��(n)�ĳ˷���Ԫ d 
 * PU(e,n) PR(d,n)
 * Encrypt: C=M^e mod n   ;   Decrypt: M=C^d mod n
 * RSA��һ�ַ������룬����M������C����С��n����������ͨ��n��1024λ������ֵ
*/
int main(){
	long long p,q,n,fain,e,d;
	long long M,C;
	cout<<"������p��q:\n";
	cin>>p>>q;
	while(!PrimeTest(p)|!PrimeTest(q)){
		cout<<"p��q������, ��������\n";
		cin>>p>>q;
	}
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
	if(d<0)d+=fain; //��֤dΪ����
	cout<<"n:"<<n<<endl<<"��(n):"<<fain<<endl<<"e:"<<e<<endl<<"d:"<<d<<endl;
	cout<<"������Ҫ����M (0<M<n) :\n";
	cin>>M;
	while(M>n|M==n){
		cout<<"Warning:RSA��һ�ַ�������,���ĺ����ı���С��n\n����������M:";
		cin>>M;
	}
	C=multiMod(M,e,n);
	cout<<"����: "<<C<<endl;
	cout<<"����: "<<multiMod(C,d,n);
}
