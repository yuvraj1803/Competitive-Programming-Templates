const int N = 1e6;
bool sieve[N];

void pc(){
	memset(sieve, 1, sizeof(sieve));
	sieve[0] = sieve[1] = 0;
	sieve[2] = 1;
	for(int i=2;i*i<=N;i++){
		if(sieve[i]){
			for(int j=i*i;j<=N;j+=i){
				sieve[j] = 0;
			}
		}
	}
}