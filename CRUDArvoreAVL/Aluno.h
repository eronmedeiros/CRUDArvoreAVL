#ifndef ALUNO_H
#define ALUNO_H

typedef struct aluno Aluno;



Aluno *criar_aluno();
void destruir_aluno(Aluno *aluno);
void set_matricula_aluno(Aluno *aluno, char *matricula);
char* get_matricula_aluno(Aluno *aluno);
void set_nome_aluno(Aluno *aluno, char *nome);
char* get_nome_aluno(Aluno *aluno);
void set_email_aluno(Aluno *aluno, char *email);
char* get_email_aluno(Aluno *aluno);
void set_telefone_aluno(Aluno *aluno, char *telefone);
char* get_telefone_aluno(Aluno *aluno);
char** get_dados_aluno(Aluno *aluno);

#endif // ALUNO_H
