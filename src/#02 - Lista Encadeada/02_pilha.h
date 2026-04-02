/**
* @file cdstpessoa.h
* @author @guilhermegcastro
* @date 2026-04-02
* @brief header para ser utilizado com o código "02_pilha.c"
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Entity{
    char* nome;
    int idade;
    char sexo;
    float peso;
    struct Entity* prox;
}Entity;

Entity* new_Entity(Entity* topo, char* nome, int idade, char sexo, float peso){
    Entity* new = malloc(sizeof(Entity));
    new->nome = malloc(strlen(nome)+1);
    strcpy(new->nome, nome);
    new->idade = idade;
    new->sexo = sexo;
    new->peso = peso;
    new->prox = topo;
    topo = new;
    return new;
};

void print_Entity(Entity* entity){
  while(entity) {
      printf(">> NOME: %s | SEXO: %c | IDADE: %d | PESO: %.2f\n", entity->nome, entity->sexo, entity->idade, entity->peso);
      entity = entity->prox;
  };
    
};



