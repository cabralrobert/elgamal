#include <stdio.h>
#include "cripto.h"
#include "socket.h"

int main(){

#ifdef AUTO
  printf("AUTO\n");
    time_t t;

    srand((unsigned) time(&t));

    int p;
    printf("Gerando um numero primo...");
      p = rand() % 20412341;

    while(verificaPrimo(p) == 0)
      p = rand() % 20412341;

    printf("\n\nGerando alfa...\n");
    sleep(1);
    long long int alfa = rand() % (p-1);
    printf("O valor de alfa é: %lld\n", alfa);

    printf("\n\nGerando D...\n");
    sleep(1);
    int d = rand() % (p-2) + 2;
    printf("O valor de d é: %d\n", d);

    printf("\n\nCalculando beta...\n");
    sleep(1);
    long long int beta = modulo(alfa,d,p);
    printf("beta(%lld) = alfa(%lld)^d(%d) mod p(%d)\n",beta,alfa,d,p);

    printf("\n#######\nALFA: %lld\nD: %d\nBETA: %lld\n",alfa,d,beta);

    client();

    printf("\n----- Enviando (p,alfa,beta) para Alice -----\n");
    sleep(1.5);
    printf("\n----- Esperando resposta de Alice -----\n");

    sendServer(&p);
    sendServer(&alfa);
    sendServer(&beta);

    int ke,y;

    readServer(&ke);
    readServer(&y);

    printf("\n\n ----- Valores de ke e y recebidos de Alice -----\n\n");
    printf("ke: %d\ny: %d", ke, y);

    printf("\n\nCalculando km...\n");
    sleep(1);
    long long int kmbob = modulo(ke,d,p);
    printf("km(%d) = ke(%d)^d(%d) mod p(%d)",kmbob,ke,d,p);

    printf("\n\nDescriptografando a mensagem...\n");
    sleep(1);
    long long int x = (y * inverse(kmbob,p)) % p;
    printf("x(%d) = y(%d) * km^-1(%d) mod p(%d)",x,y,inverse(kmbob,p),p);


    printf("\n\n########### A mensagem é: %lld ###########\n\n\n",x );

#endif


#ifdef MANUAL

    int p;
    printf("Digite um numero primo:");
      scanf("%d",&p);

    while(verificaPrimo(p) == 0){
      printf("Porfavor, digite um numero primo: ");
      scanf("%d",&p);
    }

    printf("\n\nDigite um número para alfa...\n");
    long long int alfa;
    scanf("%lld",&alfa);
    alfa = alfa % (p-1);

    printf("\n\nDigite um número para d...\n");
    long long int d;
    scanf("%lld",&d);
    d = d % (p-1);

    printf("\n\nCalculando beta...\n");
    sleep(1);
    long long int beta = modulo(alfa,d,p);
    printf("beta(%lld) = alfa(%lld)^d(%d) mod p(%d)\n",beta,alfa,d,p);

    printf("\n#######\nALFA: %lld\nD: %d\nBETA: %lld\n",alfa,d,beta);

    client();

    printf("\n----- Enviando (p,alfa,beta) para Alice -----\n");
    sleep(1.5);
    printf("\n----- Esperando resposta de Alice -----\n");

    sendServer(&p);
    sendServer(&alfa);
    sendServer(&beta);

    int ke,y;

    readServer(&ke);
    readServer(&y);

    printf("\n\n ----- Valores de ke e y recebidos de Alice -----\n\n");
    printf("ke: %d\ny: %d", ke, y);

    printf("\n\nCalculando km...\n");
    sleep(1);
    long long int kmbob = modulo(ke,d,p);
    printf("km(%d) = ke(%d)^d(%d) mod p(%d)",kmbob,ke,d,p);

    printf("\n\nDescriptografando a mensagem...\n");
    sleep(1);
    long long int x = (y * inverse(kmbob,p)) % p;
    printf("x(%d) = y(%d) * km^-1(%d) mod p(%d)",x,y,inverse(kmbob,p),p);


    printf("\n\n########### A mensagem é: %lld ###########\n\n\n",x );

#endif

    return 0;
}

