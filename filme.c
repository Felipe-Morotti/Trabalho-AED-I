#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "filme.h"
#include "ator.h"

Lista * criar_lista ( ){ // Inicializa a lista;
    Lista * li = ( Lista * ) malloc ( sizeof ( Lista ));
    if ( li == NULL ){
        limparTela();
        printf ("\n Erro na alocacao de memoria. \n");
        sleep(2);
        return li;
        
    }
    *li = NULL;
    return li;
}

int adicionar_filme_ordenado_nome ( Lista * li , Filme filme ){ // Insere o filme, e os ordena por meio do título;
    if ( li == NULL ){
        limparTela();
        printf ("\n Ponteiro invalido. \n"); // Primeiras checagens;
        sleep(2);
        return 0;
        
    }
    NoFilme * novo = ( NoFilme * ) malloc ( sizeof ( NoFilme )); // criação de um novo filme;
    if ( novo == NULL ){
        limparTela();
        printf ("\n Erro na alocacao de memoria, nao pode ser inserido. \n");
        sleep(2);
        return 0;
        
    }
    novo -> filme = filme;
    novo -> Atores = NULL;
    
    if ( *li == NULL ){ // Caso a lista for vazia, novo se torna o primeiro elemento;
    
        (*li) = novo;
        novo -> prox = NULL;
        novo -> ant = NULL; 
        return 1;
    }
    
    NoFilme * atual = *li;
    NoFilme * aux = NULL;
    
    while ( atual != NULL && strcasecmp ( novo -> filme.titulo, atual -> filme.titulo ) > 0 ){ // Busca até encontrar o elemento maior na ordem alfabética do que o título do filme;
        aux = atual;
        atual = atual -> prox; 
    }
    
    if ( atual == *li ){ // primeiro elemento é maior alfabeticamente;
        
        novo -> prox = *li;
        (*li)-> ant = novo;
        *li = novo; 
        return 1;
    }
    
    if ( atual == NULL ){ // Não encontrou-se elemento maiores alfabeticamente do que o título, portanto insere-se no fim;
        
        aux -> prox = novo;
        novo -> ant = aux;
        novo -> prox = NULL;
        return 1;
    }
    
    atual -> ant -> prox = novo; // Caso o elemento esteja entre dois elementos, no meio da lista;
    novo -> ant = atual -> ant;
    novo -> prox = atual; 
    atual -> ant = novo;
    
    return 1;
    
}

int remover_filme_nome ( Lista *li , char * filme ){ // Remove o filme atráves de seu título;
    if ( li == NULL || (*li) == NULL ){
        limparTela();
        printf ("\n Ponteiro invalido ou lista vazia. \n");
        sleep(2);
        return 0;
        
    }
    
    NoFilme * atual = *li; 
    
    while ( atual != NULL && strcasecmp ( atual -> filme.titulo , filme ) != 0 ){ // Busca até encontrar o filme;
        atual = atual -> prox;
    }
    
    if ( atual == NULL ){ // Percorreu toda a lista e não achou o elemento;
        limparTela();
        printf ("\n Filme nao encontrado. \n"); 
        sleep(2);
        return 0;
        
    }
    
    NoAtor *aux = atual->Atores;
    
    while (aux != NULL) { // Primeiramente libera a memória referente aos atores;
        
        NoAtor *temp = aux;
        aux = aux->prox;
        free(temp);
     
    }
    
    if ( atual == (*li) ){ // Caso o elemento a ser retirado for o primeiro da lista;
        *li = atual -> prox;
        if (*li != NULL) { 
            (*li)->ant = NULL; 
        }
        free ( atual );
        return 1;
    }
    
    if ( atual -> prox == NULL ){ // Caso o elemento a ser retirado for o último da lista;
        
        atual -> ant -> prox = NULL;
        free ( atual );
        return 1;
        
    }
    
    atual -> ant -> prox = atual -> prox; // Caso o elemento a ser retirado estiver no centro da lista;
    atual -> prox -> ant = atual -> ant; 
    free (atual);

    return 1;
}

void imprimir_lista_filmes ( Lista *li ){ // Imprime todos os filmes com seus atores;
    if ( li == NULL || *li == NULL ){ // Não é possível realizar a impressão da lista;
        limparTela();
        printf ("\n Ponteiro invalido ou lista vazia. \n");
        sleep(2);
        return;
        
    }
    
    NoFilme * atual = *li;
    NoAtor * aux; 
    
    while ( atual != NULL ){ // A cada filme imprime suas informações básicas e seu elenco;
        
        printf ("\n------------------------------------- \n");
        printf (">>> Filme        : %s \n", atual -> filme.titulo );
        printf (">>> Duracao      : %d \n", atual -> filme.duracao );
        printf (">>> Diretor      : %s \n", atual -> filme.diretor );
        printf (">>> Nota Pessoal : %d \n", atual -> filme.nota_pessoal);
        printf (">>> Descricao    : %s \n", atual -> filme.descricao );
        printf ("\n");
        printf ("\t Elenco do filme %s \n", atual -> filme.titulo );
        
        aux = atual -> Atores;
      
            if ( atual -> Atores == NULL ){
                printf ("\n Elenco nao adicionado. \n");
            } else {
                while ( aux != NULL ) {
                    printf (">>> Nome: %s , >>> Papel: %s \n", aux -> ator.nome , aux -> ator.papel );
                    aux = aux -> prox;
                }   
        }
        atual = atual -> prox;
    }
}
void destruir_lista ( Lista *li ){ // Realiza a liberação de memória da lista;
    
    if ( li == NULL ){ 
        return;
    }
    if ( *li == NULL ){
        free (li);
        return;
    }
    
    NoFilme * atual = *li;
    NoFilme * aux2;
    NoAtor * aux;
    NoAtor * aux1;
    
    while ( atual != NULL ){ // Percorre a lista liberando os Atores, e os filmes;
        
        aux = atual -> Atores;
        
            while ( aux != NULL ){
                aux1 = aux -> prox;
                free ( aux );
                aux = aux1;
        }
        
        aux2 = atual -> prox;
        free ( atual );
        atual = aux2;
        
    }
    
    free ( li ); // Libera a alocacao de memória do ponteiro duplo;
    
}

int quantidade_filme ( Lista * li ){ // função que retorna a quantidade de filmes presentes na lista;
    if ( li == NULL || *li == NULL ){
        return 0;
    }
    
    NoFilme * atual = *li;
    int i = 0;
    
    while ( atual != NULL ){
        i++;
        atual = atual -> prox;
    }
    
    return i;
    
}

void filmes_por_diretor ( Lista *li , char * diretor ){ // Função que retorna todos os filmes realizados por dado diretor;
    if ( li == NULL || *li == NULL ){
        limparTela();
        printf ("\n Ponteiro invalido ou lista vazia. \n");
        sleep(2);
        return;
        
    }
    
    NoFilme * atual = *li;
    int achou = 0;
    
    printf ("\n Filmes dirigidos por %s: \n", diretor );
    
    while ( atual != NULL ){ // Percorre a lista achando aqueles que o diretor é igual ao diretor solicitado;
        if ( strcasecmp ( atual -> filme.diretor , diretor ) == 0 ){ 
            printf (">>> %s \n", atual -> filme.titulo );
            achou = 1;
        }
        atual = atual -> prox;
    }
    
    if ( achou == 0 ){ // Caso não se achou um filme;
        limparTela();
        printf ("\n Nao ha filmes com o diretor solicitado. \n");
        sleep(2);

    }
    
}

void modificar_filme ( Lista *li , char * titulo_atual , Filme filme ){ // Modifica toda a estrutura de um filme, para possíveis correções;
    if ( li == NULL || *li == NULL ){
        limparTela();
        printf ("\n Ponteiro invalido ou lista vazia. \n");
        sleep(2);
        return;
        
    }
    
    NoFilme * atual = *li;
    
    while ( atual != NULL ){ // Busca pelo exato título atual para modificado;
        if ( strcmp ( titulo_atual , atual -> filme.titulo ) == 0 ){
            break;
        }
        atual = atual -> prox;
    }
    
    if ( atual == NULL ){
        limparTela();
        printf ("\n Filme nao encontrado na lista \n");
        sleep(2);
        return;
        
    }
    
    if ( filme.duracao >= 0 ){  // Verifica se os dados não são nulos ou inválidos e os modifica;
        atual -> filme.duracao = filme.duracao;
    }
    
    if ( strlen ( filme.diretor ) > 0 ){
        strcpy ( atual -> filme.diretor , filme.diretor );
    }
    
    if ( strlen ( filme.titulo ) > 0 ){
        strcpy ( atual -> filme.titulo , filme.titulo );
    }
    if ( strlen ( filme.descricao ) > 0 ){
        strcpy ( atual -> filme.descricao , filme.descricao );
    }
    
    if ( filme.nota_pessoal >= 0 ){
        atual -> filme.nota_pessoal = filme.nota_pessoal;
    }
    
    limparTela();
    printf ("\n Filme modificado com sucesso!!\n");
    sleep(2);
    
}

void filmes_nota_superior ( Lista *li , int limite ){ // Função que dada um nota, busca filmes com nota superior à ela;
    if ( li == NULL || *li == NULL ){
        limparTela();
        printf ("\n Ponteiro invalido ou lista vazia. \n");
        sleep(2);
        return;
        
    }
    
    NoFilme * atual = *li;
    int achou = 0;
    
    while ( atual != NULL ){
        if ( atual -> filme.nota_pessoal > limite ){ // Realiza a busca por filmes com nota pessoa superior;
            printf (">>> %s (Nota: %d) \n", atual -> filme.titulo, atual ->filme.nota_pessoal );
            achou = 1;
        }
        atual = atual -> prox;
    }
    
    if ( achou == 0 ){
        limparTela();
        printf ("\n Nao ha filmes com Nota superior a %d \n", limite );
       
    }
}

void sortear_filme ( Lista *li ){ // Sorteia algum filme;
    if ( li == NULL || *li == NULL ){
        limparTela();
        printf ("\n Ponteiro invalido ou lista vazia. \n");
        sleep(2);
        return;
        
    }
    
    int q = rand () % 100;
    int k = q % quantidade_filme ( li ); // Sorteia um número K e pega seu módulo pela quantidade de filmes;
    NoFilme * atual = *li;
    
    while ( atual -> prox != NULL ){ // Percorre a lista até o fim;
        atual = atual -> prox;
    }
    
    for ( int i = 0 ; i < k ; i ++ ){ // Retorna K posições por meio do ponteiro anterior;
        atual = atual -> ant;
    }
     
    NoAtor * aux;
    
    printf ("\n------------------------------------- \n"); // Imprime o filme e suas informações básicas;
    printf (">>> Filme        : %s \n", atual -> filme.titulo );
    printf (">>> Duracao      : %d \n", atual -> filme.duracao );
    printf (">>> Diretor      : %s \n", atual -> filme.diretor );
    printf (">>> Nota Pessoal : %d \n", atual -> filme.nota_pessoal);
    printf (">>> Descricao    : %s \n", atual -> filme.descricao );
    printf ("\n------------------------------------- \n\n");
        
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
