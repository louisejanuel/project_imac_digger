#include "mapGenerator.hpp"

MapGenerator::MapGenerator(int w, int h, int fillProb)
    : width(w), height(h), fillProbability(fillProb)
{
    std::srand(std::time(0));
    initializeMap();
}

void MapGenerator::initializeMap()
{
    map.resize(height, std::vector<int>(width));
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            map[y][x] = (std::rand() % 100 < fillProbability) ? FULL : EMPTY;
}

void MapGenerator::generate(int iterations)
{
    for (int i = 0; i < iterations; ++i)
        step();
    addFeatures(); // Ajout des pièges, obstacles, objets
}

void MapGenerator::step()
{
    std::vector<std::vector<int>> newMap = map;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int count = countFullNeighbors(x, y);
            if (map[y][x] == FULL)
                newMap[y][x] = (count >= 5) ? FULL : EMPTY;
            else
                newMap[y][x] = (count > 4) ? FULL : EMPTY;
        }
    }
    map = newMap;
}

int MapGenerator::countFullNeighbors(int x, int y) const
{
    int count = 0;
    for (int j = -1; j <= 1; j++)
        for (int i = -1; i <= 1; i++)
        {
            int nx = x + i, ny = y + j;
            if (nx >= 0 && ny >= 0 && nx < width && ny < height)
                if (map[ny][nx] == FULL)
                    count++;
        }
    return count;
}

void MapGenerator::addFeatures()
{
    totalObjects = 0;
    // Placer exactement 15 objets de manière aléatoire
    while (totalObjects < 15)
    {
        int x = rand() % width;  // Coordonnée X aléatoire
        int y = rand() % height; // Coordonnée Y aléatoire

        if (map[y][x] == EMPTY) 
        {
            map[y][x] = OBJECT;
            totalObjects++;
        }
    }

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (map[y][x] == FULL && rand() % 100 < 25) // 5% de chance de placer un obstacle
            {
                map[y][x] = OBSTACLE;
            }

            if (map[y][x] == EMPTY)
            {
                if (rand() % 100 < 0.10)
                {
                    map[y][x] = TRAP;
                }
            }
        }
    }
}

const std::vector<std::vector<int>> &MapGenerator::getMap() const
{
    return map;
}

std::vector<std::vector<int>> &MapGenerator::getMutableMap()
{
    return map;
}
