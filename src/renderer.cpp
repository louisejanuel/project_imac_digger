#include "renderer.hpp"
#include <GLFW/glfw3.h>

Renderer::Renderer(int width, int height, const MapGenerator &mapGen, FlowField &flowfield)
    : winWidth(width), winHeight(height), mapGen(mapGen), flowfield(flowfield) {}

void Renderer::run()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (!glfwInit())
        return;

    // glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); // désactivé

    GLFWwindow *window = glfwCreateWindow(winWidth, winHeight, "Map", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    const auto &map = mapGen.getMap();
    int rows = map.size();
    int cols = map[0].size();

    flowfield.compute(cols / 2, rows / 2);
    flowfield.loadTexture("assets/images/chat.png");

    while (!glfwWindowShouldClose(window))
    {
        static double lastTime = glfwGetTime();
        double currentTime = glfwGetTime();
        float deltaTime = float(currentTime - lastTime);
        lastTime = currentTime;

        flowfield.updateEnemies(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        float scale = 2.0f;
        float cellW = (2.0f / cols) * scale;
        float cellH = (2.0f / rows) * scale;

        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < cols; ++x)
            {
                if (map[y][x] == 1)
                    glColor4f(0.2f, 0.2f, 0.2f, 1.0f); // opaque
                else
                    glColor4f(0.8f, 0.8f, 0.8f, 1.0f); // opaque

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

        flowfield.drawEnemies(); // texture avec transparence

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
