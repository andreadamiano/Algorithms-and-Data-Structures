#pragma once 
#include <string>

using namespace std; 

class RedBlackTree
{
    private:
        enum class Color { Black, Red };
        struct Node {
            Color color;
            Node* left;
            Node* right;
            Node* parent;
            int value;

            Node(Color _color = Color::Black, int _value = 0) : color(_color), left(nullptr), right(nullptr), parent(nullptr), value(_value) {}
            bool isRed() {return color == Color::Red; }
            bool isBlack() {return color == Color::Black; }   
        };
        Node* NIL;
        Node* root ;
    public:
        RedBlackTree(/* args */);
        ~RedBlackTree();
        void insert(int value); 
        void remove(int value); 

    private:
        void rotate_left(Node* node); 
        void rotate_right(Node* node); 
        void fix_insert(Node* node); 
        void fix_delete(Node* node); 
        Node* search(Node* node, int value) const; 
        void transplant(Node* original, Node* replacement); 
        Node* minimum(Node* node); 

};

void RedBlackTree::rotate_right(Node* x)
{
    Node* y = x->left; 
    x->left = y->right; 

    //update all parent and children
    if(y->right != NIL)
    {
        y->right->parent = x; 
    }
    y->parent = x->parent; 
    if(x->parent == NIL)
    {
        root = y; 
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y; 
    }
    else
    {
        x->parent->right = y; 
    }
    y->right = x; 
    x->parent = y; 
}

void RedBlackTree::rotate_left(Node* x)
{
    Node* y = x->right; 
    x->right = y->left; 
    
    //update all parent and child of x and y
    if (y->left != NIL)
    {
        y->left->parent = x;
    }
    y->parent = x->parent; 
    if (x->parent == NIL)
    {
        root = y; 
    }
    else if(x == x->parent->right)
    {
        x->parent->right = y; 
    }
    else
    {
        x->parent->left = y; 
    }
    y->left = x; 
    x->parent = y; 
}

RedBlackTree::RedBlackTree()
{
    NIL = new Node();
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;
    root = NIL;
}

RedBlackTree::~RedBlackTree()
{
    delete NIL;
}

void RedBlackTree::insert(int value)
{
    Node* new_node = new Node(Color::Red,  value); //a new node inserted has alwasy color red   
    new_node->left = new_node->right = NIL; 
    Node* current_node = root; 
    Node* parent = NIL; 

    while(current_node != NIL)
    {
        parent = current_node; //keep track of the parent of the NIL node found 
        if (new_node->value < current_node->value)
            current_node = current_node->left;
        else
            current_node = current_node->right; 
    }

    new_node->parent = parent;
    if(parent == NIL)
    {
        root = new_node; 
        new_node->color = Color::Black; 
        new_node->parent = NIL; 
    }
        
    else if (new_node->value < parent->value )
        parent->left = new_node; 

    else    
        parent->right = new_node; 

    fix_insert(new_node); 
}

void RedBlackTree::fix_insert(Node* node)
{
    while (node != root && node->parent->isRed())
    {
        //find if the parent is the left or right node 
        if (node->parent == node->parent->parent->left)
        {
            Node* uncle = node->parent->parent->right; 
            
            //check if the uncle is balck or red 
            if(uncle->isBlack())
            {
                //check if the new node is the left or right node 
                if (node == node->parent->right)
                {
                    //if the node is the right node, make a left left strcuture 
                    node = node->parent; 
                    rotate_left(node); 
                }
                node->parent->color = Color::Black; 
                node->parent->parent->color = Color::Red; 
                rotate_right(node->parent->parent); 
            }
            else
            {
                node->parent->color = Color::Black; 
                uncle->color = Color::Black; 
                node->parent->parent->color = Color::Red; 
                node = node->parent->parent; //move upward to the grandparent and repeat the check 
            }
        }

        else
        {
            Node* uncle = node->parent->parent->left; 

            if (uncle->isBlack())
            {
                if (node == node->parent->left)
                {
                    node = node->parent; 
                    rotate_right(node); //get into a structure of right-right
                }
                node->parent->color = Color::Black; 
                node->parent->parent->color = Color::Red; 
                rotate_left(node->parent->parent); 
            }
            else
            {
                node->parent->color = Color::Black; 
                uncle->color = Color::Black; 
                node->parent->parent->color = Color::Red; 
                node = node->parent->parent; 
            }
        }
    }

    //ensure root is black
    root->color = Color::Black; 
    
}


RedBlackTree::Node* RedBlackTree::search(Node* node, int value) const
{
    if (node == NIL || node->value == value)
        return node;
        
    if (value < node->value)
        search(node->left, value); 
    search(node->right, value); 

}       


void RedBlackTree::remove(int value)
{
    Node* node = search(root, value);   //find the node to delete 
    if (node == NIL)
        return; 

    Node* y = node; //save the node that will be deleted 
    Color y_original_color = y->color; 
    Node* x;  // node x will be the node replacing y 

    //if a node has only one child , that child is the inorder successor 
    if (node->left == NIL) 
    {
        x = node->right;
        transplant(node, node->right);
    }
    else if (node->right == NIL) 
    {
        x = node->left;
        transplant(node, node->left);
    }
    else //if the target node has 2 children, we need to find the inorder successor 
    {// in a binary tree the inorder traversal , traverse the nodes in ascending order 
        y = minimum(node->right);  // find the inorder successor 
        //in this case we track the inorder successor since this willl be the node wchiihc will be phisically removed 
        // y always track node that are phisically removed not logically 
        y_original_color = y->color;
        x = y->right; // y is the left-most node so it will only have a right child at most 
        if (y->parent == node) 
        {
            x->parent = y; //set it again in case x was NIL 
        } 
        else 
        {
            transplant(y, y->right); //remove x from the old position 
            y->right = node->right;
            y->right->parent = y;
        }
        transplant(node, y); //transplant y into the new position 
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }
    if (y_original_color == Color::Black) //if the removed node was black 
        fix_delete(x); //check for a double black situation 
}

void RedBlackTree::transplant(Node* original, Node* replacement)
{
    if (original->parent == NIL)
        root = replacement; 

    else if (original == original->parent->left)
        original->parent->left = replacement; 
    else
        original->parent->right = replacement; 

    replacement->parent = original->parent; 

}


RedBlackTree::Node* RedBlackTree::minimum(Node* node)
{
    while(node->left != NIL)
        node = node->left; 

    return node; 
}



void RedBlackTree::fix_delete(Node* node)
{
    while(node != NIL && node->color == Color::Black)
    {
        if (node == node->parent->left)
        {
            Node* sibiling = node->parent->right; 
            if (sibiling->color == Color::Red)
            {
                sibiling->color = Color::Black; 
                node->parent->color = Color::Red;   
                rotate_left(node->parent); 
                sibiling = node->parent->right; //redefine the sibiling after the rotation

            }
            if (sibiling->color == Color::Black && sibiling->right->color == Color::Black)
            {
                sibiling->color = Color::Red; 
                node = node->parent; 
            }
            else // if the sibiling has a red child 
            {
                if (sibiling->right->color == Color::Black)
                {
                    //fix structure right right
                    sibiling->left->color = Color::Black; 
                    sibiling->color = Color::Red; 
                    rotate_right(sibiling); 
                    sibiling = node->parent->right;  //redefine sibiling after the rotation 
                }
                sibiling->color = node->parent->color; 
                node->parent->color = Color::Black; 
                sibiling->right->color = Color::Black;
                rotate_left(node->parent); 
                node = root;  
            }
        }
        else
        {
            Node* sibiling = node->parent->left; 
            if (sibiling->color == Color::Red)
            {
                sibiling->color = Color::Black; 
                node->parent->color = Color::Red; 
                rotate_right(sibiling); 
                sibiling = node->parent->left; 
            }
            else if (sibiling->left->color == Color::Black && sibiling->right->color == Color::Black)
            {
                sibiling->color = Color::Red; 
                node = node->parent; //check higher 
            }
            else 
            {
                if (sibiling->left->color == Color::Black)
                {
                    //impose structure left left
                    sibiling->left->color = Color::Black; 
                    sibiling->color = Color::Red; 
                    rotate_left(sibiling); 
                    sibiling = node->parent->left; 
                }
                sibiling->color = node->parent->color; 
                node->parent->color = Color::Black; 
                sibiling->left->color = Color::Black;
                rotate_right(node->parent); 
                node = root; 

            }
        }
    }

    node->color = Color::Black; 
}