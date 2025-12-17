#include <iostream>

int main ()
{
    // enum Day {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY}; //enumeration type (named intger constants)

    // for (int i = MONDAY; i <= SUNDAY; i++)
    // {
    //     std::cout << i << std::endl;
    // }

    //  a better alternative is to use enum class , which are scoped enumeration
    enum class Day {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY};
    enum class Fruit {APPLE, ORANGE}; 

    //must be accessed with enum name 
    std::cout <<(int) Day::FRIDAY;  //they also require explicit casitng 

    //cannot compare different enum class
    if (Day::FRIDAY == Fruit::APPLE) //this give as error 
        std::cout << "makes no sense"; 
}   