#pragma once

#include "mapGenerator.hpp"
#include "flowfield.hpp"
#include "player.hpp"
#include "ennemis.hpp"
#include "utils.hpp"

struct Renderer {
    int width, height;
    GLFWwindow* window;
    glbasimac::GLBI_Map& map;
    FlowField& flowfield;
    Player player;
    Ennemi ennemi;
    float lastFrameTime;

    bool isPaused = false;

    Renderer(int screenW, int screenH, glbasimac::GLBI_Map& mapGen, FlowField& flow, Ennemi ennemi);
    void run();
};

// void drawMap(const std::vector<std::vector<int>>& map);
void drawQuitButton(int windowWidth, int windowHeight);
bool handleQuitButtonClick(int windowWidth, int windowHeight, double xpos, double ypos);
void setOverlayProjection(int windowWidth, int windowHeight);
void setMapProjection(int mapWidth, int mapHeight);
void drawObjectCounter(int windowWidth, int windowHeight, int score, int totalObjects);

void drawPauseButton(int windowWidth, int windowHeight);
bool handlePauseButtonClick(int windowWidth, int windowHeight, double xpos, double ypos);
void drawPlayOverlay(int windowWidth, int windowHeight);
bool handlePlayButtonClick(int windowWidth, int windowHeight, double xpos, double ypos);
GLuint chargerTexture(const char* filename);

void drawMap(const GLBI_Map& map, GLuint tex_mur, GLuint tex_sol, GLuint tex_objet, GLuint tex_piege, GLuint tex_obstacle);

// void drawMap(const std::vector<std::vector<int>>& map);
