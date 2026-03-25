#include <stdio.h>
#define TF 4

typedef struct sPilha {
    int topo;
    int vetor[TF];
} PILHA;

void inicializar(PILHA *pilha) {
    pilha->topo = -1;
}

int vazia(PILHA *pilha) {
    if (pilha->topo == -1)
        return 1;
    return 0;
}

int cheia(PILHA *pilha) {
    if ((pilha->topo + 1) == TF)
        return 1;
    return 0;
}

void inserir_topo(PILHA *pilha, int elem) {
    if (cheia(pilha)) {
        printf("\n Pilha cheia!\n");
    } else {
        pilha->topo += 1;
        pilha->vetor[pilha->topo] = elem;
        printf("\n Elemento inserido com sucesso!.\n");
    }
}

int remover_topo(PILHA *pilha) {
    int elem;

    if (vazia(pilha)) {
        printf("\n Pilha vazia!\n");
        return -1;  // Retorno para indicar falha
    } else {
        elem = pilha->vetor[pilha->topo];
        pilha->topo -= 1;
        return elem;
    }
}

void imprimir_elementos(PILHA pilha) {
    int i;

    if (vazia(&pilha)) {
        printf("\n Pilha vazia!\n");
    } else {
        printf("\n [PILHA] \n");
        for (i = pilha.topo; i >= 0; i--) {
            printf(" [%d] \n", pilha.vetor[i]);
        }
    }
}

int ler_elemento() {
    int num;
    printf("\n Insira um numero inteiro: ");
    scanf("%d", &num);

    return num;
}

int menu() {
    int op;

    printf("\n\n ================= [MENU] =================");
    printf("\n [1] - Inserir um elemento.");
    printf("\n [2] - Remover um elemento.");
    printf("\n [3] - Imprimir todos os elementos.");
    printf("\n [0] - Sair.");
    printf("\n =========================================");
    printf("\n A seguir, insira uma das opcoes: ");
    scanf("%d", &op);

    return op;
}

int main() {
    int elem;
    PILHA pilha;

    inicializar(&pilha);
    int op;

    do {
        op = menu();
        switch (op) {
            case 1:
                inserir_topo(&pilha, ler_elemento());
                imprimir_elementos(pilha);
                break;

            case 2:
                elem = remover_topo(&pilha);
                if (elem != -1) {
                    printf("\n Elemento removido: [%d]\n", elem);
                    imprimir_elementos(pilha);
                }
                break;

            case 3:
                imprimir_elementos(pilha);
                break;

            case 0:
                printf("\n Fim do programa.\n");
                break;

            default:
                printf("\n Opcao invalida! Tente novamente.\n");
        }

    } while (op != 0);

    return 0;
}
