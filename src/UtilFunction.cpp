#include "UtilFunction.h"


namespace UtilFunction
{
    bool doubleEqual(double a, double b, double epsilon)//判斷兩個double是否相等
    {
        return std::abs(a - b) < epsilon;
    }

    std::vector<std::string> split(std::string s, char delim)//將string根據delim做切割的函式
    {
        std::vector<std::string> result;
        std::stringstream ss(s);
        std::string item;

        while (std::getline(ss, item, delim))
        {
            result.push_back(item);
        }

        return result;
    }

    bool isNumber(std::string str){//判斷字串是不是數字
        for (char c : str){
            if (!isdigit(c)){
                return false;
            }
        }
        return true;
    }

    int getRandomInt(int min, int max){//取得min~max之間的隨機數
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }


    std::set<Graph::Edge> difference(const std::set<Graph::Edge>& s1, const std::set<Graph::Edge>& s2) { //計算s1-s2
        std::set<Graph::Edge> result;
        std::set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(result, result.begin()));
        return result;
    }

    void placeOptimalEdgeLast(std::vector<Graph::Edge>& notSelectedEdges, const std::vector<std::pair<int, std::pair<int, int>>>& nodeInfo) { //將最適合的邊放到最後一個
        int lastIndex = notSelectedEdges.size() - 1;
        int selectedIndex = lastIndex; // 預設最後一個元素為最適合的

        for (int i = 0; i < lastIndex; ++i) {
            Graph::Edge e1 = notSelectedEdges[i];
            Graph::Edge e2 = notSelectedEdges[selectedIndex];

            int u1 = e1.vertex1();
            int v1 = e1.vertex2();
            int u2 = e2.vertex1();
            int v2 = e2.vertex2();

            int e1DegreeSum = nodeInfo[u1].first + nodeInfo[v1].first;
            int e2DegreeSum = nodeInfo[u2].first + nodeInfo[v2].first;
            if (e1DegreeSum != e2DegreeSum) {
                if (e1DegreeSum < e2DegreeSum) {
                    selectedIndex = i;
                }
                continue;
            }

            int e1SubtreeSizeSum = nodeInfo[u1].second.second + nodeInfo[v1].second.second;
            int e2SubtreeSizeSum = nodeInfo[u2].second.second + nodeInfo[v2].second.second;
            if (e1SubtreeSizeSum != e2SubtreeSizeSum) {
                if (e1SubtreeSizeSum > e2SubtreeSizeSum) {
                    selectedIndex = i;
                }
                continue;
            }            

            int e1LevelSum = nodeInfo[u1].second.first + nodeInfo[v1].second.first;
            int e2LevelSum = nodeInfo[u2].second.first + nodeInfo[v2].second.first;
            if (e1LevelSum != e2LevelSum) {
                if (e1LevelSum > e2LevelSum) {
                    selectedIndex = i;
                }
                continue;
            }
        }

        // 將最適合的邊與最後一個元素交換
        std::swap(notSelectedEdges[selectedIndex], notSelectedEdges[lastIndex]);
    }
}
