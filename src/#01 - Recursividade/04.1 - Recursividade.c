/**
* @file 04 - Recursividade.c
* @author @guilhermegcastro
* @date 05.03.2026 08:10:03 -03
* @brief FUNÇÃO RECURSIVA PARA RETORNAR: ÍNDICE (BUSCA SEQUENCIAL) DE UM VALOR EM ARRAY
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int buscaSe(int busca, int a[], int t){
    if(t==1) {
        if(a[0] == busca)
            return t;
         else 
            return -1;
    }
    if(a[t] == busca)
        return t;
    else
        return buscaSe(busca, a, t-1);
}

void sorteio(int* a, int t){
    int c = 0;
    while(c < t){
        int r = 0;
        a[c] = 1 + rand()%t;
        for (int i = 0; i <= c; i++){
            if(a[c] == a[i] && c != i) {
                r = 1;
                break;
            }
        }
        if(r)
            continue;
        else 
            c++;
    }
    
}

void printArray(int a[], int t) {
    for (int i = 0; i < t; i++){
        printf(" %d ", a[i]);
    }
}

int main() {
    srand(time(NULL));
    int tam, busca;
    printf("Tamanho do ARRAY: ");
    scanf(" %d", &tam);
    int array[tam];
    sorteio(array, tam);
    printArray(array, tam);
    printf("\n Insira um número entre 1 e %d para buscar: ", tam);
    scanf("%d", &busca);
    
    int i = buscaSe( busca, array, tam-1);
    (i!=-1)? printf("%d foi encontrado no índice %d", busca, i) : printf("Não foi encontrado %d no array ", busca);
    return 0;
}


