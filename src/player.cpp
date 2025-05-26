#include "player.hpp"
#include <GL/glu.h>
#include <GLFW/glfw3.h>

Player::Player(float x, float y, float size)
    : x(x), y(y), size(size), speed(5.0f) {}

void Player::update(float deltaTime, std::vector<std::vector<int>>& map) {
    float newX = x;
    float newY = y;

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_PRESS)
        newX += speed * deltaTime;
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_PRESS)
        newX -= speed * deltaTime;
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS)
        newY += speed * deltaTime;
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS)
        newY -= speed * deltaTime;

    // Si pas de mur => déplacement
    if (!willCollide(newX, y, map)) x = newX;
    else {
        // Si collision = mur => miner
        int mx = int(newX);
        int my = int(y);
        if (mx >= 0 && my >= 0 && my < map.size() && mx < map[0].size())
            map[my][mx] = 0;
    }

    if (!willCollide(x, newY, map)) y = newY;
    else {
        int mx = int(x);
        int my = int(newY);
        if (mx >= 0 && my >= 0 && my < map.size() && mx < map[0].size())
            map[my][mx] = 0;
    }
}

void Player::draw() {
    glColor3f(1.0f, 0.0f, 0.0f); // Rouge
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size);
    glVertex2f(x, y + size);
    glEnd();
}

bool Player::willCollide(float testX, float testY, const std::vector<std::vector<int>>& map) {
    // On vérifie les 4 coins du carré
    float corners[4][2] = {
        {testX, testY},
        {testX + size, testY},
        {testX, testY + size},
        {testX + size, testY + size}
    };

    for (int i = 0; i < 4; ++i) {
        int cx = int(corners[i][0]);
        int cy = int(corners[i][1]);

        if (cx < 0 || cy < 0 || cy >= map.size() || cx >= map[0].size())
            return true; // hors map = mur

        if (map[cy][cx] == 1) return true;
    }

    return false;
}
