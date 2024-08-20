#pragma once
#include "tile.h"


enum UnitState {
    NORMAL,
    SELECTED
};

// Units are basically tiles with movement and actions
class Unit: public Tile {
protected:
    int movement_range;
    int vision_range;
};

// Infantery are the cheapest unit.
// They are not very efficient at combat, but
// they can be a good start.
class Infantery: public Unit {
public:
    Infantery(Colors color)  {
        this->symbol = "I";
        this->movement_range = 3;
        this->vision_range = 2;
        this->color = TEAM_COLORS[(int)color];
    }
};
