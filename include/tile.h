#pragma once
#include "color.h"
#include <iostream>
struct Pos {
    int x;
    int y;
};

class Tile {
public:
    inline void print(){
        printf("%s%s%s" ANSI_RESET, this->color.foreground, this->color.background, this->symbol);
    }
    Color color;
    bool is_unit;

    virtual ~Tile() = default;
protected:
    const char* symbol = " ";
};

Color merge_colors(Tile bg, Tile fg){
    return {fg.color.foreground, bg.color.background};
}