#include "Graph.h"
#include "DisjointSet.h"
#include "UtilFunction.h"
#include "ConvertTool.h"
#include <climits>

namespace Graph
{
    Edge:: Edge(int vertex1, int vertex2, int w) {
        verticeSet = std::set<int>{vertex1, vertex2};
        weight = w;
    }

    Graph::Graph(int v) {
        verticesCount = v;
        adjList.resize(verticesCount);
        // localAvgDegree.resize(verticesCount);
        // localAvgDegree.assign(verticesCount, 0);
        averageShortestPathLength = -1;
        diameter = -1;
    }

    Graph::Graph(int _verticesCount, std::set<Edge> _edgeSet) {
        verticesCount = _verticesCount;
        adjList.resize(verticesCount);
        // localAvgDegree.resize(verticesCount);
        // localAvgDegree.assign(verticesCount, 0);
        for(auto edge : _edgeSet){
            addEdge(edge.vertex1(), edge.vertex2(), edge.weight, true);
        }
        averageShortestPathLength = -1;
        diameter = -1;
    }
    
    int Graph::getVerticesCount(){
        return verticesCount;
    }

    int Graph::getEdgesCount(){
        return edgeSet.size();
    }

    bool Graph::isConnected(){ // Check if the graph is connected
        DisjointSet::DisjointSet disjointSet(verticesCount);
        for(auto edge : edgeSet){
            disjointSet.Union(edge.vertex1(), edge.vertex2());
        }
        return disjointSet.getGroupCount() == 1;
    }

    // double Graph::getLocalAvgDegree(int vertex){ // Get local average degree for a given vertex
    //     return localAvgDegree[vertex];
    // }

    int Graph::getDegree(int vertex){ // Get degree for a given vertex
        return adjList[vertex].size();
    }
    
    std::set<Edge> Graph::getEdgeSet(){
        return edgeSet;
    }

    // void Graph::printLocalAvgDegree(){
    //     for(int i = 0; i < verticesCount; i++){
    //         std::cout<<"Node "<<i<<"'s local average degree is "<<localAvgDegree[i]<<"\n";
    //     }
    // }

    // void Graph::calculateLocalAvgDegree(){
    //     for(int i = 0; i < verticesCount; i++){
    //         std::vector<int> degrees;
    //         degrees.push_back(adjList[i].size());
    //         for(auto &[neighbor,edge] : adjList[i]){
    //             degrees.push_back(adjList[neighbor].size());
    //             }
    //         localAvgDegree[i] = UtilFunction::average(degrees);
    //     }
    // }

    Edge& Edge::operator=(const Edge& other) {
        if (this == &other) {
            return *this; // Handling self-assignment
        }

        verticeSet = other.verticeSet;
        weight = other.weight;

        return *this;
    }    

    bool Edge::operator<(const Edge& other) const {
        // Compare the vertex sets lexicographically
        if (verticeSet < other.verticeSet)
            return true;
        else if (verticeSet > other.verticeSet)
            return false;

        // If the vertex sets are the same, compare the weights
        return weight < other.weight;
    }

    bool Edge::operator==(const Edge& other) const {
        return weight == other.weight && verticeSet == other.verticeSet;
    }    

    void Graph::addEdge(int u, int v, int w, bool weighted) {
        if(weighted){
            adjList[u].emplace(v, Edge(u, v, w));
            adjList[v].emplace(u, Edge(v, u, w));
            edgeSet.insert(Edge(u, v, w));
            // std::cout<<"Edge: "<<u<<" "<<v<<" "<<w;
            // std::cout<<",size: "<<edgeSet.size()<<"\n";
        }
        else{
            adjList[u].emplace(v, Edge(u, v, 1));
            adjList[v].emplace(u, Edge(v, u, 1));
            edgeSet.insert(Edge(u, v, 1));
            // std::cout<<"Edge: "<<u<<" "<<v<<" "<<1;
            // std::cout<<",size: "<<edgeSet.size()<<"\n";           
        }
        needRecalculate();
        // std::set<int> needReCalculateVertices; //the vertices that need to recalculate the local average degree
        // needReCalculateVertices.insert(u);
        // needReCalculateVertices.insert(v);
        // for(auto &[neighbor,edge] : adjList[u]){
        //     needReCalculateVertices.insert(neighbor);
        // }
        // for(auto &[neighbor,edge] : adjList[v]){
        //     needReCalculateVertices.insert(neighbor);
        // }
        // for(auto vertex : needReCalculateVertices){
        //     std::vector<int> degrees;
        //     degrees.push_back(adjList[vertex].size());
        //     for(auto &[neighbor,edge] : adjList[vertex]){
        //         degrees.push_back(adjList[neighbor].size());
        //     }
        //     localAvgDegree[vertex] = UtilFunction::average(degrees);
        // }
    }

    void Graph::deleteEdge(int u, int v){
        Edge e = adjList.at(u).at(v);
        adjList[u].erase(v);
        adjList[v].erase(u);
        edgeSet.erase(e);
        needRecalculate();
        // std::set<int> needReCalculateVertices; //the vertices that need to recalculate the local average degree
        // needReCalculateVertices.insert(u);
        // needReCalculateVertices.insert(v);
        // for(auto &[neighbor,edge] : adjList[u]){
        //     needReCalculateVertices.insert(neighbor);
        // }
        // for(auto &[neighbor,edge] : adjList[v]){
        //     needReCalculateVertices.insert(neighbor);
        // }
        // for(auto vertex : needReCalculateVertices){
        //     std::vector<int> degrees;
        //     degrees.push_back(adjList[vertex].size());
        //     for(auto &[neighbor,edge] : adjList[vertex]){
        //         degrees.push_back(adjList[neighbor].size());
        //     }
        //     localAvgDegree[vertex] = UtilFunction::average(degrees);
        // }
    }

    void Graph::deleteEdge(Edge e){
        int u = e.vertex1();
        int v = e.vertex2();
        adjList[u].erase(v);
        adjList[v].erase(u);
        edgeSet.erase(e);
        needRecalculate();
        // std::set<int> needReCalculateVertices; //the vertices that need to recalculate the local average degree
        // needReCalculateVertices.insert(u);
        // needReCalculateVertices.insert(v);
        // for(auto &[neighbor,edge] : adjList[u]){
        //     needReCalculateVertices.insert(neighbor);
        // }
        // for(auto &[neighbor,edge] : adjList[v]){
        //     needReCalculateVertices.insert(neighbor);
        // }
        // for(auto vertex : needReCalculateVertices){
        //     std::vector<int> degrees;
        //     degrees.push_back(adjList[vertex].size());
        //     for(auto &[neighbor,edge] : adjList[vertex]){
        //         degrees.push_back(adjList[neighbor].size());
        //     }
        //     localAvgDegree[vertex] = UtilFunction::average(degrees);
        // }
    }

    void Graph::randomDeleteEdge(int n, ConvertTool::satIdConversion &translateTool){ //random delete n edges, and make sure the graph is still connected
        while(n--){
            int randomInt = UtilFunction::getRandomInt(0, edgeSet.size()-1);
            auto it = std::next(edgeSet.begin(), randomInt);
            int u = it->vertex1();
            int v = it->vertex2();
            int weight = it->weight;
            adjList[u].erase(v);
            adjList[v].erase(u);
            edgeSet.erase(it);
            if(!isConnected()){
                adjList[u].emplace(v, Edge(u, v, weight));
                adjList[v].emplace(u, Edge(v, u, weight));
                edgeSet.insert(Edge(u, v, it->weight));
                n++;
                continue;
            }
            // std::cout<<"Delete edge: "<<translateTool.indexToSatId(u)<<" "<<translateTool.indexToSatId(v)<<"\n";
        }
        needRecalculate();
    }

    Graph Graph::getRandomDeleteEdgeGraph(int n, ConvertTool::satIdConversion &translateTool){ //return the graph that random delete n edges, and make sure the graph is still connected
        Graph newGraph = *this;
        newGraph.randomDeleteEdge(n, translateTool);
        return newGraph;
    }

    double Graph::getAverageShortestPathLength(){
        if(averageShortestPathLength > 0){
            return averageShortestPathLength;
        }
        double _averageShortestPathLength = 0;
        int _maximumShortestPathLength = 0;
        std::vector<std::vector<int>> ajacencyMatrix(verticesCount, std::vector<int>(verticesCount,std::numeric_limits<int>::max()));
        for(int i = 0; i < verticesCount; i++){
            ajacencyMatrix[i][i] = 0;
            for(auto edge : adjList[i]){
                ajacencyMatrix[i][edge.first] = edge.second.weight;
                ajacencyMatrix[edge.first][i] = edge.second.weight;
            }
        }
        //Floyd Warshall Algorithm
        for(int k = 0; k < verticesCount; k++){
            for(int i = 0; i < verticesCount; i++){
                for(int j = 0; j < verticesCount; j++){
                    if(ajacencyMatrix[i][k] != std::numeric_limits<int>::max() && ajacencyMatrix[k][j] != std::numeric_limits<int>::max()){
                        ajacencyMatrix[i][j] = std::min(ajacencyMatrix[i][j], ajacencyMatrix[i][k] + ajacencyMatrix[k][j]);
                    }
                }
            }
        }
        for(int i = 0; i < verticesCount; i++){
            for(int j = 0; j < verticesCount; j++){
                if(ajacencyMatrix[i][j] != std::numeric_limits<int>::max()){
                    _averageShortestPathLength += ajacencyMatrix[i][j];
                    _maximumShortestPathLength = std::max(_maximumShortestPathLength, ajacencyMatrix[i][j]);
                }
                else{
                    std::cout<<"Error: the graph is not connected\n";
                    exit(1);
                }
            }
        }
        _averageShortestPathLength /= (verticesCount * verticesCount) ;
        diameter = _maximumShortestPathLength;
        return averageShortestPathLength = _averageShortestPathLength;
    }

    int Graph::getDiameter(){
        if(diameter > 0){
            return diameter;
        }
        double _averageShortestPathLength = 0;
        int _maximumShortestPathLength = 0;
        std::vector<std::vector<int>> ajacencyMatrix(verticesCount, std::vector<int>(verticesCount,std::numeric_limits<int>::max()));
        for(int i = 0; i < verticesCount; i++){
            ajacencyMatrix[i][i] = 0;
            for(auto edge : adjList[i]){
                ajacencyMatrix[i][edge.first] = edge.second.weight;
                ajacencyMatrix[edge.first][i] = edge.second.weight;
            }
        }
        //Floyd Warshall Algorithm
        for(int k = 0; k < verticesCount; k++){
            for(int i = 0; i < verticesCount; i++){
                for(int j = 0; j < verticesCount; j++){
                    if(ajacencyMatrix[i][k] != std::numeric_limits<int>::max() && ajacencyMatrix[k][j] != std::numeric_limits<int>::max()){
                        ajacencyMatrix[i][j] = std::min(ajacencyMatrix[i][j], ajacencyMatrix[i][k] + ajacencyMatrix[k][j]);
                    }
                }
            }
        }
        for(int i = 0; i < verticesCount; i++){
            for(int j = 0; j < verticesCount; j++){
                if(ajacencyMatrix[i][j] != std::numeric_limits<int>::max()){
                    _averageShortestPathLength += ajacencyMatrix[i][j];
                    _maximumShortestPathLength = std::max(_maximumShortestPathLength, ajacencyMatrix[i][j]);
                }
            }
        }
        _averageShortestPathLength /= (verticesCount * verticesCount) ;
        averageShortestPathLength = _averageShortestPathLength;
        return diameter = _maximumShortestPathLength;
    }

    void Graph::needRecalculate(){
        averageShortestPathLength = -1;
        diameter = -1;
    }

    std::vector<int> Graph::shortestPathTree(int src) {
        // std::cout<<"shortestPathTree: src: "<<src<<"\n";
        std::vector<int> dist(verticesCount, std::numeric_limits<int>::max());
        std::vector<int> parent(verticesCount, -1);
        std::vector<bool> visited(verticesCount, false);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

        pq.push(std::make_pair(0, src));
        dist[src] = 0;

        while (!pq.empty()) {
            std::vector<std::pair<int, int>> candidates;
            int target = pq.top().first;
            while (!pq.empty() && pq.top().first == target) {
                if(!visited[pq.top().second]){ //only push the nonvisited element to candidates // pq may have duplicated element
                    candidates.push_back(pq.top());
                }
                pq.pop();
            }
            if(candidates.size() == 0){ 
                std::cout<<"candidates.size() == 0\n";
                continue;
            }
            // std::cout<<"all candidates:";
            // for(auto i: candidates){
            //     std::cout<<"("<<i.first<<", "<<i.second<<") ";
            // }   
            // std::cout<<"\n";
            std::pair<int, int> minDistNodePair = candidates[UtilFunction::getRandomInt(0, (int)candidates.size()-1)];
            for(auto &candidate: candidates){ //push the nonselected element back to pq 
                if(candidate == minDistNodePair){
                    // std::cout<<"selected: ("<<candidate.first<<", "<<candidate.second<<")\n";
                    continue;
                }
                pq.push(candidate);
            }
            int minDistNode = minDistNodePair.second;

            visited[minDistNode] = true;

            for (auto &[to, edge] : adjList[minDistNode]) {
                int v = to;
                int weight = edge.weight;

                if (!visited[v] && dist[v] > dist[minDistNode] + weight) {//relax
                    dist[v] = dist[minDistNode] + weight;
                    parent[v] = minDistNode;
                    // cout<<"insert (dist: "<<dist[v]<<", id: "<<v<<")\n";
                    pq.push(std::make_pair(dist[v], v));// pq may have duplicated element. better way is to use decrease key
                }
            }
        }
        return parent;
    }
    
    std::set<Edge> Graph::randomSpanningTreeEdgeSet(){
        DisjointSet::DisjointSet dsSet(verticesCount);
        std::set<Edge> edgeCandidates(edgeSet);
        std::set<Edge> rst;
        while((int)rst.size() < verticesCount - 1){
            int randomIndex = UtilFunction::getRandomInt(0, edgeCandidates.size() - 1);
            auto it = std::next(edgeCandidates.begin(), randomIndex);
            Edge edge = *it;
            edgeCandidates.erase(it);
            if(dsSet.Union(edge.vertex1(), edge.vertex2())){
                rst.insert(edge);
            }
        }
        return rst;
    }

    std::set<Edge> Graph::degreeConstrainedRandomSpanningTreeEdgeSetHelper(int degreeConstraint){
        DisjointSet::DisjointSet dsSet(verticesCount);
        std::set<Edge> edgeCandidates(edgeSet);
        std::vector<int> degree(verticesCount, 0);
        std::set<Edge> rst;
        while((int)rst.size() < verticesCount - 1){
            int randomIndex = UtilFunction::getRandomInt(0, edgeCandidates.size() - 1);
            auto it = std::next(edgeCandidates.begin(), randomIndex);
            Edge edge = *it;
            edgeCandidates.erase(it);
            if(edgeCandidates.size() == 0){ //隨機生成的拓譜不好，無法形成degreeConstrainedRandomSpanningTree
                return std::set<Edge>();
            }
            if(degree[edge.vertex1()] < degreeConstraint && degree[edge.vertex2()] < degreeConstraint && dsSet.Union(edge.vertex1(), edge.vertex2())){
                rst.insert(edge);
                degree[edge.vertex1()]++;
                degree[edge.vertex2()]++;
            }
        }
        return rst;
    }

    std::set<Edge> Graph::degreeConstrainedRandomSpanningTreeEdgeSet(int degreeConstraint){
        std::set<Edge> rst;
        while((int)rst.size() == 0){
            rst = degreeConstrainedRandomSpanningTreeEdgeSetHelper(degreeConstraint);
        }           
        return rst;
    }    

    std::set<Edge> Graph::minimumSpanningTreeEdgeSet(){
        // std::cout<<"minimumSpanningTree\n";
        DisjointSet::DisjointSet dsSet(verticesCount);
        std::set<Edge> edgeCandidates(edgeSet);
        std::set<Edge> mst;
        for(auto &edge: edgeCandidates){
            if(dsSet.Union(edge.vertex1(), edge.vertex2())){
                // std::cout<<"edge: "<<edge.vertex1()<<" "<<edge.vertex2()<<" "<<edge.weight<<"\n";
                mst.insert(edge);
            }
            if(dsSet.getGroupCount() == 1){
                break;
            }
        }
        return mst;
    }

    std::vector<std::vector<int> > Graph::getAdjacencyMatrixN2(){ // Find N'
        std::vector<std::vector<int> > adjacencyMatrixN2(verticesCount, std::vector<int>(verticesCount,0));
        for (int i = 0; i < verticesCount; i++) {
            std::vector<int> parent = this->shortestPathTree(i);

            for (int j = 0; j < verticesCount; j++) {
                int cur = j;
                while(parent[cur] != -1){
                    adjacencyMatrixN2[parent[cur]][cur]++;
                    cur = parent[cur];
                }
            }
        }  
        return adjacencyMatrixN2;      
    }

    Graph Graph::getNewWeighted_Graph(){ //回傳的graph針對當前graph的N'，edge weight是兩個方向的平均
        std::vector<std::vector<int> > adjacencyMatrixN2 = this->getAdjacencyMatrixN2();
        std::multimap<int, std::pair<int, int>> edgeTable;//(average weight, (edge vertex1, edge vertex2))
        for(int i = 0; i < verticesCount; ++i){
            for(int j = i; j < verticesCount; ++j){
                if(adjacencyMatrixN2[i][j] != 0){
                    adjacencyMatrixN2[i][j] = (adjacencyMatrixN2[i][j] + adjacencyMatrixN2[j][i])/2; // get average of the two direction of the edge
                    // cout<<translateTool.indexToSatId(i)<<"to"<<translateTool.indexToSatId(j)<<":"<<adjacencyMatrixN2[i][j]<<"\n";
                    edgeTable.emplace(adjacencyMatrixN2[i][j],std::make_pair(i, j));
                }
            }
        }

        Graph newWeighted_Graph(verticesCount);
        for(auto i:edgeTable){
            // cout<<i.second.first<<"to"<<i.second.second<<":"<<i.first<<"\n";
            // std::cout<<"("<<i.second.first<<","<<i.second.second<<")"<<"weight:"<<i.first<<"\n";
            newWeighted_Graph.addEdge(i.second.first, 
                                      i.second.second, 
                                      i.first, 
                                      true);
        }      
        return newWeighted_Graph;  
    }

    std::set<Edge> Graph::minimumLevelTreeEdgeSet(int src){ //BFS建出minimumLevelTree
        DisjointSet::DisjointSet dsSet(verticesCount);
        std::set<Edge> mlt;
        std::queue<int> q;
        q.push(src);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(auto &[v, edge]: adjList[u]){
                if(dsSet.Union(u, v)){
                    mlt.insert(edge);
                    q.push(v);
                }
            }
        }
        return mlt;
    }  

    Tree::Tree Graph::minimumLevelTree(int src){ //BFS建出minimumLevelTree
        DisjointSet::DisjointSet dsSet(verticesCount);
        Tree::Tree mlt = Tree::Tree(src, verticesCount);
        std::queue<int> q;
        q.push(src);
        while(!q.empty()){
            int levelSize = q.size();
            while(levelSize--){
                int u = q.front();
                q.pop();
                for(auto &[v, edge]: adjList[u]){
                    if(dsSet.Union(u, v)){
                        mlt.addEdge(u, v);
                        q.push(v);
                    }
                }
            }
        }
        mlt.buildLevelAndSubtreeSize();
        return mlt;
    }

    bool Graph::canSpanDegreeConstrainedMinimumLevelTree(int src, int degreeConstraint){ //回傳是否可以建出degreeConstrainedMinimumLevelTree
        DisjointSet::DisjointSet dsSet(verticesCount);
        Tree::Tree mlt = Tree::Tree(src, verticesCount);
        std::queue<int> q;
        std::vector<bool> visited(verticesCount, false);
        q.push(src);
        visited[src] = true;
        while(!q.empty()){
            int levelSize = q.size();
            std::unordered_map<int, std::vector<int>> levelNodes;//記錄這一層中有哪些以及他們的child nodes
            int maxLength = 0;
            while(levelSize--){
                int u = q.front();
                q.pop();
                levelNodes[u] = std::vector<int>();
                for(auto &[v, edge]: adjList[u]){
                    /*---------------old manner---------------*/
                    // if(mlt.getNode(u)->degree < degreeConstraint && dsSet.Union(u, v)){
                    //     mlt.addEdge(u, v);
                    //     q.push(v);
                    //     visited[v] = true;
                    // }
                    /*---------------old manner---------------*/        
                    /*---------------new manner---------------*/            
                    levelNodes[u].push_back(v);
                    maxLength = std::max(maxLength, (int)levelNodes[u].size());
                    /*---------------new manner---------------*/
                }
            }
            /*---------------new manner---------------*/
            for(int i = 0; i < maxLength; ++i){ //Round-robin將每個node的child nodes加入tree及queue中
                for(auto &[u, childNodes]: levelNodes){ //u為parent node
                    if(i < (int)childNodes.size()){ //i為child node的index
                        int v = childNodes[i];
                        if(mlt.getNode(u)->degree < degreeConstraint && dsSet.Union(u, v)){
                            mlt.addEdge(u, v);
                            q.push(v);
                            visited[v] = true;
                        }
                    }
                }
            }
            /*---------------new manner---------------*/
        }
        for(int i = 0; i < verticesCount; ++i){
            if(!visited[i]){
                return false;
            }
        }  
        return true;
    }
    
    Tree::Tree Graph::degreeConstrainedMinimumLevelTree(int src, int degreeConstraint){ //BFS建出minimumLevelTree，限制每個node的最大degree
        DisjointSet::DisjointSet dsSet(verticesCount);
        Tree::Tree mlt = Tree::Tree(src, verticesCount);
        std::queue<int> q;
        std::vector<bool> visited(verticesCount, false);
        q.push(src);
        visited[src] = true;
        while(!q.empty()){
            int levelSize = q.size();
            std::unordered_map<int, std::vector<int>> levelNodes;//記錄這一層中有哪些以及他們的child nodes
            int maxLength = 0;
            while(levelSize--){
                int u = q.front();
                q.pop();
                levelNodes[u] = std::vector<int>();
                for(auto &[v, edge]: adjList[u]){
                    /*---------------old manner---------------*/
                    // if(mlt.getNode(u)->degree < degreeConstraint && dsSet.Union(u, v)){
                    //     mlt.addEdge(u, v);
                    //     q.push(v);
                    //     visited[v] = true;
                    // }
                    /*---------------old manner---------------*/        
                    /*---------------new manner---------------*/            
                    levelNodes[u].push_back(v);
                    maxLength = std::max(maxLength, (int)levelNodes[u].size());
                    /*---------------new manner---------------*/ 
                }
            }
            /*---------------new manner---------------*/
            for(int i = 0; i < maxLength; ++i){ //Round-robin將每個node的child nodes加入tree及queue中
                for(auto &[u, childNodes]: levelNodes){ //u為parent node
                    if(i < (int)childNodes.size()){ //i為child node的index
                        int v = childNodes[i];
                        if(mlt.getNode(u)->degree < degreeConstraint && dsSet.Union(u, v)){
                            mlt.addEdge(u, v);
                            q.push(v);
                            visited[v] = true;
                        }
                    }
                }
            }
            /*---------------new manner---------------*/ 
        }
        for(int i = 0; i < verticesCount; ++i){
            if(!visited[i]){
                std::cout<<"error: degreeConstrainedMinimumLevelTree() can't build a tree with degreeConstraint "<<degreeConstraint<<"\n";
                exit(1);
            }
        }     
        mlt.buildLevelAndSubtreeSize();
        return mlt;
    }  

    Tree::Tree Graph::bestDegreeConstrainedMinimumLevelTree(int degreeConstraint){ //找出以每個node為root的degreeConstrainedMinimumLevelTree中，最好的一個
        double bestAvgShortestPath = 1000000000;
        int bestRoot = -1;
        for(int i = 0; i < verticesCount; ++i){
            if(!canSpanDegreeConstrainedMinimumLevelTree(i, degreeConstraint)){
                continue;
            }
            Tree::Tree mlt = degreeConstrainedMinimumLevelTree(i, degreeConstraint);
            Graph mltGraph = mlt.toGraph();
            double avgShortestPath = mltGraph.getAverageShortestPathLength();
            // std::cout<<"avgShortestPath:"<<avgShortestPath<<"\n";
            if(avgShortestPath < bestAvgShortestPath){
                // std::cout<<"bestAvgShortestPath:"<<avgShortestPath<<"\n";
                bestAvgShortestPath = avgShortestPath;
                bestRoot = i;
            }
        }
        if(bestRoot == -1){
            std::cout<<"error: bestDegreeConstrainedMinimumLevelTree() can't build a tree with degreeConstraint "<<degreeConstraint<<"\n";
            exit(1);
        }
        Tree::Tree bestMlt = degreeConstrainedMinimumLevelTree(bestRoot, degreeConstraint);
        return bestMlt;
    }        

    //在tree graph中先將Edge e移除，變成兩個connected component以後，嘗試找出更好的edge(使tree的diameter,avg shortest path更小)，回傳是否有找到更好的edge
    bool Graph::tryBetterEdge(Edge e, std::set<Edge> &notSelectedEdges, int degreeConstraint){
        bool res = false;
        deleteEdge(e);
        notSelectedEdges.insert(e);
        DisjointSet::DisjointSet dsSet(verticesCount);
        for(auto e:edgeSet){
            dsSet.Union(e.vertex1(), e.vertex2());
        }
        std::set<std::pair<int, std::pair<double, Edge>>> candidateEdges;
        for(auto e:notSelectedEdges){
            if(dsSet.find(e.vertex1()) != dsSet.find(e.vertex2()) && getDegree(e.vertex1()) < degreeConstraint && getDegree(e.vertex2()) < degreeConstraint){
                addEdge(e.vertex1(), e.vertex2(), e.weight, true);
                double avgShortestPath = getAverageShortestPathLength();
                int diameter = getDiameter();
                candidateEdges.insert({diameter, {avgShortestPath, e}});
                deleteEdge(e);
            }
        }
        // std::cout<<"candidateEdges.size():"<<candidateEdges.size()<<"\n";
        if(!candidateEdges.empty()){
            Edge bestEdge = candidateEdges.begin()->second.second;
            if(!(bestEdge == e)){
                res = true;
            }
            addEdge(bestEdge.vertex1(), bestEdge.vertex2(), bestEdge.weight, true);
            notSelectedEdges.erase(bestEdge);
        }
        return res;
    }

    //從tree的high level開始，循序對每一個edge進行local search，回傳總共更動了幾個edge
    int Graph::treeGraphLocalSearch(Tree::Tree &tree, std::set<Edge> &notSelectedEdges, int degreeConstraint){
        int res = 0;
        std::vector<Edge> edgesSequence;
        std::queue<Tree::TreeNode*> q;
        q.push(tree.getRoot());
        while(!q.empty()){
            int levelSize = q.size();
            while(levelSize--){
                Tree::TreeNode* cur = q.front();
                if(cur->parent != nullptr){
                    edgesSequence.push_back({cur->parent->id, cur->id, 1});
                }
                q.pop();
                for(auto child : cur->children){
                    q.push(child);
                }
            }
        }
        std::reverse(edgesSequence.begin(), edgesSequence.end());
        for(auto e:edgesSequence){
            if(tryBetterEdge(e, notSelectedEdges, degreeConstraint)){
                ++res;
            }
        }
        return res;
    }

    Graph Graph::getGraphUsingBestDCMLTAndAddEdgesGreedily(int degreeConstraint){//找出所有衛星為root的DCRST中，路由效能最好的那一個，以此DCRST加入其他edge(greedy追求最佳avg shortest path)形成最終的星網拓普
        Tree::Tree bestMlt = degreeConstrainedRandomSpanningTreeEdgeSet(degreeConstraint);
        Graph mltGraph = bestMlt.toGraph();
        std::set<Edge> notSelectedEdges = UtilFunction::difference(edgeSet, mltGraph.edgeSet);
        double minAvgShortestPathLength = mltGraph.getAverageShortestPathLength();
        while(mltGraph.getEdgesCount() < INT_MAX){ //不斷加入當前可以使avg shortest path有最佳提升的edge，直到edge數量達到特定數量
            Edge bestEdge(-1, -1, -1);
            for (std::set<Edge>::iterator it = notSelectedEdges.begin(); it != notSelectedEdges.end();){
                if(mltGraph.getDegree(it->vertex1()) > 2 || mltGraph.getDegree(it->vertex2()) > 2){
                    it = notSelectedEdges.erase(it);// because if adding this edge will cause graph node degree > 3
                    continue;
                }
                mltGraph.addEdge(it->vertex1(), it->vertex2(), 1, true);
                // std::cout<<"add edge: "<<it->vertex1()<<" "<<it->vertex2()<<"\n";
                // std::cout<<"mltGraph EdgesCount:"<<mltGraph.getEdgesCount()<<"\n";
                if(mltGraph.getAverageShortestPathLength() < minAvgShortestPathLength){
                    // minDiameter = mltGraph.getDiameter();
                    minAvgShortestPathLength = mltGraph.getAverageShortestPathLength();
                    bestEdge = *it;
                    // std::cout<<"find better avg shortest path length,";
                    // std::cout<<"average shortest path length: "<<mltGraph.getAverageShortestPathLength()<<", ";
                    // std::cout<<"diameter: "<<mltGraph.getDiameter()<<"\n";                        
                }
                mltGraph.deleteEdge(it->vertex1(), it->vertex2());
                // std::cout<<"delete edge: "<<it->vertex1()<<" "<<it->vertex2()<<"\n";
                // std::cout<<"mltGraph EdgesCount:"<<mltGraph.getEdgesCount()<<"\n";
                ++it;
            }
            if(bestEdge.vertex1() == -1){ //如果沒有找到可以使avg shortest path有提升的edge，則停止加入edge
                // std::cout<<"**********************mltGraph EdgesCount:"<<mltGraph.getEdgesCount()<<", reach limit!**********************\n";
                break;
            }
            mltGraph.addEdge(bestEdge.vertex1(), bestEdge.vertex2(), 1, true); //加入最佳的edge
            // std::cout<<"-----------------add edge: "<<bestEdge.vertex1()<<" "<<bestEdge.vertex2()<<"------------------\n";
            notSelectedEdges.erase(bestEdge); //將加入的edge從notSelectedEdgeSet中刪除                         
        }     
        return mltGraph;
    }

    Graph Graph::getDegreeConstrainedRandomGraph(int degreeConstraint){
        std::set<Edge> dcrst = degreeConstrainedRandomSpanningTreeEdgeSet(degreeConstraint);
        Graph res(verticesCount, dcrst); //用DCRST當作初始的星網拓普，確保graph是connected的
        std::set<Edge> notSelectedEdges = UtilFunction::difference(edgeSet, dcrst);
        while(notSelectedEdges.size() > 0){
            int randomIndex = UtilFunction::getRandomInt(0, notSelectedEdges.size() - 1);
            auto it = std::next(notSelectedEdges.begin(), randomIndex);
            Edge edge = *it;
            notSelectedEdges.erase(it);
            if(res.getDegree(edge.vertex1()) < degreeConstraint && res.getDegree(edge.vertex2()) < degreeConstraint){
                res.addEdge(edge.vertex1(), edge.vertex2(), edge.weight, true);
            }
        }    
        return res;        
    }

}
