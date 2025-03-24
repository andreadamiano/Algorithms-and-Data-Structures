#include <iostream>
#include <string>

template <typename T> //the compiler needs to know that th class is a template before mentioning as a fri
class TList; 

class Node 
{
    private:
        std::string element; 
        Node* next; 

    friend class List; //grant access to private elements to List
};


template <typename T>
class TNode
{
    private:
        T element; 
        TNode<T>* next; 

    friend class TList<T>; 
};


class List 
{
    public: 
        List() : head (NULL) {}
        ~List(); 

        //accessory functions 
        bool empty() const; //check if the list is empty
        const std::string& front() const; //get the element of the front Node 
        void addFront(const std::string& element); //add element to the front 
        void removeFront(); //remove element front node 
        void print(); 

    private:
        Node* head; //points to the head of the list 

}; 


List::~List()
{
    while (!empty()) removeFront(); 
}


bool List::empty() const
{
    return head == NULL; 
}

const std::string& List::front() const
{
    return head->element; 
}


void List::addFront(const std::string& element)
{
    Node* node = new Node; //create a new node
    node->element = element; //initialize the value of the element 
    node->next = head; //the new node comes before the head
    head = node; //move the head to the newly created node 
}

void List::removeFront()
{
    Node* old = head; 
    head = head->next; 
    delete old; 
}


void List::print()
{
    Node* node = head; 
    while(node!=NULL)
    {
        std::cout << node->element <<std::endl; 
        node = node->next;
    }
}



template <typename T>
class TList
{
    private:
        TNode<T>* head; 
    public:
        public: 
        TList() : head (NULL) {}
        ~TList(); 

        //accessory functions 
        bool empty() const; //check if the list is empty
        const T& front() const; //get the element of the front Node 
        void addFront(const T& element); //add element to the front 
        void removeFront(); //remove element front node 
        void print(); 
}; 

template <typename T>
TList<T>::~TList()
{
    while (!empty()) removeFront(); 
}


template <typename T>
bool TList<T>::empty() const
{
    return head == NULL; 
}


template <typename T>
const T& TList<T>::front() const
{
    return head->element; 
}


template <typename T>
void TList<T>::addFront(const T& element)
{
    TNode<T>* node = new TNode<T>; //create a new node
    node->element = element; //initialize the value of the element 
    node->next = head; //the new node comes before the head
    head = node; //move the head to the newly created node 
}


template <typename T>
void TList<T>::removeFront()
{
    TNode<T>* old = head; 
    head = head->next; 
    delete old; 
}


template <typename T>
void TList<T>::print()
{
    TNode<T>* node = head; 
    while(node!=NULL)
    {
        std::cout << node->element <<std::endl; 
        node = node->next;
    }
}



int main()
{
    TList<int> list; //create a new empty list 

    // list.addFront("ciao");
    // list.addFront("come");
    // list.addFront("stai");
    // list.addFront("?");

    list.addFront(1);
    list.addFront(2);
    list.addFront(3);
    list.addFront(4);

    list.print(); 



}