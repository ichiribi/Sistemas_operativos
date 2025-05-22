#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<cstdlib>

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
    int pipefd[4][2];
    pid_t pid;
    long int iteraciones=(4e9)/4;
    long int inicio=0; //inicio de la iteracion
    long int fin= iteraciones; // fin del primer gupo de iteraciones
    double suma_total=0;

    //creación de procesos
    for(int i=0; i<=3; i=i+1){
        int r= pipe(pipefd[i]);
        if(r==-1){
            perror("error en la tuberia");
            exit(-1);
        }
        pid = fork();
        if(pid == -1){
            perror("Error al crear el proceso hijo");
            exit(-1);
        }
        //proceso hijo
        if(pid==0){
            close(pipefd[i][0]);
            double suma = suma_intervalo(inicio, fin);
            printf("%d -> %.17f\n",i,suma);
            r= write(pipefd[i][1], &suma, sizeof(suma));
            if(r==-1){
                perror("Error al escribir en la tuberia");
                exit(-1);
            }
            exit(1);
        }
        inicio= fin+1;
        fin= fin + iteraciones;
    }
    
    //sumar valores
    for (int i=0; i<=3; i=i+1){
        close(pipefd[i][1]);
        double dato;
        int r= read(pipefd[i][0],&dato, sizeof(dato));
        if(r==-1){
            perror("Error al leer de la tuberia");
            exit(-1);
        }
        suma_total=suma_total + dato;
    }
    printf("%.17f\n", suma_total);
       
    return 0;
}