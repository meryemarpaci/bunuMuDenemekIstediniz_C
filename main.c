#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KARAKTER 15

char* dnmOneri(char kelime[]) {
    FILE *fp = fopen("kelime.txt", "r");

    if (fp == NULL) {
        printf("kelime.txt dosyasý okunamadi\n");
        return NULL;
    }

    int len = strlen(kelime);

    int sayac = 0;
    char satir[KARAKTER * len];
    
    if (fgets(satir, sizeof(satir), fp) == NULL) {
        printf("Dosya okuma hatasi\n");
        fclose(fp);
        return NULL;
    }
	
	//burasý vigulle ayrýlmýþ kelimeleri okumak icin
    char diziToken[KARAKTER][KARAKTER * len];
    char *token = strtok(satir, ",");

    while (token != NULL) {
        strcpy(diziToken[sayac], token);
        token = strtok(NULL, ",");
        sayac++;
    }

    int enYakinIndis;
    int yakinlik2 = 0;
	
	//harf harf okur benzerlik sayisini arttirir o indisi dondurur
    for (int i = 0; i < sayac; i++) {
        int yakinlik = 0;
        char geciciD[KARAKTER * len];
        strcpy(geciciD, diziToken[i]);

        for (int j = 0; j < len; j++) {
            if (geciciD[j] == kelime[j]) {
                yakinlik++;
            }
        }

        if (yakinlik > yakinlik2) {
            yakinlik2 = yakinlik;
            enYakinIndis = i;
        }
    }

    printf("\nsunu mu denemek istediniz : %s\n", diziToken[enYakinIndis]);

    // 
    char *a = (char *)malloc((len + 1) * sizeof(char));
    strcpy(a, diziToken[enYakinIndis]);

    fclose(fp);
    return a;
    free(a);
    //
}

int yerDegistirme(char kelime[], char *enYakinKelime) {
    if (strlen(kelime) == strlen(enYakinKelime)) {
        int kdizi1[26] = {0}; //ingiliz alfabesinde 26 harf var diye
        int kdizi2[26] = {0};

        for (int i = 0; i < strlen(kelime); i++) {
            kdizi1[kelime[i] - 'a']++;
        }

        for (int i = 0; i < strlen(enYakinKelime); i++) {
            kdizi2[enYakinKelime[i] - 'a']++;
        }

        for (int i = 0; i < 26; i++) {
            if (kdizi1[i] != kdizi2[i]) {
                return 0;
            }
        }
        return 1;
    } else {
        return 0;
    }
}

void eksikHarf(char kelime[25], char *enYakinKelime) {
    int len = strlen(kelime);
    for (int i = 0; i < len; i++) {
        if (enYakinKelime[i] != kelime[i]) {
            printf("Eksik harf: %c\n", enYakinKelime[i]);
            break;
        }
    }
}

int main() {
    char kelime[25];
    printf("\nAramak istediginiz kelimeyi giriniz : ");
    scanf("%s", kelime);

    if (strlen(kelime) >= 4) {
        char *enYakinKelime = dnmOneri(kelime);
        if (enYakinKelime != NULL) {
            if (strcmp(enYakinKelime, kelime) == 0) {
                printf("\ngirdiginiz kelimeler ayný");
            } else if (yerDegistirme(kelime, enYakinKelime) == 1) {
                printf("\nharflerin yerleri degismis");
            } else {
                eksikHarf(kelime, enYakinKelime);
            }

            free(enYakinKelime);
        }
    } else {
        printf("\nGirdiginiz kelime en az 4 harfli olmalidir.\n");
    }

    return 0;
}

