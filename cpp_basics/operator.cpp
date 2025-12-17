#include <iostream>

class myclass
{
    public:
        static int num;
        int num_2;
};

int myclass::num = 10; // static variable initialization, static member are accessed with :: 

class Complex 
{
    private:
        int real, imag;
    
    public:
        Complex(double r, double i) : real(r), imag(i) {} // constructor with initialization list

        bool operator == (const Complex &obj) 
        {
            return (real == obj.real && imag == obj.imag);
        }
};


int main ()
{
    myclass obj;
    obj.num_2 = 20; 
    std::cout << obj.num << std::endl;
    std::cout << obj.num_2 << std::endl;    


    int x = 1; 
    int y = 2; 

    x < y ? std::cout << "true" << std::endl : std::cout << "false" << std::endl;

    int num_3  = 10; 
    int  num_4 = 12;

    num_4 &= num_3 ;

    std::cout << num_3 << std::endl;

    //operator overloading
    Complex c1(3, 7), c2(3, 7);
    if (c1 == c2)
    {
        std::cout << "Equal" << std::endl;
    }
    else
    {
        std::cout << "Not equal" << std::endl;
    }

}


