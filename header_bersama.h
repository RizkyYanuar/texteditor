#ifndef header_bersama_H
#define header_bersama_H
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
	
#define MAX_ROWS 100
#define MAX_COLS 100
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

extern char clipboard[100];

int isShiftPressed();

void editFile(char *filename);
void drawEditor(char *filename);
#endif
