#include "graph.h"
// #include "graph2.h"
#include <iostream>
#include <queue>

void DFS(Graph& graph, std::shared_ptr<Graph::Node>& node)
{
    //depth first search
    node->decorator.set("visited",  std::make_shared<Bool> (true)); 
    std::cout << node->id + "\n"; 
    for (auto& edge : node->incidentEdges)
    {
        if (!std::dynamic_pointer_cast<Bool>( edge->decorator.get("visited"))->getValue() )
        {
            auto nextNode = edge->opposite(*node); 
            if (! std::dynamic_pointer_cast<Bool>(nextNode->decorator.get("visited"))->getValue())
            {
                edge->decorator.set("visited",  std::make_shared<Bool> (true)); 
                DFS(graph, nextNode); 
            }
            else
                edge->decorator.set("visited",  std::make_shared<Bool> (true)); 
        }
    }
    
}

void BFS(std::shared_ptr<Graph::Node>& node)
{
    std::queue<std::shared_ptr<Graph::Node> > queue; 
    node->decorator.set("visited", std::make_shared<Bool> (true)); 
    node->decorator.set("level", std::make_shared<Integer> (0)); //set initial level 
    queue.push(node); 

    while(!queue.empty())
    {
        //get next potential node 
        auto currentNode = queue.front(); 
        auto currentLevel = std::dynamic_pointer_cast<Integer> (currentNode->decorator.get("level"))->getValue(); //get current level 
        queue.pop(); 
        std::cout << currentNode->id + "\n"; 

        for (auto& edge : currentNode->incidentEdges)
        {
            if (! std::dynamic_pointer_cast<Bool>(edge->decorator.get("visited"))->getValue())
            {
                auto nextNode = edge->opposite(*currentNode); 

                if (! std::dynamic_pointer_cast<Bool>(nextNode->decorator.get("visited"))->getValue())
                {
                    nextNode->decorator.set("visited", std::make_shared<Bool> (true)); 
                    nextNode->decorator.set("level", std::make_shared<Integer>(currentLevel +1)); //increase level counter 
                    edge->decorator.set("visited", std::make_shared<Bool> (true)); 
                    queue.push(nextNode); 
                }

                else    
                    edge->decorator.set("visited", std::make_shared<Bool> (true)); 

            }
        }

    }
}



int main ()
{
    Graph graph; 

    //add nodes
    // auto nodeA = graph.addNode("A");
    // auto nodeB = graph.addNode("B");
    // auto nodeC = graph.addNode("C");
    // auto nodeD = graph.addNode("D");
    // auto nodeE = graph.addNode("E");
    // auto nodeF = graph.addNode("F");


    //add edges 
    // graph.addEdge(nodeA, nodeB, 10); 
    // graph.addEdge(nodeA, nodeC, 5);
    // graph.addEdge(nodeB, nodeD, 7);
    // graph.addEdge(nodeC, nodeE, 2);
    // graph.addEdge(nodeC, nodeF, 8);
    // graph.addEdge(nodeC, nodeB, 1);

    //corresponding directed graph 
    auto nodeSFO = graph.addNode("SFO");
    auto nodeQRD = graph.addNode("QRD");
    auto nodeBOS = graph.addNode("BOS");
    auto nodeJFK = graph.addNode("JFK");
    auto nodeDFW = graph.addNode("DFW");
    auto nodeMIA = graph.addNode("MIA");
    auto nodeJAX = graph.addNode("JAX");


    graph.addDirectedEdge(nodeBOS, nodeSFO, 0); 
    graph.addDirectedEdge(nodeBOS, nodeMIA, 0);
    graph.addDirectedEdge(nodeJFK, nodeSFO, 0);
    graph.addDirectedEdge(nodeJFK, nodeBOS, 0);
    graph.addDirectedEdge(nodeBOS, nodeJFK, 0);
    graph.addDirectedEdge(nodeJFK, nodeDFW, 0);
    graph.addDirectedEdge(nodeJFK, nodeMIA, 0);
    graph.addDirectedEdge(nodeQRD, nodeMIA, 0);
    graph.addDirectedEdge(nodeMIA, nodeJAX, 0);
    graph.addDirectedEdge(nodeJAX, nodeQRD, 0);
    graph.addDirectedEdge(nodeQRD, nodeDFW, 0);
    graph.addDirectedEdge(nodeDFW, nodeQRD, 0);


    //see nodes adjency list 
    for (auto& node : graph.getNodes())
    {
        std::cout << "Node " << node->id << "\n"; 

        for(auto& edge : node->incidentEdges)
        {
            std::cout << "   " << edge->opposite(*node)->id << " weight " << edge->weigth << "\n" ; 
        }
    }

    // std::cout << "Depth first search\n";
    // DFS(graph, *nodeA); 
    // std::cout << "Breath first search\n"; 
    // graph.initialize(); 
    // BFS(*nodeA, *nodeB); 


    std::cout << "Depth first search\n";
    DFS(graph, nodeBOS); 
    std::cout << "Breath first search\n"; 
    graph.initialize(); 
    BFS(nodeBOS); 


    std::cout << "\nShortest path of all nodes from node BOS\n"; 
    for (auto& node : graph.getNodes())
    {
        std::cout << "Node " << node->id << " level " << std::dynamic_pointer_cast<Integer> (node->decorator.get("level"))->getValue() << "\n"; 
    }



    // Graph graph; 

    // //add nodes 
    // auto nodeA = graph.addNode("A");
    // auto nodeB = graph.addNode("B");
    // auto nodeC = graph.addNode("C");
    // auto nodeD = graph.addNode("D");

    // //add edges 
    // graph.addEdge(nodeA, nodeB, 10); 
    // graph.addEdge(nodeA, nodeC, 5);
    // graph.addEdge(nodeB, nodeD, 7);

    // //visualize 
    // graph.print(); 
}