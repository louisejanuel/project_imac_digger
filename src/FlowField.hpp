#pragma once
#include <vector>

struct Vec2
{
    int dx, dy;
};

struct FlowField
{
    FlowField(const std::vector<std::vector<int>> &map);
    void compute(int targetX, int targetY);
    Vec2 getDirection(int x, int y) const;

    const std::vector<std::vector<int>> &map;
    std::vector<std::vector<int>> distance;
    std::vector<std::vector<Vec2>> directions;
    std::vector<Vec2> neighbors = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};

    bool isWalkable(int x, int y) const;
    void reset();
};
