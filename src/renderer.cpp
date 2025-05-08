#include "Renderer.hpp"
#include <GLFW/glfw3.h>

Renderer::Renderer(int width, int height, const MapGenerator& mapGen)
    : winWidth(width), winHeight(height), mapGen(mapGen) {}

void Renderer::run() {
    if (!glfwInit()) return;
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "Map", nullptr, nullptr);
    if (!window) { glfwTerminate(); return; }
    glfwMakeContextCurrent(window);

    const auto& map = mapGen.getMap();
    int rows = map.size();
    int cols = map[0].size();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        float cellW = 2.0f / cols;
        float cellH = 2.0f / rows;

        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                if (map[y][x] == 1)
                    glColor3f(0.2f, 0.2f, 0.2f); // mur
                else
                    glColor3f(0.8f, 0.8f, 0.8f); // vide

                float x1 = -1.0f + x * cellW;
                float y1 = -1.0f + y * cellH;

                glBegin(GL_QUADS);
                glVertex2f(x1, y1);
                glVertex2f(x1 + cellW, y1);
                glVertex2f(x1 + cellW, y1 + cellH);
                glVertex2f(x1, y1 + cellH);
                glEnd();
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
}
