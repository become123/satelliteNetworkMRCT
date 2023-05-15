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

    void Tree::addEdge(int p, int v){ //add edge from p to v
        nodes[p]->children.push_back(nodes[v]);
        nodes[p]->degree++;
        nodes[v]->parent = nodes[p];
        nodes[v]->degree++;
    }

    void Tree::levelOrderTraversal(ConvertTool::satIdConversion &translateTool){ //print level order traversal of the tree
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
                if(cur->level != level-1){
                    std::cout<<"level error\n";
                    exit(-1);
                }                
                std::cout<<translateTool.indexToSatId(cur->id)<<", subtreeSize:"<<cur->subtreeSize<<", degree:"<<cur->degree<<", children:(";
                for(auto child : cur->children){
                    std::cout<<" "<<translateTool.indexToSatId(child->id);
                    q.push(child);
                }
                std::cout<<")\n";
            }
            std::cout<<"\n";
        }
    }

    void Tree::buildLevelAndSubtreeSize(TreeNode* root){
        if(root == nullptr){
            std::cout<<"root is nullptr\n";
            return;
        }
        if(root->parent == nullptr){
            root->level = 0;
        }
        else{
            root->level = root->parent->level + 1;
        }
        root->subtreeSize = 1;
        for(auto child : root->children){
            buildLevelAndSubtreeSize(child);
            root->subtreeSize += child->subtreeSize;
        }
    }

    void Tree::buildLevelAndSubtreeSize(){
        this->buildLevelAndSubtreeSize(root);
    }
}