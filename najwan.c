#include "najwan.h"


void freeAll(addressBar FirstBar) {
    while (FirstBar != Nil) {
        addressKol Q = FirstBar->kol;

        while (Q != Nil) {
            addressKol tempK = Q;
            Q = Q->next;
            free(tempK);
        }

        addressBar tempB = FirstBar;
        FirstBar = FirstBar->next;
        free(tempB);
    }
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
