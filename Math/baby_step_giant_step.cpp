#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int fastexp(ll x, ll y, ll p) {
  ll ans = 1;
  while (y > 0) {
    if (y & 1)
      ans = (ans * x) % p;
    y = y >> 1;
    x = (x * x) % p;
  }
  return ans % p;
}

// a^x = b (mod m)
ll babystep_giantstep(ll a, ll b, ll m) {
  a %= m;
  b %= m;
  ll k = 1, add = 0, g;
  while ((g = __gcd(1LL * a, 1LL * m)) > 1) {
    if (b == k)
      return add;
    if (b % g)
      return -1;
    b /= g;
    m /= g;
    add++;
    k = (1LL * k * a / g) % m;
  }
  int n = sqrt(1LL * m) + 1;
  ll an = fastexp(a, n, m);
  unordered_map<ll, int> v;
  for (int q = 0, cur = b; q <= n; q++) {
    v[cur] = q;
    cur = (1LL * cur * a) % m;
  }
  for (int p = 1, cur = k; p <= n; p++) {
    cur = (1LL * cur * an) % m;
    if (v.count(cur)) {
      ll ans = 1LL * n * p - v[cur] + add;
      return ans;
    }
  }
  return -1;
}
