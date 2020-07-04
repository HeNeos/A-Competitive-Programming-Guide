int mobius[N];

void cmob(){
	mobius[1] = 1;
    for(int i=2; i<N; i++){
        if(lpf[i] == i) mobius[i] = -1;
        else{
            if(lpf[i/lpf[i]] == lpf[i]) mobius[i] = 0;
            else mobius[i] = -1*mobius[i/lpf[i]];
        }
    }
}
