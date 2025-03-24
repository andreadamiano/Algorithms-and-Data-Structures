#include <iostream>
#include <string>

class Exception
{
    public:
        Exception(const std::string& message): message(message) {}

        std::string getMessage() const  {return message;}

        friend std::ostream& operator<< (std::ostream& os , const Exception& message);

    private:
        std::string message; 
};


std::ostream& operator<< (std::ostream& os , const Exception& message)
{
    os << message.getMessage();

    return os;
}


void function () 
{
    throw Exception("An exception has occurred");
}

int main ()
{
    try
    {
        function();
    }
    catch(const Exception& e)
    {
        std::cerr << e.getMessage() << std::endl;
    }
    
}