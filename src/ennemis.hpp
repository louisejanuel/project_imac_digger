#pragma once
#include <vector>
#include <utility> // pour std::pair

struct Enemy {
    float x, y;                // position en coordonnées flottantes (pixels ou cases)
    float speed;               // cases par seconde
    std::vector<std::pair<int,int>> path; // chemin (liste de cases)
    int currentTargetIndex;    // indice dans le chemin

    Enemy(float startX, float startY, float spd)
      : x(startX), y(startY), speed(spd), currentTargetIndex(0) {}

    void update(float dt);     // avancer sur le chemin
    void draw() const;         // dessiner l'ennemi (sprite simple carré ici)
};
