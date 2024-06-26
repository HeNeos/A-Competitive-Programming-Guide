#include <bits/stdc++.h>
using namespace std;
#define N 1000005

int BIT[N];

// Point Update - Range Query

void init(vector<int> a) {
  BIT[0] = a[0];
  for (int i = 1; i < a.size(); i++)
    BIT[i] = BIT[i - 1] + a[i];

  for (int i = a.size() - 1; i > 0; i--) {
    int low = (i & (i + 1)) - 1;
    if (low >= 0)
      BIT[i] -= BIT[low];
  }
}

void update(int pos, int v) {
  for (int i = pos + 1; i <= N; i += (i & -i))
    BIT[i] += v;
}

int query(int r) { // [0, r)
  int ans = 0;
  for (int i = r; i; i -= (i & -i))
    ans += BIT[i];
  return ans;
}

int query(int l, int r) { // [l, r)
  return query(r) - query(l);
}

// BIT 2D

void update(int x, int y, int v) {
  for (int i = x + 1; i <= N; i += (i & -i)) {
    for (int j = y + 1; j <= N; j += (j & -j))
      BIT[i][j] += v;
  }
}

int query(int x, int y) { // [(0, 0), (x, y))
  int ans = 0;
  for (int i = x; i; i -= (i & -i)) {
    for (int j = y; j; j -= (j & -j))
      ans += BIT[i][j];
  }
  return ans;
}

// Range Update - Point Query

void update(int pos, int v) {
  for (int i = pos + 1; i <= N; i += (i & -i))
    BIT[i] += v;
}

void range_update(int l, int r, int v) {
  update(l, v);
  update(r + 1, -v);
}

int query(int pos) { // [0, r)
  int ans = 0;
  for (int i = pos; i; i -= (i & -i))
    ans += BIT[i];
  return ans;
}

// Range Update - Range Query

vector<int> B1(N, 0);
vector<int> B2(N, 0);

void update(vector<int> &b, int pos, int v) {
  for (++pos; pos <= N; pos += (pos & -pos))
    b[pos] += v;
}

void range_update(int l, int r, int v) {
  update(B1, l, v);
  update(B1, r + 1, -v);
  update(B2, l, v * (l - 1));
  update(B2, r + 1, -v * r);
}

int query(vector<int> &b, int pos) {
  int ans = 0;
  for (++pos; pos > 0; pos -= (pos & -pos))
    ans += b[pos];
  return ans;
}

int point_query(int pos) { return query(B1, pos) * pos - query(B2, pos); }

int range_query(int l, int r) { return point_query(r) - point_query(l - 1); }
