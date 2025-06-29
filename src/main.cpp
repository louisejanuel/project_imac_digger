#include "mapGenerator.hpp"
#include "renderer.hpp"
#include "utils.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../lib/glbasimac/tools/stb_image.h"

int main()
{
    if (!glfwInit())
        exit(-1);

    srand(static_cast<unsigned int>(time(nullptr)));
    GLFWwindow *window = glfwCreateWindow(1500, 800, "IMAC Digger", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        exit(-1);
    }

    if (showMenu(window))
    {
        glbasimac::GLBI_Map mapGen(60, 32);
        mapGen.generate(5);
        FlowField flowfield(mapGen.getGrid());
        Ennemi ennemi({});
        ennemi.placeEnemies(2, mapGen.getGrid());

        Renderer renderer(1500, 800, mapGen, flowfield, ennemi, window);
        renderer.run();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}