/**
* @file 01_pilha.c
* @author @guilhermegcastro
* @date 2026-04-02
* @brief Implemente um sistema com duas opções (cadastrar item, listar itens).
* Item pode ser qualquer entidade (pessoa, documento, produto, aluno, disciplina, etc).
* O sistema deve conseguir armazenar dinamicamente qqr volume de dados, em uma --Lista Encadeada em formato pilha--
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "easyfunc.h"// Presente no diretório de ED2 no github.
#include "02_pilha.h" // Presente no diretório de ED2 no github.
#define ENTIDADE "Pessoa"


int interface();
Entity* novaPessoa(Entity* topo);

int main() {
	    Entity* topo = NULL;
        while (1){
            switch (interface()){
                case 1: topo = novaPessoa(topo); 
                    break;
                case 2: print_Entity(topo);
                    next("Aperte Enter para prosseguir...");
                    break;
                case 0: exit(0);
                default: next("Opção inválida! Aperte ENTER para prosseguir...");
            }
            
        }
        
    return 0;
}

int interface(){
    int opc;
    header("=-=", 25, " MENU ");
    printf( 
        "1 - Cadastrar %s\n"
        "2 - Listar %ss\n"
        "0 - Encerrar Programa\n"
        " >> Escolha a opção desejada: > ",
        ENTIDADE, ENTIDADE);
        scanf(" %d", &opc);
        return opc;
}

Entity* novaPessoa(Entity* topo){
    char n[100], s;
    int i;
    float p;
    system("clear");
    header("§/", 25, " CADASTRO ");
    printf(">> Insira o nome da %s: > ", ENTIDADE);
    scanf(" %99[^\n]", n);
    while(getchar()!='\n');
    printf(">> Insira a idade: > ");
    while(1){
        scanf(" %d", &i);
        if(i >= 0) break;
        printf("Não é permitido idade negativa! Insira outro valor: > ");
    }
    printf("Insira o sexo (M == MASCULINO, F == FEMININO): > ");
    while(1){
        scanf(" %c", &s);
        if(s == 'F' || s == 'f') {
            s = 'F';
            break;
        } else if (s == 'M' || s == 'm'){
            s = 'M';
            break;
        }
        printf("Opção inválida! Insira M ou F: > ");
    }
     printf(">> Insira o peso: > ");
    while(1){
        scanf(" %f", &p);
        if(i >= 0) break;
        printf("Não é permitido peso negativo! Insira outro valor: > ");
    }
    return new_Entity(topo, n, i, s, p);
};

