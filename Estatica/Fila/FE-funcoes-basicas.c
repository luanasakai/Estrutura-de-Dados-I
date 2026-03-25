#include <stdio.h>
#define TF 4

typedef struct Fila {
    int vetor[TF];
    int inicio, fim;
} Fila;

void inicializar(Fila *fila) {
    fila->inicio = TF - 1;
    fila->fim = TF - 1;
}

int vazia(Fila *fila) {
    if (fila->fim == fila->inicio)
        return 1;
    return 0;    
}

int cheia(Fila *fila) {
    // TF = 4  cheia -> 3 
    // ((rear+1) % size == front))
    if ((fila->fim + 1) % TF == fila->inicio)
        return 1;
    return 0;
}

void enfileirar(Fila *fila, int num) {
    if (cheia(fila)) {
        printf("\n Fila cheia! nao eh possivel inserir elementos.\n");
        return;
    } else {
        fila->fim = (fila->fim + 1) % TF;
        fila->vetor[fila->fim] = num;  
    }
}

int desenfileirar(Fila *fila) {
    if (vazia(fila)) {
        printf("\n Fila vazia! nao ha elementos para remover.\n");
        return -1; 
    } else {
        fila->inicio = (fila->inicio + 1) % TF;
        return fila->vetor[fila->inicio];
    }
}

void imprimir_fila(Fila *fila) {
    if (vazia(fila)) {
        printf("\n Fila vazia! nao ha elementos para imprimir.\n");
        return;
    }

    printf("\n Fila Atual: ");
    int i = (fila->inicio + 1) % TF;
    while (i != (fila->fim + 1) % TF) {
        printf(" [%d] ", fila->vetor[i]);
        i = (i + 1) % TF;
    }
    printf("\n");
}

int ler_elemento(){
    int num;

    printf("\n Insira um numero inteiro: ");
    scanf("%d", &num);

    return num;
}

int menu(){
    int op=0;

    printf("\n ================= [FILA ESTATICA] =================");
    printf("\n [1] - Enfileirar elemento.");
    printf("\n [2] - Desenfileirar elemento.");
    printf("\n [3] - Imprimir elementos.");
    printf("\n [0] - Sair.");
    printf("\n ===================================================");
    printf("\n A seguir, insira uma opcao: ");
    scanf("%d", &op);

    return op;
}

int main() {
    Fila fila;
    printf("\n Inicializando a fila...");
    inicializar(&fila);

    int op;

    do{
        op = menu();
        switch (op){
        case 1:
            enfileirar(&fila, ler_elemento());
            printf("\n Elemento enfileirado com sucesso!");
            break;

        case 2:
            desenfileirar(&fila);
            printf("\n Elemento desenfileirado com sucesso!");
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
