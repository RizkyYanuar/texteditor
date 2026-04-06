#include "najwan.h"
#include "header_bersama.h"

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
