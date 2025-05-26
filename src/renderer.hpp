#pragma once
#include "mapGenerator.hpp"
#include "flowfield.hpp"
#include "player.hpp"
#include <GLFW/glfw3.h>

struct Renderer {
    int width, height;
    GLFWwindow* window;
    MapGenerator& map;
    FlowField& flowfield;
    Player player;

    float lastFrameTime;

    Renderer(int screenW, int screenH, MapGenerator& mapGen, FlowField& flow);
    void run();
};

void drawMap(const std::vector<std::vector<int>>& map);