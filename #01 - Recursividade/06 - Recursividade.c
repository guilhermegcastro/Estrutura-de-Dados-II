/**
* @file 06 - Recursividade.c
* @author @guilhermegcastro
* @date 07.03.2026 
* @brief A sequência Fibonacci, amplamente encontrada na natureza, é aquela em que o valor do N-ésimo termo da série é a soma dos dois valores anteriores 
* ○ 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, …
* Faça em um mesmo código-fonte, duas funções para encontrar o N-ésimo termo da série:
○ Função Iterativa => usando laços de repetição
○ Função Recursiva => fib(n) == fib(n-1) + fib(n-2) 
* Invoque ambas funções para encontrar o 45º termo da série e analise o que acontece…
**/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 45

int fibI(int n) {
    
    int n0 = 0;
    int n1 = 1;
    for (int i = 0; i < n; i++){
        int t = n1;
        n1 += n0;
        n0 = t;
    }
    
    return n0;
}
int fibR(int n) {
    if (n<=1) return n;
   return fibR(n-1) + fibR(n-2);
}


int main() {
    printf("Aperte ENTER para iniciar a Fibonacci Iterativa\n\n");
    getchar();
    int t1 = time(NULL);
    int r = fibI(N);
    int t2 = time(NULL);
    t2-= t1;
    printf("Fibonacci Iterativa do %dº Termo: %d (Tempo de execução: %d segundos)\n", N, r, t2);
    printf("Aperte ENTER para iniciar a Fibonacci Recursiva\n");
    getchar();
    t1 = time(NULL);
    r = fibR(N);
    t2 = time(NULL);
    t2-= t1;
    printf("Fibonacci Recursiva do %dº Termo: %d  (Tempo de execução: %d segundos)", N, r, t2);
    return 0; 
}


