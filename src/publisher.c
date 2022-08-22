#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "csapp.h"

int main(int argc,char *argv[]){

	if(argc<2 || argc>2){
		printf("Se debe ingresar : <./ejecutable> <IPservidor>\n");
	}

	struct sockaddr_in direccionServidor;

	direccionServidor.sin_family= AF_INET;
	direccionServidor.sin_port = htons(1212);
	direccionServidor.sin_addr.s_addr=inet_addr(argv[1]);//ip del servidor
	
	int publisher = socket(AF_INET, SOCK_STREAM,0);

	if(connect(publisher, (void*)&direccionServidor, sizeof(direccionServidor)) != 0){
	perror("NO SE PUDO CONECTAR");
	return 1;	
	}
	while(1){
		char clave[50];
		printf("Ingrese mensaje:");
		scanf("%s",clave);

		send(publisher, clave, strlen(clave),0);	
	}
	return 0;

}
