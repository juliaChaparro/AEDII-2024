#include "lse_neutra.h"
#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"


typedef struct musica{
    char nome[60];
    char genero[40];
    int duracao;
    int favorita;
    int nro_reproducao;
}t_musica;

t_musica* criar_musica(char nome[], char genero[], int duracao, int favorita, int nro_reproducao){
    t_musica* nova = malloc(sizeof(t_musica));
    strcpy(nova->nome, nome);
    strcpy(nova->genero, genero);
    nova->duracao = duracao;
    nova->favorita = favorita;
    nova->nro_reproducao = nro_reproducao;

    return nova;
}

void imprimir_musica(t_musica* m){
    int min = m->duracao/60;
    int seg = m->duracao%60;

    printf("%s(%s) %02d:%02d\n", m->nome, m->genero, min, seg);
}

int comparar_musica(t_musica* m1, t_musica* m2){
    return strcmp(m1->nome, m2->nome);
}

int comparar_musica_repr(t_musica* m1, t_musica* m2){
    return (m1->nro_reproducao - m2->nro_reproducao);
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
    t->colecao = criar_lse( imprimir_musica, comparar_musica );
    t->favoritas = criar_lse( imprimir_musica, comparar_musica );
    t->ultimas_tocadas = criar_lse( imprimir_musica, NULL);
    t->mais_tocadas = criar_lse( imprimir_musica, comparar_musica_repr );

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
    int favorito;
    int nro_reproducao;

    for(int i=1;i<=3;i++){
        scanf("%[^;]s",nome);
        scanf("%s ",separador);
        scanf("%[^;]s", genero);
        scanf("%s ",separador);
        scanf("%d", &duracao);
        scanf("%d", &favorito);
        scanf("%d", &nro_reproducao);

        t_musica* nova = criar_musica(nome, genero, duracao, favorito, nro_reproducao);
        inserir_conteudo_lse(tocador->colecao, nova);
        if (nova->favorita){
            inserir_inicio_lse(tocador->favoritas, nova);
        }
        inserir_conteudo_lse(tocador->mais_tocadas, nova);

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