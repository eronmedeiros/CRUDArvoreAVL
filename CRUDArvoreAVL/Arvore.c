#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arvore.h"

typedef struct no No;

struct no
{
	int info;
	char str[63];
	No * esq;
	No * dir;
};

struct arvore
{
	No * raiz;
};

/*
----------------------------
-----OPERAÇÕES GENÉRICAS----
----------------------------
*/

Arvore * criar()
{
	Arvore * arv = (Arvore*) malloc(sizeof(Arvore));
	arv->raiz = NULL;
	return arv;
}

void destruir_rec(No *no)
{
	if (no != NULL)
	{
		destruir_rec(no->esq);
		destruir_rec(no->dir);
		free(no);
	}
}

void destruir(Arvore * arv)
{
	destruir_rec(arv->raiz);
	free(arv);
}

int contar_nos_rec(No * no)
{
	if (no != NULL)
		return contar_nos_rec(no->esq) + contar_nos_rec(no->dir) + 1;
	return 0;
}

int contar_nos(Arvore * arv)
{
	return contar_nos_rec(arv->raiz);
}

int contar_folhas_rec(No * no)
{
	if (no != NULL)
	{
		if(no->esq == NULL && no->dir == NULL)
			return 1;
		return contar_folhas_rec(no->esq) + contar_folhas_rec(no->dir);
	}
	return 0;
}

int contar_folhas(Arvore * arv)
{
	return contar_folhas_rec(arv->raiz);
}

int altura_rec(No * no)
{
	if (no != NULL)
	{
		int ae = altura_rec(no->esq);
		int ad = altura_rec(no->dir);
		return (ae > ad ? ae : ad) + 1;
	}
	return -1;
}

int altura(Arvore * arv)
{
	return altura_rec(arv->raiz);
}

int estaVazia(Arvore *arv)
{
	return (arv->raiz != NULL ? 1 : 0 );
}

void pre_ordem(No * no) // percorrendo árvore e imprimindo pre_ordem
{
	if (no != NULL)
	{
		printf("%d ", no->info);
		pre_ordem(no->esq);
		pre_ordem(no->dir);
	}
}

void in_ordem(No * no) // percorrendo árvore e imprimindo in_ordem
{
	if (no != NULL)
	{
		in_ordem(no->esq);
		printf("%d ", no->info);
		in_ordem(no->dir);
	}
}

void pos_ordem(No * no) // percorrendo árvore e imprimindo pos_ordem
{
	if (no != NULL)
	{
		pos_ordem(no->esq);
		pos_ordem(no->dir);
		printf("%d ", no->info);
	}
}

void imprimir_in_ordem_rec(No * no) // percorrendo árvore e imprimindo os dados in_ordem
{
	if (no != NULL)
	{
		imprimir_in_ordem_rec(no->esq);
		printf("%s \n", no->str);
		imprimir_in_ordem_rec(no->dir);
	}
}

void imprimir_in_ordem(Arvore * arv)
{
	imprimir_in_ordem_rec(arv->raiz);
	printf("\n");
}

void imprimir_pre_ordem_rec(No * no) // percorrendo árvore e imprimindo os dados pre_ordem
{
	if (no != NULL)
	{
		printf("%s \n", no->str);
		imprimir_pre_ordem_rec(no->esq);
		imprimir_pre_ordem_rec(no->dir);
	}
}

void imprimir_pre_ordem(Arvore * arv)
{
	pre_ordem(arv->raiz);
	printf("\n");
}

void imprimir_pos_ordem_rec(No * no) // percorrendo árvore e imprimindo os dados pos_ordem
{
	if (no != NULL)
	{
		imprimir_pos_ordem_rec(no->esq);
		imprimir_pos_ordem_rec(no->dir);
		printf("%s \n", no->str);
	}
}

void imprimir_pos_ordem(Arvore * arv)
{
	pos_ordem(arv->raiz);
	printf("\n");
}

int maior_chave_rec(No *no)
{
	if (no->dir != NULL)
		return maior_chave(no->dir);
	else
		return no->info;
}

int maior_chave(Arvore *arv)
{
	return maior_chave_rec(arv->raiz);
}

/*
----------------------------------
-------------ROTAÇÕES-------------
----------------------------------
*/

No* rotacao_a_esquerda(No *no)
{
	No *aux = no->dir;

	no->dir = aux->esq;
	aux->esq = no;

	return aux;
}

No* rotacao_a_direita(No *no)
{
	No *aux = no->esq;

	no->esq = aux->dir;
	aux->dir = no;

	return aux;
}

No* rotacao_dupla_a_esquerda(No *no)
{
	no->dir = rotacao_a_direita(no->dir);
	return rotacao_a_esquerda(no);
}

No* rotacao_dupla_a_direita(No *no)
{
	no->dir = rotacao_a_esquerda(no->esq);
	return rotacao_a_direita(no);
}

/*
----------------------------------
INSERÇÃO, REMOÇÃO E BALANCEAMENTO
----------------------------------
*/

No* balancear(No *no)
{
	int dir, esq, fb;

	dir = altura_rec(no->dir)+1;
	esq = altura_rec(no->esq)+1;
	/*
	esq = (esq == -1 ? 0 : esq);
	dir = (dir == -1 ? 0 : dir);
	*/
	fb = esq - dir;

	if (fb > 1)
	{
		int esq2, dir2, fb2;
		esq2 = altura_rec(no->esq->esq)+1;
		dir2 = altura_rec(no->esq->dir)+1;
		/*
		esq2 = (esq2 == -1 ? 0 : esq2);
		dir2 = (dir2 == -1 ? 0 : dir2);
		*/
		fb2 = esq2 - dir2;

		if (fb2 >= 0)
			return rotacao_a_direita(no);
		else
			return rotacao_dupla_a_direita(no);
	}
	if (fb < -1)
	{
		int esq2, dir2, fb2;
		esq2 = altura_rec(no->dir->esq)+1;
		dir2 = altura_rec(no->dir->dir)+1;
		/*
		esq2 = (esq2 == -1 ? 0 : esq2);
		dir2 = (dir2 == -1 ? 0 : dir2);
		*/
		fb2 = esq2 - dir2;

		if (fb2 <= 0)
			return rotacao_a_esquerda(no);
		else
			return rotacao_dupla_a_esquerda(no);
	}
	return no;
}

No* inserir_rec(No *no, int key, char *str)
{
	if (no != NULL)
	{
		if (key == no->info)
		{
			printf("A chave \"%d\" ja foi adicionada! \n", key);
			return no;
		}

		if (key > no->info)
		{
			no->dir = inserir_rec(no->dir, key, str);
			/* balanceando */
			return balancear(no);
		}
		else
		{
			no->esq = inserir_rec(no->esq, key, str);
			/* balanceando */
			return balancear(no);
		}
	}
	else
	{
		no = (No*) malloc(sizeof(No));
		strcpy(no->str, str);
		no->info = key;
		no->esq = NULL;
		no->dir = NULL;
		return no;
	}
	return no;
}

void inserir(Arvore *arv, int key, char * str)
{
	arv->raiz = inserir_rec(arv->raiz, key, str);
}

/*
	A função inserir2_rec() considera que a estrutura de no contem dois
	inteiros a mais que representam a altura da arvore a esquerda e a direita.
	Ela será modificada posteriormente.

No* inserir2_rec(No *no, int key, char *str)
{
	if (no != NULL)
	{
		if (key == no->info)
		{
			printf("A chave \"%d\" ja foi adicionada! \n", key);
			return no;
		}

		if (key > no->info)
		{
			no->dir = inserir2_rec(no->dir, key, str);
			no->altdir++;
			// balanceando
			return balancear(no);
		}
		else
		{
			no->esq = inserir2_rec(no->esq, key, str);
			no->altesq++;
			// balanceando
			return balancear(no);
		}
	}
	else
	{
		no = (No*)malloc(sizeof(No));
		strcpy_s(no->str, sizeof no->str, str);
		no->info = key;
		no->esq = NULL;
		no->dir = NULL;
		no->altesq = 0;
		no->altdir = 0;
		return no;
	}
	return no;
}

void inserir2(Arvore *arv, int key, char *str)
{
	arv->raiz = inserir2_rec(arv->raiz, key, str);
}*/

void remover_rec(No *no, int valor)
{

}

void remover(Arvore *arv, int valor)
{
	remover_rec(arv->raiz, valor);
}

char* buscar_rec(No *no, int key)
{
	if (no != NULL)
	{
		if (no->info == key)
			return no->str;
		if (key > no->info)
			return buscar_rec(no->dir, key);
		else
			return buscar_rec(no->esq, key);
	}
	return "\0";
}

char* buscar(Arvore *arv, int key)
{
	return buscar_rec(arv->raiz, key);
}
