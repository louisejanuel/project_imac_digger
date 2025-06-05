#pragma once
#include "utils.hpp"

enum Direction {
    RIGHT,
    LEFT,
    UP,
    DOWN
};

struct Player {
    int score;
    Player(float x, float y, float size);
    int getScore() const { return score; }
    void resetScore() { score = 0; }
    void update(float deltaTime, std::vector<std::vector<int>>& map);
    void draw();
    float x, y;
    float speed;
    float size;
    Direction currentDirection; // Direction actuelle du joueur

    bool willCollide(float newX, float newY, const std::vector<std::vector<int>>& map);
    GLuint tex;
};
