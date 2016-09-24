#ifndef TRABALHO_H
#define TRABALHO_H

#include "Arvore.h"
#include "Aluno.h"

char* int_to_string(int matricula);
char** recuperar_dados(char *str);
char* aluno_to_string(Aluno* aluno);
void novos_dados_do_aluno(Aluno *aluno);
void carregar_arvore(Arvore *arv);
void cadastrar_aluno(Arvore *arv);
void listar_alunos_da_arvore(Arvore *arv);
void listar_alunos_do_arquivo(Arvore *arv);
void pesquisar_aluno(Arvore *arv);
void alterar_aluno(Arvore *arv);
void remover_aluno(Arvore *arv);
void remover_alunos_por_arquivo(Arvore *arv);
void remover_todos_os_alunos(Arvore **arv);
void salvar(Arvore *arv);
int menu(Arvore *arv);

#endif // !TRABALHO_H
