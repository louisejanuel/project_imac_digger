#pragma once
#include "mapGenerator.hpp"

struct Renderer {
    Renderer(int width, int height, const MapGenerator& mapGen);
    void run();

    const MapGenerator& mapGen;
    int winWidth, winHeight;
    void render();
};
