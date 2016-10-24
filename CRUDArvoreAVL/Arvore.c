#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arvore.h"
#include "Aluno.h"
#include "Trabalho.h"

/*
------------------------------------------------------------------------------------
--------------------------------ESTRUTURAS DA ÁRVORE--------------------------------
------------------------------------------------------------------------------------
*/

typedef struct no No;

struct no
{
	long long int chave; // SUPORTA ATÉ 9223372036854775807 CHAVES.
	long long int altura; // ESSA ALTURA É CONTADA COMO NÚMERO DE NÓS DA RAIZ ATÉ A FOLHA, NÃO NÚMERO DE PULOS.
	Aluno *aluno;
	No *esq;
	No *dir;
};

struct arvore
{
	No *raiz;
};

/*
------------------------------------------------------------------------------------
---------------------------------OPERAÇÕES GENÉRICAS--------------------------------
------------------------------------------------------------------------------------
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

long long int contar_nos_rec(No *no)
{
	if (no != NULL)
		return contar_nos_rec(no->esq) + contar_nos_rec(no->dir) + 1;
	return 0;
}

long long int contar_nos(Arvore *arv)
{
	return contar_nos_rec(arv->raiz);
}

long long int contar_folhas_rec(No *no)
{
	if (no != NULL)
	{
		if(no->esq == NULL && no->dir == NULL)
			return 1;
		return contar_folhas_rec(no->esq) + contar_folhas_rec(no->dir);
	}
	return 0;
}

long long int contar_folhas(Arvore *arv)
{
	return contar_folhas_rec(arv->raiz);
}

long long int altura_no(No *no)
{
	if (no != NULL)
		return no->altura;
	return 0;
}

long long int altura2(Arvore *arv)
{
	return altura_no(arv->raiz) - 1;
}

long long int altura_rec(No *no)
{
	if (no != NULL)
	{
		long long int ae = altura_rec(no->esq);
		long long int ad = altura_rec(no->dir);
		return (ae > ad ? ae : ad) + 1;
	}
	return -1;
}

long long int altura(Arvore *arv)
{
	return altura_rec(arv->raiz);
}

int vazia(Arvore *arv)
{
	return (arv->raiz == NULL ? 1 : 0 );
}

long long int menor_chave_rec(No *no)
{
    if (no->esq != NULL)
		return menor_chave_rec(no->esq);
    return no->chave;
}

long long int menor_chave(Arvore *arv)
{
    // IMPLEMENTAÇÃO ITERATIVA
	if(arv->raiz != NULL)
	{
		No *no = arv->raiz;

		while(no->esq != NULL)
			no = no->esq;

		return no->chave;
	}
	return -1;

	/*
	// IMPLEMENTAÇÃO RECURSIVA
	if (arv->raiz != NULL)
		return menor_chave_rec(arv->raiz);
	return -1;
	*/
}

long long int maior_chave_rec(No *no)
{
	if (no->dir != NULL)
		return maior_chave_rec(no->dir);
    return no->chave;
}

long long int maior_chave(Arvore *arv)
{
    // IMPLEMENTAÇÃO ITERATIVA
	if(arv->raiz != NULL)
	{
		No *no = arv->raiz;

		while(no->dir != NULL)
			no = no->dir;

		return no->chave;
	}
	return -1;

	/*
	IMPLEMENTAÇÃO RECURSIVA
    if (arv->raiz != NULL)
        return menor_chave_rec(arv->raiz);
    return -1;
	*/
}

int buscar_rec(No *no, long long int chave)
{
	if (no != NULL)
	{
		if (chave < no->chave)
			return buscar_rec(no->esq, chave);
		if (chave > no->chave)
			return buscar_rec(no->dir, chave);
        return 1;
	}
	return 0;
}

int buscar(Arvore *arv, long long int chave)
{
	/*
	// IMPLEMENTAÇÃO ITERATIVA
	No *no;
	for (no = arv->raiz;
		(no != NULL && no->chave != chave);
		(no = (chave > no->chave ? no->dir : no->esq)) );

	return (no != NULL ? 1 : 0);
	*/

	//IMPLEMENTADO RECURSIVA
	return buscar_rec(arv->raiz, chave);
}

/*
------------------------------------------------------------------------------------------
--------------------------------ALGORITMOS DE CAMINHAMENTO--------------------------------
------------------------------------------------------------------------------------------
*/

void pre_ordem(No *no)
{
	if (no != NULL)
	{
 		printf("%lli ", no->chave);
		pre_ordem(no->esq);
		pre_ordem(no->dir);
	}
}

void in_ordem(No *no)
{
	if (no != NULL)
	{
		in_ordem(no->esq);
		printf("%lli ", no->chave);
		in_ordem(no->dir);
	}
}

void pos_ordem(No *no)
{
	if (no != NULL)
	{
		pos_ordem(no->esq);
		pos_ordem(no->dir);
		printf("%lli ", no->chave);
	}
}

/*
------------------------------------------------------------------------------------------
-----------------------------------------ROTAÇÕES-----------------------------------------
------------------------------------------------------------------------------------------
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
------------------------------------------------------------------------------------------
------------------------------------INSERÇÃO E REMOÇÃO------------------------------------
------------------------------------------------------------------------------------------
*/

int inserir_rec(No **no, long long int chave, Aluno *aluno)
{
    No *no2 = *no;

	if (no2 != NULL)
	{
	    int adicionou;

		if (chave > no2->chave)
        {
            adicionou = inserir_rec(&no2->dir, chave, aluno);
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
		else if (chave < no2->chave)
        {
            adicionou = inserir_rec(&no2->esq, chave, aluno);
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
	no2->chave = chave;
	no2->altura = 1;
	no2->esq = NULL;
	no2->dir = NULL;
	*no = no2;

	return 1;
}

int inserir(Arvore *arv, long long int chave, Aluno *aluno)
{
	return inserir_rec(&arv->raiz, chave, aluno);
}

No* pegar_maior(No **no)
{
    No *no2 = *no;

    while (no2->dir != NULL)
        no2 = no2->dir;

    return no2;

    /*
    // IMPLEMENTAÇÃO RECURSIVA
    No *no2 = *no;

    if (no2->dir != NULL)
        return pegar_maior(&no2->dir);

    *no = no2->esq;

    return no2;
    */
}

int remover_rec(No **no, long long int chave)
{
    No *no2 = *no;

    if (no2 != NULL)
    {
		int removeu;
		int fb;

        if (chave > no2->chave)
        {
            removeu = remover_rec(&no2->dir, chave);
			if (!removeu)
				return 0;

			// PRECISA AJUSTAR A ALTURA DO NO2 E BALANCEAR
			no2->altura = (altura_no(no2->dir) > altura_no(no2->esq) ? altura_no(no2->dir) : altura_no(no2->esq)) + 1;

			fb = altura_no(no2->dir) - altura_no(no2->esq);
            if (fb < -1)
            {
                fb = altura_no(no2->esq->dir) - altura_no(no2->esq->esq);

				if(fb < 0)
					*no = rotacao_a_direita(no2);
				else
					*no = rotacao_dupla_a_direita(no2);
            }
        }
        else if (chave < no2->chave)
        {
			removeu = remover_rec(&no2->esq, chave);
			if (!removeu)
				return 0;

			// PRECISA AJUSTAR A ALTURA DO NO2 E BALANCEAR
			no2->altura = (altura_no(no2->dir) > altura_no(no2->esq) ? altura_no(no2->dir) : altura_no(no2->esq)) + 1;

			fb = altura_no(no2->dir) - altura_no(no2->esq);
            if (fb > 1)
            {
                fb = altura_no(no2->dir->dir) - altura_no(no2->dir->esq);

				if(fb > 0)
					*no = rotacao_a_esquerda(no2);
				else
					*no = rotacao_dupla_a_esquerda(no2);
            }
        }
        else // (chave == no2->chave)
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

int remover(Arvore *arv, long long int chave)
{
	return remover_rec(&arv->raiz, chave);
}

/*
------------------------------------------------------------------------------------------
----------------------------------------TESTE AVL-----------------------------------------
------------------------------------------------------------------------------------------
*/

int avl_rec(No *no)
{
    if (no != NULL)
    {
        int ad = avl_rec(no->dir);
        int ae = avl_rec(no->esq);

        if (ad == -1 || ae == -1)
            return -1;

        int fb = ad - ae;

        if (abs(fb) > 1)
            return -1;

        return ((ad > ae ? ad : ae) + 1);
    }
	return 0;
}

int avl(Arvore *arv)
{
    if (avl_rec(arv->raiz) != -1)
        return 1;
    return 0;
}

/*
------------------------------------------------------------------------------------------
----------------------------------OPERAÇÕES DO TRABALHO-----------------------------------
------------------------------------------------------------------------------------------
*/

Aluno* buscar_aluno_rec(No *no, long long int matricula)
{
	if (no != NULL)
	{
	    if (matricula < no->chave)
            return buscar_aluno_rec(no->esq, matricula);
		if (matricula > no->chave)
			return buscar_aluno_rec(no->dir, matricula);
        return no->aluno;
	}
	return NULL;
}

Aluno* buscar_aluno(Arvore *arv, long long int matricula)
{
	/*
	// IMPLEMENTAÇÃO ITERATIVA
	No *no;
	for (no = arv->raiz;
		(no != NULL && no->chave != matricula);
		(no = (matricula > no->chave ? no->dir : no->esq)) );

	return (no != NULL ? no->aluno : NULL);
	*/

	//IMPLEMENTADO RECURSIVA
	return buscar_aluno_rec(arv->raiz, matricula);
}

void imprimir_alunos_in_ordem_rec(No *no)
{
	if (no != NULL)
	{
	    char **dados = get_dados_aluno(no->aluno);

		imprimir_alunos_in_ordem_rec(no->esq);
		printf("\t%s \t%s \t%s \t%s \n", dados[0], dados[1], dados[2], dados[3]);
		free(dados);
		imprimir_alunos_in_ordem_rec(no->dir);
	}
}

void imprimir_alunos_in_ordem(Arvore *arv)
{
	if(arv->raiz == NULL)
		printf("\tArvore Vazia!\n");
	else
		imprimir_alunos_in_ordem_rec(arv->raiz);

	printf("\n");
}

void remover_todos_os_alunos_da_arvore_rec(No *no)
{
    if (no != NULL)
    {
        remover_todos_os_alunos_da_arvore_rec(no->dir);
        remover_todos_os_alunos_da_arvore_rec(no->esq);
        destruir_aluno(no->aluno);
        free(no);
    }
}

void remover_todos_os_alunos_da_arvore(Arvore *arv)
{
    remover_todos_os_alunos_da_arvore_rec(arv->raiz);
    arv->raiz = NULL;
}

void salvar_alunos_no_arquivo_rec(No *no, FILE *fp)
{
    if (no != NULL)
    {
        salvar_alunos_no_arquivo_rec(no->esq, fp);
        char *str = aluno_to_string(no->aluno);
        fprintf(fp, str);
        free(str);
        salvar_alunos_no_arquivo_rec(no->dir, fp);
    }
}

void salvar_alunos_no_arquivo(Arvore *arv, FILE *fp)
{
    salvar_alunos_no_arquivo_rec(arv->raiz, fp);
}
