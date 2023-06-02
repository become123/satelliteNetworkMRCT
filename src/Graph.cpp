#include "Graph.h"
#include "DisjointSet.h"
#include "UtilFunction.h"
#include "ConvertTool.h"

namespace Graph
{
    Edge:: Edge(int vertex1, int vertex2, int w) {
        verticeSet = std::set<int>{vertex1, vertex2};
        weight = w;
    }

    int Graph::getVerticesCount(){
        return verticesCount;
    }

    int Graph::getEdgesCount(){
        return edgeSet.size();
    }

    std::set<Edge> Graph::getEdgeSet(){
        return edgeSet;
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

    Graph::Graph(int v) {
        verticesCount = v;
        adjList.resize(verticesCount);
        averageShortestPathLength = -1;
        diameter = -1;
    }

    Graph::Graph(int _verticesCount, std::set<Edge> _edgeSet) {
        verticesCount = _verticesCount;
        adjList.resize(verticesCount);
        for(auto edge : _edgeSet){
            adjList[edge.vertex1()].emplace(edge.vertex2(), edge);
            adjList[edge.vertex2()].emplace(edge.vertex1(), edge);
        }
        this->edgeSet = _edgeSet;
        averageShortestPathLength = -1;
        diameter = -1;
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
    }

    void Graph::randomDeleteEdge(int n, ConvertTool::satIdConversion &translateTool){ //random delete n edges, and make sure the graph is still connected
        while(n--){
            int randomInt = UtilFunction::getRandomInt(0, edgeSet.size()-1);
            auto it = std::next(edgeSet.begin(), randomInt);
            int u = it->vertex1();
            int v = it->vertex2();
            if(adjList[u].size() == 1 || adjList[v].size() == 1){ //delete edge will make a vertex isolated
                n++;
                continue;
            }
            adjList[u].erase(v);
            adjList[v].erase(u);
            edgeSet.erase(it);
            std::cout<<"Delete edge: "<<translateTool.indexToSatId(u)<<" "<<translateTool.indexToSatId(v)<<"\n";
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

    std::set<Edge> Graph::degreeConstrainedRandomSpanningTreeEdgeSet(int degreeConstraint){
        DisjointSet::DisjointSet dsSet(verticesCount);
        std::set<Edge> edgeCandidates(edgeSet);
        std::vector<int> degree(verticesCount, 0);
        std::set<Edge> rst;
        while((int)rst.size() < verticesCount - 1){
            int randomIndex = UtilFunction::getRandomInt(0, edgeCandidates.size() - 1);
            auto it = std::next(edgeCandidates.begin(), randomIndex);
            Edge edge = *it;
            edgeCandidates.erase(it);
            if(degree[edge.vertex1()] < degreeConstraint && degree[edge.vertex2()] < degreeConstraint && dsSet.Union(edge.vertex1(), edge.vertex2())){
                rst.insert(edge);
                degree[edge.vertex1()]++;
                degree[edge.vertex2()]++;
            }
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
            while(levelSize--){
                int u = q.front();
                q.pop();
                for(auto &[v, edge]: adjList[u]){
                    if(mlt.getNode(u)->degree < degreeConstraint && dsSet.Union(u, v)){
                        mlt.addEdge(u, v);
                        q.push(v);
                        visited[v] = true;
                    }
                }
            }
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
            while(levelSize--){
                int u = q.front();
                q.pop();
                for(auto &[v, edge]: adjList[u]){
                    if(mlt.getNode(u)->degree < degreeConstraint && dsSet.Union(u, v)){
                        mlt.addEdge(u, v);
                        q.push(v);
                        visited[v] = true;
                    }
                }
            }
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

}
