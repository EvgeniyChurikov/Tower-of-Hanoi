#include <iostream>
#include "Gui.h"

int main() {
    std::cout << "Hello World!" << std::endl;
    Towers towers;
    Solver solver(&towers);
    Gui gui(&towers, &solver);
    gui.run();

    return 0;
}
