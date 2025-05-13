#include "graph.h"
#include "graph2.h"
#include <iostream>


int main ()
{
    // Graph graph; 

    // //add nodes
    // auto nodeA = graph.addNode("A");
    // auto nodeB = graph.addNode("B");
    // graph.addNode("C");
    // graph.addNode("D");

    // //add edges 
    // graph.addEdge("A", "B", 10); 
    // graph.addEdge("A", "C", 5);
    // graph.addEdge("B", "D", 7);

    // //see nodes adjency list 
    // for (const auto& [id, node] : graph.getNodes())
    // {
    //     std::cout << "Node " << id << "\n"; 

    //     for(const auto& edge : node->incidentEdges)
    //     {
    //         std::cout << "   " << edge->destination->id << " weight " << edge->weigth << "\n"; 
    //     }
    // }


    Graph2 graph; 

    //add nodes 
    graph.addNode("A");
    graph.addNode("B");
    graph.addNode("C");
    graph.addNode("D");
     
    //add edges 
    graph.addEdge("A", "B"); 
    graph.addEdge("B", "C"); 

    //visualize 
    graph.print(); 
}