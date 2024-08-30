#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

typedef struct elem_lse t_elementos_lse;

typedef struct {
    t_elementos_lse* prim;
    t_elementos_lse* ult;
    int tamanho;
}t_lse;


struct elem_lse{
    int carga_util;
    t_elementos_lse* prox;
};

t_elementos_lse* criar_elem_lse(int carga){
    t_elementos_lse* novo= malloc(sizeof(t_elementos_lse));
    assert(novo!=NULL);
    novo->carga_util= carga;
    novo->prox= NULL;
    return novo;
}

t_lse* criar_lse(){
    t_lse* nova=malloc(sizeof(t_lse));
    assert(nova!=NULL);
    nova->prim =NULL;
    nova->ult= NULL;
    nova-> tamanho = 0;
    return nova;
}

 void destroy_lse(t_lse* lse){
    assert(lse->prim != NULL);
    free(lse);

}

void inserir_inicio_lse(t_lse* lse, int carga){
    t_elementos_lse *novo = criar_elem_lse(carga);
    novo->prox = lse->prim;
    lse->prim = novo;

    if(lse->ult==NULL){
        lse->ult = novo;
    }
    lse->tamanho++;
}


void inserir_final_lse(t_lse* lse,int carga){
    t_elementos_lse *novo = criar_elem_lse(carga);
    if (lse->prim==NULL){
        lse->prim= novo;
        lse->ult= novo;
    }else{
        lse->ult->prox=novo;
        lse->ult= novo;
    }
    lse->tamanho++;

}


void remover_inicio_lse(t_lse* lse){
    // assert(lse->ult!=NULL);
    t_elementos_lse* seg = lse->prim->prox;
    free(lse->prim);
    lse->prim=seg;
    lse->tamanho--;

    if(seg==NULL){
        lse->ult=NULL;
    }
}



void remover_final_lse(t_lse* lse){

}


int acessar_lse(t_lse* lse,int pos){


}


int main(){
    t_lse* lse = criar_lse();
    destroy_lse(lse);
    printf("lista Destruida!!!");
}

