#include <iostream>



class Person 
{
    public: 
        virtual void print() 
        // void print() 
        {
            std::cout << "Person" << std::endl;
        }

        virtual ~Person()
        // ~Person()
        {
            std::cout << "Person Destructor called" << std::endl;
        }
};

class Student : public Person
{
    public: 
        void print() 
        {
            std::cout << "Student" << std::endl;
        }

        ~Student()
        {
            std::cout << "Student Destructor called" << std::endl;
        }
};

int main ()
{
    Person* p[2];
    p[0] = new Person ();
    p[1] = new Student ();

    //print
    p[0]->print();
    p[1]->print();

    delete p[0];
    delete p[1];
}