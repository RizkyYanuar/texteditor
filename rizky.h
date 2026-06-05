#ifndef RIZKY_H
#define RIZKY_H
#include "hafiez.h"

void printBar(addressBar FirstBar);

void backspace(addressBar FirstBar, addressBar *CurrentBar, addressKol *Cursor, int *CursorX, int *CursorY, SelectPoint SelStart, SelectPoint SelEnd, int *Selecting);

void CekClipboard  (addressClipboard *CopyClipboard);

addressClipboard CopyToClipboard(addressKol SelStart, addressKol SelEnd);

void Copy(addressClipboard *Hasil, addressKol tempStart, addressKol tempEnd);

void backspaceSelecting(addressBar *CurrentBar, addressKol *Cursor, int *CursorX, SelectPoint SelStart, SelectPoint SelEnd);

void backspaceNormal(addressBar *CurrentBar, addressKol *Cursor, int *CursorX, int *CursorY);
#endif
