#ifndef UTIL_FUNCTION
#define UTIL_FUNCTION
#include <vector>
#include <string>
#include <sstream>


namespace UtilFunction
{
    std::vector<std::string> split(std::string s, char delim);//將string根據delim做切割的函式

    bool isNumber(std::string str);//判斷字串是不是數字
}


#endif