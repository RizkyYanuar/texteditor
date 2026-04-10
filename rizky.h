#ifndef rizky_H
#define rizky_H
#include <stdio.h>

void newFile (char* namaFile);
int openFile(char* namaFile);
int pilihFile(int j, int *pilihan);
void openFileToBuffer(char *filename);
void cutSelection();
void backspace();
#endif
