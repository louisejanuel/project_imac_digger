#include <GLFW/glfw3.h>
#define STB_EASY_FONT_IMPLEMENTATION
#include "stb_easy_font.h"

// Affiche du texte en pixels (0,0 en haut-gauche)
void drawText(float x, float y, const char* text) {
    char buffer[99999];
    int quads = stb_easy_font_print(x, y, (char*)text, nullptr, buffer, sizeof(buffer));
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 16, buffer);
    glDrawArrays(GL_QUADS, 0, quads * 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

int showMenu()
{
    if (!glfwInit())
        return -1;

    GLFWwindow *window = glfwCreateWindow(800, 600, "Menu", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
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

        glClear(GL_COLOR_BUFFER_BIT);

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        bool leftClick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

        // Zones clic boutons (en pixels)
        // Jouer
        if (xpos > width / 2 - 100 && xpos < width / 2 + 100 &&
            ypos > height / 2 - 100 && ypos < height / 2 - 50 && leftClick)
        {
            glfwDestroyWindow(window);
            glfwTerminate();
            return 1;
        }

        // Quitter
        if (xpos > width / 2 - 100 && xpos < width / 2 + 100 &&
            ypos > height / 2 + 50 && ypos < height / 2 + 100 && leftClick)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        // Dessin des boutons (verts et rouges)
        glColor3f(0.2f, 0.8f, 0.2f);
        glBegin(GL_QUADS);
        glVertex2f(width / 2 - 100, height / 2 - 100);
        glVertex2f(width / 2 + 100, height / 2 - 100);
        glVertex2f(width / 2 + 100, height / 2 - 50);
        glVertex2f(width / 2 - 100, height / 2 - 50);
        glEnd();

        glColor3f(0.8f, 0.2f, 0.2f);
        glBegin(GL_QUADS);
        glVertex2f(width / 2 - 100, height / 2 + 50);
        glVertex2f(width / 2 + 100, height / 2 + 50);
        glVertex2f(width / 2 + 100, height / 2 + 100);
        glVertex2f(width / 2 - 100, height / 2 + 100);
        glEnd();

        // Texte jaune sur boutons
        glColor3f(1.0f, 1.0f, 0.0f);
        drawText(width / 2 - 30, height / 2 - 85, "Jouer");
        drawText(width / 2 - 35, height / 2 + 75, "Quitter");

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
