#include "Solver.h"

Solver::Solver(Towers *towers_) {
    this->towers = towers_;
    generate();
}

void Solver::generate() {
    alg.clear();
    generateRecursive(0, 2, towers->getDisksAmount());
    reset();
}

void Solver::generateRecursive(int from, int to, int n) {
    if (n == 1) {
        alg.push_back(std::make_pair(from, to));
    }
    else {
        generateRecursive(from, 3 - from - to, n - 1);
        alg.push_back(std::make_pair(from, to));
        generateRecursive(3 - from - to, to, n - 1);
    }
}

void Solver::reset() {
    iter = alg.cbegin();
}

void Solver::next() {
    towers->move(iter->first, iter->second);
    ++iter;
}
