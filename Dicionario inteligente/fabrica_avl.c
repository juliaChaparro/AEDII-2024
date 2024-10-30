#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#include "lse_neutra.h"
#include "avl.h"



typedef struct {
    
    char Pump_ID[100];
    char Class_ID[100];
    char Temperature[100];
    char Vibration[100];
    char Pressure[100];
    char Flow_Rate[100];
    char RPM[100];
    char Operational_Hours[100];
    char Maintenance_Flag[100]; 

} t_sensores;


typedef struct {
    t_avl* avl;
}t_fabrica;



t_sensores* criar_sensores(char Pump_ID[], char Class_ID[], char Temperature[], char Vibration[], char Pressure[], char Flow_Rate[], char RPM[], char Operational_Hours[], char Maintenance_Flag[]){
    t_sensores* sensores = malloc(sizeof(t_sensores));

    if(sensores == NULL){
        return NULL;
    }
    strcpy(sensores->Class_ID,Class_ID);
    strcpy(sensores->Flow_Rate,Flow_Rate);
    strcpy(sensores->Maintenance_Flag,Maintenance_Flag);
    strcpy(sensores->Operational_Hours,Operational_Hours);
    strcpy(sensores->RPM, RPM);
    strcpy(sensores->Pump_ID,Pump_ID);
    strcpy(sensores->Vibration,Vibration);
    strcpy(sensores->Temperature,Temperature);
    strcpy(sensores->Pressure,Pressure);

    return sensores;
}


void add( t_fabrica* fabi,char Pump_ID[], char Class_ID[], char Temperature[], char Vibration[], char Pressure[], char Flow_Rate[], char RPM[], char Operational_Hours[], char Maintenance_Flag[]){
    t_sensores* sensor = criar_sensores(Pump_ID,Class_ID,Temperature,Vibration,Pressure,Flow_Rate,RPM,Operational_Hours,Maintenance_Flag);
    inserir_avl(fabi->avl,sensor);

}

void search(t_fabrica* fabi, char chave[]){
    t_sensores sensor;
    strcpy(sensor.Pump_ID,chave);

    t_sensores* result = acessar_conteudo_lse(fabi->avl,&sensor);
    if(result){
        printf("achou\n");
    }
    else{
        printf("nao achou a bomba\n");
    }
}

void remover(t_fabrica* fabi, char chave){
    t_sensores sensor;
    strcpy(sensor.Pump_ID,chave);

    t_sensores* result = acessar_conteudo_lse(fabi->avl,&sensor);
    if(result){
        remover_avl(fabi->avl,&sensor);
        printf("removeu\n");
    }
    else{
        printf("nao achou a bomba\n");
    }

}


