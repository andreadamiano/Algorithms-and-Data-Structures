#include <iostream>
#include <string>

class Person 
{
    private:
        std::string name; 
        std::string idNum; 
        std::string* surname; 
    public: 
        Person(const std::string& name, const std::string& idNum, const std::string& surname) : name(name), idNum(idNum) 
        {
            this->surname = new std::string(surname);
        }
        void print() const; 
        std::string getName() const;

        virtual ~Person() 
        {
            std::cout << "Person Destructor called" << std::endl;
            delete surname; 
        }
};

void Person::print() const 
{
    std::cout << "Name: " << name << std::endl; 
    std::cout << "ID: " << idNum << std::endl;
    std::cout << "Surname: " << *surname << std::endl;
}

class Student :public Person
{
    private: 
        // Person p = Person("Andrea", "10665938", "Damiano"); //static binding
        std::string major; 
        int gradYear;
        std::string* course; 
    public:
        Student(const std::string& name, const std::string& idNum, const std::string& surname, const std::string& major, int gradYear, const std::string course) : Person(name, idNum, surname), major(major), gradYear(gradYear)  //calls the Person constructor to initialize the parents class
        {
            this->course = new std::string(course);
        }
        void print() const; 
        void changeMajor (const std::string& newMajor) {major = newMajor;}

        ~Student() 
        {
            std::cout << "Student Destructor called" << std::endl;
            delete course; 
        }

};


void Student::print() const 
{
    Person::print(); 
    // p.print();
    std::cout << "Major: " << major << std::endl;
    std::cout << "Graduation Year: " << gradYear << std::endl;
    std::cout << "Course: " << *course << std::endl;
}

int main ()
{
    // Student* s = new Student ("John", "123", "Doe", "Computer Science", 2023, "C++");

    // // Person p = *s; //shallow copy

    // // std::cout << "Person print" << std::endl;
    // // p.print();

    // std::cout << "Student print" << std::endl;
    // s->print(); 


    Person* p [2];
    p[0] = new Student {"Andrea", "10665938", "Damiano", "Computer Science", 2023, "C++"};
    p[1] = new Person  {"Andrea", "10665938", "Damiano"};

    // p[0]->changeMajor("Maths");

    Student* s = dynamic_cast<Student*> (p[0]);
    s->changeMajor("Maths");

    Student* s2 = dynamic_cast<Student*> (p[1]);

    if (s2 == NULL)
    {
        std::cout << "invalid casting" << std::endl;
    }

    delete p[0];
    delete p[1];


}