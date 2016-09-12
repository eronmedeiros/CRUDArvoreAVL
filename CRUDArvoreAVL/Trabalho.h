#ifndef TRABALHO_H
#define TRABALHO_H

#include "Arvore.h"

int menu(Arvore *arv);
void carregar_arvore(Arvore *arv);
char * pesquisar_aluno(Arvore *arv, int key);
void excluir_aluno(Arvore *arv);
void cadastrar_aluno(Arvore *arv);
void salvar(Arvore *arv);
void sair_sem_salvar();

#endif // !TRABALHO_H
