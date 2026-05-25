#include "rizky.h"
#include "hafiez.h"

void printBar(addressBar FirstBar) {
	int i = 1;
	addressBar temp = FirstBar;
    while (temp != Nil) {
        addressKol Q = temp->kol;
		printf("%d| ",i);
        while (Q != Nil) {
            printf("%c", Q->info);
            Q = Q->next;
        }

//        printf("   | longBar = %d", FirstBar->longBar);
		
		if(temp->tail != Nil) {
        printf("   | Tail = %c   |   Panjang : %d", temp->tail->info,temp->longBar); //ki urang nitip ini dulu lagi nyari bug dimananya
        }
        printf("\n");
        temp = temp->next;
        i++;
    	
    }
}

void backspace(addressBar FirstBar, addressBar *CurrentBar, addressKol *Cursor, int *CursorX, int *CursorY) {
	if(*Cursor == Nil && (*CurrentBar)->prev == Nil && (*CurrentBar)->kol == Nil) { // jika cursor saat ini nil, tidak memiliki baris sebelumnya, baris saat ini tidak memiliki node kol
		// tidak akan melakukan apa apa
	} else if (*Cursor == Nil && (*CurrentBar)->prev != Nil && (*CurrentBar)->kol != Nil) { // cek apakah kursor saat ini tidak menunjuk ke node manapun (artinya cursor berada di paling kiri baris) dan apakah baris saat ini memiliki baris sebelumnya dan apakah baris saat ini posisinya tidak kosong (yang artinya blok ini digunakan untuk meng-handle backspace di baris yang memiliki prev dan cursor berada di paling kiri dan baris saat ini memiliki node kol (terdapat huruf di baris saat ini)
		addressBar tempBar = *CurrentBar; // isi tempBar dengan pointer ke baris saat ini (akan digunakan untuk free)
		if ((*CurrentBar)->prev->tail != Nil) { // jika baris sebelumnya memiliki tail
			(*CurrentBar)->prev->tail->next = (*CurrentBar)->kol; // sambungkan next dari tail baris sebelumnya ke node pertama pada baris saat ini
			(*CurrentBar)->kol->prev = (*CurrentBar)->prev->tail; // sambungkan prev dari node pertama baris saat ini ke tail dari baris sebelumnya
		} else { // jika baris sebelumnya tidak memiliki tail / tidak memiliki node kol
			(*CurrentBar)->prev->kol = (*CurrentBar)->kol; // isi kol dari baris sebelumnya dengan node pertama dari baris saat ini
		}
		(*CurrentBar)->kol = Nil; // reset isi dari kol baris saat ini
		if ((*CurrentBar)->next != Nil) { // cek apakah baris saat ini memiliki baris selanjutnya
			(*CurrentBar)->prev->next = (*CurrentBar)->next; // isi next dari baris sebelumnya dengan baris selanjutnya
			(*CurrentBar)->next->prev = (*CurrentBar)->prev; // isi prev dari baris selanjutnya dengan baris sebelumnya
		} else { // jika baris saat ini tidak memiliki baris selanjutnya
			(*CurrentBar)->prev->next = Nil; // isi next dari baris sebelumnya menjadi Nil (memutus rantai)
		}
		*Cursor = (*CurrentBar)->prev->tail; // cursor akan menunjuk tail dari baris sebelumnya
		(*CurrentBar)->prev->tail = (*CurrentBar)->tail; // isi tail dari baris sebelumnya menjadi tail dari baris saat ini
		*CursorY = PCY(*CursorY, -1); // kurangi nilai dari cursorY sebanyak 1
		*CursorX = PCX(*CursorX, (*CurrentBar)->prev->longBar); // ubah nilai cursorX menjadi panjang dari baris sebelumnya
		(*CurrentBar)->prev->longBar = (*CurrentBar)->prev->longBar + (*CurrentBar)->longBar; // isi longBar dari baris sebelumnya menjadi jumlah dari panjang baris sebelumnya dengan baris saat ini
		*CurrentBar = (*CurrentBar)->prev; // ubah pointer currentbar menjadi menunjuk ke baris sebelumnya
		free(tempBar); // membebaskan node baris yang tadi (currentbar)
	} else if (*Cursor != Nil) { // jika kursor saat ini tidak nil (berarti sedang menunjuk ke node kol (huruf)
		addressKol tempKol = *Cursor; // isi tempKol dengan pointer ke node kol (huruf) saat ini;
		if ((*Cursor)->prev != Nil && (*Cursor)->next == Nil) { // jika node kol saat ini memiliki node sebelumnya namun tidak memiliki node selanjutnya
			(*Cursor)->prev->next = Nil; // reset isi next dari node kol sebelumnya
			(*CurrentBar)->tail = (*Cursor)->prev; // ubah isi tail dari baris saat ini menjadi node kol sebelumnya
			*Cursor = (*Cursor)->prev; // isi cursor menjadi node kol sebelumnya
		} else if ((*Cursor)->prev != Nil && (*Cursor)->next != Nil) { // jika node saat ini memiliki node sebelumnya, berarti cursor sedang menunjuk node yang berada di tengah
			(*Cursor)->prev->next = (*Cursor)->next; // isi next dari node kol sebelumnya menjadi node kol selanjutnya
			(*Cursor)->next->prev = (*Cursor)->prev; // isi prev dari node kol selanjutnya menjadi node kol sebelumnya
			*Cursor = (*Cursor)->prev; // isi cursor menjadi node kol sebelumnya
		} else if ((*Cursor)->prev == Nil && (*Cursor)->next != Nil) { // jika node kol saat ini memiliki prev Nil (node kol saat ini adalah node pertama) dan node kol saat ini memiliki node selanjutnya (masih ada huruf di kanannya)
			(*CurrentBar)->kol = (*Cursor)->next; // isi elemen pertama dari node baris menjadi node kol selanjutnya
			(*Cursor)->next->prev = Nil; // isi prev dari node kol selanjutnya menjadi Nil
			*Cursor = Nil; // isi cursor dengan Nil karena saat ini kursor akan berada di paling kiri baris tersebut (tidak menunjuk node kol manapun)
		} else { // jika node kol saat ini tidak berada di kedua kondisi diatas (node baris saat ini hanya memiliki 1 node kol, yaitu node yang ditunjuk oleh cursor)
			(*CurrentBar)->kol = Nil; // reset isi dari baris saat ini
			(*CurrentBar)->tail = Nil; // reset isi dari tail baris saat inii
			*Cursor = Nil; // reset isi dari cursor
		}
		(*CurrentBar)->longBar--; // kurangi panjang dari longbar sebanyak 1
		if (*CursorX > 3) { // memastikan agar nilai cursor x tidak kurang dari 3
			*CursorX = PCX(*CursorX, -1); // kurangi nilai cursor x sebanyak 1
		}
		free(tempKol); // membebaskan node kol yang tadi (yang tadi ditunjuk cursor)
	} else { // berarti jika kursor saat ini tidak menunjuk ke node manapun, dalam kondisi memiliki node baris sebelumnya, yang artinya baris saat ini kosong, ini sama saja seperti menghapus baris saat ini
		addressBar tempBar = (*CurrentBar); // isi tempBar dengan pointer ke baris saat ini (akan digunakan untuk free)
		*Cursor = (*CurrentBar)->prev->tail; // kursor akan menunjuk ke elemen terakhir dari node baris sebelumnya
		*CursorY = PCY(*CursorY, -1); // kurangi nilai dari kursor y sebanyak 1
		*CursorX = PCX(*CursorX, (*CurrentBar)->prev->longBar); // tambah nilai dari kursor x sebanyak jumlah elemen pada node baris sebelumnya
		if ((*CurrentBar)->next != Nil) { // jika node baris saat ini memiliki node selanjutnya
			(*CurrentBar)->prev->next = (*CurrentBar)->next; // isi next dari node baris sebelumnya menjadi node selanjutnya dari node baris saat ini
			(*CurrentBar)->next->prev = (*CurrentBar)->prev; // isi prev dari node baris selanjutnya menjadi node sebelumnya dari node baris saat ini
		} else {
			(*CurrentBar)->prev->next = Nil; // reset nilai dari next node baris sebelumnya
		}
		*CurrentBar = (*CurrentBar)->prev; // ubah pointer currentbar menjadi menunjuk ke node sebelumnya
		free(tempBar); // membebaskan node baris yang tadi (currentbar)
	}
	
	system("cls");
	printf(" TEXT EDITOR COBA COBA \n");
	printBar(FirstBar);
	setCursor(*CursorX, *CursorY);
	
}

