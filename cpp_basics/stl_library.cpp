#include <vector>
#include <iostream>

int main ()
{
    //vector
    std::vector<int> v {1,2,3,4} ; //initialize a vector with 4 elements of type <int> (vector is a template class)
    std::vector <int> v2 = v; //deep copy of v
    v.resize(v.size() + 1); //resize the vector to 5 elements
    
    std::cout << &v2 << std::endl; //4
    std::cout << &v << std::endl; //4
    std::cout << v.size() << std::endl; 
    std::cout << v.at(4) << std::endl; 


    //strings 
    std::string s ("Hello World");
    std::cout << s.find("World") << std::endl; //returns the index of the first character of the substring
    std::cout << s.find("l", 4) <<std::endl; //returns the index of the first character of the substring after the 4th character
    std::cout << s.substr(6, 5) << std::endl; //returns a substring starting from the 6th character and 5 characters long
    // std::cout << s.insert(6, "Universe") << std::endl; //insert "Universe" at the 6th character
    std::cout << s.replace(6, 5, "Universe") << std::endl; //replace the substring starting from the 6th character and 5 characters long with "Universe"
    std::cout << s.erase(6, 8) << std::endl; //erase the substring starting from the 6th character and 8 characters long
    getline(std::cin, s); //get a line of input from the user
    std::cout << s << std::endl;

    if (s.find("come") != std::string::npos) //if the substring "come" is found in the string
    {
        std::cout << "Found" << std::endl;
    }
    else
    {
        std::cout << "Not found" << std::endl;
    }
}