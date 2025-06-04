#include "utils.hpp"

// Définition des variables globales
GLBI_Engine myEngine;
StandardMesh carre;
StandardMesh tileShape;

float uvs[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f};
float coordCoins[] = {-0.5, -0.5, -0.5, 0.5, 0.5, 0.5, 0.5, -0.5};
float tileCoords[] = {-0.5, -0.5, -0.5, 0.5, 0.5, 0.5, 0.5, -0.5};

GLBI_Texture texturePerso;
GLBI_Texture textureFond;
GLBI_Texture textureObjet;
GLBI_Texture texturePiege;

int winWidth = 800;
int winHeight = 600;

float winHaut = 1.0f;
float winBas = -1.0f;
float winDroite = 1.0f;
float winGauche = -1.0f;

const float GL_VIEW_SIZE = 1.;
float aspectRatio = 1.0f;

std::vector<std::vector<int>> grilleMap;