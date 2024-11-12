#include "stdio.h"
#include "math.h"
#include <stdlib.h>

int pega_digito(int k , int d){
  return k;
}

void counting_sort(int array[], int size, int d) {

  int count[]={0,0,0,0,0,0,0,0,0,0,0};

  // levantamento
  for (int i = 0; i < size; i++) {
    count[ pega_digito(array[i],d)]++;
  }

  // define as posições 
  for (int i = 1; i <= 9; i++) {
    count[i] += count[i - 1];
  }

    int output[size];
  // posiciona os elementos  
  for (int i = size - 1; i >= 0; i--) {
    output[count[ array[i] ] - 1] = array[i];
    count[ array[i] ]--;
  }

  // retorna os elementos ao vetor original
  for (int i = 0; i < size; i++) {
    array[i] = output[i];
  }
}


int* gerador(int tam){
  int* vetor = malloc(sizeof(int)*tam);
  for(int i = 0;i<tam;i++){
    vetor[i]= (int)(random()%6);
  }
  return vetor;
}


int main(int argc, char const *argv[]){
    int tam=100;
    //int vetor[] = {5,2,1,1,3,2,3,4,4,1,1,3,4,5};
    int* vetor  = gerador(tam);
    counting_sort(vetor,tam,1);

    for(int i=0;i<tam;i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
    return 0;
}