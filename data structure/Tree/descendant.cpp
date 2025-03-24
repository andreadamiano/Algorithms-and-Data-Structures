#include <iostream>
#include <unordered_map>
#include "binaryTree.h"

struct Node 
{
    int leftVisit;
    int rightVisit; 
    int descendants; 
    Node(int leftVisit =0) : leftVisit(leftVisit), rightVisit(0) {}
}; 

void descendants(Tree::Position&& p, std::unordered_map<Tree::Position, Node, Tree::PositionHash>& positions, int& count)
{
    count++; 
    positions.insert({p, Node(count)});

    if (!p.isExternal())
        descendants(p.left(), positions, count); 
    // positions.push_back(p);  
    if (!p.isExternal())
        descendants(p.right(), positions, count); 
    positions.at(p).rightVisit = count; 
    positions.at(p).descendants = positions.at(p).rightVisit-positions.at(p).leftVisit; 
    
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
    // auto positions = t.positions(); 
    // for (auto it = positions.begin(); it != positions.end(); ++it)
    //     std::cout << **it << "\n"; 

    std::unordered_map<Tree::Position, Node, Tree::PositionHash> positions; 
    int n =0;
    descendants(t.Root(), positions, n); 

    for (auto it = positions.begin(); it != positions.end(); ++it)
        std::cout << "Node: " << *(it->first) << " left count: " << it->second.leftVisit << " right count: " << it->second.rightVisit << " descendant: " << it->second.descendants << "\n"; 
      

}