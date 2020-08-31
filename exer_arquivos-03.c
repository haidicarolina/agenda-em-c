#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 30

/*
Faça um programa para manter as informações de uma agenda de contatos utilizando estruturas. O
programa deve conter um menu inicial com 5 opções: i) incluir um novo contato; ii) excluir um
contato existente; iii) alterar um contato existente; iv) listar todos os contatos cadastrados; e v)
finalizar o programa. A estrutura do contato deve conter um código de identificação, nome, e-mail e
celular. Os dados da agenda de contatos devem ser salvos em arquivo, garantindo que ao fechar o
programa, os dados serão mantidos.

~~~~~~~~~~~~ NÃO TERMINADO AINDA ~~~~~~~~~~~~

*/
void Cadastrar(char nome[BUFFER_SIZE], int tel){
    FILE *arquivo = fopen("agenda.txt","a");
    fprintf(arquivo, "%s %d\n", nome, tel);
    fclose(arquivo);
}

void Listar(){
    FILE *arquivo = fopen("agenda.txt","r");
    char nome[BUFFER_SIZE];
    int tel;
    while (!feof(arquivo))
    {
        fscanf(arquivo, "%s %d ", nome, &tel);
        printf("Nome: %s - Tel: %d\n", nome, tel);
    }
    fclose(arquivo);
}
/**< LIMPA A TELA */

void clrscr()
{
    system("@cls||clear");
}

void main() {

    int opcao;
    char nome[BUFFER_SIZE];
    int fone;

    do
    {        
        printf("\n\n\t\tMENU");
        printf("\n1 - Cadastrar");
        printf("\n2 - Listar");
        printf("\n3 - Sair");
        printf("\nOpção: ");

        scanf("%d", &opcao);
        fflush(stdin);
        clrscr();
        switch (opcao)
        {
            case 1:
                printf("\nDigite um nome: ");
                scanf("%s", nome);
                printf("\nDigite um telefone: ");
                scanf("%d", &fone);
                Cadastrar(nome, fone);
                getchar();
                clrscr();
                break;
            case 2:
                Listar();
                getchar();
                fflush(stdin);
                break;
            case 3:
                printf("\n\nFinalizando...\n\n");
                getchar();
                fflush(stdin);
                break;
            default:
                printf("opção inválida!");
                break;
        }
    } while (opcao != 3);
}
