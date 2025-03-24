#include <iostream>

using E = int; 

class Sequence 
{
    static constexpr int DEF_CAPACITY = 100; //default capacity of the array 

    private:
        struct Position
        { 
            int index; 
            E element; 
            Position(int index , const E& element) : index(index), element(element) {}
        }; 

    private:
        int f; //front of the circular array
        Position** array; 
        int capacity; 
        int n; 

    public: 
        class Iterator 
        {
            public:
                //operator overloading 
                E& operator*(); 
                bool operator==(const Iterator& it) const;
                bool operator!=(const Iterator& it) const; 
                Iterator& operator++(); 
                Iterator& operator--(); 
                friend class Sequence; //Sequence can access the private members of the iterator class 

            private: 
                Position* p; 
                const Sequence* s; 
                Iterator(const Sequence* s, Position* p); //private constructor, so that only the sequence is allowed to create a new iterator  
        };

    public:
        Sequence(int capacity = DEF_CAPACITY) : f(0), capacity(capacity), n(0), array(new Position*[capacity]()) {}
        ~Sequence();
        int size () const; 
        bool empty() const; 
        Iterator atIndex(int index) const;
        int indexOf(const Iterator& it) const; 
        Iterator begin() const; 
        Iterator end() const;   
        void insertFront(const E& element); 
        void insertBack(const E& element); 
        void eraseFront();
        void eraseBack(); 
    
    protected:
        void insert(const Iterator& it, const E& element); //insert before an iterator 
        void erase(const Iterator& it);
};


Sequence::Iterator::Iterator(const Sequence* s, Position* p) : p(p) , s(s) {}

E& Sequence::Iterator::operator*()
{
    return p->element; 
}

bool Sequence::Iterator::operator==(const Iterator& it) const
{
    return p == it.p; //check if they point to the same mempry address 
}

bool Sequence::Iterator::operator!=(const Iterator& it) const
{
    return p != it.p ; 
}

Sequence::Iterator& Sequence::Iterator::operator++()
{
    p=s->array[(p->index+1)%s->capacity];  //update position
    return *this; 
}

Sequence::Iterator& Sequence::Iterator::operator--()
{
    p = s->array[(p->index-1+s->capacity)%s->capacity]; 
    return *this;
}

Sequence::~Sequence()
{
    for (int i=0; i<n; ++i)
    {
        int logic_index = (f+i)% capacity; 
        delete array[logic_index]; 
    }

    delete[] array; 
}

int Sequence::size() const
{
    return n; 
}

bool Sequence::empty() const
{
    return n==0; 
}


Sequence::Iterator Sequence::begin() const 
{
    return Iterator(this, array[f]);  
}        

Sequence::Iterator Sequence::end() const
{
    return Iterator(this, array[(f+n)%capacity]);
}  

Sequence::Iterator Sequence::atIndex(int index) const
{
    return Iterator(this, array[(f+index)%capacity]); 
}

int Sequence::indexOf(const Iterator& it) const
{
    return (it.p->index -f +capacity)%capacity; 
}

void Sequence::insert(const Iterator& it, const E& element) 
{
    if (n>= capacity)
        throw std::runtime_error("Sequence full"); 

    int real_index; //this will be assigned to the position index 

    if (n==0)//empty sequence case
        real_index = f; 
    
    else if (it.p == nullptr) //end iterator
    {
        real_index = n; 
    }
 
    else{
        int logic_index = indexOf(it);  
        if (logic_index <= n/2)
        {
            f = (f-1+capacity)%capacity; 
            real_index = (f+logic_index)%capacity; 
            for (int i=0; i<logic_index ; ++i)
            {
                int curr = (f+i)% capacity; 
                int next = (f+i+1)% capacity; 
                array[curr] = array[next];
                array[curr]->index = curr; 
            }
            
        }
        else
        {
            real_index = (f+logic_index)%capacity; 
            for (int i=n; i>logic_index; --i)
            {
                int curr = (f+i)% capacity; 
                int prev = (f+i-1)%capacity; 
                array[curr] = array[prev];
                array[curr]->index = curr;  
            }
        }
    
    }

    array[real_index] = new Position(real_index, element); //create a new position
    ++n; 
}

void Sequence::erase(const Iterator& it)
{
    if (it.p == nullptr)
    {
        delete array[(n-1-f)%capacity]; 
        array[(n-1-f)%capacity] = nullptr; 
    }

    else if (indexOf(it) == 0)
    {
        int real_index = it.p->index; 
        int logic_index = indexOf(it);

        delete array[real_index]; 
        array[real_index] = nullptr;
        f = (f+1)% capacity; 
    }

    else
    {
        int real_index = it.p->index; 
        int logic_index = indexOf(it); 
        delete array[real_index];
        array[real_index] = nullptr; 


        if (logic_index < n/2)
        {
            for(int i =logic_index; i>0; --i)
            {
                int curr = (f+i)%capacity; 
                int prev = (f+i-1)%capacity;
                array[curr] = array[prev];
                if (array[curr])
                    array[curr]->index = curr; //update index 
            }
        }
        else
        {
            for (int i=0; i<n; ++i)
            {
                int curr = (f+i)%capacity;
                int next = (f+i+1)% capacity; 
                array[curr] = array[next];
                if (array[curr])
                    array[curr]->index = curr; 
            }
        } 
    }

    --n;
}

void Sequence::insertFront(const E& element)
{
    if (n>= capacity)
        throw (std::runtime_error("Sequence full")); 
    insert(begin(), element); 
}

void Sequence::insertBack(const E& element)
{
    if (n>= capacity)
        throw (std::runtime_error("Sequence full"));
    insert(end(), element); 
}

void Sequence::eraseFront()
{
    erase(begin()); 
}

void Sequence::eraseBack()
{
    erase(end()); 
}

int main()
{
    Sequence s; 
    try
    {
        for(int i=0; i< 99; ++i)
        {
            s.insertBack(i); 
        }
    }
    catch(std::runtime_error& error)
    {
        std::cout << error.what() << std::flush; 
    }
    
    // for (auto it = s.begin(); it !=s.end(); ++it)
    //     std::cout << *it << "\n";  

    //delete elements 
    for (int i =0; i< 5 ; ++i)
    {
        s.eraseFront(); 
    }

    for (auto it = s.begin(); it !=s.end(); ++it)
        std::cout << *it << "\n";  
}