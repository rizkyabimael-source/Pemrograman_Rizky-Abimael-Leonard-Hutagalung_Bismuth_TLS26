/*
    Problem 1 : The Last Astronaut
    -------------------------------
    Simulasi eliminasi astronot melingkar (modifikasi Josephus Problem)
    dengan nilai K yang berubah secara dinamis setelah setiap eliminasi.

    Ketentuan pengerjaan:
    - Hanya menggunakan library <iostream>
    - Tidak menggunakan function dari library lain
    - Semua function dibuat manual (user-defined function)
*/

#include <iostream>
using namespace std;

const int MAKS_N = 1000; // batas maksimum jumlah astronot yang didukung

// Function manual: mencari nomor astronot hidup berikutnya secara melingkar
// setelah posisi 'dari' (1-based index).
int astronotBerikutnya(bool hidup[], int n, int dari) {
    int posisi = dari;
    do {
        posisi = (posisi % n) + 1; // maju satu langkah, melingkar ke posisi 1 setelah n
    } while (!hidup[posisi]);
    return posisi;
}

int main() {
    int n, k;

    cout << "=== Sistem Eliminasi Astronot (The Last Astronaut) ===" << endl;
    cout << "Masukkan jumlah astronot (N): ";
    cin >> n;
    cout << "Masukkan nilai awal K: ";
    cin >> k;

    if (n < 1 || n > MAKS_N) {
        cout << "Nilai N tidak valid." << endl;
        return 0;
    }

    bool hidup[MAKS_N + 1];
    for (int i = 1; i <= n; i++) {
        hidup[i] = true;
    }

    int sisa = n;
    int posisi = 1; // perhitungan pertama dimulai dari astronot nomor 1

    cout << "\nUrutan astronot yang dieliminasi:" << endl;

    while (sisa > 1) {
        int hitung = 0;

        // Mencari astronot yang mendapat hitungan ke-K dari posisi saat ini
        while (hitung < k) {
            if (hidup[posisi]) {
                hitung++;
                if (hitung == k) {
                    break;
                }
            }
            if (hitung < k) {
                posisi = (posisi % n) + 1;
            }
        }

        int dieliminasi = posisi;
        cout << "- Astronot nomor " << dieliminasi << " dieliminasi (nilai K saat itu = " << k << ")" << endl;

        hidup[dieliminasi] = false;
        sisa--;

        // Perbarui nilai K sesuai aturan khusus
        if (dieliminasi % 2 == 0) {
            k = k + 2;      // genap -> K bertambah 2
        } else {
            k = k - 1;      // ganjil -> K berkurang 1
        }
        if (k < 2) {
            k = 2;          // K tidak boleh kurang dari 2
        }

        // Tentukan titik awal hitungan untuk putaran berikutnya
        if (sisa > 1) {
            posisi = astronotBerikutnya(hidup, n, dieliminasi);
        }
    }

    // Mencari astronot terakhir yang masih bertahan
    int terakhir = -1;
    for (int i = 1; i <= n; i++) {
        if (hidup[i]) {
            terakhir = i;
        }
    }

    cout << "\nAstronot terakhir yang bertahan: " << terakhir << endl;

    return 0;
}
