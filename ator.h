#ifndef ATOR_H
#define ATOR_H

typedef struct {
    char nome [100];
    char papel [100];
} Ator;

struct noator{
    struct noator *ant; // Estrutura de encadeamento duplo da struct "Ator";
    Ator ator;
    struct noator *prox;
};

int adicionar_ator ( Lista *li , char * filme , Ator ator );
int remover_ator ( Lista *li , char * filme , char * nome );
void filmes_por_ator ( Lista *li , char * nome );
void modificar_nome_ator ( Lista *li , char * nome_atual , char * nome_novo );
void carregar_atores_arquivo(Lista* li, const char* nomeArquivo, char * filme);
void trim(char *str);

#endif