#pragma once 

#include <list>
#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>
#include <map>
#include <vector>

class Object 
{
    public:
        virtual ~Object() {}
}; 

class Integer : public Object
{
    private:
        uint32_t value; 
    
    public:
        Integer(uint32_t _value = 0) : value(_value) {}
        uint32_t getValue() const {return value; }
}; 

class Float : public Object
{
    private:
        double value; 
    
    public:
        Float(double _value = 0) : value(_value) {}
        double getValue() const {return value; }
};

class String : public Object
{
    private:
        std::string value; 
    
    public:
        String(std::string& _value) : value(_value) {}
        std::string& getValue() {return value; }
}; 

class Bool : public Object
{
    private:
        bool value; 
    
    public:
        Bool(int _value = 0) : value(_value) {}
        bool getValue() const {return value; }
};

class Decorator 
{
    private:
        std::map<std::string, std::shared_ptr<Object> > map; //discovery map 

    public:
        std::shared_ptr<Object> get(const std::string& id) //get value of attribute
        {
            return map[id]; 
        } 

        void set(const std::string& id ,  std::shared_ptr<Object> value) //set value
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
    public:
        struct Edge; //forward declaration

        struct Node
        {
            std::string id ; //node id 
            std::list <std::shared_ptr <Node> >::iterator position; 
            std::list<std::shared_ptr<Edge> > incidentEdges;     
            int order=0;        
            int inDegree =0;  
            int latitude;
            int longitute; 
            Decorator decorator; 
            std::string operator*() const {return id; }
            Node(const std::string& _id , int _latitude, int _longitute) : id(_id), longitute(_longitute), latitude(_latitude) {}

            bool operator== (Graph::Node& other)
            {
                return this == &other; 
            }
        };
        

        struct Edge
        {
            std::shared_ptr<Node> source; 
            std::shared_ptr<Node> destination; 
            std::list<std::shared_ptr<Edge> > ::iterator position;
            std::list<std::shared_ptr<Edge> > ::iterator incidencePosition;
            int weigth; 
            // Decorator<bool> decorator;  
            Decorator decorator; 
            bool directed; 

            std::shared_ptr<Node> opposite(Node& node) const {
                if (node.id == source->id)
                    return destination;
                else
                    return source;
            }
            Edge(std::shared_ptr<Node> _source, std::shared_ptr<Node> _destination, int _weight) : source(_source), destination(_destination), weigth(_weight) {}
        };
        

        std::list<std::shared_ptr<Node> > nodes ; 
        std::list<std::shared_ptr<Edge>> edges; 

    public:
        Graph() {}
        std::shared_ptr<Node> addNode(const std::string& id, int latitude = 0, int longitute = 0); //insert a new node 
        std::shared_ptr<Edge> addEdge(const std::shared_ptr<Node>& source, const std::shared_ptr<Node>& destination, int weight); //insert an edge 
        void initialize(); 
        std::shared_ptr<Edge> addDirectedEdge(const std::shared_ptr<Node>& source, const std::shared_ptr<Node>& destination, int weight); 

        auto getNodes() { return nodes; }
        auto getEdges() { return edges; }

}; 

void Graph::initialize()
{
    for (auto& node : nodes)
        node->decorator.set("visited", std::make_shared<Bool> (false));

    for (auto& edge : edges)
        edge->decorator.set("visited",  std::make_shared<Bool> (false));  
}

std::shared_ptr<Graph::Node> Graph::addNode(const std::string& id , int latitude, int longitute)
{    
    auto node = std::make_shared<Node> (id, latitude, longitute); 
    nodes.push_back(node);  
    node->position = std::prev(nodes.end()); 
    node->decorator.set("visited",  std::make_shared<Bool> (false)); 

    return node; 
}   

std::shared_ptr<Graph::Edge> Graph::addEdge(const std::shared_ptr<Graph::Node>& source, const std::shared_ptr<Graph::Node>& destination, int weight )
{
    auto edge = std::make_shared<Edge> (source, destination, weight);
    edges.push_back(edge); 
    edge->position = std::prev(edges.end()); 
    source->incidentEdges.push_back(edge); 
    destination->incidentEdges.push_back(edge); 
    edge->incidencePosition = std::prev(source->incidentEdges.end()); 
    edge->decorator.set("visited",  std::make_shared<Bool> (false)); 
    edge->directed = false; 
    return edge; 
}


std::shared_ptr<Graph::Edge> Graph::addDirectedEdge(const std::shared_ptr<Graph::Node>& source, const std::shared_ptr<Graph::Node>& destination, int weight)
{
    auto edge = std::make_shared<Edge> (source, destination, weight);
    edges.push_back(edge); 
    edge->position = std::prev(edges.end()); 
    source->incidentEdges.push_back(edge); 
    edge->incidencePosition = std::prev(source->incidentEdges.end()); 
    edge->decorator.set("visited",  std::make_shared<Bool> (false)); 
    edge->directed = true; 
    destination->inDegree++; 
    return edge; 
}
