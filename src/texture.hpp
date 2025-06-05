#pragma once
#include "utils.hpp"

extern std::array<int, GLFW_KEY_LAST> keysState;


void initTexturePerso();
void initTextureBackground();


void loadTexture(const char* filename,GLBI_Texture& texture);
void loadTexturePerso(GLBI_Texture& texture);
void loadTextureFond(GLBI_Texture& texture);
void loadTextureObjet(GLBI_Texture& texture);
void loadTexturePiege(GLBI_Texture& texture);