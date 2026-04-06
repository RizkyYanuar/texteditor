#include "hafiez.h"
#include "headerbersama.h"
//int totalLines = 0;
//char text[MAX_ROWS][MAX_COLS];
//int cursorX = 0;
//int cursorY = 0;
//int viewTop = 0; 
//int isModified = 0;
//int isShiftPressed(){
//	return (GetKeyState(VK_SHIFT) & 0x8000);
//}
//int selStartX = 0, selStartY = 0;
//int selEndX = 0, selEndY = 0;
//int isSelecting = 0;
//char clipboard[5000]; 

void saveFile(char *filename){
		int i;
	    FILE *fp = fopen(filename,"w");
	    for(i=0;i<totalLines;i++){
	        fprintf(fp,"%s\n", text[i]);
	    }
	    fclose(fp);
	}

	void editFile(char *filename){
	    char key;
	    drawEditor(filename);
	    moveCursor(5, cursorY + HEADER_LINES); // posisi cursor setelah nomor baris
		if(totalLines == 0){
		    text[0][0] = '\0';
		    totalLines = 1;
		}
	    while(1){
	        key = getch();
	        
	        if(key == 3){ // Ctrl + C
			    copySelection();
			    isSelecting = 0;
			}
			
			else if(key == 24){ // Ctrl + X
			    cutSelection();
			}
			
			else if(key == 22){ // Ctrl + V
			    pasteClipboard();
			}
	
	        // ESC untuk keluar edit
	        if(key == 27) {
	        	isModified = 0;
	        	break;
			}
	
	        // Arrow key
	        if(key == 0 || key == -32){
	            key = getch();
	
		    int shift = isShiftPressed();
		
		    // ?? ATAS
		    if(key == 72 && cursorY > 0){
		        if(shift && !isSelecting){
		            selStartX = cursorX;
		            selStartY = cursorY;
		            isSelecting = 1;
		        }
		
		        cursorY--;
		
		        if(cursorX > strlen(text[cursorY])){
		            cursorX = strlen(text[cursorY]);
		        }
		    }
		
		    // ?? BAWAH
		    else if(key == 80 && cursorY < totalLines - 1){
		        if(shift && !isSelecting){
		            selStartX = cursorX;
		            selStartY = cursorY;
		            isSelecting = 1;
		        }
		
		        cursorY++;
		
		        if(cursorX > strlen(text[cursorY])){
		            cursorX = strlen(text[cursorY]);
		        }
		    }
		
		    // ?? KIRI
		    else if(key == 75 && cursorX > 0){
		        if(shift && !isSelecting){
		            selStartX = cursorX;
		            selStartY = cursorY;
		            isSelecting = 1;
		        }
		
		        cursorX--;
		    }
		
		    // ?? KANAN
		    else if(key == 77 && cursorX < strlen(text[cursorY])){
		        if(shift && !isSelecting){
		            selStartX = cursorX;
		            selStartY = cursorY;
		            isSelecting = 1;
		        }
		
		        cursorX++;
		    }
	        // ?? HANDLE DELETE DULU
			if(key == 83){
			
			    if(isSelecting){
			        deleteSelection();
			    }
			    else{
			        int len = strlen(text[cursorY]);
			
			        if(cursorX < len){
			            int i;
			            for(i = cursorX; i < len; i++){
			                text[cursorY][i] = text[cursorY][i+1];
			            }
			        }
			        else{
			            if(cursorY < totalLines - 1){
			                int nextLen = strlen(text[cursorY + 1]);
			
			                if(len + nextLen < MAX_COLS){
			                    strcat(text[cursorY], text[cursorY + 1]);
			
			                    int i;
			                    for(i = cursorY + 1; i < totalLines - 1; i++){
			                        strcpy(text[i], text[i+1]);
			                    }
			
			                    totalLines--;
			                }
			            }
			        }
			    }
			
			    isModified = 1;
			}
			
			// ?? BARU update selection
			if(isSelecting){
			    if(shift){
			        selEndX = cursorX;
			        selEndY = cursorY;
			    } else {
			        isSelecting = 0;
			    }
			}
	        }
	        // Backspace
	        else if(key == 8){
	            if(isSelecting){
		        deleteSelection();
		    }
		
		    else{
		        int len = strlen(text[cursorY]);
		
		        if(cursorX > 0){
		            int i;
		            for(i = cursorX-1; i < len; i++){
		                text[cursorY][i] = text[cursorY][i+1];
		            }
		            cursorX--;
		        }
		
		        else{
		            // ?? join ke atas
		            if(cursorY > 0){
		                int prevLen = strlen(text[cursorY - 1]);
		
		                if(prevLen + len < MAX_COLS){
		                    strcat(text[cursorY - 1], text[cursorY]);
		
		                    int i;
		                    for(i = cursorY; i < totalLines - 1; i++){
		                        strcpy(text[i], text[i+1]);
		                    }
		
		                    totalLines--;
		                    cursorY--;
		                    cursorX = prevLen;
		                }
		            }
		        }
		    }
		
		    isModified = 1;
	        }
	        // Enter ? pindah baris baru
	        else if(key == 13){
	            if(totalLines<MAX_ROWS-1){
	            	int i;
	                // pindahkan sisa baris ke bawah
	                for(i=totalLines;i>cursorY+1;i--){
	                    strcpy(text[i], text[i-1]);
	                }
	                text[cursorY+1][0]=0;
	                cursorY++;
	                cursorX=0;
	                totalLines++;
	            }
	            isModified = 1;
	        } else if (key == 19) {
	        	saveFile(filename);
	        	isModified = 0;
			}
	        // karakter normal
	        else{
	            int len = strlen(text[cursorY]);
	            if(len<MAX_COLS-1){
	            	int i;
	                for(i=len;i>=cursorX;i--){
	                    text[cursorY][i+1]=text[cursorY][i];
	                }
	                text[cursorY][cursorX]=key;
	                cursorX++;
	            }
	            isModified = 1;
	        }
	        // update viewTop untuk scrolling
	        if(cursorY < viewTop) viewTop = cursorY;
	        if(cursorY >= viewTop + VIEW_ROWS) viewTop = cursorY - VIEW_ROWS + 1;
	        
	        drawEditor(filename);
	        moveCursor(5+cursorX, cursorY + HEADER_LINES);
	    }
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
	
	void drawEditor(char *filename){
		int i;
	    system("cls");
	    printf("=== Editing: %s ===\n", filename);
	    printf("Save File: CTRL + S 	Exit File: Esc\n");
	    if(isModified == 1){
	    printf("Perubahan belum disimpan!\n");
		} else {
		    printf("                          \n"); // clear bar
		}
	    for(i=0;i<totalLines;i++){
		    printf("%2d | ", i+1);
		
		    int j;
		    for(j=0; j<strlen(text[i]); j++){
		
		        if(isSelecting && isSelected(j,i)){
		            setColor(31); // biru + putih (clean)
		            printf("%c", text[i][j]);
		            setColor(7);
		        } else {
		            setColor(7); // pastikan normal
		            printf("%c", text[i][j]);
		        }
		    }
		
		    printf("\n");
		}
		setColor(7);
	    printf("\nLn %d, Col %d", cursorY + 1, cursorX + 1);
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
