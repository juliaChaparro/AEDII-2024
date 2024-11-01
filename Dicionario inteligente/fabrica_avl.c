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
    t_lse* media;
}t_fabrica;


t_sensores* criar_sensores(int Pump_ID, int Class_ID, double Temperature, double Vibration, double Pressure, double Flow_Rate, double RPM, double Operational_Hours, int Maintenance_Flag){
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

void add( t_fabrica* fabi,int Pump_ID, int Class_ID, double Temperature, double Vibration, double Pressure, double Flow_Rate, double RPM, double Operational_Hours, int Maintenance_Flag){
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

void imprimir_sensores(t_sensores* senso){
    printf("Pump_ID: %d\n Class_ID: %d\n Temperature: %.4f\n Vibration: %.4f\n Pressure: %.4f\n Flow_Rate: %.4f\n RPM: %.4f\n Operational_Hours: %.4f\n Maintenance_Flag: %.4f\n",senso->Pump_ID, senso->Class_ID,senso->Temperature,senso->Vibration,senso->Pressure,senso->Flow_Rate,senso->RPM, senso->Operational_Hours,senso->Maintenance_Flag);
}

int comparar_sensores(t_sensores *s1, t_sensores *s2){
    if(s1->Pump_ID == s2->Pump_ID){
        return 0;
    }
    else if(s1->Class_ID == s2->Class_ID){
        return 0;
    }
    else if(s1-> Temperature== s2->Temperature){
        return 0;
    }
    else if(s1->Vibration == s2->Vibration){
        return 0;
    }
    else if(s1->Pressure == s2->Pressure){
        return 0;
    }
    else if(s1->Flow_Rate == s2->Flow_Rate){
        return 0;
    }
    else if(s1->RPM == s2->RPM){
        return 0;
    }
    else if(s1->Operational_Hours == s2->Operational_Hours){
        return 0;
    }
    else if(s1->Maintenance_Flag == s2->Maintenance_Flag){
        return 0;
    }
    else{
        return 1;
    }

}

t_fabrica* criar_fabrica(){
    t_fabrica *f = malloc(sizeof(t_fabrica));

    f->avl = criar_avl(imprimir_sensores,comparar_sensores);
    f->lse = criar_lse(imprimir_sensores, comparar_sensores);
    f->media= criar_avl(imprimir_avl,comparar_sensores);
    return f;

}

t_fabrica* abrir_fabrica(char nome_entrada[], char nome_saida[]){
    t_fabrica *fabi;

    fabi=criar_fabrica();

    char comando[50];
    int Pump_ID;
    int Class_ID;
    double Temperature;
    double Vibration;
    double Pressure;
    double Flow_Rate;
    double RPM;
    double Operational_Hours;
    int Maintenance_Flag;

    while (scanf(" %49[^ ]", comando) == 1){
        if(strcmp(comando, "ADD") == 0){
            scanf("[^ ]%d%*c [^ ]%d%*c [^ ]%f%*c [^ ]%f%*c [^ ]%f%*c [^ ]%f%*c [^ ]%f%*c [^ ]%f%*c [^ ]%d%*c", Pump_ID,Class_ID,Temperature,Vibration,Pressure,Flow_Rate,RPM,Operational_Hours,Maintenance_Flag);
            add(fabi,Pump_ID,Class_ID,Temperature,Vibration,Pressure,Flow_Rate,RPM,Operational_Hours,Maintenance_Flag);
        }
        else if (strcmp(comando, "SEARCH") == 0){
            scanf(" %d", Pump_ID);
            search(fabi,Pump_ID);
        }
        else if (strcmp(comando, "REMOVE") == 0){
            scanf(" %d", Pump_ID);
            remover(fabi,Pump_ID);
        }
        else if (strcmp(comando, "REPORT MEAN") == 0){
            scanf(" %d", Pump_ID);
            report_mean(fabi,Pump_ID);
        }
        else if (strcmp(comando, "REPORT MIN") == 0){
            scanf(" %d", Pump_ID);
            //report_min(fabi,Pump_ID); tenho que fazer essas funçoes 
        }
        else if (strcmp(comando, "REPORT MAX") == 0){
            scanf(" %d", Pump_ID);
            //report_max(fabi,Pump_ID); tenho que fazer essas funçoes 
        }
    }
}