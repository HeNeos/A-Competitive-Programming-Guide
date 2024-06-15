using ll = long long;

ll fastexp(ll x, ll y, ll p) {
  ll ans = 1;
  while (y > 0) {
    if (y & 1)
      ans = (ans * x) % p;
    y = y >> 1;
    x = (x * x) % p;
  }
  return ans % p;
}

ll inv(ll x, ll p) { return fastexp(x, p - 2, p); }
