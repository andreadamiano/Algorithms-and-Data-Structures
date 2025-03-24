#include <iostream>
#include <vector>
#include <stack>

using E = int; 
enum InsertPosition {ROOT, LEFT, RIGHT};    

class Tree
{
    private: 
        struct Node
        {
            E element; 
            Node* left; 
            Node* right; 
            Node* parent; 
            Node (const E& element, Node* parent) : element(element), left(nullptr), right(nullptr), parent(parent) {}
        };

        Node* root; 
        int n; 

    public: 

        class Position; 

        class PositionList
        {
            private:
                std::vector<Position> children; 
            
            public:
                class Iterator 
                {
                    private: 
                        std::vector<Position>::iterator it; 
                    
                    public:
                        Iterator(std::vector<Position>::iterator it) : it(it) {}
                        Position& operator*() {return *it;} 
                        bool operator==(const Iterator& iterator) const {return it == iterator.it;}
                        bool operator!=(const Iterator& iterator) const {return it != iterator.it; }
                        Iterator& operator++() {++it; return *this; }
                        Iterator& operator--() {--it; return *this; }
                }; 

                PositionList(std::vector<Position>& children) : children(children) {}
                Iterator begin() {return Iterator(children.begin()); }
                Iterator end() {return Iterator(children.end()); }


        }; 

        class Position
        {
            public: 
                Position left() const {return Position(node->left);} 
                Position right() const {return Position(node->right);} 
                Position parent() const {return Position(node->parent);}
                bool isRoot() const {return node->parent == nullptr;}
                bool isExternal() const {return node->left == nullptr && node->right == nullptr; }
                Position(Node* node) : node(node) {} 
                E& operator* () const {return node->element; }

                friend class Tree; 

            private:    
                Node* node; 

        }; 

        Tree() : n(0), root(nullptr) {}
        ~Tree(); 
        int size() const {return n;} 
        bool empty() const {return n==0;}
        Position Root() const {return Position(root);} 
        PositionList positions(); 
        void addChild(const Position& parent, const E& element, InsertPosition position); 
        void prune (const Position& p); 
        Position removeaboveExternal(const Position& p); 

    protected:
        int clear(Node* node); 
        void preorderTraverse(const Position& p, std::vector<Position>& positions); 

}; 

Tree::~Tree()
{
    clear(root); 
}

int Tree::clear(Node* node)
{
    int count =0; 
    if (node)
    {
        count += clear(node->left); 
        count += clear(node->right); 

        delete node; 
        count++; 
    }
    return count; 
}

Tree::PositionList Tree::positions() 
{
    std::vector<Position> positions; 
    preorderTraverse(Root(), positions); 
    return PositionList(positions); 
}

void Tree::preorderTraverse(const Position& p, std::vector<Position>& positions)
{
    
    if (p.node == nullptr)
        return ; 

    std::stack<Position> stack; 
    stack.push(p); 

    while(!stack.empty())
    {
        //pop top postion from the stack 
        Position current = stack.top();
        stack.pop(); 
        positions.push_back(current); 

        //push all child node to the stack 
        if (current.node->right != nullptr)
            stack.push(current.right()); 
        if (current.node->left != nullptr)
            stack.push(current.left()); //push left least so that it will be retrieve first 
    }
}

void Tree::addChild(const Position& parent, const E& element, InsertPosition position)
{
    if (position == ROOT && parent.node == nullptr)
    {
        root = new Node(element, parent.node); 
    }
    else if (position == LEFT && parent.node->left == nullptr)
    {
        parent.node->left = new Node(element, parent.node); 
    }
    else if (position == RIGHT && parent.node->right == nullptr)
    {
        parent.node->right = new Node(element, parent.node); 
    }
    n++; 
}

void Tree::prune(const Position& p)
{
    //delete memory usage 
    int n_removed = clear(p.node); 

    //remove reference in parent's node
    if (p.isRoot())
    {
        root = nullptr; 
    }
    else if(p.parent().node != nullptr)
    {
        if(p.parent().node->left == p.node)
            p.parent().node->left = nullptr; 
        else if (p.parent().node->right == p.node)
            p.parent().node->right =nullptr; 
    }

    n-=n_removed; 
}

Tree::Position Tree::removeaboveExternal(const Position& p)
{
    Node* node = p.node; 
    Node* parent = p.node->parent; 
    Node* sibiling = (parent->left == node ? parent->right : parent->left); //the sibiling is the other node 

    if (parent == root)
    {
        root = sibiling; 
        sibiling->parent = nullptr; 
    }
    else
    {
        Node* grandparent = parent->parent; 
        if (parent == grandparent->left)
            grandparent->left = sibiling; 
        else
            grandparent->right = sibiling; 

        sibiling->parent = grandparent; 
    }

    delete node; 
    delete parent; 
    n-=2; 

    return Position(sibiling); 
}

int main ()
{
    Tree t; 

    t.addChild(t.Root(), 0, ROOT); 
    t.addChild(t.Root(), 1, LEFT); 
    t.addChild(t.Root(), 2, RIGHT); 


    std::cout << *t.Root() << "\n"; 
    std::cout << *(t.Root().left()) << "\n"; 
    std::cout << *(t.Root().right()) << "\n"; 

    std::cout << "binary tree positions: "; 
    auto positions = t.positions(); 
    for (auto it = positions.begin(); it != positions.end(); ++it)
        std::cout << **it << " "; 
    std::cout << "\n"; 

    //prune root node
    t.prune(t.Root()); 
    
    if (!t.empty())
    {
        std::cout << *t.Root() << "\n"; 
        std::cout << *(t.Root().left()) << "\n"; 
        std::cout << *(t.Root().right()) << "\n"; 
    }
    else
    {
        std::cout << "Tree is empty\n";
    }

}