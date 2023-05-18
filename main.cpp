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
#include "MainFunction.h"
#include "Tree.h"


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
    
    
    std::vector<int> allSatId = translateTool.allSatId();
    // for(auto satId: allSatId){
    //     Graph::Graph mltGraph(satelliteNetworkGraph.getVerticesCount(),satelliteNetworkGraph.degreeConstrainedMinimumLevelTree(translateTool.satIdToIndex(satId), 3).getEdgeSet());
    //     std::cout<<"degree constrained minimum level tree of satellite "<<satId<<" average shortest path length:";
    //     std::cout<<std::fixed<<std::setprecision(3)<<mltGraph.getAverageShortestPathLength();
    //     std::cout<<", maximum shortest path length:";
    //     std::cout<<mltGraph.getMaximumShortestPathLength()<<"\n";
    // }

    for(size_t i = 0; i < allSatId.size(); ++i){
        Graph::Graph rstGraph(satelliteNetworkGraph.getVerticesCount(),satelliteNetworkGraph.degreeConstrainedRandomSpanningTreeEdgeSet(3));
        std::cout<<"degree constrained random spanning tree of satellite average shortest path length:";
        std::cout<<std::fixed<<std::setprecision(3)<<rstGraph.getAverageShortestPathLength();
        std::cout<<", maximum shortest path length:";
        std::cout<<rstGraph.getMaximumShortestPathLength()<<"\n";        
    }


    




    return 0;
}
