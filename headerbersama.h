#ifndef headerbersama_H
#define headerbersama_H
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
	
#define MAX_ROWS 100
#define MAX_COLS 256
#define VIEW_ROWS 20   // jumlah baris yang terlihat di layar
#define HEADER_LINES 3

extern int totalLines;
extern char text[MAX_ROWS][MAX_COLS];
extern int cursorX;
extern int cursorY;
extern int viewTop;
extern int isModified;

extern int selStartX, selStartY;
extern int selEndX, selEndY;
extern int isSelecting;

extern char clipboard[5000];
int isShiftPressed();

#endif
