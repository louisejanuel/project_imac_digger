#pragma once
#include "utils.hpp"

struct Menu {
    Menu(GLFWwindow* win);
    void run();
    bool shouldPlay() const;

    GLFWwindow* window;
    int width, height;
    bool playSelected;
};

// int showMenu();
// void drawText(float x, float y, const char* text);