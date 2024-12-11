#include <iostream>
#include <cstring>
#include <algorithm> // untuk swap
#include <iomanip>

using namespace std;

struct Mobil {
    char tanggalSewa[20];
    char namaMobil[20];
    char kodeMobil[20];
    char durasiSewa[20];
    float hargaSewa, pendapatan,pendapatanDenda;
    int stok,totalDisewa;
    float hargaPerHari;
};


struct Customer {
    char username[20];
    char password[20];
    char transaksi[10][40];
    int transaksiCount;
    float totalPembayaran;
};


Customer customers[10];
int customerCount = 0;

const char adminUsername[] = "admin";
const char adminPassword[] = "admin123";

void registerUser() {
    int choice;
    cout << "-------------------------------------------\n";
    cout << "|Pilih jenis registrasi:                   |"<<endl;
    cout << "| 1. Admin                                 |"<<endl;
    cout << "| 2. Customer                              |"<<endl;
    cout << "| Pilihan: ";
    cin >> choice;
    

    if (choice == 1) {
        cout << "|Admin sudah terdaftar.\n";
    	cout << "-------------------------------------------\n";
        return;
    } else if (choice == 2) {
        if (customerCount >= 10) {
            cout << "|Batas registrasi customer tercapai.\n";
            cout << "-------------------------------------------\n";
            return;
        }
        
        cout << "|Masukkan Username: ";
        cin >> customers[customerCount].username;
        cout << "|Masukkan Password: ";
        cin >> customers[customerCount].password;
        
        customers[customerCount].transaksiCount = 0;
        customerCount++;
        cout << "|Registrasi customer berhasil.\n";
        cout << "-------------------------------------------\n";
    } else {
        cout << "|Pilihan tidak valid. Silakan coba lagi.\n";
        cout << "-------------------------------------------\n";
        registerUser();
    }
}

void chooseLogin(char username[], char role[]) {
    int choice;
    cout << "-------------------------------------------\n";
    cout << "|Pilih jenis login atau registrasi:       |\n";
    cout << "|1. Login Admin                           |\n";
    cout << "|2. Login Customer                        |\n";
    cout << "|3. Registrasi                            |\n";
    cout << "|4. Keluar Program                        |\n";
    cout << "|Pilihan: ";
    cin >> choice;

    switch (choice) {
        case 1:
            {	char username[20];
            	cout <<"|Masukkan Username Admin : ";
            	cin >> username;
                char password[20];
                cout << "|Masukkan Password Admin: ";
                cin >> password;
                if (strcmp(adminUsername, username) == 0 && strcmp(adminPassword, password) == 0) {
                    strcpy(username, adminUsername);
                    strcpy(role, "admin");
                } else {
                    cout << "|Password/Username Admin salah. Silakan coba lagi. |\n";
                    cout << "-------------------------------------------\n"<<endl;   
                    chooseLogin(username, role);
                }
                break;
            }
        case 2:
            {
                strcpy(role, "customer");
                cout << "|Masukkan Username: ";
                cin >> username;
                char password[20];
                cout << "|Masukkan Password: ";
                cin >> password;

                bool found = false;
                for (int i = 0; i < customerCount; i++) {
                    if (strcmp(customers[i].username, username) == 0 && strcmp(customers[i].password, password) == 0) {
                        cout << "|Berhasil login sebagai customer.\n";
                        cout << "-------------------------------------------\n"<<endl;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "|Login gagal, customer tidak terdaftar. |\n";
                    cout << "-------------------------------------------\n"<<endl;
                    chooseLogin(username, role);
                }
                break;
            }
        case 3:
            registerUser();
            chooseLogin(username, role);
            break;
        case 4 : 
        	exit(0);
        	break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            cout << "-------------------------------------------\n"<<endl;
            chooseLogin(username, role);
            break;
    }
}

Mobil mobil[3] = {
	
    {"", "Avanza", "001", "", 200000, 0, 0, 0 },
    {"", "Innova", "002", "", 250000, 0, 0, 0 },
    {"", "Fortuner", "003", "", 300000, 0, 0, 0 }
};



void setHargaSewa(Mobil &mobil) {
    if (strcmp(mobil.kodeMobil, "001") == 0) {
        mobil.hargaPerHari = 200000;
    } else if (strcmp(mobil.kodeMobil, "002") == 0) {
        mobil.hargaPerHari = 350000;
    } else if (strcmp(mobil.kodeMobil, "003") == 0) {
        mobil.hargaPerHari = 600000;
    }

    if (strcmp(mobil.durasiSewa, "1 Hari") == 0) {
        mobil.hargaSewa = mobil.hargaPerHari;
    } else if (strcmp(mobil.durasiSewa, "2 Hari") == 0) {
        mobil.hargaSewa = mobil.hargaPerHari * 2;
    } else if (strcmp(mobil.durasiSewa, "3 Hari") == 0) {
        mobil.hargaSewa = mobil.hargaPerHari * 3;
    }
}


void inputData() {
    char kodeMobil[20];
    cout << "|Masukkan Kode Mobil : ";
    cin >> kodeMobil;

    for (int i = 0; i < 3; i++) {
        if (strcmp(kodeMobil, mobil[i].kodeMobil) == 0) {
            cout << "|Masukkan Tanggal Ready Mobil : ";
            cin >> mobil[i].tanggalSewa;
            int stokBaru;
            cout << "|Masukkan Jumlah Ready Mobil : ";
            cin >> stokBaru;
            mobil[i].stok += stokBaru;
            strcpy(mobil[i].durasiSewa, "1 Hari"); 
            setHargaSewa(mobil[i]); 
            cout << "|Mobil berhasil ditambahkan." << endl;
            cout << "-------------------------------------------\n"<<endl;
            return;
        }
    }
    cout << "|Kode Mobil tidak valid.\n";
    cout << "-------------------------------------------\n"<<endl;
}

void dataTetap() {
	cout << "----------------------------------------------------------------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "|Kode Mobil: " << mobil[i].kodeMobil << ", Nama Mobil: " << mobil[i].namaMobil;
        if (strcmp(mobil[i].durasiSewa, "") == 0) {
            cout << ", Harga Sewa Perhari : " << mobil[i].hargaSewa <<"     |"<<endl;
        } else {
            setHargaSewa(mobil[i]); 
            cout << ", Harga Sewa Perhari : " << mobil[i].hargaSewa <<"    |"<<endl;
        }
    }
    cout << "----------------------------------------------------------------------\n";
}

void lihatData() {
    for (int i = 0; i < 3 - 1; ++i) {
        for (int j = 0; j < 3 - i - 1; ++j) {
            if (strcmp(mobil[j].kodeMobil, mobil[j + 1].kodeMobil) > 0 ||
                (strcmp(mobil[j].kodeMobil, mobil[j + 1].kodeMobil) == 0 &&
                 strcmp(mobil[j].durasiSewa, mobil[j + 1].durasiSewa) > 0)) {
                swap(mobil[j], mobil[j + 1]);
            }
        }
    }
    cout << "\n" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "|Data Stok :                                                                                                                          \n";
    cout << "|                                                                                                                                     \n";
    for (int i = 0; i < 3; i++) {
        cout << "|No Urut " << i + 1 << " , Kode Mobil : " << mobil[i].kodeMobil << " , Nama Mobil : " << mobil[i].namaMobil
             << " , Tanggal Mobil Ready : " << mobil[i].tanggalSewa;
        if (strcmp(mobil[i].durasiSewa, "") == 0) {
            cout << " , Harga Perhari :  , Total Mobil Yang Ada: " << mobil[i].stok << endl;
        } else {
            setHargaSewa(mobil[i]);
            cout << " , Harga Perhari : " << mobil[i].hargaPerHari << noshowpoint << " , Total Mobil Yang Ada: " << mobil[i].stok << endl;
        }  
    }
    cout << "---------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << endl;
}

void transaksi() {
    float uang;
    char namaPenyewa[20];
    char kodeMobil[20];
    int transaksiMobil;
    char sewahari[20];
    char tanggalPengambilan[20];
    char nomorKTP[20];
    char alamatPenyewa[50];

    cout << "|Masukkan Nama Penyewa: ";
    cin.ignore();
    cin.getline(namaPenyewa, 20);
    cout << "|Masukkan Nomor KTP: ";
    cin.getline(nomorKTP, 20);
    cout << "|Masukkan Alamat Penyewa: ";
    cin.getline(alamatPenyewa, 50);
    cout << "|Masukkan Kode Mobil Yang Ingin Disewa: ";
    cin >> kodeMobil;
    cout << "|Masukkan Jumlah Mobil Yang Ingin Disewa: ";
    cin >> transaksiMobil;
    cout << "|Berapa Hari Mobil disewa: ";
    cin >> sewahari;
    cout << "|Masukkan Tanggal Pengambilan Mobil: ";
    cin >> tanggalPengambilan;

	Mobil mobilSewa;
    int nomerMobil = -1;
    for (int i = 0; i < 3; ++i) {
        if (strcmp(kodeMobil, mobil[i].kodeMobil) == 0) {
            nomerMobil = i;
            break;
        }
    }

    if (nomerMobil != -1) {
        if (mobil[nomerMobil].stok >= transaksiMobil) {
            mobil[nomerMobil].stok -= transaksiMobil;
            mobil[nomerMobil].totalDisewa += transaksiMobil;
            cout << "|Total Mobil Yang Berhasil Disewa: " << transaksiMobil << endl;
            int totalSewa = transaksiMobil * (mobil[nomerMobil].hargaPerHari * atoi(sewahari));
            cout << "|Total Harga Sewa: Rp. " << fixed << setprecision(0) << totalSewa << endl; 
            cout << "|Masukkan Nominal Uang Anda: ";
            cin >> uang;
            mobil[nomerMobil].pendapatan += transaksiMobil * (mobil[nomerMobil].hargaPerHari * atoi(sewahari));

            if (uang >= totalSewa) {
                uang -= totalSewa;
                cout << "\n|----------------------------------------\n";
                cout << "|           Struk Pembayaran             \n";
                cout << "|----------------------------------------\n";
                cout << "|Nama Penyewa         : " << namaPenyewa << endl;
                cout << "|Kode Mobil           : " << kodeMobil << endl;
                cout << "|Jumlah Mobil         : " << transaksiMobil << endl;
                cout << "|Durasi Sewa          : " << sewahari << " Hari" << endl;
                cout << "|Tanggal Pengambilan  : " << tanggalPengambilan << endl;
                cout << "|Total Harga Sewa     : Rp. " << totalSewa << endl;
                cout << "|Uang Pembayaran      : Rp. " << totalSewa << endl;
                cout << "|Kembalian            : Rp. " << fixed << setprecision(0) << uang << endl;
                cout << "|----------------------------------------\n";

                bool customerFound = false;
                for (int i = 0; i < customerCount; i++) {
                    if (strcmp(customers[i].username, namaPenyewa) == 0) {
                        customerFound = true;
                        strcpy(customers[i].transaksi[customers[i].transaksiCount], kodeMobil);
                        strcat(customers[i].transaksi[customers[i].transaksiCount], " (");
                        strcat(customers[i].transaksi[customers[i].transaksiCount], sewahari);
                        strcat(customers[i].transaksi[customers[i].transaksiCount], ")");
                        customers[i].transaksiCount++;
                        break;
                    }
                }

                if (!customerFound) {
                    strcpy(customers[customerCount].username, namaPenyewa);
                    strcpy(customers[customerCount].password, namaPenyewa); 
                    strcat(customers[customerCount].password, "123");
                    strcpy(customers[customerCount].transaksi[0], kodeMobil);
                    strcat(customers[customerCount].transaksi[0], " (");
                    strcat(customers[customerCount].transaksi[0], sewahari);
                    strcat(customers[customerCount].transaksi[0], ")");
                    customers[customerCount].transaksiCount = 1;
                    customerCount++;
                }
            } else {
                cout << "\n|Uang Anda Kurang, Silahkan Masukkan Nominal Uang Yang Sesuai!\n";
            }
        } else {
            cout << "\n|Maaf Jumlah Mobil Yang Tersedia Tidak Cukup.\n";
        }
    } else {
        cout << "\n|Kode Mobil Tidak Valid.\n";
    }
    cout << "-----------------------------------------------------\n" << endl;
}

void laporanKeuangan() {
    int totalPendapatan = 0;
    cout << "\n--------------------------------------------------------------------------------------";
    cout << "\n|Laporan Penjualan :\n";
    cout << "|"<<endl;
    for (int i = 0; i < 3; i++) {
        totalPendapatan += mobil[i].pendapatan;
        cout << "|Kode Mobil: " << mobil[i].kodeMobil << " , Nama Mobil: " << mobil[i].namaMobil
             << " , Total Mobil Yang Disewa : " << mobil[i].totalDisewa << " , Pendapatan: " << mobil[i].pendapatan <<endl;
    }

    cout << "|------------------------------------------------|\n";
    cout << "|Total Pendapatan Sewa Semua Mobil : Rp." << fixed << setprecision(2) << showpoint << totalPendapatan <<"        |"<< endl;
    cout << "|------------------------------------------------|\n";
    cout << "---------------------------------------------------------------------------------------\n"<<endl;
}

void pengembalianMobil() {
    char kodeMobil[20];
    char namaPenyewa[20];
    int hariKeterlambatan;
    int jumlahDikembalikan; 

    cout << "|Masukkan Nama Penyewa : ";
    cin.ignore();
    cin.getline(namaPenyewa, 20);
    cout << "|Masukkan Kode Mobil yang akan dikembalikan: ";
    cin >> kodeMobil;

    int index = -1;
    for (int i = 0; i < 3; i++) {
        if (strcmp(kodeMobil, mobil[i].kodeMobil) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "|Kode Mobil tidak ditemukan.\n";
        return;
    }

    cout << "|Masukkan jumlah mobil yang ingin dikembalikan: "; 
    cin >> jumlahDikembalikan;

    cout << "|Masukkan jumlah hari keterlambatan pengembalian: ";
    cin >> hariKeterlambatan;

    if (hariKeterlambatan < 0) {
        cout << "|Jumlah hari keterlambatan tidak valid.\n";
        cout << "-----------------------------------------------------\n";
        return;
    }

    float denda = 0.0;
    if (hariKeterlambatan > 0) {
        denda = hariKeterlambatan * mobil[index].hargaPerHari * 0.1; 
    }

    cout << "|Terima kasih atas pengembaliannya.\n";
    if (hariKeterlambatan > 0) {
        cout << "|Denda yang harus dibayar: Rp. " << fixed << setprecision(0) << denda << endl;

        float pembayaran;
        cout << "|Masukkan jumlah pembayaran: Rp. ";
        cin >> pembayaran;

        if (pembayaran < denda) {
            cout << "|Pembayaran kurang. Silakan bayar denda sebesar Rp. " << fixed << setprecision(0) << denda << endl;
            return;
        }
        
		mobil[index].pendapatan += denda;
        float kembalian = pembayaran - denda;
        
        if (kembalian > 0) {
            cout << "|Terima kasih atas pembayarannya. Kembalian: Rp. " << fixed << setprecision(0) << kembalian << endl;
            cout << "-----------------------------------------------------\n";
        } else {
            cout << "|Terima kasih atas pembayarannya.\n";
            cout << "-----------------------------------------------------\n";
        }
    } else {
        cout << "|Tidak ada denda yang harus dibayar.\n";
        cout << "-----------------------------------------------------\n";
    }
	cout << "|-----------------------------------------------------\n";
    cout << "|                 Struk Pengembalian                  \n";
    cout << "|-----------------------------------------------------\n";
    cout << "|Nama Penyewa          : " << namaPenyewa << endl;
    cout << "|Kode Mobil            : " << kodeMobil << endl;
    cout << "|Jumlah Mobil          : " << jumlahDikembalikan << endl;
    cout << "|Jumlah Hari Keterlambatan: " << hariKeterlambatan << " Hari" << endl;
    if (hariKeterlambatan > 0) {
        cout << "|Denda                 : Rp. " << fixed << setprecision(0) << denda << endl;
    }
    cout << "|-----------------------------------------------------\n";

    mobil[index].stok += jumlahDikembalikan;
}


int main() {
    char username[20];
    char role[20];
    chooseLogin(username, role);
    cout<<endl;
    dataTetap();
    
    

    while (true) {
        if (strcmp(role, "admin") == 0) {
            int pilihanAdmin;
            cout << "-------------------------------------------";
            cout << "\n|Menu Admin:                              |\n";
            cout << "|1. Input Data                            |\n";
            cout << "|2. Lihat Data                            |\n";
            cout << "|3. Laporan Keuangan                      |\n";
            cout << "|4. Logout                                |\n";
            cout << "|Pilihan: ";
            cin >> pilihanAdmin;

            switch (pilihanAdmin) {
                case 1:
                    inputData();
                    break;
                case 2:
                    lihatData();
                    break;
                case 3:
                    laporanKeuangan();
                    break;
                case 4:
                    chooseLogin(username, role);
                    break;
                default:
                    cout << "Pilihan tidak valid.\n";
                    break;
            }
        } else if (strcmp(role, "customer") == 0) {
            int pilihanCustomer;
            cout << "-----------------------------------------------------";
            cout << "\n|Menu Customer:                                      |\n";
            cout << "|1. Lihat Data                                       |\n";
            cout << "|2. Transaksi                                        |\n";
            cout << "|3. Pengembalian Mobil                               |\n";
            cout << "|4. Logout                                           |\n";
            cout << "|Pilihan: ";
            cin >> pilihanCustomer;

            switch (pilihanCustomer) {
                case 1:
                    lihatData();
                    break;
                case 2:
                    transaksi();    
                    break;   
                case 3:
                	pengembalianMobil();
                	break;
                case 4:
                	chooseLogin(username, role);
                	break;
                default:
                    cout << "Pilihan tidak valid.\n";
                    break;
            }
        }
    }
    return 0;
}
