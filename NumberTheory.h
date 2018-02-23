//get the gcd of a,b
long long gcd(long long a, long long b){
    if(b>a) return gcd(b,a);    
    while(a%b){
        long long r=a%b;
        a=b;
        b=r;       
    }
    return b;
}

//get all primes <= stop 
vector<int> getPrimes(int stop){
    int sieveStop=ceil(sqrt(stop));
    vector<int> psj;
    for(int i=2; i<=sieveStop; i++){
        bool isP=true;
        for(int j=2; j<i && isP; j++){
            isP=i%j;
        }
        if(isP) psj.push_back(i);
    }
    
    vector<bool> primesb(stop+1,true);
    for(int j:psj){
        for(int i=2; i*j<=stop; i++){
            primesb[i*j]=false;
        }
    }
    vector<int> ans;
    for(int i=2; i<=stop; i++){
        if(primesb[i]) ans.push_back(i);
    }
    return ans;
}

//calcualte the mobius function
int mu(int d, vector<int>& primes){
    int ct=0;
    for(int p:primes){
        if(!(d%p)){
            ct++;
            d/=p;
            if(!(d%p)) return 0;
        }
    }
    ct+=(d!=1);
    return (ct%2)?-1:1;
}

//calcualte powers mod m
int modpow(int x, int n, int m) {
    if (n == 0) return 1%m;
    long long u = modpow(x,n/2,m);
    u = (u*u)%m;
    if (n%2 == 1) u = (u*x)%m;
    return u;
}

