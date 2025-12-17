// #include "partition.h"
#include "partition2.h"
#include <iostream>

int main ()
{
    // Partition<int> partition; 
    // // auto pos = partition.makeSet(10); 

    // auto pos1 = partition.makeSet({10, 11, 12, 13, 14}); 
    // auto pos2 = partition.makeSet({2, 3, 4, 5}); 
    // auto& set1 = partition.find(pos1);
    // auto& set2 = partition.find(pos2);

    // partition.Union(set1, set2); 

    // for (auto it = set1.begin(); it != set1.end(); ++it)
    //     std::cout << (*it)->element << "\n"; 


    Partition<int> partition; 

    auto a = partition.makeSet(1);
    auto b = partition.makeSet(2);
    auto c = partition.makeSet(3);
    auto d = partition.makeSet(4);

    // Union some sets
    auto ab = partition.Union(a, b);
    auto cd = partition.Union(c, d);
    auto abcd = partition.Union(ab, cd);

    // Find representatives
    std::cout << "Representative of a: " << partition.find(a)->element << std::endl;
    std::cout << "Representative of b: " << partition.find(b)->element << std::endl;
    std::cout << "Representative of c: " << partition.find(c)->element << std::endl;
    std::cout << "Representative of d: " << partition.find(d)->element << std::endl;


}