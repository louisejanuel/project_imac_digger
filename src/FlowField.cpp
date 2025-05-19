#include "FlowField.hpp"
#include <queue>
#include <limits>

FlowField::FlowField(Grid& g) : grid(g) {
    directions.resize(grid.getHeight(), std::vector<Vec2>(grid.getWidth(), {0, 0}));
}

void FlowField::reset() {
    for (int y = 0; y < grid.getHeight(); ++y)
        for (int x = 0; x < grid.getWidth(); ++x) {
            grid.at(x, y).distance = -1;
            directions[y][x] = {0, 0};
        }
}

void FlowField::compute(int targetX, int targetY) {
    reset();

    std::queue<Cell*> queue;
    Cell& target = grid.at(targetX, targetY);
    target.distance = 0;
    queue.push(&target);

    // BFS to compute distances
    while (!queue.empty()) {
        Cell* current = queue.front(); queue.pop();

        for (const auto& dir : neighbors) {
            int nx = current->x + dir.dx;
            int ny = current->y + dir.dy;

            if (grid.isWalkable(nx, ny)) {
                Cell& neighbor = grid.at(nx, ny);
                if (neighbor.distance == -1 || neighbor.distance > current->distance + 1) {
                    neighbor.distance = current->distance + 1;
                    queue.push(&neighbor);
                }
            }
        }
    }

    // choisir direction
    for (int y = 0; y < grid.getHeight(); ++y) {
        for (int x = 0; x < grid.getWidth(); ++x) {
            if (!grid.isWalkable(x, y)) continue;

            int minDist = std::numeric_limits<int>::max();
            Vec2 bestDir{0, 0};

            for (const auto& dir : neighbors) {
                int nx = x + dir.dx;
                int ny = y + dir.dy;
                if (!grid.isWalkable(nx, ny)) continue;

                int dist = grid.at(nx, ny).distance;
                if (dist >= 0 && dist < minDist) {
                    minDist = dist;
                    bestDir = dir;
                }
            }
            directions[y][x] = bestDir;
        }
    }
}

Vec2 FlowField::getDirection(int x, int y) const {
    if (x < 0 || y < 0 || y >= static_cast<int>(directions.size()) || x >= static_cast<int>(directions[0].size()))
        return {0, 0};
    return directions[y][x];
}
