#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define Nil NULL

typedef char infotype;

typedef struct Kolom *addressKol;
typedef struct Baris *addressBar;

typedef struct Kolom {
    infotype info;
    addressKol prev;
    addressKol next;
} Kol;

typedef struct Baris {
	addressBar prev; 
    addressKol kol;
    addressBar next; 
} Bar;

void setCursor(int x, int y);
void printBar(Bar *bar,Bar *FB);
int getCursorIndex(Bar *bar, addressKol Cursor);

int main() {
    Bar *bar = Nil, *CurrentBar, *FirstBar;
    addressKol Cursor = Nil;
    addressKol Q;

    int key;
	printf(" TEXT EDITOR COBA COBA \n");
	
    while (1) {
        key = getch();
		
		if (key ==27 ){
			if (key == 27) {
   				Bar *B = FirstBar;

	    		while (B != Nil) {
	        		addressKol Q = B->kol;
	
	        		while (Q != Nil) {
	            		addressKol tempK = Q;
	            		Q = Q->next;
	            		free(tempK);
	        		}
	
					Bar *tempB = B;
	        		B = B->next;
	        		free(tempB);
    			}
			} 	
			printf("\n\nMemory Berhasil Di Bebaskan, Gacor Kang");	
			break;
		}
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
            printBar(bar,FirstBar);

            int pos = getCursorIndex(bar, Cursor);
            setCursor(pos, 1);
            continue;
        }
        
        if (key == 8){
    		if (Cursor == Nil){
    			continue;
			}
        	
   			addressKol temp = Cursor;


    		if (Cursor->prev != Nil){
        		Cursor->prev->next = Cursor->next;

        		if(Cursor->next != Nil){
           			Cursor->next->prev = Cursor->prev; 
        		}
        		Cursor = Cursor->prev;
    		}

    		else { 
        		if(Cursor->next != Nil){
            		bar->kol = Cursor->next; //ini kalo misalnya di awal tapi disebelahkanannya ada karakter == A|BC == maka jadi == |BC == dan kursor harus dibikin nil 
            		Cursor = Cursor->next;
            		Cursor->prev = Nil;
            		Cursor = Nil;
       			 }
        		else{
            		Cursor = Nil;
            		bar->kol = Nil; 
       				}	
    		}

    		free(temp);

		    system("cls");
		    printf(" TEXT EDITOR COBA COBA \n");
		    printBar(bar,FirstBar);
		
		    int pos = getCursorIndex(bar, Cursor);
		    setCursor(pos, 1);

    		continue;
		}
		
		
		if (key == 13){
			bar = (Bar*) malloc(sizeof(Bar));
			CurrentBar->next = bar;
			CurrentBar->next->prev = CurrentBar; // harus di kembangin lagi euy soalnya banyak yang pemisalan kaya misal kalo CurrentBar->kol = Nil nanti dia ngehapus Baris dll
			bar->next = Nil;
		}
		

        Q = (addressKol) malloc(sizeof(Kol));
        Q->info = key;
        Q->prev = Nil;
        Q->next = Nil;

        // belum ada baris sama sekali
        if (bar == Nil) {
            bar = (Bar*) malloc(sizeof(Bar));
            bar->kol = Q;
            Cursor = Q;
            CurrentBar = bar;
            FirstBar = bar;
        }
        else {
            // insert di awal
            if (Cursor == Nil) {
                Q->next = bar->kol;

                if (bar->kol != Nil)
                    bar->kol->prev = Q;

                bar->kol = Q;
                Cursor = Q;
            }
            
            //insert ditengah atau di ujung tergantung Cursor->next ada atau engga riweh pokonamah
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
        printBar(bar,FirstBar);

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

void printBar(Bar *bar, Bar *FB) {
    if (FB == Nil) {
        printf("\n");
        return;
    }

    while (FB != Nil) {
        addressKol Q = FB->kol;  

        while (Q != Nil) {
            printf("%c", Q->info);
            Q = Q->next;
        }

        printf("\n");

        FB = FB->next;  
    }
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
