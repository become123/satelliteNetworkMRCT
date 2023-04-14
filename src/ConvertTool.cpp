#include "ConvertTool.h"

namespace ConvertTool
{

    void satIdConversion::addSatId(int x){
        satIdToIndexTable[x] = size;
        indexToSatTable[size] = x;
        ++size;
    }    
    satIdConversion::satIdConversion():size(0){}

    int satIdConversion::getSize(){
        return size;
    }

    int satIdConversion::satIdToIndex(int x){
        if(satIdToIndexTable.find(x) == satIdToIndexTable.end()){
            addSatId(x);
        }
        return satIdToIndexTable[x];
    }

    int satIdConversion::indexToSatId(int x){
        return indexToSatTable[x];
    }
    
}
