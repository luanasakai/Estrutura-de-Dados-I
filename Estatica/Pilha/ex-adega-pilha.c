/*
Exercicios de Fixacao - PILHA

1.  Imagine um colecionador de vinhos que compra vinhos recentes e guarda-os em uma adega para envelhecerem,
    e que a cada ocasião especial abre sempre sua última aquisição (para poupar os mais antigos).
    Construa um programa que:
        a) Permita incluir novos vinhos na adega
        b) Informe qual vinho deve ser aberto em uma ocasião especial
        c) Relacione as cinco aquisições mais antigas
    As informações básicas que o registro do vinho deve conter são: nome do produto e safra.

2.  O problema das Torres de Hanói é bastante estudado em computação. O problema consiste em n discos
    de diferentes diâmetros e três estacas: A, B e C. Inicialmente os discos estão encaixados na estaca
    onde o menor está sempre em cima do maior disco. O objetivo é deslocar os discos para a estaca C,
    usando a estaca B como auxiliar. Somente o primeiro disco de toda estaca pode ser deslocado.
    Isso nos dá a ideia de pilhas. Portanto construa a resolução desse exercício usando pilhas
    e para n = 4, ou seja, para 04 discos.
*/
#include <stdio.h>
#include <string.h>  
#define TF 4

typedef struct sVinho{
    char nome[61];
    int safra;
}VINHO;

typedef struct sPilha{
    VINHO vinho[TF];
    int topo;
}ADEGA;

void inicializar(ADEGA *adega){
    adega->topo = -1;
}

int vazia(ADEGA *adega){
    return (adega->topo == -1);
}

int cheia(ADEGA *adega){
    return ((adega->topo + 1) == TF);
}

VINHO ler_vinho(){
    VINHO vinho;

    getchar(); // limpa buffer antes de fgets
    printf("\n Insira o nome do vinho: ");
    fgets(vinho.nome, sizeof(vinho.nome), stdin);
    vinho.nome[strcspn(vinho.nome, "\n")] = 0; // Remove o \n

    printf("\n Insira a safra do vinho: ");
    scanf("%d", &vinho.safra);

    return vinho;
}

void inserir_adega(ADEGA *adega){
    VINHO vinho;

    if(cheia(adega)){
        printf("\n Adega cheia!");
    }else{
        adega->topo += 1;
        vinho = ler_vinho();
        adega->vinho[adega->topo] = vinho;
    }
}

VINHO retirar_adega(ADEGA *adega){
    VINHO vinho = {"", 0};

    if(vazia(adega)){
        printf("\n Adega vazia!");
    }else{
        vinho = adega->vinho[adega->topo];
        adega->topo -= 1;
    }
    return vinho;
}

void imprimir_adega(ADEGA adega){
    int i;

    if(vazia(&adega)){
        printf("\n Adega vazia!");
    }else{
        printf("\n\n======== [ADEGA] ==========\n");
        for(i = adega.topo; i >= 0; i--){
            printf("\n Nome: %s", adega.vinho[i].nome);
            printf("\n Ano da Safra: %d\n", adega.vinho[i].safra);
        }
        printf("\n==========================\n\n");
    }
}

int menu(){
    int op;

    printf("\n\n ================= [OPCOES] =================");
    printf("\n [1] - Inserir um vinho.");
    printf("\n [2] - Remover um vinho.");
    printf("\n [3] - Imprimir todos os vinhos.");
    printf("\n [0] - Sair.");
    printf("\n ==============================================");
    printf("\n A seguir, insira uma das opcoes: ");
    scanf("%d", &op);

    return op;
}

int main(){
    int op;
    VINHO vinho;
    ADEGA adega;

    inicializar(&adega);

    do{
        op = menu();
        switch(op){
            case 1: inserir_adega(&adega);
                break;

            case 2: vinho = retirar_adega(&adega);
                    if(strlen(vinho.nome) > 0)
                        printf("\n Ótima escolha! Você optou pelo vinho %s da safra do ano %d", vinho.nome, vinho.safra);
                    break;

            case 3: imprimir_adega(adega);
                    break;

            case 0: printf("\n Fim do programa.");
                    break;

            default: printf("\n Opção inválida! Tente novamente.");
        }
    }while(op != 0);

    return 0;
}
