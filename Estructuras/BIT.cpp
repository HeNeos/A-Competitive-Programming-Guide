int BIT[N];

// Point Update - Range Query

void init(vector <int> a){
    BIT[0] = a[0];
    for(int i=1; i<a.size(); i++)
        BIT[i] = BIT[i-1] + a[i];

    for(int i=a.size()-1; i>0; i--){
        int low = (i&(i+1)) - 1;
        if(low >= 0) BIT[i] -= BIT[low];
    }
}

void update(int pos, int v){
    for(++pos; pos<=N; pos += (pos&-pos))
        BIT[pos] += v;
}

int query(int r){
    int ans = 0;
    for(++r; r>0; r -= (r&-r))
        ans += BIT[r];
    return ans;
}

int query(int l, int r){
    return query(r) - query(l-1);
}

// Range Update - Point Query

void update(int pos, int v) {
    for (++pos; pos<=N; pos+=(pos&-pos))
        BIT[pos] += v;
}

void range_update(int l, int r, int v) {
    update(l, v);
    update(r+1, -v);
}

int query(int pos) {
    int ans = 0;
    for (++pos; pos>0; pos-=(pos&-pos))
        ans += BIT[pos];
    return ans;
}

// Range Update - Range Query

vector <int> B1(N, 0);
vector <int> B2(N, 0);

void update(vector <int> &b, int pos, int v){
    for(++pos; pos<=N; pos+=(pos&-pos))
        b[pos] += v;
}

void range_update(int l, int r, int v){
    update(B1, l, v);
    update(B1, r+1, -v);
    update(B2, l, v*(l-1));
    update(B2, r+1, -v*r);
}

int query(vector <int> &b, int pos){
    int ans = 0;
    for(++pos; pos>0; pos-=(pos&-pos))
        ans += b[pos];
    return ans;
}

int point_query(int pos){
    return query(B1, pos)*pos -  query(B2, pos);
}

int range_query(int l, int r){
    return point_query(r) - point_query(l-1);
}
