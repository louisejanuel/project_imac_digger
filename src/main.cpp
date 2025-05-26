#include "mapGenerator.hpp"
#include "renderer.hpp"
#include "menu.hpp"

int main() {
    int choice = showMenu();
    if (choice == 1) {
        MapGenerator mapGen(150, 80, 45);
        mapGen.generate(5);
        FlowField flowfield(mapGen.getMap());
        Renderer renderer(1500, 800, mapGen, flowfield);
        renderer.run();
    }
    return 0;
}
