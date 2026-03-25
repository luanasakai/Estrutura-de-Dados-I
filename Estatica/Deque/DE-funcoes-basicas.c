#include <stdio.h>
#define TF 4

typedef struct sDeque {
    int vetor[TF];
    int inicio;
    int fim;
} DEQUE;

void inicializar(DEQUE *deque) {
    deque->inicio = 0;
    deque->fim = 0;
}


int cheia(DEQUE *deque) {
    return ((deque->fim + 1) % TF == deque->inicio);
}

int vazia(DEQUE *deque) {
    return (deque->fim == deque->inicio);
}


void inserir_inicio(DEQUE *deque, int num) {
    if (cheia(deque)) {
        printf("\nDeque cheio! Nao eh possivel adicionar.\n");
    } else {
        deque->inicio = (deque->inicio - 1 + TF) % TF;
        deque->vetor[deque->inicio] = num;
        printf("\nElemento %d inserido no incio.\n", num);
    }
}

void inserir_fim(DEQUE *deque, int num) {
    if (cheia(deque)) {
        printf("\nDeque cheio! Nao eh possivel adicionar.\n");
    } else {
        deque->vetor[deque->fim] = num;
        deque->fim = (deque->fim + 1) % TF;
        printf("\nElemento %d inserido no fim.\n", num);
    }
}

// Remove elemento do início do deque
int remover_inicio(DEQUE *deque) {
    if (vazia(deque)) {
        printf("\nDeque vazio! Nao ha elementos para remover.\n");
        return -1;
    } else {
        int elem = deque->vetor[deque->inicio];
        deque->inicio = (deque->inicio + 1) % TF;
        printf("\nElemento %d removido do inicio.\n", elem);
        return elem;
    }
}

int remover_fim(DEQUE *deque) {
    if (vazia(deque)) {
        printf("\nDeque vazio! Nao ha elementos para remover.\n");
        return -1;
    } else {
        deque->fim = (deque->fim - 1 + TF) % TF;
        int elem = deque->vetor[deque->fim];
        printf("\nElemento %d removido do fim.\n", elem);
        return elem;
    }
}

void imprimir(DEQUE *deque) {
    if (vazia(deque)) {
        printf("\nDeque vazio! Nao ha elementos para imprimir.\n");
    } else {
        printf("\nElementos do deque: ");
        int i = deque->inicio;
        while (i != deque->fim) {
            printf(" [%d] ", deque->vetor[i]);
            i = (i + 1) % TF;
        }
        printf("\n");
    }
}

int menu() {
    int op;
    printf("\n========= [MENU DEQUE ESTATICO] =========");
    printf("\n[1] - Inserir no início");
    printf("\n[2] - Inserir no fim");
    printf("\n[3] - Remover do início");
    printf("\n[4] - Remover do fim");
    printf("\n[5] - Imprimir deque");
    printf("\n[0] - Sair");
    printf("\n==========================================");
    printf("\nEscolha uma opção: ");
    scanf("%d", &op);
    return op;
}

int main() {
    DEQUE deque;
    inicializar(&deque);

    int op, num;
    do {
        op = menu();
        switch (op) {
            case 1:
                printf("Digite um número: ");
                scanf("%d", &num);
                inserir_inicio(&deque, num);
                break;
            case 2:
                printf("Digite um número: ");
                scanf("%d", &num);
                inserir_fim(&deque, num);
                break;
            case 3:
                remover_inicio(&deque);
                break;
            case 4:
                remover_fim(&deque);
                break;
            case 5:
                imprimir(&deque);
                break;
            case 0:
                printf("\nEncerrando programa...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (op != 0);

    return 0;
}
