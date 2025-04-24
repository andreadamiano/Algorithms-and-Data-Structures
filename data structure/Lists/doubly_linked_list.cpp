#include <iostream>
#include <string>

template <typename T>
class List; 

template <typename T>
class Node
{
    private:
        Node<T>* next; 
        Node<T>* previous; 
        T element; 

    friend class List<T>; 

}; 


template <typename T>
class List 
{
    public: 
        List();
        ~List(); 

        //accessory functions 
        bool empty() const; //check if the list is empty
        const T& front() const; //get the element of the front Node 
        const T& back() const; //get the element from the back Node 
        void addFront(const T& element); //add element to the front 
        void addBack(const T& element); //add element to the back 
        void removeFront(); //remove element front node 
        void removeBack(); //remove element back node 
        void print(); 




    private: 
        Node<T>* head; 
        Node<T>* tail; 

    protected: 
        //utility functions 
        void addbefore(Node<T>* target_node, const T& element); //add new node before a target node
        void remove(Node<T>* target_node); 
}; 


template <typename T>
List<T>::List()
{
    //create sentinels (dummy nodes that do not store any elements)
    head = new Node<T>; 
    tail = new Node<T>; 

    //they point to each others
    head->next = tail; 
    tail->previous = head; 
}


template <typename T>
List<T>::~List()
{
    //remove all nodes but the sentinels
    while(!empty()) removeFront(); 

    //delete sentinels
    delete head; 
    delete tail; 
}


template <typename T>
bool List<T>::empty() const
{
    return (head->next == tail); 
}


template <typename T>
const T& List<T>::front() const //get front element
{
    return head->next->element; 
}


template <typename T>
const T& List<T>::back() const//get back element 
{
    return tail->previous->element; 
}

template <typename T>
void List<T>::addbefore(Node<T>* target_node, const T& element)
{
    Node<T>* node = new Node<T>; //create a new node 
    node->element = element; 

    node->next = target_node; 
    node->previous = target_node->previous; 
    target_node->previous = target_node->previous->next = node; 

}

template <typename T>
void List<T>::addBack(const T& element)
{
    addbefore(tail, element); 
}



template <typename T>
void List<T>::addFront(const T& element)
{
    addbefore(head->next, element); 
}


template <typename T>
void List<T>::remove(Node<T>* target_node)
{
    target_node->previous->next = target_node->next; 
    target_node->next->previous = target_node->previous; 

    delete target_node;  
}


template <typename T>
void List<T>::removeBack()
{
    remove(tail->previous); 
}


template <typename T>
void List<T>::removeFront()
{
    remove(head->next); 
}

template <typename T>
void List<T>::print()
{
    Node<T>* node = head->next; 
    while(node!=tail)
    {
        std::cout << node->element <<std::endl; 
        node = node->next;
    }
}


template <typename T>
void reverse(List<T>& list)
{
    List<T> temp; 
    while(!list.empty())
    {
        temp.addFront(list.front());
        list.removeFront(); 
    }
    while(!temp.empty())
    {
        list.addBack(temp.front()); 
        temp.removeFront(); 
    }
}


int main ()
{
    List<std::string> list;

    list.addBack("ciao");
    list.addFront("come sta??");
    list.addBack("ultima volta"); 


    list.print(); 


    //iverse list 
    std::cout<<"inverse list" <<std::endl; 
    reverse(list); 

    list.print(); 
}