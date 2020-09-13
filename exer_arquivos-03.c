#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

typedef struct contato {
    int codigo;
    int ativo;
    char nome [BUFFER_SIZE];
    char email [BUFFER_SIZE];
    char celular [BUFFER_SIZE];
} Contato;

Contato contato;
Contato contatos[BUFFER_SIZE];

void incluirContato();
void listarContato();
void excluirContato();
void alterarContato();
int finalizar();
void clrscr();
int proximoId();
void entradaDados();
void fileInToArray();

/*
    Function: main() 
    Description:  Chama todas as funções do programa Agenda de Contatos
*/
void main() {
    int opcao;
    char userInput[BUFFER_SIZE];

    do {        
        printf("\n\n\t\tMENU");
        printf("\n1 - Incluir");
        printf("\n2 - Excluir");
        printf("\n3 - Alterar");
        printf("\n4 - Listar");
        printf("\n5 - Finalizar");
        printf("\nOpção: ");
        sscanf(fgets(userInput, BUFFER_SIZE-1, stdin),"%d", &opcao);
        getchar();
        fflush(stdin);
        fileInToArray();
        clrscr();
        switch (opcao) {
            case 1:
                fflush(stdin);
                printf("\nopcao: %d", opcao);
                entradaDados();
                incluirContato(contato.nome, contato.celular, contato.email);
                clrscr();
                break;
            case 2:
                clrscr();
                excluirContato();
                getchar();
                fflush(stdin);
                break;
            case 3:
                clrscr();
                alterarContato();
                break;
            case 4:
                clrscr();
                listarContato();
                break;
            case 5:
                clrscr();
                finalizar();
                break;
            default:
                printf("opção inválida!");
                break;
        }
    } while (opcao != 5);
}

/*
    Function: incluirContato(args)
    Args:   char nome
            char tel
            char email
    Description: escreverá no final do arquivo os inputs
*/
void incluirContato(char nome[BUFFER_SIZE],char tel[BUFFER_SIZE],char email[BUFFER_SIZE]){
    int id = proximoId();
    FILE *agenda = fopen("agenda.txt","a");
    fprintf(agenda, "%d;%d;%s;%s;%s\n", id, 1, nome, tel, email);
    fclose(agenda);
}

/*
    Function: listarContato
    Description: imprimirá em tela todos as linhas que estiverem Ativo = 1
*/
void listarContato(){
    fflush(stdin);
    FILE *arquivo = fopen("agenda.txt","r");
    char str[128];
    int result;
    char nome[BUFFER_SIZE];
    char tel[BUFFER_SIZE];
    char email[BUFFER_SIZE];
    int id, del, i = 0;
    int tamanho = proximoId();

    printf("\t--------------------------------------------------------\n");
    printf("\t------------------------CONTATOS------------------------\n");
    printf("\t--------------------------------------------------------\n\n");

    printf("  ID\t\t\tNOME\t\t\t\tTELEFONE\t\tEMAIL\n\n");

    for (int j = 0; j < tamanho-1; j++)
    {
        if (contatos[i].ativo != 0)
        {
            printf("%2d", contatos[i].codigo);
            printf(" %40s", contatos[i].nome);
            printf(" %24s", contatos[i].celular);
            printf(" %30s", contatos[i].email);
        }
        i++;
    }

    fclose(arquivo);
    getchar();
}

/*
    Function: finalizar
    Description: encerra o programa
*/
int finalizar(){
    clrscr();
    printf("--------------------------------------------------------\n");
    printf("--------------------FINALIZANDO PROGRAMA----------------\n");
    printf("--------------------------------------------------------\n\n");
    getchar();
    return 0;
}

/*
    Function: excluirContato
    Description: altera campo Ativo para 0 (dados persistem no banco de dados)
*/
void excluirContato (){
    FILE *arquivo = fopen("agenda.txt","r");
    FILE *copia = fopen("copia.txt","a");
    int opcao = 0, i = 0;
    int tamanho = proximoId();
    clrscr();
    printf("--------------------------------------------------------\n");
    printf("--------------------EXCLUIR CONTATO---------------------\n");
    printf("--------------------------------------------------------\n\n");
    listarContato();
    printf("\n\n\t\tEscolha o contato a ser excluído pelo seu id\n");
    printf("\nOpção: ");
    
    scanf("%d", &opcao);

    for (int j = 0; j < tamanho-1; j++)
    {
        if (opcao != contatos[i].codigo)
        {
            fprintf(copia, "%d;%d;%s;%s;%s", contatos[i].codigo, contatos[i].ativo, contatos[i].nome, contatos[i].celular, contatos[i].email);
        }else
        {
            fprintf(copia, "%d;%d;%s;%s;%s", contatos[i].codigo, 0, contatos[i].nome, contatos[i].celular, contatos[i].email);
        }
        i++;
    }
    fclose(arquivo);
    fclose(copia);
    remove("agenda.txt");
    rename("copia.txt", "agenda.txt");

}

/*
    Function: fileInToArray
    Description: cria vetor com os dados para facilitar manipulação das demais funções
*/
void fileInToArray (){
    FILE *arquivo = fopen("agenda.txt","r");

    if (!arquivo)
    {
        printf("nao foi possível abrir o arquivo!");
        exit(0);
    }

    char buff[1024];
    int row_count = 0;
    int filed_count = 0;

    int i = 0;
    while (fgets(buff, 1023, arquivo))
    {
        filed_count = 0;
        row_count++;
        char *field = strtok(buff, ";");
        while (field)
        {
            if(filed_count == 0) contatos[i].codigo = atoi(field);
            if(filed_count == 1) contatos[i].ativo = atoi(field);
            if(filed_count == 2) strcpy(contatos[i].nome, field);
            if(filed_count == 3) strcpy(contatos[i].celular, field);
            if(filed_count == 4) strcpy(contatos[i].email, field);

            field = strtok(NULL, ";");
            filed_count++;
        }
        i++;
    }
    
    fclose(arquivo);
}

/*
    Function: alterarContato
    Description: pesquisa e altera dados pelo ID informado
*/
void alterarContato (){
    FILE *arquivo = fopen("agenda.txt","r");
    FILE *copia = fopen("copia.txt","a");
    char userInput[BUFFER_SIZE], nome[BUFFER_SIZE], tel[BUFFER_SIZE], email[BUFFER_SIZE];
    int opcao = 0, i = 0;
    int tamanho = proximoId();
    clrscr();
    printf("--------------------------------------------------------\n");
    printf("---------------------EDITAR CONTATO---------------------\n");
    printf("--------------------------------------------------------\n\n");
    listarContato();
    printf("\n\n\t\tEscolha o contato a ser editado pelo seu id\n");
    printf("\nID do contato: ");
    
    sscanf(fgets(userInput, BUFFER_SIZE-1, stdin),"%d", &opcao);
    fflush(stdin);

    for (int j = 0; j < tamanho-1; j++)
    {
        if (opcao != contatos[j].codigo)
        {
            fprintf(copia, "%d;%d;%s;%s;%s", contatos[j].codigo, contatos[j].ativo, contatos[j].nome, contatos[j].celular, contatos[j].email);
        }else
        {
            printf("\n\tDados do contato\n");
            printf("\tID: %d\n", contatos[j].codigo);
            printf("\tNome: %s\n", contatos[j].nome);
            printf("\tCelular: %s\n", contatos[j].celular);
            printf("\tEmail: %s\n", contatos[j].email);
            printf("\t ---- Altere seu contato. ----\n");
            printf("\t ---- Alterar um contato inativo o tornará ativo. ----\n");
            printf("\nDigite um nome: ");
            sscanf(fgets(userInput, BUFFER_SIZE-1, stdin),"%[^\n]", nome);
            fflush(stdin);
            printf("\nDigite um telefone: ");
            sscanf(fgets(userInput, BUFFER_SIZE-1, stdin),"%[^\n]", tel);
            fflush(stdin);
            printf("\nDigite um email: ");
            sscanf(fgets(userInput, BUFFER_SIZE-1, stdin),"%[^\n]", email);
            fflush(stdin);
            fprintf(copia, "%d;%d;%s;%s;%s\n", contatos[j].codigo, 1, nome, tel, email);
        }
    }
    fclose(arquivo);
    fclose(copia);
    remove("agenda.txt");
    rename("copia.txt", "agenda.txt");

}

/*
    Function: proximoId
    Description: verifica qual próximo ID possível / quantas linhas tem o arquivo .txt
*/
int proximoId(){
    FILE *arquivo = fopen("agenda.txt","r");
    char c, letra = '\n';
    int vezes = 1;
    while(fread (&c, sizeof(char), 1, arquivo)) {
        if(c == letra) {
            vezes++;
        }
    }
    fclose(arquivo);
    return vezes;
}

/*
    Function: clrscr
    Description: limpa a tela
*/
void clrscr()
{
    system("@cls||clear");
}

/*
    Function: entradaDados
    Description: capta dados do stdin e valida alguns possíveis erros.
*/
void entradaDados(){
    char userInput[BUFFER_SIZE], tmpEmail[BUFFER_SIZE];
    int condSaidaWhile = 1;
    printf("\nDigite um nome: ");
    sscanf(fgets(userInput, BUFFER_SIZE-1, stdin),"%[^\n]", contato.nome);
    printf("\nDigite um telefone: ");
    sscanf(fgets(userInput, BUFFER_SIZE-1, stdin),"%[^\n]", contato.celular);
    while (condSaidaWhile)
    { 
        printf("\nDigite um email: ");
        sscanf(fgets(userInput, BUFFER_SIZE-1, stdin),"%[^\n]", tmpEmail);
            int tam=strlen(tmpEmail);
            int arroba = 0, ponto = 0, antesPonto = 0, depoisPonto = 0, i;
            
            for (i = 0; i < tam; i++) {
                char c = tmpEmail[i];
                if(c == '@') {
                if (arroba)
                    break; // não pode ter uma segunda @
                arroba = 1;
                if (i < 3)
                    break; // se @ vier antes de 3 caracteres, erro
                }
                else if (arroba) { // se já encontrou @
                if (ponto) { // se já encontrou . depois de @
                    depoisPonto++;
                }
                else if(c == '.') {
                    ponto = 1;
                    if (antesPonto < 3) {
                    break; // se . depois de @ vier antes de 3 caracteres, erro
                    }
                }
                else {
                    antesPonto++;
                }
                }
            } // for
            
            if (i == tam && depoisPonto > 1){
                strcpy(contato.email,tmpEmail);
                printf("Valido");
                break;
            }
            else{
                printf("Invalido");
            }
    }

    fflush(stdin);
 }
 