#include"stdio.h"
#include "stdlib.h"


int main(int argc,char* argv[]){
    FILE* arq = fopen(argv[1],"r");
    int numero,C=5;
    int ano;
    char cod[100];
    char livro[100];
    char autor[100];
    char comando[100];


    float f;
    char n;

    if(arq==NULL){
        printf ("Erro no Arquivo.\n");
    }
    while (C == 5){
        C = fscanf(arq,"%99[^ ]%*c %99[^;]%*c %99[^;]%*c %99[^;]%*c %d",comando,cod,livro,autor,&ano);
        if(C==5){
            printf("%s\n%s\n%s\n%s\n%d\n",comando,cod,livro,autor,ano);
        }
    }
    
    fclose(arq);
}
