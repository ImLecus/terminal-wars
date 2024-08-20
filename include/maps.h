#pragma once
#include "terrain.h"
#include "units.h"
#include <string>
#include <string.h>
class Map {
public:
    Map(const char* filepath){
        FILE* f = fopen(filepath, "r");
        if(!f){
            std::cout << "Could not open file '" << filepath << "'\n";
            return;
        }
        // Determine the size of the map (max is 64x64)
        std::string content;
        this->size = {0,0};
        char ch;
        do {
            ch = fgetc(f);
            if(ch == EOF){
                break;
            }
            content.push_back(ch);
            if(ch == '\n'){
                ++this->size.y;
                this->size.x = 0;
                continue;
            }
            ++this->size.x;
            
        } while(ch != EOF);

        fclose(f);
        
        
        int x = 0, y = 0;
        for(int i = 0; i < content.length(); ++i){
            switch (content.at(i))     {
            case '\n':
                x = -1;
                ++y;
                break;
            case 'G':
                this->terrain[y][x] = GrassTile();
                break;
            case 'M':
                this->terrain[y][x] = MountainTile();
                break;
            case 'L':
                this->terrain[y][x] = LowMountainTile();
                break;
            case 'B':
                this->terrain[y][x] = BeachTile();
                break;
            case 'R':
                this->terrain[y][x] = RiverTile();
                break;
            case 'O':
                this->terrain[y][x] = OceanTile();
                break;
            case 'C':
                this->terrain[y][x] = CityTile(Colors::UNCLAIMED);
                break;
            case 'H':
                this->terrain[y][x] = HouseTile(Colors::UNCLAIMED);
                break;
            
            case 'A':
                this->terrain[y][x] = AirportTile(Colors::UNCLAIMED);
                break;
            case 'P':
                this->terrain[y][x] = PortTile(Colors::UNCLAIMED);
                break;
            default:
                this->terrain[y][x] = OceanTile();
                break;
            }
            ++x;
        }


    }

    void draw(){
        for(int y = 0; y <= this->size.y; ++y){
            for(int x = 0; x < this->size.x; ++x){
                if(!this->units[y][x].empty){
                    this->units[y][x].print(
                        merge_colors(this->terrain[y][x],this->units[y][x])
                    );
                    continue;
                }
                this->terrain[y][x].print();
            }
            printf("%c",'\n');
        }
    }

    void claim(int x, int y, Colors color){
        static_cast<ClaimableTerrainTile*>(&terrain[y][x])->claim(color);
    }

    void addUnit(Unit u){
        units[u.position.y][u.position.x] = u;
    }

private:
    Pos size;
    TerrainTile terrain[64][64];
    Unit units[64][64];  
};
