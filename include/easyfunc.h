/**
* @file easyfunc.h
* @author @guilhermegcastro
* @date 2026-04-02
* @brief FUNÇÕES FÁCEIS PARA USAR NOS MEUS CÓDIGOS...
**/

#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <time.h>

void next(char* label){
    if (label!=NULL){
        printf("%s", label);
    }
    while(getchar()!='\n');
    getchar();
    system("clear");
}

void header(char* c, int t, char* h){
    for (int i = 0; i < t; i++){
        if(i==t/2) {
            printf("%s", h);
            continue;
        }
        printf("%s", c);
    }
    putchar('\n');
}

