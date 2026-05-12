#include "hafiez.h"

void setCursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int PCX(int CurX, int perubahan){
    return CurX + perubahan;
}

int PCY(int CurY, int perubahan){
    return CurY + perubahan;
}
