


template <typename T> 
class BinarySearchTree
{
    private:
        struct Element
        {
            int key; 
            T value; 
        };
        
        struct Node
        {
            Node* left;
            Node* right; 
            Node* parent; 
            Element element; 

            Node(T& _element) : element(_element) {}
        };
        Node* root; 
        Node* NIL; 

    public:

        class Iterator
        {
            private:
                Node* node; 

            public:
                Iterator operator++(Iterator& it); 
                Iterator operator--(Iterator& it); 
                T operator*(Iterator it); 

                Iterator(Node* _node) : node(_node) {}
        }; 
        BinarySearchTree(); 
        ~BinarySearchTree(); 

        Iterator begin(); 
        Iterator end(); 
        Iterator search(T& value); 
        Iterator insert(Element& element); 

    private:
        void clear(Node* node); 
        Node* search(T& value, Node* node); 
        Node* insert(Element& element, Node* node); 
        void remove(T& value); 
        void transplant(Node* original, Node* replacement);
        Node* minimum(Node* node); 
        
}; 

template <typename T>
BinarySearchTree<T>::BinarySearchTree()
{
    NIL = new Node(); 
    NIL->parent = NIL; 
    NIL->left = NIL; 
    NIL->right = NIL; 

    root = NIL; 
}

template <typename T>
void BinarySearchTree<T>::clear(Node* node)
{
    if (node == NIL)
        return; 
    clear(node->left); 
    clear(node->right); 
    delete node; 
}


template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    clear(root); 
}

template <typename T>
BinarySearchTree<T>::Iterator BinarySearchTree<T>::begin()
{
    return root; 
}

template <typename T>
BinarySearchTree<T>::Iterator BinarySearchTree<T>::end()
{
    Node* node = root; 
    while (node != NIL)
    {
        node = node->right; 
    }
    return Iterator(NIL); 
     
}

template <typename T>
BinarySearchTree<T>::Node* BinarySearchTree<T>::search(T& value, Node* node)
{
    if (node == NIL || node->element.key == value)
        return  node;
    
    if (value < node->element.key)
        return search(node->left); 
    return search(node->right); 

}

template <typename T>
BinarySearchTree<T>::Iterator BinarySearchTree<T>::search(T& value)
{
    Node* node = search(node, root); 
    return Iterator(node); 
}

template <typename T>
BinarySearchTree<T>::Node* BinarySearchTree<T>::insert(Element& element, Node* node)
{
    Node* parent = NIL; //keep track of the parent since NIL is a sentinel node 
    Node* current = root;
    
    while (current != NIL && current->element.key != element.key) 
    {
        parent = current;
        if (element.key < current->element.key)
            current = current->left;
        else
            current = current->right;
    }
    if (current != NIL) 
    {
        // Key exists, update value
        current->element.value = element.value;
        return current;
    } else 
    {
        // Insert new node
        Node* new_node = new Node(element);
        new_node->parent = parent;
        new_node->left = NIL;
        new_node->right = NIL;
        if (parent == NIL) 
        {
            root = new_node; 
        } 
        else if (element.key < parent->element.key) 
        {
            parent->left = new_node;
        } 
        else 
        {
            parent->right = new_node;
        }
        return new_node;
    }
}

template <typename T>
BinarySearchTree<T>::Iterator BinarySearchTree<T>::insert(Element& element)
{
    Node* new_node = insert(element); 
    return Iterator(new_node); 
}

template <typename T>
void BinarySearchTree<T>::remove(T& value)
{
    Node* node = search(value, root); 

    if (node == NIL)
        return;
    if (node->left == NIL)
        transplant(node, node->right);
    else if (node->right == NIL)
        transplant(node, node->left);
    else
    {
        Node* successor = minimum(node->right);  //get the inorder successor 
        Node* successor_replacement = successor->right;  //get the replacement of the inorder successor 
        if (successor->parent != node) 
        {
            transplant(successor, successor_replacement);
            successor->right = node->right;
            if (successor->right != NIL)
                successor->right->parent = successor;
        }
        transplant(node, successor);
        successor->left = node->left;
        if (successor->left != NIL)
            successor->left->parent = successor;
    }
    delete node;
}

template <typename T>
void BinarySearchTree<T>::transplant(Node* original, Node* replacement)
{
    if (original->parent == NIL)
        root = replacement; 
    else if (original == original->parent->left)
        original->parent->left = replacement; 
    else    
        original->parent->right = replacement; 
    replacement->parent = original->parent; 
    
}

template <typename T>
BinarySearchTree<T>::Node* BinarySearchTree<T>::minimum(Node* node)
{
    while (node->left != NIL)
    {
        node = node->left; 
    }
    return node; 
}