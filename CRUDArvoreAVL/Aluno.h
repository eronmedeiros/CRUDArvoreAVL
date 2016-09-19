#ifndef ALUNO_H
#define ALUNO_H

typedef struct aluno Aluno;

Aluno *criarAluno();
void destruirAluno(Aluno *aluno);

void setMatriculaAluno(Aluno *aluno, char *matricula);
char* getMatriculaAluno(Aluno *aluno);

void setNomeAluno(Aluno *aluno, char *nome);
char* getNomeAluno(Aluno *aluno);

void setEmailAluno(Aluno *aluno, char *email);
char* getEmailAluno(Aluno *aluno);

void setTelefoneAluno(Aluno *aluno, char *telefone);
char* getTelefoneAluno(Aluno *aluno);

char** getDadosAluno(Aluno *aluno);

#endif // ALUNO_H
