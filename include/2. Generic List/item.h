/**
* @file item.h
* @author @guilhermegcastro
* @date 2026-05-24
* @brief
**/
#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "object1.h"

enum{ATAQUE, DEFESA};

typedef struct __Item{
    char* nome;
    int tipo; 
    int valor;
}__Item;

typedef __Item* Item;

Object new_Item(char* nome, int tipo, int valor){
    Object no = new_Object();
    Item ni = (Item)malloc(sizeof(__Item));
    ni->nome = (char*)malloc(strlen(nome)+1);
    strcpy(ni->nome, nome);
    ni->tipo = tipo;
    ni->valor = valor;
    no->item = ni;
    return no;
}
#endif
