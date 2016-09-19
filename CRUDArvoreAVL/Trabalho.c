#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Aluno.h"
#include "Arvore.h"
#include "Trabalho.h"

// OK
int menu(Arvore *arv)
{
	int opcao;
	Aluno *aluno;

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
			cadastrar_aluno(arv);
			break;
		case 2:
			excluir_aluno(arv);
			break;
		case 3:
			;
			int matricula;
			char **dados = NULL;

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
			if (aluno == NULL)
				printf("\tAluno não encontrado! \n");
			else
			{
				dados = getDadosAluno(aluno);
				printf("\tMatricula: %s \n\t"
						"Nome: %s \n\t"
						"E-mail: %s \n\t"
						"Telefone: %s \n\t", dados[0], dados[1], dados[2], dados[3]);
			}

			if (dados != NULL)
				free(dados);

			getch();
			fflush(stdin);
			break;
		case 4:
			salvar(arv);
			break;
		case 5:
			return 0;
		default:
			printf("\tERRO NA ESTRUTURA DE SWITCH DO MENU");
			break;
	}
	return 1;
}

// TRANSFORMA OS DADOS DA STRING  LIDA NO ARQUIVO EM UM ARRAY DE STRINGS.
// O ARRAY CONTÉM OS DADOS DO ALUNO NA SEQUENCIA PADRÃO (NOME, MATRICULA, E-MAIL E TELEFONE)
// OK
char** recuperar_dados(char *str)
{
	// Ex de string recebida por parametro:
	// 1510522 | Aluno mat. 1510522 | 1510522@ffb.edu.br | 9151.0522
	// NOME			MATRICULA				EMAIL			TELEFONE

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

// OK // carrega os dados do arquivo na arvore (em memória)
void carregar_arvore(Arvore *arv)
{
	FILE *fp = fopen("C:\\Users\\Eron\\Desktop\\CRUDArvoreAVL\\Trabalho\\BDAlunos10e5v1.txt", "r");
	char str[1000]; // "str" receberá cada linha do arquivo e será fragmentada para um array de strings.
	char **dados; // "dados" guardará o array de strings da fragmentação de "str"
	int i = 0;
	Aluno *aluno;

	while (fgets(str, sizeof str, fp) != NULL)
	{
		dados = recuperar_dados(str); // NOME, MATRICULA, E-MAIL, TELEFONE

		aluno = criarAluno();
        setNomeAluno(aluno, dados[0]);
        setMatriculaAluno(aluno, dados[1]);
        setEmailAluno(aluno, dados[2]);
        setTelefoneAluno(aluno, dados[3]);

		// o segundo parametro transforma a string de matricula para inteiro e usa como chave
		inserir(arv, atoi(dados[1]), aluno);
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
	return buscar(arv, key);
}

// RETORNA 0 CASO NÃO EXISTA O ALUNO OU 1 CASO A REMOÇÃO OCORRA COM SUCESSO.
// OK
void excluir_aluno(Arvore *arv)
{
    int matricula, removeu;

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

	printf("\tExcluindo Aluno... \n");
    removeu = remover(arv, matricula);

	if (!removeu)
	{
		printf("\tO aluno de matricula %d não existe! Exclusão abortada... \n", matricula);
		system("pause");
		return;
	}

	printf("\tO aluno de matricula %d foi excluido com sucesso! \n", matricula);
	system("pause");
}

// LISTA OS ALUNOS DE UM DETERMINADO ARQUIVO QUE CONTÉM UMA LISTA DE MATRÍCULAS.
// OK
void listar_alunos(Arvore *arv)
{
    FILE *fp = fopen("C:\\Users\\Eron\\Desktop\\CRUDArvoreAVL\\Trabalho\\PesqAlunos10e1.txt", "r");
	char str[20]; // "str" receberá cada linha do arquivo.
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
            printf("Aluno de matricula \"%d\" não encontrado! \n", matricula);
	}
}

// TRANSORMA A MATRICULA EM UMA STRING DE 7 DIGITOS (TAMANHO PADRÃO)
// OK
char* intToString(int matricula)
{
    int i;
    char *str1 = (char *) malloc(7 * sizeof(char));
    char str2[7];

    str1[0] = '\0';
    sprintf(str2, "%d", matricula);

    for (i = 0; i < (7 - strlen(str2)); i++)
        strcat(str1, "0");
    strcat(str1, str2);

    printf("String: %s \n", str1);

    return str1;
}

// OK
void cadastrar_aluno(Arvore *arv)
{
	Aluno *aluno;
    int inseriu, matricula = maior_chave(arv) + 1;
	char *novaMatricula = intToString(matricula);
	char nome[50], telefone[10], email[50];

	// DEVERIAM HAVER REGRAS PARA CRIAÇÃO DE NOME, EMAIL E TELEFONE,
	// PORÉM COMO NÃO É O INTUITO DO TRABALHO, NÃO CRIEI ESSAS REGRAS.
	fflush(stdin);
	printf("Nome: ");
	scanf("%s", nome);
    fflush(stdin);

	printf("E-mail: ");
	scanf("%s", email);
    fflush(stdin);

	printf("Telefone: ");
	scanf("%s", telefone);
    fflush(stdin);

	aluno = criarAluno();
	setMatriculaAluno(aluno, novaMatricula);
	setNomeAluno(aluno, nome);
	setEmailAluno(aluno, email);
	setTelefoneAluno(aluno, telefone);

	inseriu = inserir(arv, matricula, aluno);

	if (!inseriu)
	{
		printf("\tOcorreu um erro ao cadastrar o aluno %s! \n", nome);
		destruirAluno(aluno); // ALUNO NÃO INCLUIDO! PRECISA SER DESTRUIDO.
		getch();
		fflush(stdin);
		return;
	}
	printf("\tAluno %s cadastrado com sucesso! \n", nome); // ALUNO INCLUIDO COM SUCESSO.
	getch(); 
	fflush(stdin);
}

// TRANSFORMA OS DADOS DO ALUNO EM UMA UNICA STRING.
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

// !OK // AINDA PRECISA IMPLEMENTAR A ESCRITA NO ARQUIVO.
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

	printf("\tArvore salva em arquivo! \n");
	getch();
	fflush(stdin);
}

