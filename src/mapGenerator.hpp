#pragma once
#include <vector>

class MapGenerator {
public:
    MapGenerator(int width, int height, int fillProb);
    void generate(int iterations);
    void printMap() const;
    const std::vector<std::vector<int>>& getMap() const;

private:
    int width, height, fillProbability;
    std::vector<std::vector<int>> map;

    void initializeMap();
    int countFullNeighbors(int x, int y) const;
    void step();
};
