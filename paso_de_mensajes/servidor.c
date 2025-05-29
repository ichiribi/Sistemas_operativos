#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#define puerto 3035
#define BACKLOG 5

int socket_descriptor=-1;
int clientfd=-1;

void sigterm_handler(int signum) {
    printf("cerrando");
    close(clientfd);
    close(socket_descriptor);
    exit(0);
}

int main(){
    signal(SIGTERM, sigterm_handler);
    struct sockaddr_in servidor, client;
    int r;
    char buffer[1024];
    socklen_t lenclient;

    socket_descriptor= socket(AF_INET, SOCK_STREAM, 0);
    if(socket_descriptor==-1){
        perror("No se pudo crear el socket");
        exit(-1);
    }
    int opt = 1;
    if (setsockopt(socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(EXIT_FAILURE);
    }
    
    servidor.sin_family=AF_INET;
    servidor.sin_port= htons(puerto);
    servidor.sin_addr.s_addr = INADDR_ANY;
    memset(&(servidor.sin_zero), '\0', 8);


    r=bind(socket_descriptor, (struct sockaddr *) &servidor, sizeof(servidor));
    if(r==-1){
        perror("Error en el bind");
        exit(-1);
    }

    r=listen(socket_descriptor, BACKLOG);
    if(r==-1){
        perror("Error en el listen");
        exit(-1);
    }

    lenclient= sizeof(client);
    clientfd= accept(socket_descriptor,(struct sockaddr *) &client, &lenclient);
    if(clientfd==-1){
        perror("error al recibir paquete");
        exit(-1);
    }

    r= send(clientfd, "hello world", 11, 0);
    if(r==-1){
        perror("Error en el send");
        exit(-1);
    }

    r=recv(clientfd, buffer, 10, 0);
    if(r==-1){
        perror("Error en el recv");
        exit(-1);
    }
    buffer[r] = '\0';
    printf("%s", buffer);

    close(clientfd);
    close(socket_descriptor);
    return 0;
}