//max flow using Edmonds-Karp and an adjacency matrix

vector<vector<int>> maxFlow(vector<vector<int>> graph){
    int n=graph.size();
    vector<vector<int>> fl(n,vector<int>(n,0)), res=graph;
    
    bool works=true;
    while(works){
        int maxCap=MOD;
        vector<int> preds(n,-1);
        queue<int> q;
        q.push(0);
        while(q.size() && preds[n-1]==-1){
            int cur=q.front();
            q.pop();
            for(int i=0; i<n; i++){
                if(res[cur][i] && preds[i]==-1){
                    preds[i]=cur;
                    q.push(i);
                }
            }
        }
        if(preds[n-1]==-1){
            works=false;
        }
        else{
            int cur=n-1;
            while(cur){
                maxCap=min(maxCap, res[preds[cur]][cur]);
                cur=preds[cur];
            }
            cur=n-1;
            while(cur){
                res[preds[cur]][cur]-=maxCap;
                res[cur][preds[cur]]+=maxCap;
                if(graph[preds[cur]][cur]) fl[preds[cur]][cur]+=maxCap;
                else fl[cur][preds[cur]]-=maxCap;
                cur=preds[cur];
            }
        }
        
    }
    
    return fl;
    
}


//max flow using Dinics and an adjacency list
class Edge{
    public:
    int cap,flow,dest;
    bool inGraph;
    Edge *flEdgePair, *resEdgePair;
    Edge(int _dest, int _cap, bool ing, int _flow=0):dest(_dest),inGraph(ing),
    cap(_cap), flow(_flow){}
    
    void addFlow(int fl){
        cap-=fl;
        resEdgePair->cap+=fl;
        if(inGraph) flEdgePair->flow+=fl;
        else flEdgePair->flow-=fl;
    }
};

class Dinic{
    public:
    vector<vector<Edge*>> flow, res;
    vector<int> dists, preds;
    
    int S,n,T;
    Dinic(vector<vector<pair<int,int>>>& net):S(0), n(net.size()), T(n-1){
        flow.resize(n);
        res.resize(n);
        dists.resize(n);
        preds.resize(n);
		fill(preds.begin(), preds.end(),-1);
        
        for(int i=0; i<n; i++){
            for(auto p:net[i]){
                Edge* e1=new Edge(p.first, p.second, true);
                Edge* e2=new Edge(i, 0, false);
                Edge* e3=new Edge(p.first, p.second, true);
                
                e1->flEdgePair=e3;
                e2->flEdgePair=e3;
                e1->resEdgePair=e2;
                e2->resEdgePair=e1;
                flow[i].push_back(e3);
                res[i].push_back(e1);
                res[p.first].push_back(e2);
            }
        }
    }
    bool bfs(){
        fill(dists.begin(), dists.end(),-1);
        queue<int> q;
        q.push(S);
        dists[S]=0;
        while(q.size()){
            int cur=q.front();
            q.pop();
            for(auto e:res[cur]){
                if(e->cap && dists[e->dest]==-1){
                    dists[e->dest]=dists[cur]+1;
                    q.push(e->dest);
                }
            }
        }
        return dists[T]!=-1;
    }
    
    void dfs(){
        vector<int> ep(n);
        vector<bool> dead(n);
        while(!dead[S]){
            //vector<int> preds(n,-1);
            stack<int> st;
            st.push(0);
            while(st.size()){
                int cur=st.top();
                //cout<<cur<<endl;
                if(cur==T) break;
                while(ep[cur]<res[cur].size() && (dead[res[cur][ep[cur]]->dest] ||
                dists[res[cur][ep[cur]]->dest]!=dists[cur]+1 || 
                res[cur][ep[cur]]->cap==0)){
                    ep[cur]++;
                }
                if(ep[cur]==res[cur].size()){
                    dead[cur]=true;
                    st.pop();
                }
                else{
                    preds[res[cur][ep[cur]]->dest]=cur;
                    st.push(res[cur][ep[cur]]->dest);
                }
            }
            if(st.size() && st.top()==T){
                //cout<<st.size()<<endl;
                int flVal=1e9;
                int cur=T;
                while(cur!=S){
                    //cout<<cur<<endl;
                    cur=preds[cur];
                    flVal=min(flVal,res[cur][ep[cur]]->cap);
                }
                cur=T;
                while(cur!=S){
                    cur=preds[cur];
                    res[cur][ep[cur]]->addFlow(flVal);
                }
            }
            else{
                dead[S]=true;
            }
            
        }
        
    }
    
    vector<vector<Edge*>> maxflow(){
        //bfs();
        //dfs();
        while(bfs()){
            dfs();
        }
        return flow;
    }
    
    
};

//max flow using push relabel and an adjacency list
class Edge{
    public:
    int cap,flow,dest;
    bool inGraph;
    Edge *flEdgePair, *resEdgePair;
    Edge(int _dest, int _cap, bool ing, int _flow=0):dest(_dest),inGraph(ing),
    cap(_cap), flow(_flow){}
    
    void addFlow(int fl){
        cap-=fl;
        resEdgePair->cap+=fl;
        if(inGraph) flEdgePair->flow+=fl;
        else flEdgePair->flow-=fl;
    }
};

class PushRelabel{
    public:
    vector<vector<Edge*>> flow, res;
    vector<int> heights, epos, excess;
    list<int> L;
    
    
    int S,n,T;
    PushRelabel(vector<vector<pair<int,int>>>& net):S(0), n(net.size()), T(n-1){
        flow.resize(n);
        res.resize(n);
        heights.resize(n);
        epos.resize(n);
        excess.resize(n);
        
        
        for(int i=0; i<n; i++){
            for(auto p:net[i]){
                Edge* e1=new Edge(p.first, p.second, true);
                Edge* e2=new Edge(i, 0, false);
                Edge* e3=new Edge(p.first, p.second, true);
                
                e1->flEdgePair=e3;
                e2->flEdgePair=e3;
                e1->resEdgePair=e2;
                e2->resEdgePair=e1;
                flow[i].push_back(e3);
                res[i].push_back(e1);
                res[p.first].push_back(e2);
            }
        }
        
        heights[S]=n;
        
        for(int i=0; i<res[0].size(); i++){
            if(res[0][i]->inGraph){
                excess[res[0][i]->dest]=res[0][i]->cap;
                res[0][i]->addFlow(res[0][i]->cap);
            }
        }
        
    }
    void push(int i, int j){
        int fl=min(excess[i], res[i][j]->cap);
        res[i][j]->addFlow(fl);
        excess[i]-=fl;
        excess[res[i][j]->dest]+=fl;
    }
    void relabel(int i){
        int h2=heights[i];
        for(int j=0; j<res[i].size(); j++){
            if(res[i][j]->cap) h2=min(h2,heights[res[i][j]->dest]);
        }
        heights[i]=h2+1;
    }
    void discharge(int i){
        while(excess[i]){
            if(epos[i]==res[i].size()){
                relabel(i);
                epos[i]=0;
            }
            else if(res[i][epos[i]]->cap>0 && heights[i]==heights[res[i][epos[i]]->dest]+1){
                push(i,epos[i]);
            }
            else epos[i]++;
        }
        
    }
    vector<vector<Edge*>> maxFlow(){
        for(int i=1; i<T; i++){
            if(excess[i]) L.push_front(i);
            else L.push_back(i);
        }
        auto it=L.begin();
        while(it!=L.end()){
            int oh=heights[*it];
            discharge(*it);
            if(oh!=heights[*it]){
                L.push_front(*it);
                L.erase(it);
                it=L.begin();
            }
            it++;
        }
        return flow;
    }
    
};


