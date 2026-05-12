/**
* @file escalonamento.c
* @author @guilhermegcastro
* @date 2026-05-12
* @brief 
* Questão Prática [Escalonador de Processos] 
* Contexto Real: Sistemas operacionais modernos precisam gerenciar diversos processos ativos em memória, que disputam entre si uma oportunidade para entrar em estado de execução na CPU. 
* Um dos métodos clássicos de escalonamento de processos é o Round-Robin, onde os processos são organizados em uma lista circular e cada um recebe uma mesma "fatia de tempo" para ser executado, antes de passar para o próximo. 
* Isso permite que todos os processos sejam executados alternadamente, e de forma justa. 
* 
* Problema: Você deverá implementar um protótipo de escalonador de processos do tipo Round-Robin, baseado em uma estrutura de dados dinâmica do tipo lista encadeada (qualquer variante é permitida).  
* Para validar o simulador, você deverá implementar uma interface contendo as seguintes opções de execução… 
* 
* 1) Criar novo Processo: 
* ● PID: Process ID (valor inteiro auto incrementado) 
* ● TEMPO: Tempo necessário para finalização do processo (valor inteiro sorteado entre 1 e 5). 
* * Ao criar um novo processo, nenhum valor ou informação deve ser solicitado ao usuário. 
* * As informações (PID e TEMPO) de todo processo criado deve ser impresso na tela para fins de análise. 
* * Todo novo processo criado sempre terá prioridade na lista de escalonamento. 
* 
* 2) Exibir lista de escalonamento. 
* * Exibir a lista dos processos aguardando execução. 
* 
* 3) Executar processo. 
* * Executa o primeiro processo da lista de escalonamento, decrementando 1 unidade de TEMPO da execução deste. Caso o valor TEMPO chegue a 0, este processo deverá ser eliminado da lista de escalonamento. 
* * Para fins de análise, o sistema deverá imprimir na tela os dados do processo após executado, inclusive se foi finalizado. 
* * Após a execução do processo, este deverá ir para o final da lista de escalonamento, tornando o processo seguinte o próximo a ser executado.  
* 
* REQUISITO BÔNUS 
* 4) Matar processo. 
* * Solicitar ao usuário um PID e, existindo este processo, eliminá-lo da lista de escalonamento. 
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "escalonamento.h"

int interface(){
    int opcao;
    printf(
    " == MENU ==\n"
    " 1. Criar Novo Processo\n"
    " 2. Exibir Lista de Escalonamento\n"
    " 3. Executar Processo\n"
    " 4. Matar Processo\n"
    " 0. Sair\n"
    " *  Escolha a opção desejada: > ");
    scanf(" %d", &opcao);
    system("clear");
    return opcao;
}

void criarProcesso(Lista l){
    Processo novo = malloc(sizeof(TyProcesso));
    novo->pid = (l->i)++;
    novo->time = 1 + rand()%5;
    if(!l->head){
        novo->previous = NULL;
        novo->next = NULL;
        l->head = l->tail = novo;
        printf(" Processo PID: %02d e TEMPO:%ds adicionado na lista de escalonamento.\n\n\n", novo->pid, novo->time);
        next();
        return;
    }
    novo->next = l->head;
    novo->previous = NULL;
    l->head->previous = novo;
    l->head = novo;
    printf(" Processo PID: %02d e TEMPO:%ds adicionado na lista de escalonamento.\n\n\n", novo->pid, novo->time);
    next();
}

void listar(Lista l){
    Processo alvo = l->head;
    printf("LISTA DE PROCESSOS\n PID  TIME\n");
    while(alvo){
        printf("  %02d  %d\n", alvo->pid, alvo->time);
        alvo = alvo->next;
    }
    printf("\n\n\n");
}

void executar(Lista l){
    Processo executando = l->head;
    if(!executando){
        printf("Sem processos para na fila do escalonamento!");
        return;
    }
    executando->time--;
    
    if(l->head == l->tail) {
        executando->next->previous = NULL;
    }
    else{
       l->head = executando->next;
       l->head->previous =  NULL;   
    } 
    printf("DADOS DO PROCESSO EXECUTADO:\n PID: %d TIME: %d", executando->pid, executando->time);
    
    if(executando->time <=0) {
        printf("\nO  processo foi finalizado!\n\n");
        free(executando);
    } 
    else {
        if(!l->head){
            l->head = l->tail = executando;
            executando->next = executando->previous = NULL;
        }
        else{
            l->tail->next = executando;
            executando->previous = l->tail;
            executando->next = NULL;
            l->tail = executando;
        }
    }
    listar(l);
    next();
}

Processo busca(Lista l, int id){
    Processo alvo = l->head;
    while (alvo){
        if(alvo->pid == id)
            return alvo;
        alvo = alvo->next;
    }
    return NULL;
}

void matar(Lista l){
    if(!l->head){
        printf("Sem processos na fila");
        return;
    }
    listar(l);
    int id;
    printf("Escolha o Processo que será finalizado: ");
    scanf(" %d", &id);
    Processo pro = busca(l, id);
    if(!pro){
        printf("Id inválido ou inexistente.");
        return;
    }
    
    if(pro == l->head){
        if(l->head == l->tail)
            l->head = l->tail = NULL;
        else{
            l->head = pro->next;
            l->head->previous = NULL;
        }
    } 
    else if (pro == l->tail){
            l->tail = pro->previous;
            l->tail->next = NULL;
    }
    else {
        pro->next->previous = pro->previous;
        pro->previous->next = pro->next;
    }
    printf("O processo PID: %d TIME: %d foi deletado com sucesso. ", pro->pid, pro->time);
    free(pro);
    next();
}

int main() {
    srand(time(NULL));
    Lista lista = build_list();
    while (1){
        switch (interface()){
            case 1: criarProcesso(lista);
                break;
            case 2: listar(lista);
                next();
                break;
            case 3: executar(lista);
                break;
            case 4: matar(lista);
                break;
            case 0: return 0; 
        }
    }
    return 0;
}


