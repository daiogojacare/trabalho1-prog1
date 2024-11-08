/*
• Controle de empréstimo e devolução de exemplares;
• Baixa de exemplares;
• Localização de exemplares por título, palavras-chave ou autor;
• Localização de usuários por nome.
O responsável pela biblioteca precisa que os seguintes dados sejam armazenados em relação aos livros:
título, editora, ano de publicação, autor(es) (no máximo três autores), número de páginas, edição, local da
publicação, palavras-chave e quantidade de exemplares. Para um efetivo controle do acervo também é
necessário que se tenha os seguintes dados dos usuários da biblioteca: nome, endereço, telefone para
contato, email, nº do crachá da empresa (identificação numérica), status (ativo, não ativo).
Além das funcionalidades especificadas acima o responsável pela biblioteca precisa que os seguintes
relatórios sejam gerados pelo sistema:
• Relatório de acervo;  
• Relatório de pendências (livros emprestados e ainda não devolvidos na data prevista de devolução);
• Relatório de livros editados em uma determinada faixa de ano (Ex. 2020 a 2024).*/
//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

//Definição de constantes
#define STR_TAM 55 //Tamanho da string
#define MAX_QTD 100 //Quantidade max de livros

//Definição de tipos
typedef char string[STR_TAM]; 

// Estrutura para cadastro de exemplares
struct exemplares {
    string titulo;
    string autor;
    string editora;
    int ano_publicacao;
    float vlr_emprestimo;
    bool status;   // false - se emprestado; true - se disponível
};

// Estrutura para cadastro de usuários
struct usuarios {
    int id;
    string nome;
    string endereco;
    string telefone;
    string email;
    string cpf;
};

// Estrutura para cadastro de empréstimos
struct emprestimos {
  int id_cliente;
  string livro_titulo;
  int qtd_dias;
  float vlr_emprestimo;
};

// Declaração dos arrays para armazenar os dados
struct exemplares vetor_exemplares[MAX_QTD];
struct usuarios vetor_usuarios[MAX_QTD];
struct emprestimos vetor_emprestimos[MAX_QTD];

// Variável global para controlar a quantidade de exemplares cadastrados
int qtd_exemplares = 0, qtd_usuarios = 0, qtd_emprestimos = 0;

// Cabeçalho das funções
int menu();
int submenu();
struct exemplares cadastrarNovosExemplares();
struct usuarios cadastrarNovosUsuarios();
void controleEmprestimoDevolucao();
void baixaDeExemplares();
int localizacaoDeExemplares();
void localizacaoDeUsuarios();
void relatorioAcervo();
void relatorioUsuarios();
void relatorioEmprestimos();
void relatorioPendencias();
void relatorioLivrosEditados();
void formatar_maiuscula(string str);
void retirar_enter_string(string str);

// Função principal
int main() {
    int opcao, subopcao, idx, exemplar_idx, usuario_idx;
    string titulo, autor, nome;

    do {
        opcao = menu();

        switch (opcao) {
            case 1: vetor_exemplares[qtd_exemplares] = cadastrarNovosExemplares(); 
                    qtd_exemplares++; 
                    break;
            case 2: vetor_usuarios[qtd_usuarios] = cadastrarNovosUsuarios(); 
                    qtd_usuarios++; 
                    break;
            case 3: controleEmprestimoDevolucao(); 
                    break;
            case 4: baixaDeExemplares(); 
                    break;
            case 5: localizacaoDeExemplares(); 
                    break;
            case 6: 
                    localizacaoDeUsuarios(); 
                    break;
            case 7:
                subopcao = submenu();

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

// Função do menu
int menu()
{
    int opc;

    printf("1. Cadastrar novos exemplares\n");
    printf("2. Cadastrar novo usuário\n");
    printf("3. Controle de empréstimo e devolução\n");
    printf("4. Baixa de exemplares\n");
    printf("5. Localizar exemplares por título, palavras-chave ou autor\n");
    printf("6. Localização de usuários por nome\n");
    printf("7. Relatórios\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: \n");
    fflush(stdin);
    scanf("%d", &opc);
    getchar();

    return opc;
}

// Função do submenu
int submenu()
{
    int opc;

    printf("1. Relatório de acervo\n");
    printf("2. Relatório de usuários\n");
    printf("3. Relatório de empréstimos\n");
    printf("4. Relatório de pendências\n\n");
    printf("5. Relatório de livros por ano\n");
    printf("Escolha uma opção: \n");
    fflush(stdin);
    scanf("%d", &opc);
    getchar();

    return opc;
}

// Função para cadastrar novos exemplares
struct exemplares cadastrarNovosExemplares()
{
    struct exemplares novo;

    fflush(stdin);

    printf("Título do livro: ");
    fgets(novo.titulo, STR_TAM, stdin);
    retirar_enter_string(novo.titulo);
    formatar_maiuscula(novo.titulo);

    printf("Autor do livro: ");
    fgets(novo.autor, STR_TAM, stdin);
    retirar_enter_string(novo.autor);
    formatar_maiuscula(novo.autor);

    printf("Editora do livro: ");
    fgets(novo.editora, STR_TAM, stdin);
    retirar_enter_string(novo.editora);
    formatar_maiuscula(novo.editora);

    printf("Ano de publicação: ");
    scanf("%i", &novo.ano_publicacao);
    
    printf("Valor do empréstimo: ");
    scanf("%f", &novo.vlr_emprestimo);

    novo.status = true;

    return novo;
}

// Função para cadastrar novos usuários
struct usuarios cadastrarNovosUsuarios()
{
    struct usuarios novo;

    fflush(stdin);

    printf("Nome: ");
    fgets(novo.nome, STR_TAM, stdin);
    retirar_enter_string(novo.nome);
    formatar_maiuscula(novo.nome);

    printf("Email: ");
    fgets(novo.email, STR_TAM, stdin);
    retirar_enter_string(novo.email);
    formatar_maiuscula(novo.email);

    printf("Telefone: ");
    fgets(novo.telefone, STR_TAM, stdin);
    retirar_enter_string(novo.telefone);
    formatar_maiuscula(novo.telefone);

    printf("Endereço: ");
    fgets(novo.endereco, STR_TAM, stdin);
    retirar_enter_string(novo.endereco);
    formatar_maiuscula(novo.endereco);

    printf("CPF: ");
    fgets(novo.cpf, STR_TAM, stdin);
    retirar_enter_string(novo.cpf);
    formatar_maiuscula(novo.cpf);

    novo.id = qtd_usuarios + 1;

    return novo;
}

// Função para localizar exemplares
int localizacaoDeUsuarios()
{

}

// Função para exibir exemplares
void relatorioExemplares()
{
   int i;

    for(i = 0; i < qtd_exemplares; i++){
        printf("Título: %s\n",vetor_exemplares[i].titulo);
        printf("Autor: %s\n",vetor_exemplares[i].autor);
        printf("Editora: %s\n",vetor_exemplares[i].editora);
        printf("Ano de publicação: %d\n", vetor_exemplares[i].ano_publicacao);
        printf("Status: %s\n", (vetor_exemplares[i].status)? "Disponível" : "Emprestado");
    } 
}

// Função para exibir usuários
void relatorioUsuarios()
{
    int i;

    for(i = 0; i < qtd_usuarios; i++){
        printf("Nome: %s\n",vetor_usuarios[i].nome);
        printf("Email: %s\n", vetor_usuarios[i].email);
        printf("Telefone: %s\n", vetor_usuarios[i].telefone);
        printf("Endereço: %s\n", vetor_usuarios[i].endereco);
        printf("CPF: %s\n", vetor_usuarios[i].cpf);
        printf("ID: %d\n", vetor_usuarios[i].id);
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