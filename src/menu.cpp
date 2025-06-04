#include "menu.hpp"

// Affiche du texte en pixels (0,0 en haut-gauche)
void drawText(float x, float y, const char *text)
{
    char buffer[99999];
    int quads = stb_easy_font_print(x, y, (char *)text, nullptr, buffer, sizeof(buffer));
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
    glfwSetWindowSizeCallback(window, onWindowResized);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // Setup 2D orthographic projection en pixels
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        xpos = xpos * (width / (float)width);
        ypos = ypos * (height / (float)height);
        bool leftClick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

        // Zones clic boutons (en pourcentage de la taille de la fenêtre)
        float buttonWidth = width * 0.25f;    // 25% de la largeur de la fenêtre
        float buttonHeight = height * 0.083f; // 8.3% de la hauteur de la fenêtre
        float buttonXCenter = width / 2.0f;
        float buttonYCenterPlay = height / 2.0f - buttonHeight * 1.5f;
        float buttonYCenterQuit = height / 2.0f + buttonHeight * 1.5f;

        // Jouer
        if (xpos > buttonXCenter - buttonWidth / 2 && xpos < buttonXCenter + buttonWidth / 2 &&
            ypos > buttonYCenterPlay - buttonHeight / 2 && ypos < buttonYCenterPlay + buttonHeight / 2 && leftClick)
        {
            glfwDestroyWindow(window);
            glfwTerminate();
            return 1;
        }

        // Quitter
        if (xpos > buttonXCenter - buttonWidth / 2 && xpos < buttonXCenter + buttonWidth / 2 &&
            ypos > buttonYCenterQuit - buttonHeight / 2 && ypos < buttonYCenterQuit + buttonHeight / 2 && leftClick)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        // Dessin des boutons (verts et rouges)
        glColor3f(0.2f, 0.8f, 0.2f);
        glBegin(GL_QUADS);
        glVertex2f(buttonXCenter - buttonWidth / 2, buttonYCenterPlay - buttonHeight / 2);
        glVertex2f(buttonXCenter + buttonWidth / 2, buttonYCenterPlay - buttonHeight / 2);
        glVertex2f(buttonXCenter + buttonWidth / 2, buttonYCenterPlay + buttonHeight / 2);
        glVertex2f(buttonXCenter - buttonWidth / 2, buttonYCenterPlay + buttonHeight / 2);
        glEnd();

        glColor3f(0.8f, 0.2f, 0.2f);
        glBegin(GL_QUADS);
        glVertex2f(buttonXCenter - buttonWidth / 2, buttonYCenterQuit - buttonHeight / 2);
        glVertex2f(buttonXCenter + buttonWidth / 2, buttonYCenterQuit - buttonHeight / 2);
        glVertex2f(buttonXCenter + buttonWidth / 2, buttonYCenterQuit + buttonHeight / 2);
        glVertex2f(buttonXCenter - buttonWidth / 2, buttonYCenterQuit + buttonHeight / 2);
        glEnd();

        // Texte jaune sur boutons
        glColor3f(1.0f, 1.0f, 0.0f);
        drawText(buttonXCenter - buttonWidth / 4, buttonYCenterPlay - buttonHeight / 4, "Jouer");
        drawText(buttonXCenter - buttonWidth / 4, buttonYCenterQuit - buttonHeight / 4, "Quitter");

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
