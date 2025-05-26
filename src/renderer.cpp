#include "renderer.hpp"
#include <iostream>
#include <GL/glu.h>

Renderer::Renderer(int screenW, int screenH, MapGenerator &mapGen, FlowField &flow)
    : width(screenW), height(screenH), map(mapGen), flowfield(flow),
      player(2.0f, 2.0f, 1.0f) // Position initiale (x=2, y=2), taille 1x1
{
    if (!glfwInit())
    {
        std::cerr << "Erreur GLFW\n";
        exit(-1);
    }

    window = glfwCreateWindow(width, height, "IMAC Digger", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Erreur création fenêtre GLFW\n";
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    // Projection pour que 1 unité = 1 case
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, map.getMap()[0].size(), map.getMap().size(), 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    lastFrameTime = glfwGetTime();
}

void Renderer::run()
{
    while (!glfwWindowShouldClose(window))
    {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        drawMap(map.getMap());
        std::vector<std::vector<int>> &mapData = const_cast<std::vector<std::vector<int>>&>(map.getMap());
        player.update(deltaTime, mapData);
        // player.update(deltaTime, map.getMap());
        player.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void drawMap(const std::vector<std::vector<int>> &mapData)
{
    for (int y = 0; y < mapData.size(); ++y)
    {
        for (int x = 0; x < mapData[y].size(); ++x)
        {
            if (mapData[y][x] == 1)
                glColor3f(0.0f, 0.0f, 0.0f); // Mur = noir
            else
                glColor3f(1.0f, 1.0f, 1.0f); // Sol = blanc

            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + 1, y);
            glVertex2f(x + 1, y + 1);
            glVertex2f(x, y + 1);
            glEnd();
        }
    }
}
