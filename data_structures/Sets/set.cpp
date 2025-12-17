#include "mergeable_set.h"
#include <iostream>
#include <string>


int main()
{
    // Set<std::string> set;
    
    // set.insert("ciao"); 
    // set.insert("ciao"); 
    // // set.erase("ciao");

    // for (auto it = set.begin(); it != set.end(); ++it)
    // {
    //     std::cout << *it << "\n"; 
    // }

    Set<int> set1;
    Set<int> set2;

    set1.insert(1);
    set1.insert(2);
    set1.insert(6);

    set2.insert(7);
    set2.insert(4);
    set2.insert(5);
    set2.insert(2);
    set2.insert(6);

    //union
    // set1.Union(set2);

    //intersection
    // set1.IntersectMerge(set2); 

    //subtracyion
    set1.SubtractMerge(set2); 

    // Print the result
    for (auto it = set1.begin(); it != set1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

}