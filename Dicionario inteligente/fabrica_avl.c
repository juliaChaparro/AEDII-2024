#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#include "lse_neutra.h"
#include "avl.h"

typedef struct {
    
    int Pump_ID;
    int Class_ID;
    double Temperature;
    double Vibration;
    double Pressure;
    double Flow_Rate;
    double RPM;
    double Operational_Hours;
    double Maintenance_Flag; 

} t_sensores;


typedef struct {
    t_avl* avl;
    t_lse* lse;
    t_lse* media[];
}t_fabrica;


t_sensores* criar_sensores(int Pump_ID, int Class_ID, double Temperature, double Vibration, double Pressure, double Flow_Rate, double RPM, double Operational_Hours, double Maintenance_Flag){
    t_sensores* sensores = malloc(sizeof(t_sensores));

    if(sensores == NULL){
        return NULL;
    }
    sensores->Pump_ID = Pump_ID;
    sensores->Flow_Rate=Flow_Rate;
    sensores->Maintenance_Flag= Maintenance_Flag;
    sensores->Operational_Hours=Operational_Hours;
    sensores->Pressure=Pressure;
    sensores->RPM=RPM;
    sensores->Temperature=Temperature;
    sensores->Vibration=Vibration;
    sensores->Class_ID=Class_ID;

    return sensores;
}


void add( t_fabrica* fabi,int Pump_ID, int Class_ID, double Temperature, double Vibration, double Pressure, double Flow_Rate, double RPM, double Operational_Hours, double Maintenance_Flag){
    t_sensores* sensor = criar_sensores(Pump_ID,Class_ID,Temperature,Vibration,Pressure,Flow_Rate,RPM,Operational_Hours,Maintenance_Flag);
    inserir_avl(fabi->avl,sensor);

}

void search(t_fabrica* fabi, int chave){
   t_sensores sensor;
    sensor.Pump_ID = chave;

    t_sensores* result = acessar_conteudo_lse(fabi->lse,&sensor);
    if(result){
        printf("achou\n");
    }
    else{
        printf("nao achou a bomba\n");
    }
}

void remover(t_fabrica* fabi, int chave){
    t_sensores sensor;
    sensor.Pump_ID = chave;

    t_sensores* result = acessar_conteudo_lse(fabi->lse,&sensor);
    if(result){
        remover_avl(fabi->avl,&sensor);
        printf("removeu\n");
    }
    else{
        printf("nao achou a bomba\n");
    }

}

void report_mean(t_fabrica* fabi, int chave){
    t_sensores sensor;
    sensor.Pump_ID = chave;

    t_sensores* result = acessar_conteudo_lse(fabi->lse,&sensor);
    double *media1 =malloc(sizeof(double));
    
    if(result){
        inserir_conteudo_lse(fabi->media,media1);
        *media1 = (sensor.Temperature + sensor.Vibration + sensor.Pressure)/3;// ver dps 
        printf("A media é: %0.3f",*media1);
    }

}

/*
void report_min(t_fabrica* fabi, int chave) {
    t_sensores sensor;
    sensor.Pump_ID = chave;


    int menor = fabi->media; 

    int* ptr = fabi->media;
    while (ptr != NULL) {
        if (*ptr < menor) {
            menor = *ptr;
        }
        ptr++; 
    }

    printf("O menor valor é: %d\n", menor);
}

# define MAX 100000;

void report_max(t_fabrica* fabi, int chave) {
    t_sensores sensor;
    sensor.Pump_ID = chave;

    int maior = fabi->media[0];  
    for (int i = 1; i < MAX; i++) {
        if (fabi->media[i] > maior) {
            maior = fabi->media[i];
        }
    }
    printf("O maior valor é: %d\n", maior);
}
*/


