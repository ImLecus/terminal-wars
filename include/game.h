#pragma once
#include "maps.h"
#include <iostream>
class Game {
public:
    Game(Map* map){
        this->map = map;
    }

    void select_unit_or_building(){
        void* selection = map->get_selection(cursor_position);
        if(Unit* u = (Unit*)selection){
           (*u).state = SELECTED;
           dialog = "Unit selected";
           on_state_update();
           free(u);
           return;
        }
        if(TerrainTile* t = (TerrainTile*)selection){
            dialog = "Building selected";
            on_state_update();
            free(t);
        }
        free(selection);
        
    }

    void wait_for_input(){
        char c,d,e;
        std::cin >> c;
        if(c == 'z'){
            select_unit_or_building();
            return;
        }
        std::cin >> d;
        std::cin >> e;
        if ((c==27)&&(d==91)) {
            if (e==65) {if(cursor_position.y > 0)--this->cursor_position.y;}
            if (e==66) {if(cursor_position.y < map->size.y) ++this->cursor_position.y;}
            if (e==67) {if(cursor_position.x < map->size.x - 1) ++this->cursor_position.x;}
            if (e==68) {if(cursor_position.x > 0) --this->cursor_position.x;}
        }
        on_state_update();
    }
  
    // on_state_update is called when the game state changes
    void on_state_update(){
        this->map->draw(this->cursor_position);
        printf("\n%s\n", dialog.c_str());
    }

private:
    Map* map;
    int turn = 0;
    Pos cursor_position = {0,0};
    std::string dialog = "Select a unit or building with \x1b[1mZ\x1b[0m";
};