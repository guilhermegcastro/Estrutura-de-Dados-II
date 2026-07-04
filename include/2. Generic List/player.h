/**
* @file Player.h
* @author @guilhermegcastro
* @date 2026-05-27
* @brief
**/

#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"

enum{ HUMAN, GOBLIN, ELF, GHOST, ZOMBIE, DEMON};
#define new(Type, ...) new_##Type(__VA_ARGS__)

typedef struct _Player{
    char* name; 
    int hp;
    int race;
    char racename[10];
}_Player;

typedef _Player* Player;

typedef struct _BonusContext{
    int type;
    int bonus;
}_BonusContext;

typedef _BonusContext* BonusContext;



Object new_Player(char* name, int hp, int race){
    Player n = malloc(sizeof(_Player));
    n->name = malloc(strlen(name)+1);
    strcpy(n->name, name);
    n->hp = hp;
    n->race = race;
   switch (n->race){
        case HUMAN: strcpy(n->racename, "Humano");
            break;
        case GOBLIN: strcpy(n->racename, "Goblin");
            break;
        case ELF: strcpy(n->racename, "Elfo");
            break;
        case ZOMBIE: strcpy(n->racename,"Zumbi");
            break;
        case GHOST: strcpy(n->racename,"Fantasma");
            break;
         case DEMON: strcpy(n->racename,"Demônio");
            break;
    }
    Object o = new(Object);
    o->item = n;
    o->type = PLAYER;
    return o;
}

void print_Player(Object o){
    if(!o || o->type != PLAYER) return;
    Player p = (Player)o->item;
    printf("NOME: %s | HP: %d | RAÇA: %s\n", p->name, p->hp, p->racename);    
}

BonusContext new_BonusContext(int race, int bonus){
    BonusContext  b = malloc(sizeof(_BonusContext));
    b->bonus = bonus;
    b->type = race;
    return b;
}

void set_Bonus(Object o, void* ctx){
    Player p = (Player)o->item;
    BonusContext b = (BonusContext)ctx;
    if(b->type!= p->race) return;
    p->hp += b->bonus;
    if(b->bonus)
        printf("O %s (%s) recebeu um %s%dHP!\n", p->name, p->racename, (b->bonus>0) ? "bônus de +" : "nerf de ", b->bonus);
}
#endif
