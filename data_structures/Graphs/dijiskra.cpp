#include "graph.h"
#include <queue>
#include <iostream>

class Comparator
{
    public:
        bool operator() (std::shared_ptr<Graph::Node> left, std::shared_ptr<Graph::Node> right )
        {
            return  std::dynamic_pointer_cast<Integer>(left->decorator.get("distance_from_node"))->getValue() > 
            std::dynamic_pointer_cast<Integer>(right->decorator.get("distance_from_node"))->getValue(); 
        }
}; 

void dijiskra(Graph& graph, Graph::Node& initial_node)
{
    std::priority_queue<std::shared_ptr<Graph::Node>, std::vector<std::shared_ptr<Graph::Node> >, Comparator> heap; 

    for (auto& node : graph.getNodes())
    {
        if (node->id != initial_node.id)    
            node->decorator.set("distance_from_node", std::make_shared<Integer>(~0)); //set the initial distance from the provided node to the biggest number 
        else
            node->decorator.set("distance_from_node", std::make_shared<Integer>(0));

        heap.push(node); 
    }

    while(!heap.empty())
    {
        //get the closest unvisited node 
        auto currentNode = heap.top();  
        heap.pop(); 
        
        for (auto& edge : currentNode->incidentEdges)
        {
            auto nextNode = edge->opposite(*currentNode); 

            //perform relaxation on the edge 
            int dist; 
            if ((dist = std::dynamic_pointer_cast<Integer>(currentNode->decorator.get("distance_from_node"))->getValue() + edge->weigth) < std::dynamic_pointer_cast<Integer>(nextNode->decorator.get("distance_from_node"))->getValue())
            {
                nextNode->decorator.set("distance_from_node", std::make_shared<Integer>(dist));
                heap.push(nextNode); 
            }
        }
    }

    for (auto& node : graph.getNodes())
    {
        std::cout << node->id + " " << std::dynamic_pointer_cast<Integer> (node->decorator.get("distance_from_node"))->getValue() << "\n"; 
    }


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


    dijiskra(graph, *nodeBWI); 
}