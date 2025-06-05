#include "mapGenerator.hpp"

namespace glbasimac {

GLBI_Map::GLBI_Map(int w, int h, float prob)
    : width(w), height(h), fill_prob(prob) {
    assert(fill_prob >= 0.0f && fill_prob <= 1.0f);
    srand(static_cast<unsigned int>(time(nullptr)));
    generateInitialMap();
}

void GLBI_Map::generateInitialMap() {
    grid = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            grid[y][x] = (rand() / (float)RAND_MAX < fill_prob) ? 1 : 0;
}

int GLBI_Map::countFilledNeighbors(int x, int y) {
    int count = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || ny < 0 || nx >= width || ny >= height) {
                count++; // bord = rempli
            } else if (grid[ny][nx] == 1) {
                count++;
            }
        }
    }
    return count;
}

void GLBI_Map::simulate(int steps) {
    for (int s = 0; s < steps; ++s) {
        std::vector<std::vector<int>> new_grid = grid;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int neighbors = countFilledNeighbors(x, y);
                if (grid[y][x] == 1) {
                    new_grid[y][x] = (neighbors >= 5) ? 1 : 0;
                } else {
                    new_grid[y][x] = (neighbors > 4) ? 1 : 0;
                }
            }
        }
        grid = new_grid;
    }
}

const std::vector<std::vector<int>>& GLBI_Map::getGrid() const {
    return grid;
}

// Place des gros blocs de murs (obstacles) loin des cases vides
void placeObstacles(GLBI_Map& map, int nbBlocs, int blocSize = 3) {
    int placed = 0;
    int tries = 0;
    while (placed < nbBlocs && tries < 1000) {
        tries++;
        int x0 = 1 + rand() % (map.width - blocSize - 1);
        int y0 = 1 + rand() % (map.height - blocSize - 1);
        bool canPlace = true;
        for (int dy = -1; dy <= blocSize; ++dy) {
            for (int dx = -1; dx <= blocSize; ++dx) {
                int x = x0 + dx;
                int y = y0 + dy;
                if (x < 0 || y < 0 || x >= map.width || y >= map.height) { canPlace = false; break; }
                if (map.grid[y][x] == 0) { canPlace = false; break; }
            }
            if (!canPlace) break;
        }
        if (canPlace) {
            for (int dy = 0; dy < blocSize; ++dy) {
                for (int dx = 0; dx < blocSize; ++dx) {
                    map.grid[y0 + dy][x0 + dx] = 3; // OBSTACLE
                }
            }
            placed++;
        }
    }
}

void GLBI_Map::addFeatures() {
    // Bord haut
    for (int x = 0; x < width; ++x) {
        grid[0][x] = 3;
    }
    // Bord bas
    for (int x = 0; x < width; ++x) {
        grid[height-1][x] = 3;
    }
    // Bord gauche
    for (int y = 0; y < height; ++y) {
        grid[y][0] = 3;
    }
    // Bord droit
    for (int y = 0; y < height; ++y) {
        grid[y][width-1] = 3;
    }

    // Place des obstacles
    placeObstacles(*this, 25, 2);

    // Place les objets (points)
    int totalObjects = 0;
    int tries = 0;
    while (totalObjects < 15 && tries < 1000) {
        tries++;
        int x = 1 + rand() % (width-2);
        int y = 1 + rand() % (height-2);
        if (grid[y][x] == 0) {
            grid[y][x] = 2; // OBJECT
            totalObjects++;
        }
    }

    // Place des pièges
    for (int y = 1; y < height-1; ++y) {
        for (int x = 1; x < width-1; ++x) {
            if (grid[y][x] == 0 && rand() % 100 < 1) {
                grid[y][x] = 4; // TRAP
            }
        }
    }
}

void GLBI_Map::generate(int steps) {
    simulate(steps);
    addFeatures();
}

}
