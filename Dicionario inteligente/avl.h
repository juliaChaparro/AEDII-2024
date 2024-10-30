typedef int(*t_comparar_avl)(void*, void*);
typedef void(*t_imprimir_avl)(void*);


typedef struct no t_no;
struct no{
    void* info;
    t_no* sae;
    t_no* sad;
    t_no* ancestral;
    int fb;
};

typedef struct avl t_avl;
struct avl {
    t_no* raiz;
    int tamanho;
    t_imprimir_avl impressora;
    t_comparar_avl comparar;
    int num_comparacoes; 
    int num_rotacoes; 
};



t_no* criar_no(t_no* ancestral, void* info);

t_no* criar_no(t_no* ancestral, void* info);

t_avl* criar_avl(t_imprimir_avl impressora, t_comparar_avl comparar);

void* buscar_avl(t_avl* avl, void* chave);

t_no* rotacao_SE(t_no* A, t_no* B, t_avl* avl);

t_no* rotacao_SD(t_no* A, t_no* B, t_avl* avl);

int altura_avl(t_avl* avl);

void inserir_avl(t_avl* avl, void* info);

void podar_avl(t_avl* avl, void* chave);

void remover_avl(t_avl* avl, void* chave);

void imprimir_avl(t_avl* avl);

void destruir_avl(t_avl* avl);

int get_num_comparacoes_avl(t_avl* avl);

int get_num_rotacoes_avl(t_avl* avl);
