#include "utils.hpp"

// Définition des variables globales
GLBI_Engine myEngine;

const float GL_VIEW_SIZE = 1.;
float aspectRatio = 1.0f;

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