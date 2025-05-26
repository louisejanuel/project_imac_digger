#include "renderer.hpp"
#include <GLFW/glfw3.h>

// Initialise le renderer avec la taille de fenêtre et les références
Renderer::Renderer(int width, int height, const MapGenerator &mapGen, FlowField &flowfield)
    : winWidth(width), winHeight(height), mapGen(mapGen), flowfield(flowfield) {}

void Renderer::run()
{
    // Active la transparence (pour les textures PNG avec alpha)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (!glfwInit()) return;

    // Création de la fenêtre
    GLFWwindow *window = glfwCreateWindow(winWidth, winHeight, "Map", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    // Récupère la map et initialise le flowfield
    const auto &map = mapGen.getMap();
    int rows = map.size(), cols = map[0].size();
    flowfield.compute(cols / 2, rows / 2);
    flowfield.loadTexture("assets/images/chat.png");

    // Boucle principale
    while (!glfwWindowShouldClose(window))
    {
        // Temps entre chaque frame
        static double lastTime = glfwGetTime();
        double currentTime = glfwGetTime();
        float deltaTime = float(currentTime - lastTime);
        lastTime = currentTime;

        flowfield.updateEnemies(deltaTime); // déplace les ennemis

        // Efface l'écran
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        // Calcule la taille des cases
        float scale = 2.0f;
        float cellW = (2.0f / cols) * scale;
        float cellH = (2.0f / rows) * scale;

        // Dessine la map
        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < cols; ++x)
            {
                // Choix de couleur en fonction du type de case
                (map[y][x] == 1) ? glColor3f(0.2f, 0.2f, 0.2f)
                                 : glColor3f(0.8f, 0.8f, 0.8f);

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

        // Dessine les ennemis avec texture
        flowfield.drawEnemies();

        // Affiche le tout
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
