/**
* @file 05 - Recursividade.c
* @author @guilhermegcastro
* @date 05.03.2026 
* @brief FUNÇÃO RECURSIVA PARA RETORNAR: ÍNDICE (BUSCA BINÁRIA) DE UM VALOR EM ARRAY
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int buscaBi(int a[], int i, int f, int alvo) {
    if(i > f) return -1;
    int m = i + (f-i)/2;
    if(a[m]==alvo) return m;
    if(a[m] > alvo) 
        return buscaBi(a, i, m-1, alvo);
    else
        return buscaBi(a, m+1, f, alvo);
}



int main() {
	    
    int array[] = {1, 2, 3, 4, 5};
    int n;
    printf("Informe o nº que deseja buscar no array: ");
    scanf(" %d", &n);
    int indice = buscaBi(array, 0, 4, n);
    (indice!=-1) ? printf("Achou em %d", indice) : printf("Não existe esse número no array.");
    return 0;
}


