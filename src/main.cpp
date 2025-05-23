// #include <GLFW/glfw3.h>
// #include "mapGenerator.hpp"
// #include "renderer.hpp"
// #include "FlowField.hpp"
// #include <iostream>


#include "mapGenerator.hpp"
#include "renderer.hpp"
#include "menu.hpp"

int main() {
    int choice = showMenu();
    if (choice == 1) {
        MapGenerator mapGen(150, 80, 45);
        mapGen.generate(5);
        Renderer renderer(1500, 800, mapGen);
        renderer.run();
    }
    return 0;
}
