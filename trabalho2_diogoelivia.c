//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

//Definição de constantes
#define STR_TAM 55 //Tamanho da string
#define MAX_QTD 100 //Quantidade max de livros/usuarios

//Definição de tipos
typedef char string[STR_TAM]; 

// Estrutura para cadastro de exemplares
struct exemplares {
    string titulo;
    string autor;
    string editora;
    string edicao;
    string local_publicacao;
    string palavras_chave;
    string num_paginas;
    string ano_publicacao;
    int qtd_exemplar;
    float preco;
    bool status;   
    struct exemplares *prox;
};

// Estrutura para cadastro de usuários
struct usuarios {
    int id;
    string nome;
    string endereco;
    string telefone;
    string email;
    string cpf;
    struct usuarios *prox;
};

// Estrutura para cadastro de empréstimos
struct emprestimos {
  int id_usuario;
  string livro_titulo;
  int qtd_dias;
  float vlr_atraso;
  struct emprestimos *prox;
};

typedef struct exemplares exemplares_t;
typedef struct usuarios usuarios_t;
typedef struct emprestimos emprestimos_t;

// Cabeçalho das funções
int menu();
int submenu();

// Funções para exemplares
exemplares_t *cadastrarExemplares(); //FEITO
void inserir_exemplares_lista(exemplares_t **lista, exemplares_t *novo); //FEITO
void salvar_dados_exemplares_txt(exemplares_t *lista); //FEITO
void salvar_dados_exemplares_binario(string nome, exemplares_t *lista); //FEITO
void ler_dados_exemplares_binario(string nome, exemplares_t **lista); //FEITO

// Funções para usuarios
usuarios_t *cadastrarUsuarios(int *qtd_cliente); //FEITO
void inserir_usuarios_lista(usuarios_t **lista, usuarios_t *novo); //FEITO
void salvar_dados_usuarios_txt(usuarios_t *lista); //FEITO
void salvar_dados_usuarios_binario(string nome, usuarios_t *lista); //FEITO
void ler_dados_usuarios_binario(string nome, usuarios_t **lista); //FEITO

// Funções para emprestimos
emprestimos_t *emprestimoLivro(int pos_usuario, int pos_exemplar, int qtd_dias); //
emprestimos_t *realizarEmprestimoLivro(usuarios_t *usuarios, exemplares_t *exemplares, int qtd_dias); //FEITO
void realizarDevolucaoLivro(); //
void salvar_dados_emprestimos_txt(string nome, emprestimos_t *lista); //FEITO
void salvar_dados_emprestimos_binario(string nome, emprestimos_t *lista); //FEITO
void ler_dados_emprestimos_binario(string nome, emprestimos_t **lista); //

// Funções para relatórios
void relatorioAcervo(exemplares_t *lista); //FEITO
void relatorioUsuarios(usuarios_t *lista); //FEITO
void relatorioEmprestimos(emprestimos_t *lista); //FEITO
void relatorioPendencias(); //
void relatorioLivrosEditados(); //

// Funções auxiliares
void formatar_maiuscula(string str);
void retirar_enter_string(string str);

// Função principal
int main() {
    int opcao, subopcao, subsubopcao;

    exemplares_t *lista_exemplares = NULL;
    exemplares_t *novo_exemplares = NULL;
    usuarios_t *lista_usuarios = NULL;
    usuarios_t *novo_usuarios = NULL;
    emprestimos_t *lista_emprestimos = NULL;
    emprestimos_t *novo_emprestimos = NULL;

    printf("Importando dados ...\n");
    ler_dados_exemplares_binario("exemplares.csv", &lista_exemplares);
    ler_dados_usuarios_binario("usuarios.csv", &lista_usuarios);
    ler_dados_emprestimos_binario("emprestimos.csv", &lista_emprestimos);
    printf("\n");

    do {
        opcao = menu();

        switch (opcao) {
            case 1: novo_exemplares = cadastrarExemplares();
                    inserir_exemplares_lista(&lista_exemplares, novo_exemplares);
                    break;
            case 2: novo_usuarios = cadastrarUsuarios(&lista_usuarios);
                    inserir_usuarios_lista(&lista_usuarios, novo_usuarios);
                    break;
            case 3: subsubopcao = controleEmprestimoDevolucao();
                    switch (subsubopcao) {
                        case 1: 
                                break;
                        case 2: realizarDevolucaoLivro();
                                break;
                        default: printf("Opcao invalida.\n");
                    }
                    break;
            case 4: 
                    break;
            case 5: 
                    break;
            case 6: 
                    break;
            case 7:
                subopcao = submenu();

                switch (subopcao) {
                    case 1: relatorioAcervo(lista_exemplares); 
                            break;
                    case 2: relatorioUsuarios(lista_usuarios); 
                            break;
                    case 3: relatorioEmprestimos(lista_emprestimos); 
                            break;
                    case 4: relatorioPendencias(); 
                            break;
                    case 5: relatorioLivrosEditados(); 
                            break;
                    default: printf("Opcao invalida.\n");
                }
                break;
            case 0: printf("\nSalvando dados...\n");
                    salvar_dados_exemplares_binario("exemplares.csv", lista_exemplares);
                    salvar_dados_usuarios_binario("usuarios.csv", lista_usuarios);
                    salvar_dados_emprestimos_binario("emprestimos.csv", lista_emprestimos);
                    break;
            default: printf("\nOpcao invalida!\n"); 
                    break;
        }
    } while (opcao != 0);

    return 0;
}

// Função do menu
int menu()
{
    int opc;

    printf("\nMENU INICIAL:\n");
    printf("========================\n");

    printf("1. Cadastrar novos exemplares\n");
    printf("2. Cadastrar novo usuario\n");
    printf("3. Controle de emprestimo e devolucao\n");
    printf("4. Baixa de exemplares\n");
    printf("5. Localizar exemplares por titulo, palavras-chave ou autor\n");
    printf("6. Localizacao de usuarios por nome\n");
    printf("7. Relatorios\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: \n");
    fflush(stdin);
    scanf("%i", &opc);
    getchar();

    return opc;
}

// Função do submenu
int submenu()
{
    int opc;

    printf("\nRELATORIOS:\n");
    printf("========================\n");

    printf("1. Relatorio de acervo\n");
    printf("2. Relatorio de usuarios\n");
    printf("3. Relatorio de emprestimos\n");
    printf("4. Relatorio de pendencias\n");
    printf("5. Relatorio de livros por ano\n");
    printf("Escolha uma opcao: \n");
    fflush(stdin);
    scanf("%i", &opc);
    getchar();

    return opc;
}

// Função do menu de controle de empréstimos e devoluções
int controleEmprestimoDevolucao() 
{
    int opc;

    printf("\nEMPRESTIMOS E DEVOLUCOES:\n");
    printf("========================\n");

    printf("1. Fazer emprestimos\n");
    printf("2. Fazer devolucoes\n");
    printf("Escolha uma opcao: \n");
    fflush(stdin);
    scanf("%i", &opc);

    return opc;
}

// Função para fazer emprestimos
emprestimos_t *realizarEmprestimoLivro(usuarios_t *usuarios, exemplares_t *exemplares, int qtd_dias)
{
    emprestimos_t *novo;

    novo = (emprestimos_t*)malloc(sizeof(emprestimos_t));

    strcpy(novo->livro_titulo, exemplares->titulo);
    novo->id_usuario = usuarios->id;
    novo->qtd_dias = qtd_dias;
    novo->vlr_atraso = qtd_dias * exemplares->preco;

    exemplares->status = false;  

    return novo;
}

// Função para cadastrar exemplares
exemplares_t *cadastrarExemplares() 
{
    exemplares_t *novo = (exemplares_t *)malloc(sizeof(exemplares_t));

    printf("\nCADASTRO DE EXEMPLARES:\n");
    printf("========================\n");

    printf("Titulo: ");
    fgets(novo->titulo, STR_TAM, stdin);
    retirar_enter_string(novo->titulo);
    formatar_maiuscula(novo->titulo);
    
    printf("Autor: ");
    fgets(novo->autor, STR_TAM, stdin);
    retirar_enter_string(novo->autor);
    formatar_maiuscula(novo->autor);

    printf("Editora: ");
    fgets(novo->editora, STR_TAM, stdin);
    retirar_enter_string(novo->editora);
    formatar_maiuscula(novo->editora);

    printf("Edicao: ");
    fgets(novo->edicao, STR_TAM, stdin);
    retirar_enter_string(novo->edicao);
    formatar_maiuscula(novo->edicao);

    printf("Local de publicacao: ");
    fgets(novo->local_publicacao, STR_TAM, stdin);
    retirar_enter_string(novo->local_publicacao);
    formatar_maiuscula(novo->local_publicacao);

    printf("Palavras-chave: ");
    fgets(novo->palavras_chave, STR_TAM, stdin);
    retirar_enter_string(novo->palavras_chave);
    formatar_maiuscula(novo->palavras_chave);

    printf("Numero de paginas: ");
    scanf("%i", &novo->num_paginas);

    printf("Ano de publicacao: ");
    scanf("%i", &novo->ano_publicacao);

    printf("Quantidade de exemplares: ");
    scanf("%i", &novo->qtd_exemplar);
    
    printf("Preco: ");
    scanf("%f", &novo->preco);

    novo->prox = NULL;
    return novo;
}

// Função para cadastrar usuários
usuarios_t *cadastrarUsuarios(int *qtd_cliente) 
{
    usuarios_t *novo = (usuarios_t *)malloc(sizeof(usuarios_t));

    printf("\nCADASTRO DE USUARIOS:\n");
    printf("========================\n");

    novo -> id = *qtd_cliente += 1;
    printf("ID: %i\n", novo->id);
    
    printf("Nome: ");
    fgets(novo->nome, STR_TAM, stdin);
    retirar_enter_string(novo->nome);
    formatar_maiuscula(novo->nome);

    printf("Endereco: ");
    fgets(novo->endereco, STR_TAM, stdin);
    retirar_enter_string(novo->endereco);
    formatar_maiuscula(novo->endereco);

    printf("Telefone: ");    
    scanf("%i", &novo->telefone);
    
    printf("Email: ");
    fgets(novo->email, STR_TAM, stdin);
    retirar_enter_string(novo->email);
    formatar_maiuscula(novo->email);

    printf("CPF: ");
    scanf("%i", &novo->cpf);

    novo->prox = NULL;
    return novo;
}

// Função para inserir exemplares na lista
void inserir_exemplares_lista(exemplares_t **lista, exemplares_t *novo)
{
    if (*lista == NULL) {
        *lista = novo;
    } else {
        novo->prox = *lista;
        *lista = novo;
    }
}

// Função para inserir usuários na lista
void inserir_usuarios_lista(usuarios_t **lista, usuarios_t *novo)
{
    if (*lista == NULL) {
        *lista = novo;
    } else {
        novo->prox = *lista;
        *lista = novo;
    }
}

// Função para salvar os dados de exemplares em arquivo
void salvar_dados_exemplares_txt(exemplares_t *lista) 
{
    FILE *fp = fopen("exemplares.csv", "w");

    while (lista != NULL) {
        fprintf(fp, "%s\n", lista->titulo);
        fprintf(fp, "%s\n", lista->autor);
        fprintf(fp, "%s\n", lista->editora);
        fprintf(fp, "%s\n", lista->edicao);
        fprintf(fp, "%s\n", lista->local_publicacao);
        fprintf(fp, "%s\n", lista->palavras_chave);
        fprintf(fp, "%s\n", lista->num_paginas);
        fprintf(fp, "%s\n", lista->ano_publicacao);
        fprintf(fp, "%i\n", lista->qtd_exemplar);
        fprintf(fp, "%s\n", lista->preco);
        lista = lista->prox;
    }

    fclose(fp);
    
}

void salvar_dados_exemplares_binario(string nome, exemplares_t *lista) 
{
    FILE *fp = fopen("exemplares.csv", "wb");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (lista != NULL) {
        fwrite(lista, sizeof(exemplares_t), 1, fp);
        lista = lista->prox;
    }

    fclose(fp);
    
}

// Função para salvar os dados de usuarios em arquivo
void salvar_dados_usuarios_txt(usuarios_t *lista) 
{
    FILE *fp = fopen("usuarios.csv", "w");

    while (lista != NULL) {
        fprintf(fp, "%s\n", lista->nome);
        fprintf(fp, "%s\n", lista->endereco);
        fprintf(fp, "%i\n", lista->telefone);
        fprintf(fp, "%s\n", lista->email);
        fprintf(fp, "%i\n", lista->cpf);
        lista = lista->prox;
    }

    fclose(fp);
}

void salvar_dados_usuarios_binario(string nome, usuarios_t *lista) 
{
    FILE *fp = fopen("usuarios.csv", "wb");

    while (lista != NULL) {
        fprintf(fp, "%s\n", lista->nome);
        fprintf(fp, "%s\n", lista->endereco);
        fprintf(fp, "%i\n", lista->telefone);
        fprintf(fp, "%s\n", lista->email);
        fprintf(fp, "%i\n", lista->cpf);
        lista = lista->prox;
    }

    fclose(fp);
}

// Função para salvar dados de emprestimos em arquivo
void salvar_dados_emprestimos_txt(string nome, emprestimos_t *lista) 
{
    FILE *fp = fopen("emprestimos.csv", "w");

    while (lista != NULL) {
        fprintf(fp, "%i\n", lista->id_usuario);
        fprintf(fp, "%i\n", lista->livro_titulo);
        fprintf(fp, "%s\n", lista->qtd_dias);
        fprintf(fp, "%s\n", lista->vlr_atraso);
        lista = lista->prox;
    }

    fclose(fp);

}

void salvar_dados_emprestimos_binario(string nome, emprestimos_t *lista) 
{
    FILE *fp = fopen(nome, "wb");

    while (lista!= NULL) {
        fprintf(fp, "%i\n", lista->id_usuario);
        fprintf(fp, "%i\n", lista->livro_titulo);
        fprintf(fp, "%s\n", lista->qtd_dias);
        fprintf(fp, "%s\n", lista->vlr_atraso);
        lista = lista->prox;
    }

    fclose(fp);

}

// Função para ler dados de exemplares em arquivo
void ler_dados_exemplares_binario(string nome, exemplares_t **lista)
{
  FILE *fp = fopen("exemplares.csv", "r");
  string titulo, autor, editora, edicao, local_publicacao, palavras_chave, num_paginas, ano_publicacao;
  int qtd_exemplar;
  float preco;
  exemplares_t *novo = NULL;

  if (fp == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  while (!feof(fp)) {
    fgets(titulo, STR_TAM, fp);
    retirar_enter_string(titulo);
    fgets(autor, STR_TAM, fp);
    retirar_enter_string(autor);
    fgets(editora, STR_TAM, fp);
    retirar_enter_string(editora);
    fgets(edicao, STR_TAM, fp);
    retirar_enter_string(edicao);
    fgets(local_publicacao, STR_TAM, fp);
    retirar_enter_string(local_publicacao);
    fgets(palavras_chave, STR_TAM, fp);
    retirar_enter_string(palavras_chave);
    fgets(num_paginas, STR_TAM, fp);
    retirar_enter_string(num_paginas);
    fgets(ano_publicacao, STR_TAM, fp);
    retirar_enter_string(ano_publicacao);
    fscanf(fp, "%i", &qtd_exemplar);
    fscanf(fp, "%f", &preco); 

    novo = (exemplares_t*)malloc(sizeof(exemplares_t));

    strcpy(novo->titulo, titulo);
    strcpy(novo->autor, autor);
    strcpy(novo->editora, editora);
    strcpy(novo->edicao, edicao);
    strcpy(novo->local_publicacao, local_publicacao);
    strcpy(novo->palavras_chave, palavras_chave);
    strcpy(novo->num_paginas, num_paginas);
    strcpy(novo->ano_publicacao, ano_publicacao);
    novo->qtd_exemplar = qtd_exemplar;
    novo->preco = preco;
    novo->prox = NULL;

    inserir_exemplares_lista(lista, novo);
  }

  fclose(fp);

}

// Função para ler dados de usuarios em arquivo
void ler_dados_usuarios_binario(string nome, usuarios_t **lista)
{
  FILE *fp = fopen("usuarios.csv", "r");
  int id, telefone;
  string nome, endereco, email, cpf;
  usuarios_t *novo = NULL;

  if (fp == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  while (!feof(fp)) {
    fscanf(fp, "%i", &id);
    fgets(nome, STR_TAM, fp);
    retirar_enter_string(nome);
    fgets(endereco, STR_TAM, fp);
    retirar_enter_string(endereco);
    fscanf(fp, "%i", &telefone);
    fgets(email, STR_TAM, fp);
    retirar_enter_string(email);
    fgets(cpf, STR_TAM, fp);
    retirar_enter_string(cpf);

    novo = (usuarios_t*)malloc(sizeof(usuarios_t));

    novo->id = id;
    strcpy(novo->nome, nome);
    strcpy(novo->endereco, endereco);
    strcpy(novo->telefone, telefone);
    strcpy(novo->email, email);
    strcpy(novo->cpf, cpf);
    novo->prox = NULL;

    inserir_usuarios_lista(lista, novo);
  }

  fclose(fp);

}

void ler_dados_emprestimos_binario(string nome, emprestimos_t **lista)
{
    FILE *fp = fopen("emprestimos.csv", "r");
}

// Funções de relatório
void relatorioAcervo(exemplares_t *lista)
{
    exemplares_t *aux = lista;

  while (aux != NULL) {
    printf("Titulo: %s\n", aux->titulo);
    printf("Autor: %s\n", aux->autor);
    printf("Editora: %s\n", aux->editora);
    printf("Edicao: %s\n", aux->edicao);
    printf("Local de publicacao: %s\n", aux->local_publicacao);
    printf("Palavras-chave: %s\n", aux->palavras_chave);
    printf("Numero de paginas: %i\n", aux->num_paginas);
    printf("Ano de publicacao: %i\n", aux->ano_publicacao);
    printf("Quantidade: %i\n", aux->qtd_exemplar);
    printf("Preco: %.2f\n", aux->preco);
    aux = aux->prox;
  }
}
void relatorioUsuarios(usuarios_t *lista)
{
    usuarios_t *aux = lista;

  while (aux != NULL) {
    printf("ID: %i\n", aux->id);
    printf("Nome: %s\n", aux->nome);
    printf("Endereco: %s\n", aux->endereco);
    printf("Telefone: %i\n", aux->telefone);
    printf("Email: %s\n", aux->email);
    printf("CPF: %i\n", aux->cpf);
    aux = aux->prox;
  }
}
void relatorioEmprestimos(emprestimos_t *lista)
{
    while (lista) {
        printf("Livro: %s\n", lista->livro_titulo);
        printf("ID do usuario: %s\n", lista->id_usuario);
        printf("Quantidade de dias emprestados: %s\n", lista->qtd_dias);
        printf("Valor do emprestimo: %.2f\n", lista->vlr_atraso);
        lista = lista->prox;
    }
}

// Função para formatação (não obrigatório)
void formatar_maiuscula(string str)
{
    int i;

    for (i = 0; i < strlen(str); i++) {
        str[i] = toupper(str[i]);
    }
}

// Função para retirar o enter da string (não obrigatório)
void retirar_enter_string(string str)
{
    int tamanho;

    tamanho = strlen(str);

    str[tamanho - 1] = '\0';
}