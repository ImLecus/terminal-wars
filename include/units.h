#pragma once

enum UnitState {
    NORMAL,
    SELECTED
};

class Unit {
private:
    char symbol;
    int movement_range;
    int vision_range;
    char color;
};
