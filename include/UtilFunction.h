#ifndef UTIL_FUNCTION
#define UTIL_FUNCTION
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <set>
#include <algorithm>
#include "Graph.h"



namespace UtilFunction
{
    std::vector<std::string> split(std::string s, char delim);//將string根據delim做切割的函式

    bool isNumber(std::string str);//判斷字串是不是數字

    int getRandomInt(int min, int max);//取得min~max(包含)之間的隨機數

    double average(const std::vector<int>& v); //計算vector<int>的平均值

    std::set<Graph::Edge> difference(const std::set<Graph::Edge>& s1, const std::set<Graph::Edge>& s2);//計算s1-s2
}


#endif