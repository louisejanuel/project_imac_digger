#pragma once
#include "mapGenerator.hpp"
#include "flowfield.hpp"
#include "player.hpp"
#include "ennemis.hpp"
#include "utils.hpp"

struct Renderer {
    int width, height;
    GLFWwindow* window;
    MapGenerator& map;
    FlowField& flowfield;
    Player player;
    Ennemi ennemi;
    float lastFrameTime;

    Renderer(int screenW, int screenH, MapGenerator& mapGen, FlowField& flow, Ennemi ennemi);
    void run();
};

void drawMap(const std::vector<std::vector<int>>& map);
