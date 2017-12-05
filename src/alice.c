#include <stdio.h>
#include "cripto.h"
#include "socket.h"

int main(int argc, char const *argv[]){
    time_t t;
    srand((unsigned) time(&t));

    int p, alfa, beta;

    printf("ESPERANDO POR BOB");

    server();

    readClient(&p);
    readClient(&alfa);
    readClient(&beta);

    printf("\n\n----- p, alfa, beta recebidos de Bob -----\n");
    printf("\nP: %d\nalfa: %d\nbeta: %d", p,alfa,beta);

    printf("\n\nGerando uma mensagem (msg < p-1)....");
    sleep(1);
    int msg = rand() % (p-1);
    printf("\nMensagem é: %d", msg);

    printf("\n\nGerando um i (2 <= i <= p-2)....");
    sleep(1);
    int i = rand() % (p-2) + 2;
    printf("\nO valor de i é: %d", i);

    printf("\n\nCalculando o valor de ke.....");
    sleep(1);
    long long int ke = modulo(alfa,i,p);
    printf("\nke(%lld) = alfa(%d)^i(%d) mod p(%d)",ke,alfa,i,p);

    printf("\n\nCalculando o valor de km.....");
    sleep(1);
    long long int km = modulo(beta,i,p);
    printf("\nkm(%lld) = beta(%d)^i(%d) mod p(%d)",km,beta,i,p);

    printf("\n\nCalculando o valor de Y.....");
    sleep(1);
    long long int y = (msg * km) % p;
    printf("\ny(%d) = msg(%d) * km(%d) mod p(%d)",y,msg,km,p);


    printf("\n\n############\nP: %d\nMSG: %d\nALFA: %d\nBETA: %d\nI: %d\na^i: %d\nbeta^i: %d\ny: %d\n",p,msg,alfa,beta,i,ke,km,y);
    sleep(3);

    printf("\n\n----- Enviando ke e y para Bob -----\n\n");

    sendClient(&ke);
    sendClient(&y);

    return 0;
}
