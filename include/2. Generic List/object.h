/**
* @file object1.h
* @author @guilhermegcastro
* @date 2026-05-27
* @brief
**/
#ifndef OBJECT1_H
#define OBJECT1_H

#include <stdio.h>
#include <stdlib.h>


typedef enum{
	PLAYER, ARMA, NPC,
}TypeNode;

typedef struct Node{
    void* item; 
    TypeNode type; // Tipo do Objeto.
    struct Node* left; // Objeto anterior
    struct Node* right; // Objeto seguinte
}Node;

typedef Node* Object; //Abstração do Ponteiro.

Object new_Object(){
    Object n = (Object)malloc(sizeof(Node)); 
    n->item = NULL; // Objeto nasce nulo.
    n->left = NULL; // Aponta para nulo.
    n->right = NULL; // ´´ 
    return n;
}

void destroy(Object o){
    if(!o) return; // Se não há objeto, retorna;
    if(o->item) //Se o objeto possui algum item, libera o item.
        free(o->item); 
    free(o);
}

#endif
