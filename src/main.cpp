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
        std::vector<Enemy> enemies = {
            Enemy{5.0f, 5.0f, 1.0f},
            Enemy{10.0f, 10.0f, 1.0f}};
        Ennemi ennemi(enemies);
        Renderer renderer(1500, 800, mapGen, flowfield, ennemi);
        renderer.run();
    }
    return 0;
}
