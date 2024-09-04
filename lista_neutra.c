#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include"lista_neutra.h"

typedef struct elem_lse t_elementos_lse;

struct lse{
    t_elementos_lse* prim;
    t_elementos_lse* ult;
    int tamanho;
};


struct elem_lse{
    void* carga_util;
    t_elementos_lse* prox;
};

t_elementos_lse* criar_elem_lse(void* carga){
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

void inserir_inicio_lse(t_lse* lse, void* carga){
    t_elementos_lse *novo = criar_elem_lse(carga);
    novo->prox = lse->prim;
    lse->prim = novo;

    if(lse->ult==NULL){
        lse->ult = novo;
    }
    lse->tamanho++;
}


void inserir_final_lse(t_lse* lse,void* carga){
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


void inserir_conteudo_lse(t_lse* lse, void* carga){
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


void* acessar_conteudo_lse(t_lse* lse,void* chave){
    void* carga=NULL;
    t_elementos_lse* cam = lse->prim;
//TO DO
    while((cam!=NULL)&&(cam->carga_util!=chave)){
        cam=cam->prox;

    }
    if(cam!=NULL){
        carga = cam->carga_util;
    }


}
void* remover_conteudo_lse(t_lse*lse,int chave){
    assert(lse->prim!=NULL);
    void* carga=NULL;
    t_elementos_lse* ant=NULL;
    t_elementos_lse* cam = lse->prim;
//to do
    while((cam!=NULL)&&(cam->carga_util!=chave)){
        ant = cam;
        cam = cam->prox;
    }
    if(cam!=NULL){
        if(cam==lse->prim){
            lse->prim=cam->prox;
            if (lse->prim==NULL){
                lse->ult=NULL;
            }
            cam = cam->prox;
        }else if (cam==lse->ult){
            ant->prox=NULL;
            lse->ult=ant;
        }else{
            ant->prox = cam->prox;
            
        }
        carga = cam->carga_util;
        free(cam);
        lse->tamanho--;

    }
    return carga;
}


void* remover_inicio_lse(t_lse* lse){
    assert(lse->ult!=NULL);
    
    t_elementos_lse* seg = lse->prim->prox;
    void* carga = lse->prim->carga_util;
    free(lse->prim);
    lse->prim=seg;
    lse->tamanho--;
    if(seg==NULL){
        lse->ult=NULL;
    }
    return carga;
}



void* remover_final_lse(t_lse* lse){
    assert(lse->prim!=NULL);
    void* carga;
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



void* acessar_lse(t_lse* lse,int pos){

    assert(pos>=1&&pos<=lse->tamanho);
    t_elementos_lse* cam =lse->prim;

    for(int i=1;i<pos;i++){
        cam =cam->prox;
    }
    return cam->carga_util;

}



//int main(){
//    t_lse* lse = criar_lse();
//    inserir_conteudo_lse(lse,30);
//    inserir_conteudo_lse(lse,10);
//    inserir_conteudo_lse(lse,15);
//    //inserir_final_lse(lse,10);
//
//    int carga = acessar_lse(lse,2);
//    printf("Acesso: %d\n",carga);

//    carga = acessar_conteudo_lse(lse,15);
//    printf("Acesssar: %d\n",carga);
//    carga = remover_conteudo_lse(lse,15);
//    printf("remover: %d\n",carga);

//    destroy_lse(lse);

//}

