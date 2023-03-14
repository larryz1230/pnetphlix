
#ifndef TREE_INCLUDED
#define TREE_INCLUDED

#include <iostream>
#include <vector>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
    
private:
    
    struct Node     //private node struct to hold info
    {
        Node* left;
        Node* right;
        
        KeyType key;
        std::vector<ValueType> val;
        
        Node(KeyType m_key, ValueType m_val){
            key = m_key;
            val.push_back(m_val);
            left = nullptr;
            right = nullptr;
        }
    };
    
    Node* n;    //private node pointer (head node)
    
    
    void insert (Node *p, const KeyType& key, const ValueType& value){
        if (n==nullptr){        //if this is the first node
            n = new Node(key, value);    //set n to new node, created with these values
            return;
        }
        
        if (key==p->key){       //if a node has been created with this key
            p->val.push_back(value);    //add to vector
            return;
        }
        
        if (key>p->key){        //if curr node's key is greater than tree's key
            if (p->right == nullptr){      //if right's empty, insert
                p->right = new Node(key, value);
                return;
            } else {        //other wise, recurse into the right subtree.
                insert (p->right, key, value);
            }
        }
        else if (key < p->key){ //if curr node's key is less than tree's key
            if (p->left==nullptr){      //if lefts's empty, insert
                p->left = new Node(key, value);
                return;
            } else {
                insert (p->left, key, value);       //other wise, recurse into the left subtree.
            }
        }
        
    }
    
    Node* findHelper (const KeyType& key, Node* p) const{       //binary search
        if (p!=nullptr){
            if (p->key==key){       //if found, return
                return p;
            } else if (p->key>key){     //if less, search left
                return findHelper(key, p->left);;
            } else {
                return findHelper(key, p->right);       //if greater, search right
            }
        }
        return nullptr;
    }
    
    void destructorHelper(Node* n){
        if (n!=nullptr){        //if node is null, return
            destructorHelper(n->right);     //else recurse left and right
            destructorHelper(n->left);
            delete n;       //and delete the node
        }
    }
    
    
    
    
    
public:
    
    class Iterator
    {
    public:
        Iterator()
        {
            curr = 0;
        }
        
        Iterator(Node* v){
            if (v!=nullptr){        //if not null
                for (int i = 0; i<v->val.size(); i++){
                    itvec.push_back(&v->val[i]);        //loop through v's vector and insert into itvec
                }
            }
            curr = 0;
            
        }
        
        ValueType& get_value() const
        {
            return *itvec[curr];  // Replace this line with correct code.
            
        }
        
        bool is_valid() const
        {
            return curr<itvec.size();       //check if vector has a value at current index
        }
        
        void advance()
        {
            curr++;
        }
        
    private:
        std::vector<ValueType*> itvec;      //to store values
        int curr;   //index and advance
    };
    
    TreeMultimap()
    {
        n = nullptr;        //set n as null initially
    }
    
    ~TreeMultimap()
    {
        destructorHelper(n);    //call helper
    }
    
    void insert(const KeyType& key, const ValueType& value)     //call recursive helper
    {
        insert(n, key, value);
    }
    
    
    Iterator find(const KeyType& key) const
    {
        return Iterator(findHelper(key, n));    //call helper
    }
    
};

#endif // TREE_INCLUDED
