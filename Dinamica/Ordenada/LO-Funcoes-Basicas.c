#include <stdio.h>
#include <stdlib.h>

typedef struct sNode {
    int valor; // indicates the value stored in the node
    struct sNode *next; // a pointer that will store the address of the next node in the sequence
} NODE;

// Reserve a memory location
NODE* getnode(int valor) {
    NODE* newNode = (NODE*) malloc(sizeof(NODE));
    if (newNode != NULL) {
        newNode->valor = valor;
        newNode->next = NULL;
    }
    return newNode;
}

// Initialize a linked list
NODE* init() {
    return NULL;
}

int vazia(NODE *node) {
    return (node == NULL);
}

// Insert at the head
NODE* inserir_inicio(NODE *node, int valor) {
    NODE *new_node = getnode(valor);
    if (new_node != NULL) {
        new_node->next = node;
        printf("\n Noh [%d] alocado com sucesso!", new_node->valor);
        return new_node;
    } else {
        printf("\nERRO - O noh nao foi alocado corretamente.");
        return node;
    }
}

// Insert at the end
NODE* inserir_fim(NODE *node, int valor) {
    NODE* new_node = getnode(valor);
    if (new_node != NULL) {
        if (vazia(node)) {
            return new_node;
        }
        NODE *node_atual = node;
        while (node_atual->next != NULL) {
            node_atual = node_atual->next;
        }
        node_atual->next = new_node;
        printf("\n Noh [%d] alocado com sucesso!", new_node->valor);
    } else {
        printf("\nERRO - O noh nao foi alocado adequadamente.");
    }
    return node;
}

// Insert at a given position
NODE* inserir_em_uma_posicao(NODE *node, int posi, int valor) {
    if (posi < 1) return node;
    NODE* aux = getnode(valor);
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
    } else {
        free(aux);
    }
    return node;
}

// Delete from the head
NODE* remover_do_inicio(NODE* inicio) {
    if (!vazia(inicio)) {
        NODE* aux = inicio;
        inicio = inicio->next;
        printf("\nNoh [%d] removido com sucesso!", aux->valor);
        free(aux);
    }
    return inicio;
}

// Delete from the end
NODE* remover_do_fim(NODE* node) {
    if (!vazia(node)) {
        if (node->next == NULL) {
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

// Delete from a given position
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
            free(aux);
        }
    }
    return inicio;
}

// Search for a value
int procurar_valor(NODE* node, int target) {
    if (!vazia(node)) {
        while (node != NULL) {
            if (node->valor == target) {
                return 1;
            }
            node = node->next;
        }
    }
    return 0;
}

void imprimir_lista(NODE* node) {
    while (node != NULL) {
        printf("%d -> ", node->valor);
        node = node->next;
    }
    printf("NULL\n");
}

// Insert in sorted order
void inserir_ordenado(NODE** inicio, int valor) {
    NODE* new_node = getnode(valor);
    if (new_node == NULL) {
        printf("\nERRO - O noh nao foi alocado corretamente.");
        return;
    }
    if (vazia(*inicio) || valor < (*inicio)->valor) {
        new_node->next = *inicio;
        *inicio = new_node;
        return;
    }

    NODE* atual = *inicio;
    while (atual->next != NULL && atual->next->valor < valor) {
        atual = atual->next;
    }
    new_node->next = atual->next;
    atual->next = new_node;
    printf("\n Noh [%d] alocado com sucesso!", new_node->valor);
}

// Remove a specific value from the list
NODE* remover_valor(NODE* inicio, int valor) {
    if (vazia(inicio)) return inicio;
    if (inicio->valor == valor) {
        NODE* temp = inicio;
        inicio = inicio->next;
        free(temp);
        return inicio;
    }
    
    NODE* atual = inicio;
    while (atual->next != NULL && atual->next->valor != valor) {
        atual = atual->next;
    }

    if (atual->next != NULL) {
        NODE* temp = atual->next;
        atual->next = atual->next->next;
        free(temp);
    }
    return inicio;
}

// Menu
int menu() {
    int op;
    printf("\n\n=================== [MENU PRINCIPAL] ===================");
    printf("\n [FUNCOES DE INSERCAO]");
    printf("\n [1] - Inserir no inicio");
    printf("\n [2] - Inserir no fim");
    printf("\n [3] - Inserir em uma posicao");
    printf("\n [4] - Inserir ordenado");
    printf("\n\n [FUNCOES DE REMOCAO]");
    printf("\n [5] - Remover do inicio");
    printf("\n [6] - Remover do fim");
    printf("\n [7] - Remover de uma posicao");
    printf("\n [8] - Remover valor especifico");
    printf("\n\n [OUTROS]");
    printf("\n [9] - Procurar valor");
    printf("\n [10] - Exibir lista");
    printf("\n [0] - Finalizar");
    printf("\n========================================================\n");
    printf("A seguir, escolha uma opcao: ");
    scanf("%d", &op);
    return op;
}

int main() {
    NODE* lista = init();
    int op, valor, posi;
    do {
        op = menu();
        switch(op) {
            case 1:
                printf("Digite um valor: ");
                scanf("%d", &valor);
                lista = inserir_inicio(lista, valor);
                break;
            case 2:
                printf("Digite um valor: ");
                scanf("%d", &valor);
                lista = inserir_fim(lista, valor);
                break;
            case 3:
                printf("Digite a posicao: ");
                scanf("%d", &posi);
                printf("Digite um valor: ");
                scanf("%d", &valor);
                lista = inserir_em_uma_posicao(lista, posi, valor);
                break;
            case 4:
                printf("Digite um valor: ");
                scanf("%d", &valor);
                inserir_ordenado(&lista, valor);
                break;
            case 5:
                lista = remover_do_fim(lista);
                break;
            case 6:
                printf("Digite a posicao: ");
                scanf("%d", &posi);
                lista = remover_de_posicao(lista, posi);
                break;
            case 7:
                lista = remover_do_inicio(lista);
                break;
            case 8:
                printf("Digite o valor a remover: ");
                scanf("%d", &valor);
                lista = remover_valor(lista, valor);
                printf("\nNoh removido com sucesso!");
            case 9:
                printf("Digite o valor a procurar: ");
                scanf("%d", &valor);
                if (procurar_valor(lista, valor)) {
                    printf("Valor encontrado na lista\n");
                } else {
                    printf("Valor nao encontrado\n");
                }
                break;
            case 10:
                imprimir_lista(lista);
                break;
            case 0:
                printf("Fim do programa\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    } while(op != 0);

    while (!vazia(lista)) {
        lista = remover_do_inicio(lista);
    }
    return 0;
}
