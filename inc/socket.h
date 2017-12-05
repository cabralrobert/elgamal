/*******************************************************
*                                                      *
*   Criado em: Tue 05/Dec/2017,  16:35 hs              *
*   Instituicao: Universidade Federal do Ceará         *
*   Autor: Robert Cabral                               *
*   email: robertcabral@alu.ufc.br                     *
*                                                      *
********************************************************/
#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define PORT 12345

static struct sockaddr_in serv_addr;
static int sock = 0;
static struct sockaddr_in address;
static int server_fd, new_socket, opt = 1, addrlen = sizeof(address);

void server();
void readClient(int *value);
void sendClient(int *value);
void client();
void readServer(int *value);
void sendServer(int *value);

#endif
