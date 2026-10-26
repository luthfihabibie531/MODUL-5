//main.cpp (UNGUIDED)
#include <iostream>
#include "Singlylist.h"

using namespace std;

int main() {
    List L;
    address P1, P2, P3, P4, P5;
    address P;

    createList(L);

    P1 = alokasi(2);
    insertFirst(L, P1);

    P2 = alokasi(0);
    insertFirst(L, P2);

    P3 = alokasi(8);
    insertFirst(L, P3);

    P4 = alokasi(12);
    insertFirst(L, P4);

    P5 = alokasi(9);
    insertFirst(L, P5);

    cout << "Isi Singly Linked List: ";
    printInfo(L);

    P = findElm(L, 8);

    if (P != Nil) {
        cout << "Elemen 8 ditemukan." << endl;
        cout << "Info elemen: " << P->info << endl;
    } else {
        cout << "Elemen 8 tidak ditemukan." << endl;
    }

    cout << "Total seluruh info: " << totalInfo(L) << endl;

    while (L.First != Nil) {
        P = L.First;
        L.First = L.First->next;
        dealokasi(P);
    }

    return 0;
}