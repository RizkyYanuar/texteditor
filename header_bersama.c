#include "header_bersama.h"
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

int totalLines = 0;
char text[MAX_ROWS][MAX_COLS];
int cursorX = 0;
int cursorY = 0;
int viewTop = 0;
int isModified = 0;

int selStartX = 0, selStartY = 0;
int selEndX = 0, selEndY = 0;
int isSelecting = 0;


int isShiftPressed(){
    return (GetKeyState(VK_SHIFT) & 0x8000);
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
			    drawEditor(filename);  
			    moveCursor(5 + cursorX, cursorY + HEADER_LINES); // ?? WAJIB
    			continue;
			}
						
			else if(key == 24){ // Ctrl + X
			    cutSelection();
			    isSelecting = 0;
			    drawEditor(filename);  
			    moveCursor(5 + cursorX, cursorY + HEADER_LINES); // ?? WAJIB
    			continue;
			}
			
			else if(key == 16){ // Ctrl + P
			    pasteClipboard();
			    isSelecting = 0;
			    drawEditor(filename);  
			    moveCursor(5 + cursorX, cursorY + HEADER_LINES); // ?? WAJIB
    			continue;
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
			else if (key == 8) {
				backspace();
			}
	        // Enter untuk pindah baris baru
	        else if(key == 13){
	            if(totalLines<MAX_ROWS-1){
	            	int i;
	                // geser baris ke bawah
			        for(i = totalLines; i > cursorY + 1; i--){
			            strcpy(text[i], text[i-1]);
			        }
			
			        // ambil sisa teks setelah cursor
			        char temp[MAX_COLS];
			        strcpy(temp, text[cursorY] + cursorX);
			
			        // potong baris lama
			        text[cursorY][cursorX] = '\0';
			
			        // pindahkan ke baris baru
			        strcpy(text[cursorY + 1], temp);

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
	            // cek apakah panjang string di baris tersebut lebih dari samadengan maksimum kolom
	            if(len >= MAX_COLS - 1){
	            	
			    // pindah ke baris baru (seperti Enter)
			    if(totalLines < MAX_ROWS - 1){
			        int i;
			        for(i = totalLines; i > cursorY + 1; i--){
			            strcpy(text[i], text[i-1]);
			        }
			
			        text[cursorY + 1][0] = '\0';
			        cursorY++;
			        cursorX = 0;
			        totalLines++;
			    }
}
	            isModified = 1;
	            
	        }
	        if(cursorY < viewTop) viewTop = cursorY;
	        if(cursorY >= viewTop + VIEW_ROWS) viewTop = cursorY - VIEW_ROWS + 1;
	        
	        drawEditor(filename);
	        moveCursor(5+cursorX, cursorY + HEADER_LINES);
	    }
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


