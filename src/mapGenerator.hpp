#pragma once
#include "utils.hpp"

namespace glbasimac {

struct GLBI_Map {
    GLBI_Map(int w, int h, float prob = 0.48f);

    void generateInitialMap();
    void simulate(int steps = 4);
    void addFeatures();
    void generate(int steps = 4);
    const std::vector<std::vector<int>>& getGrid() const;

    int countFilledNeighbors(int x, int y);

    int width, height;
    float fill_prob;
    std::vector<std::vector<int>> grid;
    void printDebug() const;
};

}
