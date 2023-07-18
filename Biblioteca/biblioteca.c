#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <time.h>

#define TRIES 3

void senha();
void cabecalho();
void menu();
int addLivro();
void verLivros();
int procurarLivro();
int editarLivro();
void deletarLivro();
void ajuda();
void sair();

struct INFO_LIVRO
{

    int ID;
    char Nome[30];
    char Autor[30];
    int Quant;
    int PratNum;

}add;


FILE *fp;
FILE *file2;


int main()
{
	senha();

}

void cabecalho()
{   
    system("cls");
    printf("\n\n\t===========Gerenciamento de Biblioteca==========\n\n");
}

void senha(){

    cabecalho();

    int i = 1;
    char pass[] = "Albertino";
    char ch[10];

    printf("\tDigite a Senha: \n");

    gets(ch);

    while(strcmp(ch, pass) != 0)
    {

        i++;

        if(i > TRIES){

            printf("Você excedeu a quantidade de tentativas!\n");
            Sleep(2000);
            exit(0);
        }

        if(i == 3){
            printf("\n\tUltima tentativa!\n\n");
        }

        printf("\tTente novamente\n");
        gets(ch);
    }

    printf("\n\nSessao iniciada\n\n"
           "Pressione uma tecla para continuar\n");
    
    getchar();

    //Menu Principal
    menu();

}

void menu()
{
    int choice = 0;
    system ("cls");

        printf("============Menu Principal==============\n\n");
        printf("1 - Adicionar um livro\n"
               "2 - Verificar a lista de livros\n"
               "3 - Procurar um livro na biblioteca\n"
               "4 - Editar a lista de livros\n"
               "5 - Deletar um livro da lista\n"
               "6 - Ajuda\n"
               "7 - Sair\n\n");
        printf("========================================\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &choice);
        getchar();

        switch(choice)
        {

            case 1:
            addLivro();
            break;

            case 2:
            verLivros();
            break;

            case 3:
            procurarLivro();
            break;

            case 4:
            editarLivro();
            break;

            case 5:
            deletarLivro();

            case 6:
            ajuda();
            break;

            case 7:
            sair();
            break;

            default:
            printf("Selecione uma das opções do menu!\n");
            Sleep(1000);
            menu();
            break;
                
        }
       
}

int addLivro()
{
    system("cls");

    printf("==============Informações do Livro ============\n\n");

    int id;

    fp = fopen("livros.txt", "ab+");

    printf("Digite o código identificador: ");
    fflush(stdin);
    scanf("%d", &id);

    rewind(fp);

    while (fread(&add, sizeof(add), 1, fp) == 1)
    {
        if (id == add.ID)
        {
            printf("\nEsse livro já está disponivel na biblioteca\n\n");

            printf("Nome: %s\n", add.Nome);
            printf("Autor: %s\n", add.Autor);
            printf("Quantidade: %d\n", add.Quant);
            printf("Estante: %d\n\n", add.PratNum);
                
            printf("\nPressione qualquer tecla!\n");
            getchar();

            fclose(fp);

            return 0;
        }
        
    }

    add.ID = id;

    printf("Digite o nome: ");
    fflush(stdin);
    scanf("%s", add.Nome);
    
    printf("Digite o Autor: ");
    fflush(stdin);
    scanf("%s", add.Autor);

    printf("Digite a quantidade: ");
    fflush(stdin);
    scanf("%d", &add.Quant);

    printf("Digite o numero da estante: ");
    fflush(stdin);
    scanf("%d", &add.PratNum);

    fseek(fp, 0, SEEK_END);
    fwrite(&add, sizeof(add), 1, fp);

    fclose(fp);

    printf("Livro Adicionado!\n\n");

    menu();

    return 0;
}

void verLivros(){

    system("cls");

    printf("\n\n================ Ver Livros ===============\n\n");

    int i = 0;

    printf("Ind\tNome\tAutor\tQuantidade\tEstante\n\n\n");

    fp = fopen("livros.txt", "rb");

    while (fread(&add, sizeof(add), 1, fp) == 1)
    {

        printf("%d", add.ID);
        printf("\t%s", add.Nome);
        printf("\t%s", add.Autor);
        printf("\t%d", add.Quant);
        printf("\t\t%d\n", add.PratNum);

        i = i + add.Quant;
    }

    fclose(fp);

    printf("\n\nTotal de livros na livraria: %d\n", i);

    printf("\nPressione qualquer tecla\n");

    getchar();

    menu();
}

int procurarLivro()
{
    
    int id; 
    system("cls");
    printf("============== Procurar Livros =============\n\n");

    fp = fopen("livros.txt", "rb");

    printf("Digite o código identificador: ");
    scanf("%d", &id);
    getchar();

    while (fread(&add, sizeof(add), 1, fp) == 1)
    {

        if (id == add.ID)
        {

            printf("\nLivro encontrado!\n");
            printf("Código de identificação: %d\n", add.ID);
            printf("Nome: %s\n", add.Nome);
            printf("Autor: %s\n", add.Autor);
            printf("Quantidade: %d\n", add.Quant);
            printf("Estante: %d\n\n", add.PratNum);
            
            printf("\nPressione qualquer tecla!\n");
            getchar();

            menu();
        }
    }

    printf("Identificação nao encontada\n");
    printf("\nPressione qualquer tecla!\n");
    getchar();

    menu();
}

int editarLivro()
{

    int id;
    system ("cls");

    printf("================== Editar Livro ==================\n\n");

    fp = fopen("livros.txt", "rb+");

    printf("Digite o  código de identificação: ");
    scanf("%d", &id);
    getchar();

    while(fread(&add, sizeof(add), 1, fp) == 1)
    {
        if (id == add.ID)
        {
            printf("Código encontrado!\n\n");

            printf("ID: %d\n", add.ID);

            printf("Digite o novo nome: ");
            scanf("%s", add.Nome);
            printf("Digite o novo autor: ");
            scanf("%s", add.Autor);
            printf("Digite a nova quantidade: ");
            scanf("%d", &add.Quant);
            getchar();
            printf("Digite a nova numeração da estante: ");
            scanf("%d", &add.PratNum);
            getchar();

            fseek(fp, ftell(fp) - sizeof(add), 0);
            fwrite(&add, sizeof(add), 1, fp);

            fclose(fp);

            printf("\nLivro alterado com sucesso!\n\n");

            printf("\nPressione qualquer tecla!\n");

            getchar();
            menu();
        }
    }

    printf("\nCódigo nao encontrado!\n");
    printf("\nPressione qualquer tecla!\n");
    getchar();

    menu();
}

void deletarLivro()
{
    int id, i = 0;

    system("cls");
    printf("=============== Deletar Livros =============\n\n");

    printf("Digite o código do livro: ");
    scanf("%d", &id);
    getchar();

    fp = fopen("livros.txt", "rb+");

    rewind(fp);

    while(fread(&add, sizeof(add), 1, fp) == 1)
    {
        if (id == add.ID)
        {
            printf("\nO livro está disponível\n\n");
            printf("Nome do livro: %s\n", add.Nome);
            printf("Número da estante: %d\n", add.PratNum);
            
            i++;
        }
    }
    
    if (i == 0){

    	printf("\nLivro não encontrado!\n");

        printf("\nPressione qualquer tecla");

        getchar();

        menu();
    	
	}
	else
	{
		file2 = fopen("texto.txt", "wb+");
		
		rewind(fp);
		
		while (fread(&add, sizeof(add), 1, fp) == 1){
			if (id != add.ID){
				fseek(file2, ftell(file2) - sizeof(add), 0);
				fwrite(&add, sizeof(add), 1, file2);
			}
		}
		fclose(fp);
		fclose(file2);
		
		remove("livros.txt");
		rename("texto.txt", "livros.txt");
		
		fp = fopen("livros.txt", "rb");
		fclose(fp);
	}
	printf("\nPressione qualquer tecla\n");
	getchar();
	
}

void ajuda(){
	system("cls");
	
	printf("\n\n");
	printf("Esse e um projeto simples de uma biblioteca.");
	printf("A senha é ""Albertino""\n");
	printf("Voce pode adicionar livros, editar e deletar\n\n");
}

void sair(){
	printf("\nObrigado pela sua visita!\n\n");
	Sleep(2000);
    exit(0);
}
