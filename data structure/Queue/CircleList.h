#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include <iostream>
#include <string>

//define a custom type 
typedef std::string elem; 

class Node
{
    private:
        elem element; 
        Node* next; 

    friend class CircleList; 
};


class CircleList
{
    public:
        CircleList(); 
        ~CircleList();
        bool empty() const; 
        const elem& front() const; 
        const elem& back() const; 
        void advance(); 
        void addafter(const elem& element);  //add element before the cursor 
        void removeafter(); //remove element after the cursor 
        void print() const; 


    private:
        Node* cursor; 

}; 


CircleList::CircleList() : cursor(NULL) 
{
}

CircleList::~CircleList() 
{
    while(!empty()) removeafter();
}

bool CircleList::empty() const
{
    return(cursor==NULL); 
}


const elem& CircleList::front() const
{
    return cursor->next->element;
}


const elem& CircleList::back() const
{
    return cursor->element;
}


void CircleList::advance()
{
    cursor = cursor->next; 
}


void CircleList::addafter(const elem& element)
{
    //create a new node
    Node* node = new Node; 
    node->element = element; 

    if (cursor == NULL)
    {
        node->next = node; //node points to himself 
        cursor = node; 
    }

    else
    {
        node->next= cursor->next; 
        cursor->next = node; 
    }
}


void CircleList::removeafter()
{
    Node* temp = cursor->next;

    if (temp==cursor) 
        cursor==NULL; 
    
    else
        cursor->next = temp->next;
    delete temp;  

}


void CircleList::print() const
{
    Node* temp = cursor; 

    do
    {
        std::cout << temp->element <<std::endl; 
        temp = temp->next; 
    }while(temp !=cursor); 
}

#endif