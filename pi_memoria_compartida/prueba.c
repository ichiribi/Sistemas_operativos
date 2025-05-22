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
    int num1=1258;
    float num2=2.2547;
    void *puntero;
    *(int*)puntero=num1;
    *(float*)((int*)puntero+1)=num2;
    printf("%d\n", *(int*)puntero);
    printf("%f\n", *(float*)((int*)puntero+1));
    return 0;
}
