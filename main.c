#include "hafiez.h"
#include "najwan.h"
#include "rizky.h"
	
	
int main() {
		
	addressBar FirstBar = Nil;
	addressBar CurrentBar = Nil;
	addressBar tempBar;
	addressKol Cursor ;
	int key, CursorX = 3, CursorY = 1;

	
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
	            if (Cursor == Nil && CurrentBar->prev == Nil) continue;
	            
	            if (Cursor == Nil && CurrentBar->prev != Nil) {
            	tempBar = CurrentBar;
            	CurrentBar->prev->tail->next = CurrentBar->kol;
            	CurrentBar->kol->prev = CurrentBar->prev->tail;
            	CurrentBar->kol = Nil;
            	CurrentBar->prev->next = CurrentBar->next;
            	if (CurrentBar->next != Nil){
            		CurrentBar->next->prev = CurrentBar->prev;
				}
				CurrentBar->prev->tail = CurrentBar->tail;
				CurrentBar->prev->longBar = CurrentBar->prev->longBar + CurrentBar->longBar;
				CurrentBar = CurrentBar->prev;
				free(tempBar);
				Cursor = CurrentBar->tail;
				CursorY = PCY(CursorY, -1);
				CursorX = PCX(CursorX, CurrentBar->longBar);
				} else if (Cursor != Nil) { 
	            	addressKol temp = Cursor;
	
		            if (Cursor->prev != Nil) {                  //Kalo misal di tengah atau di akhir karakter
		                Cursor->prev->next = Cursor->next;
		
		                if (Cursor->next != Nil) {
		                	Cursor->next->prev = Cursor->prev; 		
						}
						
						else {
							CurrentBar->tail = Cursor->prev;	
						}
							
		                Cursor = Cursor->prev;
		            }
		            else {
		                if (Cursor->next != Nil) {				//Kalo hapus di awal kolom dan di sebelah kanannya ada karakter nanti bakal di sambungin ke pointer baris
		                    CurrentBar->kol = Cursor->next;
		                    Cursor = Cursor->next;
		                    Cursor->prev = Nil;
		                    Cursor = Nil;
		                }
		                else {									//Kalo hapus di awal kolom dan di sebelah kananya tidak ada apa apa maka pointer baris tersebut akan kosong atau tidak ada apa apa di abris tersebut
		                    Cursor = Nil;
		                    CurrentBar->kol = Nil;
		                }
		            }
		            CurrentBar->longBar--;						//panjang baris akan dikurangi 
		            if (CursorX > 3)
		    			CursorX = PCX(CursorX, -1);
		            free(temp);
				}
	
	            
	
	            system("cls");
	            printf(" TEXT EDITOR COBA COBA \n");
	            printBar(FirstBar);
	            setCursor(CursorX, CursorY);
	            continue;
	        }
	
	
	        if (key == 13) { // Enter baris baru
				BarisBaru(&CurrentBar, &FirstBar, &Cursor, &CursorX, &CursorY);
	            continue;
	        }
	
	        else{
	        	InsertKarakter(key, &FirstBar, &CurrentBar, &Cursor, &CursorX, CursorY);
			}
	    }

    return 0;
	}
