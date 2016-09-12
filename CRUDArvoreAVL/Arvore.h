#ifndef ARVORE_H
#define ARVORE_H

typedef struct arvore Arvore;

Arvore* criar();
void destruir(Arvore * arv);

void inserir(Arvore *arv, int valor, char *str);
void remover(Arvore *arv, int valor);
char* buscar(Arvore *arv, int key);

int contar_nos(Arvore * arv);
int contar_folhas(Arvore * arv);

int altura(Arvore * arv);
int estaVazia(Arvore *arv);

void imprimir(Arvore * arv);

#endif