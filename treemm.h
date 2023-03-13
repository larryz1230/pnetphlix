
#ifndef TREE_INCLUDED
#define TREE_INCLUDED

#include <iostream>
#include <vector>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
    
private:
    
    struct Node
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
    
    Node* n;
    
    
    void insert (Node *p, const KeyType& key, const ValueType& value){
        if (n==nullptr){
            n = new Node(key, value);
            return;
        }
        
        if (key==p->key){
            p->val.push_back(value);
            return;
        }
        
        if (key>p->key){
            if (p->right == nullptr){
                p->right = new Node(key, value);
                return;
            } else {
                insert (p->right, key, value);
            }
        }
        else if (key < p->key){
            if (p->left==nullptr){
                p->left = new Node(key, value);
                return;
            } else {
                insert (p->left, key, value);
            }
        }
        
    }
    
    Node* findHelper (const KeyType& key, Node* p) const{
        if (p!=nullptr){
//            std::cout << p->key << std::endl;
            
            if (p->key==key){
                return p;
            } else if (p->key>key){
                return findHelper(key, p->left);;
            } else {
                return findHelper(key, p->right);
            }
        }
        return nullptr;
    }
    
    void destructorHelper(Node* n){
        if (n!=nullptr){
            destructorHelper(n->right);
            destructorHelper(n->left);
            delete n;
        }
    }
    
    
    
    
    
public:
    
    class Iterator
    {
    public:
        Iterator()
        {
            // Replace this line with correct code.
            curr = 0;
        }
        
        Iterator(Node* v){
            if (v!=nullptr){
                for (int i = 0; i<v->val.size(); i++){
                    itvec.push_back(&v->val[i]);
                }
            }
            curr = 0;
            
        }
        
        ValueType& get_value() const
        {
            if (!is_valid()){
                std::cout << "not defined" << std::endl;
                //                return NULL;
            }
            return *itvec[curr];  // Replace this line with correct code.
            
        }
        
        bool is_valid() const
        {
            return curr<itvec.size();
        }
        
        void advance()
        {
            curr++;
        }
        
    private:
        std::vector<ValueType*> itvec;
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
    
    void printTree (const Node* p){
        if (p!=nullptr){
            printTree (p->left);
            for (int i=0; i<p->val.size(); i++){
                std::cout << p->val.at(i) << std::endl;
            }
            printTree (p->right);
        }
    }
    
    void insert(const KeyType& key, const ValueType& value)
    {
        insert(n, key, value);
    }
    
    
    
    Iterator find(const KeyType& key) const
    {   // Replace this line with correct code.
        return Iterator(findHelper(key, n));
    }
    
};

#endif // TREE_INCLUDED
