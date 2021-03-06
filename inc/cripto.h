/*******************************************************
*                                                      *
*   Criado em: Tue 05/Dec/2017,  01:45 hs              *
*   Instituicao: Universidade Federal do Ceará         *
*   Autor: Robert Cabral                               *
*   email: robertcabral@alu.ufc.br                     *
*                                                      *
********************************************************/
#ifndef CRIPTO_H_
#define CRIPTO_H_

#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

int verificaPrimo(long long int n);
long long int inverse(int a, int c);
int modulo(int a,int b,int n);

#endif
