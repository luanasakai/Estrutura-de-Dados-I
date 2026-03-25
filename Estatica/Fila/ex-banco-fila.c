#include <stdio.h>
#include <stdlib.h>
#define TF 4

typedef struct {
    int hora_entrada;
    int minuto_entrada;
    int hora_atendimento;
    int minuto_atendimento;
} DATA;

typedef struct {
    DATA data[TF];
    int inicio;
    int fim;
} Fila;

void inicializar(Fila *fila) {
    fila->inicio = TF - 1;
    fila->fim = TF - 1;
}

int vazia(Fila *fila) {
    return (fila->fim == fila->inicio);
}

int cheia(Fila *fila) {
    return ((fila->fim + 1) % TF == fila->inicio);
}


DATA ler_data() {
    DATA d;

    printf("\n========== TICKET DE ENTRADA ===============\n");
    do {
        printf("Informe a hora de entrada (00 a 23): ");
        scanf("%d", &d.hora_entrada);
        if (d.hora_entrada < 0 || d.hora_entrada >= 24)
            printf("Hora inválida! Tente novamente.\n");
    } while (d.hora_entrada < 0 || d.hora_entrada >= 24);

    do {
        printf("Informe o minuto de entrada (00 a 59): ");
        scanf("%d", &d.minuto_entrada);
        if (d.minuto_entrada < 0 || d.minuto_entrada >= 60)
            printf("Minuto inválido! Tente novamente.\n");
    } while (d.minuto_entrada < 0 || d.minuto_entrada >= 60);

    printf("\n========== TICKET DE SAÍDA ===============\n");
    do {
        printf("Informe a hora de atendimento (00 a 23): ");
        scanf("%d", &d.hora_atendimento);
        if (d.hora_atendimento < 0 || d.hora_atendimento >= 24)
            printf("Hora inválida! Tente novamente.\n");
    } while (d.hora_atendimento < 0 || d.hora_atendimento >= 24);

    do {
        printf("Informe o minuto de atendimento (00 a 59): ");
        scanf("%d", &d.minuto_atendimento);
        if (d.minuto_atendimento < 0 || d.minuto_atendimento >= 60)
            printf("Minuto inválido! Tente novamente.\n");
    } while (d.minuto_atendimento < 0 || d.minuto_atendimento >= 60);

    printf("============================================\n");
    return d;
}

void enfileirar(Fila *fila) {
    if (cheia(fila)) {
        printf("\n Fila cheia! Não é possível inserir elementos.\n");
    } else {
        fila->fim = (fila->fim + 1) % TF;
        fila->data[fila->fim] = ler_data();
    }
}

DATA desenfileirar(Fila *fila) {
    DATA data = {0, 0, 0, 0};

    if (vazia(fila)) {
        printf("\n Fila vazia! Não há elementos para retirar.\n");
    } else {
        fila->inicio = (fila->inicio + 1) % TF;
        data = fila->data[fila->inicio];
    }
    return data;
}

double media_tempo(Fila *fila) {
    if (vazia(fila)) {
        printf("\n Fila vazia! Não há clientes para calcular o tempo médio.\n");
        return 0.0;
    }

    int i = (fila->inicio + 1) % TF;
    int total_tempo = 0, cont = 0;

    while (i != (fila->fim + 1) % TF) {
        int entrada_minutos = fila->data[i].hora_entrada * 60 + fila->data[i].minuto_entrada;
        int atendimento_minutos = fila->data[i].hora_atendimento * 60 + fila->data[i].minuto_atendimento;

        if (atendimento_minutos < entrada_minutos) {
            atendimento_minutos += 24 * 60;
        }

        total_tempo += (atendimento_minutos - entrada_minutos);
        cont++;
        i = (i + 1) % TF;
    }

    return (double)total_tempo / cont;
}

void imprimir_fila(Fila *fila)
{
    if (vazia(fila))
    {
        printf("\n Fila vazia! Não há elementos para imprimir.\n");
    }
    else
    {
        printf("\n Horário de entrada e atendimento dos clientes:\n");
        int i = (fila->inicio + 1) % TF;
        int cliente = 1;

        while (i != (fila->fim + 1) % TF)
        {
            int entrada_minutos = fila->data[i].hora_entrada * 60 + fila->data[i].minuto_entrada;
            int atendimento_minutos = fila->data[i].hora_atendimento * 60 + fila->data[i].minuto_atendimento;

            int dia_seguinte = (atendimento_minutos < entrada_minutos);

            printf("Cliente %d\nEntrada: %02d:%02d\nAtendimento: %02d:%02d%s\n\n",
                   cliente,
                   fila->data[i].hora_entrada, fila->data[i].minuto_entrada,
                   fila->data[i].hora_atendimento, fila->data[i].minuto_atendimento,
                   dia_seguinte ? " (dia seguinte)" : "");

            i = (i + 1) % TF;
            cliente++;
        }
        printf("\n Tempo medio de espera: %.2f minutos\n", media_tempo(fila));
    }
}

int menu(){
    int op=0;

    printf("\n ================= [FILA ESTATICA] =================");
    printf("\n [1] - Enfileirar cliente.");
    printf("\n [2] - Desenfileirar cliente.");
    printf("\n [3] - Imprimir clientes.");
    printf("\n [0] - Sair.");
    printf("\n ===================================================");
    printf("\n A seguir, insira uma opcao: ");
    scanf("%d", &op);

    return op;
}


int main() {
    Fila fila;
    inicializar(&fila);

    int op;

    do{
        op = menu();
        switch (op){
        case 1:
            enfileirar(&fila);
            printf("\n Cliente enfileirado com sucesso!");
            break;

        case 2:
            desenfileirar(&fila);
            printf("\n Cliente desenfileirado com sucesso!");
            break;

        case 3:
            imprimir_fila(&fila);
            break;

        case 0:
            printf("\n Saindo do programa...");
            break;
              
        default:
            printf("\n Opcao invalida!");
            break;
        }

    } while (op != 0);

    return 0;
}
