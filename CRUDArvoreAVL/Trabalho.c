#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "Aluno.h"
#include "Arvore.h"
#include "Trabalho.h"

// OK // AUXILIA OUTRAS FUNÇÕES
char* int_to_string(int matricula)
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
char* aluno_to_string(Aluno* aluno)
{
    if (aluno == NULL)
        return NULL;

    char *str = (char*) malloc(128 * sizeof(char));
    char **dados;

    // FORMATO PARA SER GUARDADO: "0000001 | Aluno mat. 0000001 | 0000001@ffb.edu.br | 9000.0001"

    dados = get_dados_aluno(aluno);

    str[0] = '\0';
    str = strcat(str, dados[0]); // NOME
    str = strcat(str, " | Aluno mat. ");
    str = strcat(str, dados[1]); // MATRICULA
    str = strcat(str, " | ");
    str = strcat(str, dados[2]); // EMAIL
    str = strcat(str, " | ");
    str = strcat(str, dados[3]); // TELEFONE
    str = strcat(str, "\n\0");

    free(dados);

    return str;
}

// OK // AUXILIA A OPÇÃO 6 DO MENU
void novos_dados_do_aluno(Aluno *aluno)
{
    int opcao, alterar_mais;
    char novo_nome[50], novo_email[30], novo_telefone[20];
    char *str;

    while (1)
    {
        printf("\n\tO que voce deseja alterar? \n\t"
               "1 - Nome \n\t"
               "2 - E-mail \n\t"
               "3 - Telefone \n\t");
        printf(">> ");
        scanf("%d", &opcao);
        fflush(stdin);

        while (opcao < 1 || opcao > 3)
        {
            printf("\tSelecione uma opcao valida: \n\t");
            printf(">> ");
            scanf("%d", &opcao);
            fflush(stdin);
        }

        switch (opcao)
        {
            case 1:
                printf("\tNovo nome: \n\t");
                printf(">> ");
                fgets(novo_nome, sizeof novo_nome, stdin);
                novo_nome[strlen(novo_nome) - 1] = '\0';

                // FREE NOS DADOS QUE JÁ ESTAVAM LÁ, POIS set_nome_aluno() alocará uma nova memória.
                str = get_nome_aluno(aluno);
                free(str);

                set_nome_aluno(aluno, novo_nome);
                break;
            case 2:
                printf("\tNovo e-mail: \n\t");
                printf(">> ");
                scanf("%s", novo_email);

                // FREE NOS DADOS QUE JÁ ESTAVAM LÁ, POIS set_email_aluno() alocará uma nova memória.
                str = get_email_aluno(aluno);
                free(str);

                set_email_aluno(aluno, novo_email);
                break;
            case 3:
                printf("\tNovo telefone: \n\t");
                printf(">> ");
                scanf("%s", novo_telefone);

                // FREE NOS DADOS QUE JÁ ESTAVAM LÁ, POIS get_telefone_aluno() alocará uma nova memória.
                str = get_telefone_aluno(aluno);
                free(str);

                set_telefone_aluno(aluno, novo_telefone);
                break;
            default:
                printf("\tERRO NO SWITCH DE ALTERACAO DE DADOS DO ALUNO \n");
        }
        fflush(stdin);

        printf("\n\tDados atualizados! \n");

        printf("\n\tDeseja alterar mais algum dado do aluno? \n\t"
               "1 - SIM \n\t"
               "0 - NAO \n\t");
        printf(">> ");
        fflush(stdin);
        scanf("%d", &alterar_mais);
        fflush(stdin);

        while (opcao < 0 || opcao > 1)
        {
            printf("\tSelecione uma opcao valida: \n\t");
            printf(">> ");
            scanf("%d", &opcao);
            fflush(stdin);
        }

        if (!alterar_mais)
            break;
    }

}

// OK // OPÇÃO 1 DO MENU
void carregar_arvore(Arvore *arv)
{
	FILE *fp = fopen("C:\\Users\\Eron\\Desktop\\CRUDArvoreAVL\\Trabalho\\BDAlunos10e1v1.txt", "r");
	char str[1000]; // "str" receberá cada linha do arquivo e será fragmentada para um array de strings.
	char **dados; // "dados" guardará o array de strings da fragmentação de "str"
	int i = 0;
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
		dados = recuperar_dados(str); // NOME, MATRICULA, E-MAIL, TELEFONE

		aluno = criar_aluno();
        set_nome_aluno(aluno, dados[0]);
        set_matricula_aluno(aluno, dados[1]);
        set_email_aluno(aluno, dados[2]);
        set_telefone_aluno(aluno, dados[3]);

		// o segundo parametro transforma a string de matricula para inteiro e usa como chave
		inserir(arv, atoi(dados[1]), aluno);

        for (i = 0; i < 4; i++)
            free(dados[i]);
        free(dados);
	}

    clock_t c1 = clock();

    double timestamp = (c1 - c0) * 1000 / CLOCKS_PER_SEC;

    printf("\t%.0lfms para inclusao dos dados na arvore. \n", timestamp);

    printf("\tAltura da arvore: %d \n\t", altura(arv));

	fclose(fp);

    system("pause");
}

// OK // OPÇÃO 2 DO MENU
void cadastrar_aluno(Arvore *arv)
{
	Aluno *aluno;
    int matricula = maior_chave(arv) + 1;
	char *nova_matricula = int_to_string(matricula);
	char nome[50], telefone[10], email[50];

	// DEVERIAM HAVER REGRAS PARA CRIAÇÃO DE NOME, EMAIL E TELEFONE,
	// PORÉM COMO NÃO É O INTUITO DO TRABALHO, NÃO CRIEI ESSAS REGRAS.
	fflush(stdin);
	printf("\tNome: ");
	fgets(nome, sizeof nome, stdin);
    fflush(stdin);
    nome[strlen(nome) -1] = '\0';

	printf("\tE-mail: ");
	scanf("%s", email);
    fflush(stdin);

	printf("\tTelefone: ");
	scanf("%s", telefone);
    fflush(stdin);

	aluno = criar_aluno();
	set_matricula_aluno(aluno, nova_matricula);
	set_nome_aluno(aluno, nome);
	set_email_aluno(aluno, email);
	set_telefone_aluno(aluno, telefone);
	free(nova_matricula);

	inserir(arv, matricula, aluno);
    printf("\tAluno cadastrado com sucesso! \n");

    getch();
    fflush(stdin);
}

// OK // OPÇÃO 3 DO MENU
void listar_alunos_da_arvore(Arvore *arv)
{
    if (esta_vazia(arv))
        printf("\tCarregue sua arvore na base de dados antes de imprimi-la. \n");
    else
    {
        printf("\n \tNome \t\tMatricula \tE-mail \t\t\tTelefone \n\n");
        clock_t c0 = clock();
        imprimir_in_ordem(arv);
        clock_t c1 = clock();
        double timestamp = (c1 - c0) * 1000 / CLOCKS_PER_SEC;
        printf("\t%.0lfms para listar os alunos da arvore. \n", timestamp);
    }

    getch();
    fflush(stdin);
}

// OK // OPÇÃO 4 DO MENU
void listar_alunos_do_arquivo(Arvore *arv)
{
	// pra facilitar nossa vida ao alterar os arquivos de pesquisa.
	int arquivo;
	char fileName[200];
	char Path[100] = "C:\\Users\\Eron\\Desktop\\CRUDArvoreAVL\\Trabalho\\";

	printf("\tEscolha o numero do arquivo (quantidade de alunos): \n\t"
        "1) 10 alunos \n\t"
        "2) 100 alunos \n\t"
        "3) 1mil alunos \n\t"
        "4) 10mil alunos \n\t"
        "5) 100mil alunos \n\t"
        "6) 1milhao alunos \n\t"
        ">> ");
	scanf("%d", &arquivo);
	fflush(stdin);

	while(arquivo < 1 || arquivo > 6) {
		printf("Escolha uma opcao valido: \n\t");
		printf(">> ");
		scanf("%d", &arquivo);
		fflush(stdin);
	}

	switch(arquivo){
		case 1:
            strcpy(fileName,"PesqAlunos10e1.txt\0");
            break;
		case 2:
            strcpy(fileName,"PesqAlunos10e2.txt\0");
            break;
		case 3:
            strcpy(fileName,"PesqAlunos10e3.txt\0");
            break;
		case 4:
            strcpy(fileName,"PesqAlunos10e4.txt\0");
            break;
		case 5:
            strcpy(fileName,"PesqAlunos10e5.txt\0");
            break;
		case 6:
            strcpy(fileName,"PesqAlunos10e6.txt\0");
            break;
		default:
		    printf("Erro no switch do arquivo!\n");
	}

	printf("\tListando alunos pelo arquivo %s... \n", fileName);

    FILE *fp = fopen(strcat(Path,fileName), "r");

	char str[20]; // "str" receberá cada linha do arquivo.
    int matricula; // "matricula" receberá o valor de "str" em formato inteiro.
    Aluno *aluno;

    printf("\n \tNome \t\tMatricula \tE-mail \t\t\tTelefone \n\n");

    while (fgets(str, sizeof str, fp) != NULL)
	{
		matricula = atoi(str);

		aluno = buscar(arv, matricula);

		if(aluno != NULL)
            printf("\t%s \t%s \t%s \t%s \n", get_matricula_aluno(aluno), get_nome_aluno(aluno), get_email_aluno(aluno), get_telefone_aluno(aluno));
        else
            printf("\tAluno de matricula de matricula \"%d\" não encontrado! \n", matricula);
	}
	getch();
	fflush(stdin);
}

// !OK // OPÇÃO 5 DO MENU // PRECISA CORRIGIR
void pesquisar_aluno(Arvore *arv)
{
	Aluno *aluno = NULL;
	char **dados = NULL;

 	int matricula;
	printf("\tQual a matricula do aluno? \n\t");
	printf(">> ");
	scanf("%d", &matricula);
	fflush(stdin);

    while (matricula < 1)
    {
        printf("\tInsira uma matricula valida: \n\t");
        printf(">> ");
        scanf("%d", &matricula);
        fflush(stdin);
    }

    aluno = buscar(arv, matricula);

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

// OK // OPÇÃO 6 DO MENU
void alterar_aluno(Arvore *arv)
{
    Aluno *aluno = NULL;

 	int matricula;
	printf("\tQual a matricula do aluno que sera alterado? \n\t");
	printf(">> ");
	scanf("%d", &matricula);
	fflush(stdin);

    while (matricula < 1)
    {
        printf("\tInsira uma matricula valida: \n\t");
        printf(">> ");
        scanf("%d", &matricula);
        fflush(stdin);
    }

    aluno = buscar(arv, matricula);

    if (aluno == NULL)
    {
        printf("\tAluno nao encontrado! \n");
        getch();
    }
    else
        novos_dados_do_aluno(aluno);

    fflush(stdin);
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
		printf("\tDigite uma matricula valida! \n\t");
		printf(">> ");
		scanf("%d", &matricula);
		fflush(stdin);
	}

    if ( !(remover(arv, matricula)) )
        printf("\tAluno nao encontrado!\n");
    else
        printf("\tAluno removido!\n");

    getch();
    fflush(stdin);
}

// OPÇÃO 8 DO MENU
void remover_alunos_por_arquivo(Arvore *arv)
{
    // LER ARQUIVO E REMOVER OS ALUNOS

	int opcao;
	char *path = (char*) malloc(128 * sizeof(char));

	path[0] = '\0';
	path = strcat(path, "C:\\Users\\Eron\\Desktop\\CRUDArvoreAVL\\Trabalho\\");

	printf("\tEscolha o numero do arquivo: \n\t"
        "1) 10 alunos \n\t"
        "2) 100 alunos \n\t"
        "3) 1mil alunos \n\t"
        "4) 10mil alunos \n\t"
        "5) 100mil alunos \n\t"
        "6) 1milhao alunos \n\t"
        ">> ");
	scanf("%d", &opcao);
	fflush(stdin);

	while(opcao < 1 || opcao > 6) {
		printf("Escolha uma opcao valida: \n\t");
		printf(">> ");
		scanf("%d", &opcao);
		fflush(stdin);
	}

	switch(opcao){
		case 1:
		    path = strcat(path,"PesqAlunos10e1.txt\0");
            break;
		case 2:
            path = strcat(path,"PesqAlunos10e2.txt\0");
            break;
		case 3:
            path = strcat(path,"PesqAlunos10e3.txt\0");
            break;
		case 4:
            path = strcat(path,"PesqAlunos10e4.txt\0");
            break;
		case 5:
            path = strcat(path,"PesqAlunos10e5.txt\0");
            break;
		case 6:
            path = strcat(path,"PesqAlunos10e6.txt\0");
            break;
		default:
		    printf("Erro no switch da funcao remover_alunos_por_arquivo!\n");
		    getch();
	}

	printf("\tRemovendo alunos com base nos dados do arquivo de caminho: \n"
            "%s... \n", path);

    FILE *fp = fopen(path, "r");
	char str[20]; // "str" receberá cada linha do arquivo.
	int matricula;

    printf("\n \tNome \t\tMatricula \tE-mail \t\t\tTelefone \n\n");

    while (fgets(str, sizeof str, fp) != NULL)
	{
	    matricula = atoi(str);

		if (remover(arv, matricula))
            printf("\tAluno de matricula \"%d\" removido! \n", matricula);
        else
            printf("\tAluno de matricula \"%d\" nao existe na arvore! \n", matricula);
	}

    getch();
    fflush(stdin);
}

// OPÇÃO 9 DO MENU
void remover_todos_os_alunos(Arvore **arv)
{
    destruir(*arv);
    *arv = criar();
    getch();
    fflush(stdin);
}

// OK // OPÇÃO 10 DO MENU
void salvar(Arvore *arv)
{
	FILE *fp = fopen("C:\\Users\\Eron\\Desktop\\CRUDArvoreAVL\\Trabalho\\alunos_salvos.txt", "w");
	char *str;
	int key, max_key;
	Aluno *aluno;

    key = menor_chave(arv);
	max_key = maior_chave(arv);

	// NÃO SEI PORQUE, MAS O LOOP SÓ ESCREVE NO ARQUIVO SE FOR ADICIONADO ALGUM CARACTERE ANTES.
	fprintf(fp, "\n");

    // ESTE FOR NÃO É EFICIENTE SE A DIFERENÇA DE VALORES DE CHAVE FOR MUITO GRANDE.
	while (key <= max_key)
	{
	    aluno = buscar(arv, key);

	    if (aluno != NULL)
	    {
	        str = aluno_to_string(aluno);
	        fprintf(fp, str);
        }
        key++;
	}

	fclose(fp);

	printf("\tArvore salva em arquivo! \n");
	getch();
	fflush(stdin);
}

// OK
int menu(Arvore *arv)
{
	system("cls");

	int opcao;

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
		"10 - Salvar alteracoes \n\t"
		"11 - Sair \n\t"); //

	printf(">> ");
	scanf("%d", &opcao);
	fflush(stdin);

	while (opcao > 11 || opcao < 1)
	{
		printf("\tSelecione uma opcao valida! \n\t");
		printf(">> ");
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
			printf("\n\tERRO NA ESTRUTURA DE SWITCH DO MENU \n\n");
			break;
	}
	return 1;
}
