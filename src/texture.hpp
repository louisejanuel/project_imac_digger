#pragma once
#include "utils.hpp"

extern const float GL_VIEW_SIZE;

extern std::array<int, GLFW_KEY_LAST> keysState;

/* OpenGL Engine */
GLBI_Engine myEngine;

extern int winWidth;
extern int winHeight;

extern float winHaut;
extern float winBas;
extern float winDroite;
extern float winGauche;

GLBI_Texture texturePerso;
GLBI_Texture textureFond;
GLBI_Texture textureObjet;
GLBI_Texture texturePiege;

extern std::vector<std::vector<int>> grilleMap;


StandardMesh carre;
StandardMesh tileShape;

// Coordonnées UV (u, v)
static float uvs[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f};

// Coordonnées des sommets (x, y) du Perso
static float coordCoins[] =  {-0.5,-0.5, -0.5,0.5, 0.5,0.5, 0.5,-0.5};

// Coordonnées des sommets (x, y) des cubes de la map
static float tileCoords[] =  {-0.5,-0.5, -0.5,0.5, 0.5,0.5, 0.5,-0.5};

extern GLBI_Texture texturePerso;
extern GLBI_Texture textureFond;


void initTexturePerso();
void initTextureBackground();


void loadTexture(const char* filename,GLBI_Texture& texture);
void loadTexturePerso(GLBI_Texture& texture);
void loadTextureFond(GLBI_Texture& texture);
void loadTextureObjet(GLBI_Texture& texture);
void loadTexturePiege(GLBI_Texture& texture);