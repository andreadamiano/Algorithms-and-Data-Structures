#include "graph.h"
#include <iostream>

int main ()
{
    Graph graph;

    //add nodes 
    graph.addNode("A");
    graph.addNode("B");
    graph.addNode("C");
    graph.addNode("D");
    graph.addNode("E");
    graph.addNode("F");
    graph.addNode("G");

    //add edges
    graph.addEdge("A", "B", 1);
    graph.addEdge("A", "C", 1);
    graph.addEdge("B", "D", 1);
    graph.addEdge("C", "E", 1);
    graph.addEdge("D", "F", 1);
    graph.addEdge("E", "F", 1);
    graph.addEdge("F", "G", 1);

    //visualize 
    // for (const auto& [id, node] : graph.getNodes())
    // {
    //     std::cout << "Node " << id << ":\n"; 

    //     for(const auto& edge : node->incidentEdges)
    //     {
    //         std::cout << "   " << edge->destination->id << "\n"; 
    //     }
    // }

    //perform DSF 
    auto visitedNodes = graph.DFS("A"); 

    for (const auto& node: visitedNodes)
        std::cout << node << " "; 

}