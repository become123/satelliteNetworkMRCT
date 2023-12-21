#include "Tree.h"
#include "Graph.h"

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

    Tree::Tree(std::set<Graph::Edge> edgeSet){
        this->size = edgeSet.size()+1;
        nodes.resize(size);
        for(int i = 0; i < size; ++i){
            nodes[i] = new TreeNode(i);
        }
        //find center of the tree to be the root(using topology sort)
        std::vector<std::vector<int>> adjList(size); 
        std::vector<int> degree(size, 0);
        for(auto edge: edgeSet){
            adjList[edge.vertex1()].push_back(edge.vertex2());
            adjList[edge.vertex2()].push_back(edge.vertex1());
            degree[edge.vertex1()]++;
            degree[edge.vertex2()]++;
        }
        std::queue<int> q;
        std::vector<bool> added(size, false);
        for(int i = 0; i < size; ++i){
            if(degree[i] == 1){ //leaf node
                q.push(i);
            }
        }
        int cur = q.front();
        int cnt = 0;
        while(!q.empty()){
            int qSize = q.size();
            // std::cout<<"qSize is "<<qSize<<"\n";
            while(qSize--){
                cur = q.front();
                q.pop();
                for(auto v: adjList[cur]){
                    if(added[v] == false){ 
                        // std::cout<<"parent: "<<v<<", child: "<<cur<<"\n";
                        addEdge(v, cur);
                        cnt++;
                        added[cur] = true; // prevent adding edge in parent->child direction
                    }
                    if(--degree[v] == 1){
                        q.push(v);
                    }
                }
            }
            // std::cout<<"---------------------------------------------\n";
        }
        // std::cout<<"cnt is "<<cnt<<"\n";
        if(cnt != size-1){
            std::cout<<"cnt != size-1\n";
            exit(-1);
        }
        root = nodes[cur];
        // std::cout<<"root is "<<root->id<<"\n";
        buildLevelAndSubtreeSize();
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

    int Tree::getDegree(int id){
        return nodes[id]->degree;
    }

    int Tree::getLevel(int id){
        return nodes[id]->level;
    }

    int Tree::getSubtreeSize(int id){
        return nodes[id]->subtreeSize;
    }

    int Tree::getTreeDepth(){
        return treeDepth;
    }

    std::set<Graph::Edge> Tree::getEdgeSet(){
        std::set<Graph::Edge> edgeSet;
        for(int i = 0; i < size; ++i){
            for(auto child: nodes[i]->children){
                edgeSet.insert(Graph::Edge(i, child->id, 1));
            }
        }
        return edgeSet;
    }

    void Tree::addEdge(int p, int v){ //add edge from p to v, p is parent, v is child
        nodes[p]->children.push_back(nodes[v]);
        nodes[p]->degree++;
        nodes[v]->parent = nodes[p];
        nodes[v]->degree++;
    }

    Graph::Graph Tree::toGraph(){
        std::set<Graph::Edge> edgeSet = getEdgeSet();
        return Graph::Graph(size, edgeSet);
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
                    std::cout<<"maybe you forget to call buildLevelAndSubtreeSize()\n";
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
        treeDepth = 0;
        for(auto &node: nodes){
            treeDepth = std::max(treeDepth, node->level);
        }
    }
}