#include "UtilFunction.h"


namespace UtilFunction
{
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
}