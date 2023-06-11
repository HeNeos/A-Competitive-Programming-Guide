typedef complex<double> cp;
const double pi = acos(-1);

#define N (1<<18)
cp w[N];

void init(){
    for(int i=0; i<N; i++) w[i] = polar(1., 2*pi/N*i);
}

template<typename T>
void fft(T *in, cp *out, int n, ll k = 1){
    if(n == 1){
        *out = *in;
        return;
    }
    int t = N/n;
    n >>= 1;
    fft(in, out, n, 2*k);
    fft(in+k, out+n, n, 2*k);
    for(int i=0, j=0; i<n; i++, j+=t){
        cp t = w[j]*out[i + n];
        out[i+n] = out[i]-t;
        out[i] += t;
    }
}

vector <cp> evaluate(vector <int> p){
    while(__builtin_popcount(p.size()) != 1){
        p.push_back(0);
    } // p. size () has to be the power of 2
    vector <cp> ans(p.size());
    fft(p.data(), ans.data(), p.size());
    return ans;
}

vector <ll> interpolate(vector <cp> p){
    int n = p.size();
    vector <cp> inv(n);
    fft(p.data(), inv.data(), n);
    vector <ll> ans(n);
    for(int i=0; i<n; i++)
        ans[i] = round(real(inv[i])/n);
    reverse(begin(ans)+1, end(ans));
    return ans;
}

void align(vector<int> &a, vector<int> &b) {
    int n = max(a.size(), b.size());
    while(a.size() < n)
        a.push_back(0);
    while(b.size() < n)
        b.push_back(0);
}

vector<ll> poly_multiply(vector<int> a, vector<int> b){
    align(a, b);
    auto A = evaluate(a);
    auto B = evaluate(b);
    for(int i=0; i<A.size(); i++)
        A[i] *= B[i];
    return interpolate(A);
}
