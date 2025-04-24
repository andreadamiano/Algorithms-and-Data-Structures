#include <iostream>
#include <unordered_map>
#include "binaryTree.h"

struct Node 
{
    Tree::Position p;
    int leftVisit;
    int rightVisit; 
    Node(Tree::Position p, int leftVisit =0) : p(p), leftVisit(leftVisit), rightVisit(0) {}
}; 

void descendants(Tree::Position&& p, std::unordered_map<Node, Tree::Position> positions, int count)
{
    positions[p] = Node(p, count); 

    if (!p.isExternal())
        descendants(p.left(), node); 
    // positions.push_back(p);  
    if (!p.isExternal())
        descendants(p.right(), node); 
    positions.at(p).rightVisit++; 
}


int main()
{
    Tree t; 
    t.addChild(t.Root(), 0, ROOT); 
    t.addChild(t.Root(),1,  LEFT); 
    t.addChild(t.Root(), 2,  RIGHT); 
    t.addChild(t.Root().left(), 3, LEFT); 
    t.addChild(t.Root().left(), 4,  RIGHT); 
    t.addChild(t.Root().right(), 5, LEFT); 
    t.addChild(t.Root().right(), 6,  RIGHT); 

    //visualize tree 
    auto positions = t.positions(); 
    for (auto it = positions.begin(); it != positions.end(); ++it)
        std::cout << **it << "\n"; 

    std::unordered_map<Node, Tree::Position> positions; 
    descendants(t.Root(), positions, 0); 




}, 