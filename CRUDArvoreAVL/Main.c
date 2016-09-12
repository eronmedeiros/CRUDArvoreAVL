#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Trabalho.h"
#include "Arvore.h"

int main(int argc, char *argv[])
{
	Arvore * arv = criar();

	printf("\n\tCARREGANDO! \n\t"
		"Aguarde um momento... \n");
	carregar_arvore(arv);

	pesquisar_aluno(arv, 4);
	//while (menu(arv))
		getch();
    listar_alunos(arv);
    	getch();

    printf("Altura: %d \n", altura(arv));
	//int mat = 100000;
	//printf("Aluno de matricula %d existe? %s \n", mat, pesquisar_aluno(arv, mat));

	destruir(arv);
	printf("\tPrograma finalizado! \n\t");
	system("pause");

	return 0;
}
