#pragma once
#include <vector>

enum TileType {
    EMPTY = 0,
    FULL = 1,
    OBJECT = 2,
    OBSTACLE = 3,
    TRAP = 4,
    // HIDDEN_OBJECT = 5
};

struct MapGenerator {
    MapGenerator(int width, int height, int fillProb);
    void generate(int iterations);
    const std::vector<std::vector<int>>& getMap() const;
    std::vector<std::vector<int>>& getMutableMap();

    int totalObjects;
    int getTotalObjects() const { return totalObjects; }

    int width, height, fillProbability;
    std::vector<std::vector<int>> map;

    void initializeMap();
    int countFullNeighbors(int x, int y) const;
    void step();
    void addFeatures();
};