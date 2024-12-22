#include <iostream>
#include "Graph.h"
#include <limits> // buat numeric_limits di line 27//

using namespace std;
void menu() {
    cout << endl;
    cout << "====== Menu ======" << endl;
    cout << "1. Bangun Graph dari Input" << endl;
    cout << "2. Cetak Graph" << endl;
    cout << "3. Cek Hubungan" << endl;
    cout << "4. Saran Followers" << endl;
    cout << "5. Hapus Vertex Pertama" << endl;
    cout << "6. Hapus Vertex Terakhir" << endl;
    cout << "7. Hapus Vertex Setelah Vertex Tertentu" << endl;
    cout << "8. Export Ke DOT" << endl;
    cout << "9. Keluar" << endl;
    cout << "Pilihan Anda: ";
}

int main() {
    graph G;
    initGraph(&G);

    int choice;
    do {
        menu();

        if (!(cin >> choice)) {
            cout << "Input tidak valid. Harap masukkan angka." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; // Code Buat biar input gaada Huruf //
        }
        switch (choice) {
            case 1:
                buildGraph(&G);
                break;
            case 2:
                cout << "Graph:" << endl;
                printGraph(&G);
                break;
            case 3: {
                char fromID, toID;
                cout << "Masukkan dua vertex untuk cek hubungan: ";
                cin >> fromID >> toID;
                cout << "Cek Hubungan " << fromID << " ke " << toID << ": "
                     << (cekHubungan(&G, fromID, toID) ? "Terhubung" : "Tidak Terhubung") << endl;
                break;
            }
            case 4: {
                char fromID;
                cout << "Masukkan pengguna untuk saran followers: ";
                cin >> fromID;
                saranFollowers(&G, fromID);
                break;
            }
            case 5:
                deleteFirstVertex(&G);
                cout << "Vertex pertama telah dihapus." << endl;
                break;
            case 6:
                deleteLastVertex(&G);
                cout << "Vertex terakhir telah dihapus." << endl;
                break;
            case 7: {
                char afterID;
                cout << "Masukkan ID vertex setelah vertex yang ingin dihapus: ";
                cin >> afterID;
                deleteAfterVertex(&G, afterID);
                cout << "Vertex setelah " << afterID << " telah dihapus." << endl;
                break;
            }
            case 8:
                exportToDot(&G);
                break;
            case 9: {
                cout << "Keluar dari program." << endl;
                break;
            }
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (choice != 9);

    return 0;
}
