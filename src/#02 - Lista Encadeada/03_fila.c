/**
* @file 03_fila.c
* @author @guilhermegcastro
* @date 2026-04-02
* @brief 
* 1. Criar Documento
* 2. Fila de Impressão
* 3. Imprimir Documento
* 4. Excluir Documento
* 5. Priorizar Documento
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "easyfunc.h"

typedef struct Doc {
    char* nome;
    int id; 
    int bytes;
    struct Doc* prox;
}Doc;

int indice = 0;

Doc* printDoc(Doc* doc){
    header(" - ", 11, " IMPRIMINDO DOCUMENTO ");
    if(!doc){
        next("Sem documentos para imprimir! APERTE ENTER...");
        return doc;
    }
    printf(" O Documento %s (%d) foi impresso!\n", doc->nome, doc->bytes);
    next("APERTE ENTER...");
    Doc* new_head = doc->prox;
    free(doc);
    return new_head;
}

Doc* new_Document(Doc* list, char* n, int i, int b){
    Doc* d = malloc(sizeof(Doc));
    d->nome = malloc(strlen(n)+1);
    strcpy(d->nome, n);
    d->id = i;
    d->bytes = b;
    if(list)
        list->prox = d;
    d->prox = NULL;
    return d;
}

void printLista(Doc* list){
    if(!list){
        next("Sem documentos na fila! PRESSIONE ENTER...");
        return;
    }
    printf(" ID - NOME\n");
    while(list){
        printf(" %2d   %-30s (%d bytes)\n", list->id, list->nome, list->bytes);
        list = list->prox;
    }
}

Doc* anterior(Doc* alvo, Doc* list){
    while(list){
        if(list->prox == alvo)
            return list;
        list = list->prox;
    }
    return NULL;
}

void excluirDoc(Doc** head, Doc** tail){
    system("clear");
    header(" - ", 11, " EXCLUIR DOCUMENTO ");
    printLista(*head);
    if(!*head)
        return;
    int id;
    printf("INSIRA O ID DO DOCUMENTO QUE DESEJA DELETAR: > ");
    scanf(" %d", &id);
    Doc* alvo;
    if((*head)->id == id){
        alvo = (*head)->prox;
        free(*head);
        *head = alvo;
        printf("Documento %s deletado! Pressione ENTER...", (*head)->nome);
    } 
    alvo = *head;
    while (alvo){
        if(alvo->id == id){
            Doc* alvo_anterior = anterior(alvo, *head);
            alvo_anterior->prox = alvo->prox;
            if(alvo == *tail)
                *tail = alvo_anterior;
            printf("Documento %s deletado! Pressione ENTER...", alvo->nome);
            free(alvo);
            next(NULL);
        }
        alvo = alvo->prox;
    }
    
}
void docPrio(Doc** head, Doc** tail){
    system("clear");
    header(" - ", 11, " DOCUMENTO PRIORITÁRIO ");
    printLista(*head);
    if(!*head)
        return;
    int id;
    printf("INSIRA O ID DO DOCUMENTO QUE DESEJA PRIORIZAR: > ");
    scanf(" %d", &id);
    if((*head)->id == id) {
        next(" O ID do documento informado já está na frente da fila!\n PRESSIONE ENTER...");
        return;
    }
    Doc* alvo = (*head)->prox;
    while(alvo){
        if(alvo->id == id){
            Doc* antes_alvo = anterior(alvo, *head);
            antes_alvo->prox = alvo->prox;
            if(alvo == *tail)
               *tail = antes_alvo;
            alvo->prox = *head;
            *head = alvo;
            system("clear");
            header(" - ", 11, " DOCUMENTO PRIORITÁRIO ");
            printLista(*head);
            printf("Documento %s inserido no inicio da fila! PRESSIONE ENTER...", (*head)->nome);
            next(NULL);
            return;
        }
        alvo = alvo->prox;
    }
    next("ID não encontrado! PRESSIONE ENTER...");
    return;
}

Doc* novoDoc(Doc* list){
    system("clear");
    char nome[100];
    int id = indice, bytes = 100 + rand()%500;
    indice++;
    header("=", 50, " NOVO DOCUMENTO ");
    printf("Insira o nome do arquivo: ");
    scanf(" %[^\n]", nome);
    next("DOCUMENTO CRIADO! PRESSIONE ENTER...");
    return new_Document(list, nome, id, bytes);
}

int interface(){
    int opt;
    header("=", 50, " IMPRESSORA ");
    printf(
        "1. Criar Documento\n"
        "2. Fila de Impressão\n"
        "3. Imprimir Documento\n"
        "4. Excluir Documento\n"
        "5. Priorizar Documento\n"
        "@- Insira a opção desejada: > ");
    scanf(" %d", &opt);
    return opt;
}

int main(){
    Doc* list_head = NULL;
    Doc* list_tail = NULL;
    while(1){
        switch (interface()){
            case 1: 
                list_tail = novoDoc(list_tail);
                if(!list_head)
                    list_head = list_tail;
                break;
            case 2: 
                system("clear");
                header("= ", 15, " FILA DE IMPRESSÃO ");
                printLista(list_head);
                if(list_head)
                    next("FIM DA LISTA! PRESSIONE ENTER...");
                break;
            case 3: 
                list_head = printDoc(list_head);
                break;
            case 4: excluirDoc(&list_head, &list_tail);
                break;
            case 5: docPrio(&list_head, &list_tail);
                break;
            default: next("Opção inválida. Aperte ENTER...");
        }
    }
}
