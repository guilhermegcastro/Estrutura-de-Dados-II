/**
* @file projeto.c
* @author @guilhermegcastro
* @date 2026-04-17
* @brief
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gconio.h"

typedef struct TypePro{
    int instr;
    int done;
    int type;
    int pid;
    int run;
    struct TypePro* prox;
    struct TypePro* ant;
}TypePro;

typedef TypePro* Pro;

typedef struct TypeLista{
    Pro head;
    Pro tail;
    Pro last_kernel;
    Pro pro_run;
    int count;
    int gPID;
}TypeLista;

typedef TypeLista* List;

List build_List(){
    List l = malloc(sizeof(TypeLista));
    l->head = NULL;
    l->tail = NULL;
    l->last_kernel = NULL;
    l->pro_run = NULL;
    l->count = 0;
    l->gPID = 100;
    return l;
}

void interface(List l){
     printf(
        "Create: (K)ernel Process / (U)ser Process\n"
        "Actions: kil(L) Process / e(X)it Application\n");
    printf("%d Process", l->count);
        (l->pro_run) ? printf(" PID: %d", l->pro_run->pid ) : printf(" ");
        printf("\nRUNNING   TYPE                PID     INSTRUCTIONS   DONE \n");
}

void print_Pro(List l){
    Pro proc = l->head;
    
    int i = l->count;
    while(i>0){
        printf("%-9c %-19s %-7d %-14d %d\n", 
        (proc->run)? '*' : ' ', 
        (proc->type) ? "USER" : "KERNEL", 
        proc->pid, proc->instr, proc->done);
        proc = proc->prox;
        i--;
    }
}

void new_Kernel(List l){
    Pro kernel = malloc(sizeof(TypePro));
    l->count++;
    kernel->type = 0; // FALSE == KERNEL
    kernel->instr = 1 + rand()%10;
    kernel->done = 0;
    kernel->pid = l->gPID++;
    kernel->run = 1;
    if(l->pro_run)
        l->pro_run->run = 0;
    l->pro_run = kernel; //Sempre prioriza o que foi adicionado.
      if(!l->head){ // Se for o primeiro...
        kernel->prox = kernel->ant = NULL;
        l->head = l->tail = l->last_kernel = kernel; 
        return;
    }  
    if(!l->last_kernel){ // Se não existe outro kernel na lista...
        kernel->prox = l->head;
        l->head->ant = kernel;
        l->head = l->last_kernel = kernel;
        kernel->ant = NULL;
        if(!l->tail) // Se for o único processo...
            l->tail = kernel;
        return;
    }   
    if(l->last_kernel->prox) {
        kernel->prox = l->last_kernel->prox; // recebe o proximo usuario (se houver) do ultimo kernel.
         kernel->prox->ant = kernel; // o anterior do proximo usuario recebe o novo kernel.
    }else {
        l->tail = kernel;
        kernel->prox = NULL;
    } 
    l->last_kernel->prox = kernel;  // ele vira o proximo do ultimo kernel.
    kernel->ant = l->last_kernel; // ele aponta para o ultimo kernel.
    l->last_kernel = kernel; // ele se torna o ultimo kernel.
};

void new_User(List l){
    Pro user = malloc(sizeof(TypePro));
    l->count++;
    user->type = 1; // TRUE == USER
    user->instr = 1 + rand()%10;
    user->done = 0;
    user->pid = l->gPID++;
    user->run = 1;
    if(l->pro_run)
        l->pro_run->run = 0; // Tira a execucao do anterior
    l->pro_run = user; //Sempre prioriza o que foi adicionado.
    if(!l->head){ // Se for o primeiro...
        user->prox = user->ant = NULL;
        l->head = l->tail = user; 
        return;
    }   
    l->tail->prox = user;
    user->ant = l->tail;
    user->prox = NULL; 
    l->tail = user;
};

void kill_process(Pro atual, List l) {
    if (!atual || !l || l->count == 0) return;

    // 1. Ajusta o vizinho anterior (ou a Head)
    if (atual->ant) 
        atual->ant->prox = atual->prox;
    else 
        l->head = atual->prox;

    // 2. Ajusta o vizinho próximo (ou a Tail)
    if (atual->prox) 
        atual->prox->ant = atual->ant;
    else 
        l->tail = atual->ant;

    // 3. Atualiza o marcador de último kernel se necessário
    if (l->last_kernel == atual) {
        Pro p = atual->ant;
        // Volta na lista procurando o kernel anterior mais próximo
        while (p && p->type != 0) p = p->ant;
        l->last_kernel = p;
    }

    // 4. Garante que o escalonador não aponte para memória liberada
    if (l->pro_run == atual) {
        l->pro_run = (atual->prox) ? atual->prox : l->head;
    }

    l->count--;
    free(atual);

    // 5. Reset de segurança
    if (l->count == 0) {
        l->head = l->tail = l->last_kernel = l->pro_run = NULL;
    }
}

void pro_Running(List l){
    
    Pro atual = l->pro_run;
    
    if(!atual)
        return; // Se não houver processos, não faz nada.
        
    atual->done++;
    if(atual->prox)// Se houver proxima instrucao
        l->pro_run = atual->prox;
    else // Se nao, a lista começa dnv
        l->pro_run = l->head;
    if(l->pro_run)
        l->pro_run->run = 1;
    if(atual->done == atual->instr) {// Se as instrucoes realizadas forem iguais ao total do processo...
        kill_process(atual, l);
    } else atual->run = 0;
};
int main() {
    srand(time(NULL));
    List l = build_List();
    do{
        char opcao;
        while(!kbhit(&opcao)){
            interface(l);
            print_Pro(l);
            system("sleep 1");
            system("clear");
            pro_Running(l);
        }
        switch (opcao){
            case 'K':
            case 'k':new_Kernel(l);
                break;
            case 'U':
            case 'u': new_User(l);
                break;
            case 'L':
            case 'l': kill_process(l->pro_run, l);
                break;
            case 'X':
            case 'x': 
                printf(" END...");
                return 0;
            default:
        }
        
    }while(1);
    
    return 0;
}


