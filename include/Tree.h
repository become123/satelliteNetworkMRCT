#ifndef TREE
#define TREE
#include <vector>
#include <queue>
#include <iostream>
#include <set>
#include "ConvertTool.h"
namespace Graph{
    class Edge;
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
        void buildLevelAndSubtreeSize(TreeNode* root);
    public:
        Tree(int rootId, int size);
        Tree(std::set<Graph::Edge> edgeSet);
        ~Tree();
        TreeNode* getRoot();
        TreeNode* getNode(int id);
        void addEdge(int p, int v); //add edge from p to v, p is parent, v is child
        void levelOrderTraversal(ConvertTool::satIdConversion &translateTool); //print level order traversal of the tree
        void buildLevelAndSubtreeSize();
    };
}

#endif

