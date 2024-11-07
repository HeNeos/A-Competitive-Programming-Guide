#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
#define N 10000000

// f(n): multiplicative function
// g(p, k): f(p^k) -> g(p, 1) = f(p)
// g(p, 1): polynomial with low degree = a0 + a1*p + a2*p^2...

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

class Min25Sieve {
public:
  ll n;
  int n_sqrt;
  int pi_nsqrt;
  vll id;
  vll a;
  vll f;
  int f_deg;
  vector<vll> prefix_sum;
  vector<vll> G;
  FloorIndexedArray floor_indexed_array;

  Min25Sieve(ll _n, vll _f)
      : n(_n), n_sqrt(isqrt(n)), f(_f), f_deg(f.size()),
        floor_indexed_array(_n) {
    prefix_sum.resize(f_deg);
    G.resize(f_deg);
    for (int i = 0; i < f_deg; i++)
      G[i].push_back(0);
    pi_nsqrt = find_prime_number(n_sqrt) + 1;
    for (int i = 0; i < f_deg; i++)
      prefix_sum[i].resize(pi_nsqrt + 1);
    id.resize(floor_indexed_array.size);
  }

  // phi(p^k) = p^k - p^(k-1) = p^k - p^k/p
  // mu(p^k) = 0
  ll g(int p, int k, ll pk) {
    // ll ans = pk;
    // return ans - ans / p;
    if (k == 1)
      return -1;
    if (k == 0)
      return 1;
    return 0;
  }

  void sieve() {
    for (int i = 0; primes[i] <= n_sqrt; i++) {
      int prime = primes[i];
      ll prime_k = 1;
      for (int k = 0; k < f_deg; k++) {
        prefix_sum[k][i + 1] = prefix_sum[k][i] + prime_k;
        prime_k *= prime;
      }
    }
  }

  void fill_g() {
    int pos = 0;
    ll i = 1;
    a.push_back(0);
    while (i <= n) {
      ll x = n / i;
      ll j = n / x;
      a.push_back(x);
      pos++;
      ll z = x;
      for (int k = 0; k < f_deg; k++) {
        if (k == 0)
          G[k].push_back(z - 1);
        if (k == 1)
          G[k].push_back(z * (z + 1) / 2 - 1);
      }
      int index = floor_indexed_array.get_index(x);
      id[index] = pos;
      i = j + 1;
    }

    for (int i = 1; i <= pi_nsqrt; i++) {
      for (int j = 1; j <= pos and primes[i - 1] <= a[j] / primes[i - 1]; j++) {
        int index = id[floor_indexed_array.get_index(a[j] / primes[i - 1])];
        ll prime_k = 1;
        for (int k = 0; k < f_deg; k++) {
          G[k][j] -= prime_k * (G[k][index] - prefix_sum[k][i - 1]);
          prime_k *= primes[i - 1];
        }
      }
    }
  }

  ll s(ll _n, int pos) {
    if (primes[pos - 1] >= _n)
      return 0;
    int index = id[floor_indexed_array.get_index(_n)];
    ll ans = 0;
    for (int k = 0; k < f_deg; k++)
      ans += f[k] * G[k][index];
    for (int k = 0; k < f_deg; k++)
      ans -= f[k] * prefix_sum[k][pos];
    for (int i = pos + 1; i <= pi_nsqrt and primes[i - 1] <= _n / primes[i - 1];
         i++) {
      ll prime_k = primes[i - 1];
      for (int e = 1; prime_k <= _n; e++) {
        ans += g(primes[i - 1], e, prime_k) * (s(_n / prime_k, i) + (e != 1));
        if (prime_k > _n / primes[i - 1])
          break;
        prime_k *= primes[i - 1];
      }
    }
    return ans;
  }
};

ll solve(ll n, vll f) {
  auto min_25_sieve = Min25Sieve(n, f);
  min_25_sieve.sieve();
  min_25_sieve.fill_g();
  return min_25_sieve.s(n, 0) + 1;
}

int main() {
  prime_sieve();
  ll n;
  while (cin >> n) {
    auto t1 = std::chrono::high_resolution_clock::now();
    // phi(p) = -1 + p
    // mu(p) = -1
    vll f = {-1};
    ll ans = solve(n, f);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    cout << duration / 1000000.0 << "s\t";
    cout << "M(" << n << ") = " << ans << '\n';
  }
  return 0;
}
