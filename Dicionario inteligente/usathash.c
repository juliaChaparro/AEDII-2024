//#include "../../../Modulo01/src/202402/musica.h"
#include "musica.h"
#include "thash.h"
#include "string.h"
#include "stdio.h"

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



// caso de uso da hashing
int main(){
    t_hash* sumsung = criar_hash(0.7);
    
    char cmd[15];
    scanf("%s", cmd);
    while(strcmp(cmd,"FINISH") != 0){
        if (strcmp(cmd,"ADD")==0){

            t_musica* info = ler_musica();
            int chave = gerar_id_musica(info);
            inserir_hash(sumsung, chave, info);
        }else if(strcmp(cmd, "PLAY") == 0){
            //play_tocador(sumsung);
        }else if(strcmp(cmd, "PAUSE") == 0){
            //pause_tocador(sumsung);
        }else if(strcmp(cmd, "RESUME") == 0){
            //resume_tocador(sumsung);
        }else if(strcmp(cmd, "STOP") == 0){
            //stop_tocador(sumsung);
        }else if(strcmp(cmd, "END") == 0){
            //end_tocador(sumsung);
        }
        scanf("%s", cmd);
    }
    imprimir_hash(sumsung);

}