#ifndef RIZKY_H
#define RIZKY_H
#include "hafiez.h"

// ================= PRINT =================
void printBar(addressBar FirstBar);

void backspace(addressBar FirstBar, addressBar *CurrentBar, addressKol *Cursor, int *CursorX, int *CursorY);

addressBar Clipboard(SelectPoint SelStart, SelectPoint SelEnd);

void Paste(addressBar *CurrentBar, addressBar Clipboard, addressKol *Cursor, int *CursorX);

#endif
