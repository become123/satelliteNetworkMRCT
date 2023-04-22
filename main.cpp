#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <fstream>
#include <sstream>
#include <map>
#include <utility>
#include "UtilFunction.h"
#include "ConvertTool.h"
#include "Graph.h"


const bool weighted = false;


// Main function
int main(int argc, char *argv[]) { 
    std::ifstream ifs(argv[1]);
    if (!ifs.is_open()) {
        std::cout << "Failed to open file.\n";
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> inputLines;
    std::string input;
    ConvertTool::satIdConversion translateTool;
    std::getline (ifs,input);
    if(!UtilFunction::isNumber(input)){
        std::cout<<"first line should be satellite count number!\n";
        exit(-1);
    }
    int satCount = std::stoi(input);//第一行是衛星數量
    // cout<<satCount<<"\n";
    while ( getline (ifs,input) ){
        inputLines.push_back(input);
    } 
       
    // Create the graph
    Graph::Graph satelliteNetworkGraph(satCount);
    for(std::string s: inputLines){
        std::vector<std::string> satRelation = UtilFunction::split(s,','); //satRelation的前兩個是衛星編號，最後一個是衛星間距離
        satelliteNetworkGraph.addEdge(translateTool.satIdToIndex(stoi(satRelation[0])), 
                                      translateTool.satIdToIndex(stoi(satRelation[1])), 
                                      stoi(satRelation[2]), 
                                      weighted);
    }

    // std::set<Graph::Edge> rst = satelliteNetworkGraph.randomSpanningTree();
    // std::cout << "Random spanning tree:\n";
    // std::cout<<"edge count: "<<rst.size()<<"\n";
    // for (Graph::Edge e : rst) {
    //     std::cout << translateTool.indexToSatId(e.from) << " " << translateTool.indexToSatId(e.to) << " " << e.weight << "\n";
    // }
    
    




    // Find N'
    std::cout<<"--------------------------------------------------------\nN':\n";
    std::vector<std::vector<int> > adjacencyMatrixN2(satCount, std::vector<int>(satCount,0));
    for (int i = 0; i < satelliteNetworkGraph.getVerticesCount(); i++) {
        std::vector<int> parent = satelliteNetworkGraph.shortestPathTree(i);

        for (int j = 0; j < satelliteNetworkGraph.getVerticesCount(); j++) {
            int cur = j;
            while(parent[cur] != -1){
                adjacencyMatrixN2[parent[cur]][cur]++;
                cur = parent[cur];
            }
        }
    }
    std::multimap<int, std::pair<int, int>> edgeTable;//(average weight, (edge from, edge to))
    for(int i = 0; i < satCount; ++i){
        for(int j = i; j < satCount; ++j){
            if(adjacencyMatrixN2[i][j] != 0){
                adjacencyMatrixN2[i][j] = (adjacencyMatrixN2[i][j] + adjacencyMatrixN2[j][i])/2; // get average of the two direction of the edge
                // cout<<translateTool.indexToSatId(i)<<"to"<<translateTool.indexToSatId(j)<<":"<<adjacencyMatrixN2[i][j]<<"\n";
                edgeTable.emplace(adjacencyMatrixN2[i][j],std::make_pair(translateTool.indexToSatId(i), translateTool.indexToSatId(j)));
            }
        }
    }
    for(auto i:edgeTable){
        // cout<<i.second.first<<"to"<<i.second.second<<":"<<i.first<<"\n";
        std::cout<<"("<<i.second.first<<","<<i.second.second<<")"<<"weight:"<<i.first<<"\n";
    }



    return 0;
}
