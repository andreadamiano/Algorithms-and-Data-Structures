#include <iostream>
#include "binaryTree.h"

struct Node 
{
    Tree::Position p; 
    int x; 
    int y; 
    Node(Tree::Position p, int x, int y) : p(p), x(x), y(y) {}
};


int count =0; 

void coordinates(Tree::Position&& p, std::vector<Node>& positions, int depth)
{
    //binary traverse 
    if(!p.isExternal())
        coordinates(p.left(), positions, depth+1);    

    int x = count++; 
    int y = depth; 
    positions.push_back(Node(p, x, y)); 

    if(!p.isExternal())
        coordinates(p.right(), positions, depth+1); 

}

void eulerTour(Tree::Position&& p, std::vector<Tree::Position>& positions)
{
    positions.push_back(p); 
    if (!p.isExternal())
        eulerTour(p.left(), positions); 
    positions.push_back(p);  
    if (!p.isExternal())
        eulerTour(p.right(), positions); 
    positions.push_back(p);   
}

int main ()
{
    Tree t; 
    t.addChild(t.Root(), 0, ROOT); 
    t.addChild(t.Root(),1,  LEFT); 
    t.addChild(t.Root(), 2,  RIGHT); 
    t.addChild(t.Root().left(), 3, LEFT); 
    t.addChild(t.Root().left(), 4,  RIGHT); 
    t.addChild(t.Root().right(), 5, LEFT); 
    t.addChild(t.Root().right(), 6,  RIGHT); 


    std::vector<Node> postions; 

    coordinates(t.Root(), postions, 0); 

    for (auto it = postions.begin(); it != postions.end(); ++it)
    {
        std::cout << "Node: " << *(it->p) << "(" << it->x << "," << it->y << ")" << "\n"; 
    }

    std::vector<Tree::Position> postions_2; 

    eulerTour(t.Root(), postions_2); 
    for (auto it = postions_2.begin(); it != postions_2.end(); ++it)
    {
        std::cout << **it << "\n"; 
    }


}