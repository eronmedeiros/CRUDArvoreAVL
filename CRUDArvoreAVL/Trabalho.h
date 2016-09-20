#ifndef TRABALHO_H
#define TRABALHO_H

#include "Arvore.h"
#include "Aluno.h"

int menu(Arvore *arv);
void carregar_arvore(Arvore *arv);
Aluno* pesquisar_aluno(Arvore *arv, int key);
int excluir_aluno(Arvore *arv);
int cadastrar_aluno(Arvore *arv);
void salvar(Arvore *arv);
void sair_sem_salvar();
void consultarAluno(Arvore *arv);
void novoAluno(Arvore *arv);
void listar_alunos(Arvore *arv);

#endif // !TRABALHO_H
