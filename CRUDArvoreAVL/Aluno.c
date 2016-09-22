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
Aluno *criarAluno()
{
    Aluno *a = (Aluno*) malloc(sizeof(Aluno));
    a->matricula = NULL;
    a->nome = NULL;
    a->email = NULL;
    a->telefone = NULL;
    return a;
}

// OK
void destruirAluno(Aluno *aluno)
{
    free(aluno->matricula);
    free(aluno->nome);
    free(aluno->email);
    free(aluno->telefone);
    free(aluno);
}

// OK
void setMatriculaAluno(Aluno *aluno, char *matricula)
{
    aluno->matricula = (char*) malloc(10 * sizeof(char));
    strcpy(aluno->matricula, matricula);
}

// OK
char* getMatriculaAluno(Aluno *aluno)
{
    return aluno->matricula;
}

// OK
void setNomeAluno(Aluno *aluno, char *nome)
{
    aluno->nome = (char*) malloc(50 * sizeof(char));
    strcpy(aluno->nome, nome);
}

// OK
char* getNomeAluno(Aluno *aluno)
{
    return aluno->nome;
}

// OK
void setEmailAluno(Aluno *aluno, char *email)
{
    aluno->email = (char*) malloc(30 * sizeof(char));
    strcpy(aluno->email, email);
}

// OK
char* getEmailAluno(Aluno *aluno)
{
	return aluno->email;
}

// OK
void setTelefoneAluno(Aluno *aluno, char *telefone)
{
    aluno->telefone = (char*) malloc(10 * sizeof(char));
    strcpy(aluno->telefone, telefone);
}

// OK
char* getTelefoneAluno(Aluno *aluno)
{
	return aluno->telefone;
}

// OK
char** getDadosAluno(Aluno *aluno)
{
    char **dados = (char**) malloc(4 * sizeof(char*));

    dados[0] = aluno->matricula;
    dados[1] = aluno->nome;
    dados[2] = aluno->email;
    dados[3] = aluno->telefone;

    return dados;
}











