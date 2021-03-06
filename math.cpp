using ll = long long;

// 高速に n^m (mod p) を求める
ll Pow(ll n, ll m, ll p){
    ll res = 1, x = n;
    for(ll i = m; i > 0; i >>= 1){
        if(i & 1){
            res *= x;
            res %= p;
        }
        x *= x;
        x %= p;
    }
    return res;
}

/* フェルマーの小定理 : a^p ≡ a (mod p) */
// a^(p - 1 - x) ≡ a^(-x) (mod p)
ll Fermat(ll a, ll x, ll p){
    return Pow(a, p - 1 - x, p);
}



class Combination {
private:
    vector<ll> fact, finv, inv;
    ll mod;
    
public:
    Combination(ll mod = 1e9 + 7, ll table_size = 300005) : mod(mod),
                                                            fact(table_size),
                                                            finv(table_size),
                                                            inv(table_size)  {
        fact[0] = fact[1] = 1;
        finv[0] = finv[1] = 1;
        inv[1] = 1;
        for (ll i = 2; i < table_size; i++){
            fact[i] = fact[i - 1] * i % mod;
            inv[i] = mod - inv[mod % i] * (mod / i) % mod;
            finv[i] = finv[i - 1] * inv[i] % mod;
        }
    }
    
    ll operator () (ll n, ll r){
        if(n < r || n < 0 || r < 0) return 0;
        return fact[n] * (finv[r] * finv[n - r] % mod) % mod;
    }
    
    ll perm(ll n, ll r){
        if(n < r || n < 0 || r < 0) return 0;
        return fact[n] * finv[n - r] % mod;
    }
};



/* 行列累乗 */
using vec = vector<ll>;
using mat = vector<vec>;

mat Mul(mat a, mat b){
    mat c(a.size(), vec(b[0].size()));
    
    for(ll i = 0; i < a.size(); i++){
        for(ll k = 0; k < b.size(); k++){
            for(ll j = 0; j < b[0].size(); j++){
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]);
            }
        }
    }
    
    return c;
}

mat Pow(mat a, ll n){
    mat b(a.size(), vec(a.size()));
    
    for(ll i = 0; i < a.size(); i++){
        b[i][i] = 1;
    }
    while(n > 0){
        if(n & 1){
            b = Mul(b, a);
        }
        a = Mul(a, a);
        n >>= 1;
    }
    
    return b;
}
