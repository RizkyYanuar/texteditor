	#include <stdio.h>
	#include <stdlib.h>
	#include <windows.h>
	#include <string.h>
	#include <conio.h>
	#include "hafiez.h"
	#include "header_bersama.h"
	#include "najwan.h"
	#include "rizky.h"
	
	
	int main() {
	    int menu;
	    WIN32_FIND_DATA findFileData;
	    HANDLE hFind;
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
	                printf("=== OPEN FILE ===\n");
	                hFind = FindFirstFile(folderPath, &findFileData);
	                if(hFind==INVALID_HANDLE_VALUE){
	                    printf("Folder kosong atau tidak ada file!\n");
	                    getchar(); getchar();
	                    break;
	                }
	
	                int i=1;
	                char files[100][100];
	                do{
	                    if(strcmp(findFileData.cFileName,".")!=0 &&
	                       strcmp(findFileData.cFileName,"..")!=0){
	                        strcpy(files[i-1], findFileData.cFileName);
	                        printf("%d. %s\n", i, findFileData.cFileName);
	                        i++;
	                    }
	                }while(FindNextFile(hFind,&findFileData)!=0);
	                FindClose(hFind);
	
	                if(i==1){
	                    printf("Tidak ada file.\n");
	                    getchar(); getchar();
	                    break;
	                }
	
	                int pilihan;
	                printf("\nPilih nomor file untuk dibuka: ");
	                scanf("%d",&pilihan);
	                getchar();
	                if(pilihan<1 || pilihan>i-1){
	                    printf("Nomor tidak valid!\n");
	                    getchar(); getchar();
	                    break;
	                }
	
	                strcpy(namaFile, files[pilihan-1]);
	                openFileToBuffer(namaFile);
	                cursorX=0; cursorY=0;
	                editFile(namaFile);
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
