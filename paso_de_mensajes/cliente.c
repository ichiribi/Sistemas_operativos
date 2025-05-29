#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#define SERVER_IP "192.168.0.22"
#define SERVER_PORT 3035
#define puerto 3035

int fd;

void sigterm_handler(int signum) {
    printf("cerrando cliente");
    close(fd);
    exit(0);
}


int main(){
    signal(SIGTERM, sigterm_handler);
    struct sockaddr_in servidor;
    char buffer[12];
    int r;

    fd= socket(AF_INET, SOCK_STREAM,0);
    servidor.sin_family=AF_INET;
    servidor.sin_port= htons(puerto);
    servidor.sin_addr.s_addr = inet_addr(SERVER_IP);
    memset(&(servidor.sin_zero), '\0', 8);

    r= connect(fd, (struct sockaddr *) &servidor, sizeof(servidor));
    if(r==-1){
        perror("Error en la conexion");
        exit(-1);
    }

    r = recv(fd, buffer, sizeof(buffer) - 1, 0);
    if(r==-1){
        perror("Error en la recepcion");
        exit(-1);
    }
    buffer[r]='\0';
    printf("%s", buffer);

    r=send(fd, "hola server", 11,0);
    if(r==-1){
        perror("Error en el envio");
        exit(-1);
    }

    close(fd);
    return 0;
}