#include <iostream>

int main ()
{
    enum Day {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY}; //enumeration type (named intger constants)


    for (int i = MONDAY; i <= SUNDAY; i++)
    {
        std::cout << i << std::endl;
    }
}