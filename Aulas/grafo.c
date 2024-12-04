#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "fila.h"

typedef struct  grafo
{
    int tam_vertice;
    int tam_aresta;
    void* **matriz;

    /* data */
} t_grafo;

t_grafo* criar_grafo(int nro_vertices){
    t_grafo* g = malloc(sizeof(t_grafo));
    g->tam_vertice = nro_vertices;
    g->tam_aresta = 0;

    g->matriz = malloc(sizeof(void*)*g->tam_vertice);
    for(int i=0;i<g->tam_vertice;i++){
        g->matriz[i] = malloc(sizeof(void*)*g->tam_vertice);

    }
    for(int i=0;i<g->tam_vertice;i++){
        for(int j=0;j<g->tam_vertice;j++){
            g->matriz[i][j] = NULL;
        }
    }
    return g;
}

void adicionar_aresta_grafo(t_grafo *g, int u, int v, void* info){
    assert((u>=0 && u<g->tam_vertice));
    assert((v>=0 && v<g->tam_vertice));

    g->matriz[u][v] = info;

}

int adjs_vertice_grafo(t_grafo *g, int u, int adjs[]){
    int nro_adjs = 0;
    for(int v=0; v<g->tam_vertice; v++ ){
        if( g->matriz[u][v] != NULL ){
            nro_adjs++;
            adjs[nro_adjs-1] = v;
        }
    
    }
    return nro_adjs;
}

int nro_vertice_grafo(t_grafo *G){
    return G->tam_vertice;
}

void imprimir_grafo(t_grafo *G){
    for (int i=0;i<G->tam_vertice;i++){
        for (int j=0;j<G->tam_vertice;j++){
            printf(" (%02d, %02d) %c", i,j,(G->matriz[i][j]?'T':'F'));
        }
        printf("\n");
    }
}

typedef struct info_aresta{
    double peso;
    int tipo; // Cruzamento Avanço Retorno
}t_info_aresta;

t_info_aresta* criar_info_aresta(double peso){
    t_info_aresta* info = malloc(sizeof(t_info_aresta));
    info->peso = peso;
    return info;
}

typedef struct info_vertice
{
    int id;
    int cor; // Branco - Cinza - Preto
    int pi;
    int d;
}t_info_vertice;

#define BRANCO 1
#define CINZA 2
#define PRETO 3

#define NULO -1
#define INFINTY -1

t_info_vertice* criar_info_vertice(int u){
    t_info_vertice* v = malloc(sizeof(t_info_vertice));
    v->cor = BRANCO;
    v->id = u;
    v->pi = NULO; // NULL
    v->d = INFINTY;

    return v;
}

static void __imprimir_menor_caminho(t_info_vertice* v, t_info_vertice* vertices[]){
    
    if (v->pi == NULO){
        printf("%02d", v->id);
        
    }else{
        __imprimir_menor_caminho(vertices[v->pi], vertices);
        printf(", %02d", v->id);
    }
}

void imprimir_grafo_bfs(int src, t_info_vertice* vertices[], int nro_vertices){
    for(int i=0;i<nro_vertices;i++){
        t_info_vertice* v = vertices[i];
        if ((v->cor == PRETO) && (v->id != src)){
            __imprimir_menor_caminho(v,vertices);
            printf("\n");
        }

    }
}

void dfs(t_grafo* g){

}

t_info_vertice* min_extract(t_info_vertice* Q[], int ocupa_q){
    int i_min = 0;
    t_info_vertice* u = Q[i_min];
    for(int i=1;i<ocupa_q;i++){
        t_info_vertice* v = Q[i];
        if ((v->d!=INFINTY) && (v->d < u->d)){
            i_min = i;
        }
    }
    t_info_vertice* aux = Q[i_min];
    Q[i_min] = Q[ocupa_q-1];
    Q[ocupa_q-1] = aux;
    return aux;
}

void relax(t_info_vertice* u, t_info_vertice* v, t_info_aresta* w){
    if ((v->d == INFINTY) || (v->d > (u->d + w->peso))){
        v->pi = u->id;
        v->d = u->d+w->peso;
    } 
}

void dijkstra(t_grafo* g){
    int nro_vertices = g->tam_vertice;

    t_info_vertice* vertices[nro_vertices];
    for(int i=0; i< nro_vertices; i++){
        vertices[i] = criar_info_vertice(i);
    }
    int adjs[nro_vertices];

    int src;
    printf("Vértice Fonte: ");
    scanf("%d", &src);

    t_info_vertice* s = vertices[src];
    s->pi = NULO;
    s->d = 0;

    t_info_vertice* Q[nro_vertices];
    for(int i =0;i<nro_vertices;i++)
        Q[i] = vertices[i];
    int ocupa_q = nro_vertices;
    while(ocupa_q > 0){
        t_info_vertice*u = min_extract(Q, ocupa_q);
        
        int nro_adjs = adjs_vertice_grafo(g,u->id,adjs);
        for (int i=0;i<nro_adjs;i++){
            t_info_vertice* v = vertices[adjs[i]];
            relax(u, v, g->matriz[u->id][v->id]);
        }
        ocupa_q--;
    }
    for(int i=0;i<nro_vertices;i++){
        t_info_vertice* u = vertices[i];
        printf("%d %d\n", u->id, u->d);
    }
    imprimir_grafo_bfs(src,vertices,nro_vertices);
}

void bfs(t_grafo *g){
    int nro_vertices = g->tam_vertice;

    t_info_vertice* vertices[nro_vertices];
    for(int i=0; i< nro_vertices; i++){
        vertices[i] = criar_info_vertice(i);
    }
    int adjs[nro_vertices];

    int src;
    printf("Vértice Fonte: ");
    scanf("%d", &src);

    t_info_vertice* s = vertices[src];
    s->cor = CINZA;
    s->pi = NULO;

    t_fila* Q = criar_fila(0);
    enfileirar_fila(Q, s);

    while(!vazia_fila(Q)){

        s = desenfileirar_fila(Q);

        int nro_adjs = adjs_vertice_grafo(g,s->id,adjs);
        for (int i = 0; i < nro_adjs; i++)
        {
            t_info_vertice* v = vertices[adjs[i]];
            if (v->cor == BRANCO){
                v->cor = CINZA;
                v->pi = s->id;
                enfileirar_fila(Q,v);
            }
        }
        s->cor = PRETO;
    }
    //printf("saiu\n");
    imprimir_grafo_bfs(src, vertices, nro_vertices);

}


int main(){
    int nro_vertices = 5;
    t_grafo *g = criar_grafo(nro_vertices);
    
    adicionar_aresta_grafo(g, 0, 1, criar_info_aresta(10));
    adicionar_aresta_grafo(g, 0, 4, criar_info_aresta(5));
    adicionar_aresta_grafo(g, 1, 2, criar_info_aresta(1));
    adicionar_aresta_grafo(g, 1, 4, criar_info_aresta(2));
    adicionar_aresta_grafo(g, 2, 3, criar_info_aresta(4));
    adicionar_aresta_grafo(g, 3, 0, criar_info_aresta(7));
    adicionar_aresta_grafo(g, 3, 2, criar_info_aresta(6));
    adicionar_aresta_grafo(g, 4, 1, criar_info_aresta(3));
    adicionar_aresta_grafo(g, 4, 2, criar_info_aresta(9));
    adicionar_aresta_grafo(g, 4, 3, criar_info_aresta(2));

    imprimir_grafo(g);

    bfs(g);
    printf("\n");

    dijkstra(g);

    printf("\n");
    
 
    return 0;
}