#include <GLFW/glfw3.h>
#include "mapGenerator.hpp"
#include "renderer.hpp"
#include "FlowField.hpp"
#include <iostream>

int main() {
    MapGenerator mapGen(150, 80, 45);
    mapGen.generate(5); 
    Renderer renderer(1500, 800, mapGen);
    renderer.run();
    return 0;
}
