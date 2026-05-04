#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define Nil NULL

typedef char infotype;

typedef struct Kolom *addressKol;

typedef struct Kolom {
    infotype info;
    addressKol prev;
    addressKol next;
} Kol;

typedef struct Baris {
    addressKol kol;
} Bar;

void setCursor(int x, int y);
void printBar(Bar *bar);
int getCursorIndex(Bar *bar, addressKol Cursor);

int main() {
    Bar *bar = Nil;
    addressKol Cursor = Nil;
    addressKol Q;

    int key;

    while (1) {
        key = getch();

        if (key == 224 || key == 0) {
            key = getch();

            // kiri
            if (key == 75) {
                if (Cursor != Nil)
                    Cursor = Cursor->prev;
            }

            // kanan
            else if (key == 77) {
                if (Cursor == Nil) {
                    if (bar != Nil)
                        Cursor = bar->kol;
                }
                else if (Cursor->next != Nil) {
                    Cursor = Cursor->next;
                }
            }

            system("cls");
            printf(" TEXT EDITOR COBA COBA \n");
            printBar(bar);

            int pos = getCursorIndex(bar, Cursor);
            setCursor(pos, 1);

            continue;
        }

        Q = (addressKol) malloc(sizeof(Kol));
        Q->info = key;
        Q->prev = Nil;
        Q->next = Nil;

        // belum ada baris kocak
        if (bar == Nil) {
            bar = (Bar*) malloc(sizeof(Bar));
            bar->kol = Q;
            Cursor = Q;
        }
        else {
            // insert di paling kiri
            if (Cursor == Nil) {
                Q->next = bar->kol;

                if (bar->kol != Nil)
                    bar->kol->prev = Q;

                bar->kol = Q;
                Cursor = Q;
            }
            
            //insert ditengah atau di ujung tergantung Cursor->next ada atau engga 
            else {
                Q->next = Cursor->next;
                Q->prev = Cursor;

                if (Cursor->next != Nil)
                    Cursor->next->prev = Q;

                Cursor->next = Q;
                Cursor = Q;
            }
        }

        system("cls");
        printf(" TEXT EDITOR COBA COBA \n");
        printBar(bar);

        int pos = getCursorIndex(bar, Cursor);
        setCursor(pos, 1);
    }

    return 0;
}


void setCursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printBar(Bar *bar) {
    if (bar == Nil) {
        printf("\n");
        return;
    }

    addressKol Q = bar->kol;

    while (Q != Nil) {
        printf("%c", Q->info);
        Q = Q->next;
    }

    printf("\n");
}

int getCursorIndex(Bar *bar, addressKol Cursor) {
    int index = 0;

    if (bar == Nil)
        return 0;

    if (Cursor == Nil)
        return 0;

    addressKol Q = bar->kol;

    while (Q != Nil) {
        index++;
        if (Q == Cursor)
            return index;
        Q = Q->next;
    }

    return index;
}
