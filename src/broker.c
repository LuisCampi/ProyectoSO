#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h>
#include <pthread.h>
#include <semaphore.h>

#include "tablahash.h"

int i=0;
volatile int bucle = 1;
sem_t sem;
static Hasht *tabla;
void *antender_cliente(void * args);
//--------------------------------------------------------------------------------------------------------------------
void manejador(int sig){
	printf("\nSEÑAL RECIBIDA!");
	bucle = 0;
	exit(1);
}

int retornar_puerto(){ //En esta función se obtiene el número de puerto del archivo configuracion.cfg

	int fd, tam1, tam2, int_puerto;
	char z, final[1000]="", puerto[10];
	int i=0, variable1=0, bandera=0;

	if(fd!=-1){

		fd = open("configuracion.cfg",O_RDONLY);

		while(read(fd,&z,sizeof(z)!=0))
		{
			final[i]=z;
			i = i+1;
		}
    		//printf("%s\n", final);
		int tam = strlen(final);

		for(int i=0;i<tam;i++){
			if(final[i]=='=' && bandera==0){
				tam1=i;
			}else if(final[i]=='\n' && bandera==0){
				tam2=i;
				bandera++;
			}
		}
		for(int i=tam1;i<tam2;i++){
			puerto[variable1]=final[i+1];
			variable1++;
		}
		int_puerto = atoi(puerto);
		close(fd);

	}
	return int_puerto;
}

int tamanoTabla(){ //En esta función se obtiene el número de tamaño de tabla del archivo configuracion.cfg

	int fd, tam1, tam2, tam3, tam4, int_tamano;
	char z, final[1000]="", puerto[10], tamano_tabla[100];
	int i=0, variable3=0, bandera=0;

	if(fd!=-1){

		fd = open("configuracion.cfg",O_RDONLY);

		while(read(fd,&z,sizeof(z)!=0))
		{
			final[i]=z;
			i = i+1;
		}
    		//printf("%s\n", final);
		int tam = strlen(final);

		for(int i=0;i<tam;i++){
			if(final[i]=='=' && bandera==0){
				tam1=i;
			}else if(final[i]=='\n' && bandera==0){
				tam2=i;
				bandera++;
			}else if(final[i]=='=' && bandera==1){
				tam3=i;
		     	}else if(final[i]=='\n' && bandera==1){//
				tam4=i;
				bandera++;
		     	}
  		}
		for(int k=tam3;k<tam4;k++){
			tamano_tabla[variable3]=final[k+1];
			variable3++;
		}
	int_tamano = atoi(tamano_tabla);
	close(fd);
	}
	return int_tamano;
}

//-----------------------------------------------------------------------------------------------------------------

void *antender_cliente(void *args){
	
	pthread_detach(pthread_self());
	char buffer[100];
	int client = *((int *) args);
	free(args);
	
	while (recv(client, buffer, 50, MSG_WAITALL) > 0){
		printf("Buscando %s en tablahash...\n", buffer);
		sem_wait(&sem); 
		get_ht(tabla,buffer); 
		add_ht(tabla,buffer);
		print_ht(tabla);
		sem_post(&sem); 
		bzero((char *)&buffer, sizeof(buffer));
	}
	
	close(client);
	printf("Servidor-Cliente desconectados\n");

	return NULL;
}
//--------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]){

	sem_init(&sem, 0, 1);
	char nombre[60], cadena[10];
	int size_of_table, p;
	
	printf("NUEVA TABLA CREADA!\n");
	tabla = new_ht(size_of_table);
//--------------------------------------------------------------------------------------------------------------------   
	size_of_table = tamanoTabla();
	tabla = new_ht(size_of_table);
	printf("\n");
	print_ht(tabla);
	signal(SIGINT, manejador);
//--------------------------------------------------------------------------------------------------------------------
	struct sockaddr_in direccionServidor;

	direccionServidor.sin_family= AF_INET;
	direccionServidor.sin_port = htons(retornar_puerto()); //Puerto 1212
	direccionServidor.sin_addr.s_addr=INADDR_ANY;

	int servidor = socket(AF_INET ,SOCK_STREAM,0);
	int activado=1;
	setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR,(char*)&activado, sizeof(activado));

	if(bind(servidor, (void*)&direccionServidor,sizeof(direccionServidor)) != 0){
		printf("FALLO EL BIND");
		return 1; 
	}

	printf("\nEstoy escuchando...");
    	listen(servidor,100);//habilita socket servidor para recibir conexiones

    	struct sockaddr_in direccionCliente;
    	
	while(1){
	    	unsigned int tamanoDireccion= sizeof(direccionCliente);

	    	int cliente= accept(servidor,(struct sockaddr*)&direccionCliente,&tamanoDireccion);
	    	if(cliente<0)
	    	{
	    		printf("Error en accept()\n");
	    		close(servidor);
	    		return 1;
	    	}
	    	printf("conectado con %s puerto cliente: %d\n", inet_ntoa(direccionCliente.sin_addr), htons(direccionCliente.sin_port));
	    	int *cl_p = (int *) malloc(sizeof(int));
	    	*cl_p=cliente;
	    	pthread_t tid;
	    	pthread_create(&tid,NULL,antender_cliente,cl_p);
	}
	return 0;
}
