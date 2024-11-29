#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

typedef struct fila t_fila;
t_fila* criar_fila(int tamanho);
int tamanho_fila(t_fila* f);
void* primeiro_fila(t_fila* f);
void* desenfileirar_fila(t_fila* f);
int enfileirar_fila(t_fila* f, void* novo);
int vazia_fila(t_fila* f);




