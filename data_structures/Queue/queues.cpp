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




template <typename E>
class Queue
{
    public:
        virtual void enqueue(const E& element) =0; 
        virtual void dequeue () =0; 
        virtual E& front() const =0; 
        virtual int size() const =0; 
        virtual bool empty() const =0; 
}; 


//array-based implemetation
template <typename E>
class ArrayQueue: public Queue<E>
{
    static constexpr int MAX_CAPACITY = 100; 

    private:
        int f; 
        int r; 
        int n; //current number of elements in the queue
        int capacity; 
        E* array; 

    public:
        ArrayQueue(int capacity = MAX_CAPACITY) : capacity(capacity), f(0), r(0), n(0) { array = new E[capacity]; }
        ~ArrayQueue(); 
        void enqueue(const E& element); 
        void dequeue();
        bool empty() const; 
        E& front() const; 
        int size () const; 
        
};

template <typename E>
ArrayQueue<E>::~ArrayQueue()
{
    for (int i =0; i<capacity; i++)
    {
        array[i].~E(); //calls the destructor of the ith element of the array 
    }
    delete[] array; 
}

template <typename E>
void ArrayQueue<E>::enqueue(const E& element) 
{
    if (size()== capacity)
        throw QueueFull("error, the queue is full"); 
    array[r] = element;
    r = (r +1) % capacity; 
    n ++; 
}

template <typename E>
void ArrayQueue<E>::dequeue()
{
    if (empty())
        throw QueueEmpty("error, the queue is empty"); 
    
    f = (f +1) % capacity; 
    n--; 
}

template <typename E>
bool ArrayQueue<E>::empty() const
{
    return (n==0);   
}

template <typename E>
E& ArrayQueue<E>::front() const
{
    if (empty())
        throw QueueEmpty("error, the queue is empty");
    return array[f]; 
}

template <typename E>
int ArrayQueue<E>::size() const 
{
    return n; 
}





//stl imlpementation
int main ()
{
    // std::queue<int> Queue; 

    // //add some elements
    // Queue.push(3); 

    // //visualize 
    // std::cout << Queue.front(); 

    Queue<int>* queue  = new ArrayQueue<int>;  


    // queue->enqueue(1);
    // queue->enqueue(2);
    // queue->enqueue(3);


    try
    {
        queue->enqueue(1);
        queue->enqueue(2);
        queue->enqueue(3);

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

