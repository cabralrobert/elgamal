#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "cripto.h"
#define PORT 8080

int main(int argc, char const *argv[])
{
    time_t t;
    srand((unsigned) time(&t));
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char pChar[1024] = {0};
    char betaChar[1024] = {0};
    char *hello = "Hello from server";

    int p, alfa, beta;

    printf("ESPERANDO POR BOB");

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }




    valread = read( new_socket , &p, sizeof(int));
    valread = read( new_socket , &alfa, sizeof(int));
    valread = read( new_socket , &beta, sizeof(int));

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

    send(new_socket , &ke , sizeof(int) , 0 );
    send(new_socket , &y , sizeof(int) , 0 );

    return 0;
}
