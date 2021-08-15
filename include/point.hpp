#pragma once

struct point
{
    int x;
    int y;
    int set;

public:
    point() = default;
    point(int _x, int _y, int _set = 0)
        : x(_x), y(_y), set(_set) {}

public:
    friend bool operator<(point const &lhs, point const &rhs)
    {
        return lhs.x < rhs.x || lhs.y < rhs.y;
    }
    friend bool operator>(point const &lhs, point const &rhs)
    {
        return !(lhs < rhs);
    }
    friend bool operator==(point const &lhs, point const &rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
    friend bool operator!=(point const &lhs, point const &rhs)
    {
        return !(lhs == rhs);
    }
};