#include <iostream>
#include <vector>

using E = int; 
//a heap is a complete binary tree 
class Heap
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
                Heap* heap;
                int index;  

            public: 
                Position left() const {return Position(heap, index*2);} 
                Position right() const {return Position(heap, index*2+1);} 
                Position parent() const {return Position(heap, index/2);}
                bool isRoot() const {return index ==1;}
                bool isExternal() const {return (2*index >= heap->vector.size() || heap->vector[2*index] == E()) && (2*index+1 >= heap->vector.size() || heap->vector[2*index+1] == E());}
                E& operator* () const {return heap->vector[index];}
                bool operator==(const Position& p) const {return index == p.index; }

                Position(Heap* heap, int index) : heap(heap), index(index) {} 
                friend class Heap; 

        }; 

        Heap() : n(0), vector(2) {} 
        int size() const {return n;} 
        bool empty() const {return n==0;}
        Position Root()  {return Position(this, 1);} 
        PositionList positions(); 
        void addLast(const E& element); 
        void removeLast(); 
        void swap (const Position&p, const Position& other); 
        bool hasRight(const Position& p); 
        bool hasLeft (const Position& p);
        bool isRoot (const Position& p);

    protected:
    void preorderTraverse(const Position& p, std::vector<Position>& positions); 
    void postorderTraverse(const Position& p, std::vector<Position>& positions); 
    void inorderTraverse(const Position& p, std::vector<Position>& positions); 
};