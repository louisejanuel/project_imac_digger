#include "player.hpp"
#include "mapGenerator.hpp"
#include <iostream>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

Player::Player(float x, float y, float size)
    : x(x), y(y), size(size), speed(5.0f), score(0) {}

void Player::update(float deltaTime, std::vector<std::vector<int>> &map)
{
    float newX = x;
    float newY = y;

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
        newX += speed * deltaTime;
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
        newX -= speed * deltaTime;
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
        newY += speed * deltaTime;
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
        newY -= speed * deltaTime;

    // Si pas de mur => déplacement
    if (!willCollide(newX, y, map))
        x = newX;
    else
    {
        // Vérification des cases adjacentes pour miner
        int mx = static_cast<int>(x);
        int my = static_cast<int>(y);

        if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_E) == GLFW_PRESS)
        {
            // Vérifie la case à droite
            if (mx + 1 < map[0].size() && map[my][mx + 1] == FULL)
            {
                map[my][mx + 1] = EMPTY;
            }
            // Vérifie la case à gauche
            else if (mx - 1 >= 0 && map[my][mx - 1] == FULL)
            {
                map[my][mx - 1] = EMPTY;
            }
            // Vérifie la case en bas
            else if (my + 1 < map.size() && map[my + 1][mx] == FULL)
            {
                map[my + 1][mx] = EMPTY;
            }
            // Vérifie la case en haut
            else if (my - 1 >= 0 && map[my - 1][mx] == FULL)
            {
                map[my - 1][mx] = EMPTY;
            }
        }
    }

    if (!willCollide(x, newY, map))
        y = newY;
    else
    {
        // Vérification des cases adjacentes pour miner
        int mx = static_cast<int>(x);
        int my = static_cast<int>(y);

        if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_E) == GLFW_PRESS)
        {
            // Vérifie la case à droite
            if (mx + 1 < map[0].size() && map[my][mx + 1] == FULL)
            {
                map[my][mx + 1] = EMPTY;
            }
            // Vérifie la case à gauche
            else if (mx - 1 >= 0 && map[my][mx - 1] == FULL)
            {
                map[my][mx - 1] = EMPTY;
            }
            // Vérifie la case en bas
            else if (my + 1 < map.size() && map[my + 1][mx] == FULL)
            {
                map[my + 1][mx] = EMPTY;
            }
            // Vérifie la case en haut
            else if (my - 1 >= 0 && map[my - 1][mx] == FULL)
            {
                map[my - 1][mx] = EMPTY;
            }
        }
    }

    int gridX = static_cast<int>(x);
    int gridY = static_cast<int>(y);

    // Objet
    if (map[gridY][gridX] == OBJECT) {
        map[gridY][gridX] = EMPTY;
        score++;
        std::cout << "Objet ramassé ! Score : " << score << "/" << 15 << "\n";
    
        // Vérifier si tous les objets ont été ramassés
        if (score == 15) {
            std::cout << "Félicitations ! Vous avez ramassé tous les objets et gagné !\n";
        }
    }

    // Piège
    if (map[gridY][gridX] == TRAP)
    {
        std::cout << "Tu es tombé dans un piège !\n";
        // gérer la mort, ou reset du joueur
    }
}

void Player::draw()
{
    glColor3f(1.0f, 0.0f, 0.0f); // Rouge
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size);
    glVertex2f(x, y + size);
    glEnd();
}

bool Player::willCollide(float testX, float testY, const std::vector<std::vector<int>> &map)
{
    // On vérifie les 4 coins du carré
    float corners[4][2] = {
        {testX, testY},
        {testX + size, testY},
        {testX, testY + size},
        {testX + size, testY + size}};

    for (int i = 0; i < 4; ++i)
    {
        int cx = int(corners[i][0]);
        int cy = int(corners[i][1]);

        if (cx < 0 || cy < 0 || cy >= map.size() || cx >= map[0].size())
            return true; // hors map = mur

        if (map[cy][cx] == 1 || map[cy][cx] == 3)
            return true;
    }

    return false;
}