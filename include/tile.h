#pragma once
#include <iostream>

struct Pos {
    int x;
    int y;
};

#define ANSI_RESET "\x1b[0m"
// Colors are represented as ANSI characters
const char* TEAM_COLORS[] = {"\x1b[90;47m","\x1b[91;101m"};
enum class Colors {
    UNCLAIMED,
    RED
};

char* get_background_color(const char* color){
    char* bg = (char*)malloc(4);
    for(int i = 2; color[i] && color[i+1] && color[i+2]; ++i){
        if(color[i + 2] == 'm'){
            break;
        }
        bg[0] = color[i];
        bg[1] = color[i + 1];
        bg[2] = color[i + 2];
    }
    bg[3] = 0;
    return bg;
}

char* get_foreground_color(const char* color){
    char* fg = (char*)malloc(3);
    for(int i = 2; color[i] && color[i+1]; ++i){
        if(color[i + 1] == 'm' || color[i + 1] == ';'){
            break;
        }
        fg[0] = color[i];
        fg[1] = color[i + 1];
    }
    fg[2] = 0;
    return fg;
}


class Tile {
public:
    inline void print(){
        printf("%s%s" ANSI_RESET, this->color, this->symbol);
    }
    const char* color = "";
protected:
    const char* symbol = " ";
};


char* merge_colors(Tile bg, Tile fg){
    char* bg_color = get_background_color(bg.color);
    char* fg_color = get_foreground_color(fg.color);

    //printf("%s, %s",fg_color, bg_color);
    char* merged = (char*)malloc(10);
    sprintf(merged, "\x1b[%s;%sm", fg_color, bg_color);
    return merged;
}