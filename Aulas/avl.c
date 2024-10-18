#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "time.h"
#include "musica.h"

//como eu uso as funcoes para atualizar o balanciamaneto

typedef int(*t_comparar_avl)(void*,s void*);
typedef void(*t_imprimir_avl)(void*);

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

typedef struct avl t_avl;
struct avl{
    t_no* raiz;
    int tamanho;
    t_imprimir_avl impressora;
    t_comparar_avl comparar;
};

t_avl* criar_avl(t_imprimir_avl impressora, t_comparar_avl comparar){
    t_avl* nova = malloc(sizeof(t_avl));

    nova->raiz = NULL;
    nova->tamanho = 0;

    nova->impressora = impressora;
    nova->comparar = comparar;

    return nova;

}

static int __tamanho_avl(t_no* no){
    if (no==NULL)
        return 0;
    return __tamanho_avl(no->sad)+__tamanho_avl(no->sae)+1;
}

static void* __buscar_avl(t_no* raiz, t_comparar_avl comparar, void* chave){
    if(raiz==NULL){
        return NULL;  
    }else if(comparar(raiz->info, chave) == 0){
        return raiz->info;
    }else if(comparar(raiz->info, chave) > 0){
        return __buscar_avl(raiz->sae, comparar, chave);
    }else{
        return __buscar_avl(raiz->sad, comparar, chave);
    }
}

void* buscar_avl(t_avl* avl, void* chave){
    assert(avl!=NULL);

    return __buscar_avl(avl->raiz, avl->comparar, chave);
}

void rotacao_SE(t_no* A, t_no* B){
    A->sad = B->sae;
    B->sae = A;
    B->ancestral = A->ancestral;
    A->ancestral = B;
    if (A->sad){
        A->sad->ancestral = A;
    }
}

void rotacao_SD(t_no* A, t_no* B){
    A->sae = B->sad;
    B->sad = A;
    B->ancestral = A->ancestral;
    A->ancestral = B;
    if (A->sae){
        A->sae->ancestral = A;
    }

}

static t_no* __inserir_avl(t_no* raiz, t_comparar_avl comparar, t_no* ancestral, void* info){
    if(raiz == NULL){
        t_no* novo = criar_no(ancestral, info);
        return novo;
    }else{
        int retorno = comparar(raiz->info, info);
        if (retorno > 0){
           raiz->sae = __inserir_avl(raiz->sae, comparar, raiz, info); 
           return raiz;
        }else{
            raiz->sad = __inserir_avl(raiz->sad, comparar, raiz, info);
            return raiz;
        }
    }
}

void inserir_avl(t_avl* avl, void* info){
    assert(avl!=NULL);

    avl->raiz = __inserir_avl(avl->raiz, avl->comparar, NULL, info);
}

static t_no* __podar_avl(t_no* no){
    if (no==NULL){
        return NULL;
    }
    no->sae = __podar_avl(no->sae);
    no->sad = __podar_avl(no->sad);
    free(no->info); // potencial para memory leak
    free(no);
    return NULL;
}

void podar_avl(t_avl* avl, void* chave){
    t_no* no = __buscar_avl(avl->raiz, avl->comparar, chave);
    if (no != NULL){
        if (no->ancestral != NULL){ // folha ou nó interno
            avl->tamanho -= __tamanho_avl(no);
            t_no* ancestral = no->ancestral;
            if (ancestral->sad == no){
                ancestral->sad = __podar_avl(no);
            }else{
                ancestral->sae = __podar_avl(no);
            }
        }else{
            avl->raiz = __podar_avl(no);
            avl->tamanho=0;
        }
    }
}

static void __trocar_info(t_no* n1, t_no* n2){
    void* info = n1->info;
    n1->info = n2->info;
    n2->info = info;
}

static t_no* __remover_avl(t_no* raiz, t_comparar_avl comparar, void* chave, int *flag){
    if(raiz == NULL){
        flag=0; // false
        return NULL;
    }else{
        int retorno = comparar(raiz->info, chave);
        if (retorno > 0){
            raiz->sae = __remover_avl(raiz->sae, comparar, chave, flag);
        }else if(retorno < 0){
            raiz->sad = __remover_avl(raiz->sad, comparar, chave, flag);
        }else{
            if ((raiz->sae == NULL) && (raiz->sad == NULL)){
                free(raiz->info); // memory leaky
                free(raiz);
                return NULL;
            }else if(raiz->sae == NULL){ // direita
                raiz->sad->ancestral = raiz->ancestral;
                t_no* sad = raiz->sad;
                free(raiz->info);
                free(raiz);
                raiz = sad;
            }else if(raiz->sad == NULL){ // esquerda
                raiz->sae->ancestral = raiz->ancestral;
                t_no* sae = raiz->sae;
                free(raiz->info);
                fre#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "time.h"
#include "../../../Modulo01/src/202402/musica.h"

typedef int(*t_comparar_avl)(void*, void*);
typedef void(*t_imprimir_avl)(void*);

typedef struct no t_no;
struct no{
    void* info;
    t_no* sae;
    t_no* sad;
    t_no* ancestral;
    int fb;
};

t_no* criar_no(t_no* ancestral, void* info){
    t_no* novo = malloc(sizeof(t_no));
    novo->info = info;
    novo->sad = NULL;
    novo->sae = NULL;
    novo->ancestral = ancestral;
    novo->fb=0;
    return novo;
}

typedef struct avl t_avl;
struct avl{
    t_no* raiz;
    int tamanho;
    t_imprimir_avl impressora;
    t_comparar_avl comparar;
};

t_avl* criar_avl(t_imprimir_avl impressora, t_comparar_avl comparar){
    t_avl* nova = malloc(sizeof(t_avl));

    nova->raiz = NULL;
    nova->tamanho = 0;

    nova->impressora = impressora;
    nova->comparar = comparar;

    return nova;

}

static int __tamanho_avl(t_no* no){
    if (no==NULL)
        return 0;
    return __tamanho_avl(no->sad)+__tamanho_avl(no->sae)+1;
}

static void* __buscar_avl(t_no* raiz, t_comparar_avl comparar, void* chave){
    if(raiz==NULL){
        return NULL;  
    }else if(comparar(raiz->info, chave) == 0){
        return raiz->info;
    }else if(comparar(raiz->info, chave) > 0){
        return __buscar_avl(raiz->sae, comparar, chave);
    }else{
        return __buscar_avl(raiz->sad, comparar, chave);
    }
}

void* buscar_avl(t_avl* avl, void* chave){
    assert(avl!=NULL);

    return __buscar_avl(avl->raiz, avl->comparar, chave);
}

t_no* rotacao_SE(t_no* A, t_no* B){
    A->sad = B->sae;
    B->sae = A;
    B->ancestral = A->ancestral;
    A->ancestral = B;
    if (A->sad!=NULL){
        A->sad->ancestral = A;
    }
    return B;
}

t_no* rotacao_SD(t_no* A, t_no* B){
    A->sae = B->sad;
    B->sad = A;
    B->ancestral = A->ancestral;
    A->ancestral = B;
    if (A->sae){
        A->sae->ancestral = A;
    }

}

static int __calcular_fb(t_no* raiz){
        int fb = __altura_avl(raiz->sad) - __altura_avl(raiz->sae);
        
        return fb;
    }

static t_no* __inserir_avl(t_no* raiz, t_comparar_avl comparar, t_no* ancestral, void* info){
    if(raiz == NULL){
        t_no* novo = criar_no(ancestral, info);
        return novo;
    }else{
        int retorno = comparar(raiz->info, info);
        if (retorno > 0){
           raiz->sae = __inserir_avl(raiz->sae, comparar, raiz, info); 
           raiz->fb = __calcular_fb(raiz);
           if (raiz->fb == -2){
                if (raiz->sae->fb == -1){
                    raiz = rotacao_SD(raiz, raiz->sae);
                }else if(raiz->sae->fb == 1){
                    t_no* aux = raiz->sae->sad;
                    t_no* B = raiz->sae;
                    rotacao_SE(B, aux);
                    raiz = rotacao_SD(aux, raiz); 
                }
           }
           return raiz;
        }else{
            raiz->sad = __inserir_avl(raiz->sad, comparar, raiz, info);
            raiz->fb = __calcular_fb(raiz);
           if (raiz->fb == 2){
                if (raiz->sad->fb == 1){
                    raiz = rotacao_SE(raiz, raiz->sad);
                }else if(raiz->sad->fb == -1){
                    t_no* aux = raiz->sad->sae;
                    t_no* B = raiz->sad;
                    rotacao_SD(B,aux);
                    raiz = rotacao_SE(raiz,aux);
                }
           }
            return raiz;
        }
    }
}

void inserir_avl(t_avl* avl, void* info){
    assert(avl!=NULL);

    avl->raiz = __inserir_avl(avl->raiz, avl->comparar, NULL, info);
}

static t_no* __podar_avl(t_no* no){
    if (no==NULL){
        return NULL;
    }
    no->sae = __podar_avl(no->sae);
    no->sad = __podar_avl(no->sad);
    free(no->info); // potencial para memory leak
    free(no);
    return NULL;
}

void podar_avl(t_avl* avl, void* chave){
    t_no* no = __buscar_avl(avl->raiz, avl->comparar, chave);
    if (no != NULL){
        if (no->ancestral != NULL){ // folha ou nó interno
            avl->tamanho -= __tamanho_avl(no);
            t_no* ancestral = no->ancestral;
            if (ancestral->sad == no){
                ancestral->sad = __podar_avl(no);
            }else{
                ancestral->sae = __podar_avl(no);
            }
        }else{
            avl->raiz = __podar_avl(no);
            avl->tamanho=0;
        }
    }
}

static void __trocar_info(t_no* n1, t_no* n2){
    void* info = n1->info;
    n1->info = n2->info;
    n2->info = info;
}

static t_no* __remover_avl(t_no* raiz, t_comparar_avl comparar, void* chave, int *flag){
    if(raiz == NULL){
        flag=0; // false
        return NULL;
    }else{
        int retorno = comparar(raiz->info, chave);
        if (retorno > 0){
            raiz->sae = __remover_avl(raiz->sae, comparar, chave, flag);
            raiz->fb = __calcular_fb(raiz);
            if (raiz->fb == 2){
                if ( (raiz->sad->fb == 1) || (raiz->sad->fb=0)){
                    raiz = rotacao_SE(raiz, raiz->sad);
                }else{
                    t_no* aux = raiz->sad->sae;
                    rotacao_SD(raiz->sad, aux);
                    raiz = rotacao_SE(raiz, aux);
                }
            }
        }else if(retorno < 0){
            raiz->sad = __remover_avl(raiz->sad, comparar, chave, flag);
        }else{
            if ((raiz->sae == NULL) && (raiz->sad == NULL)){
                free(raiz->info); // memory leaky
                free(raiz);
                return NULL;
            }else if(raiz->sae == NULL){ // direita
                raiz->sad->ancestral = raiz->ancestral;
                t_no* sad = raiz->sad;
                free(raiz->info);
                free(raiz);
                raiz = sad;
            }else if(raiz->sad == NULL){ // esquerda
                raiz->sae->ancestral = raiz->ancestral;
                t_no* sae = raiz->sae;
                free(raiz->info);
                free(raiz);
                raiz = sae;
            }else{ // duas descendencias
                t_no* aux = raiz->sae;
                while(aux->sad!=NULL){
                    aux = aux->sad;
                }
                __trocar_info(raiz, aux);
                raiz->sae = __remover_avl(raiz->sae,comparar,chave, flag);

            }
        }
    }
    *flag = 1; // true, teve remoção
    return raiz;
}


void remover_avl(t_avl* avl, void* chave){
    assert(avl!=NULL);
    int flag=0;
    avl->raiz = __remover_avl(avl->raiz, avl->comparar, chave, &flag);
    if (flag == 1){
        avl->tamanho--;
    }
}

#define MAX(a,b) (a>b?a:b)
static int __altura_avl(t_no* raiz){
    if (raiz == NULL){
        return -1;
    }
    return MAX(__altura_avl(raiz->sae),__altura_avl(raiz->sad))+1;
}

int altura_avl(t_avl* avl){

    return __altura_avl(avl->raiz);

}e(raiz);
                raiz = sae;
            }else{ // duas descendencias
                t_no* aux = raiz->sae;
                while(aux->sad!=NULL){
                    aux = aux->sad;
                }
                __trocar_info(raiz, aux);
                raiz->sae = __remover_avl(raiz->sae,comparar,chave, flag); 
            }
        }
    }
    *flag = 1; // true, teve remoção
    return raiz;
}


void remover_avl(t_avl* avl, void* chave){
    assert(avl!=NULL);
    int flag=0;
    avl->raiz = __remover_avl(avl->raiz, avl->comparar, chave, &flag);
    if (flag == 1){
        avl->tamanho--;
    }
}

#define MAX(a,b) (a>b?a:b)
static int __altura_avl(t_no* raiz){
    if (raiz == NULL){
        return -1;
    }
    return MAX(__altura_avl(raiz->sae),__altura_avl(raiz->sad))+1;
}

int altura_avl(t_avl* avl){

    return __altura_avl(avl->raiz);

}