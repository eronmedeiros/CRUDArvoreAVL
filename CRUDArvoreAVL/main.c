#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Trabalho.h"
#include "Arvore.h"

int main(int argc, char *argv[])
{
	Arvore * arv = criar();

	printf("\n\tCARREGANDO! \n\t"
		"Aguarde um momento... \n");

	clock_t c0 = clock();

	carregar_arvore(arv);

	clock_t c1 = clock();

	unsigned double timestamp = (c1 - c0) * 1000 / CLOCKS_PER_SEC;

	printf("\t%.0lfms para inclusao dos dados na arvore. \n", timestamp);

    printf("\tAltura da arvore: %d \n\t", altura2(arv));

	system("pause");

	clock_t c2 = clock();

	imprimir_in_ordem(arv);

	clock_t c3 = clock();

	timestamp = (c2 - c3) * 1000 / CLOCKS_PER_SEC;

	printf("\t%.0lfms para imprimir os dados da arvore. \n", timestamp);

	system("pause");

	while (menu(arv));

	destruir(arv);
	printf("\tPrograma finalizado! \n\t");

    //fgets(word1, sizeof(word1), stdin);

	system("pause");

	return 0;
}

