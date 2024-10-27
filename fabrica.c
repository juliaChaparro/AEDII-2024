#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "lse_neutra.h"


// Chaves: Códigos de barras, identificadores únicos para cada elemento da fábrica.

typedef struct t_fabrica{
    char modelo[50];
    char fabricante[50];
    int data_instalação;
    char histórico_de_manutenção[50];

}t_fabrica;

typedef struct t_materiais{
    char lote[50];
    char fornecedor[50];
    char data_de_validade[50];
    char localização_estoque[50];

}t_materiais;


