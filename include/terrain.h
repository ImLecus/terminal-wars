#pragma once
#include "tile.h"

// The higher the terrain is makes the units to boost their attack
// Movement resistance makes units more difficult to traverse the tile
class TerrainTile: public Tile {
public:
protected:
    int movement_resistance = 1;
    float height = 1;
};

class GrassTile: public TerrainTile {
public:
    GrassTile(){
        this->color = "\x1b[102m";
        this->symbol = " ";
    }
};  

class RiverTile: public TerrainTile {
public:
    RiverTile(){
        this->color = "\x1b[46m";
        this->symbol = " ";
        this->height = 0.8f;
    }
};  

class BeachTile: public TerrainTile {
public:
    BeachTile(){
        this->color = "\x1b[46m";
        this->symbol = " ";
        this->height = 0.8f;
    }
};  

class OceanTile: public TerrainTile {
public:
    OceanTile(){
        this->color = "\x1b[44m";
        this->symbol = " ";
        this->height = 0.8f;
    }
};  

class LowMountainTile: public TerrainTile {
public:
    LowMountainTile(){
        this->color = "\x1b[43m";
        this->symbol = " ";
        this->height = 1.2f;
        this->movement_resistance = 2;
    }
};  

class MountainTile: public TerrainTile {
public:
    MountainTile(){
        this->color = "\x1b[43m";
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
    ClaimableTerrainTile(Colors color){
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
