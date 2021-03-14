struct SuffixAutomaton {
	int N = 1; int lastp = 0;
	vi link{-1}, len{0}, pos{-1};
	vector<map<char,int>> edges{1}; vector<bool> isClone{0};
	//link[i]   : the parent of i
	//len[i] : the length of the longest string in the ith class
	//edges[i]  : the labeled edges from node i
	vector<vi> iLink; // inverse links
	vector<int> terminals;
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
		int x = getEdge(); link[cur] = x; 
		return cur;
	}

	void addString(string s){
		for(int i=0; i<s.size(); i++) lastp = add(lastp, s[i]);	
	}

	void genILink(){ // inverse links
		iLink.resize(N); 
		for(int v=1; v<N; v++) iLink[link[v]].pb(v);
	} 
};


/*
	// APPLICATIONS

  // Suffix Array:
  SuffixAutomaton S; string s; vi sa;
  void SuffixArray(int x = 0){
    if(!S.isClone[x]) sa.pb(s.size()-1-S.pos[x]);
    vector<pair<char,int>> chr;
    for(int i=0; i<S.iLink[x].size(); i++){
      chr.pb({s[S.pos[S.iLink[x][i]]-S.len[x]], S.iLink[x][i]});
    }
    sort(chr.begin(), chr.end());
    for(int i=0; i<chr.size(); i++) SuffixArray(chr[i].second);
  }
  
  void getAllOccur(vi& oc, int v) {
		if (!isClone[v]) oc.pb(pos[v]); // terminal position
		each(u,iLnk[v]) getAllOccur(oc,u);
	}
	vi allOccur(str s) { // get all occurrences of s in automaton
		int cur = 0;
		each(x,s) {
			if (!edges[cur].count(x)) return {};
			cur = edges[cur][x]; }
		vi oc; getAllOccur(oc,cur); each(t,oc) t += 1-sz(s); // convert end pos -> start pos
		sort(all(oc)); return oc;
	}
	vl distinct;
	
	ll getDistinct(int x) { // # of distinct strings starting at state x
		if (distinct[x]) return distinct[x];
		distinct[x] = 1; each(y,edges[x]) distinct[x] += getDistinct(y.s);
		return distinct[x];
	}
	ll numDistinct() { // # distinct substrings including empty
		distinct.rsz(N); return getDistinct(0);
	}
	
	ll numDistinct2() { // assert(numDistinct() == numDistinct2());
		ll ans = 1; FOR(i,1,N) ans += len[i]-len[link[i]];
		return ans;
	} 
*/
