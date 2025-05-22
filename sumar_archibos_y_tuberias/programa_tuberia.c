#include<stdio.h>
#include<unistd.h>
#include<cstdlib>

int main(){
    int r;
    int pipefd[2];
    pid_t pid;


    r= pipe(pipefd);
    if(r==-1){
        perror("error en la tuberia");
        exit(-1);
    }

    pid= fork();
    if (pid==-1){
        perror("error en el fork");
        exit(-1);
    }
    if(pid==0){

        close(pipefd[0]);
        int suma=0;
        for(int i=1;i<=499; i=i+1){
            suma= suma+i;
        }
        r= write(pipefd[1], &suma, sizeof(suma));
        if(r==-1){
            perror("Error al leer la tuberia");
            exit(-1);
        }
        close(pipefd[1]);
        exit(0);

    }else{
        int dato;
        int suma=0;
        for(int i=500;i<=999; i=i+1){
            suma= suma+i;
        }

        close(pipefd[1]);
        r= read(pipefd[0],&dato, sizeof(dato));
        if(r==-1){
            perror("Error al leer de la tuberia");
            exit(-1);
        }
        printf("%d\n", suma+dato);
        close(pipefd[0]);
        exit(0);
    }

    return 0;
}
