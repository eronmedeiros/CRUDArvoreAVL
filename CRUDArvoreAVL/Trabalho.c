#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "Aluno.h"
#include "Arvore.h"
#include "Trabalho.h"

#define TAM_MATRICULA 20 // não pode ultrapassar 9223372036854775807 (tamanho do long long int)
#define TAM_NOME 50
#define TAM_EMAIL 50
#define TAM_TELEFONE 16
#define TAM_EXTRA 11 // USADO PARA COLOCAR " | " E "\n\0" NAS STRINGS PARA SEPARAR OS CAMPOS

// AUXILIA OUTRAS FUNÇÕES
char* get_caminho_do_arquivo()
{
	int opcao;
	char *path = (char*) malloc(512 * sizeof(char));

	path[0] = '\0';
	strcat(path, "C:\\Users\\Eron\\Desktop\\CRUDArvoreAVL\\Trabalho\\");

	printf("\tEscolha o numero do arquivo: \n\t"
        "1) 10 alunos \n\t"
        "2) 100 alunos \n\t"
        "3) 1 mil alunos \n\t"
        "4) 10 mil alunos \n\t"
        "5) 100 mil alunos \n\t"
        "6) 1 milhao de alunos \n\t"
        ">> ");
	scanf("%d", &opcao);
	fflush(stdin);

	while(opcao < 1 || opcao > 6)
    {
        printf("Escolha uma opcao valida: \n\t"
                ">> ");
        scanf("%d", &opcao);
        fflush(stdin);
	}

	switch(opcao)
	{
		case 1:
		    strcat(path, "PesqAlunos10e1.txt\0");
            break;
		case 2:
		    strcat(path, "PesqAlunos10e2.txt\0");
            break;
		case 3:
		    strcat(path, "PesqAlunos10e3.txt\0");
            break;
		case 4:
		    strcat(path, "PesqAlunos10e4.txt\0");
            break;
		case 5:
		    strcat(path, "PesqAlunos10e5.txt\0");
            break;
		case 6:
		    strcat(path, "PesqAlunos10e6.txt\0");
            break;
		default:
            printf("\n\tERRO NA ESTRUTURA DO SWITCH (get_caminho_do_arquivo) \n\n");
            getch();
            fflush(stdin);
	}
	return path;
}

// AUXILIA OUTRAS FUNÇÕES
char* int_to_string(long long int matricula)
{
    int i, tam;
    long long int aux;
    char *str = (char *) malloc(TAM_MATRICULA * sizeof(char));
    char matricula_str[TAM_MATRICULA];

    // DESCOBRE A QUANTIDADE DE DÍGITOS (TAMANHO) DA MATRICULA
    for (tam = 0, aux = matricula; aux; tam++, aux /= 10);

    // CRIA UMA VERSÃO DE STRING DA MATRICULA. ERA USADO sprintf(), MAS COM A FORMATAÇÃO %lld OU %lli NÃO FUNCIONAVA.
    aux = matricula;
    matricula_str[tam--] = '\0';
    while (aux)
    {
        matricula_str[tam--] = '0' + (aux % 10);
        aux /= 10;
    }

    // COMPLETA O RESTANTE DAS CASAS DA matricula_str COM ZEROS.
    str[0] = '\0';
    tam = TAM_MATRICULA - strlen(matricula_str) - 1;
    for (i = 0; i < tam; i++)
        strcat(str, "0");
    str[tam] = '\0';

    // CONCATENA OS ZEROS COM A MATRICULA E ADICIONA O \0 AO FINAL DA STRING.
    strcat(str, matricula_str);
    str[TAM_MATRICULA - 1] = '\0';

    return str;
}

// AUXILIA OUTRAS FUNÇÕES
long long int string_to_int(char *str)
{
    int inicio, fim;
    long long int inteiro, base;

    for (inicio = 0; str[inicio] == '0'; inicio++);

    inteiro = 0;
    base = 1;
    fim = strlen(str) - 1;

    while (inicio <= fim)
    {
        inteiro = inteiro + ((str[fim] - '0') * base);
        fim--;
        base *= 10;
    }

    return inteiro;
}

// AUXILIA OUTRAS FUNÇÕES
char** recuperar_dados(char *str)
{
	// STRING RECEBIDA POR PARAMETRO SEGUE A SEQUÊNCIA:
	//   MATRICULA |         NOME       |       EMAIL        | TELEFONE
	// EX: 1510522 | Aluno mat. 1510522 | 1510522@ffb.edu.br | 9151.0522

	int i, j;
	char **dados = (char **) malloc(4 * sizeof(char *));

	// recupera a matricula
	dados[0] = (char *) malloc(TAM_MATRICULA * sizeof(char));
	for (i = 0, j = 0; str[i] != '|'; i++, j++)
		dados[0][j] = str[i];
	dados[0][--j] = '\0';

	// recupera a nome
	dados[1] = (char *) malloc(TAM_NOME * sizeof(char));
	for (i += 2, j = 0; str[i] != '|'; i++, j++)
		dados[1][j] = str[i];
	dados[1][--j] = '\0';

	// recupera o email
	dados[2] = (char *) malloc(TAM_EMAIL * sizeof(char));
	for (i += 2, j = 0; str[i] != '|'; i++, j++)
		dados[2][j] = str[i];
	dados[2][--j] = '\0';

	// recupera o telefone
	dados[3] = (char *) malloc(TAM_TELEFONE * sizeof(char));
    for (i += 2, j = 0; str[i] != '\n'; i++, j++)
		dados[3][j] = str[i];
	dados[3][j] = '\0';

	return dados;
}

// AUXILIA OUTRAS FUNÇÕES
char* aluno_to_string(Aluno* aluno)
{
    if (aluno == NULL)
        return NULL;

    // "tam" deve ter o tamanho dos campos
    int tam = TAM_MATRICULA + TAM_NOME + TAM_EMAIL + TAM_TELEFONE + TAM_EXTRA;

    char *str = (char*) malloc(tam * sizeof(char));
    char **dados = get_dados_aluno(aluno);

    // FORMATO PARA SER GUARDADO: MATRICULA NOME EMAIL TELEFONE
    // "0000001 | 0000001 | 0000001@ffb.edu.br | 9000.0001"

    str[0] = '\0';
    strcat(str, dados[0]); // MATRICULA
    strcat(str, " | ");
    strcat(str, dados[1]); // NOME
    strcat(str, " | ");
    strcat(str, dados[2]); // EMAIL
    strcat(str, " | ");
    strcat(str, dados[3]); // TELEFONE
    strcat(str, "\n\0");

    free(dados);

    return str;
}

// AUXILIA A OPÇÃO 6 DO MENU
void novos_dados_do_aluno(Aluno *aluno)
{
    int alterar = 1;
    char *novo;

    while (alterar)
    {
        printf("\n\tO que voce deseja alterar? \n\t"
                "1 - Nome \n\t"
                "2 - E-mail \n\t"
                "3 - Telefone \n\t"
                ">> ");
        scanf("%d", &alterar);
        fflush(stdin);

        while (alterar < 1 || alterar > 3)
        {
            printf("\tSelecione uma opcao valida: \n\t"
                    ">> ");
            scanf("%d", &alterar);
            fflush(stdin);
        }

        switch (alterar)
        {
            case 1:
                novo = (char*) malloc(TAM_NOME * sizeof(char));
                printf("\tNovo nome: \n\t"
                        ">> ");
                fgets(novo, TAM_NOME, stdin);
                novo[strlen(novo) - 1] = '\0'; // retira o \n do nome
                free(get_nome_aluno(aluno)); // free no nome antigo
                set_nome_aluno(aluno, novo); // set no novo nome
                break;
            case 2:
                novo = (char*) malloc(TAM_EMAIL * sizeof(char));
                printf("\tNovo e-mail: \n\t"
                       ">> ");
                fgets(novo, TAM_EMAIL, stdin);
                novo[strlen(novo) - 1] = '\0';
                free(get_email_aluno(aluno));
                set_email_aluno(aluno, novo);
                break;
            case 3:
                novo = (char*) malloc(TAM_TELEFONE * sizeof(char));
                printf("\tNovo telefone: \n\t"
                       ">> ");
                fgets(novo, TAM_TELEFONE, stdin);
                novo[strlen(novo) - 1] = '\0';
                free(get_telefone_aluno(aluno));
                set_telefone_aluno(aluno, novo);
                break;
            default:
                printf("\n\tERRO NA ESTRUTURA DO SWITCH (novos_dados_do_aluno) \n\n");
                getch();
        }
        fflush(stdin);

        printf("\n\tDados atualizados! \n\n\t"
                "Deseja alterar mais algum dado do aluno? \n\t"
                "1 - SIM \n\t"
                "0 - NAO \n\t"
                ">> ");
        scanf("%d", &alterar);
        fflush(stdin);

        while (alterar < 0 || alterar > 1)
        {
            printf("\tSelecione uma opcao valida: \n\t"
                    ">> ");
            scanf("%d", &alterar);
            fflush(stdin);
        }
    }
}

// OPÇÃO 1 DO MENU
void carregar_arvore(Arvore *arv)
{
	FILE *fp = fopen("C:\\Users\\Eron\\Desktop\\CRUDArvoreAVL\\Trabalho\\BDAlunos10e6v1.txt", "r");
    int tam = TAM_MATRICULA + TAM_NOME + TAM_EMAIL + TAM_TELEFONE + TAM_EXTRA;
	char str[tam]; // "str" receberá cada linha do arquivo e será fragmentada para um array de strings.
	char **dados; // "dados" guardará o array de strings da fragmentação de "str"
	long long int matricula = 0;
	Aluno *aluno;

    if (fp == NULL)
    {
        printf("\tArquivo para carregar a arvore nao pode ser aberto!");
        getch();
        fflush(stdin);
        return;
    }

    printf("\n\tCARREGANDO! \n\t"
            "Aguarde um momento... \n");

    clock_t c0 = clock();

	while (fgets(str, sizeof str, fp) != NULL)
	{
		dados = recuperar_dados(str); // MATRICULA, NOME, E-MAIL, TELEFONE
		aluno = criar_aluno_com_dados(dados[0], dados[1], dados[2], dados[3]);

		// o segundo parametro transforma a string de matricula para inteiro e usa como chave
		matricula = string_to_int(dados[0]);

		inserir(arv, matricula, aluno);
        free(dados);

        // TESTE
        if (!(matricula % 10000))
            printf("teste: %lli \n", matricula);
	}

    clock_t c1 = clock();

    double time_stamp = (c1 - c0) * 1000 / CLOCKS_PER_SEC;

    printf("\t%.0lfms para inclusao dos dados na arvore. \n\t"
           "Altura da arvore: %d \n\t", time_stamp, altura(arv));

	fclose(fp);

    system("pause");
}

// OPÇÃO 2 DO MENU
void cadastrar_aluno(Arvore *arv)
{
	// DEVERIAM HAVER REGRAS PARA CRIAÇÃO DE NOME, EMAIL E TELEFONE,
	// PORÉM COMO NÃO É O INTUITO DO TRABALHO, NÃO CRIEI ESSAS REGRAS.
	Aluno *aluno = criar_aluno();
    long long int matricula = maior_chave(arv) + 1;
    matricula = (matricula == 0 ? 1 : matricula);
	char *novo = int_to_string(matricula);

	set_matricula_aluno(aluno, novo);

	novo = (char*) malloc(TAM_NOME * sizeof(char));
	novo[0] = '\0';
	printf("\tNome: ");
	fgets(novo, TAM_NOME, stdin);
    fflush(stdin);
    novo[strlen(novo) - 1] = '\0';
    free(get_nome_aluno(aluno));
    set_nome_aluno(aluno, novo);

	novo = (char*) malloc(TAM_EMAIL * sizeof(char));
	novo[0] = '\0';
	printf("\tE-mail: ");
	fgets(novo, TAM_EMAIL, stdin);
    fflush(stdin);
    novo[strlen(novo) - 1] = '\0';
    free(get_email_aluno(aluno));
	set_email_aluno(aluno, novo);

    novo = (char*) malloc(TAM_TELEFONE * sizeof(char));
	novo[0] = '\0';
	printf("\tTelefone: ");
	fgets(novo, TAM_TELEFONE, stdin);
    fflush(stdin);
    novo[strlen(novo) - 1] = '\0';
    free(get_telefone_aluno(aluno));
	set_telefone_aluno(aluno, novo);

	inserir(arv, matricula, aluno);
    printf("\tAluno cadastrado com sucesso! \n");

    getch();
    fflush(stdin);
}

// OPÇÃO 3 DO MENU
void listar_alunos_da_arvore(Arvore *arv)
{
    if (vazia(arv))
        printf("\tArvore vazia. \n");
    else
    {
        printf("\n\tMatricula \t\tNome \t\t\tE-mail \t\tTelefone \n\n");
        clock_t c0 = clock();
        imprimir_alunos_in_ordem(arv);
        clock_t c1 = clock();
        double time_stamp = (c1 - c0) * 1000 / CLOCKS_PER_SEC;
        printf("\t%.0lfms para listar os alunos da arvore. \n", time_stamp);
    }

    getch();
    fflush(stdin);
}

// OPÇÃO 4 DO MENU
void listar_alunos_do_arquivo(Arvore *arv)
{
    if (vazia(arv))
        printf("\tArvore Vazia. \n");
    else
    {
        Aluno *aluno;
        char *path = get_caminho_do_arquivo();
        FILE *fp = fopen(path, "r");
        char str[TAM_MATRICULA + 2]; // "str" receberá cada linha do arquivo.

        printf("\n\tListando alunos pelo arquivo de caminho: \n\t"
               "%s \n\n\t"
               "Matricula \t\tNome \t\t\tE-mail \t\tTelefone \n\n", path);

        clock_t c0 = clock();

        while (fgets(str, sizeof str, fp) != NULL)
        {
            str[strlen(str) - 1] = '\0';
            aluno = buscar_aluno(arv, string_to_int(str));

            if(aluno != NULL)
                printf("\t%s \t%s \t%s \t%s \n", get_matricula_aluno(aluno), get_nome_aluno(aluno), get_email_aluno(aluno), get_telefone_aluno(aluno));
        }
        clock_t c1 = clock();
        double time_stamp = (c1 - c0) * 1000 / CLOCKS_PER_SEC;
        printf("\t%.0lfms para listagem dos dados da arvore. \n", time_stamp);

        free(path);
    }

	getch();
	fflush(stdin);
}

// OPÇÃO 5 DO MENU
void pesquisar_aluno(Arvore *arv)
{
	Aluno *aluno = NULL;
	char **dados = NULL;
    char scan[TAM_MATRICULA];
 	long long int matricula;

 	scan[0] = '\0';
	printf("\tQual a matricula do aluno? \n\t"
            ">> ");
    fgets(scan, TAM_MATRICULA, stdin);
	fflush(stdin);
    scan[strlen(scan) - 1] = '\0';
    matricula = string_to_int(scan);

    while (matricula < 1)
    {
        printf("\tInsira uma matricula valida: \n\t"
                ">> ");
        fgets(scan, TAM_MATRICULA, stdin);
        fflush(stdin);
        scan[strlen(scan) - 1] = '\0';
        matricula = string_to_int(scan);
    }

    aluno = buscar_aluno(arv, matricula);

    if (aluno == NULL)
        printf("\tAluno nao encontrado! \n");
    else
    {
        dados = get_dados_aluno(aluno);
        printf("\n\tMatricula: %s \n\t"
                "Nome: %s \n\t"
                "E-mail: %s \n\t"
                "Telefone: %s \n", dados[0], dados[1], dados[2], dados[3]);
        free(dados);
    }

    getch();
    fflush(stdin);
}

// OPÇÃO 6 DO MENU
void alterar_aluno(Arvore *arv)
{
    Aluno *aluno = NULL;
 	long long int matricula = 0;
 	char scan[TAM_MATRICULA];

 	scan[0] = '\0';
	printf("\tQual a matricula do aluno que sera alterado? \n\t"
            ">> ");
    fgets (scan, TAM_MATRICULA, stdin);
	fflush(stdin);
    scan[strlen(scan) - 1] = '\0';
	matricula = string_to_int(scan);

    while (matricula < 1)
    {
        scan[0] = '\0';
        printf("\tInsira uma matricula valida: \n\t"
                ">> ");
        fgets (scan, TAM_MATRICULA, stdin);
        fflush(stdin);
        scan[strlen(scan) - 1] = '\0';
        matricula = string_to_int(scan);
    }

    aluno = buscar_aluno(arv, matricula);

    if (aluno == NULL)
    {
        printf("\tAluno nao encontrado! \n");
        getch();
    }
    else
        novos_dados_do_aluno(aluno);

    fflush(stdin);
}

// OPÇÃO 7 DO MENU
void remover_aluno(Arvore *arv)
{
    long long int matricula;
 	char scan[TAM_MATRICULA];

 	scan[0] = '\0';
    printf("\tMatricula: \n\t"
            ">> ");
    fgets (scan, TAM_MATRICULA, stdin);
	fflush(stdin);
    scan[strlen(scan) - 1] = '\0';
	matricula = string_to_int(scan);

	while (matricula < 1)
	{
        scan[0] = '\0';
		printf("\tDigite uma matricula valida! \n\t"
                ">> ");
        fgets (scan, TAM_MATRICULA, stdin);
        fflush(stdin);
        scan[strlen(scan) - 1] = '\0';
        matricula = string_to_int(scan);
	}

    if (remover(arv, matricula))
        printf("\tAluno removido!\n");
    else
        printf("\tAluno nao encontrado!\n");

    getch();
    fflush(stdin);
}

// OPÇÃO 8 DO MENU
void remover_alunos_por_arquivo(Arvore *arv)
{
    char *path = get_caminho_do_arquivo();
    FILE *fp = fopen(path, "r");

	if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo %s!", path);
        return;
    }

    if (!vazia(arv))
    {
        char str[TAM_MATRICULA + 2]; // "str" receberá cada linha do arquivo.

        printf("\tRemovendo alunos pelo arquivo de caminho: \n\t"
               "%s... \n", path);

        clock_t c0 = clock();

        while (fgets(str, sizeof str, fp) != NULL)
        {
            str[strlen(str) - 1] = '\0';
            remover(arv, string_to_int(str));
        }

        clock_t c1 = clock();

        double time_stamp = (c1 - c0) * 1000 / CLOCKS_PER_SEC;
        printf("\t%.0lfms para remocao dos dados na arvore. \n", time_stamp);
    }
    else
    {
        printf("\tArvore Vazia. \n");
    }

	free(path);
    getch();
    fflush(stdin);
}

// OPÇÃO 9 DO MENU
void remover_todos_os_alunos(Arvore **arv)
{
    clock_t c0 = clock();
    remover_todos_os_alunos_da_arvore(*arv);
    clock_t c1 = clock();
    double time_stamp = (c1 - c0) * 1000 / CLOCKS_PER_SEC;
    printf("\t%.0lfms para remocao dos dados na arvore. \n", time_stamp);

    /*
    destruir(*arv);
    *arv = criar();
    */

    getch();
    fflush(stdin);
}

// OPÇÃO 10 DO MENU
void salvar(Arvore *arv)
{
    FILE *fp = fopen("C:\\Users\\Eron\\Desktop\\CRUDArvoreAVL\\Trabalho\\alunos_salvos.txt", "w");

    clock_t c0 = clock();
	salvar_alunos_no_arquivo(arv, fp);
	clock_t c1 = clock();

	double time_stamp = (c1 - c0) * 1000 / CLOCKS_PER_SEC;

    printf("\t%.0lfms para salvar os dados da arvore em arquivo. \n\t"
           "Arvore salva em arquivo! \n", time_stamp);

	fclose(fp);

	getch();
	fflush(stdin);
}

int menu(Arvore *arv)
{
	system("cls");

	int opcao;

	printf(" \n\t"
            "CRUD usando Arvore \n\n\t"
            "Selecione o que deseja fazer \n\t"
            "1 - Carregar Alunos para memoria \n\t"
            "2 - Cadastrar novo Aluno na base de dados \n\t"
            "3 - Listar Alunos por ordem de matricula \n\t"
            "4 - Listar Alunos por arquivo \n\t"
            "5 - Consultar Aluno \n\t"
            "6 - Alterar Aluno \n\t"
            "7 - Remover Aluno \n\t"
            "8 - Remover Alunos por arquivo \n\t"
            "9 - Remover todos alunos \n\t"
            "10 - Salvar alteracoes \n\t"
            "11 - Sair \n\t"
            ">> ");
	scanf("%d", &opcao);
	fflush(stdin);

	while (opcao > 11 || opcao < 1)
	{
		printf("\tSelecione uma opcao valida! \n\t"
                ">> ");
		scanf("%d", &opcao);
		fflush(stdin);
	}

	switch (opcao)
	{
		case 1:
		    carregar_arvore(arv);
		    break;
		case 2:
			cadastrar_aluno(arv);
			break;
		case 3:
		    listar_alunos_da_arvore(arv);
			break;
		case 4:
			listar_alunos_do_arquivo(arv);
			break;
		case 5:
			pesquisar_aluno(arv);
			break;
		case 6:
		    alterar_aluno(arv);
			break;
		case 7:
			remover_aluno(arv);
			break;
		case 8:
		    remover_alunos_por_arquivo(arv);
			break;
		case 9:
		    remover_todos_os_alunos(&arv);
			break;
		case 10:
			salvar(arv);
			break;
        case 11:
            return 0;
		default:
			printf("\n\tERRO NA ESTRUTURA DO SWITCH (menu) \n\n");
			break;
	}
	return 1;
}
