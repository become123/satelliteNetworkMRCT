#ifndef MAIN_FUNCTION
#define MAIN_FUNCTION
#include "Graph.h"
#include "ConvertTool.h"
#include "UtilFunction.h"


namespace MainFunction
{
    void getRandomSpanningTree_and_PrintDeletedEdge(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool);

    void getMinimumSpanningTree_and_PrintDeletedEdge(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool);

    void getdegreeConstrainedRandomSpanningTree_and_PrintDeletedEdge(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool, int degreeConstrained);

    void getdegreeConstrainedMinimumLevelTree_and_PrintDeletedEdge(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool,int rootId, int degreeConstrained);  

    //印出以每一個衛星為root的degree constrained minimum level tree的平均最短路徑長度和最長最短路徑長度
    void printAllSat_minimumLevelTree_statistic(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool);

    //印出隨機生成的spanning tree的平均最短路徑長度和最長最短路徑長度
    void print_random_spanning_tree_statistic(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool);

    //模擬部分ISL壞掉的情形，印出星網以各個衛星為root的degree constrained minimum level tree的生成情形
    void simulateISLbroken_DCMLT_spanning(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool);

    //找出所有衛星為root的DCRST中，路由效能最好的那一個，並以此DCRST加入其他edge形成最終的星網拓普
    void getGraphUsingBestDCMLT(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool);

    //找出所有衛星為root的DCRST中，路由效能最好的那一個，進行local search後以此DCRST加入其他edge形成最終的星網拓普
    void getGraphUsingBestDCMLTwithLocalSearch(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool);
}

#endif