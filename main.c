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
	    addressClipboard Clipboard = Nil;
	    addressClipboard DuplikatClipboard = Nil;
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
	        	TukarSelect(&SelStart,&SelEnd); 
	        	CekClipboard(&Clipboard);
	        	Clipboard = CopyToClipboard(SelStart.kol, SelEnd.kol);
	        	SelStart.kol = Nil;
	        	SelEnd.kol = Nil;
	        	continue;
			}
			

			if (key == 16){
			
				if (Clipboard != Nil){
					 DuplikatClipboard = CopyToClipboard(Clipboard->kol, Clipboard->tail);

					if (Cursor != Nil){ // kalo cursor ga di ujung kiri
						if(Cursor->next != Nil){ // kalo kursor di tengah tengah / diantara 2 karakter
						Cursor->next->prev = DuplikatClipboard->tail; // buat nyambungin node sebelah kanan kursor sama ujung kanan dari node clipbord
						DuplikatClipboard->tail->next = Cursor->next; // buat nyambungin ujung kanan clipboard sama node sebelah kanan cursor
						}
					Cursor->next = DuplikatClipboard->kol; //buat nyambungin node sebelah kiri kursor sama node ujung kiri clipboard
					DuplikatClipboard->kol->prev = Cursor;	// buat nyambungin ujung kiri clipboard sama node sebelah kiri kursor
					CurrentBar->longBar = CurrentBar->longBar + DuplikatClipboard->longBar;
					}
					
					else{
						if(CurrentBar->kol != Nil){ // kalo cursor ada di ujung kiri dan di kanan cursor ada karakter
							CurrentBar->kol->prev = DuplikatClipboard->tail; //buat nyambungin node sebelah kanan kursor sama node ujung kkanan clipboard
							DuplikatClipboard->tail->next = CurrentBar->kol; //buat nyambungin node ujung kanan clipbord sama node sebelah kiri kursor 
							CurrentBar->kol = DuplikatClipboard->kol; //buat mastiin bahwa ujung kiri clipboard jadi kolom pertama
							CurrentBar->longBar = CurrentBar->longBar + DuplikatClipboard->longBar;
						}
						else{
							CurrentBar->kol = DuplikatClipboard->kol;
							CurrentBar->longBar = DuplikatClipboard->longBar;
							CurrentBar->tail = DuplikatClipboard->tail;
						}
						
					}
				}
				else{
					continue;
				}
				
					
				Cursor = DuplikatClipboard->tail;
				if(Cursor->next == Nil)
					CurrentBar->tail = Cursor;
				CursorX = PCX(CursorX,DuplikatClipboard->longBar);
				DuplikatClipboard->kol = Nil;
				free(DuplikatClipboard);
				DuplikatClipboard = Nil;
				
			    system("cls");
			
			    printf(" TEXT EDITOR COBA COBA \n");
				
			    printBar(FirstBar);
			
			    setCursor(CursorX, CursorY);
	        	SelStart.kol = Nil;
	        	SelEnd.kol = Nil;
    			continue;
				}

		
			else 
			 	InsertKarakter(key, &FirstBar, &CurrentBar, &Cursor, &CursorX, CursorY);
	    
		}	
	
	}	
}
    return 0;
}

