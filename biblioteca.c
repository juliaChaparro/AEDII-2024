#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "lse_neutra.h"
#include "string.h"


typedef struct biblioteca{
    t_lse* armazem;


}t_biblioteca;


typedef struct livro{
    char codigo[50];
    char n_livro[80];
    char n_autor[80];
    int ano;
}t_livro;

void imprimir_livro(t_livro* l){
    printf(" Codigo: %s\n Nome do Livro: %s\n Nome do autor: %s\n Ano de publicacao:%d\n", l->codigo,l->n_livro,l->n_autor,l->ano);
}

//provisorio mudar dps 
void comparar_livros(t_livro* l1,t_livro* l2){
    return strcmp(l1->codigo,l2->codigo);
}


t_livro* criar_livro(char codigo[], char n_livro[],char n_autor[],int ano){
    t_livro* livro = malloc(sizeof(t_livro));

    strcpy(livro->codigo,codigo);
    strcpy(livro->n_livro,n_livro);
    strcpy(livro->n_autor,n_autor);
    livro->ano = ano;
    return livro;

}



t_biblioteca* criar_biblioteca(){
    t_biblioteca *b = malloc(sizeof(t_biblioteca));
    b->armazem = criar_lse(imprimir_livro,comparar_livros);
    return b;
}



t_biblioteca* abrir_biblioteca(char nome_arq[]){
    t_biblioteca* bib;

    bib = criar_biblioteca();

    t_livro* liv;
    FILE* arq=fopen(nome_arq,"r");
    char comando[50];
    char codigo[50];
    char n_livro[80];
    char n_autor[80];
    int ano;
    
    if(arq==NULL){
        printf ("Erro no Arquivo.\n");
    }

    while((fscanf(arq,"%49[^ ]%*c",comando)==1)){
        if (strcmp(comando,"ADD") == 0){
            fscanf(arq,"%49[^;]%*c %79[^;]%*c %79[^;]%*c %d%*c",codigo,n_livro,n_autor,&ano);
            liv = criar_livro(codigo,n_livro,n_autor,ano);
            inserir_conteudo_lse(bib->armazem, liv);
        }

    }

    fclose(arq);
    return bib;
}


int main(int  argc,char* argv[]){
    t_biblioteca* bib;
    bib = abrir_biblioteca(argv[1]);
    imprimir_lse(bib->armazem);



}