#include "ennemis.hpp"
#include <cmath>
#include <GL/gl.h> // ou autre include OpenGL

void Enemy::update(float dt) {
    if (currentTargetIndex >= (int)path.size()) return; // plus de chemin

    float targetX = path[currentTargetIndex].first + 0.5f;  // centre case X
    float targetY = path[currentTargetIndex].second + 0.5f; // centre case Y

    float dx = targetX - x;
    float dy = targetY - y;
    float dist = std::sqrt(dx*dx + dy*dy);

    float moveDist = speed * dt;
    if (dist <= moveDist) {
        // atteint la cible
        x = targetX;
        y = targetY;
        currentTargetIndex++;
    } else {
        // avance vers la cible
        x += dx / dist * moveDist;
        y += dy / dist * moveDist;
    }
}

void Enemy::draw() const {
    // Exemple carré simple
    float size = 0.4f; // taille relative à une case (à ajuster)
    glColor3f(1.0f, 0.0f, 0.0f); // rouge
    glBegin(GL_QUADS);
        glVertex2f(x - size/2, y - size/2);
        glVertex2f(x + size/2, y - size/2);
        glVertex2f(x + size/2, y + size/2);
        glVertex2f(x - size/2, y + size/2);
    glEnd();
}
