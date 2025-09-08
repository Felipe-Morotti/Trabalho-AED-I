#ifndef FILME_H
#define FILME_H

typedef struct {
    int duracao;
    int nota_pessoal;
    char diretor [100];
    char titulo [100];
    char descricao [300];
    int favorito; // 1 = favorito, 0 = não favorito
} Filme;

struct nofilme {
    struct nofilme * ant; // Formação de um estrutura de encadeamento duplo de filmes, com um ponteiro apontando para a estrutura de Atores;
    Filme filme;
    struct nofilme * prox;
    struct noator * Atores;
};

typedef struct nofilme NoFilme;
typedef struct noator NoAtor;
typedef struct nofilme *Lista;

Lista * criar_lista ();
int adicionar_filme_ordenado_nome ( Lista * li , Filme filme );
int remover_filme_nome ( Lista *li , char * filme );
int quantidade_filme ( Lista * li );
void sortear_filme ( Lista *li );
void filmes_nota_superior ( Lista *li , int limite );
void imprimir_lista_filmes ( Lista *li );
void filmes_por_diretor ( Lista *li , char * diretor );
void modificar_filme ( Lista *li , char * titulo_atual , Filme filme );
void destruir_lista ( Lista *li );


void limparTela();

#endif