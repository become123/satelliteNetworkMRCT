#include "Graph.h"
#include "DisjointSet.h"
#include "UtilFunction.h"

namespace Graph
{
    Edge:: Edge(int _from, int _to, int w) {
        from = _from;
        to = _to;
        weight = w;
    }

    int Graph::getVerticesCount(){
        return verticesCount;
    }

    std::set<Edge> Graph::getEdgeSet(){
        return edgeSet;
    }

    bool Edge::operator<(const Edge& other) const {
        if (weight != other.weight) {
            return weight < other.weight;
        }
        if (from != other.from) {
            return from < other.from;
        }
        return to < other.to;
    }

    Graph::Graph(int v) {
        verticesCount = v;
        adjList.resize(verticesCount);
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
            if(dsSet.Union(edge.from, edge.to)){
                rst.insert(edge);
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
            if(dsSet.Union(edge.from, edge.to)){
                // std::cout<<"edge: "<<edge.from<<" "<<edge.to<<" "<<edge.weight<<"\n";
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
        std::multimap<int, std::pair<int, int>> edgeTable;//(average weight, (edge from, edge to))
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
        return mlt;
    }

    Tree::Tree Graph::degreeConstrainedMinimumLevelTree(int src, int degreeConstraint){ //BFS建出minimumLevelTree，限制每個node的最大degree
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
                    if(mlt.getNode(u)->degree < degreeConstraint && dsSet.Union(u, v)){
                        mlt.addEdge(u, v);
                        q.push(v);
                    }
                }
            }
        }
        return mlt;
    }    

}