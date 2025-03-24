#include "CircleList.h"
#include <iostream>
#include <queue>

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

using E = std::string; // queue element type

class Queue
{
    public:
        virtual void enqueue(const E& element) =0; 
        virtual void dequeue () =0; 
        virtual const E& front() const =0; 
        virtual int size() const =0; 
        virtual bool empty() const =0; 
};  


class LinkedQueue : public Queue
{
    public:
        LinkedQueue() : C(), n(0) {}
        ~LinkedQueue(); 
        void enqueue(const E& element); 
        void dequeue();
        bool empty() const; 
        const E& front() const; 
        int size () const; 

    private: 
        int n; 
        CircleList C; 
};

LinkedQueue::~LinkedQueue()
{
    //we rely on the destructor of the circle list 
}

void LinkedQueue::enqueue(const E& element)
{
    C.addafter(element); //add an element to the rear of the queue 
    C.advance(); //advance the cursor to point to the rear of the queue
    n++; 
}

void LinkedQueue::dequeue()
{
    if (empty())
        throw QueueEmpty("error, the queue is empty"); 
    C.removeafter(); 
    n--; 
}

bool LinkedQueue::empty() const 
{
    return (n==0); 
}

const E& LinkedQueue::front() const
{
    if (empty())
        throw QueueEmpty("error, the queue is empty"); 
    return C.front(); 
}

int LinkedQueue::size() const 
{
    return n; 
}

int main ()
{
    Queue* queue = new LinkedQueue; 

    try
    {
        queue->enqueue("ciao");
        queue->enqueue("come");
        queue->enqueue("stai");

    }
    catch(const QueueFull& error)
    {
        std::cout << error.getError(); 
    }
    catch(const QueueEmpty& error)
    {
        std::cout << error.getError(); 
    }

    //visualize 
    while (!queue->empty())
    {
        std::cout << queue->front() << "\n"; 
        queue->dequeue(); 
    }

}