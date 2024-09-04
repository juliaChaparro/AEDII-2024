
#include "lista_neutra.h"
#include"stdio.h"
#include"stdlib.h"
#include "assert.h"
#include "string.h"


typedef struct  musica{
    char nome[60];
    char genero[40];
    int duracao;
}t_musica;


typedef struct tocador{
    t_lse* colecao;
    t_lse* mais_tocados;
    t_lse* ultimas_tocadas;
    t_lse* favoritas;
    int lim_mais_tocadas;
}t_tocador;

t_musica* criar_musica(char nome[],char genere[],int duracao){
    t_musica* nova = malloc(sizeof(t_musica));
    strcpy(nova->nome,nome);
    strcpy(nova->genero,genero);
    nova->duracao=duracao;
    return nova;
}


void destroy_musica(t_musica* m){
    assert(m!=NULL);
    free(m);
}

t_tocador* criar_tocador(int lim_mais_tocadas){
    t_tocador *t= malloc(sizeof(t_tocador));
    t->lim_mais_tocadas = lim_mais_tocadas;
    t->colecao = criar_lse();
    t->favoritas = criar_lse();
    t->ultimas_tocadas = criar_lse();
    t->mais_tocados = criar_lse();

    return t;

}

void ligar_tocador(t_tocador* tocador){
    char nome[60];
    char genero[40];
    int duracao;

    scanf("%60s %40s %d",nome,genero,&duracao);
    t_musica* nova= criar_musica(nome,genero,duracao);
    inserir_inicio_lse(tocador->colecao,nova);
}
