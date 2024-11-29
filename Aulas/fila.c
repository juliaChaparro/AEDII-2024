#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "fila.h"

struct fila{
    int tamanho;
    int ocupacao;
    int inicio;
    int final;
    int infinito;
    //t_lse* elms;
    void* *elms;
};

t_fila* criar_fila(int tamanho){
    t_fila* nova = malloc(sizeof(t_fila));
    nova->ocupacao=0;
    nova->inicio=0;
    nova->final=-1;
    nova->tamanho=(tamanho==0?2:tamanho);
    nova->infinito = (tamanho==0?1:0);

    nova->elms = malloc(sizeof(void*)*nova->tamanho);

    return nova;
}


int tamanho_fila(t_fila* f){
    return f->ocupacao;
}

void* primeiro_fila(t_fila* f){
    assert(f->ocupacao!=0);
    return f->elms[f->inicio];
}

void* desenfileirar_fila(t_fila* f){
    assert(f->ocupacao!=0);
    void* elem = f->elms[f->inicio];
    //f->elms[f->inicio] = NULL;
    f->inicio = (f->inicio+1)%f->tamanho;
    f->ocupacao--;
    return elem;
}

int enfileirar_fila(t_fila* f, void* novo){
    if ((f->infinito) && (f->tamanho == f->ocupacao)){
        int n_tam = f->tamanho*2;
        void* *n_elems = malloc(sizeof(void*)*n_tam);
        for(int i = 0; i<f->ocupacao;i++){
            n_elems[i] = f->elms[f->inicio];
            f->inicio = (f->inicio+1)%f->tamanho;
        }
        f->inicio=0;
        f->final=f->ocupacao-1;
        free(f->elms);
        f->elms = n_elems;
        f->tamanho = n_tam;
    }
    int status = 1;
    if (f->tamanho > f->ocupacao){
        f->final = (f->final+1) % f->tamanho;
        f->elms[f->final] = novo;
        f->ocupacao++;
    }else{
        status = 0;
    }
    return status;
}

int vazia_fila(t_fila* f){
    return (f->ocupacao == 0);
}



