#include <stdio.h>
#include <string.h>
#define TF 10

typedef struct sLocatario {
    char nome[61];
    char cpf[16];
} LOCATARIO;

typedef struct sBarraca {
    LOCATARIO locatario;
    int aluguel;
    int produto;
} BARRACA;

typedef struct sLista {
    BARRACA barraca[TF];
    int n;
} LISTA;

void inicializar(LISTA *lista) {
    lista->n = -1;
}

int cheia(LISTA *lista) {
    return (lista->n + 1 == TF);
}

int vazia(LISTA *lista) {
    return (lista->n == -1);
}

LOCATARIO ler_locatario() {
    LOCATARIO locatario;

    do {
        fflush(stdin);
        printf("\n Digite o nome do locatario: ");
        fgets(locatario.nome, sizeof(locatario.nome), stdin);
        locatario.nome[strcspn(locatario.nome, "\n")] = 0;

        fflush(stdin);
        printf("\n Digite o CPF do locatario: ");
        fgets(locatario.cpf, sizeof(locatario.cpf), stdin);
        locatario.cpf[strcspn(locatario.cpf, "\n")] = 0;

        if (strlen(locatario.nome) == 0 || strlen(locatario.cpf) == 0)
            printf("\n Informacoes estao vazias! Tente novamente.");

    } while (strlen(locatario.nome) == 0 || strlen(locatario.cpf) == 0);

    return locatario;
}

BARRACA ler_barraca() {
    BARRACA barraca;

    barraca.locatario = ler_locatario();

    do {
        printf("\n\n Qual a situacao do aluguel da barraca?");
        printf("\n [1] - Pago.");
        printf("\n [0] - Pendente.");
        printf("\n Opcao: ");
        scanf("%d", &barraca.aluguel);

        if (barraca.aluguel != 1 && barraca.aluguel != 0)
            printf("\n Opcao invalida! Tente novamente.");

    } while (barraca.aluguel != 1 && barraca.aluguel != 0);

    do {
        printf("\n\n Qual produto sera comercializado?");
        printf("\n [1] - Bebidas.");
        printf("\n [2] - Lanches.");
        printf("\n [3] - Artigos em geral.");
        printf("\n Opcao: ");
        scanf("%d", &barraca.produto);

        if (barraca.produto < 1 || barraca.produto > 3)
            printf("\n Opcao invalida! Tente novamente.");

    } while (barraca.produto < 1 || barraca.produto > 3);

    return barraca;
}

void inserir_fim(LISTA *lista) {
    if (cheia(lista)) {
        printf("\n Lista cheia!");
    } else {
        BARRACA barraca = ler_barraca();
        lista->n += 1;
        lista->barraca[lista->n] = barraca;
        printf("\n Locatario gravado com sucesso! Barraca %d.", lista->n + 1);
    }
}

void imprimir_relatorio_inadimplentes(LISTA lista) {
    int i, encontrou = 0;

    if (vazia(&lista)) {
        printf("\n Lista vazia!");
        return;
    }

    printf("\n\n======== [LOCATARIOS INADIMPLENTES] ========");
    for (i = 0; i <= lista.n; i++) {
        if (lista.barraca[i].aluguel != 1) {
            encontrou = 1;

            printf("\n Barraca: %d", i + 1);
            printf("\n Nome: %s", lista.barraca[i].locatario.nome);
            printf("\n CPF: %s\n", lista.barraca[i].locatario.cpf);
        }
    }

    if (!encontrou)
        printf("\n Nao ha locatarios inadimplentes.\n");

    printf("============================================\n");
}

void imprimir_relatorio_barracas(LISTA lista) {
    int i;
    int barracaOcupada = lista.n + 1;
    int barracaVazia   = TF - barracaOcupada;

    if (vazia(&lista)) {
        printf("\n Lista vazia!");
        return;
    }

    printf("\n\n======== [BARRACAS OCUPADAS] ========\n");
    for (i = 0; i <= lista.n; i++) {

        printf(" [%d]", i + 1);
    }

    printf("\n\n======== [BARRACAS LIVRES] ==========\n");
    for (i = lista.n + 1; i < TF; i++) {
        printf(" [%d]", i + 1);
    }

    printf("\n\n Total ocupadas: %d", barracaOcupada);
    printf("\n Total livres:   %d", barracaVazia);
    printf("\n=====================================\n");
}

int menu() {
    int op;
    printf("\n ============= [MENU] =============");
    printf("\n [1] - Cadastrar barraca.");
    printf("\n [2] - Inadimplentes.");
    printf("\n [3] - Barracas ocupadas e livres.");
    printf("\n [0] - Sair.");
    printf("\n ===================================");
    printf("\n Opcao: ");
    scanf("%d", &op);
    return op;
}

int main() {
    int op;
    LISTA lista;

    inicializar(&lista);

    do {
        op = menu();
        switch (op) {
            case 1: inserir_fim(&lista);                     
                    break;
            case 2: imprimir_relatorio_inadimplentes(lista); 
                    break;
            case 3: imprimir_relatorio_barracas(lista);      
                    break;
            case 0: printf("\n Fim do programa.\n");         
                    break;
            default: printf("\n Opcao invalida!");
        }
    } while (op != 0);

    return 0;
}