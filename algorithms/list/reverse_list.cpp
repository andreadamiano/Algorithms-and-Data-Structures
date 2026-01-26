struct Node
{
    int value; 
    Node* next; 
    Node(int _value) : value(_value), next(nullptr) {}
};

void reverseList(Node** head)
{
    Node* current = *head; 
    Node* next = nullptr; 
    Node* prev = nullptr; 

    while (current != nullptr)
    {
        next = current->next; 
        current->next = prev; 
        
        prev = current; 
        current = next; 
    }
    *head = prev; 
    
}


int main()
{
    //build list 
    Node* head = nullptr; 
    Node* current = head; 
    Node* prev = nullptr; 
    for (int i =1; i < 6; ++i)
    {
        current = new Node(i); 
        if (head == nullptr)
        {
            head = current; 
        }
        else
        {
            prev->next = current; 
        }
        prev = current; 
    }

    reverseList(&head); 
}
