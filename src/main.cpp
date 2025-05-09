#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    if (!glfwInit()) {
        std::cerr << "Erreur d'initialisation de GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Map Digger", NULL, NULL);
    if (!window) {
        std::cerr << "Erreur de création de la fenêtre" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Définir la couleur de fond
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Fond noir

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);  // Effacer l'écran (à chaque frame)

        // Dessiner un carré
        glBegin(GL_QUADS);
        glColor3f(0.0f, 1.0f, 0.0f);  // Couleur verte
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f(-0.5f,  0.5f);
        glEnd();

        glfwSwapBuffers(window);  // Afficher la fenêtre
        glfwPollEvents();  // Gérer les événements
    }

    glfwTerminate();  // Libérer les ressources GLFW
    return 0;
}
