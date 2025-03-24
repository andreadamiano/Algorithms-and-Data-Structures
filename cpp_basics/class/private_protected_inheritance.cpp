#include <iostream>
#include <string>   

enum status {poor, rich, middle_class};

class Person 
{
    private:
        std::string name;
    
    protected:
        status st ;  

    public:
        void sayStatus ();
        Person(std::string name, status st) : name(name), st(st) {}
};


void  Person::sayStatus ()
{
    switch (st)
    {
        case poor: 
            std::cout << "Poor"; 
            break;
        case rich: 
            std::cout << "Rich"; 
            break;
        case middle_class: 
            std::cout << "Middle Class"; 
            break;
    }
    std::cout << std::endl; 

}

class Student: protected Person
{
    public:
        Student(std::string name, status st) : Person(name, st) {} 

};

int main ()
{  
    Student s {"Andrea", poor};
    s.sayStatus();
}