#ifndef HEAP2_H
#define HEAP2_H

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>

using E = int; 

class Heap; // Forward declaration

class Position
{
    private:
        Heap* heap;
        int index;  

    public: 
        Position left() const;
        Position right() const;
        Position parent() const;
        bool isRoot() const {return index ==1;}
        E& operator* () const;
        bool operator==(const Position& p) const {return index == p.index; }
        bool hasLeft() const;
        bool hasRight() const;

        Position(Heap* heap, int index) : heap(heap), index(index) {} 
        friend class Heap; 
};

struct Node
{
    E element; 
    Position loc; 
    Node(E element, Position loc) : element(element), loc(loc) {}
};

//a heap is a complete binary tree 
class Heap
{
    private: 
        std::vector<Node> vector;
    
    public:
        int size() const {return vector.size()-1;}
        Position Root()  {return Position(this, 1);} 
        Position last() {return Position(this, size());} 
        void addLast(const E& element) {vector.push_back(Node(element, Position(this, size()+1)));}
        void removeLast() {vector.pop_back(); }
        void swap (const Position& p, const Position& other) {E temp = *p; *p = *other; *other = temp;}
};

// Position member functions that need Heap to be complete
inline Position Position::left() const {return Position(heap, index*2);} 
inline Position Position::right() const {return Position(heap, index*2+1);} 
inline Position Position::parent() const {return Position(heap, index/2);}
inline E& Position::operator* () const {return heap->vector[index].element;}
inline bool Position::hasLeft() const {return 2*index <= heap->size();} 
inline bool Position::hasRight() const {return 2*index +1 <= heap->size();}

#endif