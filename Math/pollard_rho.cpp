#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll mulmod(ll a, ll b, ll p) {
  ll x = 0, y = a % p;
  while (b > 0) {
    if (b & 1)
      x = (x + y) % p;
    y = (1LL * y * 2) % p;
    b = b >> 1LL;
    ;
  }
  return x % p;
}

/*ll fastexpp(ll x, ll y, ll p){
    ll ans = 1;
    while(y > 0){
        if(y&1) ans = mulmod(ans,x,p);
        y = y>>1;
        x = mulmod(x,x,p);
    }
    return ans%p;
}*/
// Could be faster

ll fastexpp(ll x, ll y, ll p) {
  if (y == 0)
    return 1;
  if (y == 1)
    return x;
  ll aux = (1LL * fastexpp(x, y >> 1, p)) % p;
  if (!(y & 1))
    return (1LL * mulmod(aux, aux, p)) % p;
  aux = (1LL * mulmod(aux, aux, p)) % p;
  aux = (1LL * mulmod(aux, x, p)) % p;
  return aux;
}

// Better than Miller-Rabin, why? IDK
bool isPrime(ll n) {
  srand(time(NULL));
  for (int i = 2; i <= 10; i++) {
    ll a = (1LL * rand()) % n;
    ll verif = 1LL * fastexpp(a, n, n);
    if (verif != a)
      return false;
  }
  return true;
}

ll pollard(ll n) {
  if (n == 1)
    return n;
  if (!(n & 1))
    return 2;
  ll x = (1LL * rand() % (n - 2)) + 2;
  ll y = x;
  ll c = (1LL * rand() % (n - 1)) + 1;
  ll d = 1LL;
  while (d == 1) {
    x = (1LL * fastexpp(x, 2, n) + c + n) % n;
    y = (1LL * fastexpp(y, 2, n) + c + n) % n;
    y = (1LL * fastexpp(y, 2, n) + c + n) % n;
    d = 1LL * __gcd(abs(x - y), n);
    if (d == n)
      return pollard(n);
  }
  return d;
}

void fact(ll n, map<ll, int> &f) {
  if (n == 1)
    return;
  if (isPrime(n)) {
    f[n]++;
    return;
  }
  ll q = pollard(n);
  fact(q, f);
  fact(n / q, f);
}
