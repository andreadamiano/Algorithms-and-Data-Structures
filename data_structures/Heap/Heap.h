#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>

using E = int; 

//this is not a heap but a complete binary tree, since it doesnt enforce that the key parent < key children  
class Heap
{
    private: 
            std::vector<E> vector;
    
    public:

        class Position
        {
            private:
                Heap* heap;
                int index;  

            public: 
                Position left() const {return Position(heap, index*2);} 
                Position right() const {return Position(heap, index*2+1);} 
                Position parent() const {return Position(heap, index/2);}
                bool isRoot() const {return index ==1;}
                E& operator* () const {return heap->vector[index];}
                bool operator==(const Position& p) const {return index == p.index; }
                bool hasLeft() const {return 2*index <= heap->size();} 
                bool hasRight() const {return 2*index +1 <= heap->size();}

                Position(Heap* heap, int index) : heap(heap), index(index) {} 
                friend class Heap; 

        }; 

        Heap() : vector(1) {} 
        Heap(const E& root, const Heap& leftHeap, const Heap& rightHeap); 
        int size() const {return vector.size()-1;}
        Position Root()  {return Position(this, 1);} 
        Position last() {return Position(this, size());} 
        void addLast(const E& element) {vector.push_back(element);}
        void removeLast() {vector.pop_back(); }
        void swap (const Position&p, const Position& other) {E temp = *p; *p = *other; *other = temp;}

    protected:
        void Merge(int index, int otherindex,  std::vector<E>& heap ,const std::vector<E>& other); 
        void IterativeMerge(int index, int otherindex, std::vector<E>& heap, const std::vector<E>& other); 
};

Heap::Heap(const E& root, const Heap& leftHeap, const Heap& rightHeap)
{
    //compute the required size 
    int left_size = (leftHeap.vector.size()> 1 ? leftHeap.vector.size()*2 : 0); 
    int right_size = (rightHeap.vector.size() > 1 ? rightHeap.vector.size()*2 :0); 
    int size = std::max({left_size, right_size, 2}); 
    // int size = left_size + right_size +2; 
    vector.resize(size);
    vector[1] = root; 

    if (leftHeap.vector.size() > 1)
        Merge(2, 1, vector, leftHeap.vector);
    if (rightHeap.vector.size() > 1)
        Merge(3, 1, vector, rightHeap.vector);  
  
}


void Heap::Merge(int index, int otherindex, std::vector<E>& heap , const std::vector<E>& other)
{
    if(index >= heap.size() || otherindex >= other.size())
        return; 
    
    heap[index] = other[otherindex]; 

    Merge(index*2, otherindex*2, heap, other); 
    Merge(index*2+1, otherindex*2+1, heap, other ); 
}

void Heap::IterativeMerge(int index, int otherindex, std::vector<E>& heap, const std::vector<E>& other)
{
    std::queue<std::pair<int, int>> q; //intialize the queue 
    q.push({index, otherindex}); //push the initial state 

    while(!q.empty())
    {
        auto [currentindex, currentotherindex] = q.front(); 
        q.pop(); //pop the top state 

        if(currentindex >= heap.size() || currentotherindex >= other.size())
            continue; //skip loop

        heap[currentindex] = other[currentotherindex]; //process state 

        q.push({currentindex*2, currentotherindex*2});//push new states 
        q.push({currentindex*2+1, currentotherindex*2+1});  
    }
}

#endif