#ifndef hafiez_H
#define hafiez_H
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

void saveFile(char *filename); // //
void moveCursor(int x, int y); //
void normalizeSelection();
int isSelected(int x, int y);
void setColor(int color);
void pasteClipboard(); //


#endif
