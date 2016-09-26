#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Aluno.h"

// TODOS AS FUNÇÕES "SET" ALOCARÃO MEMÓRIA E COPIARÃO OS DADOS PASSADOS POR PARÂMETRO PARA O DEVIDO CAMPO DO ALUNO.
// NENHUMA DAS FUNÇÕES "GET" FARÁ CÓPIA DOS DADOS. ELAS RETORNARÃO PONTEIROS PARA OS PRÓPRIOS DADOS DO ALUNO.

// OK
struct aluno
{
    char *matricula;
    char *nome;
    char *email;
    char *telefone;
};

// OK
Aluno *criar_aluno()
{
    Aluno *a = (Aluno*) malloc(sizeof(Aluno));
    a->matricula = NULL;
    a->nome = NULL;
    a->email = NULL;
    a->telefone = NULL;
    return a;
}

// OK
void destruir_aluno(Aluno *aluno)
{
    free(aluno->matricula);
    free(aluno->nome);
    free(aluno->email);
    free(aluno->telefone);
    free(aluno);
}

// OK
void set_matricula_aluno(Aluno *aluno, char *matricula)
{
    aluno->matricula = matricula;
}

// OK
char* get_matricula_aluno(Aluno *aluno)
{
    return aluno->matricula;
}

// OK
void set_nome_aluno(Aluno *aluno, char *nome)
{
    aluno->nome = nome;
}

// OK
char* get_nome_aluno(Aluno *aluno)
{
    return aluno->nome;
}

// OK
void set_email_aluno(Aluno *aluno, char *email)
{
    aluno->email = email;
}

// OK
char* get_email_aluno(Aluno *aluno)
{
	return aluno->email;
}

// OK
void set_telefone_aluno(Aluno *aluno, char *telefone)
{
    aluno->telefone = telefone;
}

// OK
char* get_telefone_aluno(Aluno *aluno)
{
	return aluno->telefone;
}

// OK
char** get_dados_aluno(Aluno *aluno)
{
    char **dados = (char**) malloc(4 * sizeof(char*));

    dados[0] = aluno->nome;
    dados[1] = aluno->matricula;
    dados[2] = aluno->email;
    dados[3] = aluno->telefone;

    return dados;
}











