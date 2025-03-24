#include <iostream>

class Animal
{
    public:
        virtual void makeSound()
        {
            std::cout << "Animal sound" << std::endl;
        }
};

class Dog : public Animal
{
    public:
        void makeSound() override
        {
            std::cout << "Dog sound" << std::endl;
        }
};


int main ()
{
    Animal* a  [2];

    a[0] = new Animal();
    a[1] = new Dog();

    a[0]->makeSound();
    a[1]->makeSound();


    delete a[0];
    delete a[1];
}