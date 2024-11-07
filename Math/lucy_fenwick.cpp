#include <bits/stdc++.h>
#include <cmath>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
#define N 10000000

vi primes;
bitset<N> is_prime;
void prime_sieve() {
  for (int i = 2; i < N; i++) {
    if (!is_prime[i]) {
      primes.push_back(i);
      for (ll j = 1LL * i * i; j < N; j += i)
        is_prime[j] = 1;
    }
  }
}

ll isqrt(ll n) {
  if (n <= 1)
    return n;
  ll z = n >> 2;
  ll r2 = 2 * isqrt(z);
  ll r3 = r2 + 1;
  return (n < r3 * r3) ? r2 : r3;
}

int find_prime_number(int n) {
  int lo = 0;
  int hi = primes.size();
  while (lo < hi) {
    int me = lo + (hi - lo + 1) / 2;
    if (primes[me] <= n)
      lo = me;
    else
      hi = me - 1;
  }
  if (primes[lo] > n)
    lo--;
  return lo;
}

class FloorIndexedArray {
public:
  ll number;
  int n_sqrt;
  int size;
  vll array;

  FloorIndexedArray(ll n) {
    number = n;
    size = n_sqrt = isqrt(n);
    array.resize(size);
    for (int i = 1; i <= size; i++)
      array[i - 1] = i;
    for (int i = size; i >= 1; i--) {
      if (n / i == i)
        continue;
      array.push_back(n / i);
    }
    size = array.size();
  }

  int get_index(ll x) {
    if (x <= n_sqrt)
      return x - 1;
    return 2 * n_sqrt - (number / n_sqrt == n_sqrt) - number / x;
  }
};

class BIT {
public:
  vll array;

  BIT(vi a) {
    array.resize(a.size());
    array[0] = a[0];
    for (int i = 1; i < a.size(); i++)
      array[i] = array[i - 1] + a[i];
    for (int i = a.size() - 1; i > 0; i--) {
      int lowest_bit = (i & (i + 1)) - 1;
      if (lowest_bit >= 0)
        array[i] -= array[lowest_bit];
    }
  }

  BIT(int n) { array.resize(n); }

  void update(int pos, int value) {
    for (int i = pos + 1; i < array.size(); i += (i & -i))
      array[i] += value;
  }

  ll query(int r) {
    ll ans = 0;
    for (int i = r; i; i -= (i & -i))
      ans += array[i];
    return ans;
  }
};

ll S0(ll v, ll y, vector<ll> &S, FloorIndexedArray &array, BIT &bit) {
  if (v < y)
    return bit.query(v + 1);
  int pos = array.get_index(v);
  return S[pos];
}

ll lucy_fenwick(ll n) {
  int n_sqrt = isqrt(n);
  int prime_index = find_prime_number(n_sqrt);
  auto floor_indexed_array = FloorIndexedArray(n);
  vll S(floor_indexed_array.size);
  for (int i = 0; i < S.size(); i++) {
    ll v = floor_indexed_array.array[i];
    S[i] = (v * (v + 1)) / 2 - 1;
  }
  int y = 1;
  if (n != 1) {
    y = round(2.5 * pow(1.0 * n, 2.0 / 3.0) / pow(log(1.0 * n), 2.0 / 3.0));
    y = min(y, 200000000);
    y = max(n_sqrt + 1, y);
  }
  vector<bool> sieve_lucy(y + 1, false);
  sieve_lucy[0] = sieve_lucy[1] = true;

  auto bit = BIT(y + 1);
  for (int i = 2; i <= y; i++)
    bit.update(i, i);

  for (int i = 0; i <= prime_index; i++) {
    int prime = primes[i];
    ll sp = bit.query(prime);
    for (int j = 1; j <= min(n / y, n / (1LL * prime * prime)); j++) {
      int pos = floor_indexed_array.get_index(n / j);
      S[pos] -=
          prime *
          (S0(n / (1LL * j * prime), y, S, floor_indexed_array, bit) - sp);
    }

    ll j = 1LL * prime * prime;
    while (j <= y) {
      if (!sieve_lucy[j]) {
        sieve_lucy[j] = true;
        bit.update(j, -j);
      }
      j += prime;
    }
  }

  for (int i = 0; i <= prime_index; i++) {
    int prime = primes[prime_index];
    if (prime > y)
      break;
    int previous_prime = 1;
    if (prime_index > 0)
      previous_prime = primes[prime_index - 1];
    int prime_pos = floor_indexed_array.get_index(prime);
    int previous_prime_pos = floor_indexed_array.get_index(previous_prime);
    S[prime_pos] = S[previous_prime_pos] + prime;
  }

  return S.back();
}

int main() {
  prime_sieve();
  ll n;
  cin >> n;
  cout << lucy_fenwick(n) << '\n';
  return 0;
}
