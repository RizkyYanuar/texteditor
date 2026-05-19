#include "hafiez.h"
#include "najwan.h"
#include "rizky.h"
	
	
int main() {
		
	addressBar FirstBar = Nil;
	    addressBar CurrentBar = Nil;
	    addressKol Cursor = Nil;
	    addressKol Q;
	    int CursorX = 3,CursorY = 1;
	    int i;
	
	    int key;
	
	    printf(" TEXT EDITOR COBA COBA \n");
	
	    while (1) {
	    	
	    	
	        key = getch();
	
	
	        if (key == 27) {
	            freeAll(FirstBar);
	            printf("\n\n\n================ Memory dibebaskan ======================\n\n\n");
	            break;
	        }
	
	
	        if (key == 224) {
	            key = getch();
	            GerakKursor(key, &CurrentBar, &Cursor, &CursorX, &CursorY, FirstBar);
	            continue;
        	}

	
	
	        if (key == 8) { // Backspace
				backspace(FirstBar, &CurrentBar, &Cursor, &CursorX, &CursorY);
				continue;
	        }
	
	
	        if (key == 13) { // Enter baris baru
				BarisBaru(&CurrentBar, &FirstBar, &Cursor, &CursorX, &CursorY);
	            continue;
	        }
	
	        //Insert karakter
	        Q = (addressKol) malloc(sizeof(Kol));
	        Q->info = key;
	        Q->prev = Nil;
	        Q->next = Nil;
	
	        if (CurrentBar == Nil) {
	            addressBar newBar = (addressBar) malloc(sizeof(Bar));
	            newBar->kol = Q;
	            newBar->prev = Nil;
	            newBar->next = Nil;
	            newBar->longBar = 0;
	
	            FirstBar = newBar;
	            CurrentBar = newBar;
	            CurrentBar->tail = Q;
	            Cursor = Q;
	            
	        }
	        else {
	            if (Cursor == Nil) {
	                Q->next = CurrentBar->kol;
	
	                if (CurrentBar->kol != Nil) {
                    	CurrentBar->kol->prev = Q;
	                } else {
	                    CurrentBar->tail = Q; 
	                }
	
	                CurrentBar->kol = Q;
	                Cursor = Q;
	            }
	            
	            else {
	                Q->next = Cursor->next;
	                Q->prev = Cursor;
	
	                if (Cursor->next != Nil){
	                	Cursor->next->prev = Q;
					}
	
					else{
						CurrentBar->tail = Q;
					}
					
	                Cursor->next = Q;
	                Cursor = Q;
	            }
	        }
	
	        CurrentBar->longBar++;
			CursorX = PCX(CursorX, 1);
			
	        system("cls");
	        printf(" TEXT EDITOR COBA COBA \n");
	        printBar(FirstBar);
	        setCursor(CursorX, CursorY);
	    }

    return 0;
	}

