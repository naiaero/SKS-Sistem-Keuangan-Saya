#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>
using namespace std;

int Size_Pengeluaran = 0;
int Size_Pemasukkan = 0;

string MenuUtama[3] = {"Tambah Transaksi", "Lihat Riwayat", "Keluar"};
string MenuTransaksi[3] = {"Tambah Pemasukkan", "Tambah Pengeluaran", "Kembali"};
string MenuRiwayat[4] = {"Lihat Pemasukkan", "Lihat Pengeluaran", "Lihat Semua", "Kembali"};

struct Transaksi {
    int Nominal;
    string Nama;
    string Tanggal;
    string Kategori;
};

Transaksi* daftarPemasukkan = nullptr;
Transaksi* daftarPengeluaran = nullptr;

void logo() {
    cout << R"(
     _____  _  __  _____ 
    / ____|| |/ / / ____|
   | (___  | ' / | (___  
    \___ \ |  <   \___ \ 
    ____) || . \  ____) |
   |_____/ |_|\_\|_____/ 

    Sistem Keuangan Saya
)";
    cout << string(28, '=') << endl;
}

void tekanUntukLanjut() {
    cout << "\nTekan sembarang tombol untuk melanjutkan...";
    getch();
}

int menuNavigasi(const string menu[], int size) {
    int key = 0;
    while (true) {
        system("cls");
        logo();
        
        for (int i = 0; i < size; i++) {
            if (i == key) cout << "\033[35m> ";
            else cout << "\033[0m  ";
            cout << menu[i] << "\033[0m" << endl;
        }

        int arrow = getch();
        if (arrow == 224) arrow = getch(); // Handle arrow keys
        
        if (arrow == 72 && key > 0) key--;         // Up
        else if (arrow == 80 && key < size-1) key++; // Down
        else if (arrow == 13) return key;          // Enter
    }
}

void tambahTransaksi(bool isPemasukkan) {
    system("cls");
    logo();
    cout << (isPemasukkan ? "Tambah Pemasukkan" : "Tambah Pengeluaran") << endl;
    cout << string(30, '=') << endl;

    // Membuat array baru dengan ukuran +1
    Transaksi* temp = new Transaksi[Size_Pengeluaran + 1];
    for (int i = 0; i < (isPemasukkan ? Size_Pemasukkan : Size_Pengeluaran); i++) {
        temp[i] = isPemasukkan ? daftarPemasukkan[i] : daftarPengeluaran[i];
    }

    // Input data transaksi
    cout << "Nama Transaksi: ";
    cin.ignore();
    getline(cin, temp[isPemasukkan ? Size_Pemasukkan : Size_Pengeluaran].Nama);
    
    cout << "Nominal: Rp.";
    cin >> temp[isPemasukkan ? Size_Pemasukkan : Size_Pengeluaran].Nominal;
    
    cout << "Tanggal (DD/MM/YYYY): ";
    cin >> temp[isPemasukkan ? Size_Pemasukkan : Size_Pengeluaran].Tanggal;
    
    cout << "Kategori: ";
    cin >> temp[isPemasukkan ? Size_Pemasukkan : Size_Pengeluaran].Kategori;

    // Update array
    if (isPemasukkan) {
        delete[] daftarPemasukkan;
        daftarPemasukkan = temp;
        Size_Pemasukkan++;
    } else {
        delete[] daftarPengeluaran;
        daftarPengeluaran = temp;
        Size_Pengeluaran++;
    }

    cout << "\nTransaksi berhasil ditambahkan!";
    tekanUntukLanjut();
}

void tampilkanTransaksi(bool isPemasukkan) {
    system("cls");
    logo();
    cout << (isPemasukkan ? "Riwayat Pemasukkan" : "Riwayat Pengeluaran") << endl;
    cout << string(30, '=') << endl;

    int size = isPemasukkan ? Size_Pemasukkan : Size_Pengeluaran;
    Transaksi* data = isPemasukkan ? daftarPemasukkan : daftarPengeluaran;

    if (size == 0) {
        cout << "Tidak ada data transaksi.\n";
    } else {
        // Header tabel
        cout << left << setw(4) << "No" << setw(20) << "Nama" 
             << setw(12) << "Nominal" << setw(12) << "Tanggal" 
             << setw(15) << "Kategori" << endl;
        cout << string(65, '-') << endl;

        // Data transaksi
        int total = 0;
        for (int i = 0; i < size; i++) {
            cout << left << setw(4) << i+1 
                 << setw(20) << data[i].Nama 
                 << "Rp." << setw(9) << data[i].Nominal 
                 << setw(12) << data[i].Tanggal 
                 << setw(15) << data[i].Kategori << endl;
            total += data[i].Nominal;
        }

        // Footer tabel
        cout << string(65, '-') << endl;
        cout << "Total: Rp." << total << endl;
    }

    tekanUntukLanjut();
}

void tampilkanSemua() {
    system("cls");
    logo();
    cout << "Riwayat Keuangan Lengkap" << endl;
    cout << string(30, '=') << endl;

    // Hitung total
    int totalMasuk = 0, totalKeluar = 0;
    for (int i = 0; i < Size_Pemasukkan; i++) totalMasuk += daftarPemasukkan[i].Nominal;
    for (int i = 0; i < Size_Pengeluaran; i++) totalKeluar += daftarPengeluaran[i].Nominal;

    // Tampilkan ringkasan
    cout << "Total Pemasukkan: Rp." << totalMasuk << endl;
    cout << "Total Pengeluaran: Rp." << totalKeluar << endl;
    cout << "Saldo: Rp." << (totalMasuk - totalKeluar) << endl << endl;

    // Tampilkan semua transaksi
    cout << "Detail Transaksi:\n";
    cout << string(65, '-') << endl;
    cout << left << setw(10) << "Jenis" << setw(20) << "Nama" 
         << setw(12) << "Nominal" << setw(12) << "Tanggal" 
         << setw(15) << "Kategori" << endl;
    cout << string(65, '-') << endl;

    // Pemasukkan
    for (int i = 0; i < Size_Pemasukkan; i++) {
        cout << left << setw(10) << "Pemasukkan" 
             << setw(20) << daftarPemasukkan[i].Nama 
             << "Rp." << setw(9) << daftarPemasukkan[i].Nominal 
             << setw(12) << daftarPemasukkan[i].Tanggal 
             << setw(15) << daftarPemasukkan[i].Kategori << endl;
    }

    // Pengeluaran
    for (int i = 0; i < Size_Pengeluaran; i++) {
        cout << left << setw(10) << "Pengeluaran" 
             << setw(20) << daftarPengeluaran[i].Nama 
             << "Rp." << setw(9) << daftarPengeluaran[i].Nominal 
             << setw(12) << daftarPengeluaran[i].Tanggal 
             << setw(15) << daftarPengeluaran[i].Kategori << endl;
    }

    tekanUntukLanjut();
}

void menuTransaksi() {
    while (true) {
        int pilihan = menuNavigasi(MenuTransaksi, 3);
        
        if (pilihan == 0) tambahTransaksi(true);
        else if (pilihan == 1) tambahTransaksi(false);
        else break;
    }
}

void menuRiwayat() {
    while (true) {
        int pilihan = menuNavigasi(MenuRiwayat, 4);
        
        if (pilihan == 0) tampilkanTransaksi(true);
        else if (pilihan == 1) tampilkanTransaksi(false);
        else if (pilihan == 2) tampilkanSemua();
        else break;
    }
}

int main() {
    while (true) {
        int pilihan = menuNavigasi(MenuUtama, 3);
        
        if (pilihan == 0) menuTransaksi();
        else if (pilihan == 1) menuRiwayat();
        else {
            // Bersihkan memori sebelum keluar
            if (daftarPemasukkan) delete[] daftarPemasukkan;
            if (daftarPengeluaran) delete[] daftarPengeluaran;
            break;
        }
    }
    return 0;
}
