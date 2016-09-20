#ifndef ARVORE_H
#define ARVORE_H

#include "Aluno.h"

typedef struct arvore Arvore;

Arvore* criar();
void destruir(Arvore * arv);

int inserir(Arvore *arv, int key, Aluno *aluno); // 1 = OK; 0 = FAIL;
int remover(Arvore *arv, int key);
Aluno* buscar(Arvore *arv, int key); // se aluno não existir, return NULL;

int menor_chave(Arvore *arv); // se não existir, return -1;
int maior_chave(Arvore *arv); // se não existir, return -1;
int contar_nos(Arvore * arv);
int contar_folhas(Arvore * arv);
int altura(Arvore * arv);
int altura2(Arvore * arv);
int estaVazia(Arvore *arv);

void imprimir_pre_ordem(Arvore *arv);
void imprimir_in_ordem(Arvore *arv);
void imprimir_pos_ordem(Arvore *arv);
void teste_avl(Arvore *arv);

#endif
