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

        if (*CursorX > 5)
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

        if (*CursorX - 5 < (*CurrentBar)->longBar) //Selama posisi Kursor tidak melebihi panjang suatu abris maka dia bisa bergeser ke kanan
            *CursorX = PCX(*CursorX, +1);
    }



    // ================= KURSOR ATAS =================
    else if (key == 72){

        if ((*CurrentBar)->prev == Nil) //jika diatasnya tidak ada baris maka tidak melakukan apa apa
            return;

        //ketika baris saat ini lebih pendek daro baris di atasnya maka posisi kursor di kolom tidak pindah hanya posisi abrisnya saja
        if (
            (*CurrentBar)->longBar <= (*CurrentBar)->prev->longBar || // jika panjang longbar saat ini kurang dari sama dengan  panjang baris sebelumnya 
            *CursorX - 5 <= (*CurrentBar)->prev->longBar //maka posisi koordinat cursor akan berada di ujung baris
        ){

            *CurrentBar = (*CurrentBar)->prev; // pointer current barakan berpindah ke baris sebelumnya

            if(*Cursor == Nil){ // kalau posisi kursor ada dia wal baris alias nul 
                *Cursor = Nil; //maka ketika pindah baris juga cursor akan Nil
            }

            else{

                *Cursor = (*CurrentBar)->kol; //cusor akan berpindah ke baris atas

                //maka kursor akan digeser sehauh posisi kursor terakhir biasanay ini terjadi jika di 
                for (i = 1; i < *CursorX - 5; i++){
                    *Cursor = (*Cursor)->next;
                }
            }
        }


        //Ketika baris saat ini lebih panjang dari baris diatasnya maka ketika pindah baris juga cursor akan Nil
        else {
            *CurrentBar = (*CurrentBar)->prev; // pointer currentbar akan oindah ke baris diatasnya
            *Cursor = (*CurrentBar)->tail;    //maka ketika pindah baris juga cursor akan Nil
            *CursorX = (*CurrentBar)->longBar + 5; //koordinat cursor akan di set berada di ujung kanan baris tersebut
        }
        *CursorY = PCY(*CursorY,-1); //koordinat cursor Y akan berkurang 1
    }



    // ================= KURSOR BAWAH =================
    else if (key == 80){
        if ((*CurrentBar)->next == Nil) //jika dibawahnya tidak ada baris maka tidak melakukan apa apa
            return;
            
        //ketika dibawahnya saat ini lebih pendek dari baris saat ini maka posisi kursor dikolom tidak akan berubah posisi barisnya saja yang berubah
        if ((*CurrentBar)->longBar <= (*CurrentBar)->next->longBar || *CursorX - 5 <= (*CurrentBar)->next->longBar){
            *CurrentBar = (*CurrentBar)->next; // pointer current bar berpindah
            
            if(*Cursor == Nil){ // kalau cursor sekarang ada di awal baris atau = Nil 
                *Cursor = Nil; //maka ketika pindah ke bawah dia juga bernilai Nil Cursornya
            }

            else{
                *Cursor = (*CurrentBar)->kol; //Cursor akan berpindah ke kol baris sekarang
                
                //Cursor digeser sebanyak posisi kursor terakhir
                for (i = 1; i < *CursorX - 5 ; i++){
                    *Cursor = (*Cursor)->next;
                }
            }
        }

        //ketika baris di bawahnya lebih pendek dari baris saat ini maka posisi kursor akan berada di ujung baris di bawahnya dan pindah ke baris dibawhnya
        else {

            *CurrentBar = (*CurrentBar)->next; //pointer currentBar akan berpindah
            *Cursor = (*CurrentBar)->tail; // pointer Cursor akan berada di node ujung kanan di baris di bawahnya a
            *CursorX = (*CurrentBar)->longBar + 5; //koordinat cursorx akan di set berda di ujung kanan baris bawah
        }
        *CursorY = PCY(*CursorY,+1); //koordinat kursor y akan bertambah 1
    }

    system("cls");
    printf(" TEXT EDITOR COBA COBA \n");
    printBar(FirstBar);
    setCursor(*CursorX, *CursorY);
}

void BarisBaru(addressBar *CurrentBar, addressBar *FirstBar, addressKol *Cursor, int *CursorX, int *CursorY){

    addressBar newBar = (addressBar) malloc(sizeof(Bar)); //mengalokasikan sejumlah memory untuk sebuah variable yang bertipe data addressBar

    newBar->kol = Nil;     //nilai awal 
    newBar->tail = Nil;   //nilai awal 
    newBar->next = Nil; 	//nilai awal 
    newBar->prev = Nil;	//nilai awal 
    newBar->longBar = 0;	//nilai awal 



    //kalo belum ada baris sama sekali
    if (*CurrentBar == Nil) {

        *FirstBar = newBar; // first bar akan diisi baris hasil malloc 
        *CurrentBar = newBar;  //pointer currentBar menunjuk baris baru tersebut
    }


    //kalo enter di baris pertama untuk membuat baris baru diatasnya maka baris baru tersebut akan menjadi baris pertama
    else if ((*CurrentBar)->prev == Nil && *Cursor == Nil) {

        newBar->next = *CurrentBar; //baris sebelumnya akan akan disambungkan dengan baris pertama
        newBar->prev = Nil; //baris saat ini bagian prev akan diset nil akrena ia baris pertama

        (*CurrentBar)->prev = newBar; //pointer currentbar akan berpindah ke baris hasil malloc

        *FirstBar = newBar; //firstbar akan berubah karena baris pertama berubah menjadi baris baru

        *CursorY = PCY(*CursorY,1); //koordinat kursor y akana bertambah 1
    }


    //kalo enter untuk membuat baris baru diatasnya dan ada baris sebelum di enter maka nanti akan disambungkan alias di antara 2 barisa
    else if((*CurrentBar)->prev != Nil && *Cursor == Nil){

        (*CurrentBar)->prev->next = newBar; //baris yang baru akan disambungkan dengan baris sebelumnya sebelum di tekan enter , jadi jika ada baris diatas baris baru maka bagian next dari baris tersebut akan munjuk baris baru

        newBar->prev = (*CurrentBar)->prev; //baris baru bagian prev akan menunjuk baris diatasnya/sebelumnya 

        newBar->next = *CurrentBar; //baris baru bagian next akan menunjuk baris sebelum di tenkan enter

        (*CurrentBar)->prev = newBar; //baris sebelum tekan enter yang bagian prev akan menunjuk baris baru

        *CursorY = PCY(*CursorY,1); //koordinat cursor Y akan bertambah 1
    }


    //kalo enter baris baru dibawah atau baris terakhir
    else {
    	
    	if((*Cursor) != Nil && (*Cursor)->next != Nil){ //jika Cursor tidak nil alias sedang menunjuk sesuatu dan cursor next juga tidak nil artinya ada karakter disebelahnya 
    		newBar->kol = (*Cursor)->next; // baris baru bagian kolom akan menunjuk karakter sebelah kiri cursor sbelum di enter
    		newBar->kol->prev = Nil;  //karakter pertama pada baris baru bagian prevnya akan bernilai nil, akrena ia merupaka kolom atau akrakter pertama
    		newBar->tail = (*CurrentBar)->tail; //baris baru bagian tail akan menunjuk tail baris sebelum di tekan enter
    		(*Cursor)->next = Nil; //node yang sedang oleh cursor bagian nextnya akan di set nil , karena karakter baris tersebut sudah di split
    		(*CurrentBar)->tail = *Cursor; //current bar saat ini bagian tail akan berubah menadi 
    		int PanjangKiri = HitungPanjangKiri((*CurrentBar)->kol,*Cursor); //panjang sbelah kiri kursor akan dihitung dengan melakukan looping 
    		newBar->longBar = (*CurrentBar)->longBar - PanjangKiri; //panjang baris baru akan dihitung dengan cara mengurangi panjang abris sebelumnya dikurangi panajng kiri cursor
    		(*CurrentBar)->longBar = PanjangKiri; //panjang kiri baris sebelunya akan di ubah menjadi panjang kiri karena panajng baris tersebut berubah setelah di split
		}

        newBar->next = (*CurrentBar)->next; //baris baru yang bagian next akan bernilai nil

        newBar->prev = *CurrentBar; // baris baru bagian prev akan menunjuk baris sebelum di tekan enter
        

        //kalo ini ketika enter dan dibawhanya ada baris jadi kaya di tengah tengah ada baris baru
        //nah nanti yang dibawah disambungin sama yang baris baru
        //dan baris sekarang juga akan disambungin sama baris baru
        if ((*CurrentBar)->next != Nil)
            (*CurrentBar)->next->prev = newBar;

        (*CurrentBar)->next = newBar; //baris sebelum ditekan enter bagian next aka menunjuk baris baru
 
        *CurrentBar = newBar; //pointer current bar aka menunjuk baris baru
		*CursorX = 5; //koordinat cursor akan di set ke posisi awal baris
        *CursorY = PCY(*CursorY,1); //cursor y akan bertambah 1
    }

    *Cursor = Nil; //pointer cursor akan bernilai nil karena berada di awal baris
	
    system("cls");

    printf(" TEXT EDITOR COBA COBA \n");

    printBar(*FirstBar);

    setCursor(*CursorX, *CursorY);
}


void InsertKarakter(char key, addressBar *FirstBar, addressBar *CurrentBar, addressKol *Cursor, int *CursorX, int CursorY){

    addressKol Q;

    Q = (addressKol) malloc(sizeof(Kol)); //mengalokasikan sejumlah memori untuk variabel yang bertipe addressKol

    Q->info = key;	//nilai awal
    Q->prev = Nil; //nilai awal
    Q->next = Nil;	//nilai awal


    //belum ada baris sama sekali
    if (*CurrentBar == Nil) {

        addressBar newBar = (addressBar) malloc(sizeof(Bar));// akan mengalokasikan sejumlah memori untuk variabel yang bertipe data addressbar alias membuat baris baru

        newBar->kol = Q; //bagian kol dari baris baru tersebut akan menunjuk node pertama yang diinput oleh user
        newBar->tail = Q; //newbar bagian tail akan menunjuk node hasil inputan user

        newBar->prev = Nil;// karena ini merupakan baris pertama maka bagian prev akan bernilai nil
        newBar->next = Nil;// karena ini merupakan baris pertama maka bagian next akan bernilai nil

        newBar->longBar = 0; //nilai longbar dari abris tersbut akan bernilai nil akrena user belum me

        *FirstBar = newBar; //baris ini akan menjadi baris pertama
        *CurrentBar = newBar; //pointer current bar akan menunjuk baris saat ini

        *Cursor = Q; //pointer cursor akan menunjuk node saat ini hasil inputan user
    }

    else {

        //insert di awal baris
        if (*Cursor == Nil) {

            Q->next = (*CurrentBar)->kol; //ketika insert di awal baris maka node hasil iputan user akan menjadi node pertama di abris tersebut

            if ((*CurrentBar)->kol != Nil)// jika di baris tersebut memiliki karakter sebelumyna
                (*CurrentBar)->kol->prev = Q; //maka karakter pertama pada baris tersebut bagian prevnay akan menunjuk hasil inputan baru dari user 

            (*CurrentBar)->kol = Q; //bagian kol dari currentbar akan menunjuk node baru hasil inputan user karena node baru tersebut menjadi kolom pertama  di abris tersebut

            //kalau sebelumnya baris kosong maka tail juga harus menunjuk node baru
            if ((*CurrentBar)->tail == Nil)
                (*CurrentBar)->tail = Q;// bagian tail dari baris tersebut akan menunjuk node baru hasil inputan user

            *Cursor = Q;// cursor akan menunjuk  node baru tersebut
        }


        //insert di tengah atau akhir
        else {

            Q->next = (*Cursor)->next; //bagian next dari node baru akan menunjuk sesuatu yang ditunjuk oleh pointer cursor saat ini bagian next

            Q->prev = *Cursor; // node bari bagian prev akan menunjuk pointer cursor saat ini

            if ((*Cursor)->next != Nil){ //jika pointer cursor saat ini bagian nextnya tidak nil alias ada karakter dis ebelah kanan kursor 

                (*Cursor)->next->prev = Q; // maka node/karakter disebelahkanan cursor bagian prevnya akan menunjuk node baru tersebut
            }

            //kalau insert di akhir maka tail pindah ke node baru
            else{

                (*CurrentBar)->tail = Q; // maka Q atau node baru tersebut otomatis menjadi tail dari baris tesebut karena node abru berda di ujung kanan
            }

            (*Cursor)->next = Q; //node yang sedang ditunjuk pointer cursor saat ini bagian nextnya akan menunjuk node baru

            *Cursor = Q;
        }
    }

    //panjang baris bertambah
    (*CurrentBar)->longBar++; //panjang baris akan bertambah 1

    *CursorX = PCX(*CursorX, 1); //koordinat cursor X akan bertambah 1

    system("cls");

    printf(" TEXT EDITOR COBA COBA \n");

    printBar(*FirstBar);

    setCursor(*CursorX, CursorY);
}


void SelectingAtauTidak(int key,addressBar *CurrentBar,addressKol *Cursor,int *CursorX,int *CursorY,addressBar FirstBar,SelectPoint *SelStart,SelectPoint *SelEnd,int *Selecting){

    if (*Selecting == 0){

        *Selecting = 1;

        if (key == 75){

            // gerakkan cursor dulu
//            GerakKursor(key, CurrentBar, Cursor,CursorX,CursorY,FirstBar); //kusor akan bergerak ke node kiri terlebih dahulu

            if (*Cursor != Nil){ //jika cursor tidak nil
                SelStart->kol = *Cursor; //pointer selecstart bagian kol akan menunjuk node yang sedang di tunjuk oleh pointer cursor bagian next = AB|C     A|BC maka B akan terselect
            	SelEnd->kol = SelStart->kol; // node pertama yang di select akan menjadi node terakhir juga yang di select

            // posisi visual
            SelStart->x = *CursorX ; // titik korrdinat dari node yang diselect 
            SelEnd->x = *CursorX ; // titik korrdinat dari node yang diselect  
            GerakKursor(key, CurrentBar, Cursor,CursorX,CursorY,FirstBar); //kusor akan bergerak ke node kiri terlebih dahulu
			}

        }


        else if (key == 77){

            // gerakkan cursor dulu
            GerakKursor(key, CurrentBar, Cursor,CursorX,CursorY,FirstBar);

            if (*Cursor != Nil){      //jika pointer cursor tidak nil
                SelStart->kol = *Cursor;   // pointer select awal bagian kol akan menunjuk yang sedang ditunjuk oleh cursor
            }

            SelEnd->kol = SelStart->kol; //select akhir juga akan menunjuk node yang sama dengan select awal

            // posisi secar visual
            SelStart->x = *CursorX; //koordinat dari node awal yang diselect akan disimpan oleh select awal bagian x
            SelEnd->x = *CursorX;	//koordinat dari node akhir yang diselect akan disimpan oleh select akhir bagian x
        }
    }


    else{



        if (key == 75){

//            GerakKursor(key, CurrentBar, Cursor,CursorX,CursorY,FirstBar);

            if (*Cursor != Nil){
                SelEnd->kol = *Cursor; // pointer select akhir bagian kol akan menunjuk yang sedang ditunjuk oleh cursor
                SelEnd->x = *CursorX ;  //koordinat dari node akhir yang diselect akan disimpan oleh select awal bagian x
            }
            GerakKursor(key, CurrentBar, Cursor,CursorX,CursorY,FirstBar);
        }

        else if (key == 77){

            GerakKursor(key, CurrentBar, Cursor,CursorX,CursorY,FirstBar);

            if (*Cursor != Nil){
                SelEnd->kol = *Cursor; //pointer select end bagian kol akan menunjuk node yang sedang ditunjuk oleh pointer cursor
                SelEnd->x = *CursorX; //koordinat dari node akhir yang diselect akan disimpan oleh select awal bagian x
            }
        }
    }
}

int HitungPanjangKiri(addressKol CurrentBar, addressKol Cursor)
{
    int panjang = 0;

    addressKol P = CurrentBar; //pointe P akan menunjuk node pertama suatu baris

    while (P != Nil && P != Cursor->next){ // selama pointer P tidak menunjuk node yang sama seperti yang sedang di tunjuk oleh cursor->next maka
        panjang++; //panjang akan bertambah, ini digunakan utuk menghitung betapa banyak karakter di sebelah kiri kursor dari awal baris hingga posisi kursor
        P = P->next; //P akan bergeser ke node selanjutnya
    }

    return panjang; //mereturnkan panjang karakter disebelah kiri kursor
}

void TukarSelect(SelectPoint *SelStart,SelectPoint *SelEnd)//prosedur ini digunakan untuk menukar posisi awal select dan akhir select jika diselec dari kiri ke kanan
{

    if (SelStart->x > SelEnd->x){ //jika posisi koordinat karakter yang di select lebih besar dari posisi koordinat karakter akhir yang di select

        SelectPoint Temp = *SelStart; //posisi select awal akan ditunjuk sementara

        *SelStart = *SelEnd; //pointer select awal akan menunjuk node yang ditunjuk pointer select akhir

        *SelEnd = Temp; //pointer select akhir akan menunjuk node yang sebelumnya di tunjuk oleh pointer select awal
    }
}

void PasteClipboard(addressBar FirstBar,addressBar *CurrentBar,addressKol *Cursor,addressClipboard Clipboard,int *CursorX,int CursorY ){
	
    addressClipboard DuplikatClipboard = Nil; //nilai awal

    if (Clipboard != Nil){ //selama clipboard tidak nil

        DuplikatClipboard = CopyToClipboard(Clipboard->kol,Clipboard->tail); //pointer DuplikatClipboard akan menunjuk hasil duplikat dari clipboard

        if (*Cursor != Nil){ // kalo cursor ga di ujung kiri

            if((*Cursor)->next != Nil){ //jika di sebalah kanan kursor ada arakter
            	
                // kalo kursor di tengah tengah
                (*Cursor)->next->prev = DuplikatClipboard->tail; //jadi karakter yang ada di sebelah kanan kursor bagian prevny akan menunjuk node tail dari clipboard 

                DuplikatClipboard->tail->next = (*Cursor)->next; //tail atau ujung kanan dari node bagian next akan menunjuk karakter disebelah kanan kursor
            }
            
            else if ((*Cursor)->next == Nil){
				(*CurrentBar)->tail = DuplikatClipboard->tail;
			}

            (*Cursor)->next = DuplikatClipboard->kol; //node yang sedang ditunjuk oleh cursor bagian nextnya akan menunjuk node pertama atau node paling kiri dari clipboard

            DuplikatClipboard->kol->prev = *Cursor; //ujung kkiri atau node pertama dari clipboard bagian prevnya akan menunjuk node yang sedang  ditunjuk oleh cursor

            (*CurrentBar)->longBar = (*CurrentBar)->longBar + DuplikatClipboard->longBar; //panjang baris tersbut akan ditambahn dengan panjang clipboard
            
			if ((*Cursor)->next == Nil){
				(*CurrentBar)->tail = DuplikatClipboard->tail;
			}
        }

        else{

            if((*CurrentBar)->kol != Nil){ //jika baris tersebut tidak kosong maka dan akan mempaste di awal baris alias di paling kiri

                (*CurrentBar)->kol->prev = DuplikatClipboard->tail;// bagian prev dari node pertama di baris tersebut akan menunjuk tail atau nnode ujung kanan dari clipboard

                DuplikatClipboard->tail->next = (*CurrentBar)->kol; //clipboard yang bagian tail atau node yang paling ujung kanan bagian nextnya akan menunjuk node pertama pada baris tersebut

                (*CurrentBar)->kol = DuplikatClipboard->kol; //node pertama pada baris tersebut berubah jadi node pertama di clipboard

                (*CurrentBar)->longBar = (*CurrentBar)->longBar + DuplikatClipboard->longBar; //panjang baris tersebut akan ditambah dengan panajng karakter pada clipboard
            }

            else{ //ini kalo di abris tersebut kosong

                (*CurrentBar)->kol = DuplikatClipboard->kol; //node pertama pada baris tersebut adalah node pertama pada clipboard

                (*CurrentBar)->longBar = DuplikatClipboard->longBar; //panjang baris tersebut akan sama dengan panajgn baris pada clipboard

                (*CurrentBar)->tail = DuplikatClipboard->tail; //tail pada baris tersebut akan sama dengan tail pada clipboard
            }
        }
    }

    else{
        return;
    }
	
    *Cursor = DuplikatClipboard->tail; //pointer cursor menunjuk node terakhir atau ujung kanan pada clipboard

    *CursorX =PCX(*CursorX,DuplikatClipboard->longBar); //koordinat kursor x akan bergerak sejauh panajng akrakter pada clipboard

    DuplikatClipboard->kol = Nil; //duplikatclipboard bagian kol akan bernilai nil

    free(DuplikatClipboard); //membebaskan duplikat clipboard
    
    system("cls");

    printf(" TEXT EDITOR COBA COBA \n");

    printBar(FirstBar);

    setCursor(*CursorX,CursorY);

}
