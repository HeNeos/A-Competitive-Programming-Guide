ll extended_gcd(ll a, ll b, ll& x, ll& y){
    if (b == 0){
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = extended_gcd(b, a%b, x1, y1);
    x = y1;
    y = x1 - y1*(a/b);
    return d;
}

/** Works for non-coprime moduli.
 Returns {-1,-1} if solution does not exist or input is invalid.
 Otherwise, returns {x,L}, where x is the solution unique to mod L
*/

bool verify_input(vll &x){
    vll ans;
    map <ll, ll> m;
    int n = x.size();
    for(int i=0; i<n; i++){
        if(m.find(x[i].second) != m.end()){
            if(m[x[i].second] != x[i].first) return false;
        }
        else{
            ans.pb(mp(x[i].first, x[i].second));
            m[x[i].second] = x[i].first;
        }
    }
    x = ans;
    return true;
}
//data[i].first = x[i]
//data[i].second = m[i]
pll crt(vll data){
    if(!verify_input(data)) return {-1,-1}; /** Invalid input*/
    int n = data.size();
    ll a1 = data[0].first;
    ll m1 = data[0].second; 
    for(int i = 1; i < n; i++){
        ll a2 = data[i].first;
        ll m2 = data[i].second;
        ll g = __gcd(m1, m2);
        if(a1%g != a2%g) return {-1,-1}; /*No solution*/
        ll p, q;
        extended_gcd(m1/g, m2/g, p, q);
        ll mod = m1/g*m2;
        ll x = ((__int128)a1*(m2/g)*q + (__int128)a2*(m1/g)*p)%mod;
        a1 = x;
        if(a1 < 0) a1 += mod;
        m1 = mod;
    }
    return mp(a1, m1);
}
