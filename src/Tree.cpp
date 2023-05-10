#include "Tree.h"

namespace Tree
{
    Tree::Tree(int rootId, int size){
        this->size = size;
        nodes.resize(size);
        for(int i = 0; i < size; ++i){
            nodes[i] = new TreeNode(i);
        }
        root = nodes[rootId];
    }

    Tree::~Tree(){
        for(int i = 0; i < size; ++i){
            delete nodes[i];
        }
    }
}