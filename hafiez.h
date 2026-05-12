#ifndef HAFIEZ_H
#define HAFIEZ_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define Nil NULL

typedef char infotype;

typedef struct Kolom *addressKol;
typedef struct Baris *addressBar;

typedef struct Kolom {
    infotype info;
    addressKol prev;
    addressKol next;
} Kol;

typedef struct Baris {
	addressKol tail;
    addressBar prev;
    addressKol kol;
    addressBar next;
    int longBar;
} Bar;


void setCursor(int x, int y);

int PCX(int CurX, int perubahan);
int PCY(int CurY, int perubahan);

#endif
