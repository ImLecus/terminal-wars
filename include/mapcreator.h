#pragma once
#include <deque>
#include <iostream>
#include "terrain.h"

class MapCreator {
public:
    void read(const char* path){
        FILE* f = fopen(path, "r");
        if(!f){
            return;
        }
        char ch;
        do {
            ch = fgetc(f);
            if(ch == EOF){
                break;
            }
            buffer.push_back(ch);
            ++size.x;
            if(ch == '\n'){
                ++size.y;
                size.x = 0;
                continue;
            }
            
            
        } while(ch != EOF);
        fclose(f);

    }

    TerrainTile get_tile(int i){
        char c = buffer[i];
        switch (c)
        {
        case 'G': return GrassTile();
        case 'F': return ForestTile();
        case 'M': return MountainTile();
        case 'L': return LowMountainTile();
        case 'B': return BeachTile();
        case 'R': return RiverTile();
        case 'O': return OceanTile();
        case 'C': return CityTile(Colors::UNCLAIMED);
        case 'H': return HouseTile(Colors::UNCLAIMED);
        case 'A': return AirportTile(Colors::UNCLAIMED);
        case 'P': return PortTile(Colors::UNCLAIMED);
        default:  return OceanTile();
        }
    }


    Pos size;
    std::deque<char> buffer; 
};