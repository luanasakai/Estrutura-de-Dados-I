#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sFormando {
    char prontuario[20];
    char nome[60];
    char curso[60];
    int  ano_ingresso;
    int  ano_formatura;
    char endereco[60];
    char tel1[20];
    char tel2[20];
} FORMANDO;

typedef struct sNode {
    FORMANDO formando;
    struct sNode *next;
} NODE;

// Inicialização
void inicializar(NODE **node) {
    *node = NULL;
}

int vazio(NODE *node) {
    return (node == NULL);
}

// Criação de nó
NODE* createnode(FORMANDO f) {
    NODE *newNode = (NODE*) malloc(sizeof(NODE));
    if (newNode != NULL) {
        newNode->formando = f;
        newNode->next = NULL;
    } else {
        printf("\nERRO - Falha na alocação de memória.");
    }
    return newNode;
}

// Inserção no início
void inserir_inicio(NODE **node, FORMANDO f) {
    NODE *new_node = createnode(f);
    if (new_node != NULL) {
        new_node->next = *node;
        *node = new_node;
    }
}

// Inserção no fim
void inserir_fim(NODE **node, FORMANDO f) {
    NODE *new_node = createnode(f);
    if (new_node != NULL) {
        if (vazio(*node)) {
            *node = new_node;
        } else {
            NODE *atual = *node;
            while (atual->next != NULL) {
                atual = atual->next;
            }
            atual->next = new_node;
        }
    }
}

// Remoção do início
void remover_inicio(NODE **inicio) {
    if (!vazio(*inicio)) {
        NODE *aux = *inicio;
        *inicio = (*inicio)->next;
        free(aux);
        printf("\nFormando removido do início.\n");
    } else {
        printf("\nERRO - Lista vazia.\n");
    }
}

// Remoção do fim
void remover_fim(NODE **inicio) {
    if (!vazio(*inicio)) {
        if ((*inicio)->next == NULL) {
            free(*inicio);
            *inicio = NULL;
        } else {
            NODE *atual = *inicio;
            while (atual->next->next != NULL) {
                atual = atual->next;
            }
            free(atual->next);
            atual->next = NULL;
        }
        printf("\nFormando removido do fim.\n");
    } else {
        printf("\nERRO - Lista vazia.\n");
    }
}

// Ler dados de um formando
FORMANDO ler_formando() {
    FORMANDO f;
    printf("\nProntuário: "); scanf(" %19s", f.prontuario);
    printf("Nome: "); scanf(" %[^\n]", f.nome);
    printf("Curso: "); scanf(" %[^\n]", f.curso);
    printf("Ano de ingresso: "); scanf("%d", &f.ano_ingresso);
    printf("Ano de formatura: "); scanf("%d", &f.ano_formatura);
    printf("Endereço: "); scanf(" %[^\n]", f.endereco);
    printf("Telefone 1: "); scanf(" %19s", f.tel1);
    printf("Telefone 2: "); scanf(" %19s", f.tel2);
    return f;
}

// Relatório por curso
void relatorio_por_curso(NODE *inicio, const char *curso) {
    NODE *atual = inicio;
    printf("\n======= [Relatorio do curso %s] ======\n", curso);
    while (atual != NULL) {
        if (strcmp(atual->formando.curso, curso) == 0) {
            printf("%s - %s (%d/%d)\nEndereço: %s\nTel1: %s | Tel2: %s\n\n",
                   atual->formando.prontuario,
                   atual->formando.nome,
                   atual->formando.ano_ingresso,
                   atual->formando.ano_formatura,
                   atual->formando.endereco,
                   atual->formando.tel1,
                   atual->formando.tel2);
        }
        atual = atual->next;
    }
}

// Relatório por ano de formatura
void relatorio_por_ano(NODE *inicio, int ano) {
    NODE *atual = inicio;
    printf("\n======= [Relatorio de formandos %d] =======\n", ano);
    while (atual != NULL) {
        if (atual->formando.ano_formatura == ano) {
            printf("%s - %s (%s)\nEndereco: %s\nTel1: %s | Tel2: %s\n\n",
                   atual->formando.prontuario,
                   atual->formando.nome,
                   atual->formando.curso,
                   atual->formando.endereco,
                   atual->formando.tel1,
                   atual->formando.tel2);
        }
        atual = atual->next;
    }
}

// Menu
int menu() {
    int op;
    printf("\n\n=================== [MENU PRINCIPAL] ===================");
    printf("\n[1] - Inserir formando no início");
    printf("\n[2] - Inserir formando no fim");
    printf("\n[3] - Remover do início");
    printf("\n[4] - Remover do fim");
    printf("\n[5] - Relatório por curso");
    printf("\n[6] - Relatório por ano de formatura");
    printf("\n[0] - Sair");
    printf("\n========================================================\n");
    printf("A seguir, escolha uma das opcoes: ");
    scanf("%d", &op);
    return op;
}

int main() {
    NODE *lista;
    inicializar(&lista);
    int op;

    do {
        op = menu();
        switch (op) {
            case 1:
                inserir_inicio(&lista, ler_formando());
                break;
            case 2:
                inserir_fim(&lista, ler_formando());
                break;
            case 3:
                remover_inicio(&lista);
                break;
            case 4:
                remover_fim(&lista);
                break;
            case 5: {
                char curso[60];
                printf("\nDigite o curso: ");
                scanf(" %[^\n]", curso);
                relatorio_por_curso(lista, curso);
                break;
            }
            case 6: {
                int ano;
                printf("\nDigite o ano de formatura: ");
                scanf("%d", &ano);
                relatorio_por_ano(lista, ano);
                break;
            }
            case 0:
                printf("\nEncerrando programa...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }
    } while (op != 0);

    // Liberação da memória
    while (!vazio(lista)) {
        remover_inicio(&lista);
    }

    return 0;
}
