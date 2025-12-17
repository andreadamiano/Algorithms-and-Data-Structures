#include "graph.h"
#include <iostream>
#include <queue>
#include <memory>
#include <map>
#include <set>
#include "partition2.h"
#include <string>

class Comparator
{
    public:
        bool operator() (std::shared_ptr<Graph::Edge> left, std::shared_ptr<Graph::Edge> right )
        {
            return  left->weigth > right->weigth;  
        }
}; 

std::list<std::shared_ptr<Graph::Edge>> Kruskal(Graph& graph)
{
   Partition<std::string> clusters; 
   std::priority_queue<std::shared_ptr<Graph::Edge>, std::vector<std::shared_ptr<Graph::Edge>>, Comparator> heap;
   std::list<std::shared_ptr<Graph::Edge>> MST; //edges of the minimum spanning tree 

    //each node is part of a single element cluster 
    for (auto node : graph.getNodes())
        clusters.makeSet(node->id);

    for (auto edge : graph.getEdges())
        heap.push(edge); 
    

    while (MST.size() < graph.getNodes().size() -1 )
    {
        auto edge = heap.top(); 
        heap.pop(); 

        auto cluster_source = clusters.find(edge->source->id); 
        auto cluster_destination = clusters.find(edge->destination->id);

        // If source and destination are in different clusters
        if (cluster_source != cluster_destination) 
        {
            MST.push_back(edge); 
            clusters.Union(cluster_source , cluster_destination); //unify the 2 clusters 
        }
    }

    return MST; 
}


int main ()
{
    Graph graph; 

    auto nodeSFO = graph.addNode("SFO");
    auto nodeLAX = graph.addNode("LAX");
    auto nodeDFW = graph.addNode("DFW");
    auto nodeORD = graph.addNode("ORD");
    auto nodeJFK = graph.addNode("JFK");
    auto nodeBOS = graph.addNode("BOS");
    auto nodePVD = graph.addNode("PVD");
    auto nodeBWI = graph.addNode("BWI");
    auto nodeMIA = graph.addNode("MIA");

    // add edges
    graph.addEdge(nodeSFO, nodeLAX, 337);
    graph.addEdge(nodeSFO, nodeORD, 1846);
    graph.addEdge(nodeSFO, nodeDFW, 1464);
    graph.addEdge(nodeLAX, nodeMIA, 2342);
    graph.addEdge(nodeLAX, nodeDFW, 1235);
    graph.addEdge(nodeDFW, nodeORD, 802);
    graph.addEdge(nodeDFW, nodeJFK, 1391);
    graph.addEdge(nodeDFW, nodeMIA, 1121);
    graph.addEdge(nodeORD, nodeBOS, 867);
    graph.addEdge(nodeORD, nodePVD, 849);
    graph.addEdge(nodeORD, nodeJFK, 740);
    graph.addEdge(nodeJFK, nodeBOS, 187);
    graph.addEdge(nodeJFK, nodePVD, 144);
    graph.addEdge(nodeJFK, nodeBWI, 184);
    graph.addEdge(nodeJFK, nodeMIA, 1090);
    graph.addEdge(nodeBWI, nodeMIA, 946);
    graph.addEdge(nodeMIA, nodeBOS, 1258);
    graph.addEdge(nodeORD, nodePVD, 849);
    graph.addEdge(nodeSFO, nodeBOS, 2704);
    graph.addEdge(nodeORD, nodeBWI, 621);


    std::list<std::shared_ptr<Graph::Edge>> edges = Kruskal(graph); 


    for (auto edge : edges)
    {
        std::cout  << "Edge: " << edge->source->id << "->" << edge->destination->id << "\n"; 
    }
}