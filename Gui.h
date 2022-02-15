#ifndef TOWER_OF_HANOI_GUI_H
#define TOWER_OF_HANOI_GUI_H

#include "Towers.h"
#include "Solver.h"

/*
 * Controls:
 * 1,2,3 — move disks
 * backspace — reset tower
 * +,- — change disks amount
 * enter — auto solve
 * Up/Down — change auto solving speed
 */

class Gui {
private:
    Towers *towers;
    Solver *solver;
public:
    Gui(Towers *towers, Solver *solver);

    void run();
};

#endif
