/*
    Problem 2 : Alien-In-The-Middle
    --------------------------------
    Sistem sandi: huruf pertama tidak berubah, setiap huruf berikutnya
    digeser sebanyak nilai posisi huruf ASLI sebelumnya (A=1, ..., Z=26),
    dan jika hasil pergeseran melewati Z maka berputar kembali ke A.

    Ketentuan pengerjaan:
    - Hanya menggunakan library <iostream>
    - Tidak menggunakan function dari library lain
    - Semua function dibuat manual (user-defined function)
*/

#include <iostream>
using namespace std;

const int MAKS_PANJANG = 1000;

// Function manual pengganti strlen(): menghitung panjang string
int hitungPanjang(char teks[]) {
    int panjang = 0;
    while (teks[panjang] != '\0') {
        panjang++;
    }
    return panjang;
}

// Mengonversi huruf kapital menjadi nilai posisi (A=1, B=2, ..., Z=26)
int posisiHuruf(char huruf) {
    return (huruf - 'A') + 1;
}

// Mengonversi nilai posisi (1..26) menjadi huruf kapital
char hurufDariPosisi(int nilai) {
    return (char)((nilai - 1) + 'A');
}

// Function manual untuk mod yang hasilnya selalu positif (0..m-1)
int modPositif(int a, int m) {
    int hasil = a % m;
    if (hasil < 0) {
        hasil = hasil + m;
    }
    return hasil;
}

// Meng-enkripsi pesan sesuai sistem sandi alien
void enkripsi(char pesan[], char hasil[]) {
    int panjang = hitungPanjang(pesan);

    for (int i = 0; i < panjang; i++) {
        int nilaiAsli = posisiHuruf(pesan[i]);
        int nilaiBaru;

        if (i == 0) {
            nilaiBaru = nilaiAsli; // huruf pertama tidak berubah
        } else {
            int nilaiSebelumnya = posisiHuruf(pesan[i - 1]); // huruf ASLI sebelumnya
            int temp = nilaiAsli + nilaiSebelumnya;
            nilaiBaru = modPositif(temp - 1, 26) + 1; // menjaga hasil tetap 1..26
        }

        hasil[i] = hurufDariPosisi(nilaiBaru);
    }
    hasil[panjang] = '\0';
}

// Men-dekripsi pesan tersandi kembali menjadi pesan asli
// (dilakukan berurutan karena setiap huruf asli membutuhkan huruf asli
//  sebelumnya, yang sudah diketahui dari hasil dekripsi sebelumnya)
void dekripsi(char sandi[], char asli[]) {
    int panjang = hitungPanjang(sandi);

    for (int i = 0; i < panjang; i++) {
        if (i == 0) {
            asli[i] = sandi[i]; // huruf pertama tidak berubah
        } else {
            int nilaiSandi = posisiHuruf(sandi[i]);
            int nilaiSebelumnyaAsli = posisiHuruf(asli[i - 1]);
            int temp = nilaiSandi - nilaiSebelumnyaAsli;
            int nilaiAsli = modPositif(temp - 1, 26) + 1;
            asli[i] = hurufDariPosisi(nilaiAsli);
        }
    }
    asli[panjang] = '\0';
}

int main() {
    char pesan[MAKS_PANJANG];
    char hasilEnkripsi[MAKS_PANJANG];
    char pesanAsli[MAKS_PANJANG];
    int pilihan;

    cout << "=== Sistem Sandi Alien-In-The-Middle ===" << endl;
    cout << "1. Enkripsi pesan (huruf asli -> pesan tersandi)" << endl;
    cout << "2. Dekripsi pesan (pesan tersandi -> huruf asli)" << endl;
    cout << "Pilih menu (1/2): ";
    cin >> pilihan;

    if (pilihan == 1) {
        cout << "Masukkan pesan asli (huruf kapital, tanpa spasi): ";
        cin >> pesan;
        enkripsi(pesan, hasilEnkripsi);
        cout << "Pesan setelah disandikan: " << hasilEnkripsi << endl;
    } else if (pilihan == 2) {
        cout << "Masukkan pesan tersandi (huruf kapital, tanpa spasi): ";
        cin >> pesan;
        dekripsi(pesan, pesanAsli);
        cout << "Pesan asli: " << pesanAsli << endl;
    } else {
        cout << "Pilihan tidak valid." << endl;
    }

    return 0;
}
