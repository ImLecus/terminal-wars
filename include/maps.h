#pragma once
#include "terrain.h"
#include "units.h"
#include <string>
#include <vector>
#include "mapcreator.h"

static const char* CURSOR_BG = "\x1b[48;5;254m";
static const char* CAN_MOVE_BG = "\x1b[48;5;252m";

class Map {
public:
    Map(const char* filepath){
        units.reserve(64);

        MapCreator map_creator;
        map_creator.read(filepath);
        size = map_creator.size;
        
        int x = 0, y = 0;
        for(int i = 0; i < map_creator.buffer.size(); ++i){
            if(map_creator.buffer.at(i) == '\n'){
                x = 0;
                ++y;
                continue;
            }
            this->terrain[y][x] = map_creator.get_tile(i);
            ++x;
        }

    }

    

    void draw(Pos cursor_position){
        // clear screen
        std::cout << "\x1B[2J\x1B[H";

        can_move_positions.clear();
        if(selected_unit){
            calculate_move_zone(selected_unit->position, selected_unit->get_movement_range(), true, selected_unit->type);
        }

        for(int y = 0; y <= this->size.y; ++y){
            for(int x = 0; x < this->size.x; ++x){

                bool to_move_drawed = false;

                if(x == cursor_position.x && y == cursor_position.y){
                    draw_bg(x,y, CURSOR_BG);
                    continue;
                }

                for(int u = 0; u < can_move_positions.size(); ++u){
                    if(can_move_positions.at(u).x == x &&
                        can_move_positions.at(u).y == y){
                            draw_bg(x,y, CAN_MOVE_BG);
                            to_move_drawed = true;
                            break;
                    }
                }
                if(to_move_drawed){continue;}
                
                if(Unit* u = get_unit_at(x,y)){
                    u->print(
                        merge_colors(this->terrain[y][x],*u)
                    );
                    continue;
                }

                if(!to_move_drawed){
                    this->terrain[y][x].print();
                }
                
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


    Tile* get_selection(Pos cursor_pos){
        if(Unit* u = get_unit_at(cursor_pos.x, cursor_pos.y)){
            return u;
        }
        return &this->terrain[cursor_pos.y][cursor_pos.x];
    }

    bool can_move_to(Pos target){
        for(int u = 0; u < can_move_positions.size(); ++u){
            if(can_move_positions.at(u).x == target.x &&
                can_move_positions.at(u).y == target.y){

                  return true;  
            }
        }
        return false;
    }

    Unit* selected_unit;

private:
    
    TerrainTile terrain[64][64];
    std::vector<Unit> units;  
    std::vector<Pos> can_move_positions;

    void draw_bg(int x, int y,const char* bg){
        Color selected = {"",bg};
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

    //
    // TO-DO: check this function, generates SIGSEGV when the unit is at a border tile
    Unit* get_unit_at(int x, int y){
        auto size = units.size();
        for(int i = 0; i < size; ++i){
            if(units[i].position.x == x && units[i].position.y == y){
                return &units[i];
            }
        }
        return nullptr;
    }

    void calculate_move_zone(Pos pos, int range, bool first, UnitMovementType move_type){
        if(pos.x < 0 || pos.y < 0 || pos.x > size.x || pos.y > size.y){
            return;
        }
        TerrainTile t = terrain[pos.y][pos.x];
        Unit* u = get_unit_at(pos.x, pos.y);
        if( (!u || first) && (move_type == UnitMovementType::AIR || (int)move_type == (int)t.type)){
            can_move_positions.push_back(pos);
            
            range -= t.get_movement_resistance();
            if(range > 0){
                calculate_move_zone(Pos{pos.x, pos.y + 1}, range, false, move_type);
                calculate_move_zone(Pos{pos.x, pos.y - 1}, range, false, move_type);
                calculate_move_zone(Pos{pos.x + 1, pos.y}, range, false, move_type);
                calculate_move_zone(Pos{pos.x - 1, pos.y}, range, false, move_type);
            }
        }
        
    }

};
