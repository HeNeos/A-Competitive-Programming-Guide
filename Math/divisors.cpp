//factorization[i] = (p,a): p^a
//Complexity = O(0.5*n^1/3)?

void generate_divisors(int n, int index, int d, vector<pair <int,int> > &factorization, vector <int> &ans){ 
	if(1LL*d*d > n) return;
	
	if(curIndex == factorization.size()){
		ans.push_back(d);
		if(d*d != n) ans.push_back(n/d); 
		return;
	}
	for(int i = 0; i <= factorization[index].second; ++i){
		generate_divisors(n, index+1, d, arr, ans); 
		d *= factorization[index].first;
	}
}
