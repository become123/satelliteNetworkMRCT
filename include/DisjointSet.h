#ifndef DISJOINT_SET
#define DISJOINT_SET
#include <vector>

namespace DisjointSet
{
    class DisjointSet {
    private:
        std::vector<int> parent;
        std::vector<int> size;
    public:
        DisjointSet(int n);
        int find(int x);
        bool Union(int x, int y);
    };
}

#endif