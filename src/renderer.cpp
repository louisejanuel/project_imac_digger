// #include "renderer.hpp"

// Renderer::Renderer(int screenW, int screenH, MapGenerator &mapGen, FlowField &flow, Ennemi ennemi)
//     : width(screenW), height(screenH), map(mapGen), flowfield(flow),
//       player(0.0f, 0.0f, 0.99f), ennemi(std::move(ennemi))
// {
//     if (!glfwInit())
//     {
//         std::cerr << "Erreur GLFW\n";
//         exit(-1);
//     }

//     window = glfwCreateWindow(width, height, "IMAC Digger", nullptr, nullptr);
//     if (!window)
//     {
//         std::cerr << "Erreur création fenêtre GLFW\n";
//         glfwTerminate();
//         exit(-1);
//     }

//     glfwMakeContextCurrent(window);

//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluOrtho2D(0, map.getMap()[0].size(), map.getMap().size(), 0);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();

//     lastFrameTime = glfwGetTime();

//     const std::vector<std::vector<int>> &mapData = map.getMap();
//     int mapHeight = mapData.size();
//     int mapWidth = mapData[0].size();

//     int playerX, playerY;
//     do
//     {
//         playerX = rand() % mapWidth;
//         playerY = rand() % mapHeight;
//     } while (mapData[playerY][playerX] != EMPTY);

//     player = Player(static_cast<float>(playerX), static_cast<float>(playerY), 0.99f);
// }

// void Renderer::run()
// {
//     while (!glfwWindowShouldClose(window))
//     {
//         float currentTime = glfwGetTime();
//         float deltaTime = currentTime - lastFrameTime;
//         lastFrameTime = currentTime;

//         glClear(GL_COLOR_BUFFER_BIT);
//         glLoadIdentity();

//         drawMap(map.getMap());

//         std::vector<std::vector<int>> &mapData = const_cast<std::vector<std::vector<int>> &>(map.getMap());
//         player.update(deltaTime, mapData);
//         player.draw();

//         int playerX = static_cast<int>(std::round(player.x));
//         int playerY = static_cast<int>(std::round(player.y));
//         flowfield.compute(playerX, playerY);

//         ennemi.update(deltaTime, flowfield, map.getMap());
//         ennemi.draw(map.getMap());

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glfwTerminate();
// }

// void drawMap(const std::vector<std::vector<int>> &map)
// {
//     int height = map.size();
//     int width = map[0].size();

//     for (int y = 0; y < height; ++y)
//     {
//         for (int x = 0; x < width; ++x)
//         {
//             switch (map[y][x])
//             {
//             case EMPTY:
//                 glColor3f(1.0f, 1.0f, 1.0f);
//                 break;
//             case FULL:
//                 glColor3f(0.5f, 0.25f, 0.0f);
//                 break;
//             case OBJECT:
//                 glColor3f(1.0f, 0.0f, 1.0f);
//                 break;
//             case OBSTACLE:
//                 glColor3f(0.0f, 0.0f, 0.0f);
//                 break;
//             case TRAP:
//                 glColor3f(0.0f, 0.0f, 1.0f);
//                 break;
//             default:
//                 glColor3f(0.8f, 0.8f, 0.8f);
//                 break;
//             }

//             glBegin(GL_QUADS);
//             glVertex2f(x, y);
//             glVertex2f(x + 1, y);
//             glVertex2f(x + 1, y + 1);
//             glVertex2f(x, y + 1);
//             glEnd();
//         }
//     }
// }

#include "renderer.hpp"

Renderer::Renderer(int screenW, int screenH, glbasimac::GLBI_Map &mapGen, FlowField &flow, Ennemi ennemi)
    : width(screenW), height(screenH), map(mapGen), flowfield(flow),
      player(0.0f, 0.0f, 0.99f), ennemi(std::move(ennemi))
{
    if (!glfwInit())
    {
        std::cerr << "Erreur GLFW\n";
        exit(-1);
    }

    window = glfwCreateWindow(width, height, "IMAC Digger", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Erreur création fenêtre GLFW\n";
        glfwTerminate();
        exit(-1);
    }

    glfwSetWindowSizeCallback(window, onWindowResized);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, map.getGrid()[0].size(), map.getGrid().size(), 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    lastFrameTime = glfwGetTime();

    const auto &mapData = map.getGrid();
    int mapHeight = mapData.size();
    int mapWidth = mapData[0].size();

    int playerX, playerY;
    do
    {
        playerX = rand() % mapWidth;
        playerY = rand() % mapHeight;
    } while (mapData[playerY][playerX] != EMPTY); // Assure que EMPTY est bien défini

    player = Player(static_cast<float>(playerX), static_cast<float>(playerY), 0.99f);
}

void Renderer::run()
{
    while (!glfwWindowShouldClose(window))
    {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        glClear(GL_COLOR_BUFFER_BIT);

        // Configurer la projection pour la carte
        setMapProjection(map.getGrid()[0].size(), map.getGrid().size());

        // Dessiner la carte et les éléments du jeu
        drawMap(map.getGrid());

        auto &mapData = const_cast<std::vector<std::vector<int>> &>(map.getGrid());
        player.update(deltaTime, mapData);
        player.draw();

        int playerX = static_cast<int>(std::round(player.x));
        int playerY = static_cast<int>(std::round(player.y));
        flowfield.compute(playerX, playerY);

        ennemi.update(deltaTime, flowfield, mapData, player);
        ennemi.draw(map.getGrid());

        // Obtenir les dimensions de la fenêtre
        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);

        // Configurer la projection pour l'overlay
        setOverlayProjection(windowWidth, windowHeight);

        // Dessiner le bouton "Quitter"
        drawQuitButton(windowWidth, windowHeight);

        // Dessiner le compteur des objets
        drawObjectCounter(windowWidth, windowHeight, player.getScore(), 15);

        // Gérer les clics sur le bouton "Quitter"
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS &&
            handleQuitButtonClick(windowWidth, windowHeight, xpos, ypos))
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void onWindowResized(GLFWwindow * /*window*/, int width, int height)
{
    aspectRatio = width / (float)height;
    glViewport(0, 0, width, height);
    if (aspectRatio > 1.0)
    {
        myEngine.set2DProjection(-GL_VIEW_SIZE * aspectRatio / 2.,
                                 GL_VIEW_SIZE * aspectRatio / 2.,
                                 -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
    }
    else
    {
        myEngine.set2DProjection(-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
                                 -GL_VIEW_SIZE / (2. * aspectRatio),
                                 GL_VIEW_SIZE / (2. * aspectRatio));
    }
}

void drawMap(const std::vector<std::vector<int>> &map)
{
    int height = map.size();
    int width = map[0].size();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            switch (map[y][x])
            {
            case EMPTY:
                glColor3f(1.0f, 1.0f, 1.0f);
                break;
            case FULL:
                glColor3f(0.5f, 0.25f, 0.0f);
                break;
            case OBJECT:
                glColor3f(1.0f, 0.0f, 1.0f);
                break;
            case OBSTACLE:
                glColor3f(0.0f, 0.0f, 0.0f);
                break;
            case TRAP:
                glColor3f(0.0f, 0.0f, 1.0f);
                break;
            default:
                glColor3f(0.8f, 0.8f, 0.8f);
                break;
            }

            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + 1, y);
            glVertex2f(x + 1, y + 1);
            glVertex2f(x, y + 1);
            glEnd();
        }
    }
}

void drawQuitButton(int windowWidth, int windowHeight)
{
    // Dimensions du bouton
    float buttonWidth = windowWidth * 0.1f;    // 10% de la largeur de la fenêtre
    float buttonHeight = windowHeight * 0.05f; // 5% de la hauteur de la fenêtre

    // Position du bouton (en haut à droite)
    float buttonX = windowWidth - buttonWidth - 25; // 10 pixels de marge
    float buttonY = 25;                             // 10 pixels de marge depuis le haut

    // Dessin du bouton (rouge)
    glColor3f(0.8f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(buttonX, buttonY);
    glVertex2f(buttonX + buttonWidth, buttonY);
    glVertex2f(buttonX + buttonWidth, buttonY + buttonHeight);
    glVertex2f(buttonX, buttonY + buttonHeight);
    glEnd();

    // Texte "Quitter" (jaune)
    glColor3f(1.0f, 1.0f, 0.0f);
    drawText(buttonX + buttonWidth / 4, buttonY + buttonHeight / 4, "Quitter");
}

bool handleQuitButtonClick(int windowWidth, int windowHeight, double xpos, double ypos)
{
    bool result = false;
    // Dimensions du bouton
    float buttonWidth = windowWidth * 0.1f;
    float buttonHeight = windowHeight * 0.05f;

    // Position du bouton
    float buttonX = windowWidth - buttonWidth - 10;
    float buttonY = 10;

    result = (xpos >= buttonX && xpos <= buttonX + buttonWidth && ypos >= buttonY && ypos <= buttonY + buttonHeight);

    return result;
}

void setOverlayProjection(int windowWidth, int windowHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowWidth, windowHeight, 0, -1, 1); // Projection en pixels
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setMapProjection(int mapWidth, int mapHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, mapWidth, mapHeight, 0, -1, 1); // Projection basée sur les dimensions de la carte
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawObjectCounter(int windowWidth, int windowHeight, int score, int totalObjects)
{
    // Position du texte (au milieu en haut)
    float textX = windowWidth / 2.0f - 50; // Ajustez la position horizontale si nécessaire
    float textY = 30;                      // Position verticale (en haut)

    // Texte à afficher
    std::string text = "Score : " + std::to_string(score) + " / " + std::to_string(totalObjects);

    // Dessiner le texte
    glColor3f(1.0f, 1.0f, 1.0f); // Blanc
    drawText(textX, textY, text.c_str());
}