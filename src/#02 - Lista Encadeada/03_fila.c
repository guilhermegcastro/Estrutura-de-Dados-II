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
#include "documento.h"

int indice = 0; // Proibido usar variável global em E.D. com Adriano... So não vou mudar porque to com preguiça :P

Doc printDoc(Doc doc){
    printf("IMPRIMINDO DOCUMENTO\n");
    if(!doc){
        next("Sem documentos para imprimir! APERTE ENTER...");
        return doc;
    }
    printf(" O Documento %s (%d) foi impresso!\n", doc->name, doc->bytes);
    next("APERTE ENTER...");
    Doc new_head = doc->next;
    free(doc);
    return new_head;
}

Doc new_Document(Doc list, char* n, int i, int b){
    Doc d = malloc(sizeof(Doc));
    d->name = malloc(strlen(n)+1);
    strcpy(d->name, n);
    d->id = i;
    d->bytes = b;
    if(list)
        list->next = d;
    d->next = NULL;
    return d;
}

void printLista(Doc list){
    if(!list){
        next("Sem documentos na fila! PRESSIONE ENTER...");
        return;
    }
    printf(" ID - NOME\n");
    while(list){
        printf(" %2d   %-30s (%d bytes)\n", list->id, list->name, list->bytes);
        list = list->next;
    }
}

Doc anterior(Doc alvo, Doc list){
    while(list){
        if(list->next == alvo)
            return list;
        list = list->next;
    }
    return NULL;
}

void excluirDoc(Doc head, Doc tail){
    system("clear");
    printf("EXCLUIR DOCUMENTO\n");
    printLista(head);
    if(!head)
        return;
    int id;
    printf("INSIRA O ID DO DOCUMENTO QUE DESEJA DELETAR: > ");
    scanf(" %d", &id);
    Doc alvo;
    if((head)->id == id){
        alvo = (head)->next;
        free(head);
        head = alvo;
        printf("Documento %s deletado! Pressione ENTER...", (head)->name);
    } 
    alvo = head;
    while (alvo){
        if(alvo->id == id){
            Doc alvo_anterior = anterior(alvo, head);
            alvo_anterior->next = alvo->next;
            if(alvo == tail)
                tail = alvo_anterior;
            printf("Documento %s deletado! Pressione ENTER...", alvo->name);
            free(alvo);
            next(NULL);
        }
        alvo = alvo->next;
    }
    
}
void docPrio(Doc head, Doc tail){
    system("clear");
    printf("PRIORIZAR DOCUMENTO\n");
    printLista(head);
    if(!head)
        return;
    int id;
    printf("INSIRA O ID DO DOCUMENTO QUE DESEJA PRIORIZAR: > ");
    scanf(" %d", &id);
    if((head)->id == id) {
        next(" O ID do documento informado já está na frente da fila!\n PRESSIONE ENTER...");
        return;
    }
    Doc alvo = (head)->next;
    while(alvo){
        if(alvo->id == id){
            Doc antes_alvo = anterior(alvo, head);
            antes_alvo->next = alvo->next;
            if(alvo == tail)
               tail = antes_alvo;
            alvo->next = head;
            head = alvo;
            system("clear");
            printf("PRIORIZAR DOCUMENTO");
            printLista(head);
            printf("Documento %s inserido no inicio da fila! PRESSIONE ENTER...", (head)->name);
            next(NULL);
            return;
        }
        alvo = alvo->next;
    }
    next("ID não encontrado! PRESSIONE ENTER...");
    return;
}

Doc novoDoc(Doc list){
    system("clear");
    char name[100];
    int id = indice, bytes = 100 + rand()%500;
    indice++;
    printf("NOVO DOCUMENTO\n");
    printf("Insira o nome do arquivo: ");
    scanf(" %[^\n]", name);
    next("DOCUMENTO CRIADO! PRESSIONE ENTER...");
    return new_Document(list, name, id, bytes);
}

int interface(){
    int opt;
    printf("IMPRESSORA\n");
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
    Doc list_head = NULL;
    Doc list_tail = NULL;
    while(1){
        switch (interface()){
            case 1: 
                list_tail = novoDoc(list_tail);
                if(!list_head)
                    list_head = list_tail;
                break;
            case 2: 
                system("clear");
                printf("FILA DE IMPRESSÃO\n");
                printLista(list_head);
                if(list_head)
                    next("FIM DA LISTA! PRESSIONE ENTER...");
                break;
            case 3: 
                list_head = printDoc(list_head);
                break;
            case 4: excluirDoc(list_head, list_tail);
                break;
            case 5: docPrio(list_head, list_tail);
                break;
            default: next("Opção inválida. Aperte ENTER...");
        }
    }
}
