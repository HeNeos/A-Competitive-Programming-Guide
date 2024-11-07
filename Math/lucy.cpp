#include <bits/stdc++.h>
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

ll g(ll n, int prime_index) {
  if (prime_index == -1)
    return (n * (n + 1) / 2) - 1;
  int prime = primes[prime_index];
  ll s = g(n, prime_index - 1);
  if (1LL * prime * prime <= n)
    s -= 1LL * prime *
         (g(n / prime, prime_index - 1) - g(prime - 1, prime_index - 1));
  return s;
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

ll lucy_recursive(ll n) {
  int n_sqrt = isqrt(n);
  int prime_index = find_prime_number(n_sqrt);
  return g(n, prime_index);
}

/* Iterative approach */

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

ll lucy(ll n) {
  int n_sqrt = isqrt(n);
  int prime_index = find_prime_number(n_sqrt);
  auto floor_indexed_array = FloorIndexedArray(n);
  vll S(floor_indexed_array.size);
  for (int i = 0; i < S.size(); i++) {
    ll v = floor_indexed_array.array[i];
    S[i] = (v * (v + 1)) / 2 - 1;
  }
  for (int i = 0; i <= prime_index; i++) {
    int prime = primes[i];
    for (int j = floor_indexed_array.size - 1; j >= 0; j--) {
      ll v = floor_indexed_array.array[j];
      if (v < 1LL * prime * prime)
        break;
      int previous_prime = 1;
      if (i > 0)
        previous_prime = primes[i - 1];
      int pos = floor_indexed_array.get_index(v / prime);
      int previous_prime_pos = floor_indexed_array.get_index(previous_prime);
      S[j] -= prime * (S[pos] - S[previous_prime_pos]);
    }
  }
  return S.back();
}

int main() {
  prime_sieve();
  ll n;
  cin >> n;
  cout << lucy(n) << '\n';
  return 0;
}
