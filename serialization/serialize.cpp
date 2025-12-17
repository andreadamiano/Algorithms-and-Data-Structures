#include "serializable.h"

int main()
{
    Serializable person("Andrea", 24); 
    // person.serialize("serialize_output.txt"); 
    person.deserialize("serialize_output.txt"); 
    
    // Print the deserialized data
    std::cout << "Name: " << person.getName() << std::endl;
    std::cout << "Age: " << person.getAge() << std::endl;
}