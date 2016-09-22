#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Trabalho.h"
#include "Arvore.h"

int main(int argc, char *argv[])
{
	Arvore * arv = criar();

	//while (menu(arv));

	destruir(arv);
	printf("\tPrograma finalizado! \n\t");

    //fgets(word1, sizeof(word1), stdin);

	system("pause");

	return 0;
}
