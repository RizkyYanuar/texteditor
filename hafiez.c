#include "hafiez.h"
#include "header_bersama.h"
#include "najwan.h"

void saveFile(char *filename){
		int i;
	    FILE *fp = fopen(filename,"w");
	    for(i=0;i<totalLines;i++){
	        fprintf(fp,"%s\n", text[i]);
	    }
	    fclose(fp);
	}

	
		void moveCursor(int x, int y){
	    COORD pos;
	    pos.X = x;
	    pos.Y = y;
	    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}
	
	void normalizeSelection(){
	    if(selStartY > selEndY || 
	      (selStartY == selEndY && selStartX > selEndX)){
	        
	        int tx = selStartX, ty = selStartY;
	        selStartX = selEndX; selStartY = selEndY;
	        selEndX = tx; selEndY = ty;
	    }
	}
	
	int isSelected(int x, int y){
	    int startX = selStartX, startY = selStartY;
	    int endX = selEndX, endY = selEndY;
	
	    // normalize manual (tanpa ubah global)
	    if(startY > endY || 
	      (startY == endY && startX > endX)){
	        
	        int tx = startX, ty = startY;
	        startX = endX; startY = endY;
	        endX = tx; endY = ty;
	    }
	
	    if(y < startY || y > endY) return 0;
	
	    if(startY == endY){
	        return (x >= startX && x < endX);
	    }
	    else if(y == startY){
	        return x >= startX;
	    }
	    else if(y == endY){
	        return x < endX;
	    }
	    else{
	        return 1;
	    }
	}
	
	void setColor(int color){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}
	

	void pasteClipboard(){
    int len, clipLen, i;
    char *clip = getClipboard();

    if(strlen(clip) == 0){
        return;
    }

    len = strlen(text[cursorY]);
    clipLen = strlen(clip);

    if(len + clipLen < MAX_COLS){
        for(i = len; i >= cursorX; i--){
            text[cursorY][i + clipLen] = text[cursorY][i];
        }

        memcpy(&text[cursorY][cursorX], clip, clipLen);
        cursorX += clipLen;
    }

    isModified = 1;
}
	


	

