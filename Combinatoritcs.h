
vector<vector<int>> ncr(25,vector<int>(25,0)); 
ncr[0][0]=1;
for(int n=1;n<25; n++){
	ncr[n][0]=1;
    for(int r=1; r<=n; r++){
		ncr[n][r]=ncr[n-1][r-1]+ncr[n-1][r];
		//cout<<n<<" "<<r<<" "<<ncr[n][r]<<endl; 
	}
}

//combinatorial bitmask

class CBM{
    public:
    vector<pair<long long,int>> elems;
    vector<int> starts;
    CBM(vector<long long> vi){
        sort(vi.begin(),vi.end(), greater<long long>());
        int sz=vi.size();
        elems.push_back(make_pair(vi[0], 1));
        for(int i=1; i<sz; i++){
            if(vi[i]==vi[i-1]){
                elems.back().second++;
            }
            else{
                elems.push_back(make_pair(vi[i],1));
            }
        }
        if(elems.size()>30) elems.resize(30);
        
        sz=elems.size();
        starts.resize(sz);
        starts[0]=0;
        for(int i=1; i<sz; i++){
            int inc=1;
            while(1<<inc <= elems[i-1].second){
                inc++;
            }
            starts[i]=starts[i-1]+inc;
            
        }
        
    }
    
    int getMaskEnd(int k){
        int ct=0, mask=0;
        for(int i=0; i<elems.size() && ct<k; i++){
            int goal=k-ct;
            int val=min(goal, elems[i].second);
            ct+=val;
            mask+=val<<starts[i];
        }
        return mask;
    }
    bool checkK(int k){
        int mend=getMaskEnd(k);
        for(int mask=0; mask<=mend; mask++){
            //cout<<mask<<endl;
            
            long long prod1=1, prod2=1;
            bool works=true;
            int rem=k;
            for(int i=0; i<elems.size(); i++){
                int avail=min(rem, elems[i].second);
                int ct1, ct2;
                if(i==elems.size()-1){
                    ct1=mask>>starts[i];
                }
                else{
                    int temp=mask>>starts[i];
                    int m=(1<<(starts[i+1]-starts[i]))-1;
                    ct1=m&temp;
                }
                
                if(ct1>avail){
                    works=false;
                    break;
                }
                ct2=avail-ct1;
                //cout<<avail<<endl;
                //cout<<ct1<<endl;
                //cout<<ct2<<endl;
                
                for(int j=0; j<ct1; j++){
                    prod1*=elems[i].first;
                }
                for(int j=0; j<ct2; j++){
                    prod2*=elems[i].first;
                }
                rem-=avail;
                
            }
            //cout<<prod1<<" "<<prod2<<" "<<works<<" "<<mask<<endl;
            if(works && ((h*prod1>=a && w*prod2>=b) || (h*prod1>=b && w*prod2>=a))){
                return true;
            }
        }
        return false;
    }
    
    
    void disp(){
        cout<<"elements \n";
        for(auto p:elems){
            cout<<p.first<<" "<<p.second<<endl;
        }
        cout<<"starts \n";
        for(int i:starts){
            cout<<i<<endl;
        }
        
    }
    
    
};