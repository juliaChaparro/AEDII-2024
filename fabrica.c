#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "lse_neutra.h"
#include "thash.h"


// Chaves: Códigos de barras, identificadores únicos para cada elemento da fábrica.
typedef struct {
    char Códigos_barras;
    char indentificador;
}chaves;

typedef struct {
    char modelo;
    char* fabricante;
    int data_instalacao;
    char* historico_de_manutencao;
} t_equipamentos;

typedef struct{
    char lote[50];
    char fornecedor[50];
    char data_de_validade[50];
    char localização_estoque[50];
}t_materiais;


typedef struct {
    char Tipo;
    char localização; 
    char dados_históricos;
    char alarmes;

}t_sensor;


t_equipamentos* criar_fabrica(char modelo, char fabricante, int data_instalacao, char historico_de_manutencao) {
    t_equipamentos* fabi = malloc(sizeof(t_equipamentos));
    if (fabi == NULL) {
        return NULL; 
    }
    fabi->modelo = modelo;
    fabi->fabricante = fabricante; 
    fabi->data_instalacao = data_instalacao;
    fabi->historico_de_manutencao = historico_de_manutencao; 
    return fabi;
}

t_materiais* inserir_materias(char lote[50],char fornecedor[50], char data_de_validade[50], char localização_estoque[50]){
    t_materiais* mate = malloc(sizeof(t_materiais));

}

