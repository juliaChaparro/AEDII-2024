
typedef void (*t_imprimir_lse)(void*);

typedef struct lse t_lse;

t_lse* cria_lse(t_imprimir_lse impressoara);

void destroy_lse(t_lse* lse);

void inserir_inicio_lse(t_lse* lse, void* carga);

void inserir_final_lse(t_lse* lse,void* carga);

void inserir_conteudo_lse(t_lse* lse, void* carga);

void* acessar_conteudo_lse(t_lse* lse,void* chave);

void* remover_conteudo_lse(t_lse*lse,int chave);

void* remover_inicio_lse(t_lse* lse);

void* remover_final_lse(t_lse* lse);

void* acessar_lse(t_lse* lse,int pos);

void imprimir_lse(t_lse* lse);

