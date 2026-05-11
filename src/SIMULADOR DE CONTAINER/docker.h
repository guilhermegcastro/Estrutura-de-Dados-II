/**
* @file docker.h
* @author @guilhermegcastro
* @date 2026-05-08
* @brief
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct TypeContainer* Container;
typedef struct TypeImage* Image;
typedef struct TypeListContainer* ListCon;
typedef struct TypeListImage* ListIma;

typedef struct TypeContainer{
    char* name;
    int id;
    int exe;
    struct TypeContainer* next;
    struct TypeContainer* previous;
    struct TypeImage* image; //Guarda o ponteiro da imagem relacionada.
}TypeContainer; // Criando o Ponteiro do Container.

typedef struct TypeImage{ 
    char* name;
    int id;
    struct TypeImage* next;
    struct TypeImage* previous;
    ListCon listC; // Cada Imagem Possui sua lista de Containers.
}TypeImage; // ... Ponteiro das imagens.

typedef struct TypeListContainer{ 
    Container head;
    Container tail;
    int cont;
}TypeListContainer; // Criando a Lista de Containers.

typedef struct TypeListImage{
    Image head;
    Image tail;
    int cont;
}TypeListImage; // ... Lista de Imagens.

ListCon new_listC(){
    ListCon new = malloc(sizeof(TypeListContainer));
    new->head = NULL;
    new->tail = NULL;
    new->cont = 0; 
    return new;
}

ListIma new_listI(){
    ListIma new = malloc(sizeof(TypeListImage));
    new->head = NULL;
    new->tail = NULL;    
    new->cont = 0; 
    return new;
}

void clear_listC(ListCon l){
    if(!l)
        return;
    Container atual = l->head;
    Container proximo;
    while(atual){
        proximo = atual->next;
        free(atual->name);
        free(atual);
        atual = proximo;
    }
    free(l);
}

void next(char* label){
    if(label!=NULL)
        printf("%s", label); 
    while(getchar()!='\n');
    getchar();
    system("clear");
};
