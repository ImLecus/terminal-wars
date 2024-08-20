#pragma once
#include <iostream>

#define ANSI_RESET "\x1b[0m"
// Colors are represented as a pair ANSI characters
struct Color {
    const char* foreground;
    const char* background;
    char* print(){
        char* color = (char*)malloc(sizeof(char) * 64);
        sprintf(color, "%s%s", foreground, background);
        return color;
    }
}; 

const Color TEAM_COLORS[] = {
    Color{"\x1b[38;5;235m","\x1b[48;5;252m"},
    Color{"\x1b[38;5;198m","\x1b[48;5;196m"},
    Color{"\x1b[38;5;21m","\x1b[48;5;12m"},
    Color{"\x1b[38;5;22m","\x1b[48;5;40m"},
    Color{"\x1b[38;5;226m","\x1b[48;5;214m"}
};
enum class Colors {
    UNCLAIMED,
    RED,
    BLUE,
    GREEN,
    YELLOW
};
