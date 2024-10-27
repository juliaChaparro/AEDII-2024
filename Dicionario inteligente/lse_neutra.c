#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "lse_neutra.h"


typedef struct elem_lse t_elemento_lse;
struct lse{
    t_elemento_lse* prim;
    t_elemento_lse* ult;
    int tamanho;
    t_imprimir_lse impressora;
    t_comparar_lse comparador;
};

struct elem_lse{
    void* carga_util;
    t_elemento_lse* prox;
};

// cria um novo elemento para uma lista simplesmente encadeada
t_elemento_lse* criar_elem_lse(void* carga){
    t_elemento_lse* novo = malloc(sizeof(t_elemento_lse));
    assert(novo!=NULL);
    novo->carga_util = carga;
    novo->prox=NULL;
    return novo; 
}
//cria uma nova lista simplesmente encadeada e inicializa seus campos.
t_lse* criar_lse( t_imprimir_lse impressora, t_comparar_lse comparador ){
    t_lse* nova = malloc(sizeof(t_lse));
    assert(nova!=NULL);
    nova->prim = NULL;
    nova->ult = NULL;
    nova->tamanho =0;
    nova->impressora = impressora;
    nova->comparador = comparador;
    
    return nova;
}

//é responsável por destruir uma lista simplesmente encadeada e liberar a memória alocada para essa estrutura
void destroy_lse(t_lse* lse){
    assert(lse->prim == NULL);
    free(lse);
}

//insere um novo elemento no início de uma lista simplesmente encadeada 
void inserir_inicio_lse(t_lse* lse, void* carga){
    t_elemento_lse* novo = criar_elem_lse(carga);
    novo->prox = lse->prim;
    lse->prim = novo;
    if(lse->ult == NULL){
        lse->ult = novo;
    }
    lse->tamanho++;
}

//insere um novo elemento no final de uma lista simplesmente encadeada
void inserir_final_lse(t_lse* lse, void* carga){
    t_elemento_lse* novo = criar_elem_lse(carga);
    if (lse->prim == NULL){
        lse->prim = novo;
        lse->ult = novo;
    }else{
        lse->ult->prox = novo;
        lse->ult = novo;
    }
    lse->tamanho++;
}


//nsere um novo elemento na lista simplesmente encadeada de acordo com um critério de comparação definido pela função comparador
void inserir_conteudo_lse(t_lse* lse, void* carga){
    t_elemento_lse* novo = criar_elem_lse(carga);
    t_elemento_lse* ant=NULL;
    t_elemento_lse* cam = lse->prim;


    
    while((cam!=NULL) && (lse->comparador(cam->carga_util, carga) <= 0) ){
        ant = cam;
        cam = cam->prox;
    }
    if(lse->prim==NULL){
        lse->ult = novo;
        lse->prim = novo;
    }
    else if (cam == lse->prim){ 
        novo->prox = lse->prim;
        lse->prim = novo;
    }else if(cam == NULL){
        lse->ult->prox = novo;
        lse->ult = novo;
    }else{
        ant->prox = novo;
        novo->prox = cam;
    }
    lse->tamanho++;
}

//remove o primeiro elemento de uma lista simplesmente encadeada e retorna a carga rmazenada nesse elemento
void* remover_inicio_lse(t_lse* lse){
    assert(lse->ult!= NULL);
    
    t_elemento_lse* seg = lse->prim->prox;
    void* carga = lse->prim->carga_util;

    free(lse->prim);
    
    lse->prim=seg;
    lse->tamanho--;
    if (seg == NULL){
        lse->ult = NULL;
    }

    return carga;
}


//remove o último elemento de uma lista simplesmente encadeada e retorna a carga armazenada nesse elemento.
void* remover_final_lse(t_lse* lse){
    assert(lse->prim!=NULL);
    void* carga;
    if(lse->prim == lse->ult){
        carga = lse->prim->carga_util;
        free(lse->prim);
        lse->prim = lse->ult = NULL;
    }else{
        t_elemento_lse* cam = lse->prim;
        while(cam->prox != lse->ult){
            cam = cam->prox;
        }
        carga = lse->ult->carga_util;
        free(lse->ult);
        lse->ult = cam;
    }
    lse->tamanho--;
    return carga;
}

//remove um elemento de uma lista simplesmente encadeada com base em uma chave fornecida, que é comparada com a carga útil dos elementos da lista
void* remover_conteudo_lse(t_lse* lse, void* chave){
    assert(lse->prim!=NULL);

    void* carga = NULL;
    t_elemento_lse* ant = NULL;
    t_elemento_lse* cam = lse->prim;
    while((cam!=NULL) && (lse->comparador(cam->carga_util,chave)!=0) ){
        ant = cam;
        cam = cam->prox;
    }

    if (cam!=NULL){
        if (cam == lse->prim){
            lse->prim = cam->prox;
            if(lse->prim == NULL)
                lse->ult=NULL;
        }else if (cam == lse->ult){
            ant->prox = NULL;
            lse->ult = ant;
        }else{
            ant->prox = cam->prox;
        }
        carga = cam->carga_util;
        free(cam);
        lse->tamanho--;
    }

    return carga;
}

//permite acessar o elemento de uma lista simplesmente encadeada em uma posição específica, baseada em um índice fornecido
void* acessar_lse(t_lse* lse, int pos){
    assert(pos>=1 && pos<=lse->tamanho);
    t_elemento_lse* cam = lse->prim;
    for(int i=1;i<pos;i++){
        cam = cam->prox;
    }
    return cam->carga_util;
}


//busca e retorna a carga de um elemento na lista simplesmente encadeada que corresponde a uma chave fornecida
void* acessar_conteudo_lse(t_lse* lse, void* chave){
    void* carga=NULL;
    t_elemento_lse* cam = lse->prim;
    while( (cam!=NULL) && (lse->comparador(cam->carga_util, chave)!=0) ){
        cam = cam->prox;
    }
    if(cam!=NULL){
        carga = cam->carga_util;
    }
    return carga;
}

//percorre todos os elementos de uma lista simplesmente encadeada e imprime seus conteúdos usando uma função fornecida.
void imprimir_lse(t_lse* lse){
    t_elemento_lse* cam = lse->prim;
    while (cam!=NULL){

        lse->impressora(cam->carga_util);
        cam = cam->prox;
    }
    
}


