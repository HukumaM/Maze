#pragma once

#include "point.hpp"

struct edge
{
    point first;
    point second;
    unsigned weight;

public:
    edge() = default;
    edge(point _first,
         point _second,
         unsigned _weight = 0U)
        : first(_first), second(_second), weight(_weight) {}
        
    friend bool operator<(edge const &_edge, point const &_point)
    {
        return _edge.first < _point;
    }

    friend bool operator<(point const &_point, edge const &_edge)
    {
        return _point < _edge.first;
    }
};
