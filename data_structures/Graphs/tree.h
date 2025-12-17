#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using E = int; 

class Tree
{
    private:
        struct Node
        {
            E element; 
            Node* parent; 
            std::vector<Node*> children; 
            Node (const E& element, Node* parent = nullptr) : element(element), parent(parent) {}
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
                E& operator*() const {return node->element;} 
                Position parent() const; 
                PositionList children() const; 
                bool isRoot() const; 
                bool isExternal() const; 
                Position(Node* node) : node(node) {};

                friend class Tree; 

            private:
                Node* node;  


        }; 
    
    public:
        Tree() : n(0), root(nullptr) {}
        ~Tree(); 
        int size() const {return n;}
        bool empty() const {return n==0;}
        Position Root() {return Position(root); } 
        PositionList positions (bool preorder = true); 
        void addChild(const Position& parent, const E& element); 
        void prune(const Position& node); 
        int depth(const Position& node); 
        int height(const Position& node); 

    protected:
        int clear(Node* node); 
        void preorderPositions(const Position& p, std::vector<Position>& positions); //preorder traversal of the tree 
        void postorderPositions(const Position& p, std::vector<Position>& positions); //postorder traversal of the tree 
        void breadthFirstTraversal(const Position& p, std::vector<Position>& positions); 
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
        ++count; 
        for (auto child : node->children)
            count += clear(child); 
        
        delete node; 
    }

    return count; 
}

Tree::Position Tree::Position::parent() const 
{
    return node->parent; 
}

bool Tree::Position::isExternal() const 
{
    return node->children.empty(); 
}

bool Tree::Position::isRoot() const 
{
    return node->parent == nullptr; 
}

Tree::PositionList Tree::Position::children() const 
{
    std::vector<Position> positions; 
    for (Node* child : node->children)
        positions.emplace_back(child); 
    
    return PositionList(positions); 

    // return PositionList(node->children); 
}

void Tree::addChild(const Position& parent, const E& element)
{
    if (root == nullptr)
    {
        root = new Node(element, nullptr); 
    }
    else
    {
        Node * child = new Node(element, parent.node); 
        parent.node->children.emplace_back(child);  
    }

    ++n; 
}

void Tree::prune(const Position& node)
{
    //delete memory usage
    int n_deleted = clear(node.node); 

    //remove node from parent's childre vector
    auto& sibilings = node.parent().node->children; 
    auto it  = std::find(sibilings.begin(), sibilings.end(), node.node); 
    if (it != sibilings.end())
        sibilings.erase(it); 

    n -= n_deleted; 

}

int Tree::depth(const Position& node)
{
    if(node.isRoot())
        return 0; 
    else    
        return 1+depth(node.parent());
}

Tree::PositionList Tree::positions (bool preorder)
{
    //preorder traversal 
    std::vector<Position> positions; 

    // if (root != nullptr && preorder==true)
    //     preorderPositions(root, positions); 
    // else if (root != nullptr && preorder==false)
    //     postorderPositions(root, positions); 

    
    breadthFirstTraversal(Root(), positions); 

    return PositionList(positions); 

}

void Tree::preorderPositions(const Position& p, std::vector<Position>& positions)  //positions is an empty vector 
{
    positions.push_back(p); 
    PositionList children = p.children(); //get children list 
    for (auto it = children.begin(); it!=children.end(); ++it)
        preorderPositions(*it, positions); 



    //implementation using the stack 
    // std::stack<Position> stack ; 
    // stack.push(p); 

    // while(!stack.empty())
    // {
    //     //get top 
    //     Position current = stack.top(); 
    //     stack.pop(); 
    //     positions.push_back(current); 
        
    //     //push to the stack in reverse order 
    //     PositionList children = current.children(); 
    //     for (auto it = children.begin(); it != children.end();  ++it)
    //     {
    //         stack.push(*it); 
    //     }
    // }
}



void Tree::postorderPositions(const Position& p, std::vector<Position>& positions)
{
    PositionList children = p.children(); //get children list 
    for (auto it = children.begin(); it!=children.end(); ++it)
        postorderPositions(*it, positions); 
    
    positions.push_back(p); 
}

int Tree::height(const Position& node)
{
    //inefficient solution O(n^2)
    // int h=0; 
    // PositionList nodes = positions(); //get all nodes of the tree 
    // for (auto it = nodes.begin(); it != nodes.end(); ++it)
    // {
    //     if ((*it).isExternal())
    //     {
    //         h = std::max(h, depth(*it)); 
    //     }
    // }
    // return h; 

    //more effient solution O(n)

    if (node.isExternal())
        return 0; 
    else
    {
        int h=0; 
        auto children = node.children(); 
        for (auto it = children.begin(); it != children.end(); ++it)
            h = std::max(h, height(*it)); 

        return h+1; 
    }
}

void Tree::breadthFirstTraversal(const Position& p, std::vector<Position>& positions)
{
    std::queue<Position> q; 
    q.push(p); 

    while (!q.empty())
    {
        //dequeue last elemet 
        Position current = q.front();  
        q.pop(); 
        positions.push_back(current); 

        //enque all the children of a node 
        auto children = current.children(); 
        for (auto it = children.begin(); it != children.end(); ++it)
            q.push(*it); 
    }
}

int main ()
{   
    Tree t; 

    for (int i=0; i<5; ++i)
        t.addChild(t.Root(), i); 
    
    auto it = t.Root(); 
    std::cout << "Root: " << *it <<'\n'; 

    auto root_children = it.children(); 

    for (auto it = root_children.begin(); it != root_children.end();  ++it)
    {
        for (int i=0; i<3; ++i)
            t.addChild(*it, i); 
        
    }

    auto node_2 = t.Root();
    std::cout << "\n" << "Root children:" << "\n"; 
    for (auto it = root_children.begin(); it != root_children.end();  ++it)
    {
        if (**it ==2)
            node_2 = *it; 
        std::cout << "Node: " << **it << " children: "; 
        auto grandchildren = (*it).children();
        for (auto grandchild = grandchildren.begin(); grandchild != grandchildren.end(); ++grandchild)
            std::cout  << **grandchild  << " "; 

        std::cout << "\n"; 
    }
    std::cout << "tree size: " << t.size() << '\n' ;
    std::cout << "tree positions: " << '\n' ;
    auto positions = t.positions(); 
    for (auto it=positions.begin(); it != positions.end(); ++it)
        std::cout << **it << "\n"; 

    std::cout << "depth node 2: " << t.depth(node_2) << '\n'; 
    std::cout << "height tree: " << t.height(t.Root()) << '\n'; 
    std::cout << "parent of node 2: " << *node_2.parent() << '\n'; 


    //prune tree 
    t.prune(node_2); 
    root_children = t.Root().children();

    std::cout << "\n" << "Root children after pruning:" << "\n"; 
    for (auto it = root_children.begin(); it != root_children.end();  ++it)
    {
        std::cout << "Node: " << **it << " children: "; 
        auto grandchildren = (*it).children();
        for (auto grandchild = grandchildren.begin(); grandchild != grandchildren.end(); ++grandchild)
            std::cout  << **grandchild  << " "; 

        std::cout << "\n"; 
    }

    std::cout << "tree size: " << t.size() << '\n' ;



}
