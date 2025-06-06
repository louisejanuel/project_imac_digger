#include "mapGenerator.hpp"

namespace glbasimac
{

    GLBI_Map::GLBI_Map(int w, int h, float prob)
        : width(w), height(h), fill_prob(prob)
    {
        assert(fill_prob >= 0.3f && fill_prob <= 0.7f);
        generateInitialMap();
    }

    void GLBI_Map::generateInitialMap()
    {
        grid = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
        for (int y = 0; y < height; ++y)
            for (int x = 0; x < width; ++x)
                grid[y][x] = (rand() / (float)RAND_MAX < fill_prob) ? FULL : EMPTY;
    }

    int GLBI_Map::countFilledNeighbors(int x, int y) const
    {
        int count = 0;
        for (int dy = -1; dy <= 1; ++dy)
        {
            for (int dx = -1; dx <= 1; ++dx)
            {
                int nx = x + dx;
                int ny = y + dy;
                if (nx < 0 || ny < 0 || nx >= width || ny >= height)
                {
                    count++;
                }
                else if (grid[ny][nx] == FULL)
                {
                    count++;
                }
            }
        }
        return count;
    }

    void GLBI_Map::simulate(int steps)
    {
        for (int s = 0; s < steps; ++s)
        {
            std::vector<std::vector<int>> new_grid = grid;
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    int neighbors = countFilledNeighbors(x, y);
                    if (grid[y][x] == FULL)
                    {
                        new_grid[y][x] = (neighbors >= 5) ? FULL : EMPTY;
                    }
                    else
                    {
                        new_grid[y][x] = (neighbors > 4) ? FULL : EMPTY;
                    }
                }
            }
            grid = new_grid;
        }
    }

    const std::vector<std::vector<int>> &GLBI_Map::getGrid() const
    {
        return grid;
    }

    // Place les obstacles loin des cases vides
    void placeObstacles(GLBI_Map &map, int nbBlocs, int blocSize = 3)
    {
        int placed = 0;
        int tries = 0;
        while (placed < nbBlocs && tries < 1000)
        {
            tries++;
            int x0 = 1 + rand() % (map.width - blocSize - 1);
            int y0 = 1 + rand() % (map.height - blocSize - 1);
            bool canPlace = true;
            for (int dy = -1; dy <= blocSize; ++dy)
            {
                for (int dx = -1; dx <= blocSize; ++dx)
                {
                    int x = x0 + dx;
                    int y = y0 + dy;
                    if (x < 0 || y < 0 || x >= map.width || y >= map.height)
                    {
                        canPlace = false;
                        break;
                    }
                    if (map.grid[y][x] == EMPTY)
                    {
                        canPlace = false;
                        break;
                    }
                }
                if (!canPlace)
                    break;
            }
            if (canPlace)
            {
                for (int dy = 0; dy < blocSize; ++dy)
                {
                    for (int dx = 0; dx < blocSize; ++dx)
                    {
                        map.grid[y0 + dy][x0 + dx] = OBSTACLE;
                    }
                }
                placed++;
            }
        }
    }

    void GLBI_Map::addFeatures()
    {
        // Bords
        for (int x = 0; x < width; ++x)
        {
            grid[0][x] = OBSTACLE;
            grid[height - 1][x] = OBSTACLE;
        }
        for (int y = 0; y < height; ++y)
        {
            grid[y][0] = OBSTACLE;
            grid[y][width - 1] = OBSTACLE;
        }

        // Obstacles
        placeObstacles(*this, 25, 2);

        // Objets
        int totalObjects = 0;
        int tries = 0;
        while (totalObjects < 15 && tries < 1000)
        {
            tries++;
            int x = 1 + rand() % (width - 2);
            int y = 1 + rand() % (height - 2);
            if (grid[y][x] == EMPTY)
            {
                grid[y][x] = OBJECT;
                totalObjects++;
            }
        }

        // Pièges
        for (int y = 1; y < height - 1; ++y)
        {
            for (int x = 1; x < width - 1; ++x)
            {
                if (grid[y][x] == EMPTY && rand() % 100 < 1)
                {
                    grid[y][x] = TRAP;
                }
            }
        }
    }

    void GLBI_Map::generate(int steps)
    {
        simulate(steps);
        addFeatures();
    }

}
