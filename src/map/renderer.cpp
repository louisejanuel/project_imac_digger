#include "renderer.hpp"
#include "stb_image.h"

Renderer::Renderer(int screenW, int screenH, glbasimac::GLBI_Map &mapGen, FlowField &flow, Ennemi ennemi, GLFWwindow *win)
    : width(screenW), height(screenH), map(mapGen), flowfield(flow),
      player(0.0f, 0.0f, 0.99f), ennemi(std::move(ennemi)), window(win)
{

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
    } while (mapData[playerY][playerX] != EMPTY);

    player = Player(static_cast<float>(playerX), static_cast<float>(playerY), 0.99f);
}

GLuint chargerTexture(const char *filename)
{
    int width, height, channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 4);
    if (!data)
    {
        std::cerr << "Erreur chargement image : " << filename << std::endl;
        return 0;
    }
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_image_free(data);
    return texture;
}

void drawCaseTexture(float xpos, float ypos, float cellWidth, float cellHeight, GLuint texture)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(xpos, ypos);
    glTexCoord2f(1, 0);
    glVertex2f(xpos + cellWidth, ypos);
    glTexCoord2f(1, 1);
    glVertex2f(xpos + cellWidth, ypos + cellHeight);
    glTexCoord2f(0, 1);
    glVertex2f(xpos, ypos + cellHeight);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void drawMap(const GLBI_Map &map, GLuint tex_mur, GLuint tex_sol, GLuint tex_objet, GLuint tex_piege, GLuint tex_obstacle)
{
    int largeur = map.width;
    int hauteur = map.height;

    float cellWidth = 1.0f;
    float cellHeight = 1.0f;

    for (int y = 0; y < hauteur; ++y)
    {
        for (int x = 0; x < largeur; ++x)
        {
            float xpos = static_cast<float>(x);
            float ypos = static_cast<float>(y);

            // Texture correspondante
            switch (map.grid[y][x])
            {
            case EMPTY:
                drawCaseTexture(xpos, ypos, cellWidth, cellHeight, tex_sol);
                break;
            case FULL:
                drawCaseTexture(xpos, ypos, cellWidth, cellHeight, tex_mur);
                break;
            case OBJECT:
                drawCaseTexture(xpos, ypos, cellWidth, cellHeight, tex_objet);
                break;
            case OBSTACLE:
                drawCaseTexture(xpos, ypos, cellWidth, cellHeight, tex_obstacle);
                break;
            case TRAP:
                drawCaseTexture(xpos, ypos, cellWidth, cellHeight, tex_piege);
                break;
            default:
                break;
            }
        }
    }
}

void Renderer::run()
{
    GLuint tex_mur = chargerTexture("assets/images/mur.png");
    GLuint tex_sol = chargerTexture("assets/images/sol.png");
    GLuint tex_objet = chargerTexture("assets/images/fromage.png");
    GLuint tex_piege = chargerTexture("assets/images/trou.png");
    GLuint tex_obstacle = chargerTexture("assets/images/obstacle.png");

    while (!glfwWindowShouldClose(window))
    {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        glClear(GL_COLOR_BUFFER_BIT);
        // drawMap(map.getGrid());

        // auto &mapData = const_cast<std::vector<std::vector<int>> &>(map.getGrid());

        // Config carte
        setMapProjection(map.getGrid()[0].size(), map.getGrid().size());

        if (!isPaused)
        {
            drawMap(map, tex_mur, tex_sol, tex_objet, tex_piege, tex_obstacle);

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
