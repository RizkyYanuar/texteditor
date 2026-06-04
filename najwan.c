#include "najwan.h"


void freeAll(addressBar *FirstBar) {
    addressBar tempB;
    addressKol tempK, Q;

    while (*FirstBar != Nil) {

        Q = (*FirstBar)->kol;

        while (Q != Nil) {
            tempK = Q;
            Q = Q->next;
            free(tempK);
        }

        tempB = *FirstBar;
        *FirstBar = (*FirstBar)->next;
        free(tempB);
    }

    *FirstBar = Nil;
}


void SaveFile(char *filename,addressBar FirstBar){
    FILE *fp = fopen(filename,"w");
    addressKol Kol;
   while(FirstBar != Nil){
   	Kol = FirstBar ->kol;
   		while(Kol != Nil){
   			fprintf(fp,"%c",Kol->info);
   			Kol = Kol ->next;
		   }
		   fprintf(fp,"\n");
		   FirstBar = FirstBar->next;
   }

    fclose(fp);

    printf("\n\n\nFile berhasil disimpan!\n");
}

FILE *BukaFile(char *filename){
	FILE *file;
	file = fopen(filename,"r");
	if(file==Nil){
		printf("File belum ada\n");
	}
	return file;
}

void OpenFileToLinkedList(
    FILE *file,
    addressBar *FirstBar,
    addressBar *CurrentBar,
    addressKol *Cursor,
    int *CursorX,
    int *CursorY
){
    char c;

    while((c = fgetc(file)) != EOF){

        if(c == '\n'){

            BarisBaru(
                CurrentBar,
                FirstBar,
                Cursor,
                CursorX,
                CursorY
            );
        }

        else{

            InsertKarakter(
                c,
                FirstBar,
                CurrentBar,
                Cursor,
                CursorX,
                *CursorY
            );
        }
    }
    *CursorY = PCY(*CursorY,-2);
    *Cursor = *FirstBar;
}
	
void TampilIsiFile(FILE *file){
	char buffer[256];
	while(fgets(buffer,sizeof(buffer),file)!=Nil){
		printf("%s",buffer);
		}	
	}
	

void HapusFile(char *filename, addressBar *FirstBar){

    FILE *file = BukaFile(filename);

    if(file == NULL){
        printf("File tidak ditemukan!\n");
        return;
    }

	
    if(*FirstBar != Nil){
        freeAll(FirstBar);
    }
 	fclose(file);
 	
    if(remove(filename) == 0){
        printf("File berhasil dihapus!\n");
    }
    else{
        printf("File gagal dihapus!\n");
    }
    getch();
}
