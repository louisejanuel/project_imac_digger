#pragma once
#include <vector>

struct Player {
    Player(float x, float y, float size);
    void update(float deltaTime, std::vector<std::vector<int>>& map);
    void draw();
    float x, y;
    float speed;
    float size;

    bool willCollide(float newX, float newY, const std::vector<std::vector<int>>& map);
};
