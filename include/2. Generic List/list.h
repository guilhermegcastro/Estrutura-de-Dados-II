/**
* @file List.h
* @author @guilhermegcastro
* @date 2026-05-27
* @brief
**/

#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>
#include "object2.h"

typedef struct _List{
    Object head; 
    Object tail;
    int size;
}_List;
typedef struct _List* List; // Abstração para lista.

List new_List(){
    List n = (List)malloc(sizeof(_List)); 
    n->head = NULL; // Aponta para nulo.
    n->tail = NULL; // ´´
    n->size = 0; // Inicia com zero (Vazio)
    return n;
}

 void list_push(List l, Object o){
     l->size++; //Incrementa +1 objeto.
     if(!l->head){ //Se não há head, o objeto é o primeiro.
        l->head = l->tail = o;
        return;
     } 
     o->right = l->head; // O objeto aponta para o head atual.
     l->head->left = o; // O head aponta de volta para o objeto.
     l->head = o; // O head se torna o objeto.
     
 }
 
  void list_enqueue(List l, Object o){
     l->size++; //Incrementa +1 objeto.
     if(!l->tail){ //Se não há tail, o objeto é o primeiro.
        l->head = l->tail = o;
        return;
     } 
     o->left = l->tail; // O objeto aponta de volta para o tail atual.
     l->tail->right = o; // O tail aponta para o objeto.
     l->tail = o; // O tail se torna o objeto.
     
 }
 
 Object list_pop(List l){
     if(!l->head) return NULL; //Se não há head, a lista está vazia!
    Object pop = l->head; // o pop sempre será o primeiro da lista.
    l->size--; //Decrementa -1 objeto.
    if(l->head == l->tail){ // Se o head e o tail forem iguais, significa que a lista só possui um elemento.
        l->head = l->tail = NULL; // Deixa nulo os ponteiros (Como só há 1 elemento, o left e right de ambos já estão nulos.)
    } else {
        l->head = l->head->right; //O novo head é o próximo da lista.
        l->head->left = NULL; // O anterior se torna nulo.
    }
    pop->right =  NULL; // desvincula ele da lista.
    return pop;
    
 }
 
 void list_print(List l){
    Object target = l->head;
    while(target){
        target->print;
        target = target->right;
    }
 }
 
 void list_clear(List l){
    Object target = l->head;
    while (target){
        Object prox = target->right;
        destroy(target);
        target = prox;
    }
    l->head = l->tail = NULL;
    l->size = 0;
 };
 
void foreach(List lst, void (*f)(Object)){
    Object o = lst->head;
    while(o){
        f(o);
        o = o->right;
    }
}

void foreach_ctx(List lst, void (*f)(Object, void*), void* ctx){
    Object o = lst->head;
    while(o){
        f(o, ctx);
        o = o->right;
    }
}
#endif
