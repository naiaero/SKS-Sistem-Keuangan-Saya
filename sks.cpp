#include <iostream>
#include <conio.h>
using namespace std;

int Size_Pengeluaran = 0;
int Size_Pemasukkan = 0;

string MenuA [3] = {"Riwayat Pengeluaran", "Riwayat Pemasukkan", "Riwayat Keseluruhan"};

struct Pengeluaran {
    int NominalKeluar;
    string NamaKeluar;
};

Pengeluaran* daftarPengeluaran = nullptr;

void logo () {
    cout << R"(
     _____  _  __  _____ 
    / ____|| |/ / / ____|
   | (___  | ' / | (___  
    \___ \ |  <   \___ \ 
    ____) || . \  ____) |
   |_____/ |_|\_\|_____/ 

    Sistem Keuangan Saya
)";
    for (int i = 0; i <= 28; i++) cout << "=";
    cout << endl;
}

void menu_awal () {
    int key = 0;
    int arrow = 0;    
    while (true) {
        system("cls");
        logo();  
        for (int i = 0; i < 3; i++) {
            if (i == key)
                cout << "\033[35m";
            else
                cout << "\033[0m";

            cout << MenuA[i] << endl;
        }

        cout << "\033[0m";

        arrow = getch();
        if (arrow == 72) {
            key = (key - 1 + 3) % 3;
        } else if (arrow == 80) {
            key = (key + 1) % 3;
        } else if (arrow == 13) {
            break;
        }
    }
}

void Tambah_Pengeluaran () {
    int newsize = Size_Pengeluaran + 1;
    Pengeluaran* temp = new Pengeluaran[newsize];

    for (int i = 0; i < Size_Pengeluaran; ++i) {
        temp[i] = daftarPengeluaran[i];
    }

    delete[] daftarPengeluaran;
    daftarPengeluaran = temp;
    Size_Pengeluaran = newsize;
}

int main () {
    while (true) {
        menu_awal();
    }
}