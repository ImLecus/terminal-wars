#pragma once
#include "tile.h"
// The higher the terrain is makes the units to boost their attack
// Movement resistance makes units more difficult to traverse the tile
class TerrainTile: public Tile {
public:
    TerrainTile(){
        is_unit = true;
    }
protected:
    int movement_resistance = 1;
    float height = 1;
};

class GrassTile: public TerrainTile {
public:
    GrassTile(): TerrainTile() {
        this->color = {"","\x1b[48;5;41m"};
        this->symbol = " ";
    }
};  

class ForestTile: public TerrainTile {
public:
    ForestTile(): TerrainTile() {
        this->color = {"","\x1b[48;5;35m"};
        this->symbol = "↟";
        this->height = 1.1f;
        this->movement_resistance = 2;
    }
};  

class RiverTile: public TerrainTile {
public:
    RiverTile(): TerrainTile() {
        this->color = {"","\x1b[48;5;31m"};
        this->symbol = " ";
        this->height = 0.8f;
    }
};  

class BeachTile: public TerrainTile {
public:
    BeachTile(): TerrainTile() {
        this->color = {"","\x1b[48;5;185m"};
        this->symbol = " ";
        this->height = 0.8f;
    }
};  

class OceanTile: public TerrainTile {
public:
    OceanTile(): TerrainTile() {
        this->color = {"","\x1b[48;5;26m"};
        this->symbol = " ";
        this->height = 0.8f;
    }
};  

class LowMountainTile: public TerrainTile {
public:
    LowMountainTile(): TerrainTile() {
        this->color = {"","\x1b[48;5;143m"};
        this->symbol = " ";
        this->height = 1.2f;
        this->movement_resistance = 2;
    }
};  

class MountainTile: public TerrainTile {
public:
    MountainTile(): TerrainTile() {
        this->color = {"","\x1b[48;5;136m"};
        this->symbol = "^";
        this->height = 1.4f;
        this->movement_resistance = 3;
    }
};

class ClaimableTerrainTile : public TerrainTile {
public:
    void claim(Colors color){
        this->color = TEAM_COLORS[(int)color];
    }
protected:
    ClaimableTerrainTile(Colors color): TerrainTile() {
        this->color = TEAM_COLORS[(int)color];
    }
};

class CityTile: public ClaimableTerrainTile {
public:
    CityTile(Colors color): ClaimableTerrainTile(color){
        this->symbol = "$";
    }
};  

class HouseTile: public ClaimableTerrainTile {
public:
    HouseTile(Colors color): ClaimableTerrainTile(color){
        this->symbol = "⌂";
    }
};  

class PortTile: public ClaimableTerrainTile {
public:
    PortTile(Colors color): ClaimableTerrainTile(color){
        this->symbol = "#";
    }
};  

class AirportTile: public ClaimableTerrainTile {
public:
    AirportTile(Colors color): ClaimableTerrainTile(color){
        this->symbol = "%";
    }
};  
