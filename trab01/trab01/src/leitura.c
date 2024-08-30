#include "stdio.h"

int main(){
    char CMD[30];
    char titulo[100];
    char autor[100];
    char ISDN[50];
    char ano[6];
    char separador[4];

    scanf("%s ", CMD);
    //printf("%s\n", CMD);
    scanf("%[^;]s", ISDN);
    //printf("%s\n", ISDN);
    scanf("%s ",separador);
    scanf("%[^;]s", titulo);
    //printf("%s\n", titulo);
    scanf("%s ",separador);
    scanf("%[^;]s", autor);
    //printf("%s\n", autor);
    scanf("%s ",separador);
    scanf("%s", ano);
    //printf("%s\n", ano);
    printf("%s|%s|%s|%s|%s\n", CMD, ISDN, titulo, autor, ano);

}