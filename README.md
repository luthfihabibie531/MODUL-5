# <h1 align="center">Laporan Praktikum Modul 5 - Singly Linked List (Bagian Kedua)</h1>
<p align="center">AHMAD LUTHFI HABIBIE - 109082500190</p>

## Dasar Teori

### A. Searching pada Singly Linked List<br/>
*Searching* adalah operasi dasar pada list yang dipakai untuk mencari *node* tertentu. Prosesnya dilakukan dengan mengunjungi setiap *node* dari awal list dan berhenti begitu *node* yang dicari ketemu [1]. Karena singly linked list hanya punya satu arah pointer, pencarian tidak bisa langsung loncat ke tengah seperti pada *array*, jadi penelusuran selalu dimulai dari `first` lalu bergerak lewat `next` sampai ketemu atau sampai pointer bernilai `Nil` [1][4]. Pencarian seperti ini disebut pencarian sekuensial. Manfaat utama dari operasi *searching* adalah mempermudah operasi lain seperti *insert after*, *delete after*, dan *update*, sebab ketiga operasi tersebut membutuhkan alamat *node* acuan yang harus ditemukan lebih dulu [1].

#### 1. Primitif Pencarian pada ADT
Pada modul, ADT list dilengkapi beberapa primitif pencarian. `findElm(L, X)` mencari elemen yang `info`-nya sama dengan `X`, lalu mengembalikan alamat elemen tersebut atau `Nil` jika tidak ada. `fFindElm(L, P)` mencari apakah ada elemen dengan alamat `P` dan mengembalikan `true` atau `false`. Sementara `findBefore(L, P)` mengembalikan alamat elemen sebelum `P`, dan bernilai `Nil` kalau `P` berada di awal list [1]. Pada praktikum bagian guided, pencarian dikembangkan menjadi tiga cara, yaitu berdasarkan data (nama), berdasarkan alamat *node*, dan berdasarkan rentang nilai (range harga).

#### 2. Operasi Update
*Update* adalah operasi mengubah isi data pada *node* yang sudah ada tanpa mengubah susunan pointer-nya. Sama seperti *insert* dan *delete*, update bisa dilakukan pada *node* pertama, *node* terakhir, atau *node* setelah *node* tertentu. Karena yang diubah hanya isi `isidata` (bukan sambungan `next`), list tidak perlu dibongkar ulang. Itu sebabnya fungsi update boleh menerima `List` secara *pass by value*, sebab yang disalin hanya pointer `first`, sedangkan *node*-nya tetap sama di memori.

### B. Primitif ADT Singly Linked List Lainnya<br/>
Selain pencarian, modul 5 juga memuat daftar primitif lengkap pada `list.h`, mulai dari `ListEmpty`, `CreateList`, dan `dealokasi`, operasi penambahan (`insertFirst`, `insertAfter`, `insertLast`), operasi penghapusan (`delFirst`, `delLast`, `delAfter`, `delP`), hingga proses terhadap seluruh elemen seperti `printInfo`, `nbList`, `delAll`, `invertList`, `copyList`, dan `fCopyList` [1]. `printInfo` menampilkan semua `info` pada list, `nbList` mengembalikan jumlah elemen, `delAll` menghapus dan mendealokasi semua elemen, dan `invertList` membalik urutan elemen. Semua primitif ini disimpan dalam file `*.h` untuk deklarasi dan file `*.cpp` untuk realisasinya, sehingga file lain cukup meng-*include* header untuk memakainya [1].

#### 1. Alokasi Memori Dinamis
Linked list memakai alokasi memori dinamis, artinya memori untuk sebuah elemen baru baru diminta ke sistem ketika elemen itu dibutuhkan [3]. Di C++ hal ini dilakukan dengan `new` dan dikembalikan dengan `delete`. Pada ADT, keduanya dibungkus dalam primitif `alokasi` dan `dealokasi`. Pengelolaan yang rapi penting supaya tidak terjadi kebocoran memori, terutama saat list dihapus seluruhnya [1].

### C. Perbandingan dengan Struktur Lain<br/>
Dibandingkan *array*, linked list lebih enak untuk menyisipkan atau menghapus elemen di tengah karena cukup mengubah pointer tanpa menggeser elemen lain, tetapi harga yang dibayar adalah pencarian yang harus dilakukan satu per satu [1]. Doubly Linked List punya pointer ke *node* sebelumnya dan sesudahnya sehingga bisa ditelusuri dua arah [2], sedangkan singly linked list hanya bisa maju satu arah dan karena itu butuh primitif tambahan seperti `findBefore` untuk mengetahui elemen sebelum suatu *node*.

## Guided 

### 1. listBuah.h

```C++
//listBuah.h (GUIDED)
//Header guard digunakan untuk mencegah file header yang sama 
//di-include lebih dari sekali dalam satu program.
#ifndef LISTBUAH_H
#define LISTBUAH_H
#define Nil NULL

#include<iostream>
using namespace std;

struct buah{
    string nama;
    int jumlah; 
    float harga;
};

typedef buah dataBuah; //Memberikan nama alias databuah untuk struct buah.

typedef struct node *address; //Mendefinisikan alias address sebagai pointer ke struct node

struct node{ // node untuk isi dari linked listnya, isi setiap node adalah data & pointer next
    dataBuah isidata;
    address next;
};

struct linkedlist{ //ini linked list nya
    address first;
};

//semua function & prosedur yang akan dipakai
//Materi modul 4
bool isEmpty(linkedlist List);
void createList(linkedlist &List);
address alokasi(string nama, int jumlah, float harga);
void dealokasi(address &node);
void printList(linkedlist List);
void insertFirst(linkedlist &List, address nodeBaru);
void insertAfter(linkedlist &List, address nodeBaru, address Prev);
void insertLast(linkedlist &List, address nodeBaru);
void delFirst(linkedlist &List);
void delLast(linkedlist &List);
void delAfter(linkedlist &List, address nodeHapus, address nodePrev);
int nbList(linkedlist List);
void deleteList(linkedlist &List);

//materi modul 5 (update)
void updateFirst(linkedlist List);
void updateLast(linkedlist List);
void updateAfter(linkedlist List, address prev);

//materi modul 5 (searching)
void FindNodeByData(linkedlist list, string data);
void FindNodeByAddress(linkedlist list, address node);
void FindNodeByRange(linkedlist list, float hargaAwal, float HargaAkhir);

#endif
```
File `listBuah.h` berisi spesifikasi tipe data dan prototipe semua primitif untuk list yang menyimpan data buah. Struct `buah` menyimpan `nama`, `jumlah`, dan `harga`, lalu diberi alias `dataBuah` agar dipakai sebagai isi tiap *node*. `address` didefinisikan sebagai pointer ke `struct node`, dan `struct node` sendiri berisi `isidata` serta pointer `next` ke *node* berikutnya. `struct linkedlist` hanya punya satu field yaitu `first` yang menunjuk *node* paling depan. Bagian prototipe dibagi dua sesuai materi. Primitif dasar dari modul sebelumnya (`isEmpty`, `createList`, `alokasi`, `dealokasi`, `insert`, `delete`, `printList`, `nbList`, `deleteList`) tetap dipertahankan, lalu ditambah materi modul 5 yaitu tiga prosedur update (`updateFirst`, `updateLast`, `updateAfter`) dan tiga prosedur pencarian (`FindNodeByData`, `FindNodeByAddress`, `FindNodeByRange`). Baris `#ifndef`, `#define`, dan `#endif` dipakai sebagai *header guard* supaya file ini tidak ter-*include* dua kali.

### 2. listBuah.cpp

```C++
//listBuah.cpp (GUIDED)
#include "listBuah.h"
#include <iostream>
using namespace std;

//fungsi untuk cek apakah list kosong atau tidak
bool isEmpty(linkedlist List) {
    if(List.first == Nil){
        return true; 
    } else {
        return false;
    }
}

//pembuatan linked list kosong
void createList(linkedlist &List) {
    List.first = Nil;
}

//pembuatan node baru dengan menerapkan manajemen memori
address alokasi(string nama, int jumlah, float harga) { 
    address nodeBaru = new node; 
    nodeBaru->isidata.nama = nama;
    nodeBaru->isidata.jumlah = jumlah; 
    nodeBaru->isidata.harga = harga;
    nodeBaru->next = Nil;
    return nodeBaru;
}

//penghapusan node dengan menerapkan manajemen memori
void dealokasi(address &node) {
    node->next = Nil;
    delete node;
}

//prosedur-prosedur untuk insert / menambahkan node baru kedalam list
void insertFirst(linkedlist &List, address nodeBaru) {
    nodeBaru->next = List.first; 
    List.first = nodeBaru;
}

void insertAfter(linkedlist &List, address nodeBaru, address Prev) {
    if (Prev != Nil) {
        nodeBaru->next = Prev->next;
        Prev->next = nodeBaru;
    } else {
        cout << "Node sebelumnya tidak valid!" << endl;
    }
}

void insertLast(linkedlist &List, address nodeBaru) {
    if (isEmpty(List)) {
        List.first = nodeBaru;
    } else {
        address nodeBantu = List.first;
        while (nodeBantu->next != Nil) {
            nodeBantu = nodeBantu->next;
        }
        nodeBantu->next = nodeBaru;
    }
}

//prosedur-prosedur untuk delete / menghapus node yang ada didalam list
void delFirst(linkedlist &List){
    address nodeHapus;
    if (isEmpty(List) == false) {
        nodeHapus = List.first;
        List.first = List.first->next;
        nodeHapus->next = Nil;
        dealokasi(nodeHapus);
        cout << "Node pertama berhasil terhapus!" << endl;
    } else {
        cout << "List kosong!" << endl;
    }
}

void delLast(linkedlist &List){
    address nodeHapus, nodePrev;
    if(isEmpty(List) == false){
        nodeHapus = List.first;
        if(nodeHapus->next == Nil){
            List.first->next = Nil;
            dealokasi(nodeHapus);
        } else { 
            while(nodeHapus->next != Nil){
                nodePrev = nodeHapus; 
                nodeHapus = nodeHapus->next;
            }
            nodePrev->next = Nil; 
            dealokasi(nodeHapus);
        }
        cout << "Node terakhir berhasil terhapus!" << endl;
    } else {
        cout << "list kosong" << endl;
    }
}

void delAfter(linkedlist &List, address nodeHapus, address nodePrev){
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else { //jika list tidak kosong
        if (nodePrev != Nil && nodePrev->next != Nil) { 
            nodeHapus = nodePrev->next;       
            nodePrev->next = nodeHapus->next;  
            nodeHapus->next = Nil;         
            dealokasi(nodeHapus);
            cout << "Node setelah node " << nodePrev->isidata.nama << " berhasil terhapus!" << endl;
        } else {
            cout << "Node sebelumnya (prev) tidak valid!" << endl;
        }
    }
}

//prosedur untuk menampilkan isi list
void printList(linkedlist List) {
    if (isEmpty(List)) {
        cout << "List kosong." << endl;
    } else {
        address nodeBantu = List.first;
        while (nodeBantu != Nil) { 
            cout << "Nama Buah : " << nodeBantu->isidata.nama << ", Jumlah : " << nodeBantu->isidata.jumlah << ", Harga : " << nodeBantu->isidata.harga << endl;
            nodeBantu = nodeBantu->next;
        }
    }
}

//function untuk menampilkan jumlah node didalam list
int nbList(linkedlist List) {
    int count = 0;
    address nodeBantu = List.first;
    while (nodeBantu != Nil) {
        count++;
        nodeBantu = nodeBantu->next; 
    }
    return count;
}

//prosedur untuk menghapus list (menghapus semua node didalam list)
void deleteList(linkedlist &List){
    address nodeBantu, nodeHapus;
    nodeBantu = List.first;
    while(nodeBantu != Nil){
        nodeHapus = nodeBantu;
        nodeBantu = nodeBantu->next;
        dealokasi(nodeHapus); 
    }
    List.first = Nil; 
    cout << "List berhasil terhapus!" << endl;
}

/*----- MATERI PERTEMUAN 5 - SINGLY LINKED LIST (BAGIAN KEDUA) - UPDATE -----*/
//prosedur-prosedur untuk melakukan update data node
void updateFirst(linkedlist List){
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else {
        cout << "Masukkan update data node pertama : " << endl;
        cout << "Nama buah : ";
        cin >> List.first->isidata.nama;
        cout << "Jumlah : ";
        cin >> List.first->isidata.jumlah;
        cout << "Harga : ";
        cin >> List.first->isidata.harga;
        cout << "Data Berhasil Diupdate!" << endl;
        cout << endl;
    }
}

void updateLast(linkedlist List){
    if (isEmpty(List) == true) {
        cout << "List Kosong!" << endl;
    } else {
        address nodeBantu = List.first;
        while (nodeBantu->next != Nil) {
            nodeBantu = nodeBantu->next;
        }
        cout << "masukkan update data node terakhir : " << endl;
        cout << "Nama buah : ";
        cin >> nodeBantu->isidata.nama;
        cout << "Jumlah : ";
        cin >> nodeBantu->isidata.jumlah;
        cout << "Harga : ";
        cin >> nodeBantu->isidata.harga;
        cout << "Data Berhasil Diupdate!" << endl;
        cout << endl;
    }
}

void updateAfter(linkedlist List, address nodePrev){
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else {
        if (nodePrev != Nil && nodePrev->next != Nil){
            address nodeBantu = nodePrev->next;
            cout << "masukkan update data node setelah node " << nodePrev->isidata.nama << " : " << endl;
            cout << "Nama buah : ";
            cin >> nodeBantu->isidata.nama;
            cout << "Jumlah : ";
            cin >> nodeBantu->isidata.jumlah;
            cout << "Harga : ";
            cin >> nodeBantu->isidata.harga;
            cout << "Data Berhasil Diupdate!" << endl;
            cout << endl;
        } else {
            cout << "Node sebelumnya (prev) tidak valid!" << endl;
        }
    }
}

/*----- MATERI PERTEMUAN 5 - SINGLY LINKED LIST (BAGIAN KEDUA) - SEARCHING -----*/
//prosedur-prosedur untuk searching data
//prosedur untuk mencari node berdasarkan data
void FindNodeByData(linkedlist list, string data){
    if(isEmpty(list) == true){
        cout << "List kosong!" << endl;
    } else {
        address nodeBantu = list.first;
        int posisi = 0;
        bool found = false;
        while(nodeBantu != Nil){
            posisi++;
            if(nodeBantu->isidata.nama == data){
                cout << "Data " << data << " ditemukan pada posisi ke-" << posisi << "!" << endl;
                cout << "Nama Buah : " << nodeBantu->isidata.nama << ", Jumlah : " << nodeBantu->isidata.jumlah << ", Harga : " << nodeBantu->isidata.harga << endl;
                found = true;
                break;
            }
            nodeBantu = nodeBantu->next;
        }
        if(found == false){
            cout << "Node dengan data " << data << " tidak ditemukan!" << endl;
        }
    }
    cout << endl;
}

//prosedur untuk mencari node berdasarkan alamat node
void FindNodeByAddress(linkedlist list, address node) {
    if(isEmpty(list) == true) {
        cout << "List kosong!" << endl;
    } else {
        address nodeBantu = list.first;
        int posisi = 0;
        bool found = false;
        while (nodeBantu != Nil) {
            posisi++;
            if(nodeBantu == node) {
                cout << "Node ditemukan pada posisi ke-" << posisi << "!" << endl;
                cout << "Alamat node : " << nodeBantu << endl;
                cout << "Nama Buah : " << nodeBantu->isidata.nama << ", Jumlah : " << nodeBantu->isidata.jumlah << ", Harga : " << nodeBantu->isidata.harga << endl;
                found = true;
                break;
            }
            nodeBantu = nodeBantu->next;
        }
        if(found == false) {
            cout << "Node dengan alamat " << node << " tidak ditemukan dalam list!" << endl;
        }
    }
    cout << endl;
}

//prosedur untuk mencari node berdasarkan range data (range harga)
void FindNodeByRange(linkedlist list, float hargaAwal, float hargaAkhir) {
    if(isEmpty(list) == true) {
        cout << "List kosong!" << endl;
    } else {
        address nodeBantu = list.first;
        int posisi = 0;
        bool found = false;
        cout << "--- Buah dalam range harga " << hargaAwal << " - " << hargaAkhir << " ---" << endl;
        cout << "-------------------------------------------" << endl;
        while (nodeBantu != Nil) {
            posisi++;
            float harga = nodeBantu->isidata.harga;
            if(harga >= hargaAwal && harga <= hargaAkhir) {
                cout << "Data ditemukan pada posisi ke-" << posisi << " :" << endl;
                cout << "Nama Buah : " << nodeBantu->isidata.nama << ", Jumlah : " << nodeBantu->isidata.jumlah << ", Harga : " << nodeBantu->isidata.harga << endl;
                cout << "-------------------------------------------" << endl;
                found = true;
            }
            nodeBantu = nodeBantu->next;
        }
        if(found == false) {
            cout << "Tidak ada data buah dalam range harga tersebut!" << endl;
            cout << "-------------------------------------------" << endl;
        }
    }
    cout << endl;
}
```
File `listBuah.cpp` berisi realisasi semua primitif yang sudah dideklarasikan di header. Bagian awalnya masih sama dengan modul sebelumnya. `isEmpty` mengecek apakah `first` bernilai `Nil`, `createList` mengisi `first` dengan `Nil`, dan `alokasi` membuat *node* baru dengan `new`, mengisi nama, jumlah, dan harga, lalu mengatur `next` ke `Nil`. `dealokasi` mengembalikan memori dengan `delete`. Untuk operasi sisip, `insertFirst` mengarahkan `next` *node* baru ke `first` lama lalu memindahkan `first` ke *node* baru, `insertAfter` menyambungkan *node* baru ke `Prev->next` lebih dulu baru kemudian `Prev->next` diarahkan ke *node* baru, dan `insertLast` menelusuri list sampai *node* yang `next`-nya `Nil` lalu menempelkan *node* baru di situ. Untuk operasi hapus, `delFirst` menggeser `first` ke *node* kedua lalu mendealokasi *node* lama, `delLast` menelusuri list dengan `nodePrev` yang selalu satu langkah di belakang `nodeHapus` kemudian memutus `nodePrev->next`, dan `delAfter` memutus *node* setelah `nodePrev` dengan `nodePrev->next = nodeHapus->next`. `printList` dan `nbList` sama-sama menelusuri list, yang satu mencetak isi tiap *node* dan yang satu menghitung jumlahnya, sedangkan `deleteList` mendealokasi semua *node* satu per satu lalu mengembalikan `first` ke `Nil`.

Bagian baru dari modul 5 ada di tiga prosedur update dan tiga prosedur searching. `updateFirst` langsung mengisi ulang data pada `List.first` memakai `cin`, `updateLast` menelusuri list dulu sampai *node* terakhir baru mengisi ulang datanya, dan `updateAfter` mengubah data pada *node* yang berada tepat setelah `nodePrev`. Walaupun parameter `List` dikirim sebagai salinan, perubahan tetap tersimpan karena yang disalin hanya pointer `first`, sementara *node*-nya sendiri tetap di memori yang sama. Pada pencarian, `FindNodeByData` menelusuri list sambil menghitung `posisi` dan membandingkan nama tiap *node* dengan data yang dicari, lalu berhenti dengan `break` begitu ketemu. `FindNodeByAddress` caranya sama tetapi yang dibandingkan adalah alamat *node* (`nodeBantu == node`), sehingga selain posisi, alamat memorinya juga ikut dicetak. `FindNodeByRange` berbeda sedikit karena tidak berhenti di temuan pertama; ia terus menelusuri sampai akhir list dan mencetak semua *node* yang harganya berada di antara `hargaAwal` dan `hargaAkhir`. Ketiganya memakai variabel `found` sebagai penanda, sehingga kalau sampai akhir tidak ada yang cocok, akan tercetak pesan bahwa data tidak ditemukan.

### 3. main.cpp

```C++
//main.cpp (GUIDED)
#include "listBuah.h"

#include<iostream>
using namespace std;

int main(){
    linkedlist List;
    address nodeA, nodeB, nodeC, nodeD, nodeE = Nil;
    createList(List);

    dataBuah dtBuah;

    nodeA = alokasi("Jeruk", 100, 3000);
    nodeB = alokasi("Apel", 75, 4000);
    nodeC = alokasi("Pir", 87, 5000);
    nodeD = alokasi("Semangka", 43, 11500);
    nodeE = alokasi("Durian", 15, 31450);

    insertFirst(List, nodeA);
    insertLast(List, nodeB);
    insertAfter(List, nodeC, nodeA);
    insertAfter(List, nodeD, nodeC);
    insertLast(List, nodeE);

    cout << "--- ISI LIST SETELAH DILAKUKAN INSERT ---" << endl;
    printList(List);
    cout << "jumlah node : " << nbList(List) << endl;
    cout << endl;

    updateFirst(List);
    printList(List);
    updateLast(List);
    printList(List);
    updateAfter(List, nodeD);
    printList(List);

    cout << "--- ISI LIST SETELAH DILAKUKAN UPDATE ---" << endl;
    printList(List);
    cout << "jumlah node : " << nbList(List) << endl;
    cout << endl;

    FindNodeByData(List, "kelapa");
    FindNodeByAddress(List, nodeC);
    FindNodeByRange(List, 5000, 10000);

    delFirst(List);
    printList(List);
    delLast(List);
    printList(List);
    delAfter(List, nodeD, nodeC);
    printList(List);

    cout << "--- ISI LIST SETELAH DILAKUKAN DELETE ---" << endl;
    printList(List);
    cout << "jumlah node : " << nbList(List) << endl;
    cout << endl;

    deleteList(List);
    cout << "--- ISI LIST SETELAH DILAKUKAN HAPUS LIST ---" << endl;
    printList(List);
    cout << "jumlah node : " << nbList(List) << endl;
    cout << endl;

    return 0;
} 
```
File `main.cpp` berperan sebagai *driver* untuk mencoba semua primitif. Pertama list dibuat kosong, lalu lima *node* buah dialokasikan, yaitu Jeruk (`nodeA`), Apel (`nodeB`), Pir (`nodeC`), Semangka (`nodeD`), dan Durian (`nodeE`). Proses *insert* berjalan berurutan: `insertFirst(nodeA)` menghasilkan `[A]`, `insertLast(nodeB)` menghasilkan `[A, B]`, `insertAfter(nodeC, nodeA)` menyisipkan Pir setelah Jeruk sehingga menjadi `[A, C, B]`, `insertAfter(nodeD, nodeC)` menghasilkan `[A, C, D, B]`, dan `insertLast(nodeE)` menghasilkan `[A, C, D, B, E]`, jadi list berisi Jeruk, Pir, Semangka, Apel, dan Durian dengan jumlah *node* 5.

Setelah itu dilakukan tiga kali update. `updateFirst` mengubah data *node* pertama (Jeruk), `updateLast` mengubah data *node* terakhir (Durian), dan `updateAfter(List, nodeD)` mengubah data *node* setelah Semangka, yaitu Apel. Data barunya diketik langsung lewat keyboard saat program berjalan, dan `printList` dipanggil tiap selesai update untuk memperlihatkan perubahannya. Tahap pencarian dimulai dengan `FindNodeByData(List, "kelapa")`; karena tidak ada buah bernama kelapa pada data awal, hasilnya pesan bahwa data tidak ditemukan (kecuali kalau saat update kita mengetik nama tersebut). `FindNodeByAddress(List, nodeC)` menemukan Pir pada posisi ke-2 karena alamatnya memang berada di urutan kedua, dan `FindNodeByRange(List, 5000, 10000)` menampilkan semua buah yang harganya ada di rentang 5000 sampai 10000, yang hasilnya bergantung pada harga yang dimasukkan ketika update.

Pada tahap *delete*, `delFirst` menghapus *node* pertama sehingga list menjadi `[C, D, B, E]`, `delLast` menghapus *node* terakhir sehingga menjadi `[C, D, B]`, lalu `delAfter(List, nodeD, nodeC)` menghapus *node* setelah Pir yaitu Semangka, sehingga tersisa `[C, B]` dengan jumlah *node* 2. Terakhir `deleteList` membebaskan semua *node* dan setelahnya `printList` menampilkan "List kosong." dengan jumlah *node* 0.

## Unguided 

### 1. ADT Singly Linked List pada "Singlylist.h", implementasi pada "Singlylist.cpp", dan percobaan pada "main.cpp" (data 9, 12, 8, 0, 2) beserta pencarian elemen 8 dan penjumlahan seluruh info

**Singlylist.h**
```C++
//Singlylist.h (UNGUIDED)
#ifndef SINGLYLIST_H
#define SINGLYLIST_H

#define Nil NULL

typedef int infotype;
typedef struct ElmList *address;

struct ElmList {
    infotype info;
    address next;
};

struct List {
    address First;
};

void createList(List &L);
address alokasi(infotype x);
void dealokasi(address &P);
void printInfo(List L);
void insertFirst(List &L, address P);
address findElm(List L, infotype x);
int totalInfo(List L);

#endif
```

**Singlylist.cpp**
```C++
//Singlylist.cpp (UNGUIDED)
#include <iostream>
#include "Singlylist.h"

using namespace std;

void createList(List &L) {
    L.First = Nil;
}

address alokasi(infotype x) {
    address P = new ElmList;

    if (P != Nil) {
        P->info = x;
        P->next = Nil;
    }

    return P;
}

void dealokasi(address &P) {
    if (P != Nil) {
        delete P;
        P = Nil;
    }
}

void printInfo(List L) {
    address P = L.First;

    while (P != Nil) {
        cout << P->info;

        if (P->next != Nil) {
            cout << " ";
        }

        P = P->next;
    }

    cout << endl;
}

void insertFirst(List &L, address P) {
    if (P != Nil) {
        P->next = L.First;
        L.First = P;
    }
}

address findElm(List L, infotype x) {
    address P = L.First;

    while (P != Nil) {
        if (P->info == x) {
            return P;
        }

        P = P->next;
    }

    return Nil;
}

int totalInfo(List L) {
    address P = L.First;
    int total = 0;

    while (P != Nil) {
        total += P->info;
        P = P->next;
    }

    return total;
}
```

**main.cpp**
```C++
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
```
### Output Unguided 1 :

##### Output 1
![Screenshot Output Unguided 1_1](Soal_1(unguided).png)

Program ini mengerjakan tiga soal latihan modul 5 sekaligus dengan satu ADT Singly Linked List bertipe `int`. Pada `Singlylist.h`, `infotype` didefinisikan sebagai `int`, `address` sebagai pointer ke `ElmList`, `struct ElmList` berisi `info` dan `next`, serta `struct List` berisi `First`. Prototipe yang dideklarasikan adalah lima primitif dari soal (`createList`, `alokasi`, `dealokasi`, `printInfo`, `insertFirst`) ditambah dua fungsi baru, yaitu `findElm` untuk pencarian dan `totalInfo` untuk menjumlahkan seluruh info.

Di `Singlylist.cpp`, `createList` mengisi `First` dengan `Nil`, lalu `alokasi` membuat elemen baru dengan `new` dan mengisi `info` serta `next`. `dealokasi` membebaskan memori elemen dengan `delete` dan mengembalikan pointer ke `Nil`. `insertFirst` menyisipkan elemen di depan list dengan `P->next = L.First` lalu `L.First = P`, sedangkan `printInfo` menelusuri list dari `First` dan mencetak `info` tiap elemen dengan spasi sebagai pemisah. Fungsi `findElm` sesuai dengan primitif pencarian pada modul [1]: pointer `P` mulai dari `First`, lalu digeser lewat `next` sambil membandingkan `P->info` dengan nilai `x`. Begitu cocok, alamat elemen langsung dikembalikan, dan kalau sampai `Nil` belum ketemu maka yang dikembalikan adalah `Nil`. `totalInfo` menelusuri list dengan cara yang sama dan menambahkan `P->info` ke variabel `total` di setiap langkah.

Pada `main.cpp`, nilai 2, 0, 8, 12, dan 9 dialokasikan lalu dimasukkan satu per satu dengan `insertFirst`. Karena tiap elemen baru selalu ditaruh di depan, elemen yang dimasukkan paling akhir menjadi elemen pertama, sehingga urutan list menjadi 9, 12, 8, 0, 2 seperti pada gambar ilustrasi soal. Setelah `printInfo`, program memanggil `findElm(L, 8)` dan memeriksa hasilnya: kalau tidak `Nil`, dicetak bahwa elemen 8 ditemukan beserta `info`-nya. Terakhir `totalInfo` dipanggil untuk menampilkan jumlah seluruh info, yaitu 9 + 12 + 8 + 0 + 2 = 31. Di akhir program, seluruh elemen dihapus dengan perulangan `while` yang menggeser `First` lalu memanggil `dealokasi`, supaya tidak ada memori yang tertinggal.

Pada screenshot, program dikompilasi di terminal VS Code (PowerShell) dari folder `soal_1` dengan perintah `g++ .\Singlylist.cpp .\main.cpp -o Singlylist.exe`, lalu dijalankan dengan `.\Singlylist.exe`. Kompilasi berjalan tanpa pesan *error*. Output yang muncul adalah `Isi Singly Linked List: 9 12 8 0 2`, `Elemen 8 ditemukan.`, `Info elemen: 8`, dan `Total seluruh info: 31`. Baris pertama menunjukkan urutan list hasil `insertFirst`, dua baris berikutnya menunjukkan bahwa `findElm` berhasil mengembalikan alamat elemen yang berisi 8, dan baris terakhir menunjukkan hasil penjumlahan 31 yang sama dengan perhitungan manual pada soal. Teks keluarannya sedikit berbeda dari contoh gambar di modul, tetapi isi hasilnya sama.

## Kesimpulan
Dari praktikum Modul 5 dapat disimpulkan bahwa *searching* pada singly linked list dilakukan dengan menelusuri *node* satu per satu dari `first` sampai data yang dicari ketemu atau sampai `Nil`, dan hasil pencarian ini menjadi dasar bagi operasi lain seperti *insert after*, *delete after*, dan *update* karena operasi-operasi tersebut membutuhkan alamat *node* acuan. Pada bagian guided, pencarian diterapkan dalam tiga bentuk, yaitu berdasarkan data, berdasarkan alamat, dan berdasarkan rentang harga, sedangkan operasi update memungkinkan data pada *node* pertama, terakhir, maupun setelah *node* tertentu diubah tanpa mengubah susunan pointer. Pada bagian unguided, ADT Singly Linked List dengan data bertipe `int` berhasil dibuat lengkap dengan fungsi `findElm` untuk mencari elemen bernilai 8 dan fungsi `totalInfo` untuk menjumlahkan seluruh info, dengan hasil list 9, 12, 8, 0, 2, elemen 8 ditemukan, dan total info 31 sesuai dengan yang diminta soal.

## Referensi
[1] Laboratorium Informatika, Fakultas Informatika, Telkom University. (t.t.). "Modul 5: Singly Linked List (Bagian Kedua)", Modul Praktikum Struktur Data. Bandung: Telkom University.
<br>[2] Wijoyo, A., Prayudi, L. A., Fiqih, M., Santoso, R. D., Putra, R. T. S., Arifin, T., & Farhan, A. "Penggunaan Algoritma Doubly Linked List Untuk Insertion Dan Deletion". JRIIN: Jurnal Riset Informatika dan Inovasi, 1(12), 1329–1331. Universitas Pamulang. Diakses melalui https://jurnalmahasiswa.com/index.php/jriin/article/view/1282.
<br>[3] Shaffer, C. A. "Data Structures and Algorithm Analysis" (Bab 4: Lists, Stacks, and Queues). Virginia Tech. Diakses melalui https://learn.saylor.org/pluginfile.php/591887/mod_resource/content/1/Shaffer-103-120.pdf.
<br>[4] Universitas Esa Unggul. "Struktur Data Pertemuan 4: Konsep Pointer dan Linked List". Diakses melalui https://bahan-ajar.esaunggul.ac.id/ccs120/wp-content/uploads/sites/1532/2019/12/Struktur-Data-Pertemuan-4.pdf.