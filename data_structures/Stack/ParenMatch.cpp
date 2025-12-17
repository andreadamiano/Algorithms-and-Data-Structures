#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <fstream>
#include <sstream>
// #include "LinkedStack.h"
#include "ArrayStack.h"

// template<typename E>
bool ParenMatch(std::vector<char> array)
{
    ArrayStack<char> stack(array.size()); 
    for(int i=0; i<array.size(); i++)
    {
        if (array[i] == '('  || array[i] == '[' || array[i] == '{' )
        {   
            stack.push(array[i]); 
        }
        else if (array[i] == ')'  || array[i] == ']' || array[i] == '}' )
        {
            if(stack.empty())
                return false; 

            char top = stack.top(); //get top element of the stack
            if ((array[i] == ')' && top != '(') || 
                (array[i] == ']' && top != '[') || 
                (array[i] == '}' && top != '{'))
            {
                return false; 
            }
            stack.pop(); 
            
        }
            
    }
    if (stack.empty())
            return true; //every symbol got matched 
    else
        return false; //symbol not matched
}


std::vector<std::string> getHtmlTags()
{
    std::vector<std::string> tags; //a vector of strings (containing HTML tags)

    std::ifstream file ("file.html"); //open the HTML file 
    if (file)
        std::cout << "file opened" << "\n";

    //read the file all at once
    // std::stringstream buffer;
    // buffer << file.rdbuf();
    // std::cout << buffer.str();   

    std::string line; 
    while(std::getline(file, line))
    {
        // std::cout << line << "\n";
        int pos =0; //current position in the line 
        int ts = line.find("<", pos); // search for the first "<" starting from pos = 0, return the position
        while (ts != std::string::npos)
        {
            int te = line.find(">", ts +1); 
            tags.push_back(line.substr(ts, te-ts+1)); 
            pos = te +1; 
            ts = line.find("<", pos); //search for other tags in ln the line
        }

    }

    return tags; 
}


bool isHtmlMatched(std::vector<std::string> tags)
{
    ArrayStack<std::string> stack(tags.size()); 
    using Iter = std::vector<std::string>::const_iterator; //define an iterator to loop through the array 
    for (Iter p = tags.begin(); p != tags.end(); ++p)
    {
        if(p->at(1) != '/') //check first element of the string (if it's not the closing tag)
        stack.push(*p); 
        else
        {
            if (stack.empty()) //nothing to compare the closing tag to 
                return false; 

            //define corresponding opening and closing tag
            std::string open = stack.top().substr(1); //excluding <
            std::string close = p->substr(2); //excluding "<\"

            if (open.compare(close) != 0)
                return false; 
            
            else
                stack.pop(); 
        }
    }
    if (stack.empty())
        return true; 
    
    else    
        return false; 
}


int main ()
{
    // std::string expression ("(1+2)");
    // std::vector<char> array_expression (expression.begin(), expression.end()); 

    // std::cout << ParenMatch(array_expression);
    
    std::vector<std::string> tags; 
    tags = getHtmlTags(); 

    //visualize 
    // for (std::string& tag : tags)
    //     std::cout << tag << "\n"; 

    //check if the tags match 

    if(isHtmlMatched(tags))
        std::cout << "The input file is a matched HTML document."  << std::endl; 
    else    
        std::cout <<  "The input file is not a matched HTML document." << std::endl; 
    
}