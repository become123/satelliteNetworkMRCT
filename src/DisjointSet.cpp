#include "DisjointSet.h"

namespace DisjointSet
{
    DisjointSet::DisjointSet(int n) {
        parent.resize(n);
        size.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int DisjointSet::find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    bool DisjointSet::Union(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) {
            return false;
        }
        if (size[rootX] < size[rootY]) {
            std::swap(rootX, rootY);
        }
        parent[rootY] = rootX;
        size[rootX] += size[rootY];
        return true;
    }
}