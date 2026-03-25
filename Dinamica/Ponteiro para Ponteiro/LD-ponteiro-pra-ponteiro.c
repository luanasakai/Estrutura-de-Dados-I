#include <stdio.h>
#include <stdlib.h>

typedef struct sNode {
    int valor;
    struct sNode *next;
} NODE;

NODE* createnode(int valor) {
    NODE* newNode = (NODE*) malloc(sizeof(NODE));
    if (newNode != NULL) {
        newNode->valor = valor;
        newNode->next = NULL;
    }
    return newNode;
}

NODE* inicializar() {
    return NULL;
}

int vazia(NODE *node) {
    return (node == NULL);
}

// Insere no inicio
void inserir_inicio(NODE **node, int valor) {
    NODE *new_node = createnode(valor);
    if (new_node != NULL) {
        new_node->next = *node; // O novo noh aponta para o inicio atual
        *node = new_node;       // Atualiza o inicio para o novo noh
        printf("\n Noh [%d] alocado com sucesso!", new_node->valor);
    } else {
        printf("\nERRO - O noh nao foi alocado corretamente.");
    }
}

// Insere no final
void inserir_fim(NODE **node, int valor) {
    NODE* new_node = createnode(valor);
    if (new_node != NULL) {
        if (vazia(*node)) {
            *node = new_node; // Se a lista esta vazia o novo noh se torna o inicio
        } else {
            NODE *node_atual = *node;
            while (node_atual->next != NULL) {
                node_atual = node_atual->next;
            }
            node_atual->next = new_node; // O ultimo noh aponta para o novo no
        }
        printf("\n Noh [%d] alocado com sucesso!", new_node->valor);
    } else {
        printf("\nERRO - O noh nao foi alocado adequadamente.");
    }
}

// Insere em uma posicao especifica
void inserir_em_uma_posicao(NODE **node, int posi, int valor) {
    NODE* aux = createnode(valor);
    if (aux != NULL && posi >= 1) {
        if (posi == 1) {
            aux->next = *node;
            *node = aux; // Novo noh se torna o inicio
        } else {
            NODE *ante = *node;
            for (int count = 1; count < posi - 1 && ante != NULL; count++) {
                ante = ante->next;
            }
            if (ante != NULL) {
                aux->next = ante->next;
                ante->next = aux;
            } else {
                free(aux); // Se a posicao for alem do fim libera o novo noh
                printf("\n ERRO - posicao invalida!");
                return;
            }
        }
        printf("\n Noh [%d] alocado com sucesso!", aux->valor);
    } else {
        printf("\n ERRO - alocacao mal sucedida ou posicao invalida!");
    }
}

// Remove do inicio
void remover_inicio(NODE **inicio) {
    if (!vazia(*inicio)) {
        NODE* aux = *inicio; // Armazena o primeiro noh
        *inicio = (*inicio)->next; // Atualiza o inicio da lista
        printf("\n Noh [%d] foi removido com sucesso!", aux->valor);
        free(aux); // Libera o primeiro noh
    } else {
        printf("\n ERRO - Lista Vazia!");
    }
}

void remover_fim(NODE **node) {
    if (!vazia(*node)) {
        if ((*node)->next == NULL) { // Apenas um elemento
            printf("\n Noh [%d] foi removido com sucesso!", (*node)->valor);
            free(*node);
            *node = NULL; // A lista fica vazia
        } else {
            NODE* antepenultimo = *node;
            while (antepenultimo->next->next != NULL) {
                antepenultimo = antepenultimo->next;
            }
            printf("\n Noh [%d] foi removido com sucesso!", antepenultimo->next->valor);
            free(antepenultimo->next); // Libera o ultimo noh
            antepenultimo->next = NULL; // Define o novo fim da lista
        }
    } else {
        printf("\n ERRO - Lista Vazia!");
    }
}

// Remove de uma posicao especifica
void remover_de_posicao(NODE **inicio, int posi) {
    if (!vazia(*inicio) && posi >= 1) {
        if (posi == 1) {
            remover_inicio(inicio); // Lida com a remocao do inicio
        } else {
            NODE* atual = *inicio;
            for (int i = 1; i < posi - 1 && atual != NULL; i++) {
                atual = atual->next;
            }
            if (atual != NULL && atual->next != NULL) {
                NODE* aux = atual->next; // aux recebe endereco do valor que sera removido
                atual->next = aux->next;
                printf("\n Noh [%d] foi removido com sucesso!", aux->valor);
                free(aux); // Libera o noh
            }
        }
    } else {
        printf("\n ERRO - Lista vazia ou posicao invalida!");
    }
}

// Procura por um valor
int procurar_valor(NODE* node, int target) {
    while (node != NULL) {
        if (node->valor == target) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

// Imprime a lista encadeada
void imprimir_lista(NODE* node) {
    printf("\n Lista: ");
    while (node != NULL) {
        printf(" [%d] -> ", node->valor);
        node = node->next;
    }
    printf("[NULL]\n");
}

int ler_elemento(int tipo) {
    int elem;
    if(tipo == 1){
        printf("\n A seguir, insira um numero inteiro: ");
        scanf("%d", &elem);
    } else {
        printf("\n A seguir, insira a posicao desejada: ");
        scanf("%d", &elem);
    }
    return elem;
}

int menu() {
    int op;
    printf("\n\n=================== [MENU PRINCIPAL] ===================");
    printf("\n FUNCOES DE INSERCAO");
    printf("\n [1] - Inserir no inicio.");
    printf("\n [2] - Inserir no Fim.");
    printf("\n [3] - Inserir em uma posicao.");
    printf("\n\n FUNCOES DE REMOCAO");
    printf("\n [4] - Remover do Inicio.");
    printf("\n [5] - Remover do Fim.");
    printf("\n [6] - Remover de uma posicao.");
    printf("\n\n OUTROS");
    printf("\n [7] - Exibir Lista.");
    printf("\n [0] - Finalizar.");
    printf("\n========================================================\n\n");
    printf(" A seguir, insira uma das opcoes: ");
    scanf("%d", &op);
    return op;
}

int main() {
    NODE *node = inicializar();
    int op;
    do {
        op = menu();
        switch (op) {
        case 0:
            printf("\n Fim do programa.");
            break;
        case 1:
            inserir_inicio(&node, ler_elemento(1));
            break;
        case 2:
            inserir_fim(&node, ler_elemento(1));
            break;
        case 3:
            inserir_em_uma_posicao(&node, ler_elemento(0), ler_elemento(1));
            break;
        case 4:
            remover_inicio(&node);
            break;
        case 5:
            remover_fim(&node);
            break;
        case 6:
            remover_de_posicao(&node, ler_elemento(0));
            break;
        case 7:
            imprimir_lista(node);
            break;
        default:
            printf("\n Opcao invalida!");
            break;
        }
    } while (op != 0);

    // Limpa os nohs restantes
    while (!vazia(node)) {
        remover_inicio(&node);
    }
    return 0;
}
