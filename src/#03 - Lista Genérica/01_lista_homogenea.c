/**
* @file 01_lista_homogenea.c
* @author @guilhermegcastro
* @date 2026-06-01
* @brief
**/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <time.h>
#include "object.h" 
#include "list.h" 
#include "player.h" 

#define new(Type, ...) new_##Type(__VA_ARGS__)

int main(){
    srand(time(NULL));
    List lst = new(List);

    for(int i=0; i<5; i++){
		char name[100];
		sprintf(name,"%s%d","player",i+1);
		Object p1 = new(Player, name, 50+rand()%50, rand()%6);
		list_enqueue(lst, p1);
        
    }
    
    printf("\n--- Lista antes do Bônus ---\n");
    foreach(lst, print_Player);
    BonusContext bonus = new(BonusContext, HUMAN, 50);
    for (int i = 0; i < 6; i++){
        bonus->type = i;
        foreach_ctx(lst, set_Bonus, bonus);
         bonus->bonus -= 15;
    }
 
    printf("\n--- Lista após o Bônus ---\n");
    foreach(lst, print_Player);
    
    return 0;
}
