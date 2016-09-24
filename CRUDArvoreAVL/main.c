#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "Trabalho.h"
#include "Arvore.h"

int main(int argc, char *argv[])
{
	Arvore * arv = criar();

	while (menu(arv));

	printf("\tPrograma finalizado! \n\t");
	destruir(arv);
	getch();

	return 0;
}
