/**
* @file 04 - Recursividade.c
* @author @guilhermegcastro
* @date 05.03.2026 08:10:03 -03
* @brief FUNÇÃO RECURSIVA PARA RETORNAR: ÍNDICE (BUSCA SEQUENCIAL) DE  TODOS OS VALORES EM ARRAY
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int buscaSe(int busca, int a[], int t, int* flag){
    
    if(t==1) {
        *flag = 0;
        return a[t-1];
    }
        
    if(buscaSe(busca, a, t-1, flag)==busca){
        printf("Achou %d na posição %d\n", busca, t-1);
        *flag = 1;
    }
        return a[t];
}

int main() {
    srand(time(NULL));
    int tam, busca;
    printf("Tamanho do ARRAY: ");
    scanf(" %d", &tam);
    int array[tam];
    for (int i = 0; i < tam; i++) {
        array[i] = 1 + rand()%tam;
        printf(" %d ", array[i]);
    }
    printf("\n Insira um número entre 1 e %d para buscar: ", tam);
    scanf("%d", &busca);
    
    int flag = buscaSe( busca, array, tam, &flag);
    (flag)? putchar(' '): printf("Não foi encontrado o número %d no Array.", busca);
    return 0;
}


