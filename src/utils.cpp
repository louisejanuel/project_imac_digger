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

void onWindowResized(GLFWwindow * /*window*/, int width, int height)
{
    aspectRatio = width / (float)height;
    glViewport(0, 0, width, height);
    if (aspectRatio > 1.0)
    {
        myEngine.set2DProjection(-GL_VIEW_SIZE * aspectRatio / 2.,
                                 GL_VIEW_SIZE * aspectRatio / 2.,
                                 -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
    }
    else
    {
        myEngine.set2DProjection(-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
                                 -GL_VIEW_SIZE / (2. * aspectRatio),
                                 GL_VIEW_SIZE / (2. * aspectRatio));
    }
}

void drawText(float x, float y, const char *text)
{
    char buffer[99999];
    int quads = stb_easy_font_print(x, y, (char *)text, nullptr, buffer, sizeof(buffer));
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 16, buffer);
    glDrawArrays(GL_QUADS, 0, quads * 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}