#include "player.hpp"
#include "mapGenerator.hpp"
#include "gameOver.hpp"
#include <iostream>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

Player::Player(float x, float y, float size)
    : x(x), y(y), size(size), speed(5.0f), score(0), currentDirection(DOWN) {}

void Player::update(float deltaTime, std::vector<std::vector<int>> &map)
{
    float newX = x;
    float newY = y;

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
    {
        newX += speed * deltaTime;
        currentDirection = RIGHT; // Mettre à jour la direction
    }
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
    {
        newX -= speed * deltaTime;
        currentDirection = LEFT; // Mettre à jour la direction
    }
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
    {
        newY += speed * deltaTime;
        currentDirection = DOWN; // Mettre à jour la direction
    }
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
    {
        newY -= speed * deltaTime;
        currentDirection = UP; // Mettre à jour la direction
    }

    // Si pas de mur => déplacement
    if (!willCollide(newX, y, map))
        x = newX;
    if (!willCollide(x, newY, map))
        y = newY;

    // Miner uniquement dans la direction actuelle
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_E) == GLFW_PRESS)
    {
        int mx = static_cast<int>(x);
        int my = static_cast<int>(y);

        switch (currentDirection)
        {
        case RIGHT:
            if (mx + 1 < map[0].size() && map[my][mx + 1] == FULL)
            {
                map[my][mx + 1] = EMPTY;
            }
            break;
        case LEFT:
            if (mx - 1 >= 0 && map[my][mx - 1] == FULL)
            {
                map[my][mx - 1] = EMPTY;
            }
            break;
        case DOWN:
            if (my + 1 < map.size() && map[my + 1][mx] == FULL)
            {
                map[my + 1][mx] = EMPTY;
            }
            break;
        case UP:
            if (my - 1 >= 0 && map[my - 1][mx] == FULL)
            {
                map[my - 1][mx] = EMPTY;
            }
            break;
        }
    }

    // Gestion des objets et des pièges (inchangée)
    int gridX = static_cast<int>(x);
    int gridY = static_cast<int>(y);

    if (map[gridY][gridX] == OBJECT)
    {
        map[gridY][gridX] = EMPTY;
        score++;
        std::cout << "Objet ramassé ! Score : " << score << "/" << 15 << "\n";

        if (score == 15)
        {
            std::cout << "Félicitations ! Vous avez ramassé tous les objets et gagné !\n";
        }
    }

    if (map[gridY][gridX] == TRAP)
    {
        std::cout << "Tu es tombé dans un piège !\n";
        showGameOver();
        glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);
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