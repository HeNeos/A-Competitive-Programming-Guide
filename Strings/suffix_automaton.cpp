#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
typedef vector<int> vi;
struct SuffixAutomaton {
	int N = 1; int lastp = 0;
	vi link{-1}, len{0}, pos{-1};
	vector<map<char,int>> edges{1}; vector<bool> isClone{0};
	//link[i]   : the parent of i
	//len[i]	: the length of the longest string in the ith class
	//edges[i]  : the labeled edges from node i
	//pos[i]	: position of node i
	vector<vi> iLink; // inverse links
	vi endpos; //size of endpos class
	vi pp; vi DFSOrder; //DFS arrays
	vector <bool> terminal; //terminals nodes
	int add(int p, char c){
		auto getEdge = [&]() {
			if (p == -1) return 0;
			int q = edges[p][c]; if (len[p]+1 == len[q]) return q;
			int clone = N++; link.pb(link[q]); link[q] = clone;
			len.pb(len[p]+1); edges.pb(edges[q]), pos.pb(pos[q]), isClone.pb(1);
			for (; ~p && edges[p][c] == q; p = link[p]) edges[p][c] = clone;
			return clone;
		};
		//if(edges[p].count(c)) return getEdge();// <- need if adding > 1 string
		int cur = N++; // make new state
		link.emplace_back(), len.pb(len[p]+1), edges.emplace_back(), pos.pb(pos[p]+1), isClone.pb(0);
		for(; ~p && !edges[p].count(c); p = link[p]) edges[p][c] = cur;
		int x = getEdge(); link[cur] = x; pp.pb(x);
		return cur;
	}

	void addString(string s){
		for(int i=0; i<s.size(); i++) lastp = add(lastp, s[i]);	
	}

	void suffixDFS(int x, vector <bool> &vis){
		for(auto v:edges[x]){
			if(!vis[v.second]) suffixDFS(v.second, vis);
		}
        vis[x] = true;
        DFSOrder.pb(x);
	}

	void findTerminals(){
		terminal.resize(N);
		int p = lastp;
		while(p){
			terminal[p] = 1;
			p = link[p];
		}
	}

	void buildEndPos(){
		endpos.resize(N); vector <bool> vis(N, false);
		for(int i=0; i<pp.size(); i++) endpos[pp[i]] = 1;
		suffixDFS(0, vis);
		for(int i=0; i<DFSOrder.size(); i++){
			int p = link[DFSOrder[i]];
            if(p == -1) continue;
            endpos[p] += endpos[DFSOrder[i]];
		}
	}

	void genILink(){ // inverse links
		iLink.resize(N); 
		for(int v=1; v<N; v++) iLink[link[v]].pb(v);
	}
	
	void getOccur(vi& oc, int v) {
		if (!isClone[v]) oc.pb(pos[v]); // terminal position
		for(int i=0; i<iLink[v].size(); i++) getOccur(oc, iLink[v][i]);
	}

	vector <ll> distinct;
	ll getDistinct(int x){ //# of distinct strings starting at state x, x = 0: all substrings
		if (distinct[x] != -1) return distinct[x];
		ll ans = terminal[x]; 
		for(auto v:edges[x]) ans += getDistinct(v.second);
		distinct[x] = ans;
		return ans;
	}

	vi matchString(string s) { // get all occurrences of s in automaton
		int cur = 0;
		for(int i=0; i<s.size(); i++){
			if (!edges[cur].count(s[i])) return {};
			cur = edges[cur][s[i]];
		}
		/*
		distinct.resize(N, -1);
		return getDistinct(cur);
		*/
		vi ans; getOccur(ans,cur); 
		for(int i=0; i<ans.size(); i++) ans[i] += 1-s.size(); // convert end pos -> start pos
		sort(ans.begin(), ans.end()); return ans;
	}

	ll countSubStrings(){
		ll ans = 1; 
		for(int i=1; i<N; i++) ans += len[i]-len[link[i]];
		return ans;
	}

	//DEBUG
	void printSA(){
		for(int i = 0; i <N; i++) {
			cout << "i: " << i << '\n';
			cout << "Terminal: " << terminal[i] << '\n';
			cout << "Transitions:\n"; 
			for(auto p : edges[i])
				cout << p.first << " -> " << p.second << '\n';
			
			cout << "Suf Link: " << link[i] << '\n';
			cout << '\n';
		}
	}
};



/*
// APPLICATIONS
// Suffix Array: Create suffix array of inverse string
	SuffixAutomaton S;
	string s;
	vi sa;
	void SuffixArray(int x = 0){
		if(!S.isClone[x]) sa.pb(s.size()-1-S.pos[x]);
		vector<pair<char,int>> chr;
		for(int i=0; i<S.iLink[x].size(); i++){
			chr.pb({s[S.pos[S.iLink[x][i]]-S.len[x]], S.iLink[x][i]});
		}
		sort(chr.begin(), chr.end());
		for(int i=0; i<chr.size(); i++) SuffixArray(chr[i].second);
	}
*/
