#pragma once
#include <vector>
#include <string>
#include <GL/gl.h>

struct Vec2 {
    int dx, dy;
};

struct Enemy {
    float x, y;
    float speed;
};

struct FlowField {
    FlowField(const std::vector<std::vector<int>>& map);
    void compute(int targetX, int targetY);
    Vec2 getDirection(int x, int y) const;

    void updateEnemies(float deltaTime);
    void drawEnemies();
    void loadTexture(const std::string& path);

    const std::vector<std::vector<int>>& map;
    std::vector<std::vector<int>> distance;
    std::vector<std::vector<Vec2>> directions;
    std::vector<Vec2> neighbors = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};

    std::vector<Enemy> enemies;
    GLuint enemyTexture = 0;

    bool isWalkable(int x, int y) const;
    void reset();
};
