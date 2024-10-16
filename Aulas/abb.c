#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "time.h"
#include "musica.h"

typedef int(*t_comparar_abb)(void*, void*);
typedef void(*t_imprimir_abb)(void*);

typedef struct no t_no;
struct no{
    void* info;
    t_no* sae;
    t_no* sad;
    t_no* ancestral;
};

t_no* criar_no(t_no* ancestral, void* info){
    t_no* novo = malloc(sizeof(t_no));
    novo->info = info;
    novo->sad = NULL;
    novo->sae = NULL;
    novo->ancestral = ancestral;
    return novo;
}

typedef struct abb t_abb;
struct abb{
    t_no* raiz;
    int tamanho;
    t_imprimir_abb impressora;
    t_comparar_abb comparar;
};

t_abb* criar_abb(t_imprimir_abb impressora, t_comparar_abb comparar){
    t_abb* nova = malloc(sizeof(t_abb));

    nova->raiz = NULL;
    nova->tamanho = 0;

    nova->impressora = impressora;
    nova->comparar = comparar;

    return nova;

}

static void* __buscar_abb(t_no* raiz, t_comparar_abb comparar, void* chave){
    if(raiz==NULL){
        return NULL;  
    }else if(comparar(raiz->info, chave) == 0){
        return raiz->info;
    }else if(comparar(raiz->info, chave) > 0){
        return __buscar_abb(raiz->sae, comparar, chave);
    }else{
        return __buscar_abb(raiz->sad, comparar, chave);
    }
}

void* buscar_abb(t_abb* abb, void* chave){
    assert(abb!=NULL);

    return __buscar_abb(abb->raiz, abb->comparar, chave);
}

t_no* __inserir_abb(t_no* raiz, t_comparar_abb comparar, t_no* ancestral, void* info){
    if(raiz == NULL){
        t_no* novo = criar_no(ancestral, info);
        return novo;
    }else{
        int retorno = comparar(raiz->info, info);
        if (retorno > 0){
           raiz->sae = __inserir_abb(raiz->sae, comparar, raiz, info); 
           return raiz;
        }else{
            raiz->sad = __inserir_abb(raiz->sad, comparar, raiz, info);
            return raiz;
        }
    }
}

void inserir_abb(t_abb* abb, void* info){
    assert(abb!=NULL);

    abb->raiz = __inserir_abb(abb->raiz, abb->comparar, NULL, info);
}

static t_no* __podar_abb(t_no* no){
    if(no == NULL){
        return NULL;
    }
    no->sae = __podar_abb(no->sae);
    no->sad = __podar_abb(no->sad);

}

void podar_abb(t_abb* abb, void* chave){
    t_no* no = __buscar_abb(abb->raiz,abb->comparar, chave);
    if(no != NULL){
        if(no->ancestral != NULL){ // folha ou nó interno
            abb->tamanho -= __tamanho_abb(no);
            t_no* ancestral = no->ancestral;
        }
    }
}


static void __remover_abb(t_no* raiz, t_comparar_abb comparar, void* chave){
    if(raiz == NULL){
        return;
    }else{
        int retorno = comparar(raiz->info, chave);
        if(retorno > 0){
            raiz->sae = __remover_abb(raiz->sae, comparar,chave);
        }else if(retorno < 0){
            raiz->sad = __remover_abb(raiz->sad, comparar, chave);
        }else{
            if((raiz->sae == NULL) && (raiz->sad == NULL)){
                free(raiz->info);
                free(raiz);
                return NULL;
            }else if((raiz->sae == NULL) && (raiz->sad != NULL)){ //direita
                
            }else if((raiz->sae != NULL) && (raiz->sad == NULL)){ //esquerda

            }else{ //duas descendencias
                
            }
        }
    }
}
void* remover_abb(t_abb* abb, void* chave){
    assert(abb != NULL);

    __remover_abb(abb->raiz, abb->comparar,chave)
}