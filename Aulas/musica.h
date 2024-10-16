typedef struct musica t_musica;

t_musica* criar_musica(char nome[], char genero[], int duracao, int favorita, int nro_reproducao);
void imprimir_musica(t_musica* m);
int comparar_musica(t_musica* m1, t_musica* m2);
int comparar_musica_repr(t_musica* m1, t_musica* m2);
void destroy_musica(t_musica* m);
int gerar_id_musica(t_musica* m);
t_musica* ler_musica();