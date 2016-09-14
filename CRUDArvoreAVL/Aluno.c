#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Aluno.h"

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
    aluno->matricula = malloc(10 * sizeof(char));
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
    aluno->nome = malloc(50 * sizeof(char));
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
    aluno->email = malloc(30 * sizeof(char));
    strcpy(aluno->email, email);
}

// OK
char* getEmailAluno(Aluno *aluno)
{
    if(aluno != NULL)
        return aluno->email;
    return NULL;
}

// OK
void setTelefoneAluno(Aluno *aluno, char *telefone)
{
    aluno->telefone = malloc(10 * sizeof(char));
    strcpy(aluno->telefone, telefone);
}

// OK
char* getTelefoneAluno(Aluno *aluno)
{
    if(aluno != NULL)
        return aluno->telefone;
    return NULL;
}

// OK
char** getDadosAluno(Aluno *aluno)
{
    int i;
    char **dados = malloc(4 * sizeof(char *));

    for (i = 0; i < 4; i++)
        dados[i] = (char *) malloc(50 * sizeof(char));

    strcpy(dados[0], aluno->matricula);
    strcpy(dados[1], aluno->nome);
    strcpy(dados[2], aluno->email);
    strcpy(dados[3], aluno->telefone);

    return dados;
}











