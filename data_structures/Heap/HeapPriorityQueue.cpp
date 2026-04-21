#include "HeapPriorityQueue.h"

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

