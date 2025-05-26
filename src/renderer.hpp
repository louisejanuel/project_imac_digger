#pragma once
#include "mapGenerator.hpp"
#include "FlowField.hpp"

struct Renderer
{
    Renderer(int width, int height, const MapGenerator &mapGen, FlowField &flowfield);
    void run();
    int winWidth, winHeight;
    const MapGenerator &mapGen;
    FlowField &flowfield;
};
