#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

template <typename T> //the compiler needs to know that the class is a template before mentioning as a friend
class List; 

template <typename T>
class Node
{
    private:
        T element; 
        Node<T>* next; 

    friend class List<T>; 
};

template <typename T>
class List
{
    private:
        Node<T>* head; 
    public:
        public: 
        List() : head (NULL) {}
        ~List(); 

        //accessory functions 
        bool empty() const; //check if the list is empty
        const T& front() const; //get the element of the front Node 
        void addFront(const T& element); //add element to the front 
        void removeFront(); //remove element front node 
        void print(); 
}; 

//implementation (For template classes, it’s common to include the implementation directly in the header file. This ensures that the compiler has access to the full definition when it needs to instantiate the template)

template <typename T>
List<T>::~List()
{
    while (!empty()) removeFront(); 
}


template <typename T>
bool List<T>::empty() const
{
    return head == NULL; 
}


template <typename T>
const T& List<T>::front() const
{
    return head->element; 
}


template <typename T>
void List<T>::addFront(const T& element)
{
    Node<T>* node = new Node<T>; //create a new node
    node->element = element; //initialize the value of the element 
    node->next = head; //the new node comes before the head
    head = node; //move the head to the newly created node 
}


template <typename T>
void List<T>::removeFront()
{
    Node<T>* old = head; 
    head = head->next; 
    delete old; 
}


template <typename T>
void List<T>::print()
{
    Node<T>* node = head; 
    while(node!=NULL)
    {
        std::cout << node->element <<std::endl; 
        node = node->next;
    }
}


#endif