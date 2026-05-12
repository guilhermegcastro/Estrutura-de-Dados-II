/**
* @file 04_fila.c
* @author @guilhermegcastro
* @date 2026-04-10
* @brief
* Refatorar o projeto de Impressão de Documentos, mas agora criando as seguintes estruturas...
* List (com head, tail e size)
* Função para construir e inicializar um objeto List
* Adaptar as funções da Lib Document para operar com o objeto List
* 
* Opções do sistema
* 1. Criar Documento
* 2. Fila de Impressão
* 3. Imprimir Documento
* 4. Excluir Documento
* 5. Priorizar Documento
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "documento.h"

int indice = 0; // Não usa variável global em Adriano se não quiser zerar a prova... :P Estou com preguiça te tirar.

void new_Doc(List l, char* n, int i, int b){
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

void print_List(List l){;
    Doc listagem = l->head;
    printf("TAMANHO DA FILA DA IMPRESSORA: %d Arquivo%s\n",  l->size, (l->size == 1)? " " : "s");
    while(listagem){
        printf(" ID: %d   NOME: %s  (%d bytes)\n", listagem->id, listagem->name, listagem->bytes);
        listagem = listagem->next;
    }
}

void doc_Print(List l){
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

void doc_Prio(List l){
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


void doc_Delete(List l){
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

int interface(){
    int op;
    header("-*-", 10, " IMPRESSORA DE DOCUMENTOS ");
    printf("1. Criar Documento\n"
    "2. Fila de Impressão\n"
    "3. Imprimir Documento\n"
    "4. Priorizar Documento\n"
    "5. Excluir Documento\n"
    "@- Insira a opção desejada: > ");
    int tratamento = scanf(" %d", &op);
    if(tratamento!=1)
        op = -1;
    system("clear");
    return op;
}

void novoDoc(List l){
    char name[261];
    int id = indice++;
    int size = 100 + rand()%500;
    system("clear");
    header("-*-", 10, " NOVO DOCUMENTO ");
    printf("@- Informe o nome do novo documento: > ");
        scanf(" %260[^\n]", name );
    next("+ . Documento criado! Aperte ENTER para prosseguir!");
    new_Doc(l, name, id, size);
}

int main() {
    srand(time(NULL));
    List lista = new_List();
    while (1){
        switch (interface()){
            case 1: novoDoc(lista);
                break;
            case 2: header(" -+- ", 10, "FILA DE IMPRESSÃO ");
                    print_List(lista);
                    next("\nAperte ENTER para prosseguir...");
                break;
            case 3: header(" -+- ", 15, " IMPRIMINDO DOCUMENTO ");
                    doc_Print(lista);
                    next("\nAperte ENTER para prosseguir...");
                break;
            case 4: header(" -+- ", 15, " PRIORIZAR DOCUMENTO ");
                    doc_Prio(lista);
                    next("\nAperte ENTER para prosseguir... ");
                break;
            case 5: header(" -+- ", 15, " DELETAR DOCUMENTO ");
                    doc_Delete(lista);
                    next("\nAperte ENTER para prosseguir... ");
                break;
            default: while(getchar()!='\n');
        }
    }
    return 0;
}


