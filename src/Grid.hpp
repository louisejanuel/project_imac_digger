#pragma once
#include <vector>

enum class CellType {
    Empty,
    Wall
};

struct Cell {
    CellType type;
    int distance; // Distance to target (BFS)
    int x, y;     // Position
};

struct Grid {
    Grid(int width, int height);
    Cell& at(int x, int y);
    bool isWalkable(int x, int y) const;
    int getWidth() const;
    int getHeight() const;

    int width, height;
    std::vector<Cell> cells;
};
