#ifndef najwan_H
#define najwan_H
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <dirent.h>

void displayFiles();
void deleteFileADT(const char *filename);

void deleteSelection();
void editFile(char *filename);
void exitFile();
<<<<<<< HEAD
=======
void setClipboard(const char *text);
char* getClipboard();
void clearClipboard();

>>>>>>> e8561d6c9b76b95516890a608dd7128072087b53
#endif
