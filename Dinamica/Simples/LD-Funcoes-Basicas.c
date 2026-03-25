#include <stdio.h>
#include <stdlib.h>

typedef struct sNode {
    int valor;
    struct sNode *next;
} NODE;

// Cria um novo nó
NODE* createnode(int valor) {
    NODE* newNode = (NODE*) malloc(sizeof(NODE));
    if (newNode != NULL) {
        newNode->valor = valor;
        newNode->next = NULL;
    }
    return newNode;
}

// Inicializa lista
NODE* inicializar() {
    return NULL;
}

int vazia(NODE *node) {
    return (node == NULL);
}

// Inserir no início
NODE* inserir_inicio(NODE *node, int valor) {
    NODE *new_node = createnode(valor);
    if (new_node != NULL) {
        new_node->next = node;
        printf("\nNoh [%d] alocado com sucesso!", new_node->valor);
        return new_node;
    } else {
        printf("\nERRO - O noh não foi alocado corretamente.");
        return node;
    }
}

// Inserir no fim
NODE* inserir_fim(NODE *node, int valor) {
    NODE* new_node = createnode(valor);
    if (new_node != NULL) {
        if (vazia(node)) {
            printf("\nNoh [%d] alocado com sucesso!", new_node->valor);
            return new_node;
        }
        NODE *atual = node;
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = new_node;
        printf("\nNoh [%d] alocado com sucesso!", new_node->valor);
    } else {
        printf("\nERRO - O noh nao foi alocado adequadamente.");
    }
    return node;
}

// Inserir em posição
NODE* inserir_em_uma_posicao(NODE *node, int posi, int valor) {
    if (posi < 1) return node;
    NODE* aux = createnode(valor);
    if (aux == NULL) return node;

    if (posi == 1) {
        aux->next = node;
        return aux;
    }

    NODE* ante = node;
    for (int count = 1; count < posi - 1 && ante != NULL; count++) {
        ante = ante->next;
    }

    if (ante != NULL) {
        aux->next = ante->next;
        ante->next = aux;
        printf("\nNoh [%d] alocado com sucesso!", aux->valor);
    } else {
        free(aux);
    }
    return node;
}

// Remover do início
NODE* remover_do_inicio(NODE* inicio) {
    if (!vazia(inicio)) {
        NODE* aux = inicio;
        inicio = inicio->next;
        printf("\nNoh [%d] removido com sucesso!", aux->valor);
        free(aux);
    }
    return inicio;
}

// Remover do fim
NODE* remover_do_fim(NODE* node) {
    if (!vazia(node)) {
        if (node->next == NULL) {
            printf("\nNoh [%d] removido com sucesso!", node->valor);
            free(node);
            return NULL;
        }
        NODE* antepenultimo = node;
        while (antepenultimo->next->next != NULL) {
            antepenultimo = antepenultimo->next;
        }
        printf("\nNoh [%d] removido com sucesso!", antepenultimo->next->valor);
        free(antepenultimo->next);
        antepenultimo->next = NULL;
    }
    return node;
}

// Remover de posição
NODE* remover_de_posicao(NODE* inicio, int posi) {
    if (!vazia(inicio) && posi >= 1) {
        if (posi == 1) {
            return remover_do_inicio(inicio);
        }
        NODE* atual = inicio;
        for (int i = 1; i < posi - 1 && atual != NULL; i++) {
            atual = atual->next;
        }
        if (atual != NULL && atual->next != NULL) {
            NODE* aux = atual->next;
            atual->next = aux->next;
            printf("\nNoh [%d] removido com sucesso!", aux->valor);
            free(aux);
        }
    }
    return inicio;
}

// Buscar valor
int procurar_valor(NODE* node, int target) {
    while (node != NULL) {
        if (node->valor == target) return 1;
        node = node->next;
    }
    return 0;
}

// Imprimir lista
void imprimir_lista(NODE* node) {
    while (node != NULL) {
        printf("%d -> ", node->valor);
        node = node->next;
    }
    printf("NULL\n");
}

// Ler elemento
int ler_elemento(int tipo) {
    int elem;
    if(tipo == 1){
        printf("\nInsira um numero inteiro: ");
        scanf("%d", &elem);
    } else {
        printf("\nInsira a posicaoo desejada: ");
        scanf("%d", &elem);
    }
    return elem;
}

// Menu
int menu() {
    int op;
    printf("\n\n=================== [MENU PRINCIPAL] ===================");
    printf("\n[FUNCOES DE INSERCAO]");
    printf("\n[1] - Inserir no início");
    printf("\n[2] - Inserir no fim");
    printf("\n[3] - Inserir em uma posição");
    printf("\n\n[FUNCOES DE REMOCAO]");
    printf("\n[4] - Remover do início");
    printf("\n[5] - Remover do fim");
    printf("\n[6] - Remover de uma posição");
    printf("\n\n[OUTRAS]");
    printf("\n[7] - Exibir lista");
    printf("\n[0] - Finalizar");
    printf("\n========================================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &op);
    return op;
}

int main() {
    NODE *node = inicializar();
    int op;

    do {
        op = menu();
        switch (op) {
        case 1:
            node = inserir_inicio(node, ler_elemento(1));
            break;
        case 2:
            node = inserir_fim(node, ler_elemento(1));
            break;
        case 3:
            node = inserir_em_uma_posicao(node, ler_elemento(0), ler_elemento(1));
            break;
        case 4:
            node = remover_do_inicio(node);
            break;
        case 5:
            node = remover_do_fim(node);
            break;
        case 6:
            node = remover_de_posicao(node, ler_elemento(0));
            break;
        case 7:
            imprimir_lista(node);
            break;
        case 0:
            printf("\nFim do programa.\n");
            break;
        default:
            printf("\nOpção inválida!");
            break;
        }
    } while (op != 0);

    // Liberação da memória
    while (!vazia(node)) {
        node = remover_do_inicio(node);
    }

    return 0;
}
