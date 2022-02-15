#ifndef TOWER_OF_HANOI_TOWERS_H
#define TOWER_OF_HANOI_TOWERS_H

#include <array>
#include <vector>

class Towers {
private:
    std::array<std::vector<int>, 3> rods;
    int moves, disksAmount;
public:
    Towers();

    std::array<std::vector<int>, 3> getRods() const;

    int getMoves() const;

    int getDisksAmount();

    void reset();

    void reset(int n);

    void move(int from, int to);

    bool isComplete();
};

#endif
