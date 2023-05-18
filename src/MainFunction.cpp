#include "MainFunction.h"

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
}