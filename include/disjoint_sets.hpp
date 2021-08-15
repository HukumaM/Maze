#pragma once

#include <vector>
#include <numeric>

class disjoint_sets
{
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    disjoint_sets(int size)
    {
        rank.resize(size);
        parent.resize(size);
        std::iota(parent.begin(), parent.end(), 0);
    }

    void make_set(int const u)
    {
        parent[u] = u;
        rank[u] = 0;
    }

    int find_set(int const v)
    {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int u, int v)
    {
        u = find_set(u);
        v = find_set(v);
        if (u != v)
        {
            if (rank[u] < rank[v])
                std::swap(u, v);
            parent[v] = u;
            if (rank[u] == rank[v])
                ++rank[u];
        }
    }
};