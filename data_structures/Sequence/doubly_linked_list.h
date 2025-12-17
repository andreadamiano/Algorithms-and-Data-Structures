#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

using E = int; 

class List 
{
    private:
        struct Node //members public by default 
        {
            E element; 
            Node* prev; 
            Node* next; 
        }; 

    public: 
        class Iterator 
        {
            public:
                //operator overloading 
                E& operator*(); 
                bool operator==(const Iterator& iterator) const;
                bool operator!=(const Iterator& iterator) const; 
                Iterator& operator++(); 
                Iterator& operator--(); 
                friend class List; //List can access the private members of the iterator class 

            private: 
                Node* node; 
                Iterator(Node* node); //private constructor, so that only the list is allowed to create a new iterator  
        };

    public: 
        List(); 
        List(const List& list); //copy constructor 
        ~List(); 

        int size () const; 
        bool empty() const; 
        Iterator begin() const; //return newly created iterator 
        Iterator end() const; 
        void insertFront(const E& element); 
        void insertBack(const E& element); 
        void insert(const Iterator& iterator, const E& element); //insert an element before an iterator
        void erase (const Iterator& iterator); //erase iterator
        void eraseFront(); 
        void eraseBack(); 

        //operator overloading 
        List& operator= (const List& list); 


    private: 
        int n; //number of items 
        Node* header; 
        Node* trailer; 

}; 

List::Iterator::Iterator(Node* node) : node(node) {}

E& List::Iterator::operator*()
{
    return node->element; 
}

bool List::Iterator::operator==(const Iterator& iterator) const
{
    return node == iterator.node; //check if they point to the same mempry address 
}

bool List::Iterator::operator!=(const Iterator& iterator) const
{
    return node != iterator.node ; 
}

List::Iterator& List::Iterator::operator++()
{
    //move iterator 
    node = node->next; 
    return *this; 
}

List::Iterator& List::Iterator::operator--()
{
    node = node->prev; 
    return *this; 
}

List::List() : n(0)
{
    //initialize header and trailer 
    header = new Node; 
    trailer = new Node; 

    //header and trailer point to each others 
    header->next = trailer; 
    trailer->prev = header; 
}

List::~List()
{
    while(!empty())
        eraseFront(); 

    //remove sentinels 
    delete header; 
    delete trailer; 
}

List::List(const List& list) : n(list.n)
{
    //initialize sentinel nodes
    header = new Node; 
    trailer = new Node; 

    header->next = trailer; 
    trailer->prev = header; 

    //copy elements 
    Iterator it = list.begin(); 

    while(it != list.end())
    {
        insertBack(*it); 
        ++it; 
    }
}

List& List::operator=(const List& list)
{
    //self-assignment
    if(this == &list)
        return *this;

    //eliminate old elements 
    while(!empty())
        eraseFront(); 

    //copy elements 
    Iterator it = list.begin(); 
    while(it != list.end())
    {
        insertBack(*it); 
        ++it; 
    }

    //update n
    n = list.n; 

    return *this; 
}


int List::size() const 
{
    return n;  
}

bool List::empty() const 
{
    return n==0; 
}

List::Iterator List::begin() const
{
    return Iterator(header->next); 
}

List::Iterator List::end() const 
{
    return Iterator(trailer); 
}


void List::insert(const Iterator& iterator, const E& element)
{
    Node* node = new Node; //create a new node on the heap to outlive the function scope 
    node->element = element; 

    //connect node
    node->prev = iterator.node->prev; 
    node->next = iterator.node;

    //connect other nodes
    iterator.node->prev = iterator.node->prev->next = node; 

    //incremente number of nodes 
    n++; 
}


void List::insertFront(const E& element)
{   
    insert(begin(), element); 
}   

void List::insertBack(const E& element)
{
    insert(end(), element); 
}

void List::erase (const Iterator& iterator)
{
    //disconnect the node 
    iterator.node->prev->next = iterator.node->next; 
    iterator.node->next->prev = iterator.node->prev; 

    //delete node
    delete iterator.node; 

    //decrement number of nodes
    n--; 
}


void List::eraseFront()
{
    erase(begin()); 
}

void List::eraseBack()
{
    erase(--end()); 
}


#endif