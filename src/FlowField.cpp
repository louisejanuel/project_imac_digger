#include "FlowField.hpp"
#include <queue>
#include <limits>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

FlowField::FlowField(const std::vector<std::vector<int>> &map)
    : map(map)
{
    int h = map.size(), w = map[0].size();
    distance.resize(h, std::vector<int>(w, -1));
    directions.resize(h, std::vector<Vec2>(w, {0, 0}));
    enemies.push_back({1.5f, 1.5f, 1.0f});
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
            // Inversion ici
            bestDir.dx = -bestDir.dx;
            bestDir.dy = -bestDir.dy;
            directions[y][x] = bestDir;
        }
    }
}

Vec2 FlowField::getDirection(int x, int y) const
{
    if (x < 0 || y < 0 || y >= directions.size() || x >= directions[0].size())
        return {0, 0};
    return directions[y][x];
}

void FlowField::updateEnemies(float deltaTime)
{
    for (auto &enemy : enemies)
    {
        int cx = int(enemy.x), cy = int(enemy.y);
        Vec2 dir = getDirection(cx, cy);
        enemy.x += dir.dx * deltaTime * enemy.speed;
        enemy.y += dir.dy * deltaTime * enemy.speed;
    }
}

void FlowField::drawEnemies()
{
    if (!enemyTexture)
        return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, enemyTexture);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (const auto &e : enemies)
    {
        float size = 0.05f;
        float x = (e.x / map[0].size()) * 2.0f - 1.0f;
        float y = (e.y / map.size()) * 2.0f - 1.0f;

        glBegin(GL_QUADS);
        glTexCoord2f(0, 1);
        glVertex2f(x - size, y - size);
        glTexCoord2f(1, 1);
        glVertex2f(x + size, y - size);
        glTexCoord2f(1, 0);
        glVertex2f(x + size, y + size);
        glTexCoord2f(0, 0);
        glVertex2f(x - size, y + size);
        glEnd();
    }

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

void FlowField::loadTexture(const std::string &path)
{
    int w, h, channels;
    unsigned char *data = stbi_load(path.c_str(), &w, &h, &channels, 4);
    if (!data)
        return;

    glGenTextures(1, &enemyTexture);
    glBindTexture(GL_TEXTURE_2D, enemyTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(data);
}
