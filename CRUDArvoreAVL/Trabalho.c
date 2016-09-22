#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "Aluno.h"
#include "Arvore.h"
#include "Trabalho.h"

// OK // AUXILIA A OPÇÃO 1 DO MENU
void carregar_arvore(Arvore *arv)
{
	FILE *fp = fopen("C:\\Users\\67342\\Documents\\ToolsDeveloper\\CRUDArvoreAVL\\Trabalho\\BDAlunos10e5v3.txt", "r");
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

// OK // AUXILIA A OPÇÃO 2 DO MENU
int cadastrar_aluno(Arvore *arv)
{
	Aluno *aluno;
    int matricula = maior_chave(arv) + 1;
	char *novaMatricula = intToString(matricula);
	char nome[50], telefone[10], email[50];

	// DEVERIAM HAVER REGRAS PARA CRIAÇÃO DE NOME, EMAIL E TELEFONE,
	// PORÉM COMO NÃO É O INTUITO DO TRABALHO, NÃO CRIEI ESSAS REGRAS.
	fflush(stdin);
	printf("Nome: ");
	fgets(nome, sizeof nome, stdin);
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
	free(novaMatricula);

	int cadastrou = inserir(arv, matricula, aluno);

	if(!cadastrou)
        destruirAluno(aluno);

    return cadastrou;
}

// OK // AUXILIA OUTRAS FUNÇÕES
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

    return str1;
}

// OK // AUXILIA OUTRAS FUNÇÕES
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

// OK // AUXILIA OUTRAS FUNÇÕES
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

// OK // OPÇÃO 1 DO MENU
void carregar(Arvore *arv)
{
    printf("\n\tCARREGANDO! \n\t"
    "Aguarde um momento... \n");

    clock_t c0 = clock();

    carregar_arvore(arv);

    clock_t c1 = clock();

    double timestamp = (c1 - c0) * 1000 / CLOCKS_PER_SEC;

    printf("\t%.0lfms para inclusao dos dados na arvore. \n", timestamp);

    printf("\tAltura da arvore: %d \n\t", altura(arv));

    system("pause");
}

// OK // OPÇÃO 2 DO MENU
void novo_aluno(Arvore *arv)
{
    int cadastrou = cadastrar_aluno(arv);
    if (!cadastrou)
        printf("\tOcorreu um erro ao cadastrar o aluno! \n");
    else
        printf("\tAluno cadastrado com sucesso! \n");
    getch();
    fflush(stdin);
}

// OK // OPÇÃO 3 DO MENU
void listar_alunos_da_arvore(Arvore *arv)
{
    printf("Imprimindo em ordem.. \n");
    if (arv == NULL)
        printf("Carregue sua arvore na base de dados.");
    else
    {
        clock_t c2 = clock();
        imprimir_in_ordem(arv);
        clock_t c3 = clock();
        double timestamp = (c3 - c2) * 1000 / CLOCKS_PER_SEC;
        printf("\t%.0lfms para listar os alunos da arvore. \n", timestamp);
    }

    system("pause");
}

// OK // OPÇÃO 4 DO MENU
void listar_alunos_do_arquivo(Arvore *arv)
{
	// pra facilitar nossa vida ao alterar os arquivos de pesquisa.
	int arquivo;
	char fileName[200];
	char Path[100] = "C:\\Users\\1510522\\Desktop\\CRUDArvoreAVL\\Trabalho\\";

	printf("\tEscolha o numero do arquivo: \n\t"
        "Quantidade de Alunos: \n\t"
        "1) 10 alunos \n\t"
        "2) 100 alunos \n\t"
        "3) 1mil alunos \n\t"
        "4) 10mil alunos \n\t"
        "5) 100mil alunos \n\t"
        "6) 1milhao alunos \n\t");
	scanf("%d", &arquivo);
	fflush(stdin);

	while(arquivo < 1 || arquivo > 6) {
		printf("Escolha um numero valido: ");
		scanf("%d", &arquivo);
		fflush(stdin);
	}

	switch(arquivo){
		case 1:
            strcpy(fileName,"PesqAlunos10e1.txt\n\0");
            break;
		case 2:
            strcpy(fileName,"PesqAlunos10e2.txt\n\0");
            break;
		case 3:
            strcpy(fileName,"PesqAlunos10e3.txt\n\0");
            break;
		case 4:
            strcpy(fileName,"PesqAlunos10e4.txt\n\0");
            break;
		case 5:
            strcpy(fileName,"PesqAlunos10e5.txt\n\0");
            break;
		case 6:
            strcpy(fileName,"PesqAlunos10e6.txt\n\0");
            break;
		default:
		    printf("Erro no switch do arquivo!\n");
	}

	printf("\tListando alunos pelo arquivo %s... \n", fileName);

    FILE *fp = fopen(strcat(Path,fileName), "r");

	char str[20]; // "str" receberá cada linha do arquivo.
    int matricula; // "matricula" receberá o valor de "str" em formato inteiro.
    Aluno *aluno;

    printf("\n \tNome \tMatricula \t  E-mail \t  Telefone \n\n");

    while (fgets(str, sizeof str, fp) != NULL)
	{
		matricula = atoi(str);

		aluno = buscar(arv, matricula);

        printf("Mat: %d -\t", matricula);

		if(aluno != NULL)
            printf("%s\t%s %s %s \n", getMatriculaAluno(aluno), getNomeAluno(aluno), getEmailAluno(aluno), getTelefoneAluno(aluno));
        else
            printf("Aluno de matricula \"%d\" não encontrado! \n", matricula);
	}
}

// !OK // OPÇÃO 5 DO MENU // PRECISA CORRIGIR
void pesquisar_aluno(Arvore *arv)
{
	Aluno *aluno = NULL;
	char **dados = NULL;

 	int matricula;
	printf("\tQual a matricula do aluno? ");
	scanf("%d", &matricula);
	fflush(stdin);

    while (matricula < 1){
        printf("\tInsira uma matricula valida: ");
        scanf("%d", &matricula);
        fflush(stdin);
    }

    aluno = buscar(arv, matricula);

    if (aluno == NULL)
        printf("\tAluno não encontrado! \n\t");
    else {
        dados = getDadosAluno(aluno);
        printf("\n\tMatricula: %s \n\t"
        "Nome: %s \n\t"
        "E-mail: %s \n\t"
        "Telefone: %s \n", dados[0], dados[1], dados[2], dados[3]);
        free(dados);
    }

    getch();
    fflush(stdin);
}

// OK // OPÇÃO 6 DO MENU
void alterar_aluno(Arvore *arv)
{

}

// OK // OPÇÃO 7 DO MENU
void remover_aluno(Arvore *arv)
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

	printf("\tExcluindo Aluno... \n");

    if (!remover(arv, matricula))
        printf("\tAluno não existe!\n");
}

// OPÇÃO 8 DO MENU
void remover_alunos_por_arquivo(Arvore *arv)
{

}
// OPÇÃO 9 DO MENU
void remover_todos_os_alunos(Arvore *arv)
{

}

// !OK // OPÇÃO 10 DO MENU // AINDA PRECISA IMPLEMENTAR A ESCRITA NO ARQUIVO.
void salvar(Arvore *arv)
{
	FILE *fp = fopen("C:\\Users\\1510522\\Desktop\\CRUDArvoreAVL\\Trabalho\\BDAlunos10e1v1.txt", "w");
	char *str;
	int key, max_key;
	Aluno *aluno;

    key = menor_chave(arv);
	max_key = maior_chave(arv);

    // ESTE FOR NÃO É EFICIENTE SE A DIFERENÇA DE VALORES DE CHAVE FOR MUITO GRANDE.
	while (key <= max_key)
	{
	    aluno = pesquisar_aluno(arv, key);

	    if (aluno != NULL)
	    {
	        str = alunoToString(aluno);

            // ESCREVE NO ARQUIVO!
        }
        key++;
	}

	fclose(fp);

	printf("\tArvore salva em arquivo! \n\t");
	getch();
	fflush(stdin);
}

// OK
int menu(Arvore *arv)
{
	int opcao;

	system("cls");

	printf(" \n\t"
		"CRUD usando Arvore \n\n\t"
		"Selecione o que deseja fazer \n\t"
		"1 - Carregar Alunos para memoria \n\t" // carregar_arvore(Arvore *arv)
		"2 - Cadastrar novo Aluno na base de dados \n\t" // novoAluno(Arvore *arv)
		"3 - Listar Alunos por ordem de matricula \n\t" // listar_alunos_da_arvore(Arvore *arv)
		"4 - Listar Alunos por arquivo \n\t" // listar_alunos_do_arquivo(Arvore *arv)
		"5 - Consultar Aluno \n\t" // pesquisar_aluno();
		"6 - Alterar Aluno \n\t" //
		"7 - Remover Aluno \n\t" //
		"8 - Remover Alunos por arquivo \n\t" //
		"9 - Remover todos alunos \n\t" //
		"10 - Salvar alteracoes \n\t" ); //

	printf(">> ");
	scanf("%d", &opcao);
	fflush(stdin);

	while (opcao > 10 || opcao < 1)
	{
		printf("\tSelecione uma opcao valida! \n\t");
		printf(">> ");
		scanf("%d", &opcao);
		fflush(stdin);
	}

	switch (opcao)
	{
		case 1:
		    carregar(arv);
		    break;
		case 2:
			novo_aluno(arv);
			break;
		case 3:
		    listar_alunos_da_arvore(arv);
			break;
		case 4:
			listar_alunos_do_arquivo(arv);
			break;
		case 5:
			consultar_aluno(arv);
			break;
		case 6:
			break;
		case 7:
			excluir_aluno(arv);
			break;
		case 10:
			salvar(arv);
			break;
		default:
			printf("\tERRO NA ESTRUTURA DE SWITCH DO MENU");
			break;
	}
	return 1;
}


// TRANSFORMA OS DADOS DO ALUNO EM UMA UNICA STRING.

