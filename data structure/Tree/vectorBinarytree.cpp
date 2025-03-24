#include <iostream>
#include <vector>
#include <stack>

using E = int; 
enum InsertPosition {ROOT, LEFT, RIGHT};   

class Tree
{
    private: 
        std::vector<E> vector; 
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
            private:
                Tree* tree;
                int index;  

            public: 
                Position left() const {return Position(tree, index*2);} 
                Position right() const {return Position(tree, index*2+1);} 
                Position parent() const {return Position(tree, index/2);}
                bool isRoot() const {return index ==1;}
                bool isExternal() const {return (2*index >= tree->vector.size() || tree->vector[2*index] == E()) && (2*index+1 >= tree->vector.size() || tree->vector[2*index+1] == E());}
                E& operator* () const {return tree->vector[index];}
                bool operator==(const Position& p) const {return index == p.index; }

                Position(Tree* tree, int index) : tree(tree), index(index) {} 
                friend class Tree; 

        }; 

        Tree() : n(0) {vector.resize(2);} 
        int size() const {return n;} 
        bool empty() const {return n==0;}
        Position Root()  {return Position(this, 1);} 
        PositionList positions(); 
        void addChild(const Position& parent, const E& element, InsertPosition position); 
        void prune (const Position& p); 
        Position removeaboveExternal(const Position& p); 

    protected:
    void preorderTraverse(const Position& p, std::vector<Position>& positions); 
    void postorderTraverse(const Position& p, std::vector<Position>& positions); 
    void inorderTraverse(const Position& p, std::vector<Position>& positions); 
};


void Tree::preorderTraverse(const Position& p, std::vector<Position>& positions)
{
    std::stack<Position> stack; 
    stack.push(p); 

    while (!stack.empty())
    {
        //pop top of the stack 
        Position current = stack.top();
        stack.pop();
        positions.push_back(current);

        if(!current.isExternal())
        {
            stack.push(current.right());
            stack.push(current.left());
            
        }
            
    }
    
}

void Tree::postorderTraverse(const Position& p, std::vector<Position>& positions)
{
    if (!p.isExternal()) {
        postorderTraverse(p.left(), positions);
        postorderTraverse(p.right(), positions);
    }

    positions.push_back(p);
}

void Tree::inorderTraverse(const Position& p, std::vector<Position>& positions)
{
    if (!p.isExternal())
    {
        inorderTraverse(p.left(), positions); 
    }
    positions.push_back(p); 
    if (!p.isExternal())
    {
        inorderTraverse(p.right(), positions); 
    }
}

Tree::PositionList Tree::positions()
{
    std::vector<Position> positions; 
    // preorderTraverse(Root(), positions); 
    // postorderTraverse(Root(), positions); 
    inorderTraverse(Root(), positions); 

    return (PositionList(positions)); 
}

void Tree::addChild(const Position& parent, const E& element, InsertPosition position)
{
    if(position == ROOT)
    {
        vector[1] = element; 
    }
    else if (position == LEFT)
    {
        int left_index = 2*parent.index; 
        if(left_index >= vector.size())
            vector.resize(left_index+1);
        
        vector[left_index] = element; 
    }
    else if (position == RIGHT  )
    {
        int right_index = 2*parent.index +1; 
        if(right_index >= vector.size())
            vector.resize(right_index+1); 
        
        vector[right_index] = element; 
    }
    n++;
}


int main ()
{
    Tree t; 

    t.addChild(t.Root(), 0, ROOT); 
    t.addChild(t.Root(), 1, LEFT); 
    t.addChild(t.Root(), 2, RIGHT); 

    auto left_node = t.Root().left(); 

    t.addChild(left_node, 3, LEFT); 
    t.addChild(left_node, 4, RIGHT); 
    

    auto positions = t.positions(); 

    for (auto it = positions.begin(); it != positions.end(); ++it)
        std::cout << **it << "\n"; 

    std::cout << (t.Root() == t.Root().left()); 


}