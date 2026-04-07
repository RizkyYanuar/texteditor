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
	
int listingFile(char files[][100], int *j) {
	struct dirent *entry;
    DIR *dir = opendir(".");
    				
    if (dir == NULL) {
		printf("Folder kosong atau tidak ada file!\n");
	    return 1;
	}
				    
	int i=1;
	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") != 0 &&
		strcmp(entry->d_name, "..") != 0) {
		strcpy(files[i-1], entry->d_name);
		printf("%d. %s\n", i, entry->d_name);
		i++;
		}
	}
		
	closedir(dir);
	if(i==1){
	    printf("Tidak ada file.\n");
	    getch();
	    return 1;
	}                
	*j = i;
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
	                
	listingFile(files, &j);
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
	
	    normalizeSelection();   // ?? WAJIB
	
	    copySelection();        // ambil dulu
	    deleteSelection();      // hapus
	
	    // ?? pastikan cursor fix
	    cursorX = selStartX;
	    cursorY = selStartY;
	
	    isSelecting = 0;
	    isModified = 1;
	}
