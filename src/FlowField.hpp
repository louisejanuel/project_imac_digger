#pragma once
#include "Grid.hpp"
#include <vector>

struct Vec2 {
    int dx, dy;
};

class FlowField {
public:
    FlowField(Grid& grid);
    void compute(int targetX, int targetY);
    Vec2 getDirection(int x, int y) const;

private:
    Grid& grid;
    std::vector<std::vector<Vec2>> directions;

    void reset();
    std::vector<Vec2> neighbors = { {0,-1}, {-1,0}, {1,0}, {0,1} }; // N, W, E, S
};
