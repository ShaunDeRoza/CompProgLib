#include <bits/stdc++.h>
 
using namespace std;
 
const long long MOD=1e9+7;
const double PI=3.14159265359;


//dijimon when we have an adjacency list representation using pairs
vector<int> dijimon(vector<vector<pair<int,int>>> graph, int source){
    int n=graph.size();
    vector<int> dists(n,MOD);
    vector<bool> mark(n,false);
    dists[source]=0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({dists[source],source});
    while(!pq.empty()){
        auto cur=pq.top();
        pq.pop();
        int v=cur.second;
        //cout<<v<<" "<<dists[v]<<" "<<cur.first<<endl;
        if(mark[v]) continue;
        mark[v]=true;
        for(auto& p:graph[v]){
            if(dists[p.first]>dists[v]+p.second){
                dists[p.first]=dists[v]+p.second;
                pq.push({dists[p.first],p.first});
            }
        }
    }
    return dists;
    
}

//dijimon when we have an adjacency matrix representation
vector<int> dijimonAdjMat(vector<vector<int>> graph, int source){
    int n=graph.size();
    vector<int> dists(n,MOD);
    vector<bool> mark(n,false);
    dists[source]=0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({dists[source],source});
    while(!pq.empty()){
        auto cur=pq.top();
        pq.pop();
        int v=cur.second;
        //cout<<v<<" "<<dists[v]<<" "<<cur.first<<endl;
        if(mark[v]) continue;
        mark[v]=true;
        for(int i=0; i<n; i++){
            if(graph[i][v] && dists[i]>dists[v]+graph[i][v]){
                dists[i]=dists[v]+graph[i][v];
                pq.push({dists[i],i});
            }
        }
    }
    return dists;
    
}

    
