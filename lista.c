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

t_elementos_lse* criar_elem_lse(int carga){#include "stdio.h"
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
    assert(lse->prim == NULL);
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


void inserir_conteudo_lse(t_lse* lse, int carga){
    t_elementos_lse* novo = criar_elem_lse(carga);
    t_elementos_lse* ant=NULL;
    t_elementos_lse* cam =  lse->prim;


    while((cam != NULL)&&(cam->carga_util < carga)){
        ant = cam;
        cam = cam->prox;
    }
    if(cam==lse->prim){//inicio da lista
        novo->prox=lse->prim;
        lse->prim=novo;
    }else if(cam == NULL){//final da lista 
        lse->ult->prox = novo;
        lse->ult = novo;
    }else{
        ant->prox=novo;
        novo->prox=cam;

    }
    lse->tamanho++;
}


void acessar_conteudo_lse(){

}
void remover_conteudo_lse();


int remover_inicio_lse(t_lse* lse){
    assert(lse->ult!=NULL);
    
    t_elementos_lse* seg = lse->prim->prox;
    int carga = lse->prim->carga_util;
    free(lse->prim);
    lse->prim=seg;
    lse->tamanho--;
    if(seg==NULL){
        lse->ult=NULL;
    }
    return carga;
}



int remover_final_lse(t_lse* lse){
    assert(lse->prim!=NULL);
    int carga;
    if(lse->prim==lse->ult){
        carga = lse->prim->carga_util;
        free(lse->prim);
        lse->prim=lse->ult=NULL;

    }else{
        t_elementos_lse* cam=lse->prim;

        while(cam->prox != NULL){
            cam = cam->prox;
        }
        carga=lse->ult->carga_util;
        free(lse->ult);
        lse->ult = cam;  
        }
    lse->tamanho--;    
    return carga;
}



int acessar_lse(t_lse* lse,int pos){

    assert(pos>=1&&pos<=lse->tamanho);
    t_elementos_lse* cam =lse->prim;

    for(int i=1;i<pos;i++){
        cam =cam->prox;
    }
    return cam->carga_util;

}



int main(){
    t_lse* lse = criar_lse();
    inserir_conteudo_lse(lse,30);
    inserir_conteudo_lse(lse,10);
    inserir_conteudo_lse(lse,15);
    //inserir_final_lse(lse,10);
    int carga = acessar_lse(lse,2);
    printf("Acesso: %d\n",carga);

    //int carga = remover_inicio_lse(lse);
    //printf("removido do inicio: %d\n",carga);
//
    //carga = remover_final_lse(lse);
    //printf("removido do final: %d\n",carga);
//
    //inserir_final_lse(lse,40);
//
    //carga = acessar_lse(lse,1);
    //printf("Acesso: %d\n",carga);
    destroy_lse(lse);

}


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
    t_elementos_lse* aux;

    while(lse->prim->prox != NULL){
        aux = lse->prim->prox;
    }
    
    aux->prox=NULL;
    free(lse->ult);

    lse->ult = aux;  
     
}



int acessar_lse(t_lse* lse,int pos){
    
    t_lse* nou,aux;
    
    while(aux && aux->carga != NULL){
        aux = aux->prox;
    }
    if(nou){
        nou= aux;
    }
    return nou;
}


int main(){
    t_lse* lse = criar_lse();
    destroy_lse(lse);
    printf("lista Destruida!!!");
}

