#ifndef ALUNO_H
#define ALUNO_H

/*
------------------------------------------------------------------------------------
---------------------------------ESTRUTURA DO ALUNO---------------------------------
------------------------------------------------------------------------------------
*/

typedef struct aluno Aluno;

/*
------------------------------------------------------------------------------------
--------------------------------------OPERAÇÕES-------------------------------------
------------------------------------------------------------------------------------
*/

Aluno *criar_aluno();
Aluno *criar_aluno_com_dados(char *matricula, char *nome, char *email, char *telefone);
void destruir_aluno(Aluno *aluno);

/*
------------------------------------------------------------------------------------
-----------------------------------------SET----------------------------------------
------------------------------------------------------------------------------------
*/

void set_matricula_aluno(Aluno *aluno, char *matricula);
void set_nome_aluno(Aluno *aluno, char *nome);
void set_email_aluno(Aluno *aluno, char *email);
void set_telefone_aluno(Aluno *aluno, char *telefone);

/*
------------------------------------------------------------------------------------
-----------------------------------------GET----------------------------------------
------------------------------------------------------------------------------------
*/

char* get_matricula_aluno(Aluno *aluno);
char* get_nome_aluno(Aluno *aluno);
char* get_email_aluno(Aluno *aluno);
char* get_telefone_aluno(Aluno *aluno);
char** get_dados_aluno(Aluno *aluno);

#endif // ALUNO_H
