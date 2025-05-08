#pragma once
#include "MapGenerator.hpp"

class Renderer {
public:
    Renderer(int width, int height, const MapGenerator& mapGen);
    void run();

private:
    const MapGenerator& mapGen;
    int winWidth, winHeight;
    void render();
};
