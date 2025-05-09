#pragma once 

#include <list>
#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>

class Graph
{
    private:
        struct Edge; //forward declaration

        struct Node
        {
            std::string id ; //node id 
            // std::string operator*() const {return id; }
            std::list <std::shared_ptr <Edge> > incidentEdges; //adjency list for each node 
            Node(const std::string _id ) : id(_id) {}
        };
        

        struct Edge
        {
            std::shared_ptr<Node> source; 
            std::shared_ptr<Node> destination; 
            int weigth; 

            //position in incidentEdges 
            std::list <std::shared_ptr <Edge> >::iterator sourcePos;
            std::list <std::shared_ptr <Edge> >::iterator destPos;

            Edge(std::shared_ptr<Node> _source, std::shared_ptr<Node> _destination, int _weight) : source(_source), destination(_destination), weigth(_weight) {}
        };
        

        std::unordered_map<std::string, std::shared_ptr<Node> > nodes ; //all the nodes in the graph 

    public:
        Graph() {}
        std::shared_ptr<Node> addNode(const std::string& id); //insert a new node 
        std::shared_ptr<Edge> addEdge(const std::string& source, const std::string& destination, int weight); //insert an edge 
        std::unordered_map<std::string, std::shared_ptr<Node> > getNodes() {return nodes;}


}; 


std::shared_ptr<Graph::Node> Graph::addNode(const std::string& id )
{
    if (nodes.find(id) != nodes.end())
        throw std::runtime_error("Node already existing"); 

    auto node = std::make_shared<Node> (id); 
    nodes[id] = node;  //insert node in the nodes hash map 

    return node; 
}   

std::shared_ptr<Graph::Edge> Graph::addEdge(const std::string& sourceId, const std::string& destinationId, int weight )
{
    auto sourcePos = nodes.find(sourceId); 
    auto destPos = nodes.find(destinationId); 

    if (sourcePos== nodes.end() || destPos == nodes.end())
        throw std::runtime_error("source node or destination node not fund"); 

    auto edge = std::make_shared<Edge>(sourcePos->second, destPos->second, weight);

    sourcePos->second->incidentEdges.push_front(edge); //add edge in the adjency list of the node
    edge->sourcePos = sourcePos->second->incidentEdges.begin(); 
    
    // destPos->second->incidentEdges.push_front(edge);
    // edge->destPos = destPos->second->incidentEdges.begin(); 

    return edge; 
}