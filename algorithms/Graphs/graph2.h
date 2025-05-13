#pragma once 


#include <unordered_map>
#include <list>
#include <stdexcept>
#include <memory>
#include <vector>
#include <iostream>


class Graph2
{
    private:
        struct Node
        {
            std::string id; 
            Node(const std::string& _id) : id (_id) {}
        }; 

        std::unordered_map<std::string, std::shared_ptr<Node> > nodes; //all the nodes in the graph 
        std::unordered_map<std::string, size_t > idToIndex; //maps node id to matrix index 
        std::vector< std::vector<int> > adjencyMatrix; 
        size_t nextIndex =0; //index corresponding to the inserted node id 
        
    
    public:
        Graph2() {}
        std::shared_ptr<Node> addNode(const std::string& id);
        void addEdge(const std::string& source, const std::string& destination);  
        void print() const ; 
}; 

void Graph2::print() const 
{
    for (int i =0; i< nextIndex; ++i)
    {
        for (int j=0; j<nextIndex; ++j)
            std::cout << adjencyMatrix[i][j] <<" "; 

        std::cout << "\n"; 
    }

}


std::shared_ptr<Graph2::Node> Graph2::addNode(const std::string& id)
{
    if(nodes.find(id) != nodes.end())
        throw std::runtime_error("node already exists"); 

    auto node = std::make_shared<Node> (id); 
    nodes[id] = node; //add node to the hash map 
    idToIndex[id] = nextIndex ++; 

    //resize adjency matrix 
    for (auto& row : adjencyMatrix)
    {
        row.resize(nextIndex, 0); //resize row and assign defualt value 0 (creating new columns)
    }
    adjencyMatrix.resize(nextIndex, std::vector<int>(nextIndex, 0)); //resize columns (creating new row vectors)

    return node; 
}


void Graph2::addEdge(const std::string& source, const std::string& destination)
{
    auto sourceId = idToIndex.find(source); 
    auto destinatioId = idToIndex.find(destination); 

    if (sourceId == idToIndex.end() || destinatioId == idToIndex.end())
        throw("error, either the soruce or the destination node doesnt exist");

    //add edge 
    adjencyMatrix[sourceId->second] [destinatioId->second] = 1; 
}