#pragma once
#include "color.h"

struct Pos {
    int x;
    int y;
};

class Tile {
public:
    inline void print(){
        printf("%s%s" ANSI_RESET, this->color.print(), this->symbol);
    }
    Color color;
protected:
    const char* symbol = " ";
};

Color merge_colors(Tile bg, Tile fg){
    return {fg.color.foreground, bg.color.background};
}