#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "najwan.h"
#include "header_bersama.h"

char clipboard[5000]; 


	void deleteSelection(){
	    int startX = selStartX, startY = selStartY;
	    int endX = selEndX, endY = selEndY;
	
	    // normalize
	    if(startY > endY || 
	      (startY == endY && startX > endX)){
	        
	        int tx = startX, ty = startY;
	        startX = endX; startY = endY;
	        endX = tx; endY = ty;
	    }
	
	    // ?? CASE 1: satu baris
	    if(startY == endY){
	        int len = strlen(text[startY]);
	        int i;
	
	        for(i = startX; i < len; i++){
	            text[startY][i] = text[startY][i + (endX - startX)];
	        }
	    }
	
	    // ?? CASE 2: multi baris
	    else{
	        // potong awal
	        text[startY][startX] = '\0';
	
	        // gabung dengan bagian akhir
	        strcat(text[startY], text[endY] + endX);
	
	        // hapus baris tengah
	        int i, j;
	        for(i = startY + 1; i <= endY; i++){
	            for(j = i; j < totalLines - 1; j++){
	                strcpy(text[j], text[j+1]);
	            }
	            totalLines--;
	            i--;
	            endY--;
	        }
	    }
	
	    cursorX = startX;
	    cursorY = startY;
	    isSelecting = 0;
	}



	void copySelection(){
	    if(!isSelecting) return;
	
	    normalizeSelection();   // ?? WAJIB
	
	    memset(clipboard, 0, sizeof(clipboard)); // ?? bersihin total
	
	    int i;
	    for(i = selStartY; i <= selEndY; i++){
	
	        // 1 BARIS
	        if(i == selStartY && i == selEndY){
	            strncat(clipboard, text[i] + selStartX, selEndX - selStartX);
	        }
	
	        // BARIS PERTAMA
	        else if(i == selStartY){
	            strcat(clipboard, text[i] + selStartX);
	            strcat(clipboard, "\n");
	        }
	
	        // BARIS TERAKHIR
	        else if(i == selEndY){
	            strncat(clipboard, text[i], selEndX);
	        }
	
	        // BARIS TENGAH
	        else{
	            strcat(clipboard, text[i]);
	            strcat(clipboard, "\n");
	        }
	    }
	
	    // ?? DEBUG (optional, buat cek)
	    // printf("\nCLIPBOARD:\n%s\n", clipboard);
	}
	
	int displayFiles(char files[][100]) {
    DIR *d;
    struct dirent *dir;
    int count = 0;

    d = opendir(".");
    if (!d) return 0;

    while ((dir = readdir(d)) != NULL) {
        // skip folder default
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
            printf("%d. %s\n", count + 1, dir->d_name);
            strcpy(files[count], dir->d_name);
            count++;
        }
    }

    closedir(d);
    return count;
}

		
		// delete file
	void deleteFile(const char *filename) {
    if (remove(filename) == 0) {
        printf("\nFile '%s' berhasil dihapus.\n", filename);
    } else {
        printf("\nGagal menghapus file '%s'.\n", filename);
    }

    char temp[5000];
    int i;

    temp[0] = '\0';

    if(selStartX == selEndX && selStartY == selEndY){
        return;
    }

    normalizeSelection();

    for(i = selStartY; i <= selEndY; i++){

        // ? 1 BARIS
        if(i == selStartY && i == selEndY){
            strncat(temp, text[i] + selStartX, selEndX - selStartX);
        }

        // ? BARIS PERTAMA
        else if(i == selStartY){
            strcat(temp, text[i] + selStartX);
            strcat(temp, "\n");
        }

        // ? BARIS TERAKHIR
        else if(i == selEndY){
            strncat(temp, text[i], selEndX);
        }

        // ? BARIS TENGAH
        else{
            strcat(temp, text[i]);
            strcat(temp, "\n");
        }
    }

    setClipboard(temp); // simpan ke clipboard
}

void setClipboard(const char *text){
    strcpy(clipboard, text);
}

char* getClipboard(){
    return clipboard;
}

void clearClipboard(){
    clipboard[0] = '\0';

}
