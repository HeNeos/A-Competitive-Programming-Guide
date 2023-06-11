#define N 1000005

struct state{
    int len, link;
    bool terminal; //Is the state terminal ?
    map<char, int> next;
};

struct SuffixAutomaton{
    state st[N << 1];
    int cnt, last;
    vector <vi> iLink;
    vi occur;
    void init(){
        //root node is at index 0.
        cnt = 0, last = 0;
        st[0].len = 0; st[0].link = -1; st[0].terminal = 0;
        cnt++;
    }
    
    void sa_extend(char c){
        int cur = cnt++;
        st[cur].len = st[last].len + 1;
        st[cur].terminal = 0;
        int p = last;
        while(p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if(p == -1) st[cur].link = 0;
        else{
            int q = st[p].next[c];
            if(st[q].len == st[p].len + 1) st[cur].link = q;
            else{
                int clone = cnt++;
                st[clone].terminal = 0; st[clone].len = st[p].len + 1;
                st[clone].link = st[q].link; st[clone].next = st[q].next;
                st[cur].link = st[q].link = clone;
                while(p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
            }
        }
        last = cur;
    }
    
    void find_terminals(){
        int p = last;
        while(p) {
            st[p].terminal = 1;
            p = st[p].link;
        }
    }
    
    void addString(string s){
        init();
        for(int i=0; i<s.size(); i++) sa_extend(s[i]);
        find_terminals();
    }

    void genILink(){ // inverse links
        iLink.resize(last); 
        for(int v=1; v<last; v++) iLink[st[v].link].pb(v);
    }

    int getOccur(int i){
        if(occur[i] != -1) return occur[i];
        int ans = st[i].terminal;
        for(auto v:st[i].next)
            ans += getOccur(v.second);
        occur[i] = ans;
        return ans;
    }

    int matchString(string &q){
        int cur = 0; occur.resize(N, -1);
        for(int i=0; i<q.size(); i++){
            if (!st[cur].next.count(q[i])) return 0;
            cur = st[cur].next[q[i]];
        }
        return getOccur(cur);
    }

    void printSA(){
        for(int i = 0; i < cnt; i++) {
            cout << "i: " << i << '\n';
            cout << "Terminal: " << st[i].terminal << '\n';
            cout << "Transitions:\n"; 
            for(auto p : st[i].next)
                cout << p.first << " -> " << p.second << '\n';
            
            cout << "Suf Link: " << st[i].link << '\n';
            cout << '\n';
        }
    }
};
