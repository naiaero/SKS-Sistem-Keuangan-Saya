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

void clearScreen() {
    system("cls");
}

void displayHorizontalLine(int width = 50) {
    cout << string(20, ' ') << '+' << string(width - 2, '-') << '+' << endl;
}

void logo() {
    clearScreen();
    displayHorizontalLine();
    cout << string(20, ' ') << "|" << string(48, ' ') << "|" << endl;
    cout << R"( 
     _____  _  __  _____ 
    / ____|| |/ / / ____|
   | (___  | ' / | (___  
    \___ \ |  <   \___ \ 
    ____) || . \  ____) |
   |_____/ |_|\_\|_____/ 

    Sistem Keuangan Saya
)" << endl;
    displayHorizontalLine();
    cout << endl;
}

void pressToContinue() {
    cout << string(20, ' ') << "Tekan sembarang tombol untuk melanjutkan...";
    getch();
}

int calculateMenuWidth(const string menu[], int size) {
    int maxWidth = 0;
    for (int i = 0; i < size; i++) {
        if (menu[i].length() > maxWidth)
            maxWidth = menu[i].length();
    }
    return maxWidth + 6; // Additional space for borders and padding
}

void displayMenuTopBorder(int width) {
    cout << string(20, ' ') << '+' << string(width - 2, '-') << '+' << endl;
}

void displayMenuBottomBorder(int width) {
    cout << string(20, ' ') << '+' << string(width - 2, '-') << '+' << endl;
}

void displayMenuItem(const string& item, bool isSelected, int width) {
    cout << string(20, ' ') << "| ";
    if (isSelected) 
        cout << "\033[35m> " << left << setw(width - 6) << item << "\033[0m";
    else 
        cout << "  " << left << setw(width - 6) << item;
    cout << " |" << endl;
}

int navigateMenu(const string menu[], int size) {
    int key = 0;
    int menuWidth = calculateMenuWidth(menu, size);
    
    while (true) {
        logo();
        displayMenuTopBorder(menuWidth);
        
        for (int i = 0; i < size; i++) {
            displayMenuItem(menu[i], (i == key), menuWidth);
        }
        
        displayMenuBottomBorder(menuWidth);

        int arrow = getch();
        if (arrow == 224) arrow = getch(); // Handle arrow keys
        
        if (arrow == 72 && key > 0) key--;         // Up
        else if (arrow == 80 && key < size-1) key++; // Down
        else if (arrow == 13) return key;          // Enter
    }
}

void addTransaction(bool isIncome) {
    clearScreen();
    logo();
    cout << string(20, ' ') << "+--------------------------------------+" << endl;
    cout << string(20, ' ') << "|" << (isIncome ? "       TAMBAH PEMASUKKAN       " : "      TAMBAH PENGELUARAN      ") << "|" << endl;
    cout << string(20, ' ') << "+--------------------------------------+" << endl << endl;

    Transaksi* temp = new Transaksi[(isIncome ? Size_Pemasukkan : Size_Pengeluaran) + 1];
    int currentSize = isIncome ? Size_Pemasukkan : Size_Pengeluaran;
    
    for (int i = 0; i < currentSize; i++) {
        temp[i] = isIncome ? daftarPemasukkan[i] : daftarPengeluaran[i];
    }

    cout << string(20, ' ') << "| Nama Transaksi  : ";
    cin.ignore();
    getline(cin, temp[currentSize].Nama);
    
    cout << string(20, ' ') << "| Nominal (Rp.)  : ";
    cin >> temp[currentSize].Nominal;
    
    cout << string(20, ' ') << "| Tanggal (DD/MM/YYYY): ";
    cin >> temp[currentSize].Tanggal;
    
    cout << string(20, ' ') << "| Kategori       : ";
    cin >> temp[currentSize].Kategori;

    if (isIncome) {
        delete[] daftarPemasukkan;
        daftarPemasukkan = temp;
        Size_Pemasukkan++;
    } else {
        delete[] daftarPengeluaran;
        daftarPengeluaran = temp;
        Size_Pengeluaran++;
    }

    cout << endl << string(20, ' ') << "+ Transaksi berhasil ditambahkan! +";
    pressToContinue();
}

void displayTransactionHeader() {
    cout << string(20, ' ') << "+-----+-------------------------+--------------+--------------+--------------+" << endl;
    cout << string(20, ' ') << "| No  | Nama                    | Nominal      | Tanggal      | Kategori     |" << endl;
    cout << string(20, ' ') << "+-----+-------------------------+--------------+--------------+--------------+" << endl;
}

void displayTransactionRow(int index, const Transaksi& item) {
    cout << string(20, ' ') << "| " << left << setw(3) << index + 1 << " | "
         << setw(23) << item.Nama << " | Rp." << setw(9) << item.Nominal << " | "
         << setw(12) << item.Tanggal << " | " << setw(12) << item.Kategori << " |" << endl;
}

void showTransactions(bool isIncome) {
    clearScreen();
    logo();
    cout << string(20, ' ') << "+--------------------------------------+" << endl;
    cout << string(20, ' ') << "|" << (isIncome ? "       RIWAYAT PEMASUKKAN       " : "      RIWAYAT PENGELUARAN      ") << "|" << endl;
    cout << string(20, ' ') << "+--------------------------------------+" << endl << endl;

    int size = isIncome ? Size_Pemasukkan : Size_Pengeluaran;
    Transaksi* data = isIncome ? daftarPemasukkan : daftarPengeluaran;

    if (size == 0) {
        cout << string(20, ' ') << "| Tidak ada data transaksi.           |" << endl;
    } else {
        displayTransactionHeader();
        
        int total = 0;
        for (int i = 0; i < size; i++) {
            displayTransactionRow(i, data[i]);
            total += data[i].Nominal;
        }
        
        cout << string(20, ' ') << "+-----+-------------------------+--------------+--------------+--------------+" << endl;
        cout << string(20, ' ') << "|" << string(33, ' ') << "Total: Rp." << setw(10) << total << string(4, ' ') << "|" << endl;
    }

    pressToContinue();
}

void showAllTransactions() {
    clearScreen();
    logo();
    cout << string(20, ' ') << "+--------------------------------------+" << endl;
    cout << string(20, ' ') << "|      RIWAYAT KEUANGAN LENGKAP       |" << endl;
    cout << string(20, ' ') << "+--------------------------------------+" << endl << endl;

    int totalIncome = 0, totalExpense = 0;
    for (int i = 0; i < Size_Pemasukkan; i++) totalIncome += daftarPemasukkan[i].Nominal;
    for (int i = 0; i < Size_Pengeluaran; i++) totalExpense += daftarPengeluaran[i].Nominal;

    cout << string(20, ' ') << "| Total Pemasukkan : Rp." << setw(14) << totalIncome << " |" << endl;
    cout << string(20, ' ') << "| Total Pengeluaran: Rp." << setw(14) << totalExpense << " |" << endl;
    cout << string(20, ' ') << "| Saldo           : Rp." << setw(14) << (totalIncome - totalExpense) << " |" << endl << endl;

    cout << string(20, ' ') << "+ DETAIL TRANSAKSI:" << string(24, ' ') << "+" << endl;
    displayTransactionHeader();

    for (int i = 0; i < Size_Pemasukkan; i++) {
        cout << string(20, ' ') << "| " << left << setw(3) << i+1 << "(+)";
        displayTransactionRow(i, daftarPemasukkan[i]);
    }

    for (int i = 0; i < Size_Pengeluaran; i++) {
        cout << string(20, ' ') << "| " << left << setw(3) << Size_Pemasukkan + i + 1 << "(-)";
        displayTransactionRow(i, daftarPengeluaran[i]);
    }

    pressToContinue();
}

void transactionMenu() {
    while (true) {
        int choice = navigateMenu(MenuTransaksi, 3);
        
        if (choice == 0) addTransaction(true);
        else if (choice == 1) addTransaction(false);
        else break;
    }
}

void historyMenu() {
    while (true) {
        int choice = navigateMenu(MenuRiwayat, 4);
        
        if (choice == 0) showTransactions(true);
        else if (choice == 1) showTransactions(false);
        else if (choice == 2) showAllTransactions();
        else break;
    }
}

int main() {
    while (true) {
        int choice = navigateMenu(MenuUtama, 3);
        
        if (choice == 0) transactionMenu();
        else if (choice == 1) historyMenu();
        else {
            if (daftarPemasukkan) delete[] daftarPemasukkan;
            if (daftarPengeluaran) delete[] daftarPengeluaran;
            break;
        }
    }
    return 0;
}
