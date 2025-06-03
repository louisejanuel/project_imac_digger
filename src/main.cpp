#include "mapGenerator.hpp"
#include "renderer.hpp"
#include "utils.hpp"

int main()
{
    int choice = showMenu();
    if (choice == 1)
    {
        MapGenerator mapGen(60, 32, 45);
        mapGen.generate(5);
        FlowField flowfield(mapGen.getMap());

        Ennemi ennemi({});
        ennemi.placeEnemies(2, mapGen.getMap()); // Placer 2 ennemis aléatoirement

        Renderer renderer(1500, 800, mapGen, flowfield, ennemi);
        renderer.run();
    }
    return 0;
}
