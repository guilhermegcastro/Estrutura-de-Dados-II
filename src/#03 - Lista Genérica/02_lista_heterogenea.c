/**
* @file 02_lista_heterogenea.c
* @author @guilhermegcastro
* @date 2026-06-01
* @brief
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "object2.h"
#include "list2.h"
#include "people.h"
#include "subject.h"
#define new(TYPE, ...) new_##TYPE(__VA_ARGS__)
int main() {
    List lista = new(List);
    Object n1 = new(People, "Cassandra", 30, FEMALE);
    list_enqueue(lista, n1);
    n1 = new(Subject, "ESTRUTURA DE DADOS II", 60, 3, MANDATORY);
    list_enqueue(lista, n1);
    n1 = new(People, "Alejandro", 30, MALE);
    list_enqueue(lista, n1);
    n1 = new(Subject, "ESTRUTURA DE DADOS IIIII", 1246, 30, ELECTIVE);
    list_enqueue(lista, n1);
    list_print(lista);
    
    return 0;
}


