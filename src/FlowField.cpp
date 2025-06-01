#include "FlowField.hpp"

FlowField::FlowField(const std::vector<std::vector<int>> &map)
    : map(map)
{
    int h = map.size(), w = map[0].size();
    distance.resize(h, std::vector<int>(w, -1));
    directions.resize(h, std::vector<Vec2>(w, {0, 0}));
}

void FlowField::reset()
{
    int h = map.size(), w = map[0].size();
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
        {
            distance[y][x] = -1;
            directions[y][x] = {0, 0};
        }
}

bool FlowField::isWalkable(int x, int y) const
{
    return y >= 0 && x >= 0 && y < map.size() && x < map[0].size() && map[y][x] == 0;
}

void FlowField::compute(int targetX, int targetY)
{
    reset();
    std::queue<std::pair<int, int>> queue;
    distance[targetY][targetX] = 0;
    queue.push({targetX, targetY});

    while (!queue.empty())
    {
        auto [x, y] = queue.front();
        queue.pop();
        for (const auto &dir : neighbors)
        {
            int nx = x + dir.dx, ny = y + dir.dy;
            if (isWalkable(nx, ny) && (distance[ny][nx] == -1 || distance[ny][nx] > distance[y][x] + 1))
            {
                distance[ny][nx] = distance[y][x] + 1;
                queue.push({nx, ny});
            }
        }
    }

    for (int y = 0; y < map.size(); ++y)
    {
        for (int x = 0; x < map[0].size(); ++x)
        {
            if (!isWalkable(x, y))
                continue;
            int minDist = std::numeric_limits<int>::max();
            Vec2 bestDir = {0, 0};
            for (const auto &dir : neighbors)
            {
                int nx = x + dir.dx, ny = y + dir.dy;
                if (isWalkable(nx, ny) && distance[ny][nx] >= 0 && distance[ny][nx] < minDist)
                {
                    minDist = distance[ny][nx];
                    bestDir = dir;
                }
            }
            bestDir.dx = -bestDir.dx;
            bestDir.dy = -bestDir.dy;
            directions[y][x] = bestDir;
        }
    }
}

Vec2 FlowField::getDirection(float fx, float fy) const
{
    int x0 = int(fx), y0 = int(fy);
    int x1 = x0 + 1, y1 = y0 + 1;

    if (!isWalkable(x0, y0))
        return {0, 0};

    float tx = fx - x0;
    float ty = fy - y0;

    Vec2 d00 = directions[y0][x0];
    Vec2 d10 = (x1 < map[0].size()) ? directions[y0][x1] : d00;
    Vec2 d01 = (y1 < map.size()) ? directions[y1][x0] : d00;
    Vec2 d11 = (x1 < map[0].size() && y1 < map.size()) ? directions[y1][x1] : d00;

    float dx = (1 - tx) * (1 - ty) * d00.dx +
               tx * (1 - ty) * d10.dx +
               (1 - tx) * ty * d01.dx +
               tx * ty * d11.dx;

    float dy = (1 - tx) * (1 - ty) * d00.dy +
               tx * (1 - ty) * d10.dy +
               (1 - tx) * ty * d01.dy +
               tx * ty * d11.dy;

    return {dx, dy};
}
