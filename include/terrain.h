#pragma once
#include "tile.h"

// The higher the terrain is makes the units to boost their attack
// Movement resistance makes units more difficult to traverse the tile
class TerrainTile: public Tile {
protected:
    int movement_resistance = 1;
    int height = 1;
};

class GrassTile: public TerrainTile {
public:
    GrassTile(){
        this->color = "\x1b[32m";
        this->symbol = "_";
    }
};  