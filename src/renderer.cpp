// #include "renderer.hpp"

// Renderer::Renderer(int screenW, int screenH, MapGenerator &mapGen, FlowField &flow, Ennemi ennemi)
//     : width(screenW), height(screenH), map(mapGen), flowfield(flow),
//       player(0.0f, 0.0f, 0.99f), ennemi(std::move(ennemi))
// {
//     if (!glfwInit())
//     {
//         std::cerr << "Erreur GLFW\n";
//         exit(-1);
//     }

//     window = glfwCreateWindow(width, height, "IMAC Digger", nullptr, nullptr);
//     if (!window)
//     {
//         std::cerr << "Erreur création fenêtre GLFW\n";
//         glfwTerminate();
//         exit(-1);
//     }

//     glfwMakeContextCurrent(window);

//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluOrtho2D(0, map.getMap()[0].size(), map.getMap().size(), 0);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();

//     lastFrameTime = glfwGetTime();

//     const std::vector<std::vector<int>> &mapData = map.getMap();
//     int mapHeight = mapData.size();
//     int mapWidth = mapData[0].size();

//     int playerX, playerY;
//     do
//     {
//         playerX = rand() % mapWidth;
//         playerY = rand() % mapHeight;
//     } while (mapData[playerY][playerX] != EMPTY);

//     player = Player(static_cast<float>(playerX), static_cast<float>(playerY), 0.99f);
// }

// void Renderer::run()
// {
//     while (!glfwWindowShouldClose(window))
//     {
//         float currentTime = glfwGetTime();
//         float deltaTime = currentTime - lastFrameTime;
//         lastFrameTime = currentTime;

//         glClear(GL_COLOR_BUFFER_BIT);
//         glLoadIdentity();

//         drawMap(map.getMap());

//         std::vector<std::vector<int>> &mapData = const_cast<std::vector<std::vector<int>> &>(map.getMap());
//         player.update(deltaTime, mapData);
//         player.draw();

//         int playerX = static_cast<int>(std::round(player.x));
//         int playerY = static_cast<int>(std::round(player.y));
//         flowfield.compute(playerX, playerY);

//         ennemi.update(deltaTime, flowfield, map.getMap());
//         ennemi.draw(map.getMap());

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glfwTerminate();
// }

// void drawMap(const std::vector<std::vector<int>> &map)
// {
//     int height = map.size();
//     int width = map[0].size();

//     for (int y = 0; y < height; ++y)
//     {
//         for (int x = 0; x < width; ++x)
//         {
//             switch (map[y][x])
//             {
//             case EMPTY:
//                 glColor3f(1.0f, 1.0f, 1.0f);
//                 break;
//             case FULL:
//                 glColor3f(0.5f, 0.25f, 0.0f);
//                 break;
//             case OBJECT:
//                 glColor3f(1.0f, 0.0f, 1.0f);
//                 break;
//             case OBSTACLE:
//                 glColor3f(0.0f, 0.0f, 0.0f);
//                 break;
//             case TRAP:
//                 glColor3f(0.0f, 0.0f, 1.0f);
//                 break;
//             default:
//                 glColor3f(0.8f, 0.8f, 0.8f);
//                 break;
//             }

//             glBegin(GL_QUADS);
//             glVertex2f(x, y);
//             glVertex2f(x + 1, y);
//             glVertex2f(x + 1, y + 1);
//             glVertex2f(x, y + 1);
//             glEnd();
//         }
//     }
// }


#include "renderer.hpp"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <cmath>
#include <cstdlib>
#include <iostream>

Renderer::Renderer(int screenW, int screenH, glbasimac::GLBI_Map& mapGen, FlowField& flow, Ennemi ennemi)
    : width(screenW), height(screenH), map(mapGen), flowfield(flow),
      player(0.0f, 0.0f, 0.99f), ennemi(std::move(ennemi))
{
    if (!glfwInit()) {
        std::cerr << "Erreur GLFW\n";
        exit(-1);
    }

    window = glfwCreateWindow(width, height, "IMAC Digger", nullptr, nullptr);
    if (!window) {
        std::cerr << "Erreur création fenêtre GLFW\n";
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, map.getGrid()[0].size(), map.getGrid().size(), 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    lastFrameTime = glfwGetTime();

    const auto& mapData = map.getGrid();
    int mapHeight = mapData.size();
    int mapWidth = mapData[0].size();

    int playerX, playerY;
    do {
        playerX = rand() % mapWidth;
        playerY = rand() % mapHeight;
    } while (mapData[playerY][playerX] != EMPTY); // Assure que EMPTY est bien défini

    player = Player(static_cast<float>(playerX), static_cast<float>(playerY), 0.99f);
}

void Renderer::run()
{
    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        drawMap(map.getGrid());

        auto& mapData = const_cast<std::vector<std::vector<int>>&>(map.getGrid());
        player.update(deltaTime, mapData);
        player.draw();

        int playerX = static_cast<int>(std::round(player.x));
        int playerY = static_cast<int>(std::round(player.y));
        flowfield.compute(playerX, playerY);

        ennemi.update(deltaTime, flowfield, map.getGrid());
        ennemi.draw(map.getGrid());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void drawMap(const std::vector<std::vector<int>>& map)
{
    int height = map.size();
    int width = map[0].size();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            switch (map[y][x]) {
                case EMPTY:
                    glColor3f(1.0f, 1.0f, 1.0f);
                    break;
                case FULL:
                    glColor3f(0.5f, 0.25f, 0.0f);
                    break;
                case OBJECT:
                    glColor3f(1.0f, 0.0f, 1.0f);
                    break;
                case OBSTACLE:
                    glColor3f(0.0f, 0.0f, 0.0f);
                    break;
                case TRAP:
                    glColor3f(0.0f, 0.0f, 1.0f);
                    break;
                default:
                    glColor3f(0.8f, 0.8f, 0.8f);
                    break;
            }

            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + 1, y);
            glVertex2f(x + 1, y + 1);
            glVertex2f(x, y + 1);
            glEnd();
        }
    }
}
