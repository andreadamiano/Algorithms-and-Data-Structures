#include <string>
#include <iostream>
#include <memory>

class Object
{
    public:
        virtual ~Object() {} 
        int intValue(); 
        std::string stringValue(); 


}; 


class Integer: public Object
{
    private:
        int value; 

    public:
        Integer(int _value) : value(_value) {}
        int getValue() const {return value; }
}; 

class String: public Object
{
    private:
        std::string  value; 

    public:
        String(std::string& _value) : value(_value) {}
        std::string getValue() const {return value; }

}; 

int Object::intValue()
{
    const Integer* p = dynamic_cast<const Integer* > (this); 
    if ( p == NULL)
        throw std::runtime_error("Illegal attempt to cast to Integer"); 
    return p->getValue(); 
}