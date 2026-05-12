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
#include "documento.h"

int indice = 0; // Cara é mais fácil usar variável global n sei pq adriano zera a prova se usar ;^;


void newDoc(List l, char n[], int pg, int bt, int id){
    Doc novo = (Doc)malloc(sizeof(TypeDoc));
    novo->name = (char*)malloc(strlen(n)+1);
    strcpy(novo->name, n);
    novo->bytes = bt;
    novo->id = id;
    novo->pg = pg;
    
    if(l->tail)
        l->tail->next = novo; // Se existir um tail, ele aponta para o novo.
    novo->previous = l->tail; // O  novo aponta para o tail como antigo.
    l->tail = novo; // O novo se torna o tail.
    l->tail->next = NULL; // o nextimo dele é null.
    if(!l->head){ // Se nao existe um head, ele recebe o valor de tail.
        l->head = l->tail;
    }
    system("clear");
    printf("\n * -> Documento %s criado com %d paginas e %d bytes.\n\n", novo->name, novo->pg, novo->bytes);
}

void printDoc(Doc d){
    printf(" ID: %d - %s (%d páginas) [%d bytes]\n", d->id, d->name, d->pg, d->bytes);
}

void printLista(List l){
    if(!l->head) {
        printf("\n ! -> Não há documentos na fila.\n\n");
        return;
    }
    Doc lista = l->head;
    putchar('\n');
    while(lista){
        printDoc(lista);
        lista = lista->next;
    }
    putchar('\n');
}

void printerDoc(List l){
    if(!l->head){
        printf("\n ! -> Sem documentos para imprimir.\n\n");
        return;
    }
    Doc imprimido = l->head;
    printf("\n * -> Documento %s foi impresso!\n\n", imprimido->name);
    l->head = imprimido->next;
    free(imprimido->name);
    free(imprimido);
 
}

Doc getId(List l){
    int id, valido; 
    Doc alvo = l->head;
    valido = scanf(" %d", &id);
    if(valido!=1){
        while(getchar()!='\n');
        return NULL;
    }
    while(alvo){
        if(alvo->id == id)
            return alvo;
        alvo = alvo->next;
    }
    return NULL;
}
void deletaDoc(List l){
    if(!l->head) {
        printf("\n ! -> Sem documentos para deletar.\n\n");
        return;
    }
    printLista(l);
    printf("\n @ -> Insira o ID do Documento a ser deletado: > ");
    Doc deleta = getId(l);
    if(!deleta){
        printf("\n ! -> ID inexistente.\n\n");
        return;
    }
    
    if(l->tail == l->head)
        l->tail = l->head = NULL;
    else {
        if(deleta == l->tail) {
            l->tail = l->tail->previous;
            l->tail->next = NULL;
        }
        else if (deleta == l->head) {   
            l->head = deleta->next;
            l->head->previous = NULL;
        }
        else if(deleta->next)
            deleta->previous->next = deleta->next;
    } 
    system("clear");
    printf("\n * -> O arquivo %s foi deletado.\n\n", deleta->name);
    free(deleta->name);
    free(deleta);
  
}

void priorizaDoc(List l){
    if(!l->head || !l->head->next){
        printf("\n ! -> Não há documentos suficientes para priorizar.\n\n");
        return;
    }
    printLista(l);
    printf("\n @ -> Insira o ID do documento para priorizar: > ");
    Doc prioriza = getId(l);
    system("clear");
    if(!prioriza){
        printf("\n ! -> Id inexistente.\n\n");
        return;
    }
    if(prioriza == l->head){
        printf("\n ! -> Documento %s já está no topo.\n\n", prioriza->name);
        return;
    }
    if(prioriza == l->tail){
        l->tail = prioriza->previous;
        l->tail->next = NULL;
    } 
    else {
        prioriza->previous->next = prioriza->next;
        prioriza->next->previous = prioriza->previous;
    }
    prioriza->previous = NULL;
    prioriza->next = l->head;
    l->head->previous = prioriza;
    l->head = prioriza;
    printf("\n * -> O documento %s recebeu prioridade e será o próximo da fila de impressao.\n\n", prioriza->name);
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
    char name[100];
   
    printf("Insira o nome do arquivo: > ");
    scanf(" %[^\n]", name);
    printf("Insira a quantidade de páginas: > ");
    scanf(" %d", &pg);
    newDoc(l, name, pg, byte, id);
    
}

 
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


