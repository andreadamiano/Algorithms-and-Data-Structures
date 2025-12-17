#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <random>


int sum (const std::vector<int>& vector)
{
    // std::vector<int>::iterator it; 

    std::vector<int>::const_iterator it; //to read from a constant container a constant iterator must be used 
    int sum =0; 

    for (it= vector.begin(); it != vector.end(); ++it)
    {
        sum += *it; 
    }


    return sum; 
}


// int main ()
// {
//     // std::vector<int> vector(100);
//     // sum(vector); 

//     //iterators can be used to initialize containers 
//     std::list<int> list {1,2, 3,4}; 

//     std::vector<int> vector (list.begin(), list.end()); 

//     for (int num : vector)
//         std::cout << num << std::endl; 


// }

int main ()
{
    int array[] = {17, 12, 33, 15, 62, 45}; 

    //initialize a vector 
    std::vector<int> vector (array, array+6); 

    //perform some actions 
    std::cout << vector.size() << std::endl; 

    vector.pop_back(); 
    std::cout << vector.size() << std::endl; 

    vector.push_back(19); 
    std::cout << vector.size() << std::endl; 
    for (int num : vector)
        std::cout << num << " ";

    std::cout << std::endl; 
    std::cout << vector.front() << " " << vector.back() << std::endl; 

    std::sort (vector.begin(), vector.end()); 

    for (int num : vector)
        std::cout << num << " ";

    std::cout << std::endl; 

    vector.erase(vector.end()-4, vector.end()-2);
    for (int num : vector)
        std::cout << num << " ";

    std::cout << std::endl; 


    //char vector 
    char array_2[] = {'b', 'r', 'a', 'v', 'o'};  
    std::vector<char> vector_2 (array_2, array_2+5); 

    //perform operations 
    std::random_device rd; 
    std::mt19937 gen(rd()); 

    std::shuffle(vector_2.begin(), vector_2.end(), gen); 
    
    vector_2.insert(vector_2.begin(), 's'); 

    // for (char ch: vector_2)
    //     std::cout << ch << " "; 
    
    // std::cout << std::endl; 

    std::vector<char>::iterator it; 
    for (it=vector_2.begin(); it != vector_2.end(); ++it)
        std::cout << *it << " "; 
    std::cout << std::endl; 



}