#include "hafiez.h"

void setCursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}

int PCX(int CurX, int perubahan){
    return CurX + perubahan;
}

int PCY(int CurY, int perubahan){
    return CurY + perubahan;
}



void GerakKursor(int key, addressBar *CurrentBar, addressKol *Cursor, int *CursorX, int *CursorY, addressBar FirstBar){
    int i;

    // ================= KURSOR KIRI =================
    if (key == 75) {

        if (*Cursor != Nil){
            *Cursor = (*Cursor)->prev; //Ketika disebah kiri ada karakter alias ada node dia Cursor akan geser terus ke awal node(BackEnd)
        }

        if (*CursorX > 3)
            *CursorX = PCX(*CursorX, -1); //Selama dia ga berada di awal baris maka cursor akan bergerak ke kiri(FrontEnd) kalau sudah di ujung ya dia ga ngapa ngapain
    }


    // ================= KURSOR KANAN =================
    else if (key == 77) {

        if (*Cursor == Nil && *CurrentBar != Nil){   //Ketika Kursor berada di awal baris alias tidak menunjuk node maka akan menunjuk node pertama di baris tersebut
            *Cursor = (*CurrentBar)->kol;
        }

        else if (*Cursor != Nil && (*Cursor)->next != Nil){     //Selama Kursor sedang menunjuk node maka Cursor akan menunjuk node setelahnya (backEnd)
            *Cursor = (*Cursor)->next;
        }

        if (*CursorX - 3 < (*CurrentBar)->longBar) //Selama posisi Kursor tidak melebihi panjang suatu abris maka dia bisa bergeser ke kanan
            *CursorX = PCX(*CursorX, +1);
    }



    // ================= KURSOR ATAS =================
    else if (key == 72){

        if ((*CurrentBar)->prev == Nil) //jika diatasnya tidak ada baris maka tidak melakukan apa apa
            return;

        //ketika baris saat ini lebih pendek daro baris di atasnya maka posisi kursor di kolom tidak pindah hanya posisi abrisnya saja
        if (
            (*CurrentBar)->longBar <= (*CurrentBar)->prev->longBar ||
            *CursorX - 3 <= (*CurrentBar)->prev->longBar
        ){

            *CurrentBar = (*CurrentBar)->prev;

            if(*Cursor == Nil){ // kalau posisi kursor ada dia wal baris alias nul maka ketika pindah baris juga cursor akan Nil
                *Cursor = Nil;
            }

            else{

                *Cursor = (*CurrentBar)->kol;

                //maka kursor akan digeser sehauh posisi kursor terakhir
                for (i = 1; i < *CursorX - 3; i++){
                    *Cursor = (*Cursor)->next;
                }
            }
        }


        //Ketika saat ini lebih panjang dari baris diatasnya maka posisi kursor akan berada di ujung baris diatasnya dan poisisi kursor akan pindah ke abris dia tasnya
        else {
            *CurrentBar = (*CurrentBar)->prev;
            *Cursor = (*CurrentBar)->tail;
            *CursorX = (*CurrentBar)->longBar + 3;
        }
        *CursorY = PCY(*CursorY,-1);
    }



    // ================= KURSOR BAWAH =================
    else if (key == 80){
        if ((*CurrentBar)->next == Nil) //jika dibawahnya tidak ada baris maka tidak melakukan apa apa
            return;
            
        //ketika baris saat ini lebih pendek dari baris dibawhnay maka posisi kursor dikolom tidak akan berubah posisi barisnya saja yang berubah
        if ((*CurrentBar)->longBar <= (*CurrentBar)->next->longBar || *CursorX - 3 <= (*CurrentBar)->next->longBar){
            *CurrentBar = (*CurrentBar)->next;
            
            if(*Cursor == Nil){ // kalau cursor sekarang ada di awal baris atau = Nil maka ketika pindah ke bawah dia juga bernilai Nil Cursornya
                *Cursor = Nil;
            }

            else{
                *Cursor = (*CurrentBar)->kol;
                
                //Cursor digeser sebanyak posisi kursor terakhir
                for (i = 1; i < *CursorX - 3 ; i++){
                    *Cursor = (*Cursor)->next;
                }
            }
        }

        //ketika baris di bawahnya lebih pendek dari baris saat ini maka posisi kursor akan berada di ujung baris di bawahnya dan pindah ke abris dibawhnya
        else {

            *CurrentBar = (*CurrentBar)->next;
            *Cursor = (*CurrentBar)->tail;
            *CursorX = (*CurrentBar)->longBar + 3;
        }
        *CursorY = PCY(*CursorY,+1);
    }

    system("cls");
    printf(" TEXT EDITOR COBA COBA \n");
    printBar(FirstBar);
    setCursor(*CursorX, *CursorY);
}

void BarisBaru(addressBar *CurrentBar, addressBar *FirstBar, addressKol *Cursor, int *CursorX, int *CursorY){

    addressBar newBar = (addressBar) malloc(sizeof(Bar));

    newBar->kol = Nil;
    newBar->tail = Nil;
    newBar->next = Nil;
    newBar->prev = Nil;
    newBar->longBar = 0;

    *CursorX = 3;


    //kalo belum ada baris sama sekali
    if (*CurrentBar == Nil) {

        *FirstBar = newBar;
        *CurrentBar = newBar;
    }


    //kalo enter di baris pertama untuk membuat baris baru diatasnya maka baris baru tersebut akan menjadi baris pertama
    else if ((*CurrentBar)->prev == Nil && *Cursor == Nil) {

        newBar->next = *CurrentBar;
        newBar->prev = Nil;

        (*CurrentBar)->prev = newBar;

        *FirstBar = newBar;
        *CurrentBar = newBar;

        *CursorY = PCY(*CursorY,0);
    }


    //kalo enter untuk membuat baris baru diatasnya dan ada baris sebelum di enter maka nanti akan disambungkan
    else if((*CurrentBar)->prev != Nil && *Cursor == Nil){

        (*CurrentBar)->prev->next = newBar;

        newBar->prev = (*CurrentBar)->prev;

        newBar->next = *CurrentBar;

        (*CurrentBar)->prev = newBar;

        *CurrentBar = newBar;

        *CursorY = PCY(*CursorY,0);
    }


    //kalo enter baris baru dibawah atau baris terakhir
    else {
    	
    	if((*Cursor) != Nil && (*Cursor)->next != Nil){
    		newBar->kol = (*Cursor)->next;
    		newBar->kol->prev = Nil;
    		newBar->tail = (*CurrentBar)->tail;
    		(*Cursor)->next = Nil;
    		(*CurrentBar)->tail = *Cursor;
    		int PanjangKiri = *CursorX - 3;
    		newBar->longBar = (*CurrentBar)->longBar;
    		(*CurrentBar)->longBar = PanjangKiri;
		}

        newBar->next = (*CurrentBar)->next;

        newBar->prev = *CurrentBar;

        //kalo ini ketika enter dan dibawhanya ada baris jadi kaya di tengah tengah ada baris baru
        //nah nanti yang dibawah disambungin sama yang baris baru
        //dan baris sekarang juga akan disambungin sama baris baru

        if ((*CurrentBar)->next != Nil)
            (*CurrentBar)->next->prev = newBar;

        (*CurrentBar)->next = newBar;

        *CurrentBar = newBar;

        *CursorY = PCY(*CursorY,1);
    }

    *Cursor = Nil;

    system("cls");

    printf(" TEXT EDITOR COBA COBA \n");

    printBar(*FirstBar);

    setCursor(*CursorX, *CursorY);
}


void InsertKarakter(char key, addressBar *FirstBar, addressBar *CurrentBar, addressKol *Cursor, int *CursorX, int CursorY){

    addressKol Q;

    Q = (addressKol) malloc(sizeof(Kol));

    Q->info = key;
    Q->prev = Nil;
    Q->next = Nil;


    //belum ada baris sama sekali
    if (*CurrentBar == Nil) {

        addressBar newBar = (addressBar) malloc(sizeof(Bar));

        newBar->kol = Q;
        newBar->tail = Q;

        newBar->prev = Nil;
        newBar->next = Nil;

        newBar->longBar = 0;

        *FirstBar = newBar;
        *CurrentBar = newBar;

        *Cursor = Q;
    }

    else {

        //insert di awal baris
        if (*Cursor == Nil) {

            Q->next = (*CurrentBar)->kol;

            if ((*CurrentBar)->kol != Nil)
                (*CurrentBar)->kol->prev = Q;

            (*CurrentBar)->kol = Q;

            //kalau sebelumnya baris kosong maka tail juga harus menunjuk node baru
            if ((*CurrentBar)->tail == Nil)
                (*CurrentBar)->tail = Q;

            *Cursor = Q;
        }


        //insert di tengah atau akhir
        else {

            Q->next = (*Cursor)->next;

            Q->prev = *Cursor;

            if ((*Cursor)->next != Nil){

                (*Cursor)->next->prev = Q;
            }

            //kalau insert di akhir maka tail pindah ke node baru
            else{

                (*CurrentBar)->tail = Q;
            }

            (*Cursor)->next = Q;

            *Cursor = Q;
        }
    }

    //panjang baris bertambah
    (*CurrentBar)->longBar++;

    *CursorX = PCX(*CursorX, 1);

    system("cls");

    printf(" TEXT EDITOR COBA COBA \n");

    printBar(*FirstBar);

    setCursor(*CursorX, CursorY);
}


void SelectingAtauTidak(int key,addressBar *CurrentBar,addressKol *Cursor,int *CursorX,int *CursorY,addressBar FirstBar,SelectPoint *SelStart,SelectPoint *SelEnd,int *Selecting)
{
    // awal selection
    if (*Selecting == 0){

        *Selecting = 1;

        SelStart->x = *CursorX;
        SelStart->kol = *Cursor;
    }


    // gerakkan cursor
    GerakKursor(key,CurrentBar,Cursor,CursorX,CursorY,FirstBar);

    // update titik akhir
    SelEnd->x = *CursorX;
    SelEnd->kol = *Cursor;
}
