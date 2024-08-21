#pragma once
#include "tile.h"

enum UnitState {
    NORMAL,
    SELECTED,
    FINISHED
};

enum UnitMovementType {
    GROUND,
    WATER,
    AIR  
};

// Units are basically tiles with movement and actions
class Unit: public Tile {
public:
    Unit(){
        empty = true;
    }
    Unit(Colors color, int x, int y){
        this->position = Pos{x,y};
        this->color = TEAM_COLORS[(int)color];
        is_unit = true;
    }
    inline void print(Color color){
        printf("%s%s%s" ANSI_RESET, color.foreground, color.background, this->symbol);
    }

    void move(Pos new_position){
        this->position = new_position;
    }
    void move(int x, int y){
        this->position.x += x;
        this->position.y += y;
    }

    Pos position;
    bool empty;
    UnitState state;
    UnitMovementType type;
protected:
    int movement_range;
    int vision_range;
    int price;
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

// Mechanized units are good against mechanical units.
class Tank: public Unit {
public:
    Tank(Colors color, int x, int y): Unit(color, x, y)  {
        this->symbol = "T";
        this->movement_range = 4;
        this->vision_range = 2;
        this->price = 7000;
    }
};