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
    bool doubleEqual(double a, double b, double epsilon = 0.0001);//判斷兩個double是否相等

    std::vector<std::string> split(std::string s, char delim);//將string根據delim做切割的函式

    bool isNumber(std::string str);//判斷字串是不是數字

    int getRandomInt(int min, int max);//取得min~max(包含)之間的隨機數

    template<typename T>
    double average(const std::vector<T>& v) { //計算vector的平均值
        T sum = 0;
        for (const T& x : v) {
            sum += x;
        }
        return static_cast<double>(sum) / v.size();
    } 

    template<typename T>
    T minimum(const std::vector<T>& v) { //計算vector的最小值
        if (v.empty()) {
            throw std::logic_error("Cannot find minimum of an empty vector");
        }
        T min_value = v[0];
        for (const T& x : v) {
            if (x < min_value) {
                min_value = x;
            }
        }
        return min_value;
    } 

    template<typename T>
    T maximum(const std::vector<T>& v) { //計算vector的最大值
        if (v.empty()) {
            throw std::logic_error("Cannot find maximum of an empty vector");
        }
        T max_value = v[0];
        for (const T& x : v) {
            if (x > max_value) {
                max_value = x;
            }
        }
        return max_value;
    }         

    std::set<Graph::Edge> difference(const std::set<Graph::Edge>& s1, const std::set<Graph::Edge>& s2);//計算s1-s2
}


#endif