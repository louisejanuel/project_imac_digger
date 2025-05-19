#include <GLFW/glfw3.h>
#include "mapGenerator.hpp"
#include "renderer.hpp"

int main() {
    // Générer la carte
    MapGenerator generator(40, 30, 45); // largeur, hauteur, densité de murs
    generator.generate(5); // 5 itérations de l’automate

    // Lancer le rendu
    Renderer renderer(800, 600, generator);
    renderer.run();

    return 0;
}
