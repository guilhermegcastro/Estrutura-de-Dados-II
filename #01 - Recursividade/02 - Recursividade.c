/**
* @file 02 - Recursividade.c
* @author @guilhermegcastro
* @date 04.03.2026 18:14:23 -03
* @brief FUNÇÃO RECURSIVA PARA RETORNAR: A SOMA DOS VALORES DE UM ARRAY
**/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int somaArray(int a[], int t) {
    if(!t) return a[t];
        return a[t] + somaArray(a, t-1);
}

int main() {
    srand(time(NULL));
    int t;
    printf("Tamanho do Array: ");
    scanf(" %d", &t);
    int array[t];
    printf("[");
    for (int i = 0; i < t; i++) {
        array[i] = 1 + rand()%t;
        printf(" %d ", array[i]);
        if(i!= t-1)
            putchar('+');
    }
    printf("] == %d", somaArray(array, t-1));
    return 0;
    
}
