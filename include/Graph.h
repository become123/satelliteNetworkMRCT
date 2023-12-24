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
        std::set<int> verticeSet;
        int weight;
        Edge(int vertex1, int vertex2, int w);
        Edge(const Edge& other) : verticeSet(other.verticeSet), weight(other.weight) {}
        Edge& operator=(const Edge& other);
        bool operator<(const Edge& other) const;
        bool operator==(const Edge& other) const;
        int vertex1() const { return *verticeSet.begin(); }
        int vertex2() const { return *verticeSet.rbegin(); }
    };

    // Graph class to represent the graph
    class Graph {
    private:
        int verticesCount;
        std::vector<std::unordered_map<int, Edge>> adjList;
        std::set<Edge> edgeSet;
        // std::vector<double> localAvgDegree;
        double averageShortestPathLength = -1;
        int diameter = -1;
    public:
        Graph(int v);

        Graph(int _verticesCount, std::set<Edge> _edgeSet);

        int getVerticesCount();

        int getEdgesCount();

        bool isConnected(); // Check if the graph is connected

        std::set<Edge> getEdgeSet();

        int getDegree(int vertex); // Get degree for a given vertex

        // double getLocalAvgDegree(int vertex); // Get local average degree for a given vertex

        // void printLocalAvgDegree(); // Print local average degree for each node

        // void calculateLocalAvgDegree(); // Calculate local average degree for each node

        // Function to add edge to the graph
        void addEdge(int u, int v, int w, bool weighted);

        void deleteEdge(int u, int v);

        void deleteEdge(Edge e);
        
        void randomDeleteEdge(int n, ConvertTool::satIdConversion &translateTool); //random delete n edges, and make sure the graph is still connected

        Graph getRandomDeleteEdgeGraph(int n, ConvertTool::satIdConversion &translateTool); //return the graph that random delete n edges, and make sure the graph is still connected

        double getAverageShortestPathLength();

        int getDiameter();

        void needRecalculate(); // Call this function when the graph is modified

        // Function to find shortest path tree from a given source vertex, return vector is the parent of each node
        std::vector<int> shortestPathTree(int src);
        
        std::set<Edge> randomSpanningTreeEdgeSet();

        std::set<Edge> degreeConstrainedRandomSpanningTreeEdgeSetHelper(int degreeConstraint); //為了避免無法形成的情況發生

        std::set<Edge> degreeConstrainedRandomSpanningTreeEdgeSet(int degreeConstraint);

        std::set<Edge> minimumSpanningTreeEdgeSet();

        std::vector<std::vector<int> > getAdjacencyMatrixN2();// Find N'

        Graph getNewWeighted_Graph(); //回傳的graph針對當前graph的N'，edge weight是兩個方向的平均

        std::set<Edge> minimumLevelTreeEdgeSet(int src); //BFS建出minimumLevelTree

        Tree::Tree minimumLevelTree(int src); //BFS建出minimumLevelTree

        Tree::Tree degreeConstrainedMinimumSpanningTree(int degreeConstraint); //找出degree constrained minimum spanning tree

        Tree::Tree degreeConstrainedMinimumLevelTree(int src, int degreeConstraint); //BFS建出minimumLevelTree，限制每個node的最大degree
    
        Tree::Tree bestDegreeConstrainedMinimumLevelTree(int degreeConstraint); //找出以每個node為root的degreeConstrainedMinimumLevelTree中，最好的一個

        Tree::Tree degreeConstrainedMinimumLevelTree2(int src, int degreeConstraint); //BFS建出minimumLevelTree，限制每個node的最大degree
    
        Tree::Tree bestDegreeConstrainedMinimumLevelTree2(int degreeConstraint); //找出以每個node為root的degreeConstrainedMinimumLevelTree中，最好的一個

        bool tryBetterEdge(Edge e, std::set<Edge> &notSelectedEdges, int degreeConstraint); //在tree graph中先將Edge e移除，變成兩個connected component以後，嘗試找出更好的edge(使tree的diameter,avg shortest path更小)，回傳是否有找到更好的edge

        int treeGraphLocalSearch(Tree::Tree &tree, std::set<Edge> &notSelectedEdges, int degreeConstraint); //從tree的high level開始，循序對每一個edge進行local search，回傳總共更動了幾個edge
    
        Graph getGraphUsingBestDCMLTAndAddEdgesGreedily(int degreeConstraint, int edgeCount, std::map<int,std::vector<double>> &avgShortestPathLengthRecord, std::map<int,std::vector<int>> &diameterRecord); //找出所有衛星為root的DCRST中，路由效能最好的那一個，以此DCRST加入其他edge(greedy追求最佳avg shortest path)形成最終的星網拓普
    
        Graph getDegreeConstrainedRandomGraph(int degreeConstraint, int edgeCount, std::map<int,std::vector<double>> &avgShortestPathLengthRecord, std::map<int,std::vector<int>> &diameterRecord); //回傳一個degree constrained random graph，不斷隨機加入edge，直到不能再加為止，並且graph中所有node的degree都不超過degreeConstraint
        
        Graph getGraphUsingBestDCMLTAndAddEdgesRandomly(int degreeConstraint, int edgeCount, std::map<int,std::vector<double>> &avgShortestPathLengthRecord, std::map<int,std::vector<int>> &diameterRecord); 
    
        Graph getGraphUsingDCRSTAndAddEdgesGreedily(int degreeConstraint, int edgeCount, std::map<int,std::vector<double>> &avgShortestPathLengthRecord, std::map<int,std::vector<int>> &diameterRecord); 
    
        Graph getGraphUsingBestDCMLTAndAddEdgesBaseOnTreeStructure(int degreeConstraint, int edgeCount, std::map<int,std::vector<double>> &avgShortestPathLengthRecord, std::map<int,std::vector<int>> &diameterRecord); //找出所有衛星為root的DCRST中，路由效能最好的那一個，以此DCRST加入其他edge(greedy追求最佳avg shortest path)形成最終的星網拓普
    
        Graph getGraphUsingDCMSTAndAddEdgesGreedily(int degreeConstraint, int edgeCount, std::map<int,std::vector<double>> &avgShortestPathLengthRecord, std::map<int,std::vector<int>> &diameterRecord); //找出所有衛星為root的DCRST中，路由效能最好的那一個，以此DCRST加入其他edge(greedy追求最佳avg shortest path)形成最終的星網拓普

        Graph getGraphUsingDCMSTAndAddEdgesRandomly(int degreeConstraint, int edgeCount, std::map<int,std::vector<double>> &avgShortestPathLengthRecord, std::map<int,std::vector<int>> &diameterRecord); //找出所有衛星為root的DCRST中，路由效能最好的那一個，以此DCRST加入其他edge(greedy追求最佳avg shortest path)形成最終的星網拓普
        
        Graph getGraphUsingDCMSTAndAddSortedEdge(int degreeConstraint, int edgeCount, std::map<int,std::vector<double>> &avgShortestPathLengthRecord, std::map<int,std::vector<int>> &diameterRecord); //找出所有衛星為root的DCRST中，路由效能最好的那一個，以此DCRST加入其他edge(greedy追求最佳avg shortest path)形成最終的星網拓普
    };
}

#endif