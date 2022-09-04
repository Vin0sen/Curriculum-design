//最大公约数--Euclid 算法
int gcd(int a, int b) {
    int tmp;
	if(a<b){
    	tmp=a;
    	a=b;
    	b=tmp;
	}
    int r=a%b; 
    while(r>0){
		a=b;
    	b=r;
    	r=a%b;
	}
	return b;
}
// //另一种写法(递归)：
// int Euclid(int a,int b){
// 	if(a<b){
//     	tmp=a;
//     	a=b;
//     	b=tmp;
// 	}
// 	if(b==0)return a;
// 	else return Euclid(b,a mod b);
// }