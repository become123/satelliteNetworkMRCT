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

    //找出所有衛星為root的DCRST中，路由效能最好的那一個，並以此DCRST加入其他edge(有先依照tree的拓譜排序)形成最終的星網拓普
    void getGraphUsingBestDCMLTAndAddSortedEdges(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool){
        // std::cout<<"satelliteNetworkGraph.getEdgesCount():"<<satelliteNetworkGraph.getEdgesCount()<<"\n";
        // Tree::Tree mlt = satelliteNetworkGraph.degreeConstrainedMinimumLevelTree(translateTool.satIdToIndex(101), 3);
        Tree::Tree mlt = satelliteNetworkGraph.bestDegreeConstrainedMinimumLevelTree(3);
        std::cout<<"root id:"<<translateTool.indexToSatId(mlt.getRoot()->id)<<"\n---------------------------------------\n";
        mlt.buildLevelAndSubtreeSize();
        std::set<Graph::Edge> notSelectedEdges = UtilFunction::difference(satelliteNetworkGraph.getEdgeSet(), mlt.getEdgeSet());
        std::vector<Graph::Edge> notSelectedEdgesVector(notSelectedEdges.begin(), notSelectedEdges.end());
        std::sort(notSelectedEdgesVector.begin(), notSelectedEdgesVector.end(), [&mlt](Graph::Edge e1, Graph::Edge e2){
            int e1Degree = mlt.getNode(e1.vertex1())->degree + mlt.getNode(e1.vertex2())->degree;
            int e2Degree = mlt.getNode(e2.vertex1())->degree + mlt.getNode(e2.vertex2())->degree;
            int e1Level = mlt.getNode(e1.vertex1())->level + mlt.getNode(e1.vertex2())->level;
            int e2Level = mlt.getNode(e2.vertex1())->level + mlt.getNode(e2.vertex2())->level;
            int e1SubtreeSize = mlt.getNode(e1.vertex1())->subtreeSize + mlt.getNode(e1.vertex2())->subtreeSize;
            int e2SubtreeSize = mlt.getNode(e2.vertex1())->subtreeSize + mlt.getNode(e2.vertex2())->subtreeSize;
            // int treeDepth = mlt.getTreeDepth();
            if(e1Degree < e2Degree){
                return true;
            }
            else{
                return false;
            }
            // if(abs(treeDepth-e1Level) < abs(treeDepth-e2Level)){
            //     return true;
            // }
            if(e1Level > e2Level){
                return true;
            }        
            else{
                return false;
            }
            if(e1SubtreeSize > e2SubtreeSize){
                return true;
            }
            return false;
        });
        // for(Graph::Edge e : notSelectedEdgesVector){
        //     std::cout<<"("<<translateTool.indexToSatId(e.vertex1())<<","<<translateTool.indexToSatId(e.vertex2())<<"): ";
        //     std::cout<<"degree: "<<mlt.getNode(e.vertex1())->degree + mlt.getNode(e.vertex2())->degree<<"( ";
        //     std::cout<<"v1Degree: "<<mlt.getNode(e.vertex1())->degree<<", ";
        //     std::cout<<"v2Degree: "<<mlt.getNode(e.vertex2())->degree<<") ";
        //     std::cout<<"level: "<<mlt.getNode(e.vertex1())->level + mlt.getNode(e.vertex2())->level<<"( ";
        //     std::cout<<"v1Level: "<<mlt.getNode(e.vertex1())->level<<", ";
        //     std::cout<<"v2Level: "<<mlt.getNode(e.vertex2())->level<<") ";
        //     std::cout<<"subtreeSize: "<<mlt.getNode(e.vertex1())->subtreeSize + mlt.getNode(e.vertex2())->subtreeSize<<"( ";
        //     std::cout<<"v1SubtreeSize: "<<mlt.getNode(e.vertex1())->subtreeSize<<", ";
        //     std::cout<<"v2SubtreeSize: "<<mlt.getNode(e.vertex2())->subtreeSize<<")\n";
        // }
        Graph::Graph mltGraph = mlt.toGraph(); 
        std::cout<<"before:\n";
        std::cout<<"Graph edge count: "<<mltGraph.getEdgesCount()<<", ";
        std::cout<<"average shortest path length: "<<mltGraph.getAverageShortestPathLength()<<", ";
        std::cout<<"diameter: "<<mltGraph.getDiameter()<<"\n";
        // std::cout<<"degree sequence: ";
        // for(int i = 0; i < (int)mltGraph.getVerticesCount(); ++i){
        //     std::cout<<mltGraph.getDegree(i)<<" ";
        // } 
        // std::cout<<"\n";   
        int i = 0;
        while(mltGraph.getEdgesCount() < 187){
            // std::cout<<"i = "<<i<<":";
            if(mltGraph.getDegree(notSelectedEdgesVector[i].vertex1()) > 2 || mltGraph.getDegree(notSelectedEdgesVector[i].vertex2()) > 2){
                ++i;
                // std::cout<<"skip\n";
                if(i == (int)notSelectedEdgesVector.size()){
                    std::cout<<"**********************mltGraph EdgesCount:"<<mltGraph.getEdgesCount()<<", reach limit!**********************\n";
                    break;
                }            
                continue;
            }
            // std::cout<<"add\n";
            mltGraph.addEdge(notSelectedEdgesVector[i].vertex1(), notSelectedEdgesVector[i].vertex2(), 1, true);
            ++i;
            if(i == (int)notSelectedEdgesVector.size()){
                std::cout<<"mltGraph.getEdgesCount():"<<mltGraph.getEdgesCount()<<"\n";
                break;
            }
        }
        std::cout<<"after:\n";
        std::cout<<"Graph edge count: "<<mltGraph.getEdgesCount()<<", ";
        std::cout<<"average shortest path length: "<<mltGraph.getAverageShortestPathLength()<<", ";
        std::cout<<"diameter: "<<mltGraph.getDiameter()<<"\n";
        // std::cout<<"degree sequence: ";
        // for(int i = 0; i < (int)mltGraph.getVerticesCount(); ++i){
        //     std::cout<<mltGraph.getDegree(i)<<" ";
        // }
        // std::cout<<"\n";
    }

    //找出所有衛星為root的DCRST中，路由效能最好的那一個，進行local search後以此DCRST加入其他edge(有先依照tree的拓譜排序)形成最終的星網拓普
    void getGraphUsingBestDCMLTwithLocalSearchAndAddSortedEdges(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool){
        // std::cout<<"satelliteNetworkGraph.getEdgesCount():"<<satelliteNetworkGraph.getEdgesCount()<<"\n";
        // Tree::Tree dcmlt = satelliteNetworkGraph.degreeConstrainedMinimumLevelTree(translateTool.satIdToIndex(101), 3);
        Tree::Tree dcmlt = satelliteNetworkGraph.bestDegreeConstrainedMinimumLevelTree(3);
        std::cout<<"root id:"<<translateTool.indexToSatId(dcmlt.getRoot()->id);
        dcmlt.buildLevelAndSubtreeSize();
        Graph::Graph dcmltGraph = dcmlt.toGraph();
        std::set<Graph::Edge> notSelectedEdgeSet = UtilFunction::difference(satelliteNetworkGraph.getEdgeSet(), dcmltGraph.getEdgeSet());
        std::cout<<", avg shortest path length: "<<dcmltGraph.getAverageShortestPathLength()<<", diameter:"<<dcmltGraph.getDiameter()<<"\n\n";
        int changeCnt = dcmltGraph.treeGraphLocalSearch(dcmlt, notSelectedEdgeSet, 3);
        std::cout<<"change "<<changeCnt<<" edges after local search\n\n";
        Tree::Tree dcmlt2(dcmltGraph.getEdgeSet()); 
        std::cout<<"root id:"<<translateTool.indexToSatId(dcmlt2.getRoot()->id);
        std::cout<<", avg shortest path length: "<<dcmltGraph.getAverageShortestPathLength()<<", diameter:"<<dcmltGraph.getDiameter()<<"\n";

        std::set<Graph::Edge> notSelectedEdges = UtilFunction::difference(satelliteNetworkGraph.getEdgeSet(), dcmlt2.getEdgeSet());
        std::vector<Graph::Edge> notSelectedEdgesVector(notSelectedEdges.begin(), notSelectedEdges.end());
        std::sort(notSelectedEdgesVector.begin(), notSelectedEdgesVector.end(), [&dcmlt2](Graph::Edge e1, Graph::Edge e2){
            int e1Degree = dcmlt2.getNode(e1.vertex1())->degree + dcmlt2.getNode(e1.vertex2())->degree;
            int e2Degree = dcmlt2.getNode(e2.vertex1())->degree + dcmlt2.getNode(e2.vertex2())->degree;
            int e1Level = dcmlt2.getNode(e1.vertex1())->level + dcmlt2.getNode(e1.vertex2())->level;
            int e2Level = dcmlt2.getNode(e2.vertex1())->level + dcmlt2.getNode(e2.vertex2())->level;
            int e1SubtreeSize = dcmlt2.getNode(e1.vertex1())->subtreeSize + dcmlt2.getNode(e1.vertex2())->subtreeSize;
            int e2SubtreeSize = dcmlt2.getNode(e2.vertex1())->subtreeSize + dcmlt2.getNode(e2.vertex2())->subtreeSize;
            // int treeDepth = dcmlt2.getTreeDepth();
            if(e1Degree < e2Degree){
                return true;
            }
            else{
                return false;
            }
            // if(abs(treeDepth-e1Level) < abs(treeDepth-e2Level)){
            //     return true;
            // }
            if(e1Level > e2Level){
                return true;
            }        
            else{
                return false;
            }
            if(e1SubtreeSize > e2SubtreeSize){
                return true;
            }
            return false;
        });
        // for(Graph::Edge e : notSelectedEdgesVector){
        //     std::cout<<"("<<translateTool.indexToSatId(e.vertex1())<<","<<translateTool.indexToSatId(e.vertex2())<<"): ";
        //     std::cout<<"degree: "<<dcmlt2.getNode(e.vertex1())->degree + dcmlt2.getNode(e.vertex2())->degree<<"( ";
        //     std::cout<<"v1Degree: "<<dcmlt2.getNode(e.vertex1())->degree<<", ";
        //     std::cout<<"v2Degree: "<<dcmlt2.getNode(e.vertex2())->degree<<") ";
        //     std::cout<<"level: "<<dcmlt2.getNode(e.vertex1())->level + dcmlt2.getNode(e.vertex2())->level<<"( ";
        //     std::cout<<"v1Level: "<<dcmlt2.getNode(e.vertex1())->level<<", ";
        //     std::cout<<"v2Level: "<<dcmlt2.getNode(e.vertex2())->level<<") ";
        //     std::cout<<"subtreeSize: "<<dcmlt2.getNode(e.vertex1())->subtreeSize + dcmlt2.getNode(e.vertex2())->subtreeSize<<"( ";
        //     std::cout<<"v1SubtreeSize: "<<dcmlt2.getNode(e.vertex1())->subtreeSize<<", ";
        //     std::cout<<"v2SubtreeSize: "<<dcmlt2.getNode(e.vertex2())->subtreeSize<<")\n";
        // }
        std::cout<<"------------------------------------------\nbefore add edge:\n";
        std::cout<<"Graph edge count: "<<dcmltGraph.getEdgesCount()<<", ";
        std::cout<<"average shortest path length: "<<dcmltGraph.getAverageShortestPathLength()<<", ";
        std::cout<<"diameter: "<<dcmltGraph.getDiameter()<<"\n";
        // std::cout<<"degree sequence: ";
        // for(int i = 0; i < (int)dcmltGraph.getVerticesCount(); ++i){
        //     std::cout<<dcmltGraph.getDegree(i)<<" ";
        // } 
        // std::cout<<"\n";   
        int i = 0;
        while(dcmltGraph.getEdgesCount() < 200){
            // std::cout<<"i = "<<i<<":";
            if(dcmltGraph.getDegree(notSelectedEdgesVector[i].vertex1()) > 2 || dcmltGraph.getDegree(notSelectedEdgesVector[i].vertex2()) > 2){
                ++i;
                // std::cout<<"skip\n";
                if(i == (int)notSelectedEdgesVector.size()){
                    std::cout<<"**********************dcmltGraph EdgesCount:"<<dcmltGraph.getEdgesCount()<<", reach limit!**********************\n";
                    break;
                }            
                continue;
            }
            // std::cout<<"add\n";
            dcmltGraph.addEdge(notSelectedEdgesVector[i].vertex1(), notSelectedEdgesVector[i].vertex2(), 1, true);
            ++i;
            if(i == (int)notSelectedEdgesVector.size()){
                std::cout<<"dcmltGraph.getEdgesCount():"<<dcmltGraph.getEdgesCount()<<"\n";
                break;
            }
        }
        std::cout<<"after:\n";
        std::cout<<"Graph edge count: "<<dcmltGraph.getEdgesCount()<<", ";
        std::cout<<"average shortest path length: "<<dcmltGraph.getAverageShortestPathLength()<<", ";
        std::cout<<"diameter: "<<dcmltGraph.getDiameter()<<"\n";
        // std::cout<<"degree sequence: ";
        // for(int i = 0; i < (int)dcmltGraph.getVerticesCount(); ++i){
        //     std::cout<<dcmltGraph.getDegree(i)<<" ";
        // }
        // std::cout<<"\n";
    } 

    //找出所有衛星為root的DCRST中，路由效能最好的那一個，進行local search後(後來註解掉了)以此DCRST加入其他edge(greedy追求最佳avg shortest path)形成最終的星網拓普
    void getGraphUsingBestDCMLTwithLocalSearchAndAddEdgesGreedily(Graph::Graph& satelliteNetworkGraph, ConvertTool::satIdConversion &translateTool){
        // std::cout<<"satelliteNetworkGraph.getEdgesCount():"<<satelliteNetworkGraph.getEdgesCount()<<"\n";
        // Tree::Tree dcmltBeforeLocalSearch = satelliteNetworkGraph.degreeConstrainedMinimumLevelTree(translateTool.satIdToIndex(101), 3);
        Tree::Tree dcmltBeforeLocalSearch = satelliteNetworkGraph.bestDegreeConstrainedMinimumLevelTree(3); //先獲得以所有衛星為root的DCRST中，路由效能最好的那一個
        // dcmltBeforeLocalSearch.levelOrderTraversal(translateTool);
        Graph::Graph dcmltGraph = dcmltBeforeLocalSearch.toGraph(); //轉成graph class

        std::cout<<"best dcmlt root id:"<<translateTool.indexToSatId(dcmltBeforeLocalSearch.getRoot()->id)<<"\n"; //印出root id
        // std::cout<<"avg shortest path length: "<<dcmltGraph.getAverageShortestPathLength()<<", diameter:"<<dcmltGraph.getDiameter()<<"\n\n"; //印出avg shortest path length和diameter
        std::set<Graph::Edge> notSelectedEdgeSet = UtilFunction::difference(satelliteNetworkGraph.getEdgeSet(), dcmltGraph.getEdgeSet()); //找出沒有被選到的edge
        // int changeCnt = dcmltGraph.treeGraphLocalSearch(dcmltBeforeLocalSearch, notSelectedEdgeSet, 3); //進行local search
        // std::cout<<"change "<<changeCnt<<" edges after local search\n\n"; //印出local search後改變的edge數量
        // Tree::Tree dcmltAfterLocalSearch(dcmltGraph.getEdgeSet());  //將local search後的graph轉成tree
        // std::cout<<"best dcmlt root id:"<<translateTool.indexToSatId(dcmltAfterLocalSearch.getRoot()->id); //印出root id
        // std::cout<<", avg shortest path length: "<<dcmltGraph.getAverageShortestPathLength()<<", diameter:"<<dcmltGraph.getDiameter()<<"\n"; //印出avg shortest path length和diameter

        /*印出加入edge之前的數據*/
        // std::cout<<"------------------------------------------\n";
        std::cout<<"before add edge:\n";
        std::cout<<"Graph edge count: "<<dcmltGraph.getEdgesCount()<<", ";
        std::cout<<"average shortest path length: "<<dcmltGraph.getAverageShortestPathLength()<<", ";
        std::cout<<"diameter: "<<dcmltGraph.getDiameter()<<"\n";
  
        // int minDiameter = dcmltGraph.getDiameter(); //
        double minAvgShortestPathLength = dcmltGraph.getAverageShortestPathLength();
        while(dcmltGraph.getEdgesCount() < 200){ //不斷加入當前可以使avg shortest path有最佳提升的edge，直到edge數量達到特定數量
            Graph::Edge bestEdge(-1, -1, -1);
            for (std::set<Graph::Edge>::iterator it = notSelectedEdgeSet.begin(); it != notSelectedEdgeSet.end();){
                if(dcmltGraph.getDegree(it->vertex1()) > 2 || dcmltGraph.getDegree(it->vertex2()) > 2){
                    it = notSelectedEdgeSet.erase(it);// because if adding this edge will cause graph node degree > 3
                    continue;
                }
                dcmltGraph.addEdge(it->vertex1(), it->vertex2(), 1, true);
                // if(dcmltGraph.getDiameter() < minDiameter){
                //     minDiameter = dcmltGraph.getDiameter();
                //     minAvgShortestPathLength = dcmltGraph.getAverageShortestPathLength();
                //     bestEdge = *it;
                //     std::cout<<"find better diameter,";
                //     std::cout<<"average shortest path length: "<<dcmltGraph.getAverageShortestPathLength()<<", ";
                //     std::cout<<"diameter: "<<dcmltGraph.getDiameter()<<"\n";
                // }
                // else if(dcmltGraph.getDiameter() == minDiameter){
                    if(dcmltGraph.getAverageShortestPathLength() < minAvgShortestPathLength){
                        // minDiameter = dcmltGraph.getDiameter();
                        minAvgShortestPathLength = dcmltGraph.getAverageShortestPathLength();
                        bestEdge = *it;
                        // std::cout<<"find better avg shortest path length,";
                        // std::cout<<"average shortest path length: "<<dcmltGraph.getAverageShortestPathLength()<<", ";
                        // std::cout<<"diameter: "<<dcmltGraph.getDiameter()<<"\n";                        
                    }
                // }
                dcmltGraph.deleteEdge(it->vertex1(), it->vertex2());
                ++it;
            }
            if(bestEdge.vertex1() == -1){ //如果沒有找到可以使avg shortest path有提升的edge，則停止加入edge
                std::cout<<"**********************dcmltGraph EdgesCount:"<<dcmltGraph.getEdgesCount()<<", reach limit!**********************\n";
                break;
            }
            dcmltGraph.addEdge(bestEdge.vertex1(), bestEdge.vertex2(), 1, true); //加入最佳的edge
            // std::cout<<"-----------------add edge: "<<bestEdge.vertex1()<<" "<<bestEdge.vertex2()<<"------------------\n";
            notSelectedEdgeSet.erase(bestEdge); //將加入的edge從notSelectedEdgeSet中刪除
            // if(dcmltGraph.getEdgesCount() == 140){
            //     std::cout<<"after:\n";
            //     std::cout<<"Graph edge count: "<<dcmltGraph.getEdgesCount()<<", ";
            //     std::cout<<"average shortest path length: "<<dcmltGraph.getAverageShortestPathLength()<<", ";
            //     std::cout<<"diameter: "<<dcmltGraph.getDiameter()<<"\n";                
            // }
            // if(dcmltGraph.getEdgesCount() == 148){
            //     std::cout<<"after:\n";
            //     std::cout<<"Graph edge count: "<<dcmltGraph.getEdgesCount()<<", ";
            //     std::cout<<"average shortest path length: "<<dcmltGraph.getAverageShortestPathLength()<<", ";
            //     std::cout<<"diameter: "<<dcmltGraph.getDiameter()<<"\n";                
            // } 
            // if(dcmltGraph.getEdgesCount() == 187){
            //     std::cout<<"after:\n";
            //     std::cout<<"Graph edge count: "<<dcmltGraph.getEdgesCount()<<", ";
            //     std::cout<<"average shortest path length: "<<dcmltGraph.getAverageShortestPathLength()<<", ";
            //     std::cout<<"diameter: "<<dcmltGraph.getDiameter()<<"\n";                
            // }                           
        }

        /*印出加入edge之後的數據*/
        std::cout<<"after:\n";
        std::cout<<"Graph edge count: "<<dcmltGraph.getEdgesCount()<<", ";
        std::cout<<"average shortest path length: "<<dcmltGraph.getAverageShortestPathLength()<<", ";
        std::cout<<"diameter: "<<dcmltGraph.getDiameter()<<"\n";
        // std::cout<<"degree sequence: ";
        // for(int i = 0; i < (int)dcmltGraph.getVerticesCount(); ++i){
        //     std::cout<<dcmltGraph.getDegree(i)<<" ";
        // }
        // std::cout<<"\n";
    }        
}