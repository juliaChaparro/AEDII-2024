#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lse_neutra.h"
#include "thash.h"


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


struct hash{
    //t_imprimir_hash impressora;
    t_lse* *vetor;
    int tamanho;
    double fc;
};

t_hash* criar_hash(double fc){
    t_hash* nova = malloc(sizeof(t_hash));

    nova->fc = fc;
    nova->tamanho = 7;
    nova->vetor = malloc(sizeof(t_lse*)*nova->tamanho);
    for(int i=0;i<nova->tamanho;i++){
        nova->vetor[i] = criar_lse(imprimir_elem_hash, comparar_elem_hash);
    }
    
    return nova;
}

int funcao_hashing(t_hash* t, int chave){
    int pos = chave % t->tamanho;

    return pos;
}

void inserir_hash(t_hash* t, int chave, void* carga){
    int pos = funcao_hashing(t, chave);

    t_lse* colisoes = t->vetor[pos];
    t_elem_hash* novo = criar_elem_hash(chave, carga);
    inserir_inicio_lse(colisoes, novo );
}

void* buscar_hash(t_hash* t, int chave){
    int pos = funcao_hashing(t, chave);

    t_lse* colisoes = t->vetor[pos];
    t_elem_hash* e = acessar_conteudo_lse(colisoes, &chave);
    if (e!=NULL)
        return e->carga;
    else
        return NULL;
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

t_hash* rehashing(t_hash *atual){
    t_hash* nova = malloc(sizeof(t_hash));
    // codigo da rehashing

    return nova;
}

void imprimir_hash(t_hash* t){
   int K =  t->tamanho;
   for (int k=0;k<K;k++){
        t_lse* colisoes = t->vetor[k];
        imprimir_lse(colisoes); // potencial 
   }
}

