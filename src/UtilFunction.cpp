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

}
