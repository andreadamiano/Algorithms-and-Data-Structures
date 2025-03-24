#include <iostream>

// int returnmin (int a, int b)
// {
//     return (a<b ? a : b);
// }

//define a template function 
template <typename T>
T returnmin (T a, T b)
{
    return (a < b ? a : b);
}


int main ()
{
    //now we can apply the function to any type , provided that the < operator is defined for that type 
    std::cout << returnmin(1,6) << std::endl;
    std::cout << returnmin(1.6,6.7) << std::endl;
    std::cout << returnmin("ciao","come va ") << std::endl;
}