#pragma once
#include "mapGenerator.hpp"
#include "FlowField.hpp"

// Gère l'affichage de la map et des ennemis
struct Renderer
{
    Renderer(int width, int height, const MapGenerator &mapGen, FlowField &flowfield);
    void run(); // boucle principale

    int winWidth, winHeight;
    const MapGenerator &mapGen;
    FlowField &flowfield;
};
