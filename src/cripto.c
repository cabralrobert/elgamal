/*******************************************************
*                                                      *
*   Criado em: Tue 05/Dec/2017,  01:44 hs              *
*   Instituicao: Universidade Federal do Ceará         *
*   Autor: Robert Cabral                               *
*   email: robertcabral@alu.ufc.br                     *
*                                                      *
********************************************************/
#include "cripto.h"

int verificaPrimo(long long int n){
    int isCousin;

    if (n <= 1 || (n != 2 && n % 2 == 0))
        isCousin = FALSE;
    else
        isCousin = TRUE;

    int d = 3;
    while (isCousin  && d <= n / 2) {
        if (n % d == 0)
            isCousin = FALSE;
        d = d + 2;
    }

    return isCousin;
}

long long int inverse(int a, int c){
    long long int inverse;
    for(inverse = 0; inverse < c-1;inverse++){
        if((a * inverse) % c == 1)
            return inverse;
    }

    return -1;
}

int modulo(int a,int b,int n){
    long long x=1,y=a;
    while(b > 0){
        if(b%2 == 1){
            x=(x*y)%n;
        }
        y = (y*y)%n;
        b /= 2;
    }
    return x%n;
}
