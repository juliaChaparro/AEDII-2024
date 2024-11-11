#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lse_neutra.h"
#include "thash.h"

struct hash {
    t_lse** vetor;
    int tamanho;
    double fc;
    int num_comparacoes; 
    int num_colisoes;
    int inseridos;

};

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
    nova->inseridos= 0;
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


double calcular_fc(t_hash* hash){
    return (double) hash->inseridos / (double) hash->tamanho;
}


void inserir_hash(t_hash* t, int chave, void* carga){
    double cal = calcular_fc(t);
    if(cal >= t->fc){
        rehashing(t);
    }
    
    int pos = funcao_hashing(t, chave);
    t_lse* colisoes = t->vetor[pos];

    int tam = tamanho_lse(colisoes);
    if(tam != 0){
        t->num_colisoes++;
    }

    t_elem_hash* novo = criar_elem_hash(chave, carga);
    
    inserir_inicio_lse(colisoes, novo );
    t->inseridos++;
}

void* buscar_hash(t_hash* t, int chave){
    int pos = funcao_hashing(t, chave);

    t_lse* colisoes = t->vetor[pos];
    t_elem_hash* e = acessar_conteudo_lse(colisoes, &chave);
    t->num_comparacoes++;
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
    t->inseridos--;
}


void rehashing(t_hash *atual) {
    int novoTamanho = atual->tamanho * 2;
    t_hash nova;
    nova.fc = atual->fc;
    nova.tamanho = novoTamanho;
    nova.vetor = malloc(sizeof(t_lse*) * novoTamanho);
    nova.num_colisoes = atual->num_colisoes;
    nova.num_comparacoes= atual->num_comparacoes;
    nova.inseridos= atual->inseridos;

    for (int i = 0; i < novoTamanho; i++) {
        nova.vetor[i] = criar_lse(imprimir_elem_hash, comparar_elem_hash);
    }

    for (int i = 0; i < atual->tamanho; i++) {
        t_lse* lista = atual->vetor[i];
        int tam = tamanho_lse(lista);
        for(int j=1;j<=tam;j++){
            t_elem_hash* elem0 = remover_inicio_lse(lista);
            int novaPos = funcao_hashing(&nova,elem0->chave);
            inserir_inicio_lse(nova.vetor[novaPos],elem0);
        }
        destroy_lse(lista);
    }

    free(atual->vetor);
    *atual = nova;
}


void usar_rehashing(t_hash* hash){
    int cal = calcular_fc(hash);

    if(cal == 1){
        rehashing(hash);
    }
    else{
        criar_hash(cal);
    }
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