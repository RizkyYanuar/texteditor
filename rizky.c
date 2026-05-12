#include "rizky.h"

void printBar(addressBar FirstBar) {
	int i = 1;
    while (FirstBar != Nil) {
        addressKol Q = FirstBar->kol;
		printf("%d| ",i);
        while (Q != Nil) {
            printf("%c", Q->info);
            Q = Q->next;
        }

//        printf("   | longBar = %d", FirstBar->longBar);
		
		if(FirstBar->tail != Nil)
        printf("   | Tail = %c", FirstBar->tail->info);
        printf("\n");
        FirstBar = FirstBar->next;
        i++;
    }
}

