#pragma once 

#include <list>
#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>
#include <map>
#include <vector>

template <typename T>
class Decorator
{
    private:
        std::map<std::string, T> map; //discovery map 

    public:
        T get(const std::string id) //get value of attribute
        {
            return map[id]; 
        } 

        void set(const std::string id ,  const T& value) //set value
        {
            map[id] = value; 
        } 

        bool contains(const std::string& id)
        {
            return map.find(id) != map.end(); 
        }

}; 

class Graph
{
    private:
        struct Edge; //forward declaration

        struct Node
        {
            std::string id ; //node id 
            // std::string operator*() const {return id; }
            std::list <std::shared_ptr <Edge> > incidentEdges; //adjency list for each node 
            Decorator<bool>  decorator; 
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


        std::vector<std::string> DFS(const std::string& startId) ; //depth first traversal from a given node 

    protected:
        void DFSVisit(std::shared_ptr<Node> node, std::vector<std::string>& visitedNodes); //helper function for the dft algorithm




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

    auto edge1 = std::make_shared<Edge>(sourcePos->second, destPos->second, weight);
    auto edge2 = std::make_shared<Edge>(destPos->second, sourcePos->second, weight);


    // Add A→B to A's adjacency list
    sourcePos->second->incidentEdges.push_front(edge1);
    edge1->sourcePos = sourcePos->second->incidentEdges.begin();

    // Add B→A to B's adjacency list
    destPos->second->incidentEdges.push_front(edge2);
    edge2->sourcePos = destPos->second->incidentEdges.begin();

    return edge1; 
}

std::vector<std::string> Graph::DFS(const std::string& startId)
{
    //check if start node exists
    if (nodes.find(startId) == nodes.end())
        throw("error , start node doesnt exist"); 

    //initialize decorators 
    for (auto& pair: nodes)
        pair.second->decorator.set("visited", false); 

    
    std::vector<std::string> visitedNodes; 
    visitedNodes.reserve(nodes.size()); 

    DFSVisit(nodes[startId], visitedNodes); 

    return visitedNodes; 
}


void Graph::DFSVisit(std::shared_ptr<Node> node, std::vector<std::string>& visitedNodes)
{
    //mark node as visited 
    node->decorator.set("visited", true); 
    visitedNodes.push_back(node->id); 

    for (auto& edge : node->incidentEdges)
    {
        auto neighbor = edge->destination; 
        
        if (!neighbor->decorator.get("visited")) //if node was not visited 
            DFSVisit(neighbor, visitedNodes); 
    }
}