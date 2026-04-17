/**
* @file 05_fila.c
* @author @guilhermegcastro
* @date 2026-04-15
* @brief
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "05_ponteiro_duplo.h"

int indice = 0;

//Assinaturas...
int interface();
void novoDoc(List l);
 
int main() {
    srand(time(NULL));
    List lista = new_List();
    printf("\n\n\n");
    while(1){
        switch (interface()) {
            case 1: novoDoc(lista);
                break;
            case 2: printLista(lista);
                break;
            case 3: printerDoc(lista);
                break;
            case 4: deletaDoc(lista);
                break;
            case 5: priorizaDoc(lista);
                break;
            default: system("clear");
                printf("\n !-> Opçao invalida.\n\n");
        }
    }
    return 0;
}

   
int interface(){
    printf(" MENU DA IMPRESSORA\n ");
    printf("\n1 - Criar Documento\n");
	printf("2 - Fila de Impressão\n");
	printf("3 - Imprimir Documento\n");
	printf("4 - Excluir Documento\n");
	printf("5 - Priorizar Documento\n");
	int opt, valido;
	valido = scanf(" %d",&opt);
	if(valido!=1) {
        opt = 0;
        while(getchar()!='\n');
    }
    system("clear");
    return opt;
};

void novoDoc(List l){
    int pg, byte = 100+rand()%501, id = indice++;
    char nome[100];
   
    printf("Insira o nome do arquivo: > ");
    scanf(" %[^\n]", nome);
    printf("Insira a quantidade de páginas: > ");
    scanf(" %d", &pg);
    newDoc(l, nome, pg, byte, id);
    
}


