#pragma once
#include "FlowField.hpp"
#include "utils.hpp"

struct Ennemi
{
    Ennemi(std::vector<Enemy> enemies);
    void update(float deltaTime, const FlowField& flow, const std::vector<std::vector<int>>& map);
    void draw(const std::vector<std::vector<int>> &map);
    std::vector<Enemy> enemies;

    bool willCollide(float newX, float newY, const std::vector<std::vector<int>> &map);
};
