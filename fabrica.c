#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "lse_neutra.h"
#include "thash.h"
#include "avl.h"

// tlz eu nao use as structs
// Chaves: Códigos de barras, identificadores únicos para cada elemento da fábrica.
typedef struct {
    char* chave; // Pode ser código de barras, identificador único, etc.
    void* dado;  // Ponteiro para t_equipamentos, t_materiais ou t_sensor
} t_no_hash;

typedef struct {
    char modelo;
    char* fabricante;
    int data_instalacao;
    char* historico_de_manutencao;
} t_equipamentos;

typedef struct {
    char* lote;
    char* fornecedor;
    char* data_de_validade;
    char* localizacao_estoque;
} t_materiais;

typedef struct {
    char tipo;
    char localizacao;
    char dados_historicos;
    char alarmes;
} t_sensor;

// talvez eu nao use as structs

// o trabalho começa

typedef struct {

    t_avl* avl;
    t_hash* hash;

}t_todas;


// Funções de criação

t_equipamentos* criar_equipamento(char modelo, char* fabricante, int data_instalacao, char* historico_de_manutencao) {
    t_equipamentos* fabi = malloc(sizeof(t_equipamentos));
    if (fabi == NULL) {
        return NULL;
    }
    fabi->modelo = modelo;
    fabi->fabricante = strdup(fabricante);
    fabi->data_instalacao = data_instalacao;
    fabi->historico_de_manutencao = strdup(historico_de_manutencao);
    return fabi;
}

t_materiais* criar_materiais(char* lote, char* fornecedor, char* data_de_validade, char* localizacao_estoque) {
    t_materiais* mate = malloc(sizeof(t_materiais));
    if (mate == NULL) {
        return NULL;
    }
    mate->lote = strdup(lote);
    mate->fornecedor = strdup(fornecedor);
    mate->data_de_validade = strdup(data_de_validade);
    mate->localizacao_estoque = strdup(localizacao_estoque);
    return mate;
}

t_sensor* criar_sensor(char tipo, char localizacao, char dados_historicos, char alarmes) {
    t_sensor* senso = malloc(sizeof(t_sensor));
    if (senso == NULL) {
        return NULL;
    }
    senso->tipo = tipo;
    senso->localizacao = localizacao;
    senso->dados_historicos = dados_historicos;
    senso->alarmes = alarmes;
    return senso;
}


t_todas* criar_todas(t_todas* todas){

    criar_avl(todas->avl->impressora,todas->avl->comparar);
    criar_hash(todas->hash->fc); 

}


void inserir_em_todas(t_todas* todas, void* chave, void* chave_hash){

    inserir_avl(todas->avl,chave);
    inserir_hash(todas->hash,chave, chave_hash);// dps tenho que ver o NULL // eu troquei para chave_hashs

}

void* buscar_em_todas(t_todas* todas, void* chave){

    buscar_avl(todas->avl,chave);
    buscar_hash(todas->hash, chave);

}

void* remover_em_todas(t_todas* todas, void* chave){

    remover_avl(todas->avl,chave);
    remover_hash(todas->hash,chave);

}


int todas_comparacoes(t_todas* todas){

    int avl_rotacoes = get_num_rotacoes_avl;
    int avl_comparacoes = get_num_comparacoes_avl;
    int hash_comparacoes = get_num_comparacoes_hash;
    int hash_colisoes = get_num_colisoes_hash;

    printf("numero de rotaçoes da AVL: %d",get_num_rotacoes_avl);
    printf("numero de comparaçoes da AVL: %d",get_num_comparacoes_avl);
    printf("numero de comparaçoes da HASH: %d",get_num_comparacoes_hash);
    printf("numero de colisoes da HASH: %d",get_num_colisoes_hash);

}
