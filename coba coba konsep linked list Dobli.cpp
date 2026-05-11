//===========================================================================================Head=======================================================================================
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
    int longBar;
} Bar;
//===========================================================================================NECK=======================================================================================
// ================= CURSOR =================
void setCursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// ================= PRINT =================
void printBar(addressBar FirstBar) {
	int i = 1;
    while (FirstBar != Nil) {
        addressKol Q = FirstBar->kol;
		printf("%d| ",i);
        while (Q != Nil) {
            printf("%c", Q->info);
            Q = Q->next;
        }

//        printf("   | longBar = %d", FirstBar->longBar);
        printf("\n");
        FirstBar = FirstBar->next;
        i++;
    }
}


void freeAll(addressBar FirstBar) {
    while (FirstBar != Nil) {
        addressKol Q = FirstBar->kol;

        while (Q != Nil) {
            addressKol tempK = Q;
            Q = Q->next;
            free(tempK);
        }

        addressBar tempB = FirstBar;
        FirstBar = FirstBar->next;
        free(tempB);
    }
}

int PCX(int CurX, int perubahan){
    return CurX + perubahan;
}

int PCY(int CurY, int perubahan){
    return CurY + perubahan;
}


//===========================================================================================Body=======================================================================================


int main() {
    addressBar FirstBar = Nil;
    addressBar CurrentBar = Nil;
    addressKol Cursor = Nil;
    addressKol Q;
    int CursorX = 3,CursorY = 1;

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
						for (int i = 1; i < CursorX - 3; i++){         //maka kursor akan digeser sehauh posisi kursor terakhir
							Cursor = Cursor->next;
						}
					}
				}
				
				
				else {                                                     //Ketika saat ini lebih panjang dari baris diatasnya maka posisi kursor akan berada di ujung baris diatasnya dan poisisi kursor akan pindah ke abris dia tasnya
					CurrentBar = CurrentBar->prev; 
					Cursor = CurrentBar->kol;
					for (int i = 1; i < CurrentBar->longBar ; i++){
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
						for (int i = 1; i < CursorX - 3 ; i++){             
							Cursor = Cursor->next;     //Cursor digeser sebanyak posisi kursor terakhir
						}
					}
				}
				else {                                                     //ketika baris di bawahnya lebih pendek dari baris saat ini maka posisi kursor akan berada di ujung baris di bawahnya dan pindah ke abris dibawhnya
					CurrentBar = CurrentBar->next; 
					Cursor = CurrentBar->kol;
					for (int i = 1 ;i < CurrentBar->longBar ; i++){
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
            if (Cursor == Nil) continue;

            addressKol temp = Cursor;

            if (Cursor->prev != Nil) {                  //Kalo misal di tengah atau di akhir
                Cursor->prev->next = Cursor->next;

                if (Cursor->next != Nil)
                    Cursor->next->prev = Cursor->prev; 	

                Cursor = Cursor->prev;
            }
            else {
                if (Cursor->next != Nil) {
                    CurrentBar->kol = Cursor->next;
                    Cursor = Cursor->next;
                    Cursor->prev = Nil;
                    Cursor = Nil;
                }
                else {
                    Cursor = Nil;
                    CurrentBar->kol = Nil;
                }
            }

            CurrentBar->longBar--;
            if (CursorX > 0)
    			CursorX = PCX(CursorX, -1);
            free(temp);

            system("cls");
            printf(" TEXT EDITOR COBA COBA \n");
            printBar(FirstBar);
            setCursor(CursorX, CursorY);
            continue;
        }


        if (key == 13) { // Enter baris baru

            addressBar newBar = (addressBar) malloc(sizeof(Bar));
            newBar->kol = Nil;
            newBar->next = Nil;
            newBar->prev = Nil;
            newBar->longBar = 0;
            CursorX = 3;
            

            if (CurrentBar == Nil) {
                FirstBar = newBar;
                CurrentBar = newBar;
            }
            
            else if (CurrentBar->prev == Nil && Cursor == Nil) {

                newBar->next = CurrentBar;
                newBar->prev = Nil;

                CurrentBar->prev = newBar;

                FirstBar = newBar;
                CurrentBar = newBar;
                CursorY = PCY(CursorY,0);
            }
            
            else if(CurrentBar->prev != Nil && Cursor == Nil){
            	CurrentBar->prev->next = newBar;
            	newBar->prev = CurrentBar->prev;
            	newBar->next = CurrentBar;
            	CurrentBar->prev = newBar;
            	CurrentBar = newBar;
            	CursorY = PCY(CursorY,0);
            	
			}
			
            else {
                newBar->next = CurrentBar->next;
                newBar->prev = CurrentBar;

                if (CurrentBar->next != Nil)
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

                if (Cursor->next != Nil)
                    Cursor->next->prev = Q;

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
