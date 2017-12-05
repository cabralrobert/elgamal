#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "cripto.h"
#define PORT 8080

int main(){

    time_t t;

    int sock = 0;
    struct sockaddr_in serv_addr;

    srand((unsigned) time(&t));

    int p;
    printf("Insira um numero primo: ");
    scanf("%d", &p);

    if(verificaPrimo(p) == 0){
        printf("\nNão é primo!\n");
        return -1;
    }


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


    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0){
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    printf("\n----- Enviando (p,alfa,beta) para Alice -----\n");
    sleep(1.5);
    printf("\n----- Esperando resposta de Alice -----\n");

    send(sock , &p , sizeof(int) , 0 );
    send(sock , &alfa , sizeof(int) , 0 );
    send(sock , &beta , sizeof(int) , 0 );

    int ke,y;

    read( sock , &ke, sizeof(int));
    read( sock , &y, sizeof(int));

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
    return 0;
}
