#ifndef RIZKY_H
#define RIZKY_H
#include "hafiez.h"

void printBar(addressBar FirstBar);

void backspace(addressBar FirstBar, addressBar *CurrentBar, addressKol *Cursor, int *CursorX, int *CursorY);

void CekClipboard  (addressClipboard *CopyClipboard);

addressClipboard CopyToClipboard(addressKol SelStart, addressKol SelEnd);

void Copy(addressClipboard *Hasil, addressKol tempStart, addressKol tempEnd);

#endif
