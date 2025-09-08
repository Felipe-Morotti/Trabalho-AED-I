#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "filme.h"
#include "ator.h"


int adicionar_ator ( Lista *li , char * filme , Ator ator ){  // Adiciona um ator à determinado filme;
    
    if ( li == NULL || *li == NULL ){
        limparTela();
        printf ("\n Ponteiro invalido ou lista vazia. \n");
        sleep(2);
        return 0;
        
    }
    
    NoFilme * atual = *li;
    
    while ( atual != NULL && strcasecmp ( atual -> filme.titulo , filme ) != 0 ){ // Compara até achar o filme com nome dado;
        atual = atual -> prox;
    }
    
    if ( atual == NULL ){ // Caso o filme não for encontrado;
        limparTela();
        printf ("\n Filme nao encontrado. \n");
        sleep(2);
        return 0;
        
    }
    
    NoAtor * novo = ( NoAtor * ) malloc (sizeof ( NoAtor )); // Aloca - se memória para inserir os dados e encadea-lo;
    
    if ( novo == NULL ){
        limparTela();
        printf ("\n Erro na alocacao de memoria. \n");
        sleep(2);
        return 0;
        
    }
    
    novo -> ator = ator; 
    
    if ( atual -> Atores == NULL ){ // Caso ainda não houver atores, realiza a sua inserção diretamente pelo ponteiro de "atual -> Atores";
        atual -> Atores = novo;
        novo -> prox = NULL;
        novo -> ant = NULL;
        return 1;
        
    }
    
    novo -> prox = atual -> Atores; // Realiza a inserção sempre na cabeça da lista;
    atual -> Atores -> ant = novo;
    atual -> Atores = novo;
    return 1;
    
}

void filmes_por_ator ( Lista *li , char * nome ){ // Filmes dos quais dado ator participa;
    if ( li == NULL || *li == NULL ){
        limparTela();
        printf ("\n Ponteiro invalido ou lista vazia. \n");
        sleep(2);
        return;
        
    }
    
    NoFilme * atual = *li;
    NoAtor* aux;
    int achou = 0;
    
    printf ("\n Filmes dos quais o ator(a) %s participa : \n", nome );
    
    while ( atual != NULL ){ // Realiza a busca pelo nome do ator em todos os filmes, caso encontrado imprime o filme do qual participa;
        aux = atual -> Atores;
            while ( aux != NULL ){
                if ( strcasecmp ( aux -> ator.nome , nome ) == 0 ){
                    printf (">>> %s \n", atual -> filme.titulo );
                    achou = 1;
                    break;
                }
            aux = aux -> prox;
            }
        atual = atual -> prox;
    }
    if ( achou == 0 ) { // Caso o Ator não for encontrado;
        limparTela();
        printf ("\n Não ha filmes, presentes na lista, que o ator participe. \n");
        
    }
    
}

int remover_ator ( Lista *li , char * filme , char * nome ){ // Realizar a remoção do Ator, através do título do filme que participa e seu nome;
    if ( li == NULL || *li == NULL ){
        limparTela();
        printf ("\n Ponteiro invalido ou lista vazia. \n");
        sleep(2);
        
        return 0;
    }
    
    NoFilme *atual = *li;
    
    while ( atual != NULL && strcasecmp ( atual -> filme.titulo , filme ) != 0 ){ // busca pelo filme;
        atual = atual -> prox;
    }
    
    if ( atual == NULL ){ // Caso o filme não for encontrado;
        limparTela();
        printf ("\n Filme nao encontrado \n");
        sleep(2);
        return 0;
        
    }
    
    NoAtor * aux = atual -> Atores;
    
    while ( aux != NULL && strcasecmp ( aux -> ator.nome , nome ) != 0 ){ // busca pelo seu nome no filme;
        aux = aux -> prox;
    }
    
    if ( aux == NULL ){ // Caso o seu nome não for encontrado no filme solicitado;
        limparTela();
        printf ("\n Ator nao encontrado no filme \n");
        sleep(2);
        return 0;
        
    }
    
    if ( aux == atual -> Atores ){ // Caso o Ator for o primeiro da lista;
        atual -> Atores = atual -> Atores -> prox;
        free ( aux );
            if ( atual -> Atores != NULL ){
                atual -> Atores -> ant = NULL;
            }
        
        return 1;
    }
    
    if ( aux -> prox == NULL ){ // Caso o Ator for o último da lista;
        aux -> ant -> prox = NULL;
        free ( aux );
        return 1;
        
    }
    
    aux -> ant -> prox = aux -> prox; // Realiza a remoção caso o Ator estiver no meio da lista;
    aux -> prox -> ant = aux -> ant; 
    free ( aux );
    return 1;

}

void modificar_nome_ator ( Lista *li , char * nome_atual , char * nome_novo ){ // Função responsável por modificar o nome do Ator em toda a lista;
    if ( li == NULL || *li == NULL ){
        limparTela();
        printf ("\n Ponteiro invalido ou lista vazia. \n");
        sleep(2);
        return;
        
    }
    
    NoFilme * atual = *li;
    NoAtor * aux;
    int achou = 0;
    
    while ( atual != NULL ){ // Percorre toda a lista , a cada vez que encontrar o nome do Ator modifica-o, pelo nome corrigido;
        aux = atual -> Atores;
        while ( aux != NULL ){
            if ( strcasecmp ( aux -> ator.nome , nome_atual ) == 0){
                 strcpy ( aux -> ator.nome , nome_novo );
                 achou = 1;
            }
            aux = aux -> prox;
        }
        atual = atual -> prox;
    }
    
    if ( achou == 0 ){ // Caso o Ator não ter sido encontrado na lista;
        limparTela();
        printf ("\n Ator não encontrado para realizar a alteracao \n");
        sleep(2);
        
    } else {
        limparTela();
        printf ("\n Nome alterado com sucesso \n");
        sleep(2);
    
    }
}

void carregar_atores_arquivo(Lista* li, const char* nomeArquivo, char* filme) { // Função responsável por carregar o elenco de dado filme por meio de um arquivo;
    Ator ator;
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        limparTela();
        printf("\n Erro ao abrir o arquivo.\n");
        sleep(2);
        return;
    }

    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';
        
        char* token = strtok(linha, ">>>");
        if (token != NULL) {
            strncpy(ator.nome, token, sizeof(ator.nome) - 1);
            ator.nome[sizeof(ator.nome) - 1] = '\0'; 
            trim(ator.nome);
        } else {

            continue; 
        }

        token = strtok(NULL, ">>>");
        if (token != NULL) {
            strncpy(ator.papel, token, sizeof(ator.papel) - 1);
            ator.papel[sizeof(ator.papel) - 1] = '\0'; 
            trim(ator.papel);
        } else {
            
            continue; 
        }

        adicionar_ator(li, filme, ator);
    }
    
    limparTela();
    printf("\n Elenco adicionado com sucesso \n");
    sleep(2);
    
    fclose(arquivo);
}

void trim(char *str) { // função auxiliar para realizar a "poda" da palavra;
    char *start, *end;

    start = str;
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }

    if (*start == 0) {
        *str = '\0';
        return;
    }

    end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }

    *(end + 1) = '\0';

    if (start != str) {
        memmove(str, start, end - start + 2);
    }
}