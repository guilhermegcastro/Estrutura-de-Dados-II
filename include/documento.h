/**
* @file documento.h
* @author @guilhermegcastro
* @date 2026-05-12
* @brief header para utilizar nos codigos "03_fila.c", "04_lista_generica.c" e "05_ponteiro_duplo.c".
**/

#include <stdio.h>
#include <stdlib.h>

typedef struct TypeDoc{
    char* name;
    int id;
    int bytes;
    int pg;
    struct TypeDoc* next;
    struct TypeDoc* previous;
} TypeDoc;

typedef TypeDoc* Doc;

typedef struct TypeList{
    Doc head;
    Doc tail;
    int size;
}TypeList;

typedef  TypeList* List;

List new_List(){
    List new = malloc(sizeof(TypeList));
    new->head = NULL;
    new->tail = NULL; 
    new->size = 0;
    return new;
}

void next(char* label){
    if (label!=NULL){
        printf("%s", label);
    }
    while(getchar()!='\n');
    getchar();
    system("clear");
}

void header(char* c, int t, char* h){
    for (int i = 0; i < t; i++){
        if(i==t/2) {
            printf("%s", h);
            continue;
        }
        printf("%s", c);
    }
    putchar('\n');
}

