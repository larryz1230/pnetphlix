#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    
    struct Node
    {
        Node* left;
        Node* right;

        KeyType key;
        ValueType val;
        
        Node(){
            left = nullptr;
            right = nullptr;
        }
    };
    
    
    class Iterator
    {
      public:
        Iterator()
        {
            // Replace this line with correct code.
            curr = 0;
        }
        
        Iterator(vector<Node*> v){
            for (int i = 0; i<v.size(); i++){
                itvec.push_back(v[i]);
            }
            curr = 0;
        }

        ValueType& get_value() const
        {
            return itvec[curr]->val;  // Replace this line with correct code.
        }

        bool is_valid() const
        {
            return curr<itvec.size();  // Replace this line with correct code.
        }

        void advance()
        {
            // Replace this line with correct code.
            curr++;
        }
        
      private:
        vector<Node*> itvec;
        int curr;
    };

    TreeMultimap()
    {
        n = nullptr;
    }

    ~TreeMultimap()
    {
        destructorHelper(n);
    }
    
    void printTree (){
        printTree(n);
    }
    
    void printTree ( const Node* p){
        if (p!=nullptr){
            printTree (p->left);
            cout << p->val << endl;
            printTree (p->right);
        }
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        insert (n, key, value);
    }
    
    

    Iterator find(const KeyType& key) const
    {
        vector<Node*>v;
        findHelper(v, key, n);  // Replace this line with correct code.
        return Iterator(v);
    }
    

private:
    
    Node* n;
    
    void insert (Node *p, const KeyType& key, const ValueType& value){
        if (n==nullptr){
            n = new Node;
            n->key = key;
            n->val = value;
            return;
        }

        if (key>p->key){
            if (p->right == nullptr){
                p->right = new Node;
                p->right->key = key;
                p->right->val = value;
            } else {
                insert (p->right, key, value);
            }
        }
        else if (key <= p->key){
            if (p->left==nullptr){
                p->left = new Node;
                p->left->key = key;
                p->left->val = value;
            } else {
                insert (p->left, key, value);
            }
        }
    }
    
    void findHelper (vector <Node*>& v, const KeyType& key, Node* p) const{
        if (p!=nullptr){
            findHelper(v, key, p->left);
            if (p->key==key){
                v.push_back(p);
            }
            findHelper(v, key, p->right);
        }
    }
    
    void destructorHelper(Node* n){
        if (n!=nullptr){
            destructorHelper(n->right);
            destructorHelper(n->left);
            delete n;
        }
    }

};

#endif // TREEMULTIMAP_INCLUDED
