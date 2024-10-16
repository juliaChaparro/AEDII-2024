#include "musica.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"

struct musica{
    char nome[60];
    char genero[40];
    int duracao;
    int favorita;
    int nro_reproducao;
};

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

    printf("%s(%s) %02d:%02d %d %d\n", m->nome, m->genero, min, seg, m->favorita, m->nro_reproducao);
}

int comparar_musica(t_musica* m1, t_musica* m2){
    return strcmp(m1->nome, m2->nome);
}

int comparar_musica_repr(t_musica* m1, t_musica* m2){
    //printf("rep1: %d  rep2: %d\n", m1->nro_reproducao, m2->nro_reproducao);
    return (m1->nro_reproducao - m2->nro_reproducao);
}

int gerar_id_musica(t_musica* m ){
    int id = 0;
    for(int i=0;i<strlen(m->nome)&&(i<5);i++){
        id += m->nome[i]*(i+1);
    }

    for(int i=0;i<strlen(m->genero)&&(i<5);i++){
        id += m->genero[i]*(i+1);
    }
    
    return id;
}

void destroy_musica(t_musica* m){
    assert(m!=NULL);
    free(m);
}

t_musica* ler_musica(){
    char nome[60];
    char genero[40];
    int duracao;
    char separador[3];
    int favorita;
    int nro_reproducao;

    scanf("%[^;]s",nome);
    scanf("%s ",separador);
    scanf("%[^;]s", genero);
    scanf("%s ",separador);
    scanf("%d", &duracao);
    scanf("%d", &favorita);
    scanf("%d", &nro_reproducao);

    t_musica* nova = criar_musica(nome, genero, duracao, favorita, nro_reproducao);
    return nova;
}
