#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#include "lse_neutra.h"
#include "avl.h"

typedef struct {

    int Class_ID;
    double Temperature;
    double Vibration;
    double Pressure;
    double Flow_Rate;
    double RPM;
    double Operational_Hours;
    double Maintenance_Flag; 

} t_sensores;

typedef struct{

    int Pump_ID;
    t_lse* lse;

}t_bomba;

typedef struct {
    t_avl* avl;
}t_fabrica;


void imprimir_bomba(t_bomba* bom){ 
    printf("Pump_ID: ",bom->Pump_ID);
    imprimir_lse(bom->lse);
}


int comparar_bomba(t_bomba* bomba1,t_bomba* bomba2){
    return bomba1->Pump_ID - bomba2->Pump_ID;
}

void imprimir_sensores(t_sensores* senso){
    printf("Class_ID: %d\n Temperature: %.4f\n Vibration: %.4f\n Pressure: %.4f\n Flow_Rate: %.4f\n RPM: %.4f\n Operational_Hours: %.4f\n Maintenance_Flag: %.4d\n",senso->Class_ID,senso->Temperature,senso->Vibration,senso->Pressure,senso->Flow_Rate,senso->RPM, senso->Operational_Hours,senso->Maintenance_Flag);
}

int comparar_sensores(t_sensores *s1, t_sensores *s2){
    
    if(s1->Class_ID == s2->Class_ID){
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
        if(s1->Maintenance_Flag == s2->Maintenance_Flag){
            return 0;
        }
    }
}

t_sensores* criar_sensores(int Class_ID, double Temperature, double Vibration, double Pressure, double Flow_Rate, double RPM, double Operational_Hours, int Maintenance_Flag){
    t_sensores* sensores = malloc(sizeof(t_sensores));

    if(sensores == NULL){
        return NULL;
    }
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

t_bomba* criar_bomba(int ID){
    t_bomba* bom = malloc(sizeof(t_bomba));

    if(bom == NULL){
        return NULL;
    }
    bom->Pump_ID= ID;
    bom->lse = criar_lse(imprimir_sensores,comparar_sensores);
    return bom;
}

t_bomba* remover_bomba(t_avl* avl){


}

void add(FILE* arq,t_fabrica* fabi,int Pump_ID, int Class_ID, double Temperature, double Vibration, double Pressure, double Flow_Rate, double RPM, double Operational_Hours, int Maintenance_Flag){
    t_sensores* sensor = criar_sensores(Class_ID,Temperature,Vibration,Pressure,Flow_Rate,RPM,Operational_Hours,Maintenance_Flag);
    t_bomba chave;

    chave.Pump_ID = Pump_ID;

    t_bomba* result = buscar_avl(fabi->avl,&chave);

    if(result){
        inserir_conteudo_lse(result->lse,sensor);
        fprintf(arq,"achou a bomba\n");
    }else{
        t_bomba* bomba = criar_bomba(Pump_ID);
        inserir_avl(fabi->avl,bomba);
        inserir_conteudo_lse(bomba->lse,sensor);
        fprintf(arq,"add com sucesso\n");
    }
}

void search(FILE* arq,t_fabrica* fabi, int Pump_ID){
    t_bomba ID;
    ID.Pump_ID = Pump_ID;

    t_bomba* result = buscar_avl(fabi->avl,&ID);
    if(result){
        imprimir_lse(result->lse);
    }else{
        fprintf(arq, "nao foi emcontrado\n");
    }
}

void remover(FILE* arq,t_fabrica* fabi, int chave){
    t_bomba bom;
    bom.Pump_ID = chave;

    t_bomba* result = buscar_avl(fabi->avl,&bom);
    if(result){
        fprintf(arq,"foi removido\n");
        imprimir_lse(result->lse);

        int tam = tamanho_lse(result->lse);
        
        while(tam !=0){   
            remover_inicio_lse(result->lse);
            tam--;
        }
        destroy_lse(result->lse);
        remover_avl(fabi->avl,&bom);
    }else{
        fprintf(arq,"id não  encontrado\n");
    }
}


void report_mean(FILE* arq,t_fabrica* fabi, int chave){
    t_bomba bom;
    t_sensores* senso;
    bom.Pump_ID = chave;

    double somador_pressure = 0;
    double somador_Temperature = 0;
    double somador_Vibration = 0;
    
    t_bomba* result = buscar_avl(fabi->avl,&bom);
    
    int tam = tamanho_lse(result->lse);

    if(result){
        for(int i = 1;i<=tam;i++){
            senso =  acessar_lse(result->lse,i);
            somador_pressure += senso->Pressure;
            somador_Temperature += senso->Temperature;
            somador_Vibration += senso->Vibration;
        }
        fprintf(arq,"A media da Temperature: %lf\n",somador_Temperature/tam);
        fprintf(arq,"A media da Vibration: %lf\n",somador_Vibration/tam);
        fprintf(arq,"A media da Pressure: %lf\n",somador_pressure/tam);
    }else{
        fprintf(arq, "media nao encontrada\n");
    }

}


t_fabrica* criar_fabrica(){
    t_fabrica* fabi = malloc(sizeof(t_fabrica));

    fabi->avl = criar_avl(imprimir_bomba,comparar_bomba);

    return fabi;
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

    FILE* arq_saida = fopen(nome_saida,"w+");

    FILE *arq = fopen(nome_entrada, "r");

    if (arq == NULL){
        printf("Erro no Arquivo.\n");
    }

    while (fscanf(arq," %49[^ ]", comando) == 1){
        if(strcmp(comando, "ADD") == 0){
            fscanf(arq,"%d%*c %d%*c %lf%*c %lf%*c %lf%*c %lf%*c %lf%*c %lf%*c %d%*c\n", &Pump_ID,&Class_ID,&Temperature,&Vibration,&Pressure,&Flow_Rate,&RPM,&Operational_Hours,&Maintenance_Flag);
            add(arq_saida,fabi,Pump_ID,Class_ID,Temperature,Vibration,Pressure,Flow_Rate,RPM,Operational_Hours,Maintenance_Flag);
            
        }
        else if (strcmp(comando, "SEARCH") == 0){
            fscanf(arq,"%d%*c", &Pump_ID);
            search(arq_saida,fabi,Pump_ID);
        }
        
        else if (strcmp(comando, "REMOVE") == 0){
            fscanf(arq,"%d%*c", &Pump_ID);
            remover(arq_saida,fabi,Pump_ID);
        }
        
        else if (strcmp(comando, "REPORT MEAN") == 0){
            fscanf(arq,"%d%*c", &Pump_ID);
            report_mean(arq_saida,fabi,Pump_ID);
        }
        /*
        else if (strcmp(comando, "REPORT MIN") == 0){
            fscanf(arq,"[^ ]%*d", Pump_ID);
            //report_min(fabi,Pump_ID); tenho que fazer essas funçoes 
        }
        else if (strcmp(comando, "REPORT MAX") == 0){
            fscanf(arq,"[^ ]%*d", Pump_ID);
            //report_max(fabi,Pump_ID); tenho que fazer essas funçoes 
        }
        */
        else if(strcmp(comando,"END")==0){
            // tlz eu faça a funçao end "so tlz"
            fprintf(arq_saida,"end\n");

        }

        else{
            fprintf(arq_saida,"acabou\n");
        }
    }
    fclose(arq);
    fclose(arq_saida);
    return fabi;
}

int main(int argc, char *argv[]){
    t_fabrica *fabi;
    fabi = abrir_fabrica(argv[argc - 2],argv[argc - 1]);
}
