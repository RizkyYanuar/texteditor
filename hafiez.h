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

// ================= FUNCTION =================

void setCursor(int x, int y);

int PCX(int CurX, int perubahan);
int PCY(int CurY, int perubahan);

void printBar(addressBar FirstBar);

void freeAll(addressBar FirstBar);

void GerakKursor(int key, addressBar *CurrentBar, addressKol *Cursor, int *CursorX, int *CursorY, addressBar FirstBar);
void BarisBaru(addressBar *CurrentBar,addressBar *FirstBar,addressKol *Cursor, int *CursorX, int *CursorY);
void InsertKarakter(char key, addressBar *FirstBar, addressBar *CurrentBar, addressKol *Cursor, int *CursorX, int CursorY);

#endif
