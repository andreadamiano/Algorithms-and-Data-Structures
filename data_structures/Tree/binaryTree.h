#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <vector>
#include <stack>
#include <functional> //for std::hash
#include <variant>

using E = int; 
enum InsertPosition {ROOT, LEFT, RIGHT};   

class Tree
{
    private: 
        struct Node
        {
            E element; 
            int operation(int leftValue, int rightValue) const;
            void print () 
            {
                if (element == '+' || element == '-' || element == '*' || element == '/')
                        std::cout << static_cast<char> (element);
                else    
                    std::cout << element; 
            }
        };

        std::vector<Node> vector; 
        int n; 
    
    public:
        class Position; 

        // custom hash functor (a class that overloads the operator () to behave like a function)
        struct PositionHash {
            size_t operator()(const Tree::Position& p) const {
                // Use the index as the hash value
                std::hash<int> int_hasher;
                return int_hasher(p.index); //return an unsigned integer which represent the hash value 
            }
        };

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
                bool isExternal() const {return (2*index >= tree->vector.size() || tree->vector[2*index].element == E()) && (2*index+1 >= tree->vector.size() || tree->vector[2*index+1].element == E());}
                Node& operator* () const {return tree->vector[index];}
                bool operator==(const Position& p) const {return index == p.index; }
                // int operation(int left, int right) const; 

                Position(Tree* tree, int index) : tree(tree), index(index) {} 
                friend class Tree; 
                friend struct PositionHash;

        }; 

        Tree() : n(0) {vector.resize(2);} 
        int size() const {return n;} 
        bool empty() const {return n==0;}
        const Position Root()  {return Position(this, 1);} 
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
        vector[1].element = element; 
    }
    else if (position == LEFT)
    {
        int left_index = 2*parent.index; 
        if(left_index >= vector.size())
            vector.resize(left_index+1); //add new node initialized with the default constructor 
        
        vector[left_index].element = element; 
    }
    else if (position == RIGHT  )
    {
        int right_index = 2*parent.index +1; 
        if(right_index >= vector.size())
            vector.resize(right_index+1); 
        
        vector[right_index].element = element; 
    }
    n++;
}

int Tree::Node::operation(int leftValue, int rightValue) const 
{
    switch(static_cast<char>(element))
    {
        case '+':
            return leftValue + rightValue;
        case '-':
            return leftValue - rightValue;
        case '*':
            return leftValue * rightValue;
        case '/':
            if (rightValue == 0) {
                throw std::invalid_argument("Division by zero");
            }
            return leftValue / rightValue;
        default:
            throw std::invalid_argument("Unknown operator");
    }
}

#endif