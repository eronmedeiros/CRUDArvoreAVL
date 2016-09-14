#ifndef ALUNO_H
#define ALUNO_H

typedef struct aluno Aluno;

Aluno *criarAluno();
void destruirAluno(Aluno *aluno);

void setMatricula(Aluno *aluno, char *matricula);
char* getMatriculaAluno(Aluno *aluno);

void setNome(Aluno *aluno, char *nome);
char* getNomeAluno(Aluno *aluno);

void setEmail(Aluno *aluno, char *email);
char* getEmailAluno(Aluno *aluno);

void setTelefone(Aluno *aluno, char *telefone);
char* getTelefoneAluno(Aluno *aluno);

char** getDadosAluno(Aluno *aluno);

#endif // ALUNO_H
