#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Barang {
    string nama;
    string kode;
    int harga;
    int stok;
    Barang* next;
};

Barang* head = nullptr;

Barang* buatBarang(string nama, string kode, int harga, int stok) {
    Barang* baru = new Barang;
    baru->nama = nama;
    baru->kode = kode;
    baru->harga = harga;
    baru->stok = stok;
    baru->next = nullptr;
    return baru;
}

void tambahBarang(string nama, string kode, int harga, int stok) {
    Barang* baru = buatBarang(nama, kode, harga, stok);
    if (head == nullptr) {
        head = baru;
    } else {
        Barang* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = baru;
    }
    cout << "Barang \"" << nama << "\" berhasil ditambahkan.\n";
}

void tampilkanBarang(bool ascending) {
    if (head == nullptr) {
        cout << "Nama barang yang Anda masukkan tidak ada.\n";
        return;
    }

    if (ascending)
        cout << "\n===============    STOK TERMURAH    ===============\n";
    else
        cout << "\n===============    STOK TERMAHAL    ===============\n";

    cout << "==================================================\n";
    cout << "|Kode    |Nama Barang        |Harga    |Stok     |\n";
    cout << "==================================================\n";

    Barang* temp = head;
    while (temp != nullptr) {
        cout << "|" << left << setw(8) << temp->kode
             << "|" << left << setw(19) << temp->nama
             << "|" << left << setw(9) << temp->harga
             << "|" << left << setw(8) << temp->stok << "|\n";
        temp = temp->next;
    }

    cout << "==================================================\n";
}

void urutkanBarang(bool ascending) {
    if (head == nullptr || head->next == nullptr)
        return;

    for (Barang* i = head; i != nullptr; i = i->next) {
        for (Barang* j = i->next; j != nullptr; j = j->next) {
            bool kondisi = ascending ? (i->harga > j->harga) : (i->harga < j->harga);
            if (kondisi) {
                swap(i->nama, j->nama);
                swap(i->kode, j->kode);
                swap(i->harga, j->harga);
                swap(i->stok, j->stok);
            }
        }
    }
}

void hapusBarang(string namaCari) {
    if (head == nullptr) {
        cout << "Stok kosong! Tidak ada barang yang bisa dihapus.\n";
        return;
    }

    Barang* temp = head;
    Barang* prev = nullptr;

    while (temp != nullptr && temp->nama != namaCari) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Barang dengan nama \"" << namaCari << "\" tidak ditemukan.\n";
        return;
    }

    if (prev == nullptr) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;
    cout << "Barang dengan nama \"" << namaCari << "\" berhasil dihapus.\n"<<endl;

    if (head == nullptr) {
        cout << "Stok kosong! Tidak ada barang yang bisa ditampilkan.\n";
    } else {
        cout << "----- Daftar stok barang terbaru urut dari yang termurah -----\n";
        urutkanBarang(true);
        tampilkanBarang(true);
    }
}

// Menu utama
void menu() {
    int pilihan;

    do {
        cout << "\n=====================================\n";
        cout << "|  SISTEM MANAJEMEN STOK GUDANG     |\n";
        cout << "=====================================\n";
        cout << "| 1. Input stok barang              |\n";
        cout << "| 2. Lihat daftar stok              |\n";
        cout << "| 3. Hapus barang dari stok         |\n";
        cout << "| 4. Keluar                         |\n";
        cout << "=====================================\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: {
                int jumlah;
                cout << "\n========================================\n";
                cout << "|     INPUT STOK BARANG GUDANG         |\n";
                cout << "========================================\n";
                cout << "Jumlah barang yang akan ditambahkan: ";
                cin >> jumlah;
                cin.ignore();

                for (int i = 0; i < jumlah; ++i) {
                    string nama, kode;
                    int harga, stok;

                    cout << "\nBarang ke-" << (i + 1) << endl;
                    cout << "Nama barang  : ";
                    getline(cin, nama);
                    cout << "Harga barang : ";
                    cin >> harga;
                    cin.ignore();
                    cout << "Kode barang  : ";
                    getline(cin, kode);
                    cout << "Jumlah stok  : ";
                    cin >> stok;
                    cin.ignore();

                    tambahBarang(nama, kode, harga, stok);
                }
                break;
            }
            case 2: {
                if (head == nullptr) {
                    cout << "Stok kosong! Tidak ada barang yang bisa ditampilkan.\n";
                    break;
                }

                int opsi;
                cout << "\n--- LIHAT STOK BARANG ---\n";
                cout << "1. Urutkan dari harga termurah ke termahal\n";
                cout << "2. Urutkan dari harga termahal ke termurah\n";
                cout << "Pilih opsi: ";
                cin >> opsi;

                if (opsi == 1 || opsi == 2) {
                    urutkanBarang(opsi == 1);
                    tampilkanBarang(opsi == 1);
                } else {
                    cout << "Opsi yang Anda masukkan tidak valid.\n";
                }
                break;
            }
            case 3: {
                if (head == nullptr) {
                    cout << "Stok kosong! Tidak ada barang yang bisa dihapus.\n";
                    break;
                }

                string nama;
                cout << "\n--- HAPUS DATA BARANG ---\n";
                cout << "Masukkan nama barang yang ingin dihapus: ";
                getline(cin >> ws, nama);
                hapusBarang(nama);
                break;
            }
            case 4:
                cout << "Anda telah keluar dari program. Terima kasih~\n";
                break;
            default:
                cout << "Menu yang Anda pilih tidak valid. Silakan coba lagi.\n";
        }

    } while (pilihan != 0);
}

int main() {
    menu();
    return 0;
}
