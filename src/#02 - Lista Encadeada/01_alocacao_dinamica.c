/**
* @file Alocação Dinâmica.c
* @author @guilhermegcastro
* @date 2026-03-31
* @brief Defina um novo tipo Document para armazenar os dados de um arquivo enviado para impressão (nome do arquivo, número de páginas, tamanho em bytes do arquivo).
* Declare um ponteiro (não uma variável) do tipo Document.
* Faça uma função que (utilizando Alocação Dinâmica) cria uma tarefa de impressão para um Documento, e outra Função para simular a impressão desse documento, tal como nos protótipos a seguir…
* Document* doc = new_Document("doc.pdf",5,180);
* print_Document(doc);
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100];
    int page;
    int byte;
}Document;

Document* new_Document(char n[], int p, int b){
    Document* d = malloc(sizeof(Document));
    strcpy(d->name, n);
    d->page = p;
    d->byte = b;
    return d;
}

void delete_Document(Document* d){
    if(d!=NULL) {
        free(d);
        printf("> MEMÓRIA DO DOCUMENTO LIBERADA.\n");
    }
}

void print_Document(Document* d){
    printf(
        "Nome: %s\n"
        "Páginas: %d\n"
        "Bytes: %d\n",
        d->name, d->page, d->byte);
    
}
int main() {
    
    Document* doc = new_Document("doc.pdf", 5, 180);
    print_Document(doc);
    delete_Document(doc);
    doc=NULL;
    return 0;
}


