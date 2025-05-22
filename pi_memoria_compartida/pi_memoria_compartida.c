#include<iostream>
#include<sys/shm.h>
#include<sys/wait.h>
#include<unistd.h>
//suma los a_k en el intervalo
double suma_intervalo(long int inicio,long int fin){
    double suma=0;
    double valor;
    for(inicio; inicio<=fin; inicio= inicio+1){
        valor=4/(2*(double)inicio+1);
        if(inicio%2==0){
            suma= suma+valor;
        }else{
            suma= suma-valor;
        }
    }
    return suma;
}

int main(){
    key_t key= 12345;
    pid_t pid;
    long int iteraciones=(4e9)/4;
    void *memory_apt;
    long int inicio=0; //inicio de la iteracion
    long int fin= iteraciones; // fin del primer gupo de iteraciones
    double suma_total=0;

    int shmId;
    //memoria compartida
    shmId = shmget(key, sizeof(float),IPC_CREAT | 0666);
    if (shmId == -1){
        perror("Error en el shmId");
        exit(-1);
    }

    memory_apt = shmat(shmId, 0, 0);
    if(*(int*)memory_apt == -1){
        perror("Error en shmat");
        exit(-1);
    }

    //creación de procesos
    for(int i=0; i<=3; i=i+1){
        pid = fork();
        if(pid == -1){
            perror("Error al crear el proceso hijo");
            exit(-1);
        }
        //proceso hijo
        if(pid==0){
            double suma = suma_intervalo(inicio, fin);
            printf("%d -> %.17f\n",i,suma);
            *((double*)memory_apt+i)=suma;
            exit(1);
        }
        inicio= fin+1;
        fin= fin + iteraciones;
    }
    //Epera a que los procesos terminen
    for(int i=0; i<=3; i=i+1){
        if(wait(NULL)==-1){
            perror("Error al esperar procesos hijos");
            exit(-1);
        }
    }
    //sumar valores
    for (int i=0; i<=3; i=i+1){
        suma_total=suma_total + *((double*)memory_apt+i);
    }
    printf("%.17f\n", suma_total);
    //liberar memoria compartida
    int r;
    r= shmdt(memory_apt);
    if(r==-1){
        perror("Error al liberar memoria shmdt");
        exit(-1);
    }
    r=shmctl(shmId, IPC_RMID, 0);
    if(r==-1){
        perror("Error al liberar memoria shmctl");
        exit(-1);
    }
    
    return 0;
}