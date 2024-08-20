#pragma once
#include <iostream>

#define ANSI_RESET "\x1b[0m"
// Colors are represented as ANSI characters
const char* TEAM_COLORS[] = {"\x1b[31m"};
enum class Colors {
    RED
};

class Tile {
public:
    void print(){
         std::cout << this->color << this->symbol << ANSI_RESET;
    }
protected:
    const char* symbol;
    const char* color;
};