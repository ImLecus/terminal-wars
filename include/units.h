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
    int price;
    Pos position;

    Unit(Colors color, int x, int y){
        this->position = {x,y};
        this->color = TEAM_COLORS[(int)color];
    }
};

// Infantery are the cheapest unit.
// They are not very efficient at combat, but
// they can be a good start.
class Infantery: public Unit {
public:
    Infantery(Colors color, int x, int y): Unit(color, x, y)  {
        this->symbol = "I";
        this->movement_range = 3;
        this->vision_range = 2;
        this->price = 1000;
    }
};

// Mechanized units are good against mechanical units.
class Mechanized: public Unit {
public:
    Mechanized(Colors color, int x, int y): Unit(color, x, y)  {
        this->symbol = "M";
        this->movement_range = 2;
        this->vision_range = 1;
        this->price = 3000;
    }
};