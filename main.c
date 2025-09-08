#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include "filme.h"
#include "ator.h"

int main() {
    Lista *lista = criar_lista();
    
    srand(time(NULL));
    
    Filme filme; // Varíaveis para armazenar informações que serão inseridas na lista ;
    Ator ator;
    char titulo [100];
    char nome [100];
    char nome_1 [100];
    int opcao, sub_opcao, j, nota;
    bool run = true;
    
    while (run){
        limparTela();
        printf ("\n------ Menu Principal ------\n\n");
        printf ("Quantidade de filmes no catalogo: %d\n\n", quantidade_filme (lista) );
        printf ("1 - Filmes e Elencos;\n"); //Operações sobre a lista
        printf ("2 - Alteracoes;\n"); //Modificação de nós
        printf ("3 - Pesquisa;\n"); //Funções extras
        printf ("4 - Lista de Filmes;\n"); //Imprimir a lista
        printf ("5 - Sair;\n\n"); //Sair do programa
        printf ("Opcao: ");
        scanf ("%d", & opcao );
        getchar();
        
            switch ( opcao ) {
                
                case 1 :
                    limparTela();
                    printf ("\n--- Filmes e Elencos ---\n\n");
                    printf ("1 - Adicionar filme;\n"); //Deseja adicionar um filme
                    printf ("2 - Remover filme;\n"); //Deseja remover um filme;
                    printf ("3 - Adicionar ator a um filme;\n"); //Deseja adicionar um ator a um filme
                    printf ("4 - Remover ator de um filme;\n"); //Deseja remover um Ator de um filme
                    printf ("5 - Carregar elenco;\n"); //Carregar arquivo contendo elenco
                    printf ("6 - Voltar;\n\n");
                    printf ("Opcao: ");
                    scanf ("%d", & sub_opcao );
                    getchar();
                        
                        switch ( sub_opcao ){
                            
                            case 1 :
                                limparTela();
                                printf ("\nTitulo do filme:\n"); //Qual o nome do filme
                                scanf (" %99[^\n]", filme.titulo);
                                printf ("\nDuracao do filme (em minutos): "); //Qual a duração do filme (em minutos)
                                scanf ("%d", &filme.duracao);
                                getchar();
                                printf ("\nDiretor(a) do filme:\n"); //Qual o(a) diretor(a) do filme
                                scanf (" %99[^\n]", filme.diretor);
                                getchar();
                                printf ("\nNota pessoal para o filme (0 a 10): "); //Qual a sua nota para o filme (0 a 10)
                                scanf ("%d", &filme.nota_pessoal);

                                while (filme.nota_pessoal > 10 || filme.nota_pessoal < 0) {
                                    printf("\nNota invalida, digite uma nota entre 0 e 10: ");
                                    scanf ("%d", &filme.nota_pessoal);
                                }
                                getchar();
                                printf ("\nSinopse/descricao do filme:\n"); //Qual a sinopse/descrição do filme
                                scanf (" %299[^\n]", filme.descricao);
                                
                                j = adicionar_filme_ordenado_nome ( lista , filme );
                                if (j == 1) {
                                    limparTela();
                                    printf ("\nFilme inserido com sucesso!!\n");
                                    sleep(2);
                                }
                                
                            break;
                            
                            case 2 :
                                limparTela();
                                printf ("\nTitulo do filme:\n"); //Qual o título do filme a ser removido
                                scanf (" %99[^\n]", titulo);
                                j = remover_filme_nome ( lista , titulo );
                                if (j == 1) {
                                    limparTela();
                                    printf ("\nFilme removido com sucesso!!\n");
                                    sleep(2);
                                }
                            
                            break;
                            
                            case 3 :
                                limparTela();
                                printf ("\nTitulo do filme:\n"); //Qual o título do filme que o ator participa
                                scanf (" %99[^\n]", titulo);
                                printf ("\nNome do ator:\n"); //Qual o nome do ator
                                scanf (" %99[^\n]", ator.nome );
                                printf ("\nPapel do ator no filme:\n"); //Qual é o papel que o ator desempenha no filme
                                scanf (" %99[^\n]", ator.papel );
                                
                                j = adicionar_ator ( lista , titulo , ator );
                                if (j == 1) {
                                    limparTela();
                                    printf ("\nAtor inserido com sucesso!!\n");
                                    sleep(2);
                                }
                                
                            
                            break;
                            
                            case 4 :
                                limparTela();
                                printf ("\nTitulo do filme:\n"); //Qual o título do filme que deseja remover o ator
                                scanf (" %99[^\n]", titulo);
                                printf ("\nNome do ator:\n"); //Qual é o nome do ator
                                scanf (" %99[^\n]", nome );
                                
                                j = remover_ator ( lista , titulo , nome );
                                if (j == 1) {
                                    limparTela();
                                    printf ("\nAtor removido com sucesso!!\n");
                                    sleep(2);
                                }
                            
                            break;
                            
                            case 5 :
                                limparTela();
                                printf ("\nTitulo do filme:\n"); //Qual o título do filme que deseja adicionar o elenco
                                scanf (" %99[^\n]", titulo);
                                printf ("\nTitulo do arquivo:\n"); //Qual o título do arquivo
                                scanf (" %99[^\n]", nome );
                                
                                carregar_atores_arquivo ( lista , nome , titulo );
                                
                            break;
                            default :
                                limparTela();
                                printf ("\nOpcao invalida!\n");
                                sleep(2);
                                
                            continue;

                            case 6 :
                                continue;
                        }
                break;
                
                case 2 :
                    limparTela();
                    printf ("\n------ Alteracoes ------\n\n");
                    printf ("1 - Editar filme;\n"); //Deseja alterar algum filme
                    printf ("2 - Editar elenco;\n"); //Deseja alterar o nome de algum ator
                    printf ("3 - Voltar;\n\n");
                    printf ("Opcao: ");
                    scanf ("%d", & sub_opcao);
                    getchar();
                        switch ( sub_opcao ){
                            
                            case 1 :
                                limparTela();
                                printf ("\nTitulo atual do filme:\n"); //Qual o nome do filme atualmente
                                scanf (" %99[^\n]", titulo);
                                printf ("\nNovo titulo:\n"); //Qual o nome desejado
                                scanf (" %99[^\n]", filme.titulo);
                                printf ("\nNova duracao:\n"); //Qual a duração atualizada
                                scanf ("%d", &filme.duracao);
                                getchar();
                                printf ("\nNovo(a) diretor(a):\n"); //Qual o diretor (a) atualizado
                                scanf (" %99[^\n]", filme.diretor);
                                printf ("\nNova nota:\n"); //Qual a sua nota atualizada para o filme
                                scanf ("%d", &filme.nota_pessoal);
                                getchar();
                                printf ("\nNova sinopse:\n"); //Qual a sinopse / descrição atualizada do filme
                                scanf (" %299[^\n]", filme.descricao);
                                
                                modificar_filme ( lista , titulo , filme);
                                
                            break;
                            
                            case 2:
                                limparTela();
                                printf ("\nNome atual do ator:\n"); //Qual o nome atual do ator
                                scanf (" %99[^\n]", nome);
                                printf ("\nNovo nome do ator:\n"); //Qual o nome atualizado do ator
                                scanf (" %99[^\n]", nome_1);
                                
                                modificar_nome_ator ( lista , nome , nome_1 );
                            
                            break;

                            case 3:
                                continue;
                            
                            default:
                                limparTela();
                                printf ("\nOpcao invalida.\n");
                                sleep(2);
                                
                            continue;
                            
                        }
                break;
                
                case 3 :
                    limparTela();
                    printf ("\n------ Pesquisa ------\n\n");
                    printf ("1 - Filmes por diretor;\n");
                    printf ("2 - Filmes por ator;\n");
                    printf ("3 - Filmes superiores a uma nota;\n");
                    printf ("4 - Sortear filme;\n");
                    printf ("5 - Voltar;\n\n");
                    printf ("Opcao: ");
                    scanf ("%d", & sub_opcao );
                    getchar();
                
                        switch ( sub_opcao  ){
                        
                            case 1 :
                                limparTela();
                                printf ("\nNome do diretor:\n"); //Qual o nome do Diretor
                                scanf (" %99[^\n]", nome);
                                
                                filmes_por_diretor ( lista , nome );
                                sleep ( 2 );
                            break;
                        
                            case 2:
                                limparTela();
                                printf ("\nNome do ator:\n"); //Qual o nome do Ator
                                scanf (" %99[^\n]", nome);
                        
                                filmes_por_ator ( lista , nome );
                                sleep ( 2 );
                            break;
                        
                            case 3:
                                limparTela();
                                printf ("\nNota: "); //Qual a nota desejada
                                scanf ("%d", &nota);
                                getchar();
                                printf ("\nFilmes com nota superior a %d\n\n", nota);
                                filmes_nota_superior ( lista , nota );
                                printf ("\n\nVoltar: digiter Enter");
                                getchar();
                            break;
                        
                            case 4:
                                limparTela();
                                sortear_filme ( lista );
                                getchar ();
                                
                            break;

                            case 5:
                                continue;
                        
                            default :
                                limparTela();
                                printf ("Opcao invalida.\n");
                                sleep(2);
                        
                            break;
                    }
                    
                break;
                
                case 4 :
                
                    limparTela();
                    imprimir_lista_filmes ( lista );
                    
                    printf ("\n\nVoltar: digiter Enter");
                    getchar();
                    
                break;
                
                case 5 :
                    limparTela();
                    printf ("\nFim do programa.\n");
                    destruir_lista ( lista );
                    run = false;
                break;
                
                default :
                limparTela();
                printf ("\nOpcao invalida.\n");
                sleep(2);
                run = false;
                break;
            }
    }
    
    return 0;

}
