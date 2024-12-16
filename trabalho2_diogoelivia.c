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
void salvar_dados_exemplares_binario(string nome, exemplares_t *lista); //FEITO
void ler_dados_exemplares_binario(string nome, exemplares_t **lista); //FEITO
exemplares_t* localizar_exemplares(exemplares_t *lista, string chave); //FEITO
exemplares_t* localizar_exemplares_titulo(exemplares_t *lista, string titulo); //FEITO
void baixar_exemplares(exemplares_t *lista, string titulo) ; //FEITO
void mostrar_dados_exemplares(exemplares_t *lista); //FEITO

// Funções para usuarios
usuarios_t *cadastrarUsuarios(int *qtd_cliente); //FEITO
void inserir_usuarios_lista(usuarios_t **lista, usuarios_t *novo); //FEITO
void salvar_dados_usuarios_binario(string nome, usuarios_t *lista); //FEITO
void ler_dados_usuarios_binario(string nome, usuarios_t **lista); //FEITO
usuarios_t* localizar_usuarios(usuarios_t *lista, string nome); //FEITO
void mostrar_dados_usuarios(usuarios_t *lista); //FEITO

// Funções para emprestimos
emprestimos_t *emprestimoLivro(int pos_usuario, int pos_exemplar, int qtd_dias); //
emprestimos_t *realizarEmprestimoLivro(usuarios_t *usuarios, exemplares_t *exemplares, int qtd_dias); //FEITO
void inserir_emprestimos_lista(emprestimos_t **lista, emprestimos_t *novo); //FEITO
void realizarDevolucaoLivro(usuarios_t *usuario, exemplares_t *exemplar, int dias_realizados, int dias_permitidos); //
int menuEmprestimoDevolucao(); // FEITO
void salvar_dados_emprestimos_binario(string nome, emprestimos_t *lista); //FEITO
void ler_dados_emprestimos_binario(string nome, emprestimos_t **lista); //FEITO

// Funções para relatórios
void relatorioAcervo(exemplares_t *lista); //FEITO
void relatorioAcervo_txt(exemplares_t *lista, string nome); //FEITO
void relatorioUsuarios(usuarios_t *lista); //FEITO
void relatorioUsuarios_txt(usuarios_t *lista, string nome); //FEITO
void relatorioEmprestimos(emprestimos_t *lista_emprestimos, usuarios_t *lista_usuarios); //FEITO
void relatorioEmprestimos_txt(emprestimos_t *lista_emprestimos, string nome, usuarios_t *lista_usuarios); //FEITO
void relatorioPendencias(emprestimos_t *lista_emprestimos, usuarios_t *lista_usuarios); //FEITO
void relatorioPendencias_txt(emprestimos_t *lista_emprestimos, string nome, usuarios_t *lista_usuarios); //FEITO
void relatorioLivrosEditados(exemplares_t *lista); //FEITO
void relatorioLivrosEditados_txt(exemplares_t *lista, string nome); //FEITO

// Funções auxiliares
void formatar_maiuscula(string str);
void retirar_enter_string(string str);

// Função principal
int main() {
    int opcao, subopcao, subsubopcao, qtd_cliente = 0, qtd_dias = 0, dias_realizados = 0, dias_permitidos = 0;
    string nome_arq, nome, titulo, autor, chave;

    exemplares_t *lista_exemplares = NULL, *livro;
    usuarios_t *lista_usuarios = NULL, *usuario;
    emprestimos_t *lista_emprestimos = NULL;

    printf("Importando dados ...\n");
    ler_dados_exemplares_binario("exemplares.bin", &lista_exemplares);
    ler_dados_usuarios_binario("usuarios.bin", &lista_usuarios);
    ler_dados_emprestimos_binario("emprestimos.bin", &lista_emprestimos);
    printf("\n");

    do {
        opcao = menu();

        switch (opcao) {
            case 1: inserir_exemplares_lista(&lista_exemplares, cadastrarExemplares());
                    break;
            case 2: inserir_usuarios_lista(&lista_usuarios, cadastrarUsuarios(&qtd_cliente));
                    break;
            case 3: subsubopcao = menuEmprestimoDevolucao();
                    switch (subsubopcao) {
                    case 1: getchar();
                            printf("Qual livro sera emprestado?\n");
                            fgets(titulo, STR_TAM, stdin);
                            retirar_enter_string(titulo);
                            formatar_maiuscula(titulo);

                            livro = localizar_exemplares_titulo(lista_exemplares, titulo);    
                            if (!livro) {
                                printf("O livro %s nao existe!\n", titulo);  
                            } else {
                                if (livro->status == true) {  
                                    printf("Qual o nome do usuario?\n");
                                    fgets(nome, STR_TAM, stdin);
                                    retirar_enter_string(nome);
                                    formatar_maiuscula(nome);

                                    usuario = localizar_usuarios(lista_usuarios, nome);  

                                    if (!usuario) {
                                        printf("O usuario %s nao existe!\n", nome);
                                        break;
                                    } else {
                                        printf("Quantos dias sera emprestado?\n");
                                        scanf("%d", &qtd_dias);
                                        getchar();  

                                        inserir_emprestimos_lista(&lista_emprestimos, realizarEmprestimoLivro(usuario, livro, qtd_dias));
                                    }
                                } else {
                                    printf("O livro %s nao esta disponivel!\n", titulo);
                                    break;  
                                }
                            }
                            break;
                    case 2: getchar();
                            printf("Qual livro sera devolvido?\n");
                            fgets(chave, STR_TAM, stdin);
                            retirar_enter_string(chave);
                            formatar_maiuscula(chave);

                            livro = localizar_exemplares(lista_exemplares, chave);
                            if (!livro) {
                                printf("O livro %s nao existe!\n", chave);  
                            } else {
                                printf("Qual o nome do usuario?\n");
                                fgets(nome, STR_TAM, stdin);
                                retirar_enter_string(nome);
                                formatar_maiuscula(nome);

                                usuario = localizar_usuarios(lista_usuarios, nome);

                                if (!usuario) {
                                    printf("O usuario %s nao existe!\n", nome);
                                    break;
                                } else {
                                    printf("Quantos dias foi emprestado (tempo permitido)?\n");
                                    scanf("%d", &dias_permitidos);
                                    getchar();  
                                    printf("Quantos dias o livro ficou com o usuario?\n");
                                    scanf("%d", &dias_realizados);
                                    getchar();  

                                    if (dias_realizados <= 0 || dias_permitidos <= 0) {
                                        printf("Erro: os valores de dias devem ser maiores que zero.\n");
                                        break;
                                    }

                                    realizarDevolucaoLivro(usuario, livro, dias_realizados, dias_permitidos);
                                    printf("Livro devolvido com sucesso!\n");
                                }
                            }
                            break;
                    default:
                        printf("Opcao invalida.\n");
                }
                break;
            case 4: printf("\nQual o titulo do livro para dar baixa?\n");
                    fgets(titulo, STR_TAM, stdin);
                    retirar_enter_string(titulo);
                    formatar_maiuscula(titulo);

                    livro = localizar_exemplares_titulo(lista_exemplares, titulo);

                    if (!livro) {
                        printf("O livro %s nao existe!\n", titulo);  
                    } else {
                        baixar_exemplares(livro, titulo);
                    }
                    break;
                    break;
            case 5: printf("Digite o criterio de busca (titulo, palavras-chave ou autor):\n");
                    fgets(chave, STR_TAM, stdin);
                    retirar_enter_string(chave);
                    formatar_maiuscula(chave);
                    
                    livro = localizar_exemplares(lista_exemplares, chave);

                    if (!livro) {
                        printf("O livro com o criterio %s nao existe!\n", chave);
                    } else {
                        mostrar_dados_exemplares(livro);
                    }
                    break;
            case 6: printf("Qual o nome do usuario?\n");
                    fgets(nome, STR_TAM, stdin);
                    retirar_enter_string(nome);
                    formatar_maiuscula(nome);

                    usuario = localizar_usuarios(lista_usuarios, nome);

                    if (!usuario) {
                        printf("O usuario %s nao existe!\n", nome);
                    } else {
                        mostrar_dados_usuarios(usuario);
                    }      
                break;
            case 7:
                subopcao = submenu();

                switch (subopcao) {

                    case 1: printf("1 - Mostrar relatorio na tela\n");
                            printf("2 - Exportar relatorio em arquivo\n");
                            scanf("%d", &subsubopcao);
                            getchar();
                            if (subsubopcao == true) {
                                relatorioAcervo(lista_exemplares); 
                            } else if (subsubopcao == 2) {
                                printf("Qual o nome do arquivo?\n");
                                fgets(nome_arq, STR_TAM, stdin);
                                retirar_enter_string(nome_arq);
                                relatorioAcervo_txt(lista_exemplares, nome_arq);
                            } else printf("Opcao invalida.\n");
                            break;
                    case 2: printf("1 - Mostrar relatorio na tela\n");
                            printf("2 - Exportar relatorio em arquivo\n");
                            scanf("%d", &subsubopcao);
                            getchar();
                            if (subsubopcao == true) {
                                relatorioUsuarios(lista_usuarios); 
                            } else if (subsubopcao == 2) {
                                printf("Qual o nome do arquivo?\n");
                                fgets(nome_arq, STR_TAM, stdin);
                                retirar_enter_string(nome_arq);
                                relatorioUsuarios_txt(lista_usuarios, nome_arq); 
                            } else printf("Opcao invalida.\n");
                            break;
                    case 3: printf("1 - Mostrar relatorio na tela\n");
                            printf("2 - Exportar relatorio em arquivo\n");
                            scanf("%d", &subsubopcao);
                            getchar();
                            if (subsubopcao == true) {
                                relatorioEmprestimos(lista_emprestimos, lista_usuarios); 
                            } else if (subsubopcao == 2) {
                                printf("Qual o nome do arquivo?\n");
                                fgets(nome_arq, STR_TAM, stdin);
                                retirar_enter_string(nome_arq);
                                relatorioEmprestimos_txt(lista_emprestimos, nome_arq, lista_usuarios); 
                            } else printf("Opcao invalida.\n");
                            break;
                    case 4: printf("1 - Mostrar relatorio na tela\n");
                            printf("2 - Exportar relatorio em arquivo\n");
                            scanf("%d", &subsubopcao);
                            getchar();
                            if (subsubopcao == true) {
                                relatorioPendencias(lista_emprestimos, lista_usuarios); 
                            } else if (subsubopcao == 2) {
                                printf("Qual o nome do arquivo?\n");
                                fgets(nome_arq, STR_TAM, stdin);
                                retirar_enter_string(nome_arq);
                                relatorioPendencias_txt(lista_emprestimos, nome_arq, lista_usuarios);
                            } else printf("Opcao invalida.\n");
                            break;
                    case 5: printf("1 - Mostrar relatorio na tela\n");
                            printf("2 - Exportar relatorio em arquivo\n");
                            scanf("%d", &subsubopcao);
                            getchar();
                            if (subsubopcao == true) {
                                relatorioLivrosEditados(lista_exemplares); 
                            } else if (subsubopcao == 2) {
                                printf("Qual o nome do arquivo?\n");
                                fgets(nome_arq, STR_TAM, stdin);
                                retirar_enter_string(nome_arq);
                                relatorioLivrosEditados_txt(lista_exemplares, nome_arq);
                            } else printf("Opcao invalida.\n");
                            break;
                    default: printf("Opcao invalida.\n");
                }
                break;
            case 0: printf("\nSalvando dados...\n");
                    salvar_dados_exemplares_binario("exemplares.bin", lista_exemplares);
                    salvar_dados_usuarios_binario("usuarios.bin", lista_usuarios);
                    salvar_dados_emprestimos_binario("emprestimos.bin", lista_emprestimos);
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
int menuEmprestimoDevolucao() 
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
    emprestimos_t *novo = (emprestimos_t *)malloc(sizeof(emprestimos_t));
    if (!novo) {
        printf("Erro ao alocar memória para o empréstimo.\n");
        return NULL;
    }

    strncpy(novo->livro_titulo, exemplares->titulo, STR_TAM - 1);
    novo->livro_titulo[STR_TAM - 1] = '\0'; 
    novo->id_usuario = usuarios->id;
    novo->qtd_dias = qtd_dias;
    novo->vlr_atraso = qtd_dias * exemplares->preco;
    novo->prox = NULL;

    exemplares->status = false; 

    return novo;
}

void realizarDevolucaoLivro(usuarios_t *usuario, exemplares_t *exemplar, int dias_realizados, int dias_permitidos)
{
    exemplar->status = true;

    if (dias_realizados > dias_permitidos) {
        int dias_extras = dias_realizados - dias_permitidos;
        float valor_atraso = dias_extras * exemplar->preco;
        printf("Devolução realizada com atraso! Dias extras: %d. Multa a ser paga: %.2f\n", dias_extras, valor_atraso);
    } else {
        printf("Devolução realizada sem atrasos! Obrigado.\n");
    }

    exemplar->qtd_exemplar += 1;
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
    fgets(novo->num_paginas, STR_TAM, stdin);
    retirar_enter_string(novo->num_paginas);
    formatar_maiuscula(novo->num_paginas);

    printf("Ano de publicacao: ");
    fgets(novo->ano_publicacao, STR_TAM, stdin);
    retirar_enter_string(novo->ano_publicacao);
    formatar_maiuscula(novo->ano_publicacao);

    printf("Quantidade de exemplares: ");
    scanf("%i", &novo->qtd_exemplar);
    
    printf("Preco: ");
    scanf("%f", &novo->preco);
    
    novo->status = true; 

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
    fgets(novo->telefone, STR_TAM, stdin);
    retirar_enter_string(novo->telefone);
    formatar_maiuscula(novo->telefone);
    
    printf("Email: ");
    fgets(novo->email, STR_TAM, stdin);
    retirar_enter_string(novo->email);
    formatar_maiuscula(novo->email);

    printf("CPF: ");
    fgets(novo->cpf, STR_TAM, stdin);
    retirar_enter_string(novo->cpf);
    formatar_maiuscula(novo->cpf);

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

void relatorioAcervo_txt(exemplares_t *lista, string nome) 
{
    FILE *fp = fopen(nome, "w");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

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
        fprintf(fp, "%f\n", lista->preco);
        fprintf(fp, "\n");

        lista = lista->prox;
    }

    fclose(fp);
    
}

exemplares_t* localizar_exemplares_titulo(exemplares_t *lista, string titulo) 
{
    while (lista){
        if (strcmp(lista->titulo, titulo) == 0) {
            return lista;
        }
        lista = lista->prox;
    }

    return NULL;
}

void salvar_dados_exemplares_binario(string nome, exemplares_t *lista) 
{
    FILE *fp = fopen("exemplares.bin", "wb");

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
void relatorioUsuarios_txt(usuarios_t *lista, string nome) 
{
    FILE *fp = fopen(nome, "w");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (lista != NULL) {
        fprintf(fp, "%s\n", lista->nome);
        fprintf(fp, "%s\n", lista->endereco);
        fprintf(fp, "%s\n", lista->telefone);
        fprintf(fp, "%s\n", lista->email);
        fprintf(fp, "%s\n", lista->cpf);
        fprintf(fp, "\n");

        lista = lista->prox;
    }

    fclose(fp);
}

void salvar_dados_usuarios_binario(string nome, usuarios_t *lista) 
{
    FILE *fp = fopen("usuarios.bin", "wb");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (lista != NULL) {
        fwrite(lista, sizeof(usuarios_t), 1, fp);
        lista = lista->prox;
    }

    fclose(fp);
}

void salvar_dados_emprestimos_binario(string nome, emprestimos_t *lista) 
{
    FILE *fp = fopen(nome, "wb");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para salvar os empréstimos.\n");
        return;
    }

    while (lista != NULL) {
        fwrite(lista, sizeof(emprestimos_t), 1, fp);
        lista = lista->prox;
    }

    fclose(fp);
}

// Função para ler dados de exemplares em arquivo
void ler_dados_exemplares_binario(string nome, exemplares_t **lista)
{
    FILE *fp = fopen(nome, "rb");
    exemplares_t temp;

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome);
        return;
    }

    while (fread(&temp, sizeof(exemplares_t), 1, fp)) {
        exemplares_t *novo = (exemplares_t *)malloc(sizeof(exemplares_t));
        *novo = temp;
        novo->prox = NULL;
        inserir_exemplares_lista(lista, novo);
    }

    fclose(fp);
}

// Função para ler dados de usuarios em arquivo
void ler_dados_usuarios_binario(string nome, usuarios_t **lista)
{
    FILE *fp = fopen(nome, "rb");
    usuarios_t temp;

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome);
        return;
    }

    while (fread(&temp, sizeof(usuarios_t), 1, fp)) {
        usuarios_t *novo = (usuarios_t *)malloc(sizeof(usuarios_t));
        *novo = temp;
        novo->prox = NULL;
        inserir_usuarios_lista(lista, novo);
    }

    fclose(fp);

}

void ler_dados_emprestimos_binario(string nome, emprestimos_t **lista) 
{
    FILE *fp = fopen(nome, "rb");
    emprestimos_t temp;

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s para leitura.\n", nome);
        return;
    }

    while (fread(&temp, sizeof(emprestimos_t), 1, fp)) {
        emprestimos_t *novo = (emprestimos_t *)malloc(sizeof(emprestimos_t));
        if (!novo) {
            printf("Erro ao alocar memória ao carregar empréstimos.\n");
            break;
        }

        *novo = temp;
        novo->prox = NULL;
        inserir_emprestimos_lista(lista, novo);
    }

    fclose(fp);
}

// Função de localizar usuário por nome
usuarios_t* localizar_usuarios(usuarios_t *lista, string nome)
{
    while (lista) {
        if (strcmp(lista->nome, nome) == 0) {
            return lista;
        }
        lista = lista->prox;
    }

    return NULL;
}

void mostrar_dados_usuarios(usuarios_t *lista)
{
    if (lista == NULL) {
        printf("Nenhum usuário encontrado.\n");
        return;
    }

    printf("ID......: %i\n", lista->id);
    printf("Nome....: %s\n", lista->nome);
    printf("Endereco: %s\n", lista->endereco);
    printf("Telefone: %s\n", lista->telefone);
    printf("Email...: %s\n", lista->email);
}

void mostrar_dados_exemplares(exemplares_t *lista)
{
    if (lista == NULL) {
        printf("Nenhum exemplar encontrado.\n");
        return;
    }

    printf("Titulo..................: %s\n", lista->titulo);
    printf("Autor...................: %s\n", lista->autor);
    printf("Editora.................: %s\n", lista->editora);
    printf("Edicao..................: %s\n", lista->edicao);
    printf("Local de publicacao.....: %s\n", lista->local_publicacao);
    printf("Palavras-chaves.........: %s\n", lista->palavras_chave);
    printf("Numero de paginas.......: %s\n", lista->num_paginas);
    printf("Ano de publicacao.......: %s\n", lista->ano_publicacao);
    printf("Quantidade de exemplares: %i\n", lista->qtd_exemplar);
    printf("Preco...................: %.2f\n", lista->preco);
}

// Função de localizar exemplar por título
exemplares_t* localizar_exemplares(exemplares_t *lista, string chave)
{
    while (lista) {
        if (strcmp(lista->titulo, chave) == 0 || strcmp(lista->autor, chave) == 0 || strcmp(lista->palavras_chave, chave) == 0) {
            return lista;
        }
        lista = lista->prox;
    }

    return NULL;
}

void inserir_emprestimos_lista(emprestimos_t **lista, emprestimos_t *novo)
{
    if (*lista != NULL) {
        novo->prox = *lista;
    }
    *lista = novo;
}

// Função para dar baixa
void baixar_exemplares(exemplares_t *lista, string titulo)  
{
    exemplares_t *aux = lista;

    while (aux != NULL) {
        if (strcmp(aux->titulo, titulo) == 0) {  
            if (aux->status) {  
                printf("Nao e possivel dar baixa. O exemplar esta emprestado.\n");
            } else if (aux->qtd_exemplar > 0) {
                aux->qtd_exemplar -= 1;
                printf("Baixa realizada com sucesso. Exemplares restantes: %d\n", aux->qtd_exemplar);
            } else {
                printf("Nao ha exemplares disponiveis para dar baixa.\n");
            }
            return;
        }
        aux = aux->prox;
    }

    printf("Exemplar nao encontrado.\n");
}

// Funções de relatório
void relatorioAcervo(exemplares_t *lista)
{
    exemplares_t *aux = lista;

    while (aux != NULL) {
        printf("Titulo.............: %s\n", aux->titulo);
        printf("Autor..............: %s\n", aux->autor);
        printf("Editora............: %s\n", aux->editora);
        printf("Edicao.............: %s\n", aux->edicao);
        printf("Local de publicacao: %s\n", aux->local_publicacao);
        printf("Palavras-chave.....: %s\n", aux->palavras_chave);
        printf("Numero de paginas..: %s\n", aux->num_paginas);
        printf("Ano de publicacao..: %s\n", aux->ano_publicacao);
        printf("Quantidade.........: %i\n", aux->qtd_exemplar);
        printf("Preco..............: %.2f\n", aux->preco);
        printf("\n");
        aux = aux->prox;
    }
}
void relatorioUsuarios(usuarios_t *lista)
{
    usuarios_t *aux = lista;

    while (aux != NULL) {
        printf("ID......: %i\n", aux->id);
        printf("Nome....: %s\n", aux->nome);
        printf("Endereco: %s\n", aux->endereco);
        printf("Telefone: %s\n", aux->telefone);
        printf("Email...: %s\n", aux->email);
        printf("CPF.....: %s\n", aux->cpf);
        printf("\n");
        aux = aux->prox;
    }
}
void relatorioEmprestimos(emprestimos_t *lista_emprestimos, usuarios_t *lista_usuarios) 
{
    if (lista_emprestimos == NULL) {
        printf("Nenhum empréstimo cadastrado.\n");
        return;
    }

    while (lista_emprestimos) {
        usuarios_t *usuario_atual = lista_usuarios;
        string nome = "Não encontrado";

        while (usuario_atual != NULL) {
            if (lista_emprestimos->id_usuario == usuario_atual->id) {
                strncpy(nome, usuario_atual->nome, STR_TAM - 1);
                nome[STR_TAM - 1] = '\0';
                break;
            }
            usuario_atual = usuario_atual->prox;
        }

        printf("ID...: %d\n", lista_emprestimos->id_usuario);
        printf("Nome.: %s\n", nome);
        printf("Livro: %s\n", lista_emprestimos->livro_titulo);
        printf("Dias.: %d\n", lista_emprestimos->qtd_dias);
        printf("Valor: %.2f\n\n", lista_emprestimos->vlr_atraso);

        lista_emprestimos = lista_emprestimos->prox;
    }
}

void relatorioEmprestimos_txt(emprestimos_t *lista_emprestimos, string nome, usuarios_t *lista_usuarios)
{
    FILE *fp = fopen(nome, "w");
    string nome_usuario;

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    if (lista_emprestimos == NULL) {
        printf("Nenhum emprestimo cadastrado.\n");
        fclose(fp);  
        return;
    }

    while (lista_emprestimos) {
        while (lista_usuarios != NULL) {
            if (lista_emprestimos->id_usuario == lista_usuarios->id) {  
                strcpy(nome_usuario, lista_usuarios->nome);  
                break;  
            }
            lista_usuarios = lista_usuarios->prox; 
        }

        fprintf(fp, "%i\n", lista_emprestimos->id_usuario);
        fprintf(fp, "%s\n", nome_usuario);
        fprintf(fp, "%s\n", lista_emprestimos->livro_titulo);
        fprintf(fp, "%i\n", lista_emprestimos->qtd_dias);
        fprintf(fp, "%.2f\n", lista_emprestimos->vlr_atraso);
        fprintf(fp, "\n");

        lista_emprestimos = lista_emprestimos->prox;  
    }

    fclose(fp); 
}

void relatorioPendencias(emprestimos_t *lista_emprestimos, usuarios_t *lista_usuarios)
{
    emprestimos_t *aux = lista_emprestimos;
    usuarios_t *auxi = lista_usuarios;
    string nome;

    if (lista_emprestimos == NULL) {
        printf("Nenhum emprestimo cadastrado.\n");
        return;
    }

    while (lista_emprestimos != NULL) {

        while (aux != NULL) {
            if (auxi->id == lista_emprestimos->id_usuario) {
                strcpy(nome, auxi->nome);
            }
            aux = aux->prox;
        }

        printf("ID.....: %i\n", lista_emprestimos->id_usuario);
        printf("Usuario: %s\n", nome);
        printf("Livro..: %s\n", lista_emprestimos->livro_titulo);
        printf("Dias...: %i\n", lista_emprestimos->qtd_dias);
        printf("Valor..: %.2f\n", lista_emprestimos->vlr_atraso);
        printf("\n");
        lista_emprestimos = lista_emprestimos->prox;
    }
}

void relatorioPendencias_txt(emprestimos_t *lista_emprestimos, string nome, usuarios_t *lista_usuarios)
{
    FILE *fp = fopen(nome, "w");
    usuarios_t *aux = lista_usuarios;
    string nome_usuario;

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (lista_emprestimos != NULL) {

        while (aux != NULL) {
            if (aux->id == lista_emprestimos->id_usuario) {
                strcpy(nome_usuario, aux->nome);
            }
            aux = aux->prox;
        }

        fprintf(fp, "%i\n", lista_emprestimos->id_usuario);
        fprintf(fp, "%s\n", nome_usuario);
        fprintf(fp, "%s\n", lista_emprestimos->livro_titulo);
        fprintf(fp, "%i\n", lista_emprestimos->qtd_dias);
        fprintf(fp, "%.2f\n", lista_emprestimos->vlr_atraso);
        fprintf(fp, "\n");

        lista_emprestimos = lista_emprestimos->prox;
    }

    fclose(fp);
}

void relatorioLivrosEditados(exemplares_t *lista)
{
    exemplares_t *aux = lista;
    int ano_inicial, ano_final, ano_publicacao_int;

    printf("\nDigite o ano inicial: ");
    scanf("%i", &ano_inicial);
    printf("Digite o ano final: ");
    scanf("%i", &ano_final);

    while (aux != NULL) {
        ano_publicacao_int = atoi(aux->ano_publicacao);

        if (ano_publicacao_int >= ano_inicial && ano_publicacao_int <= ano_final) {
            printf("\n");
            mostrar_dados_exemplares(aux);
            printf("\n");
        }
        aux = aux->prox;
    }
}

void relatorioLivrosEditados_txt(exemplares_t *lista, string nome)
{
    FILE *fp = fopen(nome, "w");
    exemplares_t *aux = lista;
    int ano_inicial, ano_final, ano_publicacao_int;

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("\nDigite o ano inicial: ");
    scanf("%i", &ano_inicial);
    printf("Digite o ano final: ");
    scanf("%i", &ano_final);

    while (aux != NULL) {
        // Converte o ano de publicação de string para inteiro
        ano_publicacao_int = atoi(aux->ano_publicacao);

        if (ano_publicacao_int >= ano_inicial && ano_publicacao_int <= ano_final) {
            fprintf(fp, "%s\n", aux->titulo);
            fprintf(fp, "%s\n", aux->autor);
            fprintf(fp, "%s\n", aux->editora);
            fprintf(fp, "%s\n", aux->edicao);
            fprintf(fp, "%s\n", aux->local_publicacao);
            fprintf(fp, "%s\n", aux->palavras_chave);
            fprintf(fp, "%s\n", aux->num_paginas);
            fprintf(fp, "%s\n", aux->ano_publicacao);
            fprintf(fp, "%i\n", aux->qtd_exemplar);
            fprintf(fp, "%.2f\n", aux->preco);
            fprintf(fp, "\n");
        }
        aux = aux->prox;
    }

    fclose(fp);
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