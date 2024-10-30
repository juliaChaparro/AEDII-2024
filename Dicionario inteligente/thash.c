#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lse_neutra.h"
#include "thash.h"

//inconpleto  / estramanete imcompleto 

typedef struct elem_hash t_elem_hash;
struct elem_hash{
    int chave;
    void* carga;
};


t_elem_hash* criar_elem_hash(int chave, void* carga){
    t_elem_hash* e = malloc(sizeof(t_elem_hash));
    e->chave = chave;
    e->carga = carga;

    return e;
}

int comparar_elem_hash(void* e1, void* e2){
    t_elem_hash* ee1 = e1;
    t_elem_hash* ee2 = e2;
    return (ee1->chave - ee2->chave);
}
void imprimir_elem_hash(void* ee){
    t_elem_hash* e = ee;

    printf("%d %p\n", e->chave, e->carga);
}

void destroy_elem_hash(t_elem_hash* e){
    //free(e->carga);
    free(e);
}





t_hash* criar_hash(double fc) {
    t_hash* nova = malloc(sizeof(t_hash));
    nova->fc = fc;
    nova->tamanho = 7;
    nova->num_comparacoes = 0;
    nova->num_colisoes = 0;
    nova->vetor = malloc(sizeof(t_lse*) * nova->tamanho);
    for (int i = 0; i < nova->tamanho; i++) {
        nova->vetor[i] = criar_lse(imprimir_elem_hash, comparar_elem_hash);
    }
    return nova;
}



int funcao_hashing(t_hash* t, int chave){
    int pos = chave % t->tamanho;

    return pos;
}

void inserir_hash(t_hash* t, int chave, void* carga) {
    int pos = funcao_hashing(t, chave);
    t_lse* colisoes = t->vetor[pos];
    t_elem_hash* novo = criar_elem_hash(chave, carga);

    // Count collisions in this slot
    if (acessar_inicio_lse(colisoes) != NULL) {
        t->num_colisoes++;
    }

    inserir_inicio_lse(colisoes, novo);
}


void* buscar_hash(t_hash* t, int chave) {
    int pos = funcao_hashing(t, chave);
    t_lse* colisoes = t->vetor[pos];
    t_elem_hash* elem = acessar_inicio_lse(colisoes);
    int local_comparacoes = 0;

    while (elem != NULL) {
        t->num_comparacoes++;
        local_comparacoes++;
        if (elem->chave == chave) {
            return elem->carga;
        }
        elem = proximo_elem_lse(colisoes, elem);
    }
}

void* remover_hash(t_hash* t, int chave){
    void* carga =NULL;
    int pos = funcao_hashing(t, chave);

    t_lse* colisoes = t->vetor[pos];

    t_elem_hash* e = remover_conteudo_lse(colisoes, &chave);
    if (e != NULL){
        carga = e->carga;
        destroy_elem_hash(e); 
    }
    return carga;
}

t_hash* rehashing(t_hash *atual) {
    int novoTamanho = atual->tamanho * 2;
    
    t_hash* nova = malloc(sizeof(t_hash));
    nova->fc = atual->fc;
    nova->tamanho = novoTamanho;
    nova->vetor = malloc(sizeof(t_lse*) * novoTamanho);

    for (int i = 0; i < novoTamanho; i++) {
        nova->vetor[i] = criar_lse(imprimir_elem_hash, comparar_elem_hash);
    }

    for (int i = 0; i < atual->tamanho; i++) {
        t_lse* lista = atual->vetor[i];
        t_elem_hash* elem = acessar_inicio_lse(lista);
        
        while (elem != NULL) {
            int novaPos = funcao_hashing(nova, elem->chave);
            inserir_inicio_lse(nova->vetor[novaPos], criar_elem_hash(elem->chave, elem->carga));
            elem = proximo_elem_lse(lista, elem);
        }
    }

    free(atual->vetor);
    free(atual);

    return nova;
}



void imprimir_hash(t_hash* t){
   int K =  t->tamanho;
   for (int k=0;k<K;k++){
        t_lse* colisoes = t->vetor[k];
        imprimir_lse(colisoes);  
   }
}

int get_num_comparacoes_hash(t_hash* t) {
    return t->num_comparacoes;
}

int get_num_colisoes_hash(t_hash* t) {
    return t->num_colisoes;
}