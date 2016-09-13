#include <stdio.h>
#include <stdlib.h>
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
void setNomeAluno(Aluno *aluno, char *nome)
{
    aluno->nome = malloc(50 * sizeof(char));
    strcpy(aluno->nome, nome);
}

// OK
void setEmailAluno(Aluno *aluno, char *email)
{
    aluno->email = malloc(30 * sizeof(char));
    strcpy(aluno->email, email);
}

// OK
void setTelefoneAluno(Aluno *aluno, char *telefone)
{
    aluno->telefone = malloc(10 * sizeof(char));
    strcpy(aluno->telefone, telefone);
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
    strcpy(dados[3], alunos->telefone);

    return dados;
}











