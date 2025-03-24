#include <iostream>

class Shape
{
    public: 
        virtual void print() =0;  //pure virtual function
};


class Circle: public Shape
{
    public:
        void print() override {std::cout << "drawing a circle" << std::endl;}
};

int main ()
{
    Shape* s [0];
    s[0] = new Circle; 

    s[0]->print();

    delete s[0]; 


    //you can't create an object of a class that has one or more pure virtual functions
    Shape shape;
}