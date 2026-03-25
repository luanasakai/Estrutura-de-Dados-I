#include <stdio.h>
#define TF 50

//estrutura da lista
typedef struct sLista{
    int vetor[TF];//vetor, armazena os valores da lista 
    int n;//ultima posicao possivel
}Lista;

//inicializa a lista em -1 (= vazia)
void inicializar_lista(Lista *lista){
    lista->n = -1;
}

//verifica se a lista esta cheia
int cheia(Lista *lista){

    /*se for adicionado mais uma posicao (n+1) a lista, e o valor de 'n' se igualar ao 'TF',
     a lista esta cheia. retorna 1 (true)*/
    if(lista->n+1 == TF){
        return 1;
    }else{
    /*se nao se igualar ao 'TF', a lista possui espaco, retorna 0 (false)*/
        return 0;
    }
}

//verifica se a lista esta vazia
int vazia(Lista *lista){
    
    /*se o valor da posicao da lista for -1, quer dizer que esta vazia. retorna 1 (true)*/
    if(lista->n == -1){
        return 1;
    }else{
    /*se nao, quer dizer que possui elementos (nao necessariamente cheia). retorna 0 (false)*/
        return 0;
    }
}


void inserir_fim(Lista *lista, int elem){
    
    if(cheia(lista)){
        printf("\n Lista Cheia! Não é possível inserir nenhum elemento.");
        return;

    }else {
        // ou lista->n++;
        lista->vetor[++lista->n] = elem;

        printf("\n Insercao concluida!\n");
    }

}

void inserir_inicio(Lista *lista, int elem){
    int i;
    if(!cheia(lista)){
        lista->n++;
        for(i=lista->n; i>0; i--){
            lista->vetor[i] = lista->vetor[i-1];
        }
        lista->vetor[0] = elem;

        printf("\n Insercao concluida!\n");
    }else{

        printf("\n Lista Cheia! Não é possível inserir nenhum elemento.");
    }
}

void exibir_lista(Lista lista){
    int i;
    if(vazia(&lista)){
        printf("\n Lista Vazia! Insira algum elemento.");
        return;
    }

    printf("\n Lista: ");    
    for(i=0; i <= lista.n; i++){
            printf(" [%d] ", lista.vetor[i]);
    }
    printf("\n");   
}

int ler_elemento(){
    int elem;

    do{
        printf("\n Insira um numero inteiro: ");
        scanf("%d", &elem);
    
        if(elem < 0)
            printf("\n Elemento invalido! Tente novamente");
    
    }while(elem < 0);

    return elem;
}

int buscar_elemento(Lista *lista, int elem){
    int i = 0;

    if (vazia(lista)){
        printf("\n Lista Vazia! Insira algum elemento.");
        return;
    }

    while (i <= lista->n){
        if (lista->vetor[i] == elem){
            return i; // Retorna a posição encontrada
        }
        i++;
    }
    return -1; // Se não encontrou, retorna -1
}   

void remover_elemento(Lista *lista, int elem){
    int i, posi;

    if(vazia(lista)){

        printf("\n Lista Vazia! Insira algum elemento.");
        return;
    }
    posi = buscar_elemento(lista, elem);
        if(posi == -1){
            printf("\n Elemento inexistente! Tente novamente.");

        }else{
            for(i = posi; i < lista->n; i++){
                lista->vetor[i] = lista->vetor[i+1];//move os elementos para a esquerda
            }
            lista->n = lista->n-1;// decrementa o tamanho da lista

            printf("\n Remocao concluida!\n");
            exibir_lista(*lista);
        }
}

//exercicio
void intercalar(Lista lista1, Lista lista2, Lista *lista3){
    int i=0, j=0;

    if((lista1.n + lista2.n + 2) > TF){
        printf("\n Não foi possível realizar a operação! Tamanho das listas excedeu o limite.");
        return;
    }

    while(i <= lista1.n || j <= lista2.n){
        if(i <= lista1.n && !cheia(lista3)){
            inserir_fim(lista3, lista1.vetor[i]);
            i++;
        }
        if(j <= lista2.n && !cheia(lista3)){
            inserir_fim(lista3, lista2.vetor[j]);
            j++;
        }
    }
    printf("\n Lista 3 (Concatenada) -");
    exibir_lista(*lista3);
}


void menuOp(Lista *lista, int num){
    int op;
    do{
        printf("\n=============== [LISTA %d - OPERACOES] ====================", num);
        printf("\n [1] - Inserir elementos no FINAL da lista.");
        printf("\n [2] - Inserir elementos no INICIO da lista.");
        printf("\n [3] - Imprimir elementos.");
        printf("\n [4] - Remover um elemento especifico.");
        printf("\n [0] - Voltar.");
        printf("\n=======================================================\n");
        printf("\n A seguir, insira a operacao que deseja realizar: ");
        scanf("%d", &op);

        switch (op){
        case 1: inserir_fim(lista, ler_elemento());
            break;
        case 2: inserir_inicio(lista, ler_elemento());
            break;        
        case 3: exibir_lista(*lista);
            break;
        case 4: remover_elemento(lista, ler_elemento());
            break;
        default: 
            if(op != 0)
                printf("\n Opcao Invalida! Tente novamente.");
            break;
        }
    }while(op != 0);
}

int menuLista(){
    int op;

    printf("\n============== [LISTA] =================");
    printf("\n [1] - Lista 1 ");
    printf("\n [2] - Lista 2 ");
    printf("\n [3] - Concatenar Lista 1 com Lista 2");
    printf("\n [0] - Sair.");
    printf("\n========================================");
    printf("\n A seguir, escolha com qual lista deseja trabalhar: ");
    scanf("%d", &op);

    return op;
}

int main(){
    int opLista;
    Lista lista1, lista2, lista3;

    inicializar_lista(&lista1);
    inicializar_lista(&lista2);
    inicializar_lista(&lista3);

    do{
        opLista = menuLista();
        switch (opLista){
        case 1: menuOp(&lista1, 1);    
            break;
        case 2: menuOp(&lista2, 2);    
            break;
        case 3: 
            printf("\n Lista 1 -");
            exibir_lista(lista1);
            printf("\n Lista 2 -");
            exibir_lista(lista2);
            intercalar(lista1, lista2, &lista3);    
            break;
        default: printf("\n Fim do programa.\n");
            break;
        }
    }while(opLista != 0);
   
    return 0;
}
