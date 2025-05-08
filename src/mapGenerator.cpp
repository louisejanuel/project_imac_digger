#include "MapGenerator.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

MapGenerator::MapGenerator(int w, int h, int fillProb) 
    : width(w), height(h), fillProbability(fillProb) {
    std::srand(std::time(0));
    initializeMap();
}

void MapGenerator::initializeMap() {
    map.resize(height, std::vector<int>(width));
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            map[y][x] = (std::rand() % 100 < fillProbability) ? 1 : 0;
}

void MapGenerator::generate(int iterations) {
    for (int i = 0; i < iterations; ++i)
        step();
}

void MapGenerator::step() {
    std::vector<std::vector<int>> newMap = map;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int count = countFullNeighbors(x, y);
            if (map[y][x] == 1)
                newMap[y][x] = (count >= 5) ? 1 : 0;
            else
                newMap[y][x] = (count > 4) ? 1 : 0;
        }
    }
    map = newMap;
}

int MapGenerator::countFullNeighbors(int x, int y) const {
    int count = 0;
    for (int j = -1; j <= 1; j++)
        for (int i = -1; i <= 1; i++) {
            int nx = x + i, ny = y + j;
            if (nx >= 0 && ny >= 0 && nx < width && ny < height)
                if (map[ny][nx] == 1)
                    count++;
        }
    return count;
}

void MapGenerator::printMap() const {
    for (const auto& row : map) {
        for (int cell : row)
            std::cout << (cell ? "#" : ".");
        std::cout << '\n';
    }
}

const std::vector<std::vector<int>>& MapGenerator::getMap() const {
    return map;
}
