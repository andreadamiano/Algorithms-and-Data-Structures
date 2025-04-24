#include <iostream>
#include <vector>

using E = int; 

//a heap is a complete binary tree 
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
        int size() const {return vector.size()-1;}
        Position Root()  {return Position(this, 1);} 
        Position last() {return Position(this, size());} 
        void addLast(const E& element) {vector.push_back(element);}
        void removeLast() {vector.pop_back(); }
        void swap (const Position&p, const Position& other) {E temp = *p; *p = *other; *other = temp;}
};

int main ()
{
    Heap h; 
    h.addLast(0);
    h.addLast(1);
    h.addLast(2);
    h.addLast(3);
    h.addLast(4);
    h.addLast(5);

    std::cout << *(h.Root().right().left());
}