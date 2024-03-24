#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h> 

// Definisi struktur data untuk menyimpan informasi barang
typedef struct {
    char product[20]; // Nama produk
    int price; // Harga
    int quantity; // Jumlah
    int total_price; // Total harga
    int discount; // Diskon
} Item;

// Fungsi untuk mengurutkan barang berdasarkan jumlah (dari jumlah terbesar ke terkecil)
void sortItems(Item items[], int size) {
    Item temp;
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (items[j].quantity < items[j + 1].quantity) {
                temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
}

// Fungsi untuk menghitung diskon berdasarkan jumlah barang
int calculateDiscount(int quantity) {
    return quantity > 5 ? 15 : quantity > 3 ? 10 : 0;
}

// Fungsi untuk menampilkan menu utama
void displayMenu(Item items[], int size) {
    printf("\t\t                                SELAMAT DATANG DI                                 \n");
    printf("\t\t                                   TOKO SKENSA                                    \n");
    printf("\t\t==================================================================================\n");
    printf("\t\t                    Silahkan Pilih Barang yang Anda Inginkan :                    \n");
    printf("\t\t==================================================================================\n\n");
    printf("\t\t|No|Barang \t\t|Harga      |\n");
    printf("\t\t-------------------------------------\n");
    for (int i = 0; i < size; i++)
        printf("\t\t|%i.|%-20s|Rp. %i,00 |\n", i + 1, items[i].product, items[i].price);
    printf("\t\t==================================================================================\n\n");
    printf("\t\t99. Struk Pembayaran\n");
    printf("\t\t55. Reset Pilihan\n");
    printf("\t\t00. Keluar Aplikasi\n\n");
}

// Fungsi untuk menampilkan struk pembayaran
void displayReceipt(Item items[], int size, int total_bill, int total_discount, int payment, int change) {
    printf("\n\n\t\t                              REKAP PESANAN BARANG                                    \n");
    printf("\t\t==================================================================================\n");
    printf("\t\t|No|Jumlah  |Nama Barang        |Harga       |Total Harga\t|Diskon         |                  \n");
    printf("\t\t==================================================================================\n\n");
    for (int i = 0; i < size; i++)
        printf("\t\t|%i.|%-9i|%-20s|Rp. %-9i|Rp. %-9i\t|Rp. %-9i\t|\n", i + 1, items[i].quantity, items[i].product, items[i].price, items[i].total_price, items[i].discount);
    printf("\t\t==================================================================================\n");
    printf("\t\tTotal Harga \t:Rp. %i,-\n", total_bill);
    printf("\t\tTotal Diskon \t:Rp. %i,-\n", total_discount);
    printf("\t\tTotal Bayar \t:Rp. %i,-\n", total_bill - total_discount);
    printf("\t\tPembayaran \t:Rp. %i,-\n", payment);
    printf("\t\tKembalian \t:Rp. %i,-\n", change);
    printf("\t\t==================================================================================\n\n");
}

int main() {
    // Inisialisasi array barang dan jumlah barang
    Item items[] = {{"Buku Tulis", 5000, 0, 0, 0}, {"Pensil", 2000, 0, 0, 0}, {"Penghapus", 1000, 0, 0, 0}, {"Penggaris", 1000, 0, 0, 0}, {"Bujur", 500, 0, 0, 0}};
    int size = sizeof(items) / sizeof(Item);

    // Inisialisasi variabel
    int choice, total_bill = 0, total_discount = 0, payment, change;
    char timezone[80];
    time_t now = time(NULL);
    struct tm* local_time = localtime(&now);
    strftime(timezone, sizeof(timezone), "%a %b %d %H:%M:%S %Y", local_time);

    // Loop utama program
    do {
        displayMenu(items, size);
        printf("\t\tInput Pilihan yang Anda Inginkan : ");
        
        // Memeriksa input apakah angka atau bukan
        if (scanf("%d", &choice) != 1) {
            printf("\t\tInput tidak valid (harus berupa angka)!\n");
            char c;
            while ((c = getchar()) != '\n' && c != EOF); // Membersihkan buffer input
            continue;
        }

        // Validasi input pilihan
        if (choice < 1 || choice > size) {
            if (choice != 99 && choice != 55 && choice != 0)
                printf("\t\tPilihan Tidak Valid\n");
        } else if (choice == 99 || choice == 55 || choice == 0) {
            break;
        } else {
            // Penanganan pemesanan barang
            printf("\t\tMasukkan Jumlah %s \t : ", items[choice - 1].product);
            scanf("%i", &items[choice - 1].quantity);

            // Menghitung total harga dan diskon untuk setiap barang
            for (int i = 0; i < size; i++) {
                items[i].total_price = items[i].price * items[i].quantity;
                items[i].discount = (items[i].total_price * calculateDiscount(items[i].quantity)) / 100;
            }

            // Reset pemesanan jika memilih opsi 55
            if (choice == 55)
                for (int i = 0; i < size; i++)
                    items[i].quantity = items[i].total_price = items[i].discount = 0;
        }
    } while (choice != 99 && choice != 0);

    // Mengurutkan barang berdasarkan jumlah (dari jumlah terbesar ke terkecil)
    sortItems(items, size);

    // Keluar dari program jika memilih opsi 0
    if (choice == 0) {
        printf("\t\tKeluar Dari Program\n");
        return 0;
    }

    // Menghitung total harga keseluruhan dan total diskon
    for (int i = 0; i < size; i++)
        total_bill += items[i].total_price, total_discount += items[i].discount;

    // Menampilkan struk pembayaran sebelum pembayaran
    displayReceipt(items, size, total_bill, total_discount, 0, 0);

    // Meminta pengguna memasukkan nominal pembayaran
    printf("\t\tMasukkan Nominal Pembayaran :Rp. ");
    scanf("%i", &payment);

    // Memastikan nominal pembayaran cukup
    while (payment < total_bill - total_discount) {
        printf("\n\t\tNominal Pembayaran Kurang!, Silahkan Masukkan Ulang Nominal Pembayaraan");
        printf("\n\t\tMasukkan Ulang Nominal Pembayaran :Rp. ");
        scanf("%i", &payment);
    }

    // Menghitung kembalian
    change = payment - (total_bill - total_discount);

    // Menampilkan struk pembayaran setelah pembayaran
    displayReceipt(items, size, total_bill, total_discount, payment, change);

    // Membuat file struk pembayaran
    FILE* file;
    char filename[50];
    sprintf(filename, "Receipt_%ld.txt", now);
    file = fopen(filename, "w");

    fprintf(file, "\n\t\t==================================================================================\n");
    fprintf(file, "\t\t|                                   TOKO SKENSA                                  |\n");
    fprintf(file, "\t\t|                          JALAN HOS COKROAMINOTO NO. 84                         |\n");
    fprintf(file, "\t\t|                                  DENPASAR, BALI                                |\n");
    fprintf(file, "\t\t|                                  TELP. 081628579                               |\n");
    fprintf(file, "\t\t|                                                                                |\n");
    fprintf(file, "\t\t|ID Struk : %ld                                                           |\n", now);
    fprintf(file, "\t\t==================================================================================\n");
    fprintf(file, "\t\t|No|Jumlah  |Nama Barang        |Harga       |Total Harga\t|Diskon         |                  \n");
    fprintf(file, "\t\t==================================================================================\n\n");
    for (int i = 0; i < size; i++)
        fprintf(file, "\t\t|%i.|%-9i|%-20s|Rp. %-9i|Rp. %-9i\t|Rp. %-9i\t|\n", i + 1, items[i].quantity, items[i].product, items[i].price, items[i].total_price, items[i].discount);
    fprintf(file, "\t\t==================================================================================\n");
    fprintf(file, "\t\t|                                                                                |\n");
    fprintf(file, "\t\t|Total Harga \t:Rp. %i,-                                                     |\n", total_bill);
    fprintf(file, "\t\t|Total Diskon \t:Rp. %i,-                                                      |\n", total_discount);
    fprintf(file, "\t\t|Total Bayar \t:Rp. %i,-                                                     |\n", total_bill - total_discount);
    fprintf(file, "\t\t|Pembayaran \t:Rp. %i,-                                                     |\n", payment);
    fprintf(file, "\t\t|Kembalian \t:Rp. %i,-                                                      |\n", change);
    fprintf(file, "\t\t|                                                                                |\n");
    fprintf(file, "\t\t|                                                                                |\n");
    fprintf(file, "\t\t|Waktu / Hari : %s                                         |\n", timezone);
    fprintf(file, "\t\t|                                                                                |\n");
    fprintf(file, "\t\t==================================================================================\n");
    fclose(file);

    return 0;
}
