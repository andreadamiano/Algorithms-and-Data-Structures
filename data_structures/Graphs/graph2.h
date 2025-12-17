#pragma once 

#include <list>
#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>
#include <map>
#include <vector>
#include <Eigen/Dense>
#include <iostream>

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
            std::list <std::shared_ptr <Node> >::iterator position; 
            int index;              

            Decorator<bool>  decorator; 
            std::string operator*() const {return id; }
            // bool isAdjentTo(Node& other) const; 
            Node(const std::string _id ) : id(_id) {}
        };
        

        struct Edge
        {
            std::shared_ptr<Node> source; 
            std::shared_ptr<Node> destination; 
            std::list<std::shared_ptr<Edge> > ::iterator position;


            int weigth; 

            // bool opposite(Node& end) const; 
            // std::list<Node> endVertices() const; 
            // bool isAdjentTo(Edge& other) const; 
            // bool isIncidentOn(Node& node) const;  

            Edge(std::shared_ptr<Node> _source, std::shared_ptr<Node> _destination, int _weight) : source(_source), destination(_destination), weigth(_weight) {}
        };
        

        std::list<std::shared_ptr<Node> > nodes ; 
        std::list<std::shared_ptr<Edge>> edges; 
        Eigen::MatrixXd matrix; 
        int nodeCount =0; 

    public:
        Graph() {}
        std::shared_ptr<Node> addNode(const std::string& id); //insert a new node 
        std::shared_ptr<Edge> addEdge(const std::shared_ptr<Node>& source, const std::shared_ptr<Node>& destination, int weight); //insert an edge 
        // std::unordered_map<std::string, std::shared_ptr<Node> > getNodes() {return nodes;}


        // std::vector<std::string> DFS(const std::string& startId) ; //depth first traversal from a given node 

        void print() {std::cout << matrix; }
        auto getNodes() { return nodes; }
        auto getEdges() { return edges; }


    // protected:
        // void DFSVisit(std::shared_ptr<Node> node, std::vector<std::string>& visitedNodes); //helper function for the dft algorithm




}; 


std::shared_ptr<Graph::Node> Graph::addNode(const std::string& id )
{    
    auto node = std::make_shared<Node> (id); 
    nodes.push_back(node);  
    node->position = std::prev(nodes.end()); 
    node->index = nodeCount++; 

    //resize matrix 
    Eigen::MatrixXd newMatrix = Eigen::MatrixXd::Zero(nodeCount, nodeCount); 

    newMatrix.block(0, 0, nodeCount-1, nodeCount-1) = matrix; 
    matrix = newMatrix; 

    return node; 
}   

std::shared_ptr<Graph::Edge> Graph::addEdge(const std::shared_ptr<Graph::Node>& source, const std::shared_ptr<Graph::Node>& destination, int weight )
{

    //create an edge object 
    auto edge = std::make_shared<Edge> (source, destination, weight);
    edges.push_back(edge); 
    edge->position = std::prev(edges.end()); 
    
    matrix(source->index, destination->index) = edge->weigth;  

    return edge; 
}
