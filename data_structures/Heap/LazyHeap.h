#include "HeapPriorityQueue.h"
#include <unordered_map>

template <typename E, typename C>
class LazyHeap 
{
    private:
        int size; 
        std::unordered_map<E, int> removed; 
        PriorityQueue<E, C> heap;

    public:
        LazyHeap(); 
        ~LazyHeap() {} 
        void remove(E element); 
        void add (E element) ;
        const E& pop();
        const E& top(); 
        int size() {return size; }

};

template <typename E, typename C>
LazyHeap<E, C>::LazyHeap() : size(0)
{

}

template <typename E, typename C>
void LazyHeap<E, C>::remove(E element)
{
    size--; 
    removed[element]++; //lazy remove the element by adding to the dictionary and decrementing the logical dimension 
}

template <typename E, typename C>
void LazyHeap<E, C>::add(E element)
{
    size++; 
    heap.insert(element);  
}

template <typename E, typename C>
const E& LazyHeap<E, C>::top()
{
    //performe clean up while returning the top of the heap 
    E current; 
    while ((current = removed[heap.min()]) > 0)
    {
        heap.removeMin(); 
        removed[current]--;
    }
    return current; 
    
}

template <typename E, typename C>
const E& LazyHeap<E, C>::pop()
{
    E top = top(); 
    remove(top); 
    return top; 
}