#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define N 1000000000
const long long limit = (int)(10*sqrt(2*N));

vector <int> prime_sieve(){
    bitset <limit> sieve;
    vector <int> ans;
    for(int i=2; i<limit; i++){
        if(!sieve[i]){
            ans.push_back(i);
            for(ll j=1LL*i*i; j<limit; j+=i) sieve[j] = 1;
        }
    }
	return ans;
}

vector <int> primes;

int find_position(int p){
    int lo = 0;
    int hi = primes.size()-1;
    while(lo < hi){
        int me = lo + (hi-lo+1)/2;
        if(primes[me] <= p) lo = me;
        else hi = me-1;
    }
    return lo;
}

map <pair <ll,ll>, ll> phi_cache;

ll phi(ll x, ll a){
    pair <ll,ll> values = {x,a};
    if(phi_cache.find(values) != phi_cache.end()) return phi_cache[values];      
    if(a == 1) return (x+1)/2;
    ll ans = phi(x, a-1) - phi(x/primes[a-1], a-1);
    phi_cache[values] = ans;
    return ans;
}

map <ll,ll> pi_cache;

ll pi(ll x){
    if(pi_cache.find(x) != pi_cache.end()) return pi_cache[x];

    if(x < limit){
        ll ans = find_position(x)+1;
		pi_cache[x] = ans;
        return ans;
    }

    int a = pi((int)(pow(x,1.0/4)));
    int b = pi((int)(sqrt(x)));
    int c = pi((int)(pow(x,1.0/3)));

    ll ans = phi(x,a) + 1LL*(b+a-2)*(b-a+1)/2;

    for(int i=a+1; i<b+1; i++){
        ll w = x/primes[i-1];
        ll b_i = pi((int)(sqrt(w)));
        ans -= pi(w);
        if(i <= c){
            for(int j=i; j<b_i+1; j++)
                ans = ans - pi(w/primes[j-1]) + j - 1;
        }
    }
    pi_cache[x] = ans;
    return ans;
}

int main(){
    primes = prime_sieve();
    cout << pi(N) << '\n';
    return 0;
}
