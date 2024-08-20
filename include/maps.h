#pragma once
#include "terrain.h"
#include "units.h"
#include <string>
#include <vector>
class Map {
public:
    Map(const char* filepath){
        units.reserve(64);

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
            ++this->size.x;
            if(ch == '\n'){
                ++this->size.y;
                this->size.x = 0;
                continue;
            }
            
            
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
            case 'F':
                this->terrain[y][x] = ForestTile();
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

    

    void draw(Pos cursor_position){
        std::cout << "\x1B[2J\x1B[H";

        for(int y = 0; y <= this->size.y; ++y){
            for(int x = 0; x < this->size.x; ++x){
                if(x == cursor_position.x && y == cursor_position.y){
                    draw_cursor(x,y);
                    continue;
                }
                if(Unit* u = get_unit_at(x,y)){
                    u->print(
                        merge_colors(this->terrain[y][x],*u)
                    );
                    continue;
                }
                this->terrain[y][x].print();
            }
            printf("%c",'\n');
        }
    }

    inline void claim(int x, int y, Colors color){
        static_cast<ClaimableTerrainTile*>(&terrain[y][x])->claim(color);
    }

    inline void addUnit(Unit u){
        units.push_back(u);
    }
    Pos size;

    //
    //  TO-DO: change this function, generates a SIGSEGV
    //
    Tile* get_selection(Pos cursor_pos){
        if(Unit* u = get_unit_at(cursor_pos.x, cursor_pos.y)){
            return u;
        }
        return &this->terrain[cursor_pos.y][cursor_pos.x];
    }

private:
    
    TerrainTile terrain[64][64];
    std::vector<Unit> units;  

    void draw_cursor(int x, int y){
        Color selected = {"","\x1b[48;5;254m"};
        if(Unit* u = get_unit_at(x,y)){
            selected.foreground = u->color.foreground;
            u->print(selected);
        }
        else{
            Color saved_color = this->terrain[y][x].color;
            this->terrain[y][x].color = selected;
            this->terrain[y][x].print();
            this->terrain[y][x].color = saved_color;
        }
    }

    Unit* get_unit_at(int x, int y){
        for(int i = 0; i < units.size(); ++i){
            if(units[i].position.x == x && units[i].position.y == y){
                return &units[i];
            }
        }
        return nullptr;
    }
};
