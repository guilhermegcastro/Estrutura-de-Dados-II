/**
* @file playlist.c
* @author @guilhermegcastro
* @date 2026-05-12
* @brief 
* [DESAFIO PRÁTICO: GERENCIADOR DE PLAYLIST DINÂMICA]
* 
* Contexto: Simulação de um aplicativo de streaming onde a ordem das músicas 
* pode ser alterada manualmente e a memória deve ser gerida de forma rigorosa.
*
* Requisitos Técnicos:
* O software deve utilizar uma LISTA DUPLAMENTE ENCADEADA com ponteiros para 
* o início (head) e fim (tail).
*
* Funcionalidades Solicitadas:
*
* 1) Inserir após uma Música (CREATE):
*    - O usuário informa o ID de uma música já existente.
*    - A nova música deve ser inserida imediatamente após este nó.
*    - Deve-se tratar os casos de: lista vazia, inserção no meio e inserção após o tail.
*
* 2) Trocar de Posição (UPDATE DE ESTRUTURA):
*    - Solicitar dois IDs (A e B).
*    - Os nós devem trocar de lugar fisicamente na memória através da 
*      manipulação dos ponteiros 'next' e 'previous' (não vale apenas trocar os dados).
*
* 3) Remover por Artista (DELETE EM MASSA):
*    - Solicitar o nome de um artista e remover TODAS as músicas vinculadas a ele.
*    - A busca deve ser contínua até que não restem músicas do artista na lista.
*    - Cuidado redobrado para não perder a referência do 'próximo' ao dar free no 'atual'.
*
* 4) Exibir Playlist e Tempo Total (READ):
*    - Listar ID, Título, Artista e Duração.
*    - Ao final, exibir a soma total do tempo de todas as músicas da playlist.
*
* 5) Inversão Literal (REVERSE):
*    - Inverter fisicamente todos os ponteiros da lista.
*    - Ao final, o antigo head deve ser o tail, e o antigo tail deve ser o head.
*    - Todos os ponteiros 'next' e 'prev' de todos os nós devem ser trocados.
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct TyMusica{
    int id;
    char* titulo;
    char* artista;
    int tempo;
    struct TyMusica* next;
    struct TyMusica* previous;
}TyMusica;


typedef struct TyLista{
    TyMusica* head;
    TyMusica* tail;
    int id;
}TyLista;

typedef struct TyLista* Lista;
typedef struct TyMusica* Musica;

Lista construir_lista(){
    Lista nova = malloc(sizeof(TyLista));
    nova->head = NULL;
    nova->tail = NULL;
    nova->id = 1;
    return nova;
}
void printm(Musica m){
    printf("{%02d} %s - %-25s [%d:%d]\n", m->id, m->titulo, m->artista, m->tempo/60, m->tempo%60);
}


void next(char* label){
    if(label!=NULL)
        printf("%s", label);
    while(getchar()!='\n');
    getchar();
    system("clear");
}

int listar_musica(Lista l){
    Musica alvo = l->head;
    int totaltemp=0;
    while(alvo){
        printm(alvo);
        totaltemp+=alvo->tempo;
        alvo = alvo->next;
    }
    return totaltemp;
}

Musica buscar_musica(Lista l, int id){
     Musica alvo = l->head;
    while(alvo){
       if(alvo->id == id)
            return alvo;
        alvo = alvo->next;
    }
    return NULL;
}

void inserir_musica(Lista l){
    Musica nova = malloc(sizeof(TyMusica));
    char titulo[100], artista[100];
    int tempo;
    printf("{+} - Insira o nome da música: > ");
    scanf(" %[^\n]99", titulo);
    printf("{+} - Insira o nome do artista: > ");
    scanf(" %[^\n]99", artista);
    printf("{+} - Insira a duração (em segundos): > ");
    scanf(" %d", &tempo);
    nova->id = l->id++;
    nova->tempo = tempo;
    nova->artista = malloc(strlen(artista)+1);
    nova->titulo = malloc(strlen(titulo)+1);
    strcpy(nova->titulo, titulo);
    strcpy(nova->artista, artista);
    if(l->head){
        listar_musica(l);
        int id;
        printf("{+} - Escolha o ID da música da lista que será a antecessora da nova música (0 para adicionar no topo): > ");
        scanf(" %d", &id);
        if(id){
            Musica anterior = buscar_musica(l, id);
            if(!anterior){
                next("ID inválido ou inexistente. Adição não concluída. Aperte Enter para prosseguir!");
                free(nova->artista);
                free(nova->titulo);
                free(nova);
                l->id--;
                return;
            }
            nova->previous = anterior;
            nova->next = anterior->next;
            if(anterior!=l->tail){
                nova->next->previous = nova;
            }
            else
                l->tail=nova;
            anterior->next = nova;
        } else {
            l->head->previous = nova;
            nova->next = l->head;
            nova->previous = NULL;
            l->head = nova;
        }
    }
    else 
        l->head = l->tail = nova;
    next("Música registrada com sucesso. Aperte ENTER");
}

void trocar_posicao(Lista l){
    if(!l->head || !l->head->next){
        next("Não há músicas o suficiente para trocar. Aperte ENTER");
        returm;
    }
    int id1, id2;
    printf("Insira os 2 IDs das músicas que deseja trocar: > ");
    scanf(" %d %d", &id1, &id2);
    if(id1 > id2){
        int trade = id1;
        id1 = id2;
        id2 = trade;
    }
    if(id1 == id2){
        next("Não pode selecionar a mesma música. Aperte ENTER");
        return;
    }
    Musica troca1 = buscar_musica(l,id1);
    Musica troca2 = buscar_musica(l,id2);
    if(!troca1 || !troca2){
        next("Um ou mais IDs inválidos. Aperte ENTER.");
        return;
    }
    
   
}
int interface(){
    int op;
    printf(
        "= = PLAYLIST = =\n"
        "1. Inserir Música\n"
        "2. Trocar Posição\n"
        "3. Remover por Artista\n"
        "4. Exibir Playlist\n"
        "5. Inversão de Ordem\n"
        "0. Finalizar\n"
        " * - Escolha a opção desejada: > ");
    scanf(" %d", &op);
    system("clear");
    return op;
}

int main() {
    Lista playlist = construir_lista();
    while(1){
        switch (interface()){
            case 1: inserir_musica(playlist);
                break;
            case 2: trocar_posicao(playlist);
                break;
            case 4: printf("= = MÚSICAS DA PLAYLIST = =\n");
                listar_musica(playlist);
                next("Aperte ENTER para prosseguir.");
                break;
            default:
        }
    }
    return 0;
}


