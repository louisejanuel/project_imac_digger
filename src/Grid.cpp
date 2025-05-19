#include "Grid.hpp"

Grid::Grid(int width, int height) : width(width), height(height), cells(width * height) {
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x) {
            Cell& cell = at(x, y);
            cell.x = x;
            cell.y = y;
            cell.type = CellType::Empty;
            cell.distance = -1;
        }
}

Cell& Grid::at(int x, int y) {
    return cells[y * width + x];
}

bool Grid::isWalkable(int x, int y) const {
    if (x < 0 || y < 0 || x >= width || y >= height) return false;
    const Cell& cell = cells[y * width + x];
    return cell.type == CellType::Empty;
}

int Grid::getWidth() const { return width; }
int Grid::getHeight() const { return height; }
