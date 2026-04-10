#include "rizky.h"
#include "header_bersama.h"
#include <dirent.h>

void newFile(char* namaFile) {
	printf("=== NEW FILE ===\n");
	printf("Masukkan nama file beserta ekstensi (contoh: catatan.txt): ");
	scanf("%s", namaFile);
	{
	    FILE* fp = fopen(namaFile, "w"); // buat file
		if (fp == NULL) {
	    	printf("Gagal membuat file %s\n", namaFile);
	    } else {
	        printf("File %s berhasil dibuat!\n", namaFile);
	        fclose(fp);
		}
	}
	
	printf("\nTekan ENTER untuk kembali ke menu...");
	getchar(); // bersihkan newline dari scanf
	getchar(); // tunggu user tekan ENTER
}

void openFileToBuffer(char *filename){
	FILE *fp = fopen(filename,"r");
	totalLines = 0;
	if (fp != NULL){
	    while(fgets(text[totalLines], MAX_COLS, fp) != NULL){
	        text[totalLines][strcspn(text[totalLines], "\n")] = 0;
	        totalLines++;
	        if(totalLines>=MAX_ROWS) break;
	    }
	    fclose(fp);
	}
	if (totalLines == 0){
		text[0][0] = '\0';
		totalLines = 1;
	}
}
	


int pilihFile(int j, int *pilihan) {
	printf("\nPilih nomor file untuk dibuka: ");
	scanf("%d", pilihan);
	getchar();
	if (*pilihan<1 || *pilihan>j-1) {
		printf("Nomor tidak valid!\n");
		getch();
		return 1;
	} 
	return 0;           
}



int openFile(char* namaFile) {
	char files[100][100];
	int j, pilihan;

	printf("=== OPEN FILE ===\n");
	                
	j = displayFiles(files);
	if (pilihFile(j, &pilihan)) {
		return 1;
	}
	strcpy(namaFile, files[pilihan-1]);
	openFileToBuffer(namaFile);
	cursorX=0; cursorY=0;
	editFile(namaFile);
}

	void cutSelection(){
	    if(!isSelecting) return;
	
	    normalizeSelection();
	
	    copySelection();        // ambil dulu
	    deleteSelection();      // hapus
	
	    // cursor fix
	    cursorX = selStartX;
	    cursorY = selStartY;
	
	    isSelecting = 0;
	    isModified = 1;
	}
