#ifndef ARVORE_H
#define ARVORE_H
#include "Aluno.h"

typedef struct arvore Arvore;

Arvore* criar();
void destruir(Arvore * arv);

void inserir(Arvore *arv, int key, Aluno *aluno);
void remover(Arvore *arv, int key);
Aluno* buscar(Arvore *arv, int key);

int menor_chave(Arvore *arv);
int maior_chave(Arvore *arv);
int contar_nos(Arvore * arv);
int contar_folhas(Arvore * arv);
int altura(Arvore * arv);
int estaVazia(Arvore *arv);

void imprimir_pre_ordem(Arvore *arv);
void imprimir_in_ordem(Arvore *arv);
void imprimir_pos_ordem(Arvore *arv);

#endif
