#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
// Deklarasi Array Data Variabel Global
    typedef struct Variabel_Global{
        char produk[20];
        int harga;
        int jumlah;
        int TotalHarga;
        int diskon;
    } GVariabel;
// Fungsi Urutan Data Produk Berdasarkan Jumlah
    void UrutkanProduk(GVariabel data[]) {
        GVariabel temp; // deklarasi variable temp

        // Fungsi Perulangan Pengurutan
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4 - i; j++) {
                if(data[j].jumlah < data[j+1].jumlah) { // Kondisi Cek Pengurutan Produk, Jika Produk pertama lebih kecil jumlahnya dari produk selanjutnya
                    temp = data[j];
                    data[j] = data[j+1];
                    data[j+1] = temp;
                }
            }
        } // End Fungsi Perulangan Pengurutan
    }
// Fungsi Menentukan Jumlah Diskon
    int jumlahDiskon(int jumlah) {
        return jumlah > 5 ? 15 : jumlah > 3 ? 10 : 0;
    }
// Akhir Fungsi Menentukan Jumlah Diskon

// Fungsi Tampilan Menu Awal
    void tampilkanMenuAwal(GVariabel data[]) {
        printf("                                SELAMAT DATANG DI                                 \n");
        printf("                                   TOKO SKENSA                                    \n");
        printf("==================================================================================\n");
        printf("                    Silahkan Pilih Barang yang Anda Inginkan :                    \n");
        printf("==================================================================================\n\n");
        printf("\|No|Barang \t\t|Harga      |\n");
        printf("-------------------------------------\n");
        // Funsi Looping untuk menampilkan data array barang dalam tampilan
        for(int i=0;i<6;i++){
            printf("|%i.|%s|\t\t|%d|\n",i+1,data[i].produk,data[i].harga);
        }// End Funsi Looping untuk menampilkan data array barang dalam tampilan
        printf("==================================================================================\n\n");
        printf("99. Struk Pembayaran\n");
        printf("55. Reset Pilihan\n");
        printf("00. Keluar Aplikasi\n\n");
    }
// Akhir fungsi Tampilan Menu Awal

// Fungsi Rekap Pesanan / Struk Pesanan
    void TampilkanStruk(GVariabel data[]) {
        printf("\n\n                              REKAP PESANAN BARANG                                    \n");
        printf("==================================================================================\n");
        printf("|No|Jumlah  |Nama Barang        |Harga       |Total Harga\t|Diskon         |                  \n");
        printf("==================================================================================\n\n");
        for (int i = 0; i < 6; i++) {
            if (data[i].jumlah != 0) {  // Periksa apakah jumlah barang tidak nol
                printf("|%i.|%i\t    |%s\t\t|%i\t     |%i\t\t|%i\t\t|\n", i + 1, data[i].jumlah, data[i].produk, data[i].harga, data[i].TotalHarga, data[i].diskon);
            }
        } // End Funsi Looping untuk menampilkan data array barang dalam tampilan
        printf("==================================================================================\n\n");
    }
// Akhir Fungsi Rekap Pesanan / Struk Pesanan

    int main() {
         //  Deklarasi Variabel int
        int BarangDipilih;
        int PersentaseDiskon;
        int TotalSemuaTagihan;
        int loop = 0;
        int TotalDiskon;
        int Tagihan;
        int Pembayaran;
        int Kembalian;
        int jumlahTambahan;
        int IDStruk[20];
        // Akhir Deklarasi Variabel int

        // Deklarasi variable Char / String
        char ZonaWaktu[80];
        char namafile[50];
        // Akhir Deklarasi variable Char / String

       

        // Deklarasi Variabel Fungsi Waktu
        time_t sekarang;
        time(&sekarang);
        struct tm *waktu_lokal = localtime(&sekarang);
        strftime(ZonaWaktu, 80, "%a %b %d %H:%M:%S %Y", waktu_lokal);
        // Deklarasi Variabel Fungsi Waktu

     // Deklarasi Data dari Array Global
        GVariabel data[6] = {
            {"Buku Tulis", 5000, 0},
            {"Pensil", 2000, 0},
            {"Penghapus", 1000, 0},
            {"Penggaris", 1000, 0},
            {"Bujur", 500, 0},
            {"Peraut", 700, 0}
        };
    // Akhir deklarasi Data dari Array Global

       // Panggil Fungsi TampilkanMenuAwal
        tampilkanMenuAwal(data);
    // Akhir Panggil Fungsi TampilkanMenuAwal

    // Fungsi Do While untuk Perulangan Pilihan
        do {
            printf("\n==================================================================================\n\n");
            printf("\Input Pilihan yang Anda Inginkan : ");
            if(scanf("%i", &BarangDipilih) != 1) {
                while ((getchar()) != '\n'); // Membersihkan buffer masukan
                printf("Input tidak valid.\n");
                continue;
            }

            switch (BarangDipilih) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                    printf("--------------------------------------\n");
                    printf("Masukkan Jumlah %s \t : ", data[BarangDipilih - 1].produk);
                    int tambahanJumlah;
                    scanf("%i", &tambahanJumlah);
                    data[BarangDipilih - 1].jumlah += tambahanJumlah; // Menggunakan += untuk menambahkan jumlah baru ke jumlah yang sudah ada
                    printf("\n");

                    for(int i = 0; i < 6; i++) {
                        data[i].TotalHarga = data[i].harga * data[i].jumlah; // rumus total harga
                        PersentaseDiskon = jumlahDiskon(data[i].jumlah);
                        data[i].diskon = (data[i].TotalHarga * PersentaseDiskon) / 100; // rumus diskon
                    }
                    break;

                case 55:
                    system("cls"); // Membersihkan layar
                    main(); // Memanggil main() untuk mereset pilihan
                    return 0; // Keluar dari loop setelah main() selesai
                    break;

                case 99:
                case 0:
                    break;  // Keluar dari loop jika pilihan adalah 99 atau 0

                default:
                    printf("--------------------------------------\n");
                    printf("Pilihan Tidak Valid\n");
            }
        } while (BarangDipilih != 99 && BarangDipilih != 55 && BarangDipilih != 0);
         // Akhir Fungsi Do While untuk Perulangan Pilihan

        // Panggil Fungsi UrutkanProduk
    UrutkanProduk(data);
    // Akhir Panggil Fungsi UrutkanProduk

    // Fungsi Jika BarangDipilih == 00
        if(BarangDipilih == 00) {
            printf("\n----------------------------------------------------------------------------------\n");
                printf("                               Keluar Dari Program                              \n");
                printf("----------------------------------------------------------------------------------\n");
            return 0;
        }
    // Akhir fungsi Jika BarangDipilih == 00


 // Fungsi Jika BarangDipilih == 99
     if(BarangDipilih == 99) {

            // Mendeklarasikan array karakter untuk menyimpan ID Struk sebelum dicetak ke konsol
        char IDStrukConsole[50];
        // Mengonversi nilai waktu saat ini menjadi string dan menyimpannya dalam variabel IDStrukConsole
        sprintf(IDStrukConsole, "%ld", sekarang);


            TampilkanStruk(data);

          // Menghitung total tagihan dari semua produk yang dibeli
        TotalSemuaTagihan = data[0].TotalHarga + data[1].TotalHarga + data[2].TotalHarga + data[3].TotalHarga + data[4].TotalHarga + data[5].TotalHarga;
        printf("Total Harga \t:Rp. %i,-", TotalSemuaTagihan);

        // Menghitung total diskon dari semua produk yang dibeli
        TotalDiskon = data[0].diskon + data[1].diskon + data[2].diskon + data[3].diskon + data[4].diskon + data[5].diskon;
        printf("\nTotal Diskon \t:Rp. %i,-", TotalDiskon);

        // Menghitung total tagihan setelah diskon
        Tagihan = TotalSemuaTagihan - TotalDiskon;
        printf("\nTotal Bayar \t:Rp. %i,-", Tagihan);


            printf("\n==================================================================================\n\n");

            printf("Masukkan Nominal Pembayaran :Rp. ");
            scanf("%i", &Pembayaran);


        // looping untuk uang pembayaran kurang
            do {

                if(Pembayaran < Tagihan) {

                    printf("\nNominal Pembayaran Kurang!, Silahkan Masukkan Ulang Nominal Pembayaran");
                    printf("\n==================================================================================\n\n");
                    printf("\nMasukkan Ulang Nominal Pembayaran :Rp. ");
                    scanf("%i", &Pembayaran);

                } else {
                    break;
                }

            } while (Pembayaran != Tagihan || Pembayaran < Tagihan);
            // Akhir looping untuk uang pembayaran kurang


            // kondisi ketika uang pas
            if(Pembayaran == Tagihan || Pembayaran > Tagihan) {
                Kembalian = Pembayaran - Tagihan; // rumus kembalian
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
                 for (int i = 0; i < 6; i++) {
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

    // Fungsi Jika BarangDipilih == 99


       // Mendeklarasikan pointer ke FILE untuk menangani file
        FILE *file;
        // Mengonversi nilai waktu saat ini menjadi string dan menyimpannya dalam variabel IDStruk
        sprintf(IDStruk, "%ld", sekarang);

        // Menggabungkan IDStruk dengan nama file untuk membuat nama file unik
        sprintf(namafile, "Struk_%s.txt", IDStruk);

        // Membuka file dengan nama yang telah dibuat untuk ditulisi
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
         for (int i = 0; i < 6; i++) {
            if (data[i].jumlah != 0) { // Periksa apakah jumlah barang tidak nol
                fprintf(file,"|%i.|%i\t    |%s\t\t|%i\t     |%i\t\t|%i\t\t|\n", i + 1, data[i].jumlah, data[i].produk, data[i].harga, data[i].TotalHarga, data[i].diskon);
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
