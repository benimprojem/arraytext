#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraytext.h"

// arrtext fonksiyonu diziyi metin dosyasına dönüştürür
void arrtext(const char *filename, int **data, int rows, int cols) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Dosya acilamadı");
        return;
    }
    
    // Dizinin adını ve kayıt sayısını yaz
    fprintf(file, "# Kayitlar: %d\n", rows);
    
    // Anahtar ifadelerini otomatik olarak oluştur
    fprintf(file, "{ ");
    for (int i = 0; i < cols; i++) { // Dinamik sütun sayısı
        fprintf(file, "Sutun%d", i + 1);
        if (i < cols - 1) {
            fprintf(file, ", ");
        }
    }
    fprintf(file, " }\n");
    
    for (int i = 0; i < rows; i++) {
        // Her dizi kaydını belirtilen formatta yazdır
        fprintf(file, "[");
        for (int j = 0; j < cols; j++) { // Dinamik sütun sayısı
            fprintf(file, "%d", data[i][j]); // Dizi elemanına erişim
            if (j < cols - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "]\n");
    }
    
    fclose(file);
}

// textarr fonksiyonu metin dosyasını okuyup diziye çevirir
void textarr(const char *filename, int ***data, int *rows, int *cols) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Dosya acilamadi");
        return;
    }
    
    char line[256];
    *rows = 0;
    *cols = 0; // Başlangıçta sütun sayısını sıfırla

    // İlk iki satırı atla (Kayıtlar ve Anahtarlar)
    fgets(line, sizeof(line), file); // # Kayıtlar: ...
    fgets(line, sizeof(line), file); // { Sutun1, Sutun2, Sutun3 }

    // Kayıtları oku
    while (fgets(line, sizeof(line), file)) { // Tüm satırları oku
        if (line[0] == '[') {
            // Satırdaki elemanları ayrıştır
            char *token = strtok(line, "[,]");
            int count = 0;
            int *rowData = malloc(10 * sizeof(int)); // Geçici dizi
            while (token != NULL) {
                if (count > 0) { // İlk elemanı atla
                    rowData[count - 1] = atoi(token); // Elemanı diziye ekle
                }
                token = strtok(NULL, "[,]");
                count++;
            }
            if (*cols == 0) {
                *cols = count - 1; // Sütun sayısını güncelle
            }
            *data = realloc(*data, (*rows + 1) * sizeof(int*)); // Dinamik bellek ayır
            (*data)[*rows] = rowData; // Geçici diziyi kaydet
            (*rows)++;
        }
    }
    
    fclose(file);
}
// Dizi boyutunu ve anahtarlarını otomatik olarak çıkaran fonksiyon
void processArray(int **data, int rows, int cols) {
    const char *filename = "output.arr";
    
    // Diziyi dosyaya yaz
    arrtext(filename, data, rows, cols);
    
    // Dosyayı oku ve içeriği yazdır
    int **loadedData = NULL; // Yüklenen veriler için geçici dizi
    int loadedRows = 0;
    textarr(filename, &loadedData, &loadedRows, &cols); // Dosyadan verileri yükle

    // Yüklenen verileri istenen formatta ekrana yazdır
    printf("Yuklenen Veriler:\n");
    printf("{\n");
    for (int i = 0; i < loadedRows; i++) {
        printf("  {");
        for (int j = 0; j < cols; j++) {
            printf("%d", loadedData[i][j]);
            if (j < cols - 1) {
                printf(", ");
            }
        }
        printf("}");
        if (i < loadedRows - 1) {
            printf(",\n");
        }
    }
    printf("\n}\n");

    // Belleği serbest bırak
    for (int i = 0; i < loadedRows; i++) {
        free(loadedData[i]); // Yüklenen veriler için ayrılan bellek
    }
    free(loadedData); // Belleği serbest bırak
}

// Test için ana fonksiyon
int main() {
     // Dizi tanımlamaları
    int rows1 = 2, cols1 = 4; // dizi1 için boyutlar
    int dizi1[2][4] = { { 1, 2, 3, 8 }, { 4, 5, 6, 5 } };
    
    // Dizi işleme
    int **data1 = malloc(rows1 * sizeof(int*));
    for (int i = 0; i < rows1; i++) {
        data1[i] = malloc(cols1 * sizeof(int));
        memcpy(data1[i], dizi1[i], cols1 * sizeof(int));
    }
    processArray(data1, rows1, cols1);
    /*

    int rows2 = 2, cols2 = 3; // dizi2 için boyutlar
    int dizi2[2][3] = { { 1, 2, 3 }, { 4, 5, 0 } }; 
    

    int **data2 = malloc(rows2 * sizeof(int*));
    for (int i = 0; i < rows2; i++) {
        data2[i] = malloc(cols2 * sizeof(int));
        memcpy(data2[i], dizi2[i], cols2 * sizeof(int));
    }
    processArray(data2, rows2, cols2);
    */
    // Kullanıcıdan bir tuşa basmasını bekle
    printf("Devam etmek icin ENTERa basin...\n");

    getchar(); // Kullanıcıdan bir tuş girişi bekler
    
    return 0;
}