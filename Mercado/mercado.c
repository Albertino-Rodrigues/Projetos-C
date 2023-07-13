#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

typedef struct{
    int codigo;
    char nome[30];
    float preco;
}Produto;

typedef struct{
    Produto produto;
    int quantidade;
}Carrinho;

void inforProduto(Produto prod);
void menu();
void cadastrarProduto();
void listarProdutos();
void comprarProduto();
void visualizarCarrinho();
Produto pegarProdutoPorCodigo(int codigo);
int * temNoCarrinho(int codigo);
void fecharPedido();

static int contador_produto = 0;
static int contador_carrinho = 0;
static Carrinho carrinho[50];
static Produto produtos[50];

int main(){

    setlocale(LC_ALL, "Portuguese");

    menu();

    return 0;
}

void infoProduto(Produto prod){
    printf("Código: %d \nNome: %s \nPreço: %.2f\n", prod.codigo, strtok(prod.nome, "\n"), prod.preco);
}

void menu(){

    system("cls");

    printf("==============================================\n");
    printf("================Bem-vindo(a)==================\n");
    printf("==================Loja GCC====================\n");
    printf("==============================================\n\n");

    printf("Selecione uma opção abaixo: \n");
    printf("1 - Cadastrar produto\n2 - Listar produtos\n3 - Comprar produto\n4 - Visualizar carrinho\n5 - Fechar pedido\n6 - Sair do sistema\n");
    int opcao;
    scanf("%d", &opcao);
    getchar();

    switch (opcao)
    {
    case 1:
        system("cls");
        fflush(stdin);
        cadastrarProduto();
        break;   
    case 2:
        system("cls");
        fflush(stdin);
        listarProdutos();
        break;
    case 3:
        system("cls");
        fflush(stdin);
        comprarProduto();
        break;
    case 4:
        system("cls");
        fflush(stdin);
        visualizarCarrinho();
        break;
    case 5:
        system("cls");
        fflush(stdin);
        fecharPedido();
        break;
    case 6:
        printf("Volte sempre!\n");
        Sleep(2);
        exit(0);
    default:
        printf("Opção inválida!\n");
        Sleep(2);
        menu();
        break;
    }
};

void cadastrarProduto(){
    printf("Cadastro de produto\n");
    printf("=====================\n");

    printf("Informe o nome do produto\n");
    fgets(produtos[contador_produto].nome, 30, stdin);

    printf("Informe o preço do produto: \n");
    scanf("%f", &produtos[contador_produto].preco);

    printf("O produto %s foi cadastrado com sucesso.\n", strtok(produtos[contador_produto].nome, "\n"));

    produtos[contador_produto].codigo = (contador_produto + 1);
    contador_produto++;

    Sleep(2000);
    system("cls");
    fflush(stdin);
    menu();
};

void listarProdutos(){
    if(contador_produto > 0){
        printf("Listagem de produtos.\n");
        printf("---------------------------\n");
        for(int i = 0; i < contador_produto; i++){
            infoProduto(produtos[i]);
            printf("----------------\n");
            Sleep(1000);
        }
        Sleep(2000);
        system("cls");
        fflush(stdin);
        menu();
    }
    else{
        printf("Não há produtos cadastrados.\n");
        Sleep(2000);
        system("cls");
        fflush(stdin);
        menu();
    }
};

void comprarProduto(){
    if(contador_produto > 0){
        printf("Infome o código do produto que deseja adicionar ao carrinho.\n");

        printf("=====================Produtos disponíveis=====================\n");
        for(int i = 0; i < contador_produto; i++){
            infoProduto(produtos[i]);
            printf("---------------------------------\n");
            Sleep(1000);
        }
        int codigo;
        scanf("%d", &codigo);
        getchar();

        int tem_mercado = 0;
        for(int i = 0; i < contador_produto; i++){
            if(produtos[i].codigo == codigo){
                tem_mercado = 0;
                int posicao_no_carrinho = -1;

                if(contador_carrinho > 0){
                    int * retorno = temNoCarrinho(codigo);

                    for (int i = 0; i < contador_carrinho; i++)
                    {
                        if (carrinho[i].produto.codigo == codigo)
                        {
                            tem_mercado = 1;
                            posicao_no_carrinho = i;
                            break; 
                        }
                    }

                    if (tem_mercado)
                    {
                        carrinho[posicao_no_carrinho].quantidade++;
                        printf("Aumentei a quantidade do produto %s já existente no carrinho.\n",
                               strtok(carrinho[posicao_no_carrinho].produto.nome, "\n"));
                        Sleep(2000);
                        system("cls");
                        menu();
                    }
                    else
                    {
                        Produto p = pegarProdutoPorCodigo(codigo);
                        carrinho[contador_carrinho].produto = p;
                        carrinho[contador_carrinho].quantidade = 1;
                        contador_carrinho ++;
                        printf("O produto %s foi adicionado ao carrinho.\n", strtok(p.nome, "\n"));
                        Sleep(2000);
                        system("cls");
                        menu();
                    }
                }else{
                    Produto p = pegarProdutoPorCodigo(codigo);
                    carrinho[contador_carrinho].produto = p;
                    carrinho[contador_carrinho].quantidade = 1;
                    contador_carrinho ++;
                    printf("O produto %s foi adicionado ao carrinho.\n", strtok(p.nome, "\n"));
                    Sleep(2000);
                    system("cls");
                    menu();
                }
            }
        }
        if(tem_mercado < 1){
            printf("Não foi encontrado o produto com o código %d.\n", codigo);
            Sleep(2000);
            system("cls");
            menu();
        }

    }else{
        printf("Ainda não existem produtos para vender.\n");
        Sleep(2000);
        system("cls");
        menu();
    }

};

void visualizarCarrinho(){
    if(contador_carrinho > 0){
        printf("Produtos do Carrinho:\n");
        printf("--------------------------------\n");
        for(int i  = 0; i < contador_carrinho; i++){
            infoProduto(carrinho[i].produto);
            printf("Quantidade: %d\n", carrinho[i].quantidade);
            printf("-------------------------------\n");
            Sleep(1000);
        }
        system("cls");
        menu();
    }else{
        printf("Não há produtos no carrinho.\n");
        Sleep(2000);
        system("cls");
        fflush(stdin);
        menu();
    }
};

Produto pegarProdutoPorCodigo(int codigo){
    Produto p;
    for(int i = 0; i < contador_produto; i++){
        if(produtos[i].codigo == codigo){
            p = produtos[i];
        }

    }
    return p;
};

int * temNoCarrinho(int codigo){
    int static retorno[] = {0, 0};
    for(int i = 0; i < contador_carrinho; i++){
        if(carrinho[i].produto.codigo == codigo){
            retorno[0] = 1;
            retorno[1] = i;
        }
    }
    return retorno;
};

void fecharPedido(){
    if(contador_carrinho > 0){
        float valorTotal = 0.0;
        printf("Produtos do Carrinho\n");
        printf("----------------------\n");
        for(int i = 0; i < contador_carrinho; i++){
            Produto p = carrinho[i].produto;
            int quantidade = carrinho[i].quantidade;
            valorTotal += p.preco * quantidade;
            infoProduto(p);
            printf("Quantidade: %d\n", quantidade);
            printf("-----------------------------\n");
            Sleep(1000);
        }
        printf("Sua fatura total é R$: %.2f\n", valorTotal);

        contador_carrinho = 0;
        printf("Obrigado pela preferência.\n");
        Sleep(3000);
        system("cls");
        fflush(stdin);
        menu();
    }else{
        printf("Você não tem nenhum produto no carrinho.\n");
        Sleep(2000);
        system("cls");
        fflush(stdin);
        menu();
    }
};
