#include <iostream>

int main ()
{
    struct student
    {
        int id;
        char name[20];
        float percentage;
    };

    student Andrea {10666938, "Andrea", 99.9};

    std::cout << "ID: " << Andrea.id << std::endl;
    std::cout << "Name: " << Andrea.name << std::endl;
    std::cout << "Percentage: " << Andrea.percentage << std::endl;
}