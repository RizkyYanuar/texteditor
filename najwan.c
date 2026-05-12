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

