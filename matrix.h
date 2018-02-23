//matrix mult


vector<vector<long long>> operator*(const vector<vector<long long>>&  mat1, const vector<vector<long long>>& mat2){
    int n1=mat1.size(), m1=mat1[0].size(), n2=mat2.size(), m2=mat2[0].size();
    vector<vector<long long>> ans(n1,vector<long long>(m2,0));
    for(int i=0; i<n1; i++){
        for(int j=0; j<m2; j++){
            for(int k=0; k<m1; k++){
                ans[i][j]+=mat1[i][k]*mat2[k][j];
            }
        }
    }
    return ans;
}

//matrix powers

vector<vector<long long>> matPow(const vector<vector<long long>>& mat, long long p){

auto ans=mat, prod=mat;
for(int i=0; i<ans.size(); i++){
    for(int j=0; j<ans.size(); j++){
       ans[i][j]=i==j;
    }
}

while(p){
        if(p&1){
            ans=ans*prod;
        }
        prod=prod*prod;
        p=p>>1;
    }
    return ans;    


}