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