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
	    addressBar tempBar;
	
	    int key;
	
	    printf(" TEXT EDITOR COBA COBA \n");
	
	    while (1) {
	    	
	    	
	        key = getch();
	
	
	        if (key == 27) {
	            freeAll(FirstBar);
	            printf("\n\n\n================ Memory dibebaskan ======================\n\n\n");
	            break;
	        }
	
	
	        if (key == 224 || key == 0) {
	            key = getch();
	
	            if (key == 75) {
				    if (Cursor != Nil){
				        Cursor = Cursor->prev; //Ketika disebah kiri ada karakter alias ada node dia Cursor akan geser terus ke awal node(BackEnd)
				    }
				    if (CursorX > 3)
	    				CursorX = PCX(CursorX, -1); //Selama dia ga berada di awal baris maka cursor akan bergerak ke kiri(FrontEnd) kalau sudah di ujung ya dia ga ngapa ngapain
				}
	
	            else if (key == 77) {
				    if (Cursor == Nil && CurrentBar != Nil){   //Ketika Kursor berada di awal baris alias tidak menunjuk node maka akan menunjuk node pertama di baris tersebut
				        Cursor = CurrentBar->kol;                  
				    }
				    else if (Cursor != Nil && Cursor->next != Nil){     //Selama Kursor sedang menunjuk node maka Cursor akan menunjuk node setelahnya (backEnd) 
				        Cursor = Cursor->next;						
				    }
				    if (CursorX - 3 < CurrentBar->longBar) //Selama posisi Kursor tidak melebihi panjang suatu abris maka dia bisa bergeser ke kanan
	    				CursorX = PCX(CursorX, + 1);			   
				}
				
				
				else if (key == 72){
					if(CurrentBar->prev == Nil) //jika diatasnya tidak ada baris maka tidak melakukan apa apa
					continue;
					
					if (CurrentBar->longBar <= CurrentBar->prev->longBar || CursorX - 3 <= CurrentBar->prev->longBar){   //ketika baris saat ini lebih pendek daro baris di atasnya maka posisi kursor di kolom tidak pindah hanya posisi abrisnya saja
						CurrentBar = CurrentBar->prev; 
						
						if(Cursor == Nil){ // kalau posisi kursor ada dia wal baris alias nul maka ketika pindah baris juga cursor akan Nil
							Cursor = Nil;
						} 
						else{
							Cursor = CurrentBar->kol;
							for (i = 1; i < CursorX - 3; i++){         //maka kursor akan digeser sehauh posisi kursor terakhir
								Cursor = Cursor->next;
							}
						}
					}
					
					
					else {                                                     //Ketika saat ini lebih panjang dari baris diatasnya maka posisi kursor akan berada di ujung baris diatasnya dan poisisi kursor akan pindah ke abris dia tasnya
						CurrentBar = CurrentBar->prev; 
						Cursor = CurrentBar->kol;
						for (i = 1; i < CurrentBar->longBar ; i++){
							Cursor = Cursor->next;	 							//maka kursor akan digeser sehauh panjang baris
						}
						CursorX = CurrentBar->longBar + 3;
					}
					CursorY = PCY(CursorY,-1);
				}
				
				else if (key == 80){
					if (CurrentBar->next == Nil)
						continue;
						
					if (CurrentBar->longBar <= CurrentBar->next->longBar || CursorX - 3 <= CurrentBar->next->longBar){   //ketika baris saat ini lebih pendek dari baris dibawhnay maka posisi kursor dikolom tidak akan berubahn posisi barisnya saja yang berubah
						CurrentBar = CurrentBar->next; 
						if(Cursor == Nil){               // kalau cursor sekarang ada di awal baris atau = Nil maka ketika pindah ke bawah dia juga bernilai Nil Cursornya
							Cursor = Nil;
						}
						
						else{
							Cursor = CurrentBar->kol;
							for (i = 1; i < CursorX - 3 ; i++){             
								Cursor = Cursor->next;     //Cursor digeser sebanyak posisi kursor terakhir
							}
						}
					}
					else {                                                     //ketika baris di bawahnya lebih pendek dari baris saat ini maka posisi kursor akan berada di ujung baris di bawahnya dan pindah ke abris dibawhnya
						CurrentBar = CurrentBar->next; 
						Cursor = CurrentBar->kol;
						for (i = 1 ;i < CurrentBar->longBar ; i++){
							Cursor = Cursor->next;
						}
						CursorX = CurrentBar->longBar + 3;
					}
					CursorY = PCY(CursorY,+1);
				}
			
	            system("cls");
	            printf(" TEXT EDITOR COBA COBA \n");
	            printBar(FirstBar);
	            setCursor(CursorX, CursorY);
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
	
	            addressBar newBar = (addressBar) malloc(sizeof(Bar));
				newBar->kol = Nil;
				newBar->tail = Nil;
				newBar->next = Nil;
				newBar->prev = Nil;
				newBar->longBar = 0;
	            CursorX = 3;
	            
	
	            if (CurrentBar == Nil) {			//kalo belum ada baris sama sekali
	                FirstBar = newBar;
	                CurrentBar = newBar;
	            }
	            
	            else if (CurrentBar->prev == Nil && Cursor == Nil) { //kalo enter di baris pertama untuk membuat baris baru diatasnya maka baris baru tersebut akan menjadi baris pertama
	
	                newBar->next = CurrentBar;
	                newBar->prev = Nil;
	
	                CurrentBar->prev = newBar;
	
	                FirstBar = newBar;
	                CurrentBar = newBar;
	                CursorY = PCY(CursorY,0);
	            }
	            
	            else if(CurrentBar->prev != Nil && Cursor == Nil){    //kalo enter untuk membuat baris baru diatasnya dan ada baris sebelum di enter maka nanti akan disambungkan
	            	CurrentBar->prev->next = newBar;
	            	newBar->prev = CurrentBar->prev;
	            	newBar->next = CurrentBar;
	            	CurrentBar->prev = newBar;
	            	CurrentBar = newBar;
	            	CursorY = PCY(CursorY,0);
	            	
				}
				
	            else {												//kalo enter baris baru dibawah atau baris terakhir
	                newBar->next = CurrentBar->next;
	                newBar->prev = CurrentBar;
	
	                if (CurrentBar->next != Nil)                   //kalo ini ketika enter dan dibawhanya ada baris jadi kaya di tengah tengah ada baris baru nah nanti yang dibawah disambungin sama yang abris baru dan baris sekarang juga akal disambungin sama baris baru
	                    CurrentBar->next->prev = newBar;
	
	                CurrentBar->next = newBar;
	                CurrentBar = newBar;
	                CursorY = PCY(CursorY,1);
	            }
		
	            Cursor = Nil;
	
	            system("cls");
	            printf(" TEXT EDITOR COBA COBA \n");
	            printBar(FirstBar);
	            
	            setCursor(CursorX, CursorY);
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
	
	                if (CurrentBar->kol != Nil)
	                    CurrentBar->kol->prev = Q;
	
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
