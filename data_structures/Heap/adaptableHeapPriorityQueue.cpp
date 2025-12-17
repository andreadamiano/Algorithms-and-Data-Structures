#include <iostream>
#include <random>
#include <list>
#include "Heap2.h" 

// struct Node
// {
//     E element; 
//     Heap::Position loc; 
//     Node(E element, Heap::Position loc) : element(element), loc(loc) {}
// };

template <typename E, typename C>
class PriorityQueue
{
    private:

        Heap h; 
        C isLess; //comparator 

    public:
        Heap::Position at(int index) {return h.at(index);}  
        int size() const {return h.size();}
        bool empty() const {return size() ==0; }
        Heap::Position& insert(const E& element); 
        const E& min() {return *(h.Root());}
        void removeMin(); 
        void remove (Heap::Position& p); //remove a generic position 
        void replace(Heap::Position& p, const E& element); 
};

template < typename E, typename C>
Heap::Position& PriorityQueue<E, C>::insert(const E& element)
{
    h.addLast(element); 
    Heap::Position& last = h.last(); 

    while(!last.isRoot())
    {
        Heap::Position& parent = last.parent(); 
        if(isLess(*parent, *last))
            break;

        h.swap(last, parent);
        // last = parent; 

    }

    return last; 
}

template < typename E, typename C>
void PriorityQueue<E, C>::removeMin()
{
    if (size() == 1)
    {
        h.removeLast(); 
        return; 
    }

    else
    {
        h.swap(h.last(), h.Root()); 
        h.removeLast(); 
        auto& last = h.Root();

        while(last.hasLeft())
        {
            Heap::Position* child = &last.left(); //by default the child is the left node
            if(last.hasRight() && isLess(*(last.right()), *(last.left()))) // check if the right node exist and if its smaller 
                child = &last.right(); 
            
            if (isLess(*last, **child))
                break; 

            h.swap(last, *child);    
            // last = child; 
        }  
    }
}

template <typename E, typename C>
void PriorityQueue<E, C>::remove (Heap::Position& p)
{
    if (size() ==1 )
    {
        h.removeLast(); 
        return;
    } 

    else
    {
        auto& current = h.last(); 
        h.swap(h.last(), p); 
        h.removeLast(); 

        //restore heap property (heap-up bubbling)
        while(!current.isRoot())
        {
            auto& parent = current.parent(); 
            if (isLess(*parent, *current))
                break; 
            h.swap(parent, current); 
            // current = parent; 
        }

        //head-down bubbling
        while(current.hasLeft())
        {
            Heap::Position* child = &current.left(); 

            if(current.hasRight() && isLess(*(current.right()), *(current.left())))
                child = &current.right(); 

            if(isLess(*current, **child))
                break;
            
            h.swap(*child, current); 
            // current = child; 
        }

    }

}

template <typename E, typename C>
void PriorityQueue<E, C>::replace(Heap::Position& p, const E& element)
{
    E oldElement = *p; 
    *p = element;  // modify the element of the Position

    auto& current = p; 

    //if the new element is smaller bubble-up 
    if (isLess(*current, oldElement))
    {
        while(!current.isRoot())
        {
            auto& parent = current.parent(); 
            if (isLess(*parent, *current))
                break; 
            h.swap(parent, current); 
            // current = parent; 
        }
    }
    else //bubble-down
    {
        while(current.hasLeft())
        {
            Heap::Position* child = &current.left(); 

            if(current.hasRight() && isLess(*(current.right()), *(current.left())))
                child = &current.right(); 

            if(isLess(*current, **child))
                break;
            
            h.swap(*child, current); 
            // current = child; 
        }
    }
}

class Comparator
{
    public: 
        bool operator() (int& first, int& second)
        {
            return first < second; 
        }
}; 


int main ()
{
    PriorityQueue<int, Comparator> q; 

    q.insert(2); 
    q.insert(1); 
    q.insert(0); 
    q.insert(3); 
    q.insert(4); 
    q.insert(5); 
    q.insert(6); 

    std::cout << "before removal\n"; 
    while (!q.empty())
    {
        std::cout << q.min() << " "; 
        q.removeMin(); 
    }
    std::cout << "\n"; 
    
    auto& pos = q.insert(2); 
    q.insert(1); 
    q.insert(0); 
    q.insert(3); 
    q.insert(4); 
    q.insert(5); 
    q.insert(6); 

    q.remove(pos); 
   
    std::cout << "after removing " << *pos << "\n"; 
    while (!q.empty())
    {
        std::cout << q.min() << " "; 
        q.removeMin(); 
    }
    std::cout << "\n"; 

    q.insert(1); 
    q.insert(0); 
    q.insert(3); 
    auto& pos2 = q.insert(4); 
    q.insert(5); 
    q.insert(6); 

    q.replace(pos2 ,  8); 

    std::cout << "after modifying " << *pos2 << "\n"; 
    while (!q.empty())
    {
        std::cout << q.min() << " "; 
        q.removeMin(); 
    }

}
