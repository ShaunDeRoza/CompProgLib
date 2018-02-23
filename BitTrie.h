class Node{
    public:
    bool hasLeft, hasRight;
    int ct;
    Node* left;
    Node* right;
    Node(int _ct):hasLeft(0),hasRight(0),ct(_ct){}
    
    Node* addLeft(int val){
        if(hasLeft) left->ct++;
        else{
            hasLeft=true;
            left=new Node(val);
        }
        return left;
    }
    
    Node* addRight(int val){
        if(hasRight) right->ct++;
        else{
            hasRight=true;
            right=new Node(val);
        }
        return right;
    }
};

class Trie{
    public:
    vector<Node*> nodes;
    Node* root;
    int depth;
    
    Trie(int _depth=30):depth(_depth){
        root=new Node(1);
        auto curNode=root;
        for(int i=1; i<=depth+1; i++){
            curNode=curNode->addLeft(300000);
            nodes.push_back(curNode);
        }
    }
    
    void add(int val){
        int pos=(1<<depth);
        Node* curNode=root;
        while(pos){
            if(pos&val){
                curNode=curNode->addRight(1);
                nodes.push_back(curNode);
            }
            else{
                curNode=curNode->addLeft(1);
                nodes.push_back(curNode);
            }
            pos=(pos>>1);
        }
    }
    
    void rem(int val){
        int pos=(1<<depth);
        Node* curNode=root;
        while(pos){
            if(pos&val){
                curNode=curNode->right;
                curNode->ct--;
            }
            else{
                curNode=curNode->left;
                curNode->ct--;
            }
            pos=(pos>>1);
        }
    }
    int query(int val){
        int pos=(1<<depth);
        Node* curNode=root;
        int ans=0;
        while(pos){
            //cout<<pos<<endl;
            if(pos&val){
                if(curNode->hasLeft && curNode->left->ct){
                    ans+=pos;
                    curNode=curNode->left;
                }
                else curNode=curNode->right;
            }
            else{
                if(curNode->hasRight && curNode->right->ct){
                    ans+=pos;
                    curNode=curNode->right;
                }
                else curNode=curNode->left;
                
            }
            pos=(pos>>1);
        }
        return ans;
    }
    
};