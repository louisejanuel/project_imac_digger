#include "ennemis.hpp"

Ennemi::Ennemi(std::vector<Enemy> enemies)
    : enemies(std::move(enemies))
{
    tex = chargerTexture("assets/images/chat.png");
}

void Ennemi::update(float deltaTime, const FlowField &flow, const std::vector<std::vector<int>> &map, Player &player)
{
    for (auto &enemy : enemies)
    {
        Vec2 dir = flow.getDirection(enemy.x, enemy.y);
        float newX = enemy.x + dir.dx * deltaTime * enemy.speed;
        float newY = enemy.y + dir.dy * deltaTime * enemy.speed;

        // Si la direction initiale est bloquée, chercher une direction alternative
        if (willCollide(newX, enemy.y, map) || willCollide(enemy.x, newY, map))
        {
            Vec2 alternativeDir = findAlternativeDirection(enemy, flow, deltaTime, map);

            // Si une direction alternative est trouvée, l'utiliser
            if (alternativeDir.dx != 0 || alternativeDir.dy != 0)
            {
                newX = enemy.x + alternativeDir.dx * deltaTime * enemy.speed;
                newY = enemy.y + alternativeDir.dy * deltaTime * enemy.speed;
            }
            else
            {
                // Sinon, continuer dans la direction actuelle
                newX = enemy.x + dir.dx * deltaTime * enemy.speed;
                newY = enemy.y + dir.dy * deltaTime * enemy.speed;
            }
        }

        // Appliquer le déplacement
        if (!willCollide(newX, enemy.y, map))
            enemy.x = newX;
        if (!willCollide(enemy.x, newY, map))
            enemy.y = newY;

        // Vérifier la collision avec le joueur
        if (isCollidingWithPlayer(enemy, player))
        {
            std::cout << "Collision avec le joueur ! Game Over.\n";
            showGameOver(); // Afficher l'écran de fin de partie
            glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);
        }
    }
}

void Ennemi::draw(const std::vector<std::vector<int>> &map)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    glColor3f(1, 1, 1);

    for (const auto &e : enemies)
    {
        float s = 1.0f;
        float x = e.x;
        float y = e.y;
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(x, y);
        glTexCoord2f(1, 0);
        glVertex2f(x + s, y);
        glTexCoord2f(1, 1);
        glVertex2f(x + s, y + s);
        glTexCoord2f(0, 1);
        glVertex2f(x, y + s);
        glEnd();
    }

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

bool Ennemi::willCollide(float testX, float testY, const std::vector<std::vector<int>> &map)
{
    // Taille de l'ennemi
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

        // Vérifier si hors de la carte
        if (cx < 0 || cy < 0 || cy >= map.size() || cx >= map[0].size())
            return true;

        // Vérifier si la case est un mur ou un obstacle
        if (map[cy][cx] == FULL || map[cy][cx] == OBSTACLE)
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

bool Ennemi::isCollidingWithPlayer(const Enemy &enemy, const Player &player)
{
    float size = 0.99f; // Taille de l'ennemi et du joueur
    return enemy.x < player.x + size &&
           enemy.x + size > player.x &&
           enemy.y < player.y + size &&
           enemy.y + size > player.y;
}

Vec2 Ennemi::findAlternativeDirection(const Enemy &enemy, const FlowField &flow, float deltaTime, const std::vector<std::vector<int>> &map)
{
    for (const auto &neighbor : flow.neighbors)
    {
        float altX = enemy.x + neighbor.dx * deltaTime * enemy.speed;
        float altY = enemy.y + neighbor.dy * deltaTime * enemy.speed;

        if (!willCollide(altX, altY, map))
        {
            return neighbor;
        }
    }

    return {0, 0}; // Retourner une direction neutre si aucune alternative n'est trouvée
}
