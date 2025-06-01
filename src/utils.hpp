#pragma once

#include <windows.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "../lib/glbasimac/tools/stb_image.h"
#include "glbasimac/glbi_texture.hpp"

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

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
#include <cmath>

#include <cstdlib>
#include <ctime>

#define STB_EASY_FONT_IMPLEMENTATION
#include "stb_easy_font.h"

using namespace glbasimac;

void drawText(float x, float y, const char* text);
int showMenu();
void showGameOver();