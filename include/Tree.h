#ifndef TREE
#define TREE
#include <vector>
#include <queue>
#include <iostream>
#include "ConvertTool.h"

namespace Tree
{
    class TreeNode {
    public:
        int id;
        int subtreeSize;
        TreeNode* parent;
        std::vector<TreeNode*> children;

        TreeNode(int x) : id(x), subtreeSize(0), parent(nullptr) {}
    };

    class Tree{
    private:
        TreeNode* root;
        std::vector<TreeNode*> nodes;
        int size;
    public:
        Tree(int rootId, int size);
        ~Tree();
        TreeNode* getRoot();
        TreeNode* getNode(int id);
        void addEdge(int u, int v);
        void levelOrderTraversal(ConvertTool::satIdConversion &translateTool);
    };
}

#endif

