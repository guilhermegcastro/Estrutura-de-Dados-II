/**
* @file 03 - Recursividade.c
* @author @guilhermegcastro
* @date 05.03.2026 
* @brief FUNÇÃO RECURSIVA PARA RETORNAR: O MAIOR VALOR DE UM ARRAY
**/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int maiorValor(int a[], int t) {
    if(!t) return a[t];
    int n = maiorValor(a, t-1);
    if(a[t] > n) return a[t];
    else return n;
}

int main() {
    srand(time(NULL));
    int tam;
    printf("Tamanho do Array: ");
    scanf(" %d", &tam);
    int array[tam];
    printf("NÚMEROS SORTEADOS:\n[");
    for (int i = 0; i < tam; i++) {
        array[i] = 1 + rand()%(2*tam);
        printf(" %d", array[i]);
        printf("%s", (i!=tam-1)? "," : " ]\n");
    }
    printf("O maior valor do array é: %d", maiorValor(array, tam-1));
    return 0;
    
}
