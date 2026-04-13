/**
* @file 04_fila.h
* @author @guilhermegcastro
* @date 2026-04-10
* @brief
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


typedef struct TypeDoc{
    char* name;
    int id;
    int bytes;
    struct TypeDoc* next;
} TypeDoc;

typedef TypeDoc* Doc;

typedef struct TypeList{
    Doc head;
    Doc tail;
    int size;
}TypeList;

typedef  TypeList* List;

static List new_List(){
    List new = malloc(sizeof(TypeList));
    new->head = NULL;
    new->tail = NULL; 
    new->size = 0;
    return new;
}

static void new_Doc(List l, char* n, int i, int b){
    Doc new = malloc(sizeof(TypeDoc));
    new->name = malloc(strlen(n)+1);
    strcpy(new->name, n);
    new->id = i;
    new->bytes = b;
    new->next = NULL;
    l->size++;
    if(l->tail != NULL)
        l->tail->next = new;
    l->tail = new;
    if(!l->head)
        l->head = new;
}

static void print_List(List l){;
    Doc listagem = l->head;
    printf("TAMANHO DA FILA DA IMPRESSORA: %d Arquivo%s\n",  l->size, (l->size == 1)? " " : "s");
    while(listagem){
        printf(" ID: %d   NOME: %s  (%d bytes)\n", listagem->id, listagem->name, listagem->bytes);
        listagem = listagem->next;
    }
}

static void doc_Print(List l){
    if(!l->head) {
        printf("Sem documentos para imprimir!");
        return;
    }
    printf("\nO documento %s foi impresso!", l->head->name);
    Doc nex;
    l->size--;
    nex = l->head->next;
    free(l->head->name);
    free(l->head);
    l->head = nex;
    if(!l->head)
        l->tail=NULL;
}

static void doc_Prio(List l){
    if(!l->head){
        printf("Não há documentos na fila!");
        return;
    }
    print_List(l);
    int id;
    printf("@- Escolha o ID do arquivo que deseja priorizar: > ");
    scanf(" %d", &id);
    if(l->head->id == id) {
        printf("O arquivo \"%s\" já está no topo da fila! ", l->head->name);
        return;
    }
    Doc anterior = l->head;
    Doc alvo = anterior->next;
    while(alvo){
        if(alvo->id == id){
            if(alvo==l->tail)
                l->tail = anterior;
            anterior->next = alvo->next;
            alvo->next = l->head;
            l->head = alvo;
            system("clear");
            print_List(l);
            printf("O arquivo \"%s\" foi movido para o topo da fila!", l->head->name);
            return;
        }
        anterior = alvo;
        alvo = alvo->next;
    }
    printf("O ID informado é inexistente.");
}


static void doc_Delete(List l){
    if(!l->head){
        printf("Não há documentos na fila!");
        return;
    }
    system("clear");
    print_List(l);
    int id;
    printf("@- Escolha o ID do arquivo que deseja deletar: > ");
    scanf(" %d", &id);
    Doc atual = l->head;
    if(atual->id == id){
        l->head = atual->next;
        l->size--;
        system("clear");
        print_List(l);
        printf("O arquivo \"%s\" foi deletado da fila!", atual->name);
        free(atual->name);
        free(atual);
        return;
    } 
    while(atual){
        if(atual->next != NULL && atual->next->id == id){ 
           Doc alvo = atual->next;
           if(alvo == l->tail) { 
               l->tail = atual;
               atual->next = NULL;
            } // se o alvo for o ultimo, muda o tail para o anterior
            else // se ele nao for o ultimo, existe um ponteiro para ligar com o antecessor
                atual->next = alvo->next;
            l->size--;
            system("clear");
            print_List(l);
            printf("O arquivo \"%s\" foi deletado da fila!", alvo->name);
            free(alvo->name);
            free(alvo);
            return;
        }
        atual = atual-> next;
    }
    printf("O ID informado é inexistente.");
    
}
