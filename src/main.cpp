#include "mapGenerator.hpp"
#include "renderer.hpp"
#include "utils.hpp"

int main()
{
    int choice = showMenu();
    if (choice == 1)
    {
        glbasimac::GLBI_Map mapGen(60, 32);
        mapGen.generate(5);
        FlowField flowfield(mapGen.getGrid());

        Ennemi ennemi({});
        ennemi.placeEnemies(2, mapGen.getGrid()); // Placer 2 ennemis aléatoirement

        Renderer renderer(1500, 800, mapGen, flowfield, ennemi);
        renderer.run();
    }
    return 0;
}
