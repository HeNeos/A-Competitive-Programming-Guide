#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;

// factorization[i] = (p,a): p^a
// Complexity = O(0.5*n^1/3)?
//  generate_divisors(n, 0, 1, &factorization, &ans)

void generate_divisors(int n, int index, int d, vii &factorization, vi &ans) {
  if (1LL * d * d > n)
    return;

  if (index == factorization.size()) {
    ans.push_back(d);
    if (d * d != n)
      ans.push_back(n / d);
    return;
  }
  for (int i = 0; i <= factorization[index].second; ++i) {
    generate_divisors(n, index + 1, d, factorization, ans);
    d *= factorization[index].first;
  }
}
