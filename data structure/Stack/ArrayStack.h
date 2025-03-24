#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include "SinglyLinkedList.h"
#include <string>
//exception class  thrown on performing top or pop of an empty stack
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



//stack interface (the actual implementation inherits from this class)
template <typename E>
class Stack //pure virtual class (it cannot be instantiate directly)
{
    public:
        virtual ~Stack() {}
        virtual int size() const = 0;       // Derived classes must implement
        virtual bool empty() const = 0;     // Derived classes must implement
        virtual const E& top() const = 0;   // Derived classes must implement
        virtual void push(const E& e) = 0;  // Derived classes must implement
        virtual void pop() = 0;             // Derived classes must implement
};



//stack implementation using an array 
template <typename E>
class ArrayStack : public Stack<E>
{
    static constexpr int DEF_CAPACITY =100; //static means that the member belongs to the class itself, not to any specific object of the class, constexpr ensure the constant is evaluated at compile time        
    private:
        int capacity;
        int t; //index of the top of the stack  
        E* array;  

    public:
        ArrayStack(int capacity = DEF_CAPACITY) : capacity(capacity), array(new E[capacity]), t(-1) {}
        int size() const; 
        bool empty() const; 
        ~ArrayStack(); 
        const E& top() const;
        void push(const E& element); 
        void pop();  

}; 

template <typename E>
ArrayStack<E>::~ArrayStack()
{
    for (int i =0; i<=t; i++)
    {
        array[i].~E(); //calling the destructor of the element (for an array of objects)
    }

    delete[] array; //sufficient for primitive types 
}

template <typename E>
int ArrayStack<E>::size() const
{
    return t +1; 
}

template <typename E>
bool ArrayStack<E>::empty() const
{
    return (t < 0); 
}

template <typename E>
const E& ArrayStack<E>::top() const
{
    if(empty())
        throw StackEmpty("error, the stack is empty"); 
    
    return array[t]; 
}

template <typename E>
void ArrayStack<E>::push(const E& element) 
{
    if(size() == capacity)
        throw StackFull("error, the stack is full");
    array[++t] = element; //increase top index and add element 
}

template <typename E>
void ArrayStack<E>::pop() 
{
    if(empty())
        throw StackEmpty("error, the stack is empty"); 

    t--; //move the top index to the left (the element is not actually removed)

}

#endif
