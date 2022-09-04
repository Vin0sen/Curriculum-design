/* 大数幂模运算 */
typedef long long ll;

// 使用二进制平方乘法计算 (input^key mod n )
ll multiMod(ll input, ll key, ll n){
    ll out=1;

    while(key){
        /*对于b中的每个1，累加y*/
        if(key & 1)
            out= (out*input) % n;

        /*对于b中的每一位，计算a的平方*/
        input = (input*input) % n;

        /*准备b中的下一位*/
        key = key>>1;
    }
    return out;
}