#include <iostream>
#include <queue>
#include <list>
#include <random>

int main ()
{
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution dis(0,100);
    std::list<int> list(100);
    std::priority_queue<int, std::vector<int>, std::greater<int>> priority; 
    
    //populate the list 
    for (int& num: list)
    {
        num =  dis(gen);
        std::cout << num << "\n"; 
    }

    while(!list.empty())
    {
        int element = list.front(); 
        list.pop_front();
        priority.push(element); 
    }
    while(!priority.empty())
    {
        int element = priority.top();  
        priority.pop(); 
        list.push_back(element); 
    }

    //see reuslts 
    std::cout << "\nSorted list: \n";
    for (int& num: list)
    {
        std::cout << num << "\n"; 
    }

}