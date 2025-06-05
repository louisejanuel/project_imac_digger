#pragma once
#include "utils.hpp"

struct Vec2
{
    float dx, dy;
};

struct Enemy
{
    float x, y;
    float speed;
};

struct FlowField
{
    FlowField(const std::vector<std::vector<int>> &map);
    void compute(int targetX, int targetY);
    Vec2 getDirection(float fx, float fy) const;

    const std::vector<std::vector<int>> &map;
    std::vector<std::vector<int>> distance;
    std::vector<std::vector<Vec2>> directions;
    std::vector<Vec2> neighbors = {{0, -1}, {-1, 0}, {1, 0}, {0, 1},{1, 1},{-1, 1},{1, -1},{-1, -1}};

    GLuint enemyTexture = 0;

    bool isWalkable(int x, int y) const;
    void reset();
};