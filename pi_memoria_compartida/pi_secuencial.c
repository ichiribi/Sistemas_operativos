#include<iostream>

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
    long int iteraciones=4e9;
    printf("%.17f",suma_intervalo(0,iteraciones));
    return 0;
}