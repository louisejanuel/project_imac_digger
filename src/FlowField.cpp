#include "FlowField.hpp"
#include <queue>
#include <limits>

FlowField::FlowField(const std::vector<std::vector<int>>& map)
    : map(map) {
    int h = map.size(), w = map[0].size();
    distance.resize(h, std::vector<int>(w, -1));
    directions.resize(h, std::vector<Vec2>(w, {0, 0}));
}

void FlowField::reset() {
    int h = map.size(), w = map[0].size();
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x) {
            distance[y][x] = -1;
            directions[y][x] = {0, 0};
        }
}

bool FlowField::isWalkable(int x, int y) const {
    return y >= 0 && x >= 0 && y < map.size() && x < map[0].size() && map[y][x] == 0;
}

void FlowField::compute(int targetX, int targetY) {
    reset();
    std::queue<std::pair<int, int>> queue;
    distance[targetY][targetX] = 0;
    queue.push({targetX, targetY});

    while (!queue.empty()) {
        auto [x, y] = queue.front(); queue.pop();
        for (const auto& dir : neighbors) {
            int nx = x + dir.dx, ny = y + dir.dy;
            if (isWalkable(nx, ny) && (distance[ny][nx] == -1 || distance[ny][nx] > distance[y][x] + 1)) {
                distance[ny][nx] = distance[y][x] + 1;
                queue.push({nx, ny});
            }
        }
    }

    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[0].size(); ++x) {
            if (!isWalkable(x, y)) continue;
            int minDist = std::numeric_limits<int>::max();
            Vec2 bestDir = {0, 0};
            for (const auto& dir : neighbors) {
                int nx = x + dir.dx, ny = y + dir.dy;
                if (isWalkable(nx, ny) && distance[ny][nx] >= 0 && distance[ny][nx] < minDist) {
                    minDist = distance[ny][nx];
                    bestDir = dir;
                }
            }
            directions[y][x] = bestDir;
        }
    }
}

Vec2 FlowField::getDirection(int x, int y) const {
    if (x < 0 || y < 0 || y >= directions.size() || x >= directions[0].size())
        return {0, 0};
    return directions[y][x];
}
