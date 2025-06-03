#include "ennemis.hpp"

Ennemi::Ennemi(std::vector<Enemy> enemies)
    : enemies(std::move(enemies)) {}

void Ennemi::update(float deltaTime, const FlowField &flow, const std::vector<std::vector<int>> &map)
{
    for (auto &enemy : enemies)
    {
        Vec2 dir = flow.getDirection(enemy.x, enemy.y);
        float newX = enemy.x + dir.dx * deltaTime * enemy.speed;
        float newY = enemy.y + dir.dy * deltaTime * enemy.speed;

        // Si la direction initiale est bloquée, chercher une direction alternative
        if (willCollide(newX, enemy.y, map) || willCollide(enemy.x, newY, map))
        {
            Vec2 bestDir = {0, 0};
            int minDist = std::numeric_limits<int>::max();

            // Parcourir les voisins pour trouver une direction alternative
            for (const auto &neighbor : flow.neighbors)
            {
                float altX = enemy.x + neighbor.dx * deltaTime * enemy.speed;
                float altY = enemy.y + neighbor.dy * deltaTime * enemy.speed;

                int nx = static_cast<int>(altX);
                int ny = static_cast<int>(altY);

                if (!willCollide(altX, altY, map) && flow.distance[ny][nx] >= 0 && flow.distance[ny][nx] < minDist)
                {
                    minDist = flow.distance[ny][nx];
                    bestDir = neighbor;
                }
            }

            // Mettre à jour la direction avec la meilleure alternative
            newX = enemy.x + bestDir.dx * deltaTime * enemy.speed;
            newY = enemy.y + bestDir.dy * deltaTime * enemy.speed;
        }

        // Appliquer le déplacement
        if (!willCollide(newX, enemy.y, map))
            enemy.x = newX;
        if (!willCollide(enemy.x, newY, map))
            enemy.y = newY;
    }
}

void Ennemi::draw(const std::vector<std::vector<int>> &map)
{
    glColor3f(0.3f, 0.3f, 0.3f);
    for (const auto &e : enemies)
    {
        float s = 1.0f;
        float x = e.x;
        float y = e.y;
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + s, y);
        glVertex2f(x + s, y + s);
        glVertex2f(x, y + s);
        glEnd();
    }
}

bool Ennemi::willCollide(float testX, float testY, const std::vector<std::vector<int>> &map)
{
    // 4 coins du carré (taille 1)
    float size = .99f;
    float corners[4][2] = {
        {testX, testY},
        {testX + size, testY},
        {testX, testY + size},
        {testX + size, testY + size}};

    for (int i = 0; i < 4; ++i)
    {
        int cx = int(corners[i][0]);
        int cy = int(corners[i][1]);

        if (cx < 0 || cy < 0 || cy >= map.size() || cx >= map[0].size())
            return true; // hors map = collision

        if (map[cy][cx] == 1 || map[cy][cx] == 3) // mur, obstacle
            return true;
    }

    return false;
}

void Ennemi::placeEnemies(int numEnemies, const std::vector<std::vector<int>> &map)
{
    int mapHeight = map.size();
    int mapWidth = map[0].size();

    enemies.clear(); // Réinitialiser la liste des ennemis

    for (int i = 0; i < numEnemies; ++i)
    {
        int enemyX, enemyY;
        do
        {
            enemyX = rand() % mapWidth;
            enemyY = rand() % mapHeight;
        } while (map[enemyY][enemyX] != EMPTY); // Vérifier que la case est EMPTY

        enemies.emplace_back(Enemy{static_cast<float>(enemyX), static_cast<float>(enemyY), 1.0f});
    }
}
