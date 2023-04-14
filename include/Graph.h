#ifndef GRAPH
#define GRAPH
#include <vector>
#include <queue>
#include <utility>
#include <limits>

namespace Graph
{
    // Edge class to represent edges in the graph
    class Edge {
    public:
        int to;
        int weight;
        Edge(int t, int w);
    };

    // Graph class to represent the graph
    class Graph {
    private:
        int verticesCount;
        std::vector<std::vector<Edge>> adjList;
    public:
        Graph(int v);

        // Function to add edge to the graph
        void addEdge(int u, int v, int w, bool weighted);

        // Function to find shortest path tree from a given source vertex, return vector is the parent of each node
        std::vector<int> shortestPathTree(int src);

        int getVerticesCount();
    };
}

#endif