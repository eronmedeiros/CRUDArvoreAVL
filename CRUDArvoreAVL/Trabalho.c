#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trabalho.h"
#include "Arvore.h"
#include "Aluno.h"

// OK
int menu(Arvore *arv)
{
	int opcao, aluno;

	system("cls");

	printf(" \n\t"
		"CRUD usando Arvore \n\n\t"
		"Selecione o que deseja fazer \n\t"
		"1 - Cadastrar Aluno \n\t"
		"2 - Excluir Aluno \n\t"
		"3 - Pesquisar Aluno \n\t"
		"4 - Salvar \n\t"
		"5 - Sair \n\t");

	printf(">> ");
	scanf("%d", &opcao);
	fflush(stdin);

	while (opcao > 5 || opcao < 1)
	{
		printf("\tSelecione uma opcao valida! \n\t");
		printf(">> ");
		scanf("%d", &opcao);
		fflush(stdin);
	}

	switch (opcao)
	{
		case 1:
			printf("\tselecionou opcao 1 \n");
			//cadastrar_aluno(arv);
			break;
		case 2:
			printf("\tselecionou opcao 2 \n");
			excluir_aluno(arv);
			break;
		case 3:
			printf("\tselecionou opcao 3 \n");

			int matricula;

			printf("\tQual a matricula do aluno? ");
			scanf("%d", &matricula);
			fflush(stdin);

			while (matricula < 1)
			{
				printf("\tInsira uma matricula valida: ");
				scanf("%d", &matricula);
				fflush(stdin);
			}

			aluno = pesquisar_aluno(arv, matricula);

			break;
		case 4:
			printf("\tselecionou opcao 4 \n");
			salvar(arv);
			return 0;
		case 5:
			printf("\tselecionou opcao 5 \n");
			return 0;
		default:
			printf("\tERRO NA ESTRUTURA DE SWITCH DO MENU");
			break;
	}
	return 1;
}

// OK
char** recuperar_dados(char *str)
{
	// Ex de string recebida por parametro:
	// 1510522 | Aluno mat. 1510522 | 1510522@ffb.edu.br | 9151.0522
	// NOME				MATRICULA		EMAIL				TELEFONE

	char **dados;
	char *nome, *matricula, *email, *telefone;
	int i, j;

	dados =		(char **) malloc(4 * sizeof(char *));
	nome =		(char *) malloc(50 * sizeof(char));
	matricula = (char *) malloc(10 * sizeof(char));
	email =		(char *) malloc(50 * sizeof(char));
	telefone =	(char *) malloc(10 * sizeof(char));

	// recupera o nome
	for (i = 0, j = 0; str[i] != '|'; i++, j++)
		nome[j] = str[i];
	nome[--j] = '\0';
	dados[0] = nome;

	// recupera a matricula
	for (i += 13, j = 0; str[i] != ' '; i++, j++)
		matricula[j] = str[i];
	matricula[j] = '\0';
	dados[1] = matricula;

	// recupera o email
	for (i += 3, j = 0; str[i] != ' '; i++, j++)
		email[j] = str[i];
	email[j] = '\0';
	dados[2] = email;

	// recupera o telefone
	for (i += 3, j = 0; str[i] != '\n'; i++, j++)
		telefone[j] = str[i];
	telefone[j] = '\0';
	dados[3] = telefone;

	return dados;
}

// OK
// carrega os dados do arquivo na arvore (em memória)
void carregar_arvore(Arvore *arv)
{
	FILE *fp = fopen("C:\\Users\\1510522\\Desktop\\CRUDArvoreAVL\\Trabalho\\BDAlunos10e1v1.txt", "r");
	char str[1000]; // "str" receberá cada linha do arquivo e será fragmentada para um array de strings.
	char **dados; // "dados" guardará o array de strings da fragmentação de "str"
	int key, i = 0;
	Aluno *aluno;

	while (fgets(str, sizeof str, fp) != NULL)
	{
		dados = recuperar_dados(str); // NOME, MATRICULA, E-MAIL, TELEFONE

		aluno = criarAluno();
        setNomeAluno(aluno, dados[0]);
        setMatriculaAluno(aluno, dados[1]);
        setEmailAluno(aluno, dados[2]);
        setTelefoneAluno(aluno, dados[3]);

		// segundo parametro transforma a string de matricula para inteiro e usa como chave da arvore
		inserir(arv, atoi(dados[1]), aluno);
		if(!(i++ % 2))
            printf("%d \n", i);

		// imprimindo os dados recebidos (só para testar se está tudo ok)
		//printf("%s %s %s %s \n", dados[0], dados[1], dados[2], dados[3]);
	}

    // limpando as informações já inseridas na arvore
    for (i = 0; i < 4; i++)
        free(dados[i]);
    free(dados);

	fclose(fp);
}

//OK
Aluno* pesquisar_aluno(Arvore *arv, int key)
{
	Aluno *aluno;

	aluno = buscar(arv, key);

	//printf("strlen(str): %d \n", strlen(str));
	//printf("str: %s", str);

	return (aluno != NULL ? aluno : NULL);
}

void excluir_aluno(Arvore *arv)
{
    int matricula;

    printf("\tMatricula: \n\t");
    printf(">> ");
    scanf("%d", &matricula);
	fflush(stdin);

	while (matricula < 1)
	{
		printf("\tSelecione uma matricula valida! \n\t");
		printf(">> ");
		scanf("%d", &matricula);
		fflush(stdin);
	}

    remover(arv, matricula);
}

void listar_alunos(Arvore *arv)
{
    FILE *fp = fopen("C:\\Users\\1510522\\Desktop\\CRUDArvoreAVL\\Trabalho\\PesqAlunos10e1.txt", "r");
	char str[10]; // "str" receberá cada linha do arquivo.
    int matricula; // "matricula" receberá o valor de "str" em formato inteiro.
    Aluno *aluno;

    printf("\n \t\tNome \t\tMatricula \t  E-mail \t  Telefone \n\n");

    while (fgets(str, sizeof str, fp) != NULL)
	{
		matricula = atoi(str);

		aluno = pesquisar_aluno(arv, matricula);

        printf("Mat.: %d - ", matricula);

		if(aluno != NULL)
            printf("%s %s %s %s \n", getMatriculaAluno(aluno), getNomeAluno(aluno), getEmailAluno(aluno), getTelefoneAluno(aluno));
        else
            printf("Não encontrado!");
	}
}

char* intToString(int matricula)
{
    int i;
    char *str1 = (char *) malloc(7 * sizeof(char));
    char str2[7];

    str1[0] = '\0';
    sprintf(str2, "%d", matricula);

    for (i = 0; i < 7 - strlen(str2); i++)
        strcat(str1, "0");
    strcat(str1, str2);

    free(str2);
    printf("String: %s \n", str1);

    return str1;
}

// OK
int cadastrar_aluno(Arvore *arv)
{
    int matricula = maior_chave(arv);
	char *nome = (char*) malloc(50 * sizeof(char));
	char *telefone = (char*) malloc(10 * sizeof(char));
	char *email = (char*) malloc(20 * sizeof(char));
	char *str = intToString(matricula);
	char *dados = (char*) malloc(256 * sizeof(char));
	dados[0] = '\0';

	// DEVERIAM HAVER REGRAS PARA CRIAÇÃO DE NOME, EMAIL E TELEFONE,
	// PORÉM COMO NÃO É O INTUITO DO TRABALHO, NÃO CRIEI ESSAS REGRAS.

	printf("Nome: ");
	scanf("%s", nome);
    fflush(stdin);

	printf("E-mail: ");
	scanf("%s", email);
    fflush(stdin);

	printf("Telefone: ");
	scanf("%s", telefone);
    fflush(stdin);

	dados = strcat(dados, nome);
	dados = strcat(dados, " | Aluno mat. ");
	dados = strcat(dados, str);
	dados = strcat(dados, " | ");
	dados = strcat(dados, email);
	dados = strcat(dados, " | ");
	dados = strcat(dados, telefone);
	dados = strcat(dados, "\n\0");

	return inserir(arv, matricula, dados);
}

// OK
char* alunoToString(Aluno* aluno)
{
    if (aluno == NULL)
        return NULL;

    char *str = (char*) malloc(128 * sizeof(char));
    char **dados;

    // FORMATO PARA SER GUARDADO: "0000001 | Aluno mat. 0000001 | 0000001@ffb.edu.br | 9000.0001"

    dados = getDadosAluno(aluno);

    strcpy(str, dados[0]); // NOME
    strcpy(str, dados[1]); // MATRICULA
    strcpy(str, " | Aluno mat. ");
    strcpy(str, dados[2]); // EMAIL
    strcpy(str, " | ");
    strcpy(str, dados[3]); // TELEFONE
    strcpy(str, "\n\0");

    free(dados[0]);
    free(dados[1]);
    free(dados[2]);
    free(dados[3]);

    return str;
}

void salvar(Arvore *arv)
{
	FILE *fp = fopen("C:\\Users\\Eron\\Desktop\\Trabalho\\BDAlunos10e1v1.txt", "w");
	char *str;
	int key, max_key;
	Aluno *aluno;

	max_key = maior_chave(arv);

    // ESTE FOR NÃO É EFICIENTE SE A DIFERENÇA DE VALORES DE CHAVE FOR MUITO GRANDE.
	for (key = menor_chave(arv); key <= max_key; key++)
	{
	    aluno = pesquisar_aluno(arv, key);
	    str = alunoToString(aluno);
	    if (str != NULL)
        {
            // ESCREVE NO ARQUIVO!
        }
	}

	fclose(fp);
}

void sair()
{

}

