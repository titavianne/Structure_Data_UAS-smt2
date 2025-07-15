
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

struct Paket {
    string resi;
    string nama;
    string kota;
    int estimasi;
};

vector<Paket> daftarPaket;
unordered_map<string, Paket> hashPaket;

void tambahPaket() {
    Paket p;
    cout << "Masukkan nomor resi: "; cin >> p.resi;
    cout << "Masukkan nama penerima: "; cin.ignore(); getline(cin, p.nama);
    cout << "Masukkan kota tujuan: "; getline(cin, p.kota);
    cout << "Masukkan estimasi waktu (hari): "; cin >> p.estimasi;
    daftarPaket.push_back(p);
    hashPaket[p.resi] = p;
    cout << "Paket berhasil ditambahkan!\n";
}

void lihatPaket() {
    if (daftarPaket.empty()) {
        cout << "Belum ada paket.\n";
        return;
    }
    for (const auto& p : daftarPaket) {
        cout << "Resi: " << p.resi << ", Nama: " << p.nama << ", Kota: " << p.kota << ", Estimasi: " << p.estimasi << " hari\n";
    }
}

void hapusPaket() {
    string resi;
    cout << "Masukkan resi paket yang ingin dihapus: "; cin >> resi;
    auto it = remove_if(daftarPaket.begin(), daftarPaket.end(), [&](Paket& p) {
        return p.resi == resi;
    });
    if (it != daftarPaket.end()) {
        daftarPaket.erase(it, daftarPaket.end());
        hashPaket.erase(resi);
        cout << "Paket berhasil dihapus!\n";
    } else {
        cout << "Paket tidak ditemukan.\n";
    }
}

void cariPaket() {
    string resi;
    cout << "Masukkan resi paket: "; cin >> resi;
    if (hashPaket.find(resi) != hashPaket.end()) {
        Paket p = hashPaket[resi];
        cout << "Paket ditemukan! Nama: " << p.nama << ", Kota: " << p.kota << ", Estimasi: " << p.estimasi << " hari\n";
    } else {
        cout << "Paket tidak ditemukan.\n";
    }
}

void urutkanPaket() {
    sort(daftarPaket.begin(), daftarPaket.end(), [](Paket a, Paket b) {
        return a.estimasi < b.estimasi;
    });
    cout << "Paket berhasil diurutkan berdasarkan estimasi waktu.\n";
    lihatPaket();
}

void jalurTercepat() {
    const int INF = INT_MAX;
    const int kota = 4; // A, B, C, D
    int graph[kota][kota] = {
        {0, 5, INF, 10},
        {INF, 0, 3, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0}
    };
    int start;
    cout << "Pilih kota asal (0:A, 1:B, 2:C, 3:D): "; cin >> start;

    vector<int> dist(kota, INF);
    dist[start] = 0;
    vector<bool> visited(kota, false);

    for (int i = 0; i < kota - 1; i++) {
        int u = -1;
        for (int j = 0; j < kota; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) u = j;
        }
        visited[u] = true;
        for (int v = 0; v < kota; v++) {
            if (graph[u][v] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    for (int i = 0; i < kota; i++) {
        cout << "Jarak tercepat ke kota " << char('A' + i) << " = ";
        if (dist[i] == INF) cout << "Tidak Terjangkau\n";
        else cout << dist[i] << "\n";
    }
}

int main() {
    int pilihan;
    do {
        cout << "\n===== MENU PAKET =====\n";
        cout << "1. Tambah Paket\n";
        cout << "2. Lihat Paket\n";
        cout << "3. Hapus Paket\n";
        cout << "4. Cari Paket\n";
        cout << "5. Urutkan Paket\n";
        cout << "6. Jalur Tercepat\n";
        cout << "7. Keluar\n";
        cout << "Pilih: "; cin >> pilihan;

        switch (pilihan) {
            case 1: tambahPaket(); break;
            case 2: lihatPaket(); break;
            case 3: hapusPaket(); break;
            case 4: cariPaket(); break;
            case 5: urutkanPaket(); break;
            case 6: jalurTercepat(); break;
            case 7: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 7);
    return 0;
}
