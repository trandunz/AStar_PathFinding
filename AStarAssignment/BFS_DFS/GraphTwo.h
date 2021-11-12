#pragma once
#include "NumptyBehavior.h"
// Data structure to store a graph edge
struct Edge {
    int src, dest;
};

// A class to represent a graph object
class GraphTwo : NumptyBehavior
{
public:
    // a vector of vectors to represent an adjacency list
    std::vector<std::vector<int>> adjList;

    // Graph Constructor
    GraphTwo(std::vector<Edge> const& edges, int n)
    {
        // resize the vector to hold `n` elements of type `vector<int>`
        adjList.resize(n);

        // add edges to the undirected graph
        for (auto& edge : edges)
        {
            adjList[edge.src].push_back(edge.dest);
            adjList[edge.dest].push_back(edge.src);
        }
    }
};

// Perform BFS recursively on the graph
void recursiveBFS(GraphTwo const& graph, std::queue<int>& q, std::vector<bool>& discovered)
{
    if (q.empty()) {
        return;
    }

    // dequeue front node and print it
    int v = q.front();
    q.pop();
    std::cout << (char)(v + ASCIIOFFSET) << " ";

    // do for every edge (v, u)
    for (int u : graph.adjList[v])
    {
        if (!discovered[u])
        {
            // mark it as discovered and enqueue it
            discovered[u] = true;
            q.push(u);
        }
    }

    recursiveBFS(graph, q, discovered);
}


