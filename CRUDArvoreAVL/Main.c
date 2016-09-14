#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Trabalho.h"
#include "Arvore.h"

int main(int argc, char *argv[])
{
	Arvore * arv = criar();

    printf("Altura: %d \n", altura(arv));

	printf("\n\tCARREGANDO! \n\t"
		"Aguarde um momento... \n");

	carregar_arvore(arv);

    printf("Altura: %d \n", altura(arv));

	destruir(arv);
	printf("\tPrograma finalizado! \n\t");
	system("pause");

	return 0;
}
