#pragma once
#include <iostream>

struct Pos {
    int x;
    int y;
};

#define ANSI_RESET "\x1b[0m"
// Colors are represented as ANSI characters
const char* TEAM_COLORS[] = {"\x1b[31m"};
enum class Colors {
    RED
};

class Tile {
public:
    void print(){
        if(!this || !this->color || !this->symbol){
            printf("NO OBJECT");
            return;
        }
        printf("%s%s" ANSI_RESET, this->color, this->symbol);
        

    }
protected:
    const char* symbol = " ";
    const char* color = "";
};