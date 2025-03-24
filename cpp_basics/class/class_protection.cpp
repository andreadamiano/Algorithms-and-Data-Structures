#include <iostream>
#include <string>

class Base 
{
    private:
        std::string priv = "private"; 
    protected:
        std::string prot = "protected";
    public:
        std::string pub = "public";
}; 

class Derived : public Base
{
    public: 
        // void print_priv() {std::cout << priv << std::endl;} //error: ‘int Base::priv’ is private within this context
        void print_prot() {std::cout << prot << std::endl;} 
        void print_pub() {std::cout << pub << std::endl;} 

};

int main ()
{
    Derived d; 
    // d.print_priv(); 
    d.print_prot(); 
    d.print_pub();
}