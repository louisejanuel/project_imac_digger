#pragma once

#include <windows.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// #define STB_IMAGE_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

// #include "../lib/glbasimac/tools/stb_image.h"
#include "glbasimac/glbi_texture.hpp"

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"

#include "tools/matrix_stack.hpp"
#include <iostream>
#include <cmath>
#include <array>

#include <vector>
#include <string>
#include <GL/gl.h>
#include <GL/glu.h>

#include <queue>
#include <limits>

#include <cstdlib>
#include <ctime>

#define STB_EASY_FONT_IMPLEMENTATION
#include "stb_easy_font.h"

using namespace glbasimac;

void drawText(float x, float y, const char *text);
void showGameOver();
void showGameWon();
bool showMenu(GLFWwindow* window);

void onWindowResized(GLFWwindow * /*window*/, int width, int height);
GLuint chargerTexture(const char* filename);

/* OpenGL Engine */
extern GLBI_Engine myEngine;

extern const float GL_VIEW_SIZE;
extern float aspectRatio;

enum TileType
{
    EMPTY = 0,
    FULL = 1,
    OBJECT = 2,
    OBSTACLE = 3,
    TRAP = 4,
};
