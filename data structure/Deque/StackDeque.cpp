#include <iostream>
#include "dequeue.h"

class Error
{
    public: 
        Error(const std::string& error) : error(error) {}
        std::string getError() const {return error;}

    private:
        std::string error; 
};

class StackEmpty: public Error
{
    public: 
        StackEmpty(const std::string& error) : Error(error) {}
};

class StackFull: public Error
{
    public: 
        StackFull(const std::string& error) : Error(error) {}
};

//dequeue wrapper to implement the stack 
using E = int; 
class StackDequeue
{
    public: 
        StackDequeue() : D() {}
        int size () const; 
        bool empty() const; 
        const E& top() const; 
        void push (const E& element); 
        void pop (); 

    private:
        LinkedDequeue D; 
}; 

int StackDequeue::size() const
{
    return D.size(); 
}

bool StackDequeue::empty() const 
{
    return D.empty(); 
}

const E& StackDequeue::top() const 
{
    if (D.empty())
        throw StackEmpty("error, the stack is empty"); 
    return D.front(); 
}

void StackDequeue::push(const E& element) 
{
    D.insertFront(element); 
}

void StackDequeue::pop() 
{
    if (D.empty())
        throw StackEmpty("error, the stack is empty"); 
    D.removeFront(); 
}

int main ()
{
    StackDequeue stack; 

    try 
    {
        stack.push(1); 
        stack.push(2); 
        stack.push(3); 
        
    }
    catch(StackEmpty& error)
    {
        std::cout << error.getError(); 
    }
    catch(StackFull& error)
    {
        std::cout << error.getError(); 
    }

    //visualize 
    while(!stack.empty())
    {
        std::cout << stack.top() << "\n"; 
        stack.pop(); 
    }

}