/**
* @file subject.c
* @author @guilhermegcastro
* @date 2026-06-01
* @brief Implementação do objeto Disciplina para Lista Heterogênea
**/

#ifndef SUBJECT_H
#define SUBJECT_H

#define new(TYPE, ...) new_##TYPE(__VA_ARGS__)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object2.h"

// Enum para identificar se a disciplina é Obrigatória ou Optativa
enum { MANDATORY, ELECTIVE };

typedef struct _Subject {
    char* name;      // Nome da disciplina (ex: "Estrutura de Dados II")
    int ch;          // Carga Horária (ex: 60, 80)
    int period;      // Período correspondente (ex: 3)
    char type[15];   // Texto: "OBRIGATORIA" ou "OPTATIVA"
} _Subject;

typedef _Subject* Subject;

// Função de impressão genérica amarrada à struct
void* print_Subject(void* item) {
    Object o = (Object)item;
    Subject s = (Subject)o->object; // Alvo extraído do nó genérico
    
    printf("DISCIPLINA: %s | CH: %d horas | PERÍODO: %dº | TIPO: %s\n", 
            s->name, s->ch, s->period, s->type);
            
    return NULL;
}

// Construtor da Disciplina
Object new_Subject(char name[], int ch, int period, int type_enum) {
    Subject s = malloc(sizeof(_Subject));
    
    s->name = malloc(strlen(name) + 1);
    strcpy(s->name, name);
    
    s->ch = ch;
    s->period = period;
    
    // Define a string com base no enum recebido
    strcpy(s->type, (type_enum == MANDATORY) ? "OBRIGATORIA" : "OPTATIVA");
    
    // Cria o encapsulador genérico da sua biblioteca
    Object o = new(Object);
    o->object = s;
    o->print = print_Subject; // Carimba a função de exibição de disciplinas no nó
    
    return o;
}

#endif
