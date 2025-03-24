#ifndef DEQUE_H
#define DEQUE_H


#include <iostream>
#include <string>
#include "doubly_linked_list.h"

class RuntimeException
{
    public: 
        RuntimeException(const std::string& error) : error(error) {}
        std::string getError() const {return error;}

    private:
        std::string error; 
};

class QueueEmpty: public RuntimeException
{
    public: 
        QueueEmpty(const std::string& error) : RuntimeException(error) {}
};

class QueueFull: public RuntimeException
{
    public: 
        QueueFull(const std::string& error) : RuntimeException(error) {}
};

using E = int; 

class Dequeue
{
    public:
        virtual void insertFront(const E& element) =0; 
        virtual void insertBack(const E& element) =0; 
        virtual void removeFront() =0; 
        virtual void removeBack () =0;
        virtual const E& front() const =0; 
        virtual const E& back () const =0 ;
        virtual int size() const =0; 
        virtual bool empty() const =0; 
}; 



class LinkedDequeue : public Dequeue
{
    public:

        LinkedDequeue() : L(), n(0) {} 
        ~LinkedDequeue() {} //we rely on the List destructor 
        void insertFront(const E& element) ; 
        void insertBack(const E& element) ; 
        void removeFront() ; 
        void removeBack () ;
        const E& front() const ; 
        const E& back () const  ;
        int size() const ; 
        bool empty() const ; 

    private:
        int n; 
        List<int> L; 
}; 

void LinkedDequeue::insertFront(const E& element)
{
    L.addFront(element); 
    n++; 
}

void LinkedDequeue::insertBack(const E& element)
{
    L.addBack(element); 
    n++; 
}

void LinkedDequeue::removeFront()
{
    if (empty())
        throw QueueEmpty("error, the queue is empty"); 
    L.removeFront();
    n--; 
}

void LinkedDequeue::removeBack()
{
    if (empty())
        throw QueueEmpty("error, the queue is empty"); 
    L.removeBack();
    n--; 
}

int LinkedDequeue::size() const
{
    return n; 
}

bool LinkedDequeue::empty() const 
{
    return n==0; 
}

const E& LinkedDequeue::front() const 
{
    return L.front(); 
}

const E& LinkedDequeue::back () const 
{
    return L.back(); 
}

#endif