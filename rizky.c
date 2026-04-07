#include "rizky.h"
#include "header_bersama.h"

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
