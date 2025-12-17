#include <iostream>
#include <unordered_map>
#include <string>
#include <stack>
#include <utility> 
#include <string_view>
#include <unordered_set>

class CompressedTrie
{
    private:
        struct Node
        {
            Node* parent; 
            std::unordered_map<char, Node*> children; 
            // std::string_view characters; 
            std::string characters; 
            bool isEnd; 

            Node() : parent(nullptr), characters(""), isEnd(false) {}
            Node(Node* _parent, const std::string _characters, bool _isEnd = false) : parent(_parent), characters(std::move(_characters)), isEnd(_isEnd) {}
            // Node(Node* _parent, const std::string_view _characters, bool _isEnd = false) : parent(_parent), characters(_characters), isEnd(_isEnd) {}
        };
        Node* root; 
        int nWords; 
        std::unordered_set<std::string> pool; 
    
    public:
        CompressedTrie() : root(new Node()), nWords(0) {} 
        ~CompressedTrie(); 
        void insert(const std::string& word); 
        void print() const {printer(root, 0); } 



    protected:
        void clear(Node* node); 
        void printer(Node* node, int depth) const; 

}; 

CompressedTrie::~CompressedTrie()
{
    if (root != nullptr)
    {
        clear(root); 
    }
}

void CompressedTrie::clear(Node* node)
{
    std::stack<Node*> stack; 
    stack.push(node); 

    while (!stack.empty())
    {
        Node* current_node = stack.top(); 
        stack.pop(); 

        for (auto pair : current_node->children)
        {
            stack.push(pair.second); 
        }
        delete current_node; 
    }
    
    root = nullptr;     
    nWords = 0; 
}

void CompressedTrie::insert(const std::string& word)
{   
    if (word.empty())
        return; 

    Node* current = root; 
    size_t pos = 0; //position of the word we are considering 

    while(pos < word.length())
    {
        char currentChar = word[pos]; 
        auto it = current->children.find(currentChar); //keep as dictionary key the initial letter of the string 
        
        if (it == current->children.end()) //if the curret substrig doesnt match any child 
        {
            Node* new_node = new Node(current, word.substr(pos), true); 
            current->children[currentChar] = new_node; 
            ++nWords; 
            return; 
        }

        //found a matching child 
        Node* child = it->second; 
        std::string& characters = child->characters; 
        // std::string_view characters = child->characters;


        //find longest common prefix
        size_t i = 0; 
        while(i < characters.length() && (pos + i ) < word.length() && characters[i] == word[pos + i])
            ++i; 
        
        if (i == characters.length()) //full string match 
        {
            current = child; 
            pos += i; 
        }
        else
        {
            //partial match 
            std::string commonPrefix = characters.substr(0, i);
            std::string remainingExisting = characters.substr(i);
            std::string remainingNew = word.substr(pos + i);

            // std::string_view label = std::string_view(characters);                       
            // std::string_view commonPrefix = label.substr(0, i);                     
            // std::string_view remainingExisting = label.substr(i);                   
            // std::string_view remainingNew = std::string_view(word).substr(pos + i);


            child->characters = commonPrefix; //update the child node to contain only the partial match

            if (!remainingExisting.empty())
            {
                Node* splitNode = new Node(child, remainingExisting, child->isEnd); 
                splitNode->children = std::move(child->children); //transfer children  (std::move cast to an rvalue reference)
                child->children[remainingExisting[0]] = splitNode;
                child->isEnd = false; 
                
                //update childrens' parent 
                for (auto& pair : splitNode->children)
                    pair.second->parent = splitNode; 
            }
            if (!remainingNew.empty())
            {
                Node* newNode = new Node(child, remainingNew, true);
                child->children[remainingNew[0]] = newNode; 
                ++nWords; 
            }
            else
            {
                child->isEnd = true; 
                ++nWords; 
            }
        }

    }
   return; 
}


void CompressedTrie::printer(Node* node, int depth) const
{
    if (node == nullptr)
        return; 

    for (int i = 0; i < depth; ++i)
    {
        std::cout << " " ; 
    }
    std::cout << node->characters; 
    if (node->isEnd)
        std::cout << "*\n"; 
    else
        std::cout << "\n"; 
    
    for (auto pair : node->children)
    {
        printer(pair.second, depth + node->characters.length() ); 
    }
}