#include "lse_neutra.h"
#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"


typedef struct musica{
    char nome[60];
    char genero[40];
    int duracao;
}t_musica;

t_musica* criar_musica(char nome[], char genero[], int duracao){
    t_musica* nova = malloc(sizeof(t_musica));
    strcpy(nova->nome, nome);
    strcpy(nova->genero, genero);
    nova->duracao = duracao;

    return nova;
}

void imprimir_musica(t_musica* m){
    int min = m->duracao/60;
    int seg = m->duracao%60;

    printf("%s(%s) %02d:%02d\n", m->nome, m->genero, min, seg);
}

void destroy_musica(t_musica* m){
    assert(m!=NULL);
    free(m);
}

typedef struct tocador{
    t_lse* colecao;
    t_lse* mais_tocadas;
    t_lse* ultimas_tocadas;
    t_lse* favoritas;
    int lim_mais_tocadas;
}t_tocador;

t_tocador* criar_tocador(int lim_mais_tocadas){
    t_tocador *t = malloc(sizeof(t_tocador));
    t->lim_mais_tocadas = lim_mais_tocadas;
    t->colecao = criar_lse( imprimir_musica );
    t->favoritas = criar_lse( imprimir_musica );
    t->ultimas_tocadas = criar_lse( imprimir_musica);
    t->mais_tocadas = criar_lse( imprimir_musica );

    return t;
}

void quem_sao_favoritas(t_tocador* tocador){

}

// void quem_sao_ultimas_tocadas(t_tocador* tocador){

// }

void quem_sao_mais_tocadas(t_tocador* tocador){

}

void ligar_tocador(t_tocador* tocador){

    char nome[60];
    char genero[40];
    int duracao;
    char separador[3];

    for(int i=1;i<=3;i++){
        scanf("%[^;]s",nome);
        scanf("%s ",separador);
        scanf("%[^;]s", genero);
        scanf("%s ",separador);
        scanf("%d", &duracao);

        t_musica* nova = criar_musica(nome, genero, duracao);
        inserir_inicio_lse(tocador->colecao, nova);
        //imprimir_musica(nova);

    }
}

void imprimir_colecao_tocador(t_tocador* toca){
    imprimir_lse(toca->colecao);
}


int main(){
    t_tocador* sumsung = criar_tocador(10);
    ligar_tocador(sumsung);
    
    // PLAY nome_da_musica 
    // HEART nome_da_musica
    // PLAY nome_da_musica
    // PAUSE
    // RESUME
    // STOP
    // FINISH --> gravar o status da nossa colecao

    imprimir_colecao_tocador(sumsung);
}