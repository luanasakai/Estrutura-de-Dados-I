#include <stdio.h>
#define TF 8
/*2. Leia um vetor de 16 posições e troque os 8 primeiros valores pelos 8 últimos e vice-eversa.
Escreva ao final o vetor obtido.*/

void inverter_vetor(int vetor[]){
    int inverso[TF], i;

    printf("\n Vetor Inverso: ");
    for(i = 0; i < TF; i++){
        inverso[i] = vetor[TF - 1 - i]; 
        printf(" %d ", inverso[i]);
    }
}

void imprimir_vetor(int vetor[]){
    int i;
    printf("\n Vetor Original: ");
    for(i=0 ; i < TF; i++){
        printf(" %d ", vetor[i]);
    }
}

void ler_vetor(int vetor[]){
    int i;
    for(i=0 ; i < TF; i++){
        printf("\n %d/%d - Insira um numero inteiro: ", i+1, TF);
        scanf("%d", &vetor[i]);
    }
}

void main(){
    int vetor[TF];

    ler_vetor(vetor);
    imprimir_vetor(vetor);
    inverter_vetor(vetor);


}
