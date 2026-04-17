/**
* @file 05_ponteiro_duplo.h
* @author @guilhermegcastro
* @date 2026-04-17
* @brief
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct TypeDocument{
    char* nome;
    int pg; 
    int byte;
    int id;
    struct TypeDocument* prox;
    struct TypeDocument* ante;
}TypeDocument;

typedef TypeDocument* Doc;

typedef struct TypeList{
    Doc head;
    Doc tail;
    int size;
}TypeList;

typedef TypeList* List;



List new_List(){
    List nova = (List)malloc(sizeof(TypeDocument));
    nova->head = NULL;
    nova->tail = NULL;
    nova->size = 0;
    return nova;
}


void newDoc(List l, char n[], int pg, int bt, int id){
    Doc novo = (Doc)malloc(sizeof(TypeDocument));
    novo->nome = (char*)malloc(strlen(n)+1);
    strcpy(novo->nome, n);
    novo->byte = bt;
    novo->id = id;
    novo->pg = pg;
    
    if(l->tail)
        l->tail->prox = novo; // Se existir um tail, ele aponta para o novo.
    novo->ante = l->tail; // O  novo aponta para o tail como antigo.
    l->tail = novo; // O novo se torna o tail.
    l->tail->prox = NULL; // o proximo dele é null.
    if(!l->head){ // Se nao existe um head, ele recebe o valor de tail.
        l->head = l->tail;
    }
    system("clear");
    printf("\n * -> Documento %s criado com %d paginas e %d bytes.\n\n", novo->nome, novo->pg, novo->byte);
}


void printDoc(Doc d){
    printf(" ID: %d - %s (%d páginas) [%d bytes]\n", d->id, d->nome, d->pg, d->byte);
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
        lista = lista->prox;
    }
    putchar('\n');
}

void printerDoc(List l){
    if(!l->head){
        printf("\n ! -> Sem documentos para imprimir.\n\n");
        return;
    }
    Doc imprimido = l->head;
    printf("\n * -> Documento %s foi impresso!\n\n", imprimido->nome);
    l->head = imprimido->prox;
    free(imprimido->nome);
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
        alvo = alvo->prox;
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
            l->tail = l->tail->ante;
            l->tail->prox = NULL;
        }
        else if (deleta == l->head) {   
            l->head = deleta->prox;
            l->head->ante = NULL;
        }
        else if(deleta->prox)
            deleta->ante->prox = deleta->prox;
    } 
    system("clear");
    printf("\n * -> O arquivo %s foi deletado.\n\n", deleta->nome);
    free(deleta->nome);
    free(deleta);
  
}

void priorizaDoc(List l){
    if(!l->head || !l->head->prox){
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
        printf("\n ! -> Documento %s já está no topo.\n\n", prioriza->nome);
        return;
    }
    if(prioriza == l->tail){
        l->tail = prioriza->ante;
        l->tail->prox = NULL;
    } 
    else {
        prioriza->ante->prox = prioriza->prox;
        prioriza->prox->ante = prioriza->ante;
    }
    prioriza->ante = NULL;
    prioriza->prox = l->head;
    l->head->ante = prioriza;
    l->head = prioriza;
    printf("\n * -> O documento %s recebeu prioridade e será o próximo da fila de impressao.\n\n", prioriza->nome);
}
