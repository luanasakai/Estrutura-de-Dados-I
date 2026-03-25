#include <stdio.h>
#define TF 12

void soma(int x, int y, int vetor[]){
    printf("\nResultado da Soma");
    printf("\n%d + %d = %d\n", vetor[x], vetor[y], vetor[x] + vetor[y]);
}

int ler_posicao(){
    int x;
    printf("\nInsira uma posicao de 0 a %d: ", TF-1);
    scanf("%d", &x);
    return x;
}

void ler_vetor(int vetor[]){
    int i;
    for (i = 0; i < TF; i++){
        printf("\n%d/%d - Insira um numero inteiro: ", i+1, TF);
        scanf("%d", &vetor[i]);
    }
}

int main (){
    int vetor[TF];
    ler_vetor(vetor);
    soma(ler_posicao(), ler_posicao(), vetor);
    return 0;
}
