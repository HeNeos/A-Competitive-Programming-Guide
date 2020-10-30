#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll N;
ll limit;
vector <int> pi_sieve;

pair <long,long> limits(ll n){
	double nn = (double)(n);
	double ln = log(nn);
	double lln = log(ln);
  
	ll hig = (long long)(nn*(ln+lln-1+(lln-2)/ln-(lln*lln-6*lln+10.273)/(2*ln*ln)));
	ll low = (long long)(nn*(ln+lln-1+(lln-2)/ln -(lln*lln-6*lln+11.847)/(2*ln*ln)));

	low = max(low, (long long)(ln*n));
	low = max(low, 2LL);
	if(n < 8009824){
		hig = (long long)(1.25*nn*ln)+1;
		if(n < 15) hig = hig + (long long)(2.1*nn);
	}
	return make_pair(low,hig); //reference in https://docserv.uni-duesseldorf.de/servlets/DerivateServlet/Derivate-28284/pdfa-1b.pdf
}

vector <int> prime_sieve(){
	vector <bool> sieve(limit,false);
	vector <int> ans;
	for(int i=2; i<limit; i++){
		if(!sieve[i]){
			pi_sieve[i] = pi_sieve[i-1] + 1;
			ans.push_back(i);
			for(ll j=1LL*i*i; j<limit; j+=i) sieve[j] = 1;
		}
		else pi_sieve[i] = pi_sieve[i-1];
	}
	return ans;
}

vector <int> primes;

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
	if(x < limit) return pi_sieve[x];

	if(pi_cache.find(x) != pi_cache.end()) return pi_cache[x];

	int a = pi((int)(pow(x,1.0/4)));
	int b = pi((int)(sqrt(x)));
	int c = pi((int)(pow(x,1.0/3)));

	ll ans = phi(x,a) + 1LL*(b+a-2)*(b-a+1)/2;

	for(int i=a+1; i<b+1; i++){
		ll w = x/primes[i-1];
		ans -= pi(w);
		if(i <= c){
			ll b_i = pi((int)(sqrt(w)));
			for(int j=i; j<b_i+1; j++)
				ans = ans - pi(w/primes[j-1]) + j - 1;
		}
	}
	pi_cache[x] = ans;
	return ans;
}

int main(){
	ll n;
	cin >> n;
	
	pair <ll, ll> LIMITS = limits(n);
	N = LIMITS.second;
	limit = min((int)(20*sqrt(2*N)),10000000); //optional: use fixed 1e7 and use bitset in prime_sieve :)
	ll lo = LIMITS.first;
	ll hi = LIMITS.second;
  
	pi_sieve.resize(limit);
	primes = prime_sieve();
  
	short int flag = 0;
	while(lo < hi){
		ll me = lo + (hi-lo)/2;
		ll test = pi(me); //optional: comment next if statement, it's a poorly optimization :(
		if(test != n and flag < 10){
			ll val_lo = pi(lo);
			ll val_hi = pi(hi);
			if(val_hi - val_lo > 1 and val_hi != n and val_lo != n){
				double coefficient = ((double)val_hi - n)/((double)val_hi - val_lo);
				me = (long long)(coefficient*lo + (1-coefficient)*hi);
				test = pi(me);
				flag++;
			}
			else flag = 10;
		}
		if(test >= n) hi = me;
		else lo = me + 1;
	}
	cout << lo << '\n';
	return 0;
}
