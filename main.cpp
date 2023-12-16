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


    std::map<int,std::vector<double>> avgShortestPathLengthRecord; //for calculate average value
    std::map<int,std::vector<int>> diameterRecord; //for calculate average value
    for(int times = 0; times < 3000; ++times){
        Graph::Graph brokenGraph = satelliteNetworkGraph.getRandomDeleteEdgeGraph(11, translateTool);
        Graph::Graph g = brokenGraph.getGraphUsingDCRSTAndAddEdgesGreedily(3, 1000, avgShortestPathLengthRecord, diameterRecord);  
    }   
    for(auto &[edgeCount, avgShortestPathLength]: avgShortestPathLengthRecord){
        std::cout<<edgeCount<<": ";
        double sum = 0;
        for(double d: avgShortestPathLength){
            sum += d;
        }
        std::cout<<"cnt:"<<avgShortestPathLength.size()<<", Avg :  "<<sum/avgShortestPathLength.size()<<"\n";
    }
    std::cout<<"----------------------------------------\n";
    for(auto &[edgeCount, diameter]: diameterRecord){
        std::cout<<edgeCount<<": ";
        double sum = 0;
        for(double d: diameter){
            sum += d;
        }
        std::cout<<"cnt:"<<diameter.size()<<", Avg :  "<<sum/diameter.size()<<"\n";
    }



    



    End = clock();
    cpu_time_used = ((double) (End - start)) / CLOCKS_PER_SEC;
    std::cout<<"cpu_time_used: "<<cpu_time_used<<"\n";
    return 0;
}
