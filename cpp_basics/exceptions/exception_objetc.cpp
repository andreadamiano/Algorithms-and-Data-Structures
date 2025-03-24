#include <iostream>
#include <string>
//Exceptions are thrown when a piece of code finds some sort of problem during execution


class  MathException
{
    public:
        //constructor
        MathException(const std::string& error) : errorMsg(error) {}

        //get error message 
        std::string getError() {return errorMsg;}

        friend std::ostream& operator<< (std::ostream& os , const MathException& error);


    private:
        std::string errorMsg; 
};


std::ostream& operator<< (std::ostream& os , const MathException& error)
{
    os << error.errorMsg; 
    return os; 
}

class ZeroDivide : public MathException
{
    public:
        //construcotr
        ZeroDivide(const std::string& error) : MathException(error) {} 
};


class NegativeRoot : public MathException
{
    public:
        NegativeRoot(std::string& error) : MathException(error) {}
};


void function () throw (NegativeRoot)
{
    
}

int main ()
{
    try
    {
        //some mathematical computations
        int divisor {0}; 
        if (divisor ==0)
        {
            throw ZeroDivide("Division by 0 is not allowed"); //throw an exeption,  an object of a class
        }

        std::cout << "no division by 0 found" << std::endl;
    }

    catch(NegativeRoot& message)
    {
        std::cout << message << std::endl;
    }

    // catch (ZeroDivide& message)
    // {
    //     std::cout << message << std::endl;
    // }
}