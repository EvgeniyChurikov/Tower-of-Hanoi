#ifndef TOWER_OF_HANOI_SOLVER_H
#define TOWER_OF_HANOI_SOLVER_H

#include "Towers.h"
#include <list>
#include <iostream>

class Solver {
private:
    Towers *towers;
    std::list<std::pair<int, int>> alg;
    std::list<std::pair<int, int>>::const_iterator iter;
    void generateRecursive(int from, int to, int n);
public:
    Solver(Towers *towers);
    void generate();
    void reset();
    void next();
    void print(std::ostream &out);
};


#endif
