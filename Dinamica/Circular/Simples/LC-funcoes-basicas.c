#include <stdio.h>
#include <stdlib.h>

typedef struct sNode {
    int info;              // Informacoes
    struct sNode *next;    // Ponteiro que armazena o endereco do proximo no
} NODE;

void inicializar(NODE **node) {
    *node = NULL;
}

NODE* getnode() {
    return (NODE *)malloc(sizeof(NODE));
}

void freenode(NODE *node) {
    free(node);
}

int vazia(NODE *node) {
    return node == NULL;
}

void inserir_inicio(NODE **node, int elem) {
    NODE *new_node = getnode();
    if (!vazia(new_node)) {
        new_node->info = elem;
        if (vazia(*node)) {
            new_node->next = new_node;
            *node = new_node;
        } else {
            new_node->next = (*node)->next;
            (*node)->next = new_node;
        }
        printf("\n Noh [%d] alocado com sucesso!", elem);
    } else {
        printf("\n Erro na alocacao do no.");
    }
}

void inserir_fim(NODE **node, int elem) {
    NODE *new_node = getnode();
    if (!vazia(new_node)) {
        new_node->info = elem;
        if (vazia(*node)) {
            new_node->next = new_node;
            *node = new_node;
        } else {
            new_node->next = (*node)->next;
            (*node)->next = new_node;
            *node = new_node;
        }
        printf("\n Noh [%d] alocado com sucesso!", elem);
    } else {
        printf("\n Erro ao alocar o Noh.");
    }
}

void remover_inicio(NODE **node) {
    if (!vazia(*node)) {
        NODE *aux = (*node)->next;
        if (*node == (*node)->next) {
            *node = NULL;
        } else {
            (*node)->next = aux->next;
        }
        printf("\n Noh [%d] foi removido com sucesso!", aux->info);
        freenode(aux);
    } else {
        printf("\n ERRO - Lista vazia!");
    }
}

void remover_fim(NODE **node) {
    if (vazia(*node)) {
        printf("\n Erro - Lista vazia!");
        return;
    }
    NODE *aux = *node;
    if ((*node)->next == *node) {
        printf("\n Noh [%d] foi removido com sucesso!", aux->info);
        freenode(*node);
        *node = NULL;
    } else {
        while (aux->next != *node) {
            aux = aux->next;
        }
        NODE *removido = aux->next;
        aux->next = (*node)->next;
        *node = aux;
        printf("\n Noh [%d] foi removido com sucesso!", removido->info);
        freenode(removido);
    }
}

void exibir(NODE *node) {
    if (!vazia(node)) {
        NODE *atual = node->next;
        printf("Lista: ");
        do {
            printf("[%d] -> ", atual->info);
            atual = atual->next;
        } while (atual != node->next);
        printf("NULL\n");
    } else {
        printf("\n Erro - Lista Vazia!");
    }
}

int pesquisar_elemento(NODE *node, int elem) {
    NODE *aux = node;
    int retorno = -1;
    if (vazia(aux)) {
        printf("\n ERRO - Lista Vazia.");
    } else {
        do {
            if (aux->info == elem) {
                retorno = aux->info;
                break;
            }
            aux = aux->next;
        } while (aux != node);
    }
    return retorno;
}

int ler_elemento() {
    int elem;
    printf("\n Digite um numero inteiro: ");
    scanf("%d", &elem);
    return elem;
}

int menu() {
    int op;
    printf("\n\n=================== [MENU PRINCIPAL] ===================");
    printf("\n FUNCOES DE INSERCAO");
    printf("\n [1] - Inserir no inicio.");
    printf("\n [2] - Inserir no Fim.");
    printf("\n\n FUNCOES DE REMOCAO");
    printf("\n [3] - Remover do Inicio.");
    printf("\n [4] - Remover do Fim.");
    printf("\n\n OUTROS");
    printf("\n [5] - Exibir Lista.");
    printf("\n [6] - Pesquisar um elemento.");
    printf("\n [0] - Finalizar.");
    printf("\n========================================================\n\n");
    printf(" Insira uma opcao: ");
    scanf("%d", &op);
    return op;
}

int main() {
    NODE *node;
    int op, retorno;
    inicializar(&node);
    do {
        op = menu();
        switch (op) {
        case 0:
            printf("\nFim do programa.");
            break;
        case 1:
            inserir_inicio(&node, ler_elemento());
            break;
        case 2:
            inserir_fim(&node, ler_elemento());
            break;
        case 3:
            remover_inicio(&node);
            break;
        case 4:
            remover_fim(&node);
            break;
        case 5:
            exibir(node);
            break;
        case 6:
            retorno = pesquisar_elemento(node, ler_elemento());
            if (retorno != -1) {
                printf("\n Valor encontrado: %d", retorno);
            } else {
                printf("\n Valor nao encontrado.");
            }
            break;
        default:
            printf("\nOpcao invalida!");
            break;
        }
    } while (op != 0);

    while (!vazia(node)) {
        remover_inicio(&node);
    }

    return 0;
}
