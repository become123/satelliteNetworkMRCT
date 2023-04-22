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
        std::vector<int> dist(verticesCount, std::numeric_limits<int>::max());
        std::vector<int> parent(verticesCount, -1);
        std::vector<bool> visited(verticesCount, false);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

        pq.push(std::make_pair(0, src));
        dist[src] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            if(visited[u]){// // pq may have duplicated element
                continue;
            }

            visited[u] = true;

            for (auto &[to, edge] : adjList[u]) {
                int v = to;
                int weight = edge.weight;

                if (!visited[v] && dist[v] > dist[u] + weight) {//relax
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    // cout<<"insert (dist: "<<dist[v]<<", id: "<<v<<")\n";
                    pq.push(std::make_pair(dist[v], v));// pq may have duplicated element. better way is to use decrease key
                }
            }
        }
        return parent;
    }

    std::set<Edge> Graph::randomSpanningTree(){
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
}