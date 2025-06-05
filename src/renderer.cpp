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

        // Config carte
        setMapProjection(map.getGrid()[0].size(), map.getGrid().size());

        if (!isPaused)
        {
            drawMap(map.getGrid());

            auto &mapData = const_cast<std::vector<std::vector<int>> &>(map.getGrid());
            player.update(deltaTime, mapData);
            player.draw();

            int playerX = static_cast<int>(std::round(player.x));
            int playerY = static_cast<int>(std::round(player.y));
            flowfield.compute(playerX, playerY);

            ennemi.update(deltaTime, flowfield, mapData, player);
            ennemi.draw(map.getGrid());
        }
        else
        {
            // Pendant la pause, ne met à jour ni le joueur ni les ennemis
        }

        // Overlay
        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        setOverlayProjection(windowWidth, windowHeight);

        drawQuitButton(windowWidth, windowHeight);
        drawPauseButton(windowWidth, windowHeight);
        drawObjectCounter(windowWidth, windowHeight, player.getScore(), 15);

        // Gérer clics
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            if (handleQuitButtonClick(windowWidth, windowHeight, xpos, ypos))
            {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
            else if (handlePauseButtonClick(windowWidth, windowHeight, xpos, ypos))
            {
                isPaused = true;
            }
            else if (isPaused && handlePlayButtonClick(windowWidth, windowHeight, xpos, ypos))
            {
                isPaused = false;
            }
        }

        if (isPaused)
        {
            drawPlayOverlay(windowWidth, windowHeight);
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

void drawPauseButton(int windowWidth, int windowHeight)
{
    float buttonWidth = windowWidth * 0.1f;
    float buttonHeight = windowHeight * 0.05f;
    float buttonX = 25;
    float buttonY = 25;

    glColor3f(0.2f, 0.2f, 0.8f); // Bleu
    glBegin(GL_QUADS);
    glVertex2f(buttonX, buttonY);
    glVertex2f(buttonX + buttonWidth, buttonY);
    glVertex2f(buttonX + buttonWidth, buttonY + buttonHeight);
    glVertex2f(buttonX, buttonY + buttonHeight);
    glEnd();

    glColor3f(1.0f, 1.0f, 0.0f); // Jaune
    drawText(buttonX + buttonWidth / 4, buttonY + buttonHeight / 4, "Pause");
}

bool handlePauseButtonClick(int windowWidth, int windowHeight, double xpos, double ypos)
{
    float buttonWidth = windowWidth * 0.1f;
    float buttonHeight = windowHeight * 0.05f;
    float buttonX = 25;
    float buttonY = 25;

    return (xpos >= buttonX && xpos <= buttonX + buttonWidth &&
            ypos >= buttonY && ypos <= buttonY + buttonHeight);
}

void drawPlayOverlay(int windowWidth, int windowHeight)
{
    // Fond noir plein écran
    glColor4f(0.0f, 0.0f, 0.0f, 0.85f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(windowWidth, 0);
    glVertex2f(windowWidth, windowHeight);
    glVertex2f(0, windowHeight);
    glEnd();

    // GROS bouton rouge "Play" centré
    float buttonWidth = 200;
    float buttonHeight = 100;
    float buttonX = windowWidth / 2.0f - buttonWidth / 2;
    float buttonY = windowHeight / 2.0f - buttonHeight / 2;

    glColor3f(0.9f, 0.1f, 0.1f); // Rouge
    glBegin(GL_QUADS);
    glVertex2f(buttonX, buttonY);
    glVertex2f(buttonX + buttonWidth, buttonY);
    glVertex2f(buttonX + buttonWidth, buttonY + buttonHeight);
    glVertex2f(buttonX, buttonY + buttonHeight);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); // Blanc
    drawText(buttonX + 50, buttonY + 35, "PLAY");
}

bool handlePlayButtonClick(int windowWidth, int windowHeight, double xpos, double ypos)
{
    float buttonWidth = 200;
    float buttonHeight = 100;
    float buttonX = windowWidth / 2.0f - buttonWidth / 2;
    float buttonY = windowHeight / 2.0f - buttonHeight / 2;

    return (xpos >= buttonX && xpos <= buttonX + buttonWidth &&
            ypos >= buttonY && ypos <= buttonY + buttonHeight);
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