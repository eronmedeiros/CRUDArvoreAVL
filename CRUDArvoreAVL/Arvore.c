#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arvore.h"

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
        destruirAluno(no->aluno);
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

int altura_2(Arvore *arv)
{
    if(arv->raiz == NULL)
        return -1;
    return arv->raiz->altura;
}

int estaVazia(Arvore *arv)
{
	return (arv->raiz == NULL ? 1 : 0 );
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

    /* IMPLEMENTAÇÃO ITERATIVA

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

// DESCOBRI QUE ESSA MÉTODO É EXTREMAMENTE INEFICIENTE.
// É MELHOR USAR UMA VARIÁVEL EM CADA NÓ PARA CALCULAR O FATOR DE BALANCEAMENTO.
// PORÉM SÓ EXCLUIREI ELE APÓS IMPLEMENTAR O FATOR DE BALANCEAMENTO.
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

// ESSA FUNÇÃO USAVA A FUNÇÃO "balancear()" E DEVE SER REFEITA
// O BALANCEAMENTO SERÁ IMPLEMENTADO POSTERIORMENTE
void inserir_rec(No **no, int key, Aluno *aluno)
{
    No *no2 = *no;

	if (no2 != NULL)
	{
		if (key > no2->info)
        {
            inserir_rec(&no2->dir, key, aluno);
            no2->fb++;
            if(no2->fb > 2)
            {
                if(no2->dir->fb >=0)
                    rotacao_a_esquerda(no2);
                else
                    rotacao_dupla_a_esquerda(no2);
            }
        }
		else if (key < no2->info)
        {
            inserir_rec(&no2->esq, key, aluno);
            no2->fb--;

            if(no2->fb < -2)
            {
                if(no2->dir->fb <= 0)
                    rotacao_a_direita(no2);
                else
                    rotacao_dupla_a_direita(no2);
            }
        }
        else
            printf("A chave \"%d\" ja foi adicionada! \n", key);
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
	}
}

void inserir(Arvore *arv, int key, Aluno *aluno)
{
	inserir_rec(&arv->raiz, key, aluno);
}

No* pegar_maior(No **no)
{
    No *no2 = *no;

    if (no2->dir != NULL)
        return pegar_maior(&raiz->dir);

    *no = no2->esq;

    return no2;
}

// NÃO MANTEM A ARVORE BALANCEADA, MAS É O QUE TENHO POR ENQUANTO.
// IMPLEMENTAREI O BALANCEAMENTO POSTERIORMENTE.
void remover_rec(No **no, int valor)
{
    No *no2 = *no;
    if (no2 != NULL)
    {
        if (valor > no2->info)
        {
            remover_rec(no2->dir);
            no2->alturaDireita--;
        }
        else if (valor < no2->info)
        {
            remover_rec(no2->esq);
            no2->alturaEsquerda--;
        }
        else // (valor == no2->info)
        {
            if (no2->dir == NULL && no2->esq == NULL)
            {
                destruirAluno(no2->aluno);
                free(no2);
            }
            else if (no->dir != NULL && no->esq != NULL)
            {
                *no = pegar_maior(&no2->esq);
                no2->esq = *no;
            }
            else if (no->esq == NULL)
            {
                ;
            }
            else // (no->dir == NULL)
            {
                ;
            }
        }
    }
}

void remover(Arvore *arv, int valor)
{
	remover_rec(&arv->raiz, valor);
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

    // OPERAÇÃO NÃO RECURSIVA
/*
	No *raiz = arv->raiz;

	while (raiz != NULL || raiz->info != key)
        raiz = (key > raiz->info ? raiz->dir : raiz->esq);

    return (raiz != NULL ? "\0" : raiz->str);
*/

}
