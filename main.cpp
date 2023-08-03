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
    clock_t start, End;
    double cpu_time_used;
    start = clock();    

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

    for(int brokenLinkCnt = 5; brokenLinkCnt <= 50; brokenLinkCnt+=5){
        std::cout<<"\n___________________________________brokenLinkCnt: "<<brokenLinkCnt<<"__________________________________________\n";
        std::vector<int> edgeCount; //for calculate average value
        std::vector<double> avgShortestPathLength; //for calculate average value
        std::vector<int> diameter; //for calculate average value
        for(int times = 0; times < 500; ++times){
            Graph::Graph brokenGraph = satelliteNetworkGraph.getRandomDeleteEdgeGraph(brokenLinkCnt, translateTool);
            Graph::Graph g = brokenGraph.getGraphUsingBestDCMLTAndAddEdgesGreedily(3);  
            edgeCount.push_back(g.getEdgesCount());
            avgShortestPathLength.push_back(g.getAverageShortestPathLength());
            diameter.push_back(g.getDiameter());         
        }
        std::cout<<"avg Graph edge count: "<<UtilFunction::average(edgeCount)<<", ";
        std::cout<<"avg average shortest path length: "<<UtilFunction::average(avgShortestPathLength)<<", ";
        std::cout<<"avg diameter: "<<UtilFunction::average(diameter)<<"\n";
    }



    



    End = clock();
    cpu_time_used = ((double) (End - start)) / CLOCKS_PER_SEC;
    std::cout<<"cpu_time_used: "<<cpu_time_used<<"\n";
    return 0;
}
