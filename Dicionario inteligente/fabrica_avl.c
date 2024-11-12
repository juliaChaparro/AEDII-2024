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
    int Maintenance_Flag; 

} t_sensores;

typedef struct{

    int Pump_ID;
    t_lse* lse;

}t_bomba;

typedef struct {
    t_avl* avl;
}t_fabrica;

//função permite visualizar rapidamente o identificador da bomba e os itens da lista encadeada que ela contém.
void imprimir_bomba(t_bomba* bom){ 
    printf("Pump_ID: ",bom->Pump_ID);
    imprimir_lse(bom->lse);
}
//compara dois items da bomba 
int comparar_bomba(t_bomba* bomba1,t_bomba* bomba2){
    return bomba1->Pump_ID - bomba2->Pump_ID;
}
//funçao que da para visualisar o identificador do sensor
void imprimir_sensores(t_sensores* senso){
    printf("Class_ID: %d\n Temperature: %.4f\n Vibration: %.4f\n Pressure: %.4f\n Flow_Rate: %.4f\n RPM: %.4f\n Operational_Hours: %.4f\n Maintenance_Flag: %d\n",senso->Class_ID,senso->Temperature,senso->Vibration,senso->Pressure,senso->Flow_Rate,senso->RPM, senso->Operational_Hours,senso->Maintenance_Flag);
}

//funçao de compara os items dos sensores
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

// criar cada elemento da struct sensores
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

//criação de uma nova bomba,
t_bomba* criar_bomba(int ID){
    t_bomba* bom = malloc(sizeof(t_bomba));

    if(bom == NULL){
        return NULL;
    }
    bom->Pump_ID= ID;
    bom->lse = criar_lse(imprimir_sensores,comparar_sensores);
    return bom;
}
// vai adicionar os items na avl 
void add(FILE* arq,t_fabrica* fabi,int Pump_ID, int Class_ID, double Temperature, double Vibration, double Pressure, double Flow_Rate, double RPM, double Operational_Hours, int Maintenance_Flag){
    t_sensores* sensor = criar_sensores(Class_ID,Temperature,Vibration,Pressure,Flow_Rate,RPM,Operational_Hours,Maintenance_Flag);
    t_bomba chave;

    chave.Pump_ID = Pump_ID;

    t_bomba* result = buscar_avl(fabi->avl,&chave);

    if(result){
        inserir_conteudo_lse(result->lse,sensor);
        fprintf(arq,"Novas informações adionadas: %d\n",Pump_ID);
    }else{
        t_bomba* bomba = criar_bomba(Pump_ID);
        inserir_avl(fabi->avl,bomba);
        inserir_conteudo_lse(bomba->lse,sensor);
        fprintf(arq,"Adionada com sucesso: %d\n",Pump_ID);
    }
}
//vai buscar os items na avl
void search(FILE* arq,t_fabrica* fabi, int Pump_ID){
    t_bomba ID;
    t_sensores* senso;
    ID.Pump_ID = Pump_ID;

    t_bomba* result = buscar_avl(fabi->avl,&ID);
    int tam = 0;

    if(result){
        tam = tamanho_lse(result->lse);
        for(int i=1;i<=tam;i++){
            senso= acessar_lse(result->lse,i);
            fprintf(arq,"\nPump_ID: %d\n",Pump_ID);
            fprintf(arq,"Class_ID: %0.4d\nTemperature: %.4f\nVibration: %.4f\nPressure: %.4f\nFlow_Rate: %.4f\nRPM: %.4f\nOperational_Hours: %.4f\nMaintenance_Flag: %d\n",senso->Class_ID,senso->Temperature,senso->Vibration,senso->Pressure,senso->Flow_Rate,senso->RPM, senso->Operational_Hours,senso->Maintenance_Flag);           
        }
        
    }else{
        fprintf(arq, "\nNão foi emcontrado: %d\n",Pump_ID);
    }
}

//vai remover os items na avl
void remover(FILE* arq,t_fabrica* fabi, int chave){
    t_bomba bom;
    bom.Pump_ID = chave;
    t_sensores* senso;

    t_bomba* result = buscar_avl(fabi->avl,&bom);
    if(result){

        fprintf(arq,"\nFoi removido o(s) item abaixo:");
        int tam0 = tamanho_lse(result->lse);
        for(int i=1;i<=tam0;i++){
            senso= acessar_lse(result->lse,i);
            fprintf(arq,"\nPump_ID: %d\n",chave);
            fprintf(arq,"Class_ID: %d\nTemperature: %.4f\nVibration: %.4f\nPressure: %.4f\nFlow_Rate: %.4f\nRPM: %.4f\nOperational_Hours: %.4f\nMaintenance_Flag: %d\n",senso->Class_ID,senso->Temperature,senso->Vibration,senso->Pressure,senso->Flow_Rate,senso->RPM, senso->Operational_Hours,senso->Maintenance_Flag);           
        }

        int tam = tamanho_lse(result->lse); 
        while(tam !=0){   
            remover_inicio_lse(result->lse);
            tam--;
        }
        destroy_lse(result->lse);
        remover_avl(fabi->avl,&bom);
    }else{
        fprintf(arq,"%d ID não  encontrado\n",chave);
    }
}

//vai tirar a media dos items que foi procurado
void report_mean(FILE* arq,t_fabrica* fabi, int chave){
    t_bomba bom;
    t_sensores* senso;
    bom.Pump_ID = chave;

    double somador_pressure = 0;
    double somador_Temperature = 0;
    double somador_Vibration = 0;
    
    t_bomba* result = buscar_avl(fabi->avl,&bom);
    

    if(result){
        int tam = tamanho_lse(result->lse);
        for(int i = 1;i<=tam;i++){
            senso =  acessar_lse(result->lse,i);
            somador_pressure += senso->Pressure;
            somador_Temperature += senso->Temperature;
            somador_Vibration += senso->Vibration;
        }
        
        fprintf(arq,"\nID: %d\n",chave);
        fprintf(arq,"A media da Temperature: %lf\n",somador_Temperature/tam);
        fprintf(arq,"A media da Vibration: %lf\n",somador_Vibration/tam);
        fprintf(arq,"A media da Pressure: %lf\n",somador_pressure/tam);
    }else{
        fprintf(arq, "Media nao encontrada: %d\n",chave);
    }

}

//vai tirar a maioe dos items que foi procurado
void report_max(FILE* arq,t_fabrica* fabi,int chave){
    t_bomba bom;
    bom.Pump_ID = chave;
    t_sensores* senso;
    double maior_pressure;
    double maior_Temperature;
    double maior_Vibration;

    
    t_bomba* result= buscar_avl(fabi->avl,&chave);
    if(result){
        int tam = tamanho_lse(result->lse);
        for(int i=1;i<=tam;i++){
            senso = acessar_lse(result->lse,i);
            if(i == 1){
                maior_pressure = senso->Pressure;
                maior_Temperature=senso->Temperature;
                maior_Vibration =senso->Vibration;
            }
            if (senso->Pressure > maior_pressure){
                maior_pressure = senso->Pressure;
            }
            if(senso->Vibration > maior_Vibration){
                maior_Vibration = senso->Vibration;
            }
            if(senso->Temperature > maior_Temperature){
                maior_Temperature = senso->Temperature;
            }

        }
        fprintf(arq,"\nID: %d\n",chave);
        fprintf(arq,"Maior Temperature: %lf\n",maior_Temperature);
        fprintf(arq,"Maior Vibration: %lf\n",maior_Vibration);
        fprintf(arq,"Maior Pressure: %lf\n",maior_pressure);
    }
    else{
        fprintf(arq,"nao encontrou o ID: %d\n",chave);
    }

}

//vai tirar a menor dos items que foi procurado
void report_min(FILE* arq,t_fabrica* fabi,int chave){
    t_bomba bom;
    bom.Pump_ID = chave;
    t_sensores* senso;
    double menor_pressure;
    double menor_Temperature;
    double menor_Vibration;

    
    t_bomba* result= buscar_avl(fabi->avl,&chave);
    
    if(result){
        int tam = tamanho_lse(result->lse);
        for(int i=1;i<=tam;i++){
            senso = acessar_lse(result->lse,i);
            if(i == 1){
                menor_pressure = senso->Pressure;
                menor_Temperature=senso->Temperature;
                menor_Vibration =senso->Vibration;
            }
                if (senso->Pressure < menor_pressure){
                    menor_pressure = senso->Pressure;
                }
                if(senso->Vibration < menor_Vibration){
                    menor_Vibration = senso->Vibration;
                }
                if(senso->Temperature < menor_Temperature){
                    menor_Temperature = senso->Temperature;
                }

        }

        fprintf(arq,"\nID: %d\n",chave);
        fprintf(arq,"Menor Temperature: %lf\n",menor_Temperature);
        fprintf(arq,"Menor Vibration: %lf\n",menor_Vibration);
        fprintf(arq,"Menor Pressure: %lf\n",menor_pressure);
    }
    else{
        fprintf(arq,"Não encontrou o ID: %d\n",chave);
    }

}
//vai criar uma avl para o funcionamento do codigo
t_fabrica* criar_fabrica(){
    t_fabrica* fabi = malloc(sizeof(t_fabrica));

    fabi->avl = criar_avl(imprimir_bomba,comparar_bomba);

    return fabi;
}

//vai ler os arquvos de saida e entrada e fazer os tratamentos
t_fabrica* abrir_fabrica(char nome_entrada[], char nome_saida[]){
    t_fabrica *fabi;
    fabi=criar_fabrica();

    char comando[50];
    char comando_REPORT[50];
    
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
        
        else if (strcmp(comando, "REPORT") == 0){
            if(fscanf(arq," %49[^ ]", comando_REPORT) == 1){
                if (strcmp(comando_REPORT, "MEAN") == 0){
                    fscanf(arq,"%d%*c", &Pump_ID);
                    report_mean(arq_saida,fabi,Pump_ID);
                }
                
                else if (strcmp(comando_REPORT, "MAX") == 0){
                    fscanf(arq,"%d%*c", &Pump_ID);
                    report_max(arq_saida,fabi,Pump_ID);
                }
                
                else if (strcmp(comando_REPORT, "MIN") == 0){
                    fscanf(arq,"%d%*c", &Pump_ID);
                    report_min(arq_saida,fabi,Pump_ID);
                }
            }
        }

        else if(strcmp(comando,"END")==0){
            // tlz eu faça a funçao end "so tlz"
            fprintf(arq_saida,"END\n");

        }

        else{
            fprintf(arq_saida,"acabou\n");
        }
    }

    fprintf(arq_saida,"\nNumeros de comparaçoes da AVL: %d\n",get_num_comparacoes_avl(fabi->avl));
    fprintf(arq_saida,"\nNumeros de rotações da AVL: %d\n",get_num_rotacoes_avl(fabi->avl));
    
    fclose(arq);
    fclose(arq_saida);
    return fabi;
}
//main
int main(int argc, char *argv[]){
    t_fabrica *fabi;
    fabi = abrir_fabrica(argv[1],argv[2]);
}