typedef struct hash t_hash;

t_hash* criar_hash(double fc);

int funcao_hashing(t_hash* t, int chave);

void inserir_hash(t_hash* t, int chave, void* carga);

void* buscar_hash(t_hash* t, int chave);

void* remover_hash(t_hash* t, int chave);

void rehashing(t_hash *atual);

void imprimir_hash(t_hash* t);

int get_num_colisoes_hash(t_hash* t);

int get_num_comparacoes_hash(t_hash* t);


