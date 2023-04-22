#ifndef GRAPH
#define GRAPH
#include <vector>
#include <unordered_map>
#include <queue>
#include <utility>
#include <limits>
#include <set>
#include <iostream>

namespace Graph
{
    // Edge class to represent edges in the graph
    class Edge {
    public:
        int from;
        int to;
        int weight;
        Edge(int _from, int _to, int w);
        bool operator<(const Edge& other) const;
    };

    // Graph class to represent the graph
    class Graph {
    private:
        int verticesCount;
        std::vector<std::unordered_map<int, Edge>> adjList;
        std::set<Edge> edgeSet;
    public:
        Graph(int v);

        int getVerticesCount();

        // Function to add edge to the graph
        void addEdge(int u, int v, int w, bool weighted);

        // Function to find shortest path tree from a given source vertex, return vector is the parent of each node
        std::vector<int> shortestPathTree(int src);

        std::set<Edge> randomSpanningTree();
    };
}

#endif