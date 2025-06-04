#include "gameOver.hpp"

void showGameOver()
{
    if (!glfwInit())
        return;

    GLFWwindow *window = glfwCreateWindow(800, 600, "Game Over", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        // Setup 2D orthographic projection en pixels
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fond noir
        glClear(GL_COLOR_BUFFER_BIT);

        // Texte blanc centré
        glColor3f(1.0f, 1.0f, 1.0f);
        drawText(width / 2 - 100, height / 2, "BOUUUH VOUS AVEZ PERDU");

        glfwSwapBuffers(window);
        glfwPollEvents();

        // Fermer la fenêtre si une touche est pressée ou un clic est détecté
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
            glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}