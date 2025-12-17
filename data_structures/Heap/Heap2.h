#ifndef HEAP2_H
#define HEAP2_H

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>

using E = int; 

//a heap is a complete binary tree 
class Heap
{
    public:

        class Position
        {
            public:
                Heap* heap;
                int index;  

            public: 
                Position& left() const {return *heap->vector[index*2].loc;} 
                Position& right() const {return *heap->vector[index*2+1].loc;} 
                Position& parent() const {return *heap->vector[index/2].loc;}
                bool isRoot() const {return index ==1;}
                E& operator* () const {return heap->vector[index].element;}
                bool operator==(const Position& p) const {return index == p.index; }
                bool hasLeft() const {return 2*index <= heap->size();} 
                bool hasRight() const {return 2*index +1 <= heap->size();}

                Position(Heap* heap, int index) : heap(heap), index(index) {} 
                Position() : heap(nullptr), index(0) {}
                Position(const Position&) = delete;             // Delete copy constructor
                Position& operator=(const Position&) = delete;  // Delete copy assignment

                friend class Heap; 

        }; 

        Heap() : vector(1) {} 
        int size() const {return vector.size()-1;}
        Position& Root()  {return *vector[1].loc;} 
        Position& last() {return *vector[size()].loc;} 
        Position& at(int index) {return *vector[index].loc; }
        void addLast(const E& element)  
        {
            Position* loc = new Position(this, vector.size());
            vector.push_back(Node(element, loc));
        } 

        void removeLast() 
        {
            delete vector[last().index].loc; 
            vector.pop_back(); 
        }

        void swap (Position& p, Position& other); 

    private:

        struct Node
        {
            E element; 
            Position* loc; 
            Node(E element, Position* loc) : element(element), loc(loc) {}
            Node () : element(element), loc(nullptr) {} 
        };

        std::vector<Node> vector;
    
};

void Heap::swap(Position& p, Position& other) 
{
    // (1) Swap the elements in the vector
    std::swap(vector[p.index].element, vector[other.index].element);

    // (2) Update the `loc` pointers in the Nodes
    std::swap(vector[p.index].loc, vector[other.index].loc);

    // (3) Swap the indices in the Position objects
    std::swap(p.index, other.index);
}

#endif