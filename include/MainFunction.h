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

}

#endif