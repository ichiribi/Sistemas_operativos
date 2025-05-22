#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include <cstdlib>
int main(){
	
	int suma=0;

	pid_t pid;
	pid = fork();
	if(pid==-1){
		perror("Error en el fork");
		exit(-1);
	}
	if(pid==0){
		FILE *archivo= fopen("suma1.txt","wt");
		if(archivo==NULL){
			perror("Error al leer el archivo");
			exit(-1);
		}
		int suma=0;
		for(int i=0; i<=500; i=i+1){
			suma=suma+i;
		}
		fprintf(archivo, "%d ", suma);
		fclose(archivo);
		exit(0);
	}else{
		FILE *archivo= fopen("suma2.txt","wt");
		if(archivo==NULL){
			perror("Error al leer el archivo");
			exit(-1);
		}
		int suma=0;
		for(int i=501;i<=999;i=i+1 ){
			suma= suma+i;
		}
		fprintf(archivo, "%d ", suma);
		fclose(archivo);
	}
	
	FILE *archivo1= fopen("suma1.txt","r");
	FILE *archivo2= fopen("suma2.txt","r");

	if(archivo1==NULL || archivo2==NULL){
		perror("Error al abrir archivo");
		exit(-1);
	}
	int num1, num2;
	fscanf(archivo1,"%d", & num1);
	fscanf(archivo2,"%d", & num2);
	printf("%d\n", num1+num2);
	
	fclose(archivo1);
	fclose(archivo2);

	return 0;
}
