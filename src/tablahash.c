#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablahash.h"
/*funcion creae tabla hash;   Hasht *new_ht(int size)*/
Hasht *new_ht(int size){
    Hasht *new_table;
    
    if (size<1) return NULL; /* tamano de la tabla invalido */

    /* intento de asignar memoria para la estructura de la tablahash */
    if ((new_table = malloc(sizeof(Hasht))) == NULL) {
        return NULL;
    }
    
    /* intento de asignar memoria para la estructura de la lista */
    if ((new_table->tabla = malloc(sizeof(list *) * size)) == NULL) {
        return NULL;
    }

    /* inicializar los elemetos de la tabla */
    for(int i=0; i<size; i++) new_table->tabla[i] = NULL;

    /* asigno tamano a la tabla */
    new_table->size = size;

    return new_table;}
/*buscar una clave*/
void *get_ht(Hasht *table, char *c){
    int f;
    f= strlen(c);
    int p=0;
    list *lista;

    for(int i=0;i<f;++i){
        int a=c[i]*(i+1);   
        p=p+a;
    } 
    
    int hashval = p%table->size;


    for(lista = table->tabla[hashval]; lista != NULL; lista = lista->next) {
        if (strcmp(c, lista->string) == 0) {
            printf("\n%s, SI\n",c);
	    break;
        }
    }
    if(lista == NULL){
	printf("\n%s, NO\n",c);	
    }}
/*Agregar una clave a la lista simple enlazada;   int add_ht(Hasht *table, ch ar *c)*/
int add_ht(Hasht *table, char *c){
    list *new_list;
    list *current_list;
    int f;
    f= strlen(c);
    int p=0;

    for(int i=0;i<f;++i){
        int a=c[i]*(i+1);   
        p=p+a;
    }
    
    int hashval = p%table->size;

    if ((new_list = malloc(sizeof(list))) == NULL) return 1;

    /* existe? */
    list *lista;
    for(lista = table->tabla[hashval]; lista != NULL; lista = lista->next) {
        if (strcmp(c, lista->string) == 0) {
            current_list = lista;
        }
        else{
            current_list = NULL;
        }

    }

            /* si ya existe, no lo inserto otra vez. */
    //if (current_list != NULL) return 2;
    /* Insert into list */
    new_list->string = strdup(c);
    new_list->next = table->tabla[hashval];
    table->tabla[hashval] = new_list;

    return 0;}
/*eliminar tabla;   void destroy_ht(Hasht *table);*/
void destroy_ht(Hasht *table){
    int i;
    list *lista, *temp;

    if (table==NULL) return;

    /* libero memoria para cada elemto de la tabla,incluyedo 
    los string.*/
    for(i=0; i<table->size; i++) {
        lista = table->tabla[i];
        while(lista!=NULL) {
            temp = lista;
            lista = lista->next;
            free(temp->string);
            free(temp);
        }
    }

    /* liebro la tabla */
    free(table->tabla);
    free(table);}
/*borrar una clave de la lista : void *remove_ht(Hasht *table, char *c)*/
void *remove_ht(Hasht *table, char *c){
    int i;
    list *lista, *prev;
    int f;
    f= strlen(c);
    int p=0;

    for(int i=0;i<f;++i){
        int a=c[i]*(i+1);   
        p=p+a;
    } 
    int hashval = p%table->size;

    for(prev=NULL, lista=table->tabla[hashval];
        lista != NULL && strcmp(c, lista->string);
        prev = lista,
        lista = lista->next);
    
    if (lista==NULL)  return NULL;

    if (prev==NULL) {
        table->tabla[hashval] = lista->next;
    }
    else {
        prev->next = lista->next;
    }
    
    free(lista->string);
    free(lista);}
/*imprimir por pantalla la hashtable*/
void print_ht(Hasht *table){
    list *lista;
    if (table==NULL) return;
    for(int i=0;i<table->size ;i++){
        lista= table->tabla[i];
        printf("(%i)\t",i);
        while(lista!=NULL){
            printf("%s,",lista->string);
            lista=lista->next;
        }
        printf("\n");
    }}