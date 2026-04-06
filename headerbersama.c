#include "headerbersama.h"
int totalLines = 0;
char text[MAX_ROWS][MAX_COLS];
int cursorX = 0;
int cursorY = 0;
int viewTop = 0; 
int isModified = 0;
int isShiftPressed(){
	return (GetKeyState(VK_SHIFT) & 0x8000);
}
int selStartX = 0, selStartY = 0;
int selEndX = 0, selEndY = 0;
int isSelecting = 0;
char clipboard[5000]; 

