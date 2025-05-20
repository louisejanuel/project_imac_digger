#pragma once
#include <vector>

struct MapGenerator {
    MapGenerator(int width, int height, int fillProb);
    void generate(int iterations);
    const std::vector<std::vector<int>>& getMap() const;

    int width, height, fillProbability;
    std::vector<std::vector<int>> map;

    void initializeMap();
    int countFullNeighbors(int x, int y) const;
    void step();
};