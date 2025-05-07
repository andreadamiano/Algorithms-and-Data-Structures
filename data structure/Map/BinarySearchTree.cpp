#include <iostream>
#include <stack>
#include <queue>

using E = int; 

template <typename C>
class Map
{
    private:
        struct Elem
        {
            int key; 
            E value; 
        };
        struct Node
        {
            Node* right; 
            Node* left; 
            Node* parent; 
            Elem elem; 

            Node(const Elem _elem, Node* _parent) : elem(_elem), parent(_parent), right(nullptr), left(nullptr) {}
        }; 

        C isLess; 
        int n;  
        Node* root; 

    public:
        class Iterator
        {
            private:
                Node* node; 

            public:
                Iterator(Node* _node) : node(_node) {}
                Iterator left() {return Iterator(node->left); }
                Iterator right() {return Iterator(node->right); }

                Elem operator* () {return node->elem; }

                friend class Map; 

        };      
        


        Map(): n(0), root(nullptr) {}
        ~Map() {}
        
        bool empty() const; 
        void insert (const int key, const E value); 
        void print() const ; 

        Iterator Root() {return Iterator(root); }

    public:
        void preOrderTraverse(const Iterator& node) const;
        void postOrderTraverse(Iterator&& node) const;
        void inOrderTraverse(Iterator&& node) const;
        void levelorderTraverse(Iterator&& node) const;


    protected:
        void printTree(Node* node, int depth) const; 

};

template <typename C>
bool Map<C>::empty() const 
{
    return n==0; 
}

template <typename C>
void Map<C>::insert(const int key, const E value)
{
    if(empty())
    {
        root = new Node({key, value}, nullptr); 
        ++n; 
    }
    else
    {
        Node* current = root; 
        Node* parent = nullptr; 

        while(current != nullptr)
        {
            parent = current; 
            if (isLess(key, current->elem.key))  
                current = current->left; //go to the left node
            else if (isLess(current->elem.key, key))
                current = current->right; //go to the right node

            else //if the key already exists
            {
                current->elem.value = value; //update existing value
            }
        }
        Node* newNode = new Node({key, value}, parent); 

        if (isLess(key, parent->elem.key))  
            parent->left = newNode; 
        else if (isLess(parent->elem.key, key))
            parent->right = newNode; 

        ++n; 
    }
}

template <typename C> 
void Map<C>::preOrderTraverse(const Iterator& node) const 
{
    if (node.node == nullptr)
        return; 

    std::stack<Node*> stack; 
    stack.push(node.node); 

    while(!stack.empty())
    {  

        Node* current = stack.top(); 
        stack.pop(); 
        std::cout << current->elem.key << " "; 

        //traverse the child nodes
        if (current->right != nullptr)
            stack.push(current->right);
        
        if (current->left != nullptr)
            stack.push(current->left); 
    }
}

template <typename C>
void Map<C>::inOrderTraverse(Iterator&& node) const
{
    if (node.node == nullptr)
        return; 


    inOrderTraverse(node.left()); 

    std::cout << (*node).key << " "; 
    
    inOrderTraverse(node.right()); 
}

template <typename C>
void Map<C>::postOrderTraverse (Iterator&& node) const 
{   
    if (node.node == nullptr)
        return; 
    postOrderTraverse(node.left()); 
    postOrderTraverse(node.right());
    
    std::cout << (*node).key  << " "; 
}

template < typename C>
void Map<C>::levelorderTraverse(Iterator && node) const 
{
    if (node.node == nullptr)
        return; 

    std::queue<Node*> queue; 
    queue.push(node.node); 

    while (!queue.empty())
    {
        Node* current = queue.front(); 
        queue.pop(); 

        std::cout << current->elem.key << " "; 

        if (current->left != nullptr)
            queue.push(current->left); 
        
        if (current->right != nullptr)
            queue.push(current->right); 
    }

}

template <typename C>
void Map<C>::print() const 
{   
    printTree(root, 0); 
}

template <typename C>
void Map<C>::printTree(Node* node, int depth) const 
{
    if (node == nullptr)
        return; 

    printTree(node->right, depth +1); 

    for (int i =0; i< depth; ++i)
        std::cout << "   "; 
    
    std::cout << node->elem.key << "\n"; 

    printTree(node->left, depth +1); 
}

class Comparator
{
    public:
        bool operator() (const int first, const int second)
        {
            return first < second; 
        }
}; 

int main ()
{
    Map<Comparator> map; 

    map.insert(42, 735); 
    map.insert(0, 150);   
    map.insert(6, 23);    
    map.insert(17, 892);  
    map.insert(88, 123);  
    map.insert(3, 456);   
    map.insert(91, 789);  
    map.insert(55, 321);  
    map.insert(10, 654);  
    map.insert(72, 987);   


    // map.preOrderTraverse(map.Root()); 
    // std::cout << "\n"; 
    // map.print(); 
    // std::cout << "\n"; 
    
    // map.inOrderTraverse(map.Root()); 

    // map.postOrderTraverse(map.Root());

    map.levelorderTraverse(map.Root()); 
}