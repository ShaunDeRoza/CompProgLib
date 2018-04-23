template<class T> class Point2D{
    public:
    T x,y;
    int pos;
    Point2D(){}
    Point2D(T _x, T _y, int _pos):x(_x), y(_y), pos(_pos){}
    void disp(){
        cout<<x<<" "<<y<<" "<<pos<<endl;
    }
    Point2D<T> operator +(Point2D<T> pt){
        return Point2D<T>(x+pt.x, y+pt.y, -1);
    }
    Point2D<T> operator -(Point2D<T> pt){
        return Point2D<T>(x-pt.x, y-pt.y, -1);
    }
};

template<class T> class ConvexHull{
    public:
    vector<Point2D<T>> points;
    ConvexHull(vector<Point2D<T>> pts):points(pts.begin(),pts.end()){}
    
    T crossProd(Point2D<T> v1, Point2D<T> v2){
        return v1.x*v2.y-v2.x*v1.y;
    }
    
    T dotProd(Point2D<T> v1, Point2D<T> v2){
        return v1.x*v2.x+v1.y*v2.y;
    }
    
    bool lt(Point2D<T> base, Point2D<T> p1, Point2D<T> p2){
        if(p1.pos==base.pos) return true;
        if(p2.pos==base.pos) return false;
        auto v1=p1-base, v2=p2-base;
        auto cp=crossProd(v1,v2);
        return (cp>0 ||(!cp && (dotProd(v1,v1)<dotProd(v2,v2))));
    }
    vector<Point2D<T>> grahamScan(bool removeColin=true){
        auto ps=*min_element(points.begin(), points.end(), 
        [](auto &p1, auto & p2){return p1.x<p2.x||(p1.x==p2.x && p1.y<p2.y);});
        sort(points.begin(),points.end(), [ps, this](auto p1, auto p2){return this->lt(ps,p1,p2);});
        vector<Point2D<T>> ans;
        ans.push_back(ps);
        int n=points.size();
        if(removeColin){
            for(int i=1; i<n; i++){
                while(ans.size()>=2 && crossProd(ans[ans.size()-1]-ans[ans.size()-2], points[i]-ans[ans.size()-1])<=0){
                    ans.pop_back();
                }
                ans.push_back(points[i]);
            }
        }
        else{
            for(int i=1; i<n; i++){
                while(ans.size()>=2 && crossProd(ans[ans.size()-1]-ans[ans.size()-2], points[i]-ans[ans.size()-1])<0){
                    ans.pop_back();
                }
                ans.push_back(points[i]);
            }
        }
        return ans;
    }
    
};

//convex hull trick with pointer walk

class CHT{
public:
  vector<pair<long long, long long>> lines;
  int pos;
  CHT():pos(0){}
  
  //adding lines to the hull

  bool isBad(int l1, int l2, int l3){
    long long m1=lines[l1].first, m2=lines[l2].first, m3=lines[l3].first;
    long long c1=lines[l1].second, c2=lines[l2].second, c3=lines[l3].second;
    return (__int128)(c1-c3)*(m2-m1)<(__int128)(c1-c2)*(m3-m1);
  }
  void add(long long m, long long c){
    lines.push_back(make_pair(m,c));
    
    int lsz=lines.size();
    while(lsz>=3 && isBad(lsz-3,lsz-2,lsz-1)){
      lines.erase(lines.end()-2);
      lsz=lines.size();
    }
    

  }
  
  //using a pointer walk to find the line that gives the largest value at a point
  long long query(long long x){
    int lsz=lines.size();

    
    if(pos>=lsz)
      pos=lsz-1;
    while(pos<lsz-1 && lines[pos].first*x+lines[pos].second<lines[pos+1].first*x
	  +lines[pos+1].second){
      pos++;
    } 
    
    return lines[pos].first*x+lines[pos].second;
  }

  
};

