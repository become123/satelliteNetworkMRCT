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
            std::cout<<", diameter:";
            std::cout<<mltGraph.getDiameter()<<"\n";
            averageShortestPathLength.push_back(mltGraph.getAverageShortestPathLength());
            maximumShortestPathLength.push_back(mltGraph.getDiameter());
            treeDepths.push_back(mlt.getTreeDepth());
        }
        std::cout<<"average tree depth:";
        std::cout<<std::fixed<<std::setprecision(3)<<UtilFunction::average(treeDepths);
        std::cout<<", minimum tree depth:"<<UtilFunction::minimum(treeDepths);
        std::cout<<", maximum tree depth:"<<UtilFunction::maximum(treeDepths)<<"\n";

        std::cout<<"average average shortest path length:";
        std::cout<<std::fixed<<std::setprecision(3)<<UtilFunction::average(averageShortestPathLength);
        std::cout<<", minimum average shortest path length:"<<UtilFunction::minimum(averageShortestPathLength);
        std::cout<<", maximum average shortest path length:"<<UtilFunction::maximum(averageShortestPathLength)<<"\n";

        std::cout<<"average diameter:";
        std::cout<<UtilFunction::average(maximumShortestPathLength);
        std::cout<<", minimum diameter:"<<UtilFunction::minimum(maximumShortestPathLength);
        std::cout<<", maximum diameter:"<<UtilFunction::maximum(maximumShortestPathLength)<<"\n";
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
            std::cout<<", diameter:";
            std::cout<<rstGraph.getDiameter()<<"\n";
            averageShortestPathLength.push_back(rstGraph.getAverageShortestPathLength());
            maximumShortestPathLength.push_back(rstGraph.getDiameter());   
            treeDepths.push_back(rst.getTreeDepth());    
        } 
        std::cout<<"average tree depth:";
        std::cout<<std::fixed<<std::setprecision(3)<<UtilFunction::average(treeDepths);
        std::cout<<", minimum tree depth:"<<UtilFunction::minimum(treeDepths);
        std::cout<<", maximum tree depth:"<<UtilFunction::maximum(treeDepths)<<"\n";

        std::cout<<"average average shortest path length:";
        std::cout<<std::fixed<<std::setprecision(3)<<UtilFunction::average(averageShortestPathLength);
        std::cout<<", minimum average shortest path length:"<<UtilFunction::minimum(averageShortestPathLength);
        std::cout<<", maximum average shortest path length:"<<UtilFunction::maximum(averageShortestPathLength)<<"\n";

        std::cout<<"average diameter:";
        std::cout<<UtilFunction::average(maximumShortestPathLength);
        std::cout<<", minimum diameter:"<<UtilFunction::minimum(maximumShortestPathLength);
        std::cout<<", maximum diameter:"<<UtilFunction::maximum(maximumShortestPathLength)<<"\n";
    }

    //模擬部分ISL壞掉的情形，印出星網以各個衛星為root的degree constrained minimum level tree的生成情形
    void simulateISLbroken_DCMLT_spanning(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool){
        std::vector<int> allSatId = translateTool.allSatId();
        for(int brokenLinkCnt = 0; brokenLinkCnt <= 100; brokenLinkCnt+=5){
            std::vector<int> failCnts;
            int allFailCnt = 0;
            std::vector<double> averageShortestPathLengthDiff;
            for(int time =  0; time < 1000; ++time){ //模擬1000次
                Graph::Graph brokenGraph = satelliteNetworkGraph.getRandomDeleteEdgeGraph(brokenLinkCnt, translateTool);
                std::vector<double> averageShortestPathLength;       
                int failCnt = 0;
                for(auto satId: allSatId){
                    if(brokenGraph.canSpanDegreeConstrainedMinimumLevelTree(translateTool.satIdToIndex(satId), 3)){
                        Tree::Tree mlt = brokenGraph.degreeConstrainedMinimumLevelTree(translateTool.satIdToIndex(satId), 3);
                        Graph::Graph mltGraph(brokenGraph.getVerticesCount(),mlt.getEdgeSet());
                        // std::cout<<"degree constrained minimum level tree of satellite "<<satId<<": ";
                        // std::cout<<"Tree depth:"<<mlt.getTreeDepth();
                        // std::cout<<", average shortest path length:";
                        // std::cout<<std::fixed<<std::setprecision(3)<<mltGraph.getAverageShortestPathLength();
                        // std::cout<<", diameter:";
                        // std::cout<<mltGraph.getDiameter()<<"\n";
                        averageShortestPathLength.push_back(mltGraph.getAverageShortestPathLength());
                    }
                    else{
                        // std::cout<<"sat "<<satId<<" can't span degree constrained minimum level tree\n";
                        failCnt++;
                    }
                } 
                if(averageShortestPathLength.size() == 0){
                    allFailCnt++;
                    continue;
                }
                averageShortestPathLengthDiff.push_back(UtilFunction::maximum(averageShortestPathLength) - UtilFunction::minimum(averageShortestPathLength));
                failCnts.push_back(failCnt);
            }
            std::cout<<"broken link count, "<<brokenLinkCnt<<", ";
            std::cout<<"all fail count, "<<allFailCnt<<", ";
            std::cout<<"average shortest path length difference,";
            std::cout<<std::fixed<<std::setprecision(3)<<UtilFunction::average(averageShortestPathLengthDiff)<<", ";
            std::cout<<"average fail count, ";
            std::cout<<UtilFunction::average(failCnts)<<"\n";
        }        
    }
}