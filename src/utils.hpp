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
#include <cmath>

#include <cstdlib>
#include <ctime>

#define STB_EASY_FONT_IMPLEMENTATION
#include "stb_easy_font.h"

using namespace glbasimac;

void drawText(float x, float y, const char *text);
int showMenu();
void showGameOver();

void drawObjet();
void drawPiege();
void initTextureBackground();

/* OpenGL Engine */
extern GLBI_Engine myEngine;

extern int winWidth;
extern int winHeight;

extern float winHaut;
extern float winBas;
extern float winDroite;
extern float winGauche;

extern GLBI_Texture texturePerso;
extern GLBI_Texture textureFond;
extern GLBI_Texture textureObjet;
extern GLBI_Texture texturePiege;

extern std::vector<std::vector<int>> grilleMap;

extern StandardMesh carre;
extern StandardMesh tileShape;

// Coordonnées UV (u, v)
extern float uvs[];
extern float coordCoins[];
extern float tileCoords[];


extern const float GL_VIEW_SIZE;
extern float aspectRatio;

enum TileType
{
    EMPTY = 0,
    FULL = 1,
    OBJECT = 2,
    OBSTACLE = 3,
    TRAP = 4,
    // HIDDEN_OBJECT = 5
};
