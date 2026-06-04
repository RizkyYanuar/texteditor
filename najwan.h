#ifndef NAJWAN_H
#define NAJWAN_H
#include "hafiez.h"
#include<direct.h>
#include"conio.h"
typedef struct tNode *address;

typedef struct tNode{
	char filename[100];
	address next;
}Node;

void SaveFile(char *filename,addressBar FirstBar);
void freeAll(addressBar FirstBar);
void NewFile();
FILE *BukaFile(char *filename);
void OpenFileToLinkedList(
    FILE *file,
    addressBar *FirstBar,
    addressBar *CurrentBar,
    addressKol *Cursor,
    int *CursorX,
    int *CursorY
);
void SaveFile(char *filename,addressBar FirstBar);
void freeAll(addressBar FirstBar);
void NewFile();
void TampilIsiFile(FILE *file);
#endif
