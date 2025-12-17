#include <iostream>
#include <random>
#include <list>
#include "Heap.h"

template <typename E, typename C>
class PriorityQueue
{
    private:
        Heap h; 
        C isLess; //comparator 

    public:
        PriorityQueue(std::list<E>& list) {h = BottomUpHeap(list); }
        PriorityQueue() {}
        int size() const {return h.size();}
        bool empty() const {return size() ==1; }
        void insert(const E& element); 
        const E& min() {return *(h.Root());}
        void removeMin(); 
        static void HeapSort(std::vector<E>& array, C isLess = C{}); //comparator inference to avoid repeting the comparator twice, C{} creates a temporary istance 

    protected:
        Heap BottomUpHeap(std::list<E>& list, C isLess = C{}); 

};

template < typename E, typename C>
void PriorityQueue<E, C>::insert(const E& element)
{
    h.addLast(element); 
    Heap::Position last = h.last(); 

    while(!last.isRoot())
    {
        Heap::Position parent = last.parent(); 
        if(isLess(*parent, *last))
            break; 
        h.swap(last, parent);
        last = parent; 

    }
}

template < typename E, typename C>
void PriorityQueue<E, C>::removeMin()
{
    if (size() == 1)
        h.removeLast(); 

    else
    {
        h.swap(h.last(), h.Root()); 
        auto last = h.Root(); 
        h.removeLast(); 

        while(last.hasLeft())
        {
            auto child = last.left(); //by default the child is the left node
            if(last.hasRight() && isLess(*(last.right()), *(last.left()))) // check if the right node exist and if its smaller 
                child = last.right(); 
            
            if (isLess(*last, *child))
                break; 
            h.swap(last, child);    
            last = child; 
        }  
    }
}

template <typename E, typename C>
void PriorityQueue<E,C>::HeapSort(std::vector<E>& array, C isLess)
{
    //phase 1: build the heap in place 
    for (int i =1; i<array.size(); ++i)
    {
        int last = i; 
        while(last>0) //while last is not the root node 
        {
            int parent = (last-1)/2; //get the parent node in the heap 
            if(isLess(array[last], array[parent])) //order the elements with the largest member at the root of the heap
                break; 
            E temp = array[last]; //switch last with parent 
            array[last] = array[parent];
            array[parent] = temp; 

            last = parent;  
        }

    }

    //phase 2: inserting in the array
    for (int i = array.size()-1; i>0; --i)
    {
        E temp = array[0]; //switch last with root 
        array[0] = array[i]; 
        array[i] = temp;

        int last = 0; // get the root node 
        while(true)
        {
            int left = last*2 +1; 
            int right = last*2+2; 
            int child = last; 

            if(left< i && isLess(array[child], array[left]))
                child = left; 
            
            if(right< i && isLess(array[child], array[right]))
                child = right;
            
            if(child == last) //no child available 
                break; 
            
            int temp = array[last];
            array[last] = array[child];
            array[child] = temp; 

            last = child; 
        }
    }
}

template <typename E, typename C>
Heap PriorityQueue<E, C>::BottomUpHeap(std::list<E>& list, C isLess)
{
    if (list.empty())
        return Heap(); //return empty heap 
    else
    {
        E root = list.front(); 
        list.pop_front(); 

        std::list<E> l1,l2; 
        
        auto it = list.begin(); 
        std::advance(it, list.size()/2); 
        l1.assign(list.begin(), it); 
        l2.assign(it, list.end()); 

        Heap h1 = BottomUpHeap(l1);
        Heap h2 = BottomUpHeap(l2); 

        Heap h(root, h1, h2); 

        //heap-down bubbling
        auto last = h.Root(); 
        while (last.hasLeft())
        {
            auto child = last.left(); 
            
            if(last.hasRight() && isLess(*(last.right()), *(last.left())))
                child = last.right(); 
            
            if(isLess(*last, *child))
                break;
            
            h.swap(last, child); 
            last = child; 
        }

        return h; 


    }
}

class Comparator  //functor comparator 
{
    public: 
        bool operator() (int& first, int& second)
        {
            return first < second; 
        }
}; 

int main()
{
    PriorityQueue<int, Comparator> q; 

    q.insert(100); 
    q.insert(2); 
    q.insert(56); 
    q.insert(78); 
    q.insert(5); 
    q.insert(43);
    q.insert(200); 

    while (!q.empty())
    {
        std::cout << q.min() << "\n"; 
        q.removeMin();
    }

    // std::vector<int> vector (127); 
    // std::random_device rd; 
    // std::mt19937 gen(rd()); 
    // std::uniform_int_distribution<int> dis (0,100); 

    // std::cout << "Array\n";
    // for (int& num : vector)
    // {
    //     num = dis(gen); 
    //     std::cout << num << " "; 
    // }

    // PriorityQueue<int, Comparator>::HeapSort(vector); 

    // std::cout << "\n\n" << "Sorted array" << "\n"; 
    // for (int& num : vector)
    // {
    //     std::cout << num << " "; 
    // }


    // //Bottom Up Heap construction
    // std::list<int> list(vector.begin(), vector.end()); 
    // PriorityQueue<int, Comparator> q(list); 

    // std::cout << "\n\nSorted Array:\n";

    // while(!q.empty())
    // {
    //     std::cout << q.min() << " "; 
    //     q.removeMin(); 

    // }

}

