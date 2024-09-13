#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "estrutura.h"
#include "string.h"
#include "livro.h"


//funçao que cai mostra todos os campos do livro
void imprimir_livro(t_livro *l){
    printf(" Codigo: %s\n Nome do Livro: %s\n Nome do autor: %s\n Ano de publicacao:%d\n", l->codigo, l->n_livro, l->n_autor, l->ano);
}

//funcao que  é usada para comparar dois livros com base em diferentes campos e determinar se são iguais.
int comparar_livros(t_livro *l1, t_livro *l2){
    if (strcmp(l1->codigo, l2->codigo) == 0){
        return 0;
    }
    else if (strcmp(l1->n_livro, l2->n_livro) == 0){
        return 0;
    }
    else if (strcmp(l1->n_autor, l2->n_autor) == 0){
        return 0;
    }
    else{
        return strcmp(l1->codigo, l2->codigo);
    }
}

// funcao que vai criar um campo de livro e adicionar dentro dele
t_livro *criar_livro(char codigo[], char n_livro[], char n_autor[], int ano){
    t_livro *livro = malloc(sizeof(t_livro));

    strcpy(livro->codigo, codigo);
    strcpy(livro->n_livro, n_livro);
    strcpy(livro->n_autor, n_autor);
    livro->ano = ano;
    return livro;
}
