#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// Definição de constantes
#define STR_TAM 55
#define MAX_LIVROS 100
#define MAX_USUARIOS 100

// Definição de tipos
typedef char string[STR_TAM];

// Estrutura para cadastro de exemplares
struct dados_exemplares {
    string titulo;
    string autor;
    int ano_publicacao;
    int qtd_exemplares;
    bool status; // true para disponível, false para emprestado
};

// Estrutura para cadastro de usuários
struct dados_usuarios {
    string nome;
    string endereco;
    string telefone;
    string email;
    int cracha;
    bool status; // true para ativo, false para não ativo
};

// Estrutura para controlar empréstimos
struct dados_emprestimo {
    int id_usuario;
    string titulo_livro;
    int dias_emprestimo;
    int data_devolucao;
};

// Declaração dos arrays para armazenar os dados
struct dados_exemplares livros[MAX_LIVROS];
struct dados_usuarios usuarios[MAX_USUARIOS];
struct dados_emprestimo emprestimos[MAX_LIVROS];
int qtd_livros = 0, qtd_usuarios = 0, qtd_emprestimos = 0;

// Cabeçalho das funções
void cadastrarNovosExemplares();
void cadastrarNovoUsuario();
void controleEmprestimoDevolucao();
void baixaDeExemplares();
void localizacaoDeExemplares();
void localizacaoDeUsuarios();
void relatorioAcervo();
void relatorioUsuarios();
void relatorioEmprestimos();
void relatorioPendencias();
void relatorioLivrosEditados();

// Função principal
int main() {
    int opcao, subopcao;

    do {
        printf("Menu Principal:\n1. Cadastrar novos exemplares\n2. Cadastrar novo usuário\n3. Controle de empréstimo e devolução\n4. Baixa de exemplares\n5. Localizar exemplares por título, palavras-chave ou autor\n6. Localização de usuários por nome\n7. Relatórios\n0. Sair\nEscolha uma opção: ");
        scanf("%i", &opcao);
        getchar();

        switch (opcao) {
            case 1: cadastrarNovosExemplares(); 
                    break;
            case 2: cadastrarNovoUsuario(); 
                    break;
            case 3: controleEmprestimoDevolucao(); 
                    break;
            case 4: baixaDeExemplares(); 
                    break;
            case 5: localizacaoDeExemplares(); 
                    break;
            case 6: localizacaoDeUsuarios(); 
                    break;
            case 7:
                printf("\n1. Relatório de acervo\n2. Relatório de usuários\n3. Relatório de empréstimos\n4. Relatório de pendências\n5. Relatório de livros por ano\nEscolha uma opção: ");
                scanf("%d", &subopcao);
                getchar();
                switch (subopcao) {
                    case 1: relatorioAcervo(); 
                            break;
                    case 2: relatorioUsuarios(); 
                            break;
                    case 3: relatorioEmprestimos(); 
                            break;
                    case 4: relatorioPendencias(); 
                            break;
                    case 5: relatorioLivrosEditados(); 
                            break;
                    default: printf("Opção inválida.\n");
                }
                break;
            case 0: printf("Saindo do sistema...\n"); 
                    break;
            default: printf("Opção inválida!\n"); 
                    break;
        }
    } while (opcao != 0);

    return 0;
}

// Função para cadastrar novos exemplares
void cadastrarNovosExemplares() {
    if (qtd_livros < MAX_LIVROS) {
        printf("Título: ");
        fgets(livros[qtd_livros].titulo, STR_TAM, stdin);
        livros[qtd_livros].titulo[strcspn(livros[qtd_livros].titulo, "\n")] = 0; // Remover '\n'
        printf("Autor: ");
        fgets(livros[qtd_livros].autor, STR_TAM, stdin);
        livros[qtd_livros].autor[strcspn(livros[qtd_livros].autor, "\n")] = 0; // Remover '\n'
        printf("Ano de publicação: ");
        scanf("%d", &livros[qtd_livros].ano_publicacao);
        getchar();
        printf("Quantidade de exemplares: ");
        scanf("%d", &livros[qtd_livros].qtd_exemplares);
        getchar();
        livros[qtd_livros].status = true;
        qtd_livros++;
        printf("Exemplar cadastrado com sucesso!\n");
    } else {
        printf("Limite de cadastro de livros atingido.\n");
    }
}

// Função para cadastrar novos usuários
void cadastrarNovoUsuario() {
    if (qtd_usuarios < MAX_USUARIOS) {
        printf("Nome: ");
        fgets(usuarios[qtd_usuarios].nome, STR_TAM, stdin);
        usuarios[qtd_usuarios].nome[strcspn(usuarios[qtd_usuarios].nome, "\n")] = 0; // Remover '\n'
        printf("Endereço: ");
        fgets(usuarios[qtd_usuarios].endereco, STR_TAM, stdin);
        printf("Telefone: ");
        fgets(usuarios[qtd_usuarios].telefone, STR_TAM, stdin);
        printf("Email: ");
        fgets(usuarios[qtd_usuarios].email, STR_TAM, stdin);
        getchar();
        printf("Número do crachá: ");
        scanf("%d", &usuarios[qtd_usuarios].cracha);
        getchar();
        usuarios[qtd_usuarios].status = true;
        qtd_usuarios++;
        printf("Usuário cadastrado com sucesso!\n");
    } else {
        printf("Limite de cadastro de usuários atingido.\n");
    }
}

// Função para controle de empréstimo e devolução
void controleEmprestimoDevolucao() {
    string titulo;
    int id_usuario, dias;
    printf("Digite o título do livro a ser emprestado: ");
    fgets(titulo, STR_TAM, stdin);
    titulo[strcspn(titulo, "\n")] = 0; // Remover '\n'

    for (int i = 0; i < qtd_livros; i++) {
        if (strcmp(livros[i].titulo, titulo) == 0 && livros[i].status) {
            printf("Informe o ID do usuário: ");
            scanf("%d", &id_usuario);
            getchar();
            printf("Quantos dias para o empréstimo? ");
            scanf("%d", &dias);
            getchar();
            livros[i].status = false;
            emprestimos[qtd_emprestimos].id_usuario = id_usuario;
            strcpy(emprestimos[qtd_emprestimos].titulo_livro, titulo);
            emprestimos[qtd_emprestimos].dias_emprestimo = dias;
            emprestimos[qtd_emprestimos].data_devolucao = dias; // Exemplo de cálculo de data de devolução
            qtd_emprestimos++;
            printf("Empréstimo realizado com sucesso!\n");
            return;
        }
    }
    printf("Livro não encontrado ou já emprestado.\n");
}

// As outras funções de localização, baixa e relatórios podem ser implementadas com lógica similar.

