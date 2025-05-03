#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long int timestamp;
    char id_sensor[20];
    float valor;
} Leitura;

void bubble_sort(Leitura *leituras, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (leituras[j].timestamp > leituras[j + 1].timestamp) {
                Leitura temp = leituras[j];
                leituras[j] = leituras[j + 1];
                leituras[j + 1] = temp;
            }
        }
    }
}

int main() {
    
    FILE *arquivo = fopen("leituras.txt", "r");

    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo!\n");
        return 1;
    }

    Leitura leituras[10000];
    int total = 0;

    while (fscanf(arquivo, "%ld %s %f", &leituras[total].timestamp, leituras[total].id_sensor, &leituras[total].valor) == 3) {
        total++;
    }
    fclose(arquivo);

    char sensores[100][20];
    int num_sensores = 0;

    for (int i = 0; i < total; i++) {
        int encontrado = 0;
        for (int j = 0; j < num_sensores; j++) {
            if (strcmp(leituras[i].id_sensor, sensores[j]) == 0) {
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            strcpy(sensores[num_sensores++], leituras[i].id_sensor);
        }
    }

    for (int i = 0; i < num_sensores; i++) {
        Leitura sensor_leituras[10000];
        int count = 0;

        for (int j = 0; j < total; j++) {
            if (strcmp(leituras[j].id_sensor, sensores[i]) == 0) {
                sensor_leituras[count++] = leituras[j];
            }
        }

        bubble_sort(sensor_leituras, count);

        char nome_arquivo[30];
        sprintf(nome_arquivo, "%s.txt", sensores[i]);

        FILE *arquivo = fopen(nome_arquivo, "w");
        if (arquivo == NULL) {
            printf("Erro ao criar arquivo para o sensor %s\n", sensores[i]);
            continue;
        }

        for (int j = 0; j < count; j++) {
            fprintf(arquivo, "%ld %s %.2f\n", sensor_leituras[j].timestamp, sensor_leituras[j].id_sensor, sensor_leituras[j].valor);
        }
        fclose(arquivo);
    }

    printf("Organizacao realizada!\n");
    return 0;
}
