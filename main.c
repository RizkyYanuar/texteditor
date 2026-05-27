#include "hafiez.h"
#include "najwan.h"
#include "rizky.h"
	
	
int main() {
	int menu;

    while(1){

        system("cls");

        printf("1. New File\n");
        printf("2. Open File\n");
        printf("3. Delete File\n");
        printf("4. Exit\n");
        printf("Pilih : ");
        scanf("%d",&menu);
        
        if(menu == 4){
        	break;
		}
		
	if(menu == 1){
		
		system("cls");
		
		addressBar FirstBar = Nil;
	    addressBar CurrentBar = Nil;
	    addressKol Cursor = Nil;
	    addressKol Q;
	    int CursorX = 5,CursorY = 1;
	    int i;
	    SelectPoint SelStart, SelEnd;

		SelStart.x = 0;
		SelEnd.x = 0;
		
		SelStart.kol = Nil;
		SelEnd.kol = Nil;
		int Selecting;
		
	    int key;
		char filename[100];
	    printf(" TEXT EDITOR COBA COBA \n");
	
	    while (1) {
	    	
	        key = getch();
			if(key == 19){
				printf("\nMasukan nama file:");
				scanf("%s",filename);
				
			 	SaveFile(filename,FirstBar);
				continue;
			}
	
	
	        if (key == 27) {
	            freeAll(FirstBar);
	            printf("\n\n\n================ Memory dibebaskan ======================\n\n\n");
	            break;
	        }
	
	
	        if (key == 224) {
			key = getch();
			    if (GetAsyncKeyState(VK_SHIFT) & 0x8000){
			
			        SelectingAtauTidak(key,&CurrentBar,&Cursor,&CursorX,&CursorY,FirstBar,&SelStart,&SelEnd,&Selecting);
			        	TukarSelect(&SelStart,&SelEnd); 
			    }
			
			    else {
			        Selecting = 0;
			        GerakKursor(key, &CurrentBar, &Cursor, &CursorX, &CursorY, FirstBar);
			    }
			
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
	        
	        if (key == 3) {
	        	addressBar Clipboard = Clipboard(SelStart, SelEnd);
			}
			
			
	
			InsertKarakter(key, &FirstBar, &CurrentBar, &Cursor, &CursorX, CursorY);
	    
		}	
	
	}	
}
    return 0;
}

