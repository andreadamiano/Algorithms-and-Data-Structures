#include <stack>
#include <iostream>
#include <string>
#include <vector>
#include "SinglyLinkedList.h"

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


template<typename E>
class LinkedStack : public Stack<E>
{
    public:
        LinkedStack(); 
        ~LinkedStack(); 
        int size() const; 
        bool empty() const; 
        const E& top() const;
        void push(const E& element); 
        void pop();  

    private: 
        List<E> list; //single linked list implemented in the header file 
        int n; //n of elements 


};

template <typename E>
LinkedStack<E>::~LinkedStack()
{
    //we rely on the list destructor
}

template <typename E>
LinkedStack<E>::LinkedStack() : n(0), list() {} //list() calls the default constructor 

template <typename E>
int LinkedStack<E>::size() const
{
    return n; 
}

template <typename E>
bool LinkedStack<E>::empty() const
{
    //return(list.empty());
    return(n==0); 
}

template <typename E>
const E& LinkedStack<E>::top() const 
{
    if (empty())
        throw StackEmpty("error, the stack is empty");
    return list.front(); 
}


template <typename E>
void LinkedStack<E>::push(const E& element)
{
    ++n; //increment size 
    list.addFront(element); 
}

template <typename E>
void LinkedStack<E>::pop()
{
    if (empty())
        throw(StackEmpty("error, the stack is empty"));
    
    --n; //decrement size 
    list.removeFront(); 
}



int main ()
{
    // std::stack<int> stack; 

    // stack.push(10); 
    // stack.push(5); 


    // //create a temporary stack to loop through
    // std::stack<int> temp(stack); 

    // while(!temp.empty())
    // {
    //     std::cout << temp.top() << std::endl; 
    //     temp.pop(); //pop the top element
    // }

    Stack<int>* stack = new ArrayStack<int>;

    // Stack<int>* stack = new LinkedStack<int>; 
    

    try
    {
        // stack->pop(); 
        stack->push(10); 
        std::cout << stack->size() <<std::endl;
        std::cout << stack->top() <<std::endl;  
    }
    catch(const StackEmpty& error)
    {
        std::cout << error.getError();
    }
    catch(const StackFull& error)
    {
        std::cout <<error.getError();
    }

    
}