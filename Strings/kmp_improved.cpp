#include <bits/stdc++.h>
using namespace std;

// Construct strong borders of pattern
vector<int> construct_borders(string &s) {
  int n = s.size();
  vector<int> border(n + 1);

  border[0] = -1;
  for (int i = 1, j = -1; i <= n; i++) {
    while (j != -1 && s[j] != s[i - 1])
      j = border[j];
    border[i] = ++j;
  }

  vector<int> ans(n + 1);
  ans[0] = -1;
  for (int i = 1, j = -1; i <= n; i++) {
    j = border[i - 1];
    while (j != -1 && s[j] != s[i - 1])
      j = ans[j];
    j++;
    if (i == n || s[j] != s[i])
      ans[i] = j;
    else
      ans[i] = ans[j];
  }
  return ans;
}

vector<int> kmp(string &t, string &p, vector<int> &border) {
  vector<int> ans;
  int n = t.size(), m = p.size();
  for (int i = 0, j = 0; i <= n - m;) {
    while (j < m && p[j] == t[i + j])
      j++;
    if (j == m)
      ans.push_back(i);
    i += j - border[j];
    j = max(0, border[j]);
  }
  return ans;
}
