#include "menu.hpp"

bool showMenu(GLFWwindow *window)
{
    glfwMakeContextCurrent(window);
    gladLoadGL();
    GLuint tex_menu = chargerTexture("assets/images/menu.png");

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1, 1);
        glViewport(0, 0, width, height);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex_menu);
        glColor3f(1, 1, 1);

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(0, 0);
        glTexCoord2f(1, 0);
        glVertex2f(width, 0);
        glTexCoord2f(1, 1);
        glVertex2f(width, height);
        glTexCoord2f(0, 1);
        glVertex2f(0, height);
        glEnd();

        glDisable(GL_TEXTURE_2D);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            double startX = 807.0 / 1500.0 * width;
            double startY = 360.0 / 800.0 * height;
            double btnW = 253.0 / 1500.0 * width;
            double btnH = 96.0 / 800.0 * height;
            double quitX = 1109.0 / 1500.0 * width;

            if (xpos > startX && xpos < startX + btnW && ypos > startY && ypos < startY + btnH)
                return true;

            if (xpos > quitX && xpos < quitX + btnW && ypos > startY && ypos < startY + btnH)
                glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return false;
}
