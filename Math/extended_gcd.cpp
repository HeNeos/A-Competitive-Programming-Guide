using ll = long long;

ll extended_gcd(ll a, ll b, ll &x, ll &y) { // a*x + b*y == gcd(a,b)
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  ll x1, y1;
  ll d = extended_gcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return d;
}
