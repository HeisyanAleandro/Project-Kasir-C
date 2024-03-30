#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char produk[20];
    int harga, jumlah, TotalHarga, diskon;
} GVariabel;

void UrutkanProduk(GVariabel data[]) {
    GVariabel temp;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            if (data[j].jumlah < data[j + 1].jumlah) {
                temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

int jumlahDiskon(int jumlah) {
    return jumlah > 5 ? 15 : jumlah > 3 ? 10 : 0;
}

void tampilkanMenuAwal(GVariabel data[]) {
    printf("                                SELAMAT DATANG DI                                 \n");
    printf("                                   TOKO SKENSA                                    \n");
    printf("==================================================================================\n");
    printf("                    Silahkan Pilih Barang yang Anda Inginkan :                    \n");
    printf("==================================================================================\n\n");
    printf("\|No|Barang \t\t|Harga      |\n");
    printf("-------------------------------------\n");
    for (int i = 0; i < 5; i++) {
        printf("|%i.|%s|\t\t|%d|\n", i + 1, data[i].produk, data[i].harga);
    }
    printf("==================================================================================\n\n");
    printf("99. Struk Pembayaran\n");
    printf("55. Reset Pilihan\n");
    printf("00. Keluar Aplikasi\n\n");
}

void TampilkanStruk(GVariabel data[]) {
    printf("\n\n                              REKAP PESANAN BARANG                                    \n");
    printf("==================================================================================\n");
    printf("|No|Jumlah  |Nama Barang        |Harga       |Total Harga\t|Diskon         |                  \n");
    printf("==================================================================================\n\n");
    for (int i = 0; i < 5; i++) {
        if (data[i].jumlah != 0) {
            printf("|%i.|%i\t    |%s\t\t|%i\t     |%i\t\t|%i\t\t|\n", i + 1, data[i].jumlah, data[i].produk, data[i].harga, data[i].TotalHarga, data[i].diskon);
        }
    }
    printf("==================================================================================\n\n");
}

int main() {
    int BarangDipilih, PersentaseDiskon, TotalSemuaTagihan, loop = 0, TotalDiskon, Tagihan, Pembayaran, Kembalian, jumlahTambahan;
    char IDStruk[20], IDStrukConsole[50], ZonaWaktu[80], namafile[50];
    time_t sekarang;
    time(&sekarang);
    struct tm *waktu_lokal = localtime(&sekarang);
    strftime(ZonaWaktu, 80, "%a %b %d %H:%M:%S %Y", waktu_lokal);

    GVariabel data[5] = {
        {"Buku Tulis", 5000, 0},
        {"Pensil", 2000, 0},
        {"Penghapus", 1000, 0},
        {"Penggaris", 1000, 0},
        {"Bujur", 500, 0}
    };

    tampilkanMenuAwal(data);

    do {
        printf("\n==================================================================================\n\n");
        printf("\Input Pilihan yang Anda Inginkan : ");
        if (scanf("%i", &BarangDipilih) != 1) {
            while ((getchar()) != '\n');
            printf("Input tidak valid.\n");
            continue;
        }

        switch (BarangDipilih) {
            case 1  ... 6:
                printf("--------------------------------------\n");
                printf("Masukkan Jumlah %s \t : ", data[BarangDipilih - 1].produk);
                int tambahanJumlah;
                scanf("%i", &tambahanJumlah);
                data[BarangDipilih - 1].jumlah += tambahanJumlah;
                printf("\n");

                for (int i = 0; i < 5; i++) {
                    data[i].TotalHarga = data[i].harga * data[i].jumlah;
                    PersentaseDiskon = jumlahDiskon(data[i].jumlah);
                    data[i].diskon = (data[i].TotalHarga * PersentaseDiskon) / 100;
                }
                break;

            case 55:
                system("cls");
                main();
                return 0;
                break;

            case 99:
                if (BarangDipilih == 99) {
                    sprintf(IDStrukConsole, "%ld", sekarang);
                    TampilkanStruk(data);
                    TotalSemuaTagihan = data[0].TotalHarga + data[1].TotalHarga + data[2].TotalHarga + data[3].TotalHarga + data[4].TotalHarga;
                    printf("Total Harga \t:Rp. %i,-", TotalSemuaTagihan);
                    TotalDiskon = data[0].diskon + data[1].diskon + data[2].diskon + data[3].diskon + data[4].diskon;
                    printf("\nTotal Diskon \t:Rp. %i,-", TotalDiskon);
                    Tagihan = TotalSemuaTagihan - TotalDiskon;
                    printf("\nTotal Bayar \t:Rp. %i,-", Tagihan);
                    printf("\n==================================================================================\n\n");
                    printf("Masukkan Nominal Pembayaran :Rp. ");
                    scanf("%i", &Pembayaran);

                    do {
                        if (Pembayaran < Tagihan) {
                            printf("\nNominal Pembayaran Kurang!, Silahkan Masukkan Ulang Nominal Pembayaran");
                            printf("\n==================================================================================\n\n");
                            printf("\nMasukkan Ulang Nominal Pembayaran :Rp. ");
                            scanf("%i", &Pembayaran);
                        } else {
                            break;
                        }
                    } while (Pembayaran != Tagihan || Pembayaran < Tagihan);

                    if (Pembayaran == Tagihan || Pembayaran > Tagihan) {
                        Kembalian = Pembayaran - Tagihan;
                        printf("\nKembalian \t\t    :Rp. %i\n", Kembalian);
                        printf("\n==================================================================================\n\n");
                        printf("\n==================================================================================\n");
                        printf("|                                   TOKO SKENSA                                  |\n");
                        printf("|                          JALAN HOS COKROAMINOTO NO. 84                         |\n");
		                printf("|                                  DENPASAR, BALI                                |\n");
		                printf("|                                  TELP. 081628579                               |\n");
		                printf("|                                                                                |\n");
		                printf("|ID Struk : %s                                                           |\n", IDStrukConsole);
		                printf("==================================================================================\n");
		                printf("|No|Jumlah  |Nama Barang        |Harga       |Total Harga\t|Diskon         |                  \n");
		                printf("==================================================================================\n\n");
		                 for (int i = 0; i < 5; i++) {
		            if (data[i].jumlah != 0) { // Periksa apakah jumlah barang tidak nol
		                printf("|%i.|%i\t    |%s\t\t|%i\t     |%i\t\t|%i\t\t|\n", i + 1, data[i].jumlah, data[i].produk, data[i].harga, data[i].TotalHarga, data[i].diskon);
		            }
		        }
		                printf("==================================================================================\n");
		                printf("|                                                                                |\n");
		                printf("|Total Harga \t:Rp. %i,-                                                     |\n", TotalSemuaTagihan);
		                printf("|Total Diskon \t:Rp. %i,-                                                      |\n", TotalDiskon);
		                printf("|Total Bayar \t:Rp. %i,-                                                     |\n", Tagihan);
		                printf("|Pembayaran \t:Rp. %i,-                                                     |\n", Pembayaran);
		                printf("|Kembalian \t:Rp. %i,-                                                      |\n", Kembalian);
		                printf("|                                                                                |\n");
		                printf("|Waktu / Hari : %s                                         |\n", ZonaWaktu);
		                printf("|                                                                                |\n");
		                printf("==================================================================================\n");
                    }
                }
                break;

            case 0:
                printf("\n----------------------------------------------------------------------------------\n");
                printf("                               Keluar Dari Program                              \n");
                printf("----------------------------------------------------------------------------------\n");
                return 0;
                break;

            default:
                printf("--------------------------------------\n");
                printf("Pilihan Tidak Valid\n");
        }
    } while (BarangDipilih != 99 && BarangDipilih != 55 && BarangDipilih != 0);

    UrutkanProduk(data);

    FILE *file;
    sprintf(IDStruk, "%ld", sekarang);
    sprintf(namafile, "Struk_%s.txt", IDStruk);
    file = fopen(namafile, "w");

    	fprintf(file, "\n\t\t==================================================================================\n");
    	fprintf(file, "\t\t|                                   TOKO SKENSA                                  |\n");
        fprintf(file, "\t\t|                          JALAN HOS COKROAMINOTO NO. 84                         |\n");
        fprintf(file, "\t\t|                                  DENPASAR, BALI                                |\n");
        fprintf(file, "\t\t|                                  TELP. 081628579                               |\n");
        fprintf(file, "\t\t|                                                                                |\n");
        fprintf(file, "\t\t|ID Struk : %s                                                           |\n", IDStruk);
        fprintf(file, "\t\t==================================================================================\n");
        fprintf(file, "\t\t|No|Jumlah  |Nama Barang        |Harga       |Total Harga\t|Diskon         |                  \n");
        fprintf(file, "\t\t==================================================================================\n\n");
         for (int i = 0; i < 5; i++) {
            if (data[i].jumlah != 0) { // Periksa apakah jumlah barang tidak nol
                fprintf(file,"\t\t|%i.|%i\t    |%s\t\t|%i\t     |%i\t\t|%i\t\t|\n", i + 1, data[i].jumlah, data[i].produk, data[i].harga, data[i].TotalHarga, data[i].diskon);
            }
        }
        fprintf(file, "\t\t==================================================================================\n");
        fprintf(file, "\t\t|                                                                                |\n");
        fprintf(file, "\t\t|Total Harga \t:Rp. %i,-                                                     |", TotalSemuaTagihan);
        fprintf(file, "\n\t\t|Total Diskon \t:Rp. %i,-                                                      |", TotalDiskon);
        fprintf(file, "\n\t\t|Total Bayar \t:Rp. %i,-                                                     |", Tagihan);
        fprintf(file, "\n\t\t|Pembayaran \t:Rp. %i,-                                                     |", Pembayaran);
        fprintf(file, "\n\t\t|Kembalian \t:Rp. %i,-                                                      |\n", Kembalian);
        fprintf(file, "\t\t|                                                                                |\n");
        fprintf(file, "\t\t|                                                                                |\n");
        fprintf(file, "\t\t|Waktu / Hari : %s                                         |\n", ZonaWaktu);
        fprintf(file, "\t\t|                                                                                |\n");
        fprintf(file, "\t\t==================================================================================\n");

    return 0;
}
