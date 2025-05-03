#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    long int timestamp;
    char id_sensor[20];
    float valor;
} Leitura;

long int capturar_timestamp_valido() {
    int dia, mes, ano, hora, min, seg;
    struct tm t;

    printf("Digite a data e hora (dd mm aaaa hh mm ss): ");
    scanf("%d %d %d %d %d %d", &dia, &mes, &ano, &hora, &min, &seg);

    t.tm_year = ano - 1900;
    t.tm_mon = mes - 1;
    t.tm_mday = dia;
    t.tm_hour = hora;
    t.tm_min = min;
    t.tm_sec = seg;
    t.tm_isdst = -1;

    return mktime(&t);
}

int busca_binaria(Leitura *leituras, int n, long int timestamp) {
    int esquerda = 0, direita = n - 1, melhor = 0;
    long int diff_melhor = LONG_MAX;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        long int diff = labs(leituras[meio].timestamp - timestamp);

        if (diff < diff_melhor) {
            melhor = meio;
            diff_melhor = diff;
        }

        if (leituras[meio].timestamp < timestamp) {
            esquerda = meio + 1;
        } else if (leituras[meio].timestamp > timestamp) {
            direita = meio - 1;
        } else {
            return meio;
        }
    }

    return melhor;
}

int main() {
    char sensor[20];
    char nome_arquivo[30];

    printf("Sensores disponiveis: TEMP, PRES, VIBR, UMID, FLUX\n");
    printf("Informe o nome do sensor desejado: ");
    scanf("%s", sensor);

 

    snprintf(nome_arquivo, sizeof(nome_arquivo), "%s.txt", sensor);
    printf("Abrindo: %s\n", nome_arquivo); 

    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Nao foi possível abrir o arquivo do sensor %s.\n", sensor);
        return 1;
    }

    Leitura leituras[1000];
    int total = 0;

    while (fscanf(arquivo, "%ld %s %f", &leituras[total].timestamp, leituras[total].id_sensor, &leituras[total].valor) == 3) {
        total++;
    }
    fclose(arquivo);

    long int timestamp_consulta = capturar_timestamp_valido();

    int indice = busca_binaria(leituras, total, timestamp_consulta);

    printf("Leitura mais proxima e:\n");
    printf("Timestamp: %ld\nSensor: %s\nValor: %.2f\n",
           leituras[indice].timestamp, leituras[indice].id_sensor, leituras[indice].valor);

    return 0;
}
