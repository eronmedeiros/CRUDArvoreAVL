#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arvore.h"
#include "Aluno.h"

typedef struct no No;

struct no
{
	int info;
	int altura; // USADO PARA BALANCEAR A ARVORE
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
        destruir_aluno(no->aluno);
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

int altura_no(No *no)
{
	if (no != NULL)
		return no->altura;
	return 0;
}

int altura2(Arvore *arv)
{
	return altura_no(arv->raiz) - 1;
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

int esta_vazia(Arvore *arv)
{
	return (arv->raiz == NULL ? 1 : 0 );
}

// percorrendo árvore e imprimindo pre_ordem
void pre_ordem(No *no)
{
	if (no != NULL)
	{
		printf("%d ", no->info);
		pre_ordem(no->esq);
		pre_ordem(no->dir);
	}
}

// percorrendo árvore e imprimindo in_ordem
void in_ordem(No *no)
{
	if (no != NULL)
	{
		in_ordem(no->esq);
		printf("%d ", no->info);
		in_ordem(no->dir);
	}
}

// percorrendo árvore e imprimindo pos_ordem
void pos_ordem(No *no)
{
	if (no != NULL)
	{
		pos_ordem(no->esq);
		pos_ordem(no->dir);
		printf("%d ", no->info);
	}
}

// IMPRIME OS DADOS DO ALUNO IN ORDEM
void imprimir_in_ordem_rec(No *no)
{
	if (no != NULL)
	{
	    char **dados;
		imprimir_in_ordem_rec(no->esq);
		dados = get_dados_aluno(no->aluno);
		printf("%s\t%s\t%s\t%s \n", dados[0], dados[1], dados[2], dados[3]);
		imprimir_in_ordem_rec(no->dir);
	}
}

void imprimir_in_ordem(Arvore *arv)
{
	if(arv->raiz == NULL)
		printf("Carregue sua arvore na base de dados antes de qualquer visualizacao!\n");
	else
		imprimir_in_ordem_rec(arv->raiz);

	printf("\n");
}

// IMPRIME OS DADOS DO ALUNO PRÉ ORDEM
void imprimir_pre_ordem_rec(No *no)
{
	if (no != NULL)
	{
	    char **dados;
		dados = get_dados_aluno(no->aluno);
		printf("%s  %s %s  %s \n", dados[0], dados[1], dados[2], dados[3]);
		imprimir_pre_ordem_rec(no->esq);
		imprimir_pre_ordem_rec(no->dir);
	}
}

void imprimir_pre_ordem(Arvore *arv)
{
    if(arv->raiz == NULL)
		printf("Carregue sua arvore na base de dados antes de qualquer visualizacao!\n");
	else
        imprimir_pre_ordem_rec(arv->raiz);

	printf("\n");
}

// IMPRIME OS DADOS DO ALUNO PóS ORDEM
void imprimir_pos_ordem_rec(No *no)
{
	if (no != NULL)
	{
		char **dados;

		imprimir_pos_ordem_rec(no->esq);
		imprimir_pos_ordem_rec(no->dir);

		dados = get_dados_aluno(no->aluno);
		printf("%s  %s %s  %s \n", dados[0], dados[1], dados[2], dados[3]);
	}
}

void imprimir_pos_ordem(Arvore *arv)
{
    if(arv->raiz == NULL)
		printf("Carregue sua arvore na base de dados antes de qualquer visualizacao!\n");
	else
        imprimir_pos_ordem_rec(arv->raiz);
	printf("\n");
}

int menor_chave_rec(No *no)
{
    if (no->esq != NULL)
		return menor_chave_rec(no->esq);
    return no->info;
}

int menor_chave(Arvore *arv)
{
    // IMPLEMENTAÇÃO ITERATIVA
	if(arv->raiz != NULL)
	{
		No *no = arv->raiz;

		while(no->esq != NULL)
			no = no->esq;

		return no->info;
	}
	return -1;

	/*
	// IMPLEMENTAÇÃO RECURSIVA
	if (arv->raiz != NULL)
		return menor_chave_rec(arv->raiz);
	return -1;
	*/
}

int maior_chave_rec(No *no)
{
	if (no->dir != NULL)
		return maior_chave_rec(no->dir);
    return no->info;
}

int maior_chave(Arvore *arv)
{
    // IMPLEMENTAÇÃO ITERATIVA
	if(arv->raiz != NULL)
	{
		No *no = arv->raiz;

		while(no->dir != NULL)
			no = no->dir;

		return no->info;
	}
	return -1;

	/*
	IMPLEMENTAÇÃO RECURSIVA
    if (arv->raiz != NULL)
        return menor_chave_rec(arv->raiz);
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
        return buscar_rec(no->esq, key);
	}
	return NULL;
}

Aluno* buscar(Arvore *arv, int key)
{
	/*
	// IMPLEMENTAÇÃO ITERATIVA
	No *no = arv->raiz;
	for (no = arv->raiz;
		(no != NULL && no->info != key);
		(no = (key > no->info ? no->dir : no->esq)) );

	return (no != NULL ? no->aluno : NULL);
	*/

	//IMPLEMENTADO RECURSIVA
	return buscar_rec(arv->raiz, key);

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

	no->altura = altura_rec(no) + 1;
	aux->altura = altura_rec(aux) + 1;

	return aux;
}

No* rotacao_a_direita(No *no)
{
	No *aux = no->esq;

	no->esq = aux->dir;
	aux->dir = no;

	no->altura = altura_rec(no) + 1;
	aux->altura = altura_rec(aux) + 1;

	return aux;
}

No* rotacao_dupla_a_esquerda(No *no)
{
	no->dir = rotacao_a_direita(no->dir);
	return rotacao_a_esquerda(no);
}

No* rotacao_dupla_a_direita(No *no)
{
	no->esq = rotacao_a_esquerda(no->esq);
	return rotacao_a_direita(no);
}

/*
----------------------------------
--------INSERÇÃO E REMOÇÃO--------
----------------------------------
*/

int teste_avl_rec(No *no)
{
    if (no != NULL)
    {
        int ad = teste_avl_rec(no->dir);
        int ae = teste_avl_rec(no->esq);
        int fb = ad - ae;

        if (abs(fb) > 1)
            printf("No %d nao balanceado. Fb = %d \n", no->info, ad - ae);

        return ((ad > ae ? ad : ae) + 1);
    }
	return 0;
}

void teste_avl(Arvore *arv)
{
    teste_avl_rec(arv->raiz);
}

// RETORNA 0 CASO O ALUNO JÁ EXISTA NA ARVORE E 1 CASO A INSERÇÃO OCORRA COM SUCESSO.
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

			no2->altura = ((altura_no(no2->esq) > altura_no(no2->dir) ? altura_no(no2->esq) : altura_no(no2->dir)) + 1);

			int fb = altura_no(no2->dir) - altura_no(no2->esq);
			if(fb > 1)
			{
				fb = altura_no(no2->dir->dir) - altura_no(no2->dir->esq);

				if(fb >= 0)
					*no = rotacao_a_esquerda(no2);
				else
					*no = rotacao_dupla_a_esquerda(no2);
			}
            return 1;

        }
		else if (key < no2->info)
        {
            adicionou = inserir_rec(&no2->esq, key, aluno);
            if (!adicionou)
                return 0;

			no2->altura = ((altura_no(no2->esq) > altura_no(no2->dir) ? altura_no(no2->esq) : altura_no(no2->dir)) + 1);

			int fb = altura_no(no2->dir) - altura_no(no2->esq);
			if(fb < -1)
			{
				fb = altura_no(no2->esq->dir) - altura_no(no2->esq->esq);

				if(fb <= 0)
					*no = rotacao_a_direita(no2);
				else
					*no = rotacao_dupla_a_direita(no2);
			}
			return 1;
        }
        else
            return 0;
	}

	no2 = (No*) malloc(sizeof(No));
	no2->aluno = aluno;
	no2->info = key;
	no2->altura = 1;
	no2->esq = NULL;
	no2->dir = NULL;
	*no = no2;

	return 1;
}

int inserir(Arvore *arv, int key, Aluno *aluno)
{
	return inserir_rec(&arv->raiz, key, aluno);
}

// FUNÇÃO UTILIZADA EM "remover_rec()". PEGA O NÓ DE MAIOR CHAVE.
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
// RETORNA 0 CASO NÃO HAJA O QUE REMOVER E 1 SE REMOVEU COM SUCESSO.
// !OK // AINDA HÁ ALGUM ERRO QUE NÃO ENCONTREI
int remover_rec(No **no, int key)
{
    No *no2 = *no;

    if (no2 != NULL)
    {
		int removeu;

        if (key > no2->info)
        {
            removeu = remover_rec(&no2->dir, key);
			if (!removeu)
				return 0;
			// PRECISA AJUSTAR A ALTURA NO2

        }
        else if (key < no2->info)
        {
			removeu = remover_rec(&no2->esq, key);
			if (!removeu)
				return 0;
			// PRECISA AJUSTAR A ALTURA DO NO2
        }
        else // (key == no2->info)
        {
            if (no2->dir == NULL && no2->esq == NULL)
            {
                destruir_aluno(no2->aluno);
                *no = NULL;
            }
            else if (no2->dir != NULL && no2->esq != NULL)
            {
                *no = pegar_maior(&no2->esq);
                (*no)->dir = no2->dir;
                (*no)->esq = no2->esq;
            }
            else if (no2->esq == NULL)
                *no = no2->dir;
            else // (no2->dir == NULL)
                *no = no2->esq;

            destruir_aluno(no2->aluno);
            free(no2);
        }
		return 1;
    }
	return 0;
}

// AINDA PRECISO AJUSTAR
// ESSA FUNÇÃO DEVE SER DE REMOÇÃO NÃO BALANCEADA, PORÉM FUNCIONAL
// !OK
int remover_rec2(No **no, int key)
{
    No *no2 = *no;

    if (no2 != NULL)
    {
		int removeu;

        if (key > no2->info)
        {
            removeu = remover_rec(&no2->dir, key);
			if (!removeu)
				return 0;
			// PRECISA AJUSTAR A ALTURA NO2

        }
        else if (key < no2->info)
        {
			removeu = remover_rec(&no2->esq, key);
			if (!removeu)
				return 0;
			// PRECISA AJUSTAR A ALTURA DO NO2
        }
        else // (key == no2->info)
        {
            if (no2->dir != NULL && no2->esq != NULL)
            {
                *no = pegar_maior(&no2->esq);
                (*no)->dir = no2->dir;
                (*no)->esq = no2->esq;
            }
            else if (no2->dir == NULL && no2->esq == NULL)
                *no = NULL;
            else if (no2->esq == NULL)
                *no = no2->dir;
            else // (no2->dir == NULL)
                *no = no2->esq;

            destruir_aluno(no2->aluno);
            free(no2);
        }
		return 1;
    }
	return 0;
}

// OK
int remover(Arvore *arv, int key)
{
	return remover_rec(&arv->raiz, key);
}
