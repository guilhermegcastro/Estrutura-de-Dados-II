/**
* @file object2.c
* @author @guilhermegcastro
* @date 2026-06-01
* @brief
**/

#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node{
    void* object;
    struct Node* left;
    struct Node* right;
    void* (*print)(void*);
}Node;

typedef Node* Object;

Object new_Object(){
    Object o = malloc(sizeof(Node));
    o->object = o->left = o->right = NULL;
    return o;
}
#endif
