#include "najwan.h"


//void freeAll(addressBar FirstBar) {
//    while (FirstBar != Nil) {
//        addressKol Q = FirstBar->kol;
//
//        while (Q != Nil) {
//            addressKol tempK = Q;
//            Q = Q->next;
//            free(tempK);
//        }
//
//        addressBar tempB = FirstBar;
//        FirstBar = FirstBar->next;
//        free(tempB);
//    }
//}


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

    printf("\nFile berhasil disimpan!\n");
}
