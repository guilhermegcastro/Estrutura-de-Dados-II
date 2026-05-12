/**
* @file escalonamento.h
* @author @guilhermegcastro
* @date 2026-05-12
* @brief header para ser utilizado no codigo "07_escalonamento_simulador.c"
**/

typedef struct TyProcesso* Processo;
typedef struct TyLista* Lista;

typedef struct TyProcesso{
    int pid;
    int time;
    struct TyProcesso* next;
    struct TyProcesso* previous;
}TyProcesso;

typedef struct TyLista{
    Processo head;
    Processo tail;
    int i;
}TyLista;

Lista build_list(){
   Lista l = malloc(sizeof(TyLista));
    l->head = NULL;
    l->tail = NULL;
    l->i = 0;
    return l;
}

void next(){
    printf(" Pressione ENTER para prosseguir...");
    while(getchar()!='\n');
    getchar();
    system("clear");
}


