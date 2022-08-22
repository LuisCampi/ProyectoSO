#ifndef TABLA_
#define TABLA_
typedef struct _list_t_ {
    char *string;
    struct _list_t_ *next;
} list;

typedef struct h_t {
    int size;       /* el tamano de la tabla */
    list **tabla; /* los elementos de la tabla */
} Hasht;
typedef struct h_t Hasht; //
int add_ht(Hasht *table, char *c); //
void *get_ht(Hasht *table, char *c);
void *remove_ht(Hasht *table, char *c); //
void destroy_ht(Hasht *table); //
Hasht *new_ht(int size); //
void print_ht(Hasht *table);
void ingresoDatos(char *clave,Hasht *tabla);

#endif
