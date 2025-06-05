#include "menu.hpp"
#include "utils.hpp"

Menu::Menu(GLFWwindow *win) : window(win), playSelected(false)
{
    glfwGetWindowSize(window, &width, &height);
}

bool Menu::shouldPlay() const
{
    return playSelected;
}

void Menu::run()
{
    glfwMakeContextCurrent(window);
    gladLoadGL();

    GLuint tex_menu = chargerTexture("assets/images/menu.png");

    while (!glfwWindowShouldClose(window) && !playSelected)
    {
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
            if (xpos > width / 3 && xpos < 2 * width / 3 && ypos > height / 3 && ypos < 2 * height / 3)
                playSelected = true;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
