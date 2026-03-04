/**
* @file 01- Recursividade.c
* @author @guilhermegcastro
* @date 04.03.2026 18:14:23 -03
* @brief FUNÇÃO RECURSIVA PARA RETORNAR: RESULTADO DE X^Y
**/

#include <stdio.h>

int potencia(int x, int y) {
    if (y==1) return x;
    return x*potencia(x, y-1);
    

}
int main() {
    int x, y;
    printf("Valor de X: ");
    scanf(" %d", &x);
    printf("Valor de Y: ");
    scanf(" %d", &y);
    printf("%d^%d == %d", x, y, potencia(x, y));
    
    return 0;
}
