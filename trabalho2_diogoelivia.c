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
void baixar_exemplares(exemplares_t *lista); //FEITO
void inserir_emprestimos_lista(emprestimos_t **lista, emprestimos_t *novo); //FEITO

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
int menuEmprestimoDevolucao(); // FEITO
void realizarDevolucaoLivro(); //
void salvar_dados_emprestimos_txt(string nome, emprestimos_t *lista); //FEITO
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
void relatorioLivrosEditados(emprestimos_t *lista); //
void relatorioLivrosEditados_txt(emprestimos_t *lista, string nome); //

// Funções auxiliares
void formatar_maiuscula(string str);
void retirar_enter_string(string str);

// Função principal
int main() {
    int opcao, subopcao, subsubopcao, qtd_cliente = 0, qtd_dias = 0;
    string nome_arq, nome, titulo, autor;

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
                        case 1: printf("Qual livro será emprestado?\n");
                                fgets(titulo, STR_TAM, stdin);
                                retirar_enter_string(titulo);
                                formatar_maiuscula(titulo);

                                livro = localizar_exemplares(lista_exemplares, titulo);	
                                if (!livro) {
                                    printf("O livro %s nao existe!\n", titulo);
                                } else {
                                    if (livro->status == true) {
                                        printf("\nQual o nome do usuario?\n");
                                        fgets(nome, STR_TAM, stdin);
                                        retirar_enter_string(nome);
                                        formatar_maiuscula(nome);

                                        usuario = localizar_usuarios(lista_usuarios, nome);

                                        if (!usuario) {
                                            printf("O usuario %s nao existe!\n", nome);
                                            break;
                                        } else {
                                            printf("Quantos dias será emprestado?\n");
                                            scanf("%d", &qtd_dias);
                                            inserir_emprestimos_lista(&lista_emprestimos, realizarEmprestimoLivro(usuario, livro, qtd_dias));
                                        }
                                    } else printf("O livro %s nao esta disponivel!\n", titulo);
                                } 
                                break;
                        case 2: 
                                break;
                        default: printf("Opcao invalida.\n");
                    }
                    break;
            case 4: getchar();
                    printf("\nQual o titulo do livro para dar baixa?\n");
                    fgets(titulo, STR_TAM, stdin);
                    retirar_enter_string(titulo);
                    formatar_maiuscula(titulo);
                    baixar_exemplares(lista_exemplares);
                    break;
            case 5: getchar();
                    printf("Digite o criterio de busca (titulo, palavras-chave ou autor): ");
                    fgets(titulo, STR_TAM, stdin);
                    retirar_enter_string(titulo);
                    formatar_maiuscula(titulo);
                    
                    livro = localizar_exemplares(lista_exemplares, titulo);

                    if (!livro) {
                        printf("O livro %s nao existe!\n", titulo);
                    } else {
                        mostrar_dados_exemplares(livro);
                    }
                    break;
            case 6: getchar();
                    printf("Qual o nome do usuario?\n");
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

                    case 1: printf("1 - Mostrar relatorio na tela");
                            printf("2 - Exportar relatorio em arquivo");
                            scanf("%d", &subsubopcao);
                            if (subsubopcao == 1) {
                                relatorioAcervo(lista_exemplares); 
                            } else if (subsubopcao == 2) {
                                printf("Qual o nome do arquivo?\n");
                                scanf("%s", &nome_arq);
                                relatorioAcervo_txt(lista_exemplares, nome_arq);
                            } else printf("Opcao invalida.\n");
                            break;
                    case 2: printf("1 - Mostrar relatorio na tela");
                            printf("2 - Exportar relatorio em arquivo");
                            scanf("%d", &subsubopcao);
                            if (subsubopcao == 1) {
                                relatorioUsuarios(lista_usuarios); 
                            } else if (subsubopcao == 2) {
                                printf("Qual o nome do arquivo?\n");
                                scanf("%s", &nome_arq);
                                relatorioUsuarios_txt(lista_usuarios, nome_arq); 
                            } else printf("Opcao invalida.\n");
                            break;
                    case 3: printf("1 - Mostrar relatorio na tela");
                            printf("2 - Exportar relatorio em arquivo");
                            scanf("%d", &subsubopcao);
                            if (subsubopcao == 1) {
                                relatorioEmprestimos(lista_emprestimos, lista_usuarios); 
                            } else if (subsubopcao == 2) {
                                printf("Qual o nome do arquivo?\n");
                                scanf("%s", &nome_arq);
                                relatorioEmprestimos_txt(lista_emprestimos, lista_usuarios, nome_arq); 
                            } else printf("Opcao invalida.\n");
                            break;
                    case 4: printf("1 - Mostrar relatorio na tela");
                            printf("2 - Exportar relatorio em arquivo");
                            scanf("%d", &subsubopcao);
                            if (subsubopcao == 1) {
                                relatorioPendencias(lista_emprestimos, lista_usuarios); 
                            } else if (subsubopcao == 2) {
                                printf("Qual o nome do arquivo?\n");
                                scanf("%s", &nome_arq);
                                relatorioPendencias_txt(lista_emprestimos, lista_usuarios, nome_arq);
                            } else printf("Opcao invalida.\n");
                            break;
                    case 5: printf("1 - Mostrar relatorio na tela");
                            printf("2 - Exportar relatorio em arquivo");
                            scanf("%d", &subsubopcao);
                            if (subsubopcao == 1) {
                                relatorioLivrosEditados(lista_emprestimos); 
                            } else if (subsubopcao == 2) {
                                printf("Qual o nome do arquivo?\n");
                                scanf("%s", &nome_arq);
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
    scanf("%s", novo->num_paginas); 

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

void relatorioAcervo_txt(exemplares_t *lista, string nome) 
{
    FILE *fp = fopen(nome, "w");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (lista != NULL) {
        fprintf(fp, "Titulo..................: %s\n", lista->titulo);
        fprintf(fp, "Autor...................: %s\n", lista->autor);
        fprintf(fp, "Editora.................: %s\n", lista->editora);
        fprintf(fp, "Edição..................: %s\n", lista->edicao);
        fprintf(fp, "Local de publicação.....: %s\n", lista->local_publicacao);
        fprintf(fp, "Palavras-chaves.........: %s\n", lista->palavras_chave);
        fprintf(fp, "Número de páginas.......: %s\n", lista->num_paginas);
        fprintf(fp, "Ano de publicação.......: %s\n", lista->ano_publicacao);
        fprintf(fp, "Quantidade de exemplares: %i\n", lista->qtd_exemplar);
        fprintf(fp, "Preço...................: %s\n", lista->preco);
        lista = lista->prox;
    }

    fclose(fp);
    
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
        fprintf(fp, "Nome....: %s\n", lista->nome);
        fprintf(fp, "Endereço: %s\n", lista->endereco);
        fprintf(fp, "Telefone: %i\n", lista->telefone);
        fprintf(fp, "Email...: %s\n", lista->email);
        fprintf(fp, "CPF.....: %i\n", lista->cpf);
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

// Função para salvar dados de emprestimos em arquivo
void salvar_dados_emprestimos_txt(string nome, emprestimos_t *lista) 
{
    FILE *fp = fopen(nome, "w");

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
    FILE *fp = fopen("emprestimos.bin", "wb");

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
    FILE *fp = fopen("exemplares.bin", "rb");
    exemplares_t temp;

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
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
    FILE *fp = fopen("usuarios.csv", "r");
    usuarios_t temp;

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
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
    FILE *fp = fopen("emprestimos.bin", "rb");
    emprestimos_t temp;

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fread(&temp, sizeof(emprestimos_t), 1, fp)) {
        emprestimos_t *novo = (emprestimos_t *)malloc(sizeof(emprestimos_t));
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
    printf("ID......: %i\n", lista->id);
    printf("Nome....: %s\n", lista->nome);
    printf("Endereco: %s\n", lista->endereco);
    printf("Telefone: %s\n", lista->telefone);
    printf("Email...: %s\n", lista->email);
}

// Função de localizar exemplar por título
exemplares_t* localizar_exemplares(exemplares_t *lista, string chave)
{
    while (lista) {
        if (strcmp(lista->titulo, chave) || strcmp(lista->autor, chave) || strcmp(lista->palavras_chave, chave) == 0) {
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
void baixar_exemplares(exemplares_t *lista)
{
    exemplares_t *aux = lista;
    string titulo;

    while (aux != NULL) {
        if (strcmp(aux->titulo, titulo) == 0) {
            if (aux->status == 1) {
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
        printf("Titulo: %s\n", aux->titulo);
        printf("Autor: %s\n", aux->autor);
        printf("Editora: %s\n", aux->editora);
        printf("Edicao: %s\n", aux->edicao);
        printf("Local de publicacao: %s\n", aux->local_publicacao);
        printf("Palavras-chave: %s\n", aux->palavras_chave);
        printf("Numero de paginas: %s\n", aux->num_paginas);
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
void relatorioEmprestimos(emprestimos_t *lista_emprestimos, usuarios_t *lista_usuarios)
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

void relatorioEmprestimos_txt(emprestimos_t *lista_emprestimos, string nome, usuarios_t *lista_usuarios)
{
    FILE *fp = fopen(nome, "w");
    usuarios_t *aux = lista_usuarios;
    string nome;

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (lista_emprestimos != NULL) {

        while (aux != NULL) {
            if (aux->id == lista_emprestimos->id_usuario) {
                strcpy(nome, aux->nome);
            }
            aux = aux->prox;
        }

        fprintf(fp, "ID.....: %i\n", lista_emprestimos->id_usuario);
        fprintf(fp, "Usuario: %s\n", nome);
        fprintf(fp, "Livro..: %s\n", lista_emprestimos->livro_titulo);
        fprintf(fp, "Dias...: %i\n", lista_emprestimos->qtd_dias);
        fprintf(fp, "Valor..: %.2f\n", lista_emprestimos->vlr_atraso);
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
    string nome;

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (lista_emprestimos != NULL) {

        while (aux != NULL) {
            if (aux->id == lista_emprestimos->id_usuario) {
                strcpy(nome, aux->nome);
            }
            aux = aux->prox;
        }

        fprintf(fp, "ID.....: %i\n", lista_emprestimos->id_usuario);
        fprintf(fp, "Usuario: %s\n", nome);
        fprintf(fp, "Livro..: %s\n", lista_emprestimos->livro_titulo);
        fprintf(fp, "Dias...: %i\n", lista_emprestimos->qtd_dias);
        fprintf(fp, "Valor..: %.2f\n", lista_emprestimos->vlr_atraso);
        fprintf(fp, "\n");

        lista_emprestimos = lista_emprestimos->prox;
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