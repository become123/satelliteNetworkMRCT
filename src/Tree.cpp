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

    TreeNode* Tree::getRoot(){
        return root;
    }

    TreeNode* Tree::getNode(int id){
        return nodes[id];
    }

    void Tree::addEdge(int u, int v){
        nodes[u]->children.push_back(nodes[v]);
        nodes[v]->parent = nodes[u];
    }

    void Tree::levelOrderTraversal(ConvertTool::satIdConversion &translateTool){
        std::queue<TreeNode*> q;
        q.push(root);
        int level = 0;
        while(!q.empty()){
            std::cout<<"Level "<<level++<<":\n---------------------------------------------\n";
            int levelSize = q.size();
            while(levelSize--){
                TreeNode* cur = q.front();
                q.pop();
                // std::cout<<translateTool.indexToSatId(cur->id)<<", ";
                std::cout<<translateTool.indexToSatId(cur->id)<<":(";
                for(auto child : cur->children){
                    std::cout<<" "<<translateTool.indexToSatId(child->id);
                    q.push(child);
                }
                std::cout<<"), ";
            }
            std::cout<<"\n";
        }
    }
}