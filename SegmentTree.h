class SegmentTreeMax{
    public:
    int n;
    vector<long long> vect;
    SegmentTreeMax(int _n):n(_n){
        vect.resize(2*n);
        fill(vect.begin(), vect.end(), -MOD);
    }
    void modify(int p, long long value){
        for(vect[p+=n]=value; p>1; p>>=1){
            vect[p>>1]=max(vect[p],vect[p^1]);
        }
    }
    long long query(int l, int r){
        long long res=-MOD;
        for(l+=n, r+=n; l<r; l>>=1, r>>=1){
            if(l&1) res=max(res,vect[l++]);
            if(r&1) res=max(res,vect[--r]);
        }
        return res;
    }
    
};

class SegmentTreeMin{
    public:
    int n;
    vector<long long> vect;
    SegmentTreeMin(int _n):n(_n){
        vect.resize(2*n);
        fill(vect.begin(), vect.end(), 1e10);
    }
    void modify(int p, long long value){
        for(vect[p+=n]=value; p>1; p>>=1){
            vect[p>>1]=min(vect[p],vect[p^1]);
        }
    }
    long long query(int l, int r){
        long long res=1e10;
        for(l+=n, r+=n; l<r; l>>=1, r>>=1){
            if(l&1) res=min(res,vect[l++]);
            if(r&1) res=min(res,vect[--r]);
        }
        return res;
    }
    
};

class SegmentTreePlus{
    public:
    int n;
    vector<long long> vect;
    SegmentTreePlus(int _n):n(_n){
        vect.resize(2*n);
        fill(vect.begin(), vect.end(), 0);
    }
    void modify(int p, long long value){
        for(vect[p+=n]=value; p>1; p>>=1){
            vect[p>>1]=vect[p]+vect[p^1];
        }
    }
    long long query(int l, int r){
        long long res=0;
        for(l+=n, r+=n; l<r; l>>=1, r>>=1){
            if(l&1) res+=vect[l++];
            if(r&1) res+=vect[--r];
        }
        return res;
    }
    
};

//gcd segtree with children checking codeforces 914D
class SegmentTreeGcd{
    public:
    int n;
    vector<int> vect;
    SegmentTreeGcd(int _n):n(_n){
        vect.resize(2*n);
        fill(vect.begin(), vect.end(), 1);
    }
    void modify(int p, int value){
        for(vect[p+=n]=value; p>1; p>>=1){
            vect[p>>1]=__gcd(vect[p],vect[p^1]);
        }
    }
    int query(int l, int r){
        int res=vect[l+n];
        for(l+=n, r+=n; l<r; l>>=1, r>>=1){
            if(l&1) res=__gcd(res,vect[l++]);
            if(r&1) res=__gcd(res,vect[--r]);
        }
        return res;
    }
    
    bool works(int l, int r, int x){
        int badct=0;
        for(l+=n, r+=n; l<r; l>>=1, r>>=1){
            if(l&1){
                badct+=(bool)(vect[l++]%x);
            }
            
            else if(l+1<r && vect[l]%x && vect[l+1]%x){
                return false;
            }
            if(r&1){
                badct+=(bool)(vect[--r]%x);
            }
            
            else if(r-2>l && vect[r-1]%x && vect[r-2]%x){
                return false;
            }
            if(badct>1) return false;
        }
        return true;
    }
    
};
