#include <iostream>
#include "graph.h"
#include <stack>
#include <vector>
#include <functional>

void topologicSort(Graph& graph)
{
    std::stack<std::shared_ptr<Graph::Node> >stack ; 
    int index = 1; 
    
    for(auto& node : graph.getNodes())
    {
        if (node->inDegree == 0)
            stack.push(node);  //push all nodes with in-degree = 0
    }

    while(!stack.empty())
    {
        auto currentNode = stack.top(); 
        currentNode->order = index++;    
        stack.pop(); 

        for (auto edge : currentNode->incidentEdges)
        {
            auto nextNode = edge->opposite(*currentNode); 
            if (--nextNode->inDegree == 0)
                stack.push(nextNode);    
        }
    }
}   

int main (int args, char* argv[])
{
    //DAG 
    Graph graph; 

    auto nodeA = graph.addNode("A");
    auto nodeB = graph.addNode("B");
    auto nodeC = graph.addNode("C");
    auto nodeD = graph.addNode("D");
    auto nodeE = graph.addNode("E");
    auto nodeF = graph.addNode("F");
    auto nodeG = graph.addNode("G");
    auto nodeH = graph.addNode("H");
    auto nodeI = graph.addNode("I");

    graph.addDirectedEdge(nodeA, nodeC, 0);
    graph.addDirectedEdge(nodeA, nodeD, 0);
    graph.addDirectedEdge(nodeB, nodeD, 0);
    graph.addDirectedEdge(nodeB, nodeF, 0);
    graph.addDirectedEdge(nodeC, nodeE, 0);
    graph.addDirectedEdge(nodeC, nodeD, 0);
    graph.addDirectedEdge(nodeC, nodeH, 0);
    graph.addDirectedEdge(nodeD, nodeF, 0);
    graph.addDirectedEdge(nodeE, nodeG, 0);
    graph.addDirectedEdge(nodeF, nodeG, 0);
    graph.addDirectedEdge(nodeF, nodeI, 0);
    graph.addDirectedEdge(nodeG, nodeI, 0);
    graph.addDirectedEdge(nodeH, nodeI, 0);

    //see nodes adjency list 
    // for (auto& node : graph.getNodes())
    // {
    //     std::cout << "Node " << node->id << "\n"; 

    //     for(auto& edge : node->incidentEdges)
    //     {
    //         std::cout << "   " << edge->opposite(*node).id << " weight " << edge->weigth << "\n"; 
    //     }
    // }

    for (auto& node : graph.getNodes())
    {
        std::cout << "Node " << node->id << " in-degree " << node->inDegree << "\n"; 

        for(auto& edge : node->incidentEdges)
        {
            std::cout << "   " << edge->opposite(*node)->id << " in-degree " << edge->opposite(*node)->inDegree << "\n"; 
        }
    }
    
    std::cout << "\nTopological sort\n"; 
    topologicSort(graph); 
    for (auto& node : graph.getNodes())
    {
        std::cout << "Node " << node->id << " order " << node->order << "\n"; 
    }
}