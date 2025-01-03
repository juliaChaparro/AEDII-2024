#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "estrutura.h"
#include "string.h"
#include "livro.h"


typedef struct biblioteca{
    t_lse *armazem;
    t_lse *l_empret;

} t_biblioteca;

//Funçao que adiciona na Biblioteca e cria um campo livre
void ADD(FILE* arq,t_biblioteca *bib, char codigo[], char n_livro[], char n_autor[], int ano){
    t_livro *liv = criar_livro(codigo, n_livro, n_autor, ano);
    inserir_conteudo_lse(bib->armazem, liv);
    fprintf(arq,"Livro: %s adicionado com sucesso\n",liv->n_livro);
    
}

//FuÇao de procura pelo autor, nome do livro e codigo do livro
void SEARCH(FILE* arq,t_biblioteca *bib, char randam[]){
    t_livro liv;
    strcpy(liv.codigo, randam);
    strcpy(liv.n_livro, randam);
    strcpy(liv.n_autor, randam);

    t_livro *result = acessar_conteudo_lse(bib->armazem, &liv);
    if (result){
        fprintf(arq,"\nLivro encontrado com sucesso:\nCodigo: %s\nNome do livro: %s\nNome do autor: %s\nAno de publicacao: %d\n", result->codigo, result->n_livro, result->n_autor, result->ano);
    }else{
        fprintf(arq,"\nLivro nao encontrado na biblioteca\n");
    }
}

//Função que percorre o campo armazen e coloca no campo de empréstimos
void CHECK_OUT(FILE* arq,t_biblioteca* bib, char randam[]){
    t_livro liv;
    strcpy(liv.codigo, randam);
    strcpy(liv.n_livro, randam);
    strcpy(liv.n_autor, randam);

    t_livro* resuslt = remover_conteudo_lse(bib->armazem,&liv); 

    if(resuslt){
        inserir_conteudo_lse(bib->l_empret,resuslt);
        fprintf(arq,"\nLivro: %s emprestado\n",resuslt->n_livro);
    }else{
        fprintf(arq,"\nLivro indisponivel na biblioteca\n");
    }
}

//Função que percorre o campo dos livros emprestados, verifica se o livro está no campo e, depois, remove-o e coloca-o novamente no campo de armazenamento.
void CHECK_IN(FILE* arq,t_biblioteca* bib, char randam[]){
    t_livro liv;
    strcpy(liv.codigo, randam);
    strcpy(liv.n_livro, randam);
    strcpy(liv.n_autor, randam);

    t_livro* result = acessar_conteudo_lse(bib->l_empret,&liv);

    if (result){
        inserir_conteudo_lse(bib->armazem,result);
        remover_conteudo_lse(bib->l_empret,result);
        fprintf(arq,"\nLivro: %s devolvido para a biblioteca\n",result->n_livro);
    }else{
        fprintf(arq,"\nLivro nao foi emprestado\n");
    }
}

//Função que vai gerar um campo para cada área
t_biblioteca *criar_biblioteca(){
    t_biblioteca *b = malloc(sizeof(t_biblioteca));
    b->armazem = criar_lse(imprimir_livro, comparar_livros);
    b->l_empret= criar_lse(imprimir_livro, comparar_livros);

    return b;
}
//Função que vai percorrer um arquivo, verificar o comando no arquivo e executá-lo  
t_biblioteca *abrir_biblioteca(char nome_entrada[], char nome_saida[]){
    t_biblioteca *bib;

    bib = criar_biblioteca();
    FILE* arq_saida = fopen(nome_saida,"w+");

    t_livro *liv;
    FILE *arq = fopen(nome_entrada, "r");

    char comando[50];
    char codigo[50];
    char n_livro[80];
    char n_autor[80];
    int ano;
    char randam[100];

    if (arq == NULL){
        printf("Erro no Arquivo.\n");
    }

    while ((fscanf(arq, " %49[^ ]", comando) == 1)){

        if (strcmp(comando, "ADD") == 0){
            fscanf(arq, " %49[^ ]%*c %79[^;]%*c %79[^;]%*c %d%*c", codigo, n_livro, n_autor, &ano);
            ADD(arq_saida,bib, codigo, n_livro, n_autor, ano);
        }
        else if (strcmp(comando, "SEARCH") == 0){
            fscanf(arq, " %99[^;]%*c", randam);
            SEARCH(arq_saida,bib,randam);
        }else if(strcmp(comando,"CHECK_OUT")==0){
            fscanf(arq, " %99[^;]%*c", randam);
            CHECK_OUT(arq_saida,bib,randam);
        }
        else if(strcmp(comando,"CHECK_IN")==0){
            fscanf(arq, " %99[^;]%*c", randam);
            CHECK_IN(arq_saida,bib,randam);
        }else if(strcmp(comando,"END")==0){
            break;
        }else{
            fprintf(arq_saida,"Comando nao encontrado\n");

        }
    }
    fclose(arq);
    fclose(arq_saida);
    return bib;
}
//Função main que pedirá o nome dos arquivos de entrada e saída
int main(int argc, char *argv[]){
    t_biblioteca *bib;
    bib = abrir_biblioteca(argv[1],argv[2]);
}