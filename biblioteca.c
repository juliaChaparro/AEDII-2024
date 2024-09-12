#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "lse_neutra.h"
#include "string.h"

typedef struct biblioteca
{
    t_lse *armazem;
    t_lse *l_devol;
    t_lse *l_empret;

} t_biblioteca;

typedef struct livro
{
    char codigo[50];
    char n_livro[80];
    char n_autor[80];
    int ano;
} t_livro;

void imprimir_livro(t_livro *l)
{
    printf(" Codigo: %s\n Nome do Livro: %s\n Nome do autor: %s\n Ano de publicacao:%d\n", l->codigo, l->n_livro, l->n_autor, l->ano);
}

// provisorio mudar dps
int comparar_livros(t_livro *l1, t_livro *l2)
{
    if (strcmp(l1->codigo, l2->codigo) == 0)
    {
        return 0;
    }
    else if (strcmp(l1->n_livro, l2->n_livro) == 0)
    {
        return 0;
    }
    else if (strcmp(l1->n_autor, l2->n_autor) == 0)
    {
        return 0;
    }
    else
    {
        return strcmp(l1->codigo, l2->codigo);
    }
}

t_livro *criar_livro(char codigo[], char n_livro[], char n_autor[], int ano)
{
    t_livro *livro = malloc(sizeof(t_livro));

    strcpy(livro->codigo, codigo);
    strcpy(livro->n_livro, n_livro);
    strcpy(livro->n_autor, n_autor);
    livro->ano = ano;
    return livro;
}

t_biblioteca *criar_biblioteca()
{
    t_biblioteca *b = malloc(sizeof(t_biblioteca));
    b->armazem = criar_lse(imprimir_livro, comparar_livros);
    b->l_empret= criar_lse(imprimir_livro, comparar_livros);

    return b;
}

void f_ADD(t_biblioteca *bib, char codigo[], char n_livro[], char n_autor[], int ano)
{
    t_livro *liv = criar_livro(codigo, n_livro, n_autor, ano);
    inserir_conteudo_lse(bib->armazem, liv);
}

void f_SEARCH(t_biblioteca *bib, char randam[]){

    t_livro liv;
    strcpy(liv.codigo, randam);
    strcpy(liv.n_livro, randam);
    strcpy(liv.n_autor, randam);

    t_livro *result = acessar_conteudo_lse(bib->armazem, &liv);
    if (result){
        printf("ACHOOO: %s %s %s %d\n", result->codigo, result->n_livro, result->n_autor, result->ano);
    }else{
        printf("livro nao encontrado\n");
    }
}


void CHECK_OUT(t_biblioteca* bib, char randam[]){
    t_livro liv;
    strcpy(liv.codigo, randam);
    strcpy(liv.n_livro, randam);
    strcpy(liv.n_autor, randam);

    t_livro* resuslt = remover_conteudo_lse(bib->armazem,&liv); 

    if(resuslt){
        inserir_conteudo_lse(bib->l_empret,resuslt);
        printf("livro emprestado\n");
    }else{
        printf("livro nao encontrado");
    }
}

t_biblioteca *abrir_biblioteca(char nome_arq[]){
    t_biblioteca *bib;

    bib = criar_biblioteca();

    t_livro *liv;
    FILE *arq = fopen(nome_arq, "r");
    char comando[50];
    char codigo[50];
    char n_livro[80];
    char n_autor[80];
    int ano;
    char randam[100];
    if (arq == NULL){
        printf("Erro no Arquivo.\n");
    }

    while ((fscanf(arq, "%49[^ ]%*c", comando) == 1))
    {

        if (strcmp(comando, "ADD") == 0){
            fscanf(arq, "%49[^;]%*c %79[^;]%*c %79[^;]%*c %d%*c", codigo, n_livro, n_autor, &ano);
            f_ADD(bib, codigo, n_livro, n_autor, ano);
        }
        else if (strcmp(comando, "SEARCH") == 0){
            fscanf(arq, "%99[^\n]%*c", randam);
            f_SEARCH(bib,randam);
        }else if(strcmp(comando,"CHECK_OUT")==0){
            fscanf(arq, "%99[^\n]%*c", randam);
            CHECK_OUT(bib,randam);
        }
        else if(strcmp(comando,"CHECK_IN")==0){
            fscanf(arq, "%99[^\n]%*c", randam);
            t_livro liv;
            strcpy(liv.codigo, randam);
            strcpy(liv.n_livro, randam);
            strcpy(liv.n_autor, randam);
            t_livro* result = acessar_conteudo_lse(bib->l_empret,&liv);
            if (result){
                remover_conteudo_lse(bib->l_empret,result);
                inserir_conteudo_lse(bib->armazem,result);
                printf("livro devolvido\n");
            }
        }
    }

    fclose(arq);
    return bib;
}

int main(int argc, char *argv[])
{
    t_biblioteca *bib;

    bib = abrir_biblioteca(argv[1]);

    imprimir_lse(bib->armazem);
    imprimir_lse(bib->l_empret);
}