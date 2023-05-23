#include "MainFunction.h"
#include <iostream>
#include <iomanip>

namespace MainFunction
{
    void getRandomSpanningTree_and_PrintDeletedEdge(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool){
        std::set<Graph::Edge> rst = satelliteNetworkGraph.randomSpanningTreeEdgeSet();
        std::set<Graph::Edge> notSelectedEdges = UtilFunction::difference(satelliteNetworkGraph.getEdgeSet(), rst);
        for(Graph::Edge e : notSelectedEdges){
            std::cout<<"("<<translateTool.indexToSatId(e.vertex1())<<","<<translateTool.indexToSatId(e.vertex2())<<")\n";
        }       
    }

    void getMinimumSpanningTree_and_PrintDeletedEdge(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool){
        std::set<Graph::Edge> mst = satelliteNetworkGraph.minimumSpanningTreeEdgeSet();
        std::set<Graph::Edge> notSelectedEdges = UtilFunction::difference(satelliteNetworkGraph.getEdgeSet(), mst);
        for(Graph::Edge e : notSelectedEdges){
            std::cout<<"("<<translateTool.indexToSatId(e.vertex1())<<","<<translateTool.indexToSatId(e.vertex2())<<")\n";
        }       
    }

    void getdegreeConstrainedRandomSpanningTree_and_PrintDeletedEdge(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool, int degreeConstrained){
        std::set<Graph::Edge> rst = satelliteNetworkGraph.degreeConstrainedRandomSpanningTreeEdgeSet(degreeConstrained);
        std::set<Graph::Edge> notSelectedEdges = UtilFunction::difference(satelliteNetworkGraph.getEdgeSet(), rst);
        for(Graph::Edge e : notSelectedEdges){
            std::cout<<"("<<translateTool.indexToSatId(e.vertex1())<<","<<translateTool.indexToSatId(e.vertex2())<<")\n";
        }       
    }

    void getdegreeConstrainedMinimumLevelTree_and_PrintDeletedEdge(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool,int rootId, int degreeConstrained){
        std::set<Graph::Edge> mlt = satelliteNetworkGraph.degreeConstrainedMinimumLevelTree(translateTool.satIdToIndex(rootId), degreeConstrained).getEdgeSet();
        std::set<Graph::Edge> notSelectedEdges = UtilFunction::difference(satelliteNetworkGraph.getEdgeSet(), mlt);
        for(Graph::Edge e : notSelectedEdges){
            std::cout<<"("<<translateTool.indexToSatId(e.vertex1())<<","<<translateTool.indexToSatId(e.vertex2())<<")\n";
        }
    }

    //印出以每一個衛星為root的degree constrained minimum level tree的平均最短路徑長度和最長最短路徑長度
    void printAllSat_minimumLevelTree_statistic(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool){
        std::vector<int> allSatId = translateTool.allSatId();
        std::vector<double> averageShortestPathLength;
        std::vector<int> maximumShortestPathLength;
        std::vector<int> treeDepths;
        for(auto satId: allSatId){
            Tree::Tree mlt = satelliteNetworkGraph.degreeConstrainedMinimumLevelTree(translateTool.satIdToIndex(satId), 3);
            Graph::Graph mltGraph(satelliteNetworkGraph.getVerticesCount(),mlt.getEdgeSet());
            std::cout<<"degree constrained minimum level tree of satellite "<<satId<<": ";
            std::cout<<"Tree depth:"<<mlt.getTreeDepth();
            std::cout<<", average shortest path length:";
            std::cout<<std::fixed<<std::setprecision(3)<<mltGraph.getAverageShortestPathLength();
            std::cout<<", maximum shortest path length:";
            std::cout<<mltGraph.getDiameter()<<"\n";
            averageShortestPathLength.push_back(mltGraph.getAverageShortestPathLength());
            maximumShortestPathLength.push_back(mltGraph.getDiameter());
            treeDepths.push_back(mlt.getTreeDepth());
        }    
        std::cout<<"average tree depth:";
        std::cout<<std::fixed<<std::setprecision(3)<<UtilFunction::average(treeDepths);
        std::cout<<", average average shortest path length:";
        std::cout<<std::fixed<<std::setprecision(3)<<UtilFunction::average(averageShortestPathLength);
        std::cout<<", average maximum shortest path length:";
        std::cout<<UtilFunction::average(maximumShortestPathLength)<<"\n";
    }

    //印出隨機生成的spanning tree的平均最短路徑長度和最長最短路徑長度
    void print_random_spanning_tree_statistic(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool){
        std::vector<int> allSatId = translateTool.allSatId();
        std::vector<double> averageShortestPathLength;
        std::vector<int> maximumShortestPathLength;
        std::vector<int> treeDepths;
        for(size_t i = 0; i < allSatId.size(); ++i){
            Tree::Tree rst = satelliteNetworkGraph.degreeConstrainedRandomSpanningTreeEdgeSet(3);
            Graph::Graph rstGraph = rst.toGraph();
            std::cout<<"degree constrained random spanning tree: ";
            std::cout<<"Tree depth:"<<rst.getTreeDepth();
            std::cout<<", average shortest path length:";
            std::cout<<std::fixed<<std::setprecision(3)<<rstGraph.getAverageShortestPathLength();
            std::cout<<", maximum shortest path length:";
            std::cout<<rstGraph.getDiameter()<<"\n";
            averageShortestPathLength.push_back(rstGraph.getAverageShortestPathLength());
            maximumShortestPathLength.push_back(rstGraph.getDiameter());   
            treeDepths.push_back(rst.getTreeDepth());    
        } 
        std::cout<<"average tree depth:";
        std::cout<<std::fixed<<std::setprecision(3)<<UtilFunction::average(treeDepths);
        std::cout<<", average average shortest path length:";
        std::cout<<std::fixed<<std::setprecision(3)<<UtilFunction::average(averageShortestPathLength);
        std::cout<<", average maximum shortest path length:";
        std::cout<<UtilFunction::average(maximumShortestPathLength)<<"\n";
    }
}