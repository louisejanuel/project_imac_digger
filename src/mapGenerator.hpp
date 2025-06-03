// #pragma once
// #include "utils.hpp"

// // enum TileType {
// //     EMPTY = 0,
// //     FULL = 1,
// //     OBJECT = 2,
// //     OBSTACLE = 3,
// //     TRAP = 4,
// //     // HIDDEN_OBJECT = 5
// // };

// struct MapGenerator {
//     MapGenerator(int width, int height, int fillProb);
//     void generate(int iterations);
//     const std::vector<std::vector<int>>& getMap() const;
//     std::vector<std::vector<int>>& getMutableMap();

//     int totalObjects;
//     int getTotalObjects() const { return totalObjects; }

//     int width, height, fillProbability;
//     std::vector<std::vector<int>> map;

//     void initializeMap();
//     int countFullNeighbors(int x, int y) const;
//     void step();
//     void addFeatures();
// };



#pragma once
#include <vector>

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
