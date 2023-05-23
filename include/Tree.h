#ifndef TREE
#define TREE
#include <vector>
#include <queue>
#include <iostream>
#include <set>
#include "ConvertTool.h"
namespace Graph{
    class Edge;
    class Graph;
}

namespace Tree
{
    class TreeNode {
    public:
        int id;
        int level;
        int degree;
        int subtreeSize;
        TreeNode* parent;
        std::vector<TreeNode*> children;

        TreeNode(int x) : id(x), level(-1),degree(0), subtreeSize(-1), parent(nullptr) {}
    };

    class Tree{
    private:
        TreeNode* root;
        std::vector<TreeNode*> nodes;
        int size;
        int treeDepth;
        void buildLevelAndSubtreeSize(TreeNode* root);
    public:
        Tree(int rootId, int size);
        Tree(std::set<Graph::Edge> edgeSet);
        ~Tree();
        TreeNode* getRoot();
        TreeNode* getNode(int id);
        int getTreeDepth();
        std::set<Graph::Edge> getEdgeSet();
        void addEdge(int p, int v); //add edge from p to v, p is parent, v is child
        Graph::Graph toGraph();
        void levelOrderTraversal(ConvertTool::satIdConversion &translateTool); //print level order traversal of the tree
        void buildLevelAndSubtreeSize();
    };
}

#endif

