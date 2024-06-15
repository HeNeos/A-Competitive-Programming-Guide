#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define N 1000005

bitset<N> primes;
void sieve() {
  for (int i = 2; i < N; i++) {
    if (!primes[i]) {
      for (ll j = 1LL * i * i; j < N; j += i)
        primes[j] = 1;
    }
  }
}

int lpf[N];
void sieve() {
  for (int i = 2; i < N; i++) {
    if (!lpf[i]) {
      lpf[i] = i;
      for (ll j = 1LL * i * i; j < N; j += i) {
        if (lpf[j] == 0)
          lpf[j] = i;
      }
    }
  }
}

int phi[N];
void cphi() {
  phi[1] = 1;
  for (int i = 2; i < N; i++) {
    if (!phi[i]) {
      phi[i] = i - 1;
      for (ll j = 2 * i; j < N; j += i) {
        if (phi[j] == 0)
          phi[j] = j;
        phi[j] = phi[j] / i * (i - 1);
      }
    }
  }
}
