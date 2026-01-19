#include <iostream>
#include "graph.h"
#include <list>
#include <queue>
#include <cmath>
#include <algorithm>

class Comparator
{
    public:
        bool operator()(std::shared_ptr<Graph::Node> left, std::shared_ptr<Graph::Node> right)
        {
            auto left_g = std::dynamic_pointer_cast<Integer>(left->decorator.get("distance_from_initial_node"))->getValue();
            auto left_h = std::dynamic_pointer_cast<Float>(left->decorator.get("distance_from_end_node"))->getValue();
            auto right_g = std::dynamic_pointer_cast<Integer>(right->decorator.get("distance_from_initial_node"))->getValue();
            auto right_h = std::dynamic_pointer_cast<Float>(right->decorator.get("distance_from_end_node"))->getValue();
            
            return (left_g + left_h * 100) > (right_g + right_h * 100);
        }
};

void a_star(Graph& graph, std::shared_ptr<Graph::Node> initial_node, std::shared_ptr<Graph::Node> end_node)
{
    std::priority_queue<std::shared_ptr<Graph::Node>, std::vector<std::shared_ptr<Graph::Node> >, Comparator> heap; 
    std::unordered_map<std::string, bool> visited;
    std::unordered_map<std::string, std::shared_ptr<Graph::Node>> parent;

    //initialize priority queue 
    for (auto& node : graph.getNodes())
    {
        if (node->id == initial_node->id)
        {
            node->decorator.set("distance_from_initial_node", std::make_shared<Integer>(0));
            heap.push(node); 
        }
        else
        {
            node->decorator.set("distance_from_initial_node", std::make_shared<Integer>(~0));
        }
        
        // Heuristic: Euclidean distance to end node
        float heuristic = std::sqrt(std::pow(node->latitude - end_node->latitude, 2) + std::pow(node->longitute - end_node->longitute, 2));
        node->decorator.set("distance_from_end_node", std::make_shared<Float>(heuristic));
        
        visited[node->id] = false;
        parent[node->id] = nullptr;
    }

    while (!heap.empty())
    {
        auto current_node = heap.top(); 
        heap.pop(); 

        if (visited[current_node->id]) continue;
        visited[current_node->id] = true;

        std::cout << current_node->id <<  " heuristic: " << std::dynamic_pointer_cast<Float>(current_node->decorator.get("distance_from_end_node"))->getValue()  << "\n"; 

        if (*current_node == *end_node)
        {
            break;
        }

        for (auto& edge : current_node->incidentEdges)
        {
            auto nextNode = edge->opposite(*current_node); 

            if (visited[nextNode->id]) continue;

            //relaxtion
            int dist; 
            if ((dist = std::dynamic_pointer_cast<Integer>(current_node->decorator.get("distance_from_initial_node"))->getValue() + edge->weigth) < std::dynamic_pointer_cast<Integer>(nextNode->decorator.get("distance_from_initial_node"))->getValue())
            {
                nextNode->decorator.set("distance_from_initial_node", std::make_shared<Integer>(dist)); 
                // double priority_queue = std::dynamic_pointer_cast<Float>(nextNode->decorator.get("distance_from_end_node"))->getValue() + std::dynamic_pointer_cast<Integer>(nextNode->decorator.get("distance_from_initial_node"))->getValue();
                parent[nextNode->id] = current_node;
                heap.push(nextNode); 
            }

        }
    }

    // reconstruct final path
    std::vector<std::shared_ptr<Graph::Node>> shortest_path;
    std::shared_ptr<Graph::Node> current = end_node; 
    while (current != nullptr)
    {
        shortest_path.push_back(current);
        current = parent[current->id];
    }

    std::reverse(shortest_path.begin(), shortest_path.end());

    // print
    std::cout << "\nshortest path\n"; 
    for (auto& node : shortest_path)
    {
        std::cout << node->id << " ";
    }
    std::cout << std::endl;
    

    
}



int main ()
{
    Graph graph; 

    auto nodeSFO = graph.addNode("SFO", 37.6189, -122.3750);  // San Francisco International
    auto nodeLAX = graph.addNode("LAX", 33.9425, -118.4081);  // Los Angeles International  
    auto nodeDFW = graph.addNode("DFW", 32.8998, -97.0403);   // Dallas/Fort Worth (this one was correct)
    auto nodeORD = graph.addNode("ORD", 41.9742, -87.9073);   // Chicago O'Hare (this one was correct)
    auto nodeJFK = graph.addNode("JFK", 40.6413, -73.7781);   // New York JFK (this one was correct)
    auto nodeBOS = graph.addNode("BOS", 42.3644, -71.0127);   // Boston Logan
    auto nodePVD = graph.addNode("PVD", 41.7240, -71.4282);   // Providence TF Green
    auto nodeBWI = graph.addNode("BWI", 39.1774, -76.6684);   // Baltimore/Washington
    auto nodeMIA = graph.addNode("MIA", 25.7959, -80.2870);   // Miami International (this one was correct)

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


    a_star(graph, nodeBWI, nodeLAX); 
}