#include <GLFW/glfw3.h>
#include "mapGenerator.hpp"
#include "renderer.hpp"
#include "Grid.hpp"
#include "FlowField.hpp"
#include <iostream>

int main() {
    // Générer la carte
    MapGenerator generator(40, 30, 45); // largeur, hauteur, densité de murs
    generator.generate(5); // 5 itérations de l’automate

    // Lancer le rendu
    Renderer renderer(800, 600, generator);
    renderer.run();

    // LES SUPERS CHANGEMENTS DE LOUISE

    // Grid grid(10, 10);
    // grid.at(5, 5).type = CellType::Wall; // exemple de mur

    // FlowField flow(grid);
    // flow.compute(9, 9); // joueur en bas à droite

    // // Affichage des directions
    // for (int y = 0; y < grid.getHeight(); ++y) {
    //     for (int x = 0; x < grid.getWidth(); ++x) {
    //         Vec2 dir = flow.getDirection(x, y);
    //         if (grid.at(x, y).type == CellType::Wall) {
    //             std::cout << "# ";
    //         } else if (dir.dx == 0 && dir.dy == 0) {
    //             std::cout << ". ";
    //         } else if (dir.dx == 1) std::cout << "->";
    //         else if (dir.dx == -1) std::cout << "<-";
    //         else if (dir.dy == 1) std::cout << "|";
    //         else if (dir.dy == -1) std::cout << "^";
    //     }
    //     std::cout << "\n";
    // }

    return 0;
}
