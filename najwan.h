#ifndef najwan_H
#define najwan_H
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <dirent.h>

int displayFiles(char files[][100]);
void deleteFileADT(const char *filename);

void deleteSelection();
void editFile(char *filename);
void exitFile();

void setClipboard(const char *text);
char* getClipboard();
void clearClipboard();
void copySelection();

#endif
