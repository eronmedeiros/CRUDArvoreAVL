#ifndef ALUNO_H
#define ALUNO_H

typedef struct aluno Aluno;

Aluno *criarAluno();
void destruirAluno(Aluno *aluno);
void setMatricula(Aluno *aluno, char *matricula);
void setNome(Aluno *aluno, char *nome);
void setEmail(Aluno *aluno, char *email);
void setTelefone(Aluno *aluno, char *telefone);
char** getDados(Aluno *aluno);

#endif // ALUNO_H
