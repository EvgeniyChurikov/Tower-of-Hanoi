#include "Towers.h"

Towers::Towers() {
    disksAmount = 3;
    reset();
}

std::array<std::vector<int>, 3> Towers::getRods() const {
    return this->rods;
}

int Towers::getMoves() const {
    return this->moves;
}

void Towers::reset() {
    reset(disksAmount);
}

void Towers::reset(int n) {
    for (std::vector<int>& rod : rods) {
        rod.clear();
    }
    for (int i = 0; i < n; ++i) {
        rods[0].push_back(n - i);
    }
    disksAmount = n;
    moves = 0;
}

void Towers::move(int from, int to) {
    if (!rods[from].empty() && (rods[to].empty() || rods[to].back() > rods[from].back())) {
        rods[to].push_back(rods[from].back());
        rods[from].pop_back();
        ++moves;
    }
}

bool Towers::isComplete() {
    return rods[0].empty() && rods[1].empty();
}

int Towers::getDisksAmount() {
    return disksAmount;
}

