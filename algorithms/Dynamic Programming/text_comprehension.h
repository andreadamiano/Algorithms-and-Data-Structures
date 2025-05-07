    #pragma once 

    #include <iostream>
    #include <vector>
    #include <string>
    #include <queue>
    #include <unordered_map>
    #include <memory>
    #include <bitset>

    //Huffman encoding 
    class Compression
    {
        private :
            struct Node
            {
                int frequency; 
                char character; 
                Node* left; 
                Node* right; 

                Node(const int _frequency, const char _character) : frequency(_frequency), character(_character), left(nullptr), right(nullptr) {}
                Node(Node* _left, Node* _right, const int _frequency) : left(_left), right(_right), frequency(_frequency) {}
            }; 

            class Comparator
            {
                public:
                    bool operator() (const Node* first , const Node* second)
                    {
                        return first->frequency > second->frequency;
                    }
            };

            std::priority_queue<Node*, std::vector<Node*>, Comparator> pq;   
            Node* root; 
            std::unordered_map<char, std::string> codes; 
            std::string text; 


        public:
            Compression(const std::string& text); 
            ~Compression();

        protected:
            void Huffman(const std::string& text);
            void generateCodes(Node* node, std::string&& code);  
            void Encode(); 
            void clear(Node* node); 
    }; 




    Compression::Compression(const std::string& text) : text(text)
    {   
        Huffman(text); 
        generateCodes(root, ""); 

        for (auto it = codes.begin(); it != codes.end(); ++it)
        {
            std::cout << "char: " << it->first << " code: " << it->second <<"\n"; 
        }
        Encode(); 
    }   

    Compression::~Compression()
    {
        clear(root);
    }

    void Compression::clear(Node* node)
    {
        if(node)
        {
            clear(node->left); 
            clear(node->right); 

            delete(node); 
        }
    }

void Compression::Huffman(const std::string& text)
{
    //compute frequencies 
    std::unordered_map<char, int> freqMap; 

    //compute frequencies and store in a hash map 
    for (const char& ch: text)
    {
        freqMap[ch] ++;  
    }

    //order them using a priority queue (from less frequent to more frequent)
    for (const auto& pair : freqMap)
    { 
        pq.push(new Node(pair.second, pair.first)); 
    }


    //construct binary tree 
    while (pq.size() > 1)
    {
        Node* left = pq.top(); 
        pq.pop(); 

        Node* right = pq.top(); 
        pq.pop(); 

        Node* parent = new Node(left, right, left->frequency+right->frequency); 
        pq.push(parent); 
    }   

    //store root node 
    if (!pq.empty())
    {
        root = pq.top(); 
        pq.pop();
    }
    
}


void Compression::generateCodes(Node* node, std::string&& code)
{
    //leaf nodes 
    if(node->left == nullptr && node->right == nullptr)
        codes[node->character] = code; 

    if(node->left)
        generateCodes(node->left, code +"0");
        
    if (node->right)
        generateCodes(node->right, code + "1"); 
}


void Compression::Encode()
{
    if (codes.empty())
        return; 


    std::cout << "Encoded text:\n"; 
    for(char& ch: text)
    {
        std::cout << codes[ch]; 
    }

    std::cout << "\nBinary text:\n";  
    for(char& ch: text)
    {
        std::bitset<8> bits(ch);
        std::cout << bits; 
    }
}