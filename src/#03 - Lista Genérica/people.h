/**
* @file people.c
* @author @guilhermegcastro
* @date 2026-06-01
* @brief
**/

#ifndef PEOPLE_H
#define PEOPLE_H
#define new(TYPE, ...) new_##TYPE(__VA_ARGS__)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "object2.h"
enum {MALE, FEMALE};

typedef struct _People{
    char* name; 
    int age;
    int sex;
    char sextype[10];
}_People;

typedef _People* People;

void* print_People(void* item){
    Object o = (Object)item;
    People p = (People)o->object;
    printf("NOME: %s | IDADE: %d | SEXO: %s\n", p->name, p->age, p->sextype);
    return NULL;
}

Object new_People(char name[], int age, int sex){
    People p = malloc(sizeof(_People));
    p->name = malloc(strlen(name)+1);
    strcpy(p->name, name);
    p->age = age;
    p->sex = sex;
    strcpy(p->sextype, (p->sex == MALE) ? "MASCULINO" : "FEMININO");
    Object o = new(Object);
    o->object = p;
    o->print = print_People;
    return o;
}
#endif
