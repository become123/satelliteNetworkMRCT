#ifndef CONVERT
#define CONVERT
#include <unordered_map>

namespace ConvertTool
{
    class satIdConversion{//用來轉換衛星編號和graph中的node index的物件
    private:
        std::unordered_map<int, int> satIdToIndexTable;
        std::unordered_map<int, int> indexToSatTable;
        int size;
        void addSatId(int x);
            
    public:
        satIdConversion();

        int getSize();

        int satIdToIndex(int x);

        int indexToSatId(int x);
    };
}

#endif