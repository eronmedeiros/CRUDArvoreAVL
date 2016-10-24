#include <stdlib.h>
#include "Aluno.h"

// TODOS AS FUNÇÕES "SET" NÃO ALOCARÃO MEMÓRIA. APENAS APONTARÃO PARA OS DADOS PASSADOS POR PARÂMETRO.
// NENHUMA DAS FUNÇÕES "GET" FARÁ CÓPIA DOS DADOS DO ALUNO. APENAS RETORNARÃO PONTEIROS PARA OS MESMOS.

struct aluno
{
    char *matricula;
    char *nome;
    char *email;
    char *telefone;
};

Aluno *criar_aluno()
{
    Aluno *a = (Aluno*) malloc(sizeof(Aluno));
    a->matricula = NULL;
    a->nome = NULL;
    a->email = NULL;
    a->telefone = NULL;
    return a;
}

Aluno *criar_aluno_com_dados(char *matricula, char *nome, char *email, char *telefone)
{
    Aluno *a = (Aluno*) malloc(sizeof(Aluno));
    a->matricula = matricula;
    a->nome = nome;
    a->email = email;
    a->telefone = telefone;
    return a;
}

void destruir_aluno(Aluno *aluno)
{
    free(aluno->matricula);
    free(aluno->nome);
    free(aluno->email);
    free(aluno->telefone);
    free(aluno);
}

void set_matricula_aluno(Aluno *aluno, char *matricula)
{
    aluno->matricula = matricula;
}

char* get_matricula_aluno(Aluno *aluno)
{
    return aluno->matricula;
}

void set_nome_aluno(Aluno *aluno, char *nome)
{
    aluno->nome = nome;
}

char* get_nome_aluno(Aluno *aluno)
{
    return aluno->nome;
}

void set_email_aluno(Aluno *aluno, char *email)
{
    aluno->email = email;
}

char* get_email_aluno(Aluno *aluno)
{
	return aluno->email;
}

void set_telefone_aluno(Aluno *aluno, char *telefone)
{
    aluno->telefone = telefone;
}

char* get_telefone_aluno(Aluno *aluno)
{
	return aluno->telefone;
}

char** get_dados_aluno(Aluno *aluno)
{
    char **dados = (char**) malloc(4 * sizeof(char*));

    dados[0] = aluno->matricula;
    dados[1] = aluno->nome;
    dados[2] = aluno->email;
    dados[3] = aluno->telefone;

    return dados;
}
