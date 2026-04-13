/**
* @file 04_fila.c
* @author @guilhermegcastro
* @date 2026-04-10
* @brief
* Refatorar o projeto de Impressão de Documentos, mas agora criando as seguintes estruturas...
* List (com head, tail e size)
* Função para construir e inicializar um objeto List
* Adaptar as funções da Lib Document para operar com o objeto List
* 
* Opções do sistema
* 1. Criar Documento
* 2. Fila de Impressão
* 3. Imprimir Documento
* 4. Excluir Documento
* 5. Priorizar Documento
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "easyfunc.h"
#include "04_fila.h"

int indice = 0;

int interface(){
    int op;
    header("-*-", 10, " IMPRESSORA DE DOCUMENTOS ");
    printf("1. Criar Documento\n"
    "2. Fila de Impressão\n"
    "3. Imprimir Documento\n"
    "4. Priorizar Documento\n"
    "5. Excluir Documento\n"
    "@- Insira a opção desejada: > ");
    int tratamento = scanf(" %d", &op);
    if(tratamento!=1)
        op = -1;
    system("clear");
    return op;
}

void novoDoc(List l){
    char name[261];
    int id = indice++;
    int size = 100 + rand()%500;
    system("clear");
    header("-*-", 10, " NOVO DOCUMENTO ");
    printf("@- Informe o nome do novo documento: > ");
        scanf(" %260[^\n]", name );
    next("+ . Documento criado! Aperte ENTER para prosseguir!");
    new_Doc(l, name, id, size);
}

int main() {
    srand(time(NULL));
    List lista = new_List();
    while (1){
        switch (interface()){
            case 1: novoDoc(lista);
                break;
            case 2: header(" -+- ", 10, "FILA DE IMPRESSÃO ");
                    print_List(lista);
                    next("\nAperte ENTER para prosseguir...");
                break;
            case 3: header(" -+- ", 15, " IMPRIMINDO DOCUMENTO ");
                    doc_Print(lista);
                    next("\nAperte ENTER para prosseguir...");
                break;
            case 4: header(" -+- ", 15, " PRIORIZAR DOCUMENTO ");
                    doc_Prio(lista);
                    next("\nAperte ENTER para prosseguir... ");
                break;
            case 5: header(" -+- ", 15, " DELETAR DOCUMENTO ");
                    doc_Delete(lista);
                    next("\nAperte ENTER para prosseguir... ");
                break;
            default: while(getchar()!='\n');
        }
    }
    return 0;
}


