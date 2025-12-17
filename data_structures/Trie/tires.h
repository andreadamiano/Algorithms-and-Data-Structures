#pragma once 

#include <stack>
#include <unordered_map>
#include <string>
#include <iostream>

class StandardTries
{
    private:
        struct Node
        {
            Node* parent;   
            std::unordered_map<char, Node*> children; 
            char letter; 
            bool isEnd; 

            Node(Node* _parent, char _letter = '\0', bool _isEnd = false) : parent(_parent), letter(_letter), isEnd(_isEnd) {}
            Node() : parent(nullptr), letter('\0'), isEnd(false) {}
        };
        Node* root; 
        int nWords; //n of nodes in the trie

    public:
        
        Node* Root() const {return root; }

        StandardTries() : root(new Node()), nWords(0) {}
        ~StandardTries() {clear(); } 

        bool empty()const {return nWords==0; } 
        void insert(const std::string& word) ; 
        void print() const {printer(root, 0); } 


    protected:
        void clear(); 
        void printer(Node* node, int depth) const; 
        
}; 

void StandardTries::clear()
{
    if(root == nullptr)
        return; 

    std::stack<Node*> nodes; 
    nodes.push(root); 

    while (!nodes.empty())
    {
        Node* current = nodes.top(); 
        nodes.pop(); 

        for (auto pair : current->children)
        {
            nodes.push(pair.second); 
        }
        delete current; 
    }

    root = nullptr; 
    nWords=0; 
}


void StandardTries::insert(const std::string& word)
{
    Node* current = root; 

    for (const char& ch : word)
    {
        if(current->children.find(ch) == current->children.end()) //if not found
        {
            current->children[ch] = new Node(current, ch); //insert new letter in the tree  
        }
        
        current = current->children.find(ch)->second; //go to the next node 

    }
    
    if(!current->isEnd)
    {
        current->isEnd = true; 
        ++nWords;  //count only words 
    }
    
}

// void StandardTries::printer(Node* node, int depth) const 
// {
//     if(node == nullptr)
//         return; 
//     for (int i =0; i<depth; ++i)
//         std::cout << "   "; 
    
//     std::cout << node->letter <<"\n"; 

//     for (auto pair : node->children)
//     {
//         printer(pair.second, depth++);
//     }

// }


void StandardTries::printer(Node* node, int depth) const 
{
    if(node == nullptr)
        return;
        
    //skip epty characters
    if(node != root) {
        for (int i = 0; i < depth-1; ++i)
            std::cout << "   "; 
        
        std::cout << node->letter;
        if(node->isEnd) std::cout << " *"; //mark end of words
        std::cout << "\n"; 
    }

    for (auto& pair : node->children)
    {
        printer(pair.second, depth + 1); 
    }
}