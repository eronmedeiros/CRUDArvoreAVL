#ifndef ARVORE_H
#define ARVORE_H

#include "Aluno.h"

/*
------------------------------------------------------------------------------------
---------------------------------ESTRUTURA DA ÁRVORE--------------------------------
------------------------------------------------------------------------------------
*/

typedef struct arvore Arvore;

/*
------------------------------------------------------------------------------------
---------------------------------OPERAÇÕES GENÉRICAS--------------------------------
------------------------------------------------------------------------------------
*/

Arvore* criar();
void destruir(Arvore *arv);
long long int contar_nos(Arvore *arv);
long long int contar_folhas(Arvore *arv);
long long int altura2(Arvore *arv); // -1 = ÁRVORE VAZIA;
long long int altura(Arvore *arv); // -1 = ÁRVORE VAZIA;
int vazia(Arvore *arv); // 1 = VAZIA; 0 = NÃO VAZIA;
long long int menor_chave(Arvore *arv); // -1 = ÁRVORE VAZIA;
long long int maior_chave(Arvore *arv); // -1 = ÁRVORE VAZIA;
int buscar(Arvore *arv, long long int chave); // 1 = EXISTE; 0 = NÂO EXISTE;

/*
------------------------------------------------------------------------------------------
------------------------------------INSERÇÃO E REMOÇÃO------------------------------------
------------------------------------------------------------------------------------------
*/

int inserir(Arvore *arv, long long int chave, Aluno *aluno); // 1 = OK; 0 = FAIL;
int remover(Arvore *arv, long long int chave); // 1 = OK; 0 = FAIL;

/*
------------------------------------------------------------------------------------------
----------------------------------------TESTE AVL-----------------------------------------
------------------------------------------------------------------------------------------
*/

int avl(Arvore *arv); // 1 = AVL; 0 = NÃO AVL;

/*
------------------------------------------------------------------------------------------
----------------------------------OPERAÇÕES DO TRABALHO-----------------------------------
------------------------------------------------------------------------------------------
*/

Aluno* buscar_aluno(Arvore *arv, long long int matricula); // NULL = ALUNO NÃO EXISTE;
void imprimir_alunos_in_ordem(Arvore *arv); // IMPRIME AS INFORMAÇÕES DOS ALUNOS
void remover_todos_os_alunos_da_arvore(Arvore *arv); // REMOVE TODOS OS ALUNOS DA ÁRVORE.
void salvar_alunos_no_arquivo(Arvore *arv, FILE *fp); // SALVA OS ALUNOS NO ARQUIVO PASSADO POR PARAMETRO.

#endif // ARVORE_H
