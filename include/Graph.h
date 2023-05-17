#ifndef GRAPH
#define GRAPH
#include <vector>
#include <unordered_map>
#include <queue>
#include <utility>
#include <limits>
#include <set>
#include <iostream>
#include <map>
#include "Tree.h"

namespace Graph
{
    // Edge class to represent edges in the graph
    class Edge {
    public:
        int from;
        int to;
        int weight;
        Edge(int _from, int _to, int w);
        Edge(const Edge& other) : from(other.from), to(other.to), weight(other.weight) {}
        bool operator<(const Edge& other) const;
        bool operator==(const Edge& other) const;
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

        std::set<Edge> getEdgeSet();

        // Function to add edge to the graph
        void addEdge(int u, int v, int w, bool weighted);

        // Function to find shortest path tree from a given source vertex, return vector is the parent of each node
        std::vector<int> shortestPathTree(int src);

        std::set<Edge> randomSpanningTreeEdgeSet();

        std::set<Edge> minimumSpanningTreeEdgeSet();

        std::vector<std::vector<int> > getAdjacencyMatrixN2();// Find N'

        Graph getNewWeighted_Graph(); //回傳的graph針對當前graph的N'，edge weight是兩個方向的平均

        std::set<Edge> minimumLevelTreeEdgeSet(int src); //BFS建出minimumLevelTree

        Tree::Tree minimumLevelTree(int src); //BFS建出minimumLevelTree

        Tree::Tree degreeConstrainedMinimumLevelTree(int src, int degreeConstraint); //BFS建出minimumLevelTree，限制每個node的最大degree
    };
}

#endif