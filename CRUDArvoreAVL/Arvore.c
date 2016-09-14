#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arvore.h"
#include "Aluno.h"

typedef struct no No;

struct no
{
	int info;
	int fb; // USADO PARA BALANCEAR A ARVORE
	Aluno *aluno;
	No *esq;
	No *dir;
};

struct arvore
{
	No *raiz;
};

/*
----------------------------
-----OPERAÇÕES GENÉRICAS----
----------------------------
*/

Arvore* criar()
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
        destruirAluno(no->aluno);
		free(no);
	}
}

void destruir(Arvore *arv)
{
	destruir_rec(arv->raiz);
	free(arv);
}

int contar_nos_rec(No *no)
{
	if (no != NULL)
		return contar_nos_rec(no->esq) + contar_nos_rec(no->dir) + 1;
	return 0;
}

int contar_nos(Arvore *arv)
{
	return contar_nos_rec(arv->raiz);
}

int contar_folhas_rec(No *no)
{
	if (no != NULL)
	{
		if(no->esq == NULL && no->dir == NULL)
			return 1;
		return contar_folhas_rec(no->esq) + contar_folhas_rec(no->dir);
	}
	return 0;
}

int contar_folhas(Arvore *arv)
{
	return contar_folhas_rec(arv->raiz);
}

int altura_rec(No *no)
{
	if (no != NULL)
	{
		int ae = altura_rec(no->esq);
		int ad = altura_rec(no->dir);
		return (ae > ad ? ae : ad) + 1;
	}
	return -1;
}

int altura(Arvore *arv)
{
	return altura_rec(arv->raiz);
}

int estaVazia(Arvore *arv)
{
	return (arv->raiz == NULL ? 1 : 0 );
}

void pre_ordem(No *no) // percorrendo árvore e imprimindo pre_ordem
{
	if (no != NULL)
	{
		printf("%d ", no->info);
		pre_ordem(no->esq);
		pre_ordem(no->dir);
	}
}

void in_ordem(No *no) // percorrendo árvore e imprimindo in_ordem
{
	if (no != NULL)
	{
		in_ordem(no->esq);
		printf("%d ", no->info);
		in_ordem(no->dir);
	}
}

void pos_ordem(No *no) // percorrendo árvore e imprimindo pos_ordem
{
	if (no != NULL)
	{
		pos_ordem(no->esq);
		pos_ordem(no->dir);
		printf("%d ", no->info);
	}
}

void imprimir_in_ordem_rec(No *no) // percorrendo árvore e imprimindo os dados in_ordem
{
	if (no != NULL)
	{
	    char **dados;
		imprimir_in_ordem_rec(no->esq);
		dados = getDadosAluno(no->aluno);
		printf("%s  %s %s  %s \n", dados[0], dados[1], dados[2], dados[3]);
		imprimir_in_ordem_rec(no->dir);
	}
}

void imprimir_in_ordem(Arvore *arv)
{
	imprimir_in_ordem_rec(arv->raiz);
	printf("\n");
}

void imprimir_pre_ordem_rec(No *no) // percorrendo árvore e imprimindo os dados pre_ordem
{
	if (no != NULL)
	{
	    char **dados;
		dados = getDadosAluno(no->aluno);
		printf("%s  %s %s  %s \n", dados[0], dados[1], dados[2], dados[3]);
		imprimir_in_ordem_rec(no->esq);
		imprimir_in_ordem_rec(no->dir);
	}
}

void imprimir_pre_ordem(Arvore *arv)
{
	pre_ordem(arv->raiz);
	printf("\n");
}

void imprimir_pos_ordem_rec(No *no) // percorrendo árvore e imprimindo os dados pos_ordem
{
	if (no != NULL)
	{
		char **dados;
		imprimir_in_ordem_rec(no->esq);
		imprimir_in_ordem_rec(no->dir);
		dados = getDadosAluno(no->aluno);
		printf("%s  %s %s  %s \n", dados[0], dados[1], dados[2], dados[3]);
	}
}

void imprimir_pos_ordem(Arvore *arv)
{
	pos_ordem(arv->raiz);
	printf("\n");
}

int menor_chave_rec(No *no)
{
    if (no->esq != NULL)
		return maior_chave(no->esq);
    return no->info;
}

int menor_chave(Arvore *arv)
{
    if (arv->raiz != NULL)
        return menor_chave_rec(arv->raiz);
    return -1;
}

int maior_chave_rec(No *no)
{
	if (no->dir != NULL)
		return maior_chave(no->dir);
    return no->info;
}

int maior_chave(Arvore *arv)
{
    if (arv->raiz != NULL)
        return menor_chave_rec(arv->raiz);
    return -1;

    /*
    IMPLEMENTAÇÃO ITERATIVA

    if(arv->raiz != NULL)
    {
        No *no = arv->raiz;

        while(no->dir != NULL)
            no = no->dir;

        return no->info;
    }
    return -1;
    */
}

// BUSCA UM ALUNO NA ARVORE ATRAVÉS DA MATRICULA (KEY)
Aluno* buscar_rec(No *no, int key)
{
	if (no != NULL)
	{
		if (no->info == key)
			return no->aluno;
		if (key > no->info)
			return buscar_rec(no->dir, key);
		else
			return buscar_rec(no->esq, key);
	}
	return NULL;
}

Aluno* buscar(Arvore *arv, int key)
{
	return buscar_rec(arv->raiz, key);

    // OPERAÇÃO NÃO RECURSIVA
/*
	No *raiz = arv->raiz;

	while (raiz != NULL || raiz->info != key)
        raiz = (key > raiz->info ? raiz->dir : raiz->esq);

    return (raiz != NULL ? raiz->aluno : NULL);
*/
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

    no->fb--;
    aux->fb--;

	return aux;
}

No* rotacao_a_direita(No *no)
{
	No *aux = no->esq;

	no->esq = aux->dir;
	aux->dir = no;

    no->fb++;
    aux->fb++;

	return aux;
}
// PRECISO AJUSTAR O BALANCEAMENTO DAS ROTAÇÕES. AINDA NÃO ESTÁ FUNCIONANDO.
No* rotacao_dupla_a_esquerda(No *no)
{
	//no->dir = rotacao_a_direita(no->dir);
	//return rotacao_a_esquerda(no);

    No *aux = no->dir;
	no->esq = rotacao_a_esquerda(no->dir);
    no = rotacao_a_direita(no);

    if (no->dir->esq == NULL)
    {
        no->fb = 0;
        no->esq->fb = 1;
        no->dir->fb = 0;
    }
    else
    {
        no->fb = 0;
        no->esq->fb = -1;
        no->dir->fb = 0;
    }

	return no;
}

No* rotacao_dupla_a_direita(No *no)
{
    No *aux = no->esq;
	no->dir = rotacao_a_esquerda(no->esq);
    no = rotacao_a_direita(no);

    if (no->esq->dir == NULL)
    {
        no->fb = 0;
        no->dir->fb = -1;
        no->esq->fb = 0;
    }
    else
    {
        no->fb = 0;
        no->dir->fb = 1;
        no->esq->fb = 0;
    }

	return no;
}

/*
----------------------------------
--------INSERÇÃO E REMOÇÃO--------
----------------------------------
*/

// ESSA FUNÇÃO USAVA A FUNÇÃO "balancear()" E DEVE SER REFEITA
// O BALANCEAMENTO SERÁ IMPLEMENTADO POSTERIORMENTE
int inserir_rec(No **no, int key, Aluno *aluno)
{
    No *no2 = *no;

	if (no2 != NULL)
	{
	    int adicionou;

		if (key > no2->info)
        {
            adicionou = inserir_rec(&no2->dir, key, aluno);
            if(!adicionou)
                return 0;

            no2->fb++;

            if(no2->fb > 1)
            {
                if(no2->dir->fb >= 0)
                    no2 = rotacao_a_esquerda(no2);
                else
                    no2 = rotacao_dupla_a_esquerda(no2);
            }

            return 1;
        }
		else if (key < no2->info)
        {
            adicionou = inserir_rec(&no2->esq, key, aluno);
            if (!adicionou)
                return 0;

            no2->fb--;

            if(no2->fb < -1)
            {
                if(no2->esq->fb <= 0)
                    no2 = rotacao_a_direita(no2);
                else
                    no2 = rotacao_dupla_a_direita(no2);
            }

            return 1;
        }
        else
            return 0;
	}
	else
	{
		no2 = (No*) malloc(sizeof(No));
		no2->aluno = aluno;
		no2->info = key;
		no2->fb = 0;
		no2->esq = NULL;
		no2->dir = NULL;
		*no = no2;
		return 1;
	}
}

int inserir(Arvore *arv, int key, Aluno *aluno)
{
	return inserir_rec(&arv->raiz, key, aluno);
}

// FUNÇÃO UTILIZADA EM "remover_rec()".
No* pegar_maior(No **no)
{
    No *no2 = *no;

    if (no2->dir != NULL)
        return pegar_maior(&no2->dir);

    *no = no2->esq;

    return no2;
}

// NÃO MANTEM A ARVORE BALANCEADA, MAS É O QUE TENHO POR ENQUANTO.
// IMPLEMENTAREI O BALANCEAMENTO POSTERIORMENTE.
// OK
void remover_rec(No **no, int key)
{
    No *no2 = *no;

    if (no2 != NULL)
    {
        if (key > no2->info)
        {
            remover_rec(no2->dir, key);
            no2->fb--;
        }
        else if (key < no2->info)
        {
            remover_rec(no2->esq, key);
            no2->fb++;
        }
        else // (key == no2->info)
        {
            if (no2->dir == NULL && no2->esq == NULL)
            {
                destruirAluno(no2->aluno);
                *no = NULL;
            }
            else if (no2->dir != NULL && no2->esq != NULL)
            {
                *no = pegar_maior(&no2->esq);
                (*no)->dir = no2->dir;
                (*no)->esq = no2->esq;
                destruirAluno(no2->aluno);
            }
            else if (no2->esq == NULL)
                *no = no2->dir;
            else // (no2->dir == NULL)
                *no = no2->esq;

            free(no2);
        }
    }
}

// OK
void remover(Arvore *arv, int key)
{
	remover_rec(&arv->raiz, key);
}
