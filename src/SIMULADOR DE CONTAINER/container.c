/**
* @file container.c
* @author @guilhermegcastro
* @date 2026-05-04
* @brief 
* Container é uma tecnologia de virtualização leve que permite empacotar ambientes e aplicações facilitando a portabilidade e a execução de modo independente à plataforma subjacente.
* Em geral, todo container é baseado em uma imagem, que é o modelo pronto contendo todos os recursos necessários para a sua execução.
* Em outras palavras, todo conteiner deriva de uma imagem.
* 
* Desenvolva um protótipo de software para gestão de imagens e containers (p. Ex. Docker) para servidores.
* O software deve gerenciar os recursos através de **listas dinamicamente encadeadas**
* 
* >> As seguintes opções devem ser fornecidas...
* 1. Baixar Imagem (corresponde a criar uma nova imagem)
* 2. Excluir Imagem (só pode-se excluir uma imagem se não existir nenhum container vinculado a ele) 
* 3. Criar Container (todo container deve se basear em uma Imagem já baixada, quando criado um container já entra em execução automaticamente)
* 4. Interromper container (parar a execução de um container, a interrupção não significa exclusão)
* 5. Iniciar container (colocar um container interrompido em execução)
* 6. Excluir container (só pode-se excluir um container se ele estiver interrompido)
* 7. Listar todos as imagens
* 8. Listar todos os containers e status
*  #### Sugestões #####
* 
* IDs automáticos/autoincremento para ambas entidades.
* Todo container e imagem tbm deve possuir um nome de identificacao.
* Toda imagem possui ponteiro para sua lista de container, ou seja, lista de imagens, onde cada nó aponta para uma lista de containers
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "docker.h"

int interface(){
    int opcao;
    system("clear");
    printf(
        "~   ### CONTAINER MENU ###   ~\n\n "
        "1 - Baixar Imagem\n " 
        "2 - Excluir Imagem\n "
        "3 - Criar Container\n "
        "4 - Interromper Container\n "
        "5 - Iniciar Container\n "
        "6 - Excluir Container\n "
        "7 - Listar Imagens\n "
        "8 - Listar Containers\n\n");
    printf(" > Insira uma opção da lista: > ");
    int valida = scanf(" %d", &opcao);
    if(valida!=1)
        opcao = -1;
    return opcao;
}

Image busca_Imagem(ListIma l, int id){
    Image alvo = l->head;
    while(alvo){
        if(alvo->id == id) 
            return alvo;
        alvo = alvo->next;
    }
    return NULL;
}

Container busca_Container(ListIma l, int id){
    Image alvo1 = l->head;
    while(alvo1){
        Container alvo = alvo1->listC->head;
        while(alvo){
            if(alvo->id == id) 
                return alvo;
            alvo = alvo->next;
        }
        alvo1 = alvo1->next;
    }
    return NULL;
}

void listar_Imagem(ListIma l){
    Image alvo = l->head; 
    if(!alvo){
        printf("Sem Imagens para listar!");
        return;
    }
    system("clear");
    printf("~ ### LISTA DE IMAGENS ### ~\n");
    while(alvo){
        printf(" ID: %2d | NOME: %s\n", alvo->id, alvo->name);
        alvo = alvo->next;
    }
    printf(" FIM DA LISTA");
   
}

void baixar_Imagem (ListIma l, int *c){
    
    char nome[100];
    printf(" > Insira o nome da nova Imagem >  ");
    scanf(" %[^\n]99", nome);
    Image nova = malloc(sizeof(TypeImage));
    nova->name = malloc(strlen(nome)+1);
    strcpy(nova->name, nome);
    nova->id = (*c)++;
    nova->listC = new_listC();
    if(!l->head) { // Se não há cabeça, ele é o primeiro.
        nova->previous = nova->next = NULL; // O anterior e o próximo são nulos, já que só existe uma imagem na lista.
        l->head = l->tail = nova; // O head e o tail são os mesmos.
        return;
    }
    l->tail->next = nova; // Se ele não for o primeiro, ele sempre virá depois do último.
    nova->previous = l->tail; // Ele aponta de volta para o último...
    l->tail = nova; //Ele se torna o último.
}


void excluir_imagem(ListIma l){
    system("clear");
    if(!l->head){
        next("Sem imagens para excluir! Pressione ENTER...");
        return;
    }
    listar_Imagem(l);
    int id;
    printf("\nInsira o ID da imagem que deseja deletar: > ");
    scanf(" %d", &id);
    Image alvo = busca_Imagem(l, id);
    if(!alvo){
        next(" ID inexistente. Aperte ENTER...");
        return;
    }
    if(alvo->listC->head){
        next("A imagem solicitada não pode ser excluída por possuir containers!  Aperte ENTER...");
        return;
    }
    
    if(alvo == l->head && l->head == l->tail){ // Se a imagem for a única da lista...
        l->head = l->tail = NULL;
    } else if(alvo == l->head){ // Se a imagem deletada for o head...
        l->head = alvo->next;
        l->head->previous = NULL;
    } else if(alvo == l->tail){ // Se a imagem deletada for o tail...
        l->tail = alvo->previous;
        l->tail->next = NULL;
    } else { // Se a imagem deletada estiver dentro da lista...
        alvo->previous->next = alvo->next;
        alvo->next->previous = alvo->previous;
    }
    clear_listC(alvo->listC);
    free(alvo->name);
    free(alvo);
    next("A imagem foi deletada com sucesso! Aperte ENTER...");
}


int listar_Container(ListIma l){
    Image alvo = l->head; 
    int flag = 0;
    if(!alvo){
        printf("Não há imagens baixadas!");
        return 0;
    }
    system("clear");
    printf("~ ### LISTA DE CONTAINERS ### ~\n");
    while(alvo){
        Container alvo2 = alvo->listC->head;
        if(alvo2) 
            printf("\n [ %s IMAGEM ]\n", alvo->name);
        while(alvo2){
            flag = 1;
            printf(" ID: %2d | NOME: %-30s | STATUS: %s \n", alvo2->id, alvo2->name, (alvo2->exe)? "Em execução" : "Interrompido");
            alvo2 = alvo2->next;
        }
        alvo = alvo->next;
    }
    (flag) ? printf(" FIM DA LISTA") : printf("Não há containers criados!");
    return flag;
}


void criar_Container (ListIma l, int *c){
    
    if(!l->head){
        next("Não há imagens baixadas para basear o container! Aperte Enter...");
        return;
    }
    listar_Imagem(l);
    int id;
    printf(" > Insira o ID da imagem que será baseada > ");
    scanf(" %d", &id);
    Image imagem = busca_Imagem(l, id);
    
    if(!imagem){
        next("ID não encotrado. Aperte ENTER para prosseguir...");
        return;
    }
    char nome[100];
    printf(" > Insira o nome do novo container >  ");
    scanf(" %[^\n]99", nome);
    Container novo = malloc(sizeof(TypeContainer));
    novo->name = malloc(strlen(nome)+1);
    strcpy(novo->name, nome);
    novo->id = (*c)++;
    novo->exe = 1; // Está sendo executado.
    novo->image = imagem;
    novo->next = NULL;
    
    if(!imagem->listC->head) { // Se não há cabeça, ele é o primeiro.
        novo->next = novo->previous = NULL; // O anterior e o próximo são nulos, já que só existe um container na lista.
        imagem->listC->head = imagem->listC->tail = novo; // O head e o tail são os mesmos.
        return;
    }
    imagem->listC->tail->next = novo; // Se ele não for o primeiro, ele sempre virá depois do último.
    novo->previous = imagem->listC->tail; // Ele aponta de volta para o último...
    imagem->listC->tail = novo; //Ele se torna o último.
    
}

void interromper_container(ListIma l){
    if(!listar_Container(l)){
        return;
    }
    int id;
    printf("Informe o ID do container  em execucação que será interrompido: > ");
    scanf(" %d", &id);
    Container alvo = busca_Container(l, id);
    if(!alvo){ 
        next("O ID informado não existe!");
        return;
    }
    if(!alvo->exe){
        next("O Container selecionado já está interrompido!");
        return;
    }
    alvo->exe = 0;
    printf("O container %s foi interrompido.", alvo->name);
    next(" Aperte ENTER para prosseguir... ");
}

void executar_container(ListIma l){
    if(!listar_Container(l)){
        return;
    }
    int id;
    printf("Informe o ID do container interrompido que entrará em execução: > ");
    scanf(" %d", &id);
    Container alvo = busca_Container(l, id);
    if(!alvo){ 
        next("O ID informado não existe!");
        return;
    }
    if(alvo->exe){
        next("O Container selecionado já está em execução!");
        return;
    }
    alvo->exe = 1;
    printf("O container %s entrou em execução.", alvo->name);
    next(" Aperte ENTER para prosseguir... ");
}


void deletar_container(ListIma l){
    
     system("clear");
    if(!l->head){
        next("Sem imagens baixadas! Pressione ENTER...");
        return;
    }
    listar_Container(l);
    int id;
    printf("\nInsira o ID do container interrompido que deseja deletar: > ");
    scanf(" %d", &id);
    Container alvo = busca_Container(l, id);
    if(!alvo){
        next(" ID inexistente. Aperte ENTER...");
        return;
    }
    if(alvo->exe){
        next("O container selecionado não está interrompido!");
        return;
    }
    if(alvo == alvo->image->listC->head && alvo == alvo->image->listC->tail){ //Se o container for o único da lista...
     alvo->image->listC->head = alvo->image->listC->tail = NULL;
    }  else if(alvo == alvo->image->listC->head){ // Se o container deletado for o head...
        alvo->image->listC->head = alvo->next;
       alvo->image->listC->head->previous = NULL;
    } else if(alvo == alvo->image->listC->tail){ // Se o container deletado for o tail...
       alvo->image->listC->tail = alvo->previous;
        alvo->image->listC->tail->next = NULL;
    } else { // Se a imagem deletada estiver dentro da lista...
        alvo->previous->next = alvo->next;
        alvo->next->previous = alvo->previous;
    }
    free(alvo->name);
    free(alvo);
    next("O container foi deletado com sucesso! Aperte ENTER...");
    
}

int main() {
    ListIma ListaImagem = new_listI();
    int contI=0, contC=0;
    
    while(1){
        switch (interface()){
            case 1: baixar_Imagem(ListaImagem, &contI);
                break;
            case 2: excluir_imagem(ListaImagem);
                break;
            case 3: criar_Container(ListaImagem, &contC);
                break;
            case 4: interromper_container(ListaImagem);
                break;
            case 5: executar_container(ListaImagem);
                break;
            case 6: deletar_container(ListaImagem);
                break;
            case 7: listar_Imagem(ListaImagem);
                next(" Pressione ENTER...");
                break;
            case 8: listar_Container(ListaImagem);
                next(" Pressione ENTER...");
                break;
            default:
        }
    }
    return 0;
}


