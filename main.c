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
				
				    char files[100][100];
				    int jumlah = 0;
				    int pilih = 0;
				    char confirm;
				
				    jumlah = displayFiles(files);
				
				    if (jumlah == 0) {
				        printf("Tidak ada file.\n");
				        printf("Tekan ENTER untuk kembali...");
				        getchar();
				        getchar();
				        break;
				    }
				
				    printf("\nPilih nomor file yang ingin dihapus: ");
				    scanf("%d", &pilih);
				
				    getchar();
				
				    if (pilih < 1 || pilih > jumlah) {
				        printf("Pilihan tidak valid!\n");
				        printf("Tekan ENTER untuk kembali...");
				        getchar();
				        break;
				    }
				
				    printf("Yakin ingin menghapus '%s'? (y/n): ", files[pilih - 1]);
				    scanf("%c", &confirm);
				
				    if (confirm == 'y' || confirm == 'Y') {
				        deleteFile(files[pilih - 1]);
				    } else {
				        printf("Penghapusan dibatalkan.\n");
				    }
				
				    printf("\nTekan ENTER untuk kembali ke menu...");
				    getchar(); // tunggu enter
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
