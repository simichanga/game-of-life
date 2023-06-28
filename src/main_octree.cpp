#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <unordered_set>

constexpr std::size_t   WIDTH = 80,
                        HEIGHT = 60,
                        CELL_SIZE = 10;

class Cell;
using CellPtr = std::unique_ptr<Cell>;

class Cell {
public:
    explicit Cell(bool alive) : alive(alive) {}

    [[nodiscard]]
    const bool isAlive() const { return alive; }

private:
    bool alive;
    std::unordered_set<Cell*> neighbors;
};