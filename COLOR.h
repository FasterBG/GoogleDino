#ifndef COLORS_H
#define COLORS_H

#include <windows.h>

const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 32;

const int pole_rows = SCREEN_HEIGHT;
const int pole_cols = SCREEN_WIDTH;

HANDLE hConsoleOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
COORD screen_buf = {pole_cols, pole_rows};
CHAR_INFO blank_screen[(pole_rows) * (pole_cols)] = {0};

enum COLORS {
    BLACK = 0,
    BLUE = FOREGROUND_BLUE,
    CYAN = FOREGROUND_BLUE | FOREGROUND_GREEN,
    GREEN = FOREGROUND_GREEN,
    RED = FOREGROUND_RED,
    BROWN = FOREGROUND_RED | FOREGROUND_GREEN,
    PURPLE = FOREGROUND_RED | FOREGROUND_BLUE,
    LIGHT_GREY =  FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN,

    GREY = 0 | FOREGROUND_INTENSITY,
    LIGHT_BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    LIGHT_CYAN = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    LIGHT_GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    LIGHT_RED = FOREGROUND_RED | FOREGROUND_INTENSITY,
    YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    PINK = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    WHITE =  FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY
};

const COLORS backgroundColor = LIGHT_GREEN;

void draw_char(char ch, int x, int y, COLORS foreground_color, COLORS background_color) {
    x = SCREEN_HEIGHT - 1 - x;
    int a = x;
    x = y;
    y = a;
    CHAR_INFO ch_info;
    ch_info.Char.AsciiChar = ch;
    ch_info.Attributes = foreground_color | (background_color << 4);

    COORD buf_size = {1, 1};
    COORD buf_coord = {0, 0};
    SMALL_RECT screen_pos = {x, y, x+1, y+1};
    ::WriteConsoleOutput(hConsoleOutput, &ch_info, buf_size, buf_coord, &screen_pos);

}

void clear_screen() {
    COORD buf_coord = {0, 0};
    SMALL_RECT screen_pos = {0, 0, screen_buf.X, screen_buf.Y};
    ::WriteConsoleOutput(hConsoleOutput, blank_screen, screen_buf, buf_coord, &screen_pos);
}

void set_background() {
    for (int i = 0; i < screen_buf.X; i++) {
        for (int j = 0; j < screen_buf.Y; j++) {
             draw_char(' ', j, i, BROWN, backgroundColor);
        }
    }
}

void init_console(){

    SMALL_RECT rect = {0, 0, screen_buf.X, screen_buf.Y};

    ::SetConsoleScreenBufferSize(hConsoleOutput, screen_buf);
    ::SetConsoleWindowInfo(hConsoleOutput, TRUE, &rect);
    ::SetConsoleTitle("Google Dino");
    set_background();

}

void draw_str(char* str, int r, int c){
    for(int i = 0; str[i]!='\0'; i++){
        draw_char(str[i], r, c + i, BLACK, backgroundColor);
    }
}
#endif //COLOR_H
