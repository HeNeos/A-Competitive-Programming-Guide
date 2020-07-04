int TestMillerRabin[12] = {2,3,5,7,11,13,17,19,23,29,31,37};

ll mulmod(ll a, ll b, ll p){
	ll x = 0, y = a%p;
	while(b>0){
		if(b%2==1) x = (x+y)%p;
		y = (1LL*y*2)%p;
		b = b/2;
	}
	return x%p;
}

ll fastexpp(ll x, ll y, ll p){
	ll ans = 1;
	while(y > 0){
		if(y&1) ans = mulmod(ans,x,p);
		y = y>>1;
		x = mulmod(x,x,p);
	}
	return ans%p;
}

//Change fastexpp to fastexp for small numbers :)

bool isPrime(ll p){
	bool flag = true;
	if(p<=1) return false;
	for(int i=0; i<9; i++){
		int value = TestMillerRabin[i];
		if(value >= p) break;
		if(fastexpp(value,p,p) != value){
			flag = false;
			break;
		}
	}
	return flag;
}
