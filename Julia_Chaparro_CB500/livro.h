typedef struct livro{
    char codigo[50];
    char n_livro[80];
    char n_autor[80];
    int ano;
} t_livro;

int comparar_livros(t_livro *l1, t_livro *l2);
t_livro *criar_livro(char codigo[], char n_livro[], char n_autor[], int ano);
void imprimir_livro(t_livro *l);