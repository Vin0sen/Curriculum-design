//求乘法逆元——扩展欧几里得算法
typedef long long ll;
void Exgcd(ll a, ll b, ll &x, ll &y) {
	if (b==0){
		x = 1;
		y = 0;
	} 
	else{
		Exgcd(b, a % b, y, x);
		y -= a / b * x;
	}
}
ll exEuclid(ll a, ll b){
    ll x,y;
    Exgcd(a,b,x,y);
    return y;
}