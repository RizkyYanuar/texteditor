	#include <stdio.h>
	#include <stdlib.h>
	#include <windows.h>
	#include <string.h>
	#include <conio.h>
	#include "headerbersama.h"	
	#include "hafiez.h"
	#include "najwan.h"
	#include "rizky.h"
	
	int main() {
	    int menu;
	    char folderPath[100] = ".\\*"; // "." artinya folder saat ini
	    char fileToOpen[100];
	    int cursorX = 0;
	 	int cursorY = 0;
	 	char namaFile[100];
	
	    while(1) { // loop menu
	
	        system("cls"); // bersihkan layar setiap kali menu muncul
	
	        printf("========== MENU TEXT EDITOR ==========\n");
	        printf("1. New File\n");
	        printf("2. Open File\n");
	        printf("3. Delete File\n");
	        printf("4. Exit\n");
	        printf("Pilih menu: ");
	        scanf("%d", &menu);
	
	        switch(menu) {
	
	            case 1:
	                system("cls"); // bersihkan layar sebelum aksi
	                newFile(namaFile);
	                break;
	
	            case 2:
	                system("cls");
	                openFile(namaFile);
	                break;
	
	            case 3:
	                system("cls");
	                printf("=== DELETE FILE ===\n");
	                printf("Fungsi hapus file belum dibuat\n");
	                printf("\nTekan ENTER untuk kembali ke menu...");
	                getchar(); getchar();
	                break;
	
	            case 4:
	                printf("Keluar dari program.\n");
	                exit(0); // keluar program
	
	            default:
	                printf("Menu tidak tersedia!\n");
	                printf("\nTekan ENTER untuk kembali ke menu...");
	                getchar(); getchar();
	        }
	    }
	
	    return 0;
	}
