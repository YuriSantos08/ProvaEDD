#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

time_t capturar_timestamp_valido() {
    int dia, mes, ano, hora, min, seg;
    struct tm t;

    while (1) {
        printf("Digite a data e hora (dd mm aaaa hh mm ss): ");
        if (scanf("%d %d %d %d %d %d", &dia, &mes, &ano, &hora, &min, &seg) != 6) {
            while (getchar() != '\n');
            printf("Entrada inválida. Tente novamente.\n");
            continue;
        }

        t.tm_year = ano - 1900;
        t.tm_mon = mes - 1;
        t.tm_mday = dia;
        t.tm_hour = hora;
        t.tm_min = min;
        t.tm_sec = seg;
        t.tm_isdst = -1;

        time_t timestamp = mktime(&t);
        if (timestamp == -1) {
            printf("Data inválida. Tente novamente.\n");
        } else {
            return timestamp;
        }
    }

}

time_t gerar_timestamp_aleatorio(int dia, int mes, int ano) {
    struct tm t;
    time_t timestamp_inicial, timestamp_final;
    
    t.tm_year = ano - 1900;
    t.tm_mon = mes - 1;
    t.tm_mday = dia;
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    t.tm_isdst = -1;
    
    timestamp_inicial = mktime(&t);
    if (timestamp_inicial == -1) {
        printf("Data inválida.\n");
        return -1;
    }

    t.tm_hour = 23;
    t.tm_min = 59;
    t.tm_sec = 59;
    
    timestamp_final = mktime(&t);
    if (timestamp_final == -1) {
        printf("Data inválida.\n");
        return -1;
    }

    time_t timestamp_aleatorio = timestamp_inicial + rand() % (timestamp_final - timestamp_inicial + 1);
    
    return timestamp_aleatorio;
}

int main () {

int dia , mes ,ano , hora , min ,seg;
printf("Digite a data e hora (dd mm aaaa hh mm ss): ");
scanf("%d %d %d %d %d %d", &dia, &mes, &ano, &hora, &min, &seg);

char* sensores[5] = {"TEMP", "PRES", "VIBR", "UMID", "FLUX"};
 FILE *arquivo;
 arquivo = fopen("leituras.txt" , "w");
 if (arquivo == NULL)
 {
    printf("Nao foi possivel abrir o arquivo!");
    return 1;
 }
 srand(time(NULL));

for (int i = 0; i < 5; i++)
{
for (int j = 0; j < 1000; j++)
{
time_t ts = gerar_timestamp_aleatorio(dia, mes, ano);
float valor = (float)(rand()%1000)/10.0;
fprintf(arquivo,"%ld %s %.2f\n",ts,sensores[i],valor);
}
}
fclose(arquivo);

 printf("Arquivo de leitura gerado!\n");
 
    return 0;
}
