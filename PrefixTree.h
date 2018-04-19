
//Node for prefix tree
class Node{
    public:
    char val;
    int ct;
    list<Node*>* children;
    Node(char ch):val(ch),ct(1){
        children=new list<Node*>();
    }
};

//Prefix tree class
class Trie{
    public:
    list<Node*> nodes;
    Node* root;
    Trie(){
        root=new Node('$');
        nodes=list<Node*>();
    }
    //add string in a lexographically sorted order
    void addEnd(string& s){
        int sz=s.size(), pos=0;
        list<Node*>* curList=root->children;
        while(pos<sz){
            if(!(curList->size()) || curList->back()->val !=s[pos]){
                Node* node=new Node(s[pos]);
                curList->push_back(node);
                nodes.push_back(node);
                curList=node->children;
            }
            else{
                curList->back()->ct++;
                curList=curList->back()->children;
            }
            pos++;
        }
    }
};
