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
	
	    // ?? normalize manual (tanpa ubah global)
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
	
	void pasteClipboard(){
	    if(strlen(clipboard) == 0) return;
	
	    if(isSelecting){
	        deleteSelection();
	    }
	
	    char temp[5000];
	    strcpy(temp, clipboard);
	
	    char *line = strtok(temp, "\n");
	    int first = 1;
	
	    while(line != NULL){
	
	        if(first){
	            int len = strlen(text[cursorY]);
	            int lineLen = strlen(line);
	
	            if(len + lineLen < MAX_COLS){
	                int i;
	                for(i = len; i >= cursorX; i--){
	                    text[cursorY][i + lineLen] = text[cursorY][i];
	                }
	
	                memcpy(&text[cursorY][cursorX], line, lineLen);
	                cursorX += lineLen;
	            }
	            first = 0;
	        }
	        else{
	            if(totalLines < MAX_ROWS - 1){
	                int i;
	                for(i = totalLines; i > cursorY + 1; i--){
	                    strcpy(text[i], text[i-1]);
	                }
	
	                cursorY++;
	                strcpy(text[cursorY], line);
	                cursorX = strlen(line);
	                totalLines++;
	            }
	        }
	
	        line = strtok(NULL, "\n");
	    }
	
	    isModified = 1;
	}
	
	void openFileToBuffer(char *filename){
	    FILE *fp = fopen(filename,"r");
	    totalLines = 0;
	    if(fp != NULL){
	        while(fgets(text[totalLines], MAX_COLS, fp) != NULL){
	            text[totalLines][strcspn(text[totalLines], "\n")] = 0;
	            totalLines++;
	            if(totalLines>=MAX_ROWS) break;
	        }
	        fclose(fp);
	    }
	    if(totalLines == 0){
		    text[0][0] = '\0';
		    totalLines = 1;
		}
	}
