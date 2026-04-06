#ifndef hafiez_H
#define hafiez_H
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

void saveFile(char *filename); //
void editFile(char *filename); //
void moveCursor(int x, int y); //
void normalizeSelection();
int isSelected(int x, int y);
void setColor(int color);
void deleteSelection();
void copySelection();
void cutSelection();
void pasteClipboard(); //
void drawEditor(char *filename);
void openFileToBuffer(char *filename);

#endif
