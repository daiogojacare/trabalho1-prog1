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
  int id_usuario;
  string livro_titulo;
  int qtd_dias;
  int vlr_atraso;
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
struct emprestimos emprestimoLivro(int pos_usuario, int pos_exemplar, int qtd_dias);
int controleEmprestimoDevolucao();
void realizarEmprestimo(); 
void devolucaoLivro();
void baixaDeExemplares();
int localizacaoDeExemplares();
void dadosExemplares();
int localizacaoDeUsuarios();
void dadosUsuarios();
void relatorioAcervo();
void relatorioUsuarios();
void relatorioEmprestimos();
void relatorioPendencias();
void relatorioLivrosEditados();
void formatar_maiuscula(string str);
void retirar_enter_string(string str);

// Função principal
int main() {
    int opcao, subopcao, subsubopcao, idx, idx_exemplares, idx_usuarios, qtd_dias;
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
            case 3: 
                    subsubopcao = controleEmprestimoDevolucao(); 

                    switch (subsubopcao) {
                        case 1: realizarEmprestimo();
                                break;;
                        case 2: devolucaoLivro();
                                break;
                        default: printf("Opcao invalida.\n");
                    }
                    break;
            case 4: printf("\nQual o titulo do livro para dar baixa?\n"); 
                    fgets(titulo, STR_TAM, stdin);
                    retirar_enter_string(titulo);
                    formatar_maiuscula(titulo);

                    idx = localizacaoDeExemplares(titulo);

                    if (idx < 0) {
                        printf("O livro %s nao existe!\n", titulo);
                    } else {
                        baixaDeExemplares(idx);
                    }
                    break;
            case 5: printf("Digite o criterio de busca (titulo, palavras-chave ou autor): ");
                    fgets(titulo, STR_TAM, stdin);
                    retirar_enter_string(titulo);
                    formatar_maiuscula(titulo);

                    idx_exemplares = localizacaoDeExemplares(titulo);

                    if (idx_exemplares < 0) {
                        printf("Nenhum exemplar encontrado com o criterio fornecido.\n");
                    } else {
                        dadosExemplares(idx_exemplares);
                    }
                    break;
            case 6: printf("\nQual o nome do usuario?\n");
                    fgets(nome, STR_TAM, stdin);
                    retirar_enter_string(nome);
                    formatar_maiuscula(nome);

                    idx = localizacaoDeUsuarios(nome);

                    if (idx < 0) {
                        printf("\nO usuario %s nao existe!\n", nome);
                    } else {
                        dadosUsuarios(idx); 
                    }
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
                    default: printf("Opcao invalida.\n");
                }
                break;
            case 0: printf("\nSaindo do sistema...\n"); 
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

// Função de controle de emprestimos e devolções
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

// Função para realizar empréstimo
void realizarEmprestimo() {
    string titulo, nome;
    int idx_exemplares, idx_usuarios, qtd_dias;

    printf("\nQual o titulo do livro?\n");
    getchar();
    fgets(titulo, STR_TAM, stdin);
    retirar_enter_string(titulo);
    formatar_maiuscula(titulo);

    idx_exemplares = localizacaoDeExemplares(titulo);

    if (idx_exemplares < 0) {
        printf("O livro %s nao existe!\n", titulo);
        return;
    }

    if (vetor_exemplares[idx_exemplares].status == true) {
        
        dadosExemplares(idx_exemplares);

        printf("\nQual o nome do usuario?\n");
        fgets(nome, STR_TAM, stdin);
        retirar_enter_string(nome);
        formatar_maiuscula(nome);

        idx_usuarios = localizacaoDeUsuarios(nome);

        if (idx_usuarios < 0) {
            printf("O usuario %s nao existe!\n", nome);
            return;
        }

        printf("\nQuantos dias o livro ficara emprestado?\n");
        scanf("%d", &qtd_dias);
        getchar(); 

        vetor_emprestimos[qtd_emprestimos] = emprestimoLivro(idx_usuarios, idx_exemplares, qtd_dias);
        qtd_emprestimos++;
        printf("\nEmprestimo realizado com sucesso!\n");
    } else {
        printf("\nO livro %s nao esta disponivel!\n", titulo);
    }
}

// Função para fazer emprestimos
struct emprestimos emprestimoLivro(int pos_usuario, int pos_exemplar, int qtd_dias)
{
    struct emprestimos novo;

    strcpy(novo.livro_titulo, vetor_exemplares[pos_exemplar].titulo);
    novo.id_usuario = vetor_usuarios[pos_usuario].id;
    novo.qtd_dias = qtd_dias;

    vetor_exemplares[pos_exemplar].status = false;

    return novo;
}

// Função para fazer devoluções
void devolucaoLivro() {
    string titulo;
    int idx_exemplar, idx_emprestimo;

    printf("\nQual o titulo do livro a ser devolvido?\n");
    getchar();
    fgets(titulo, STR_TAM, stdin);
    retirar_enter_string(titulo);
    formatar_maiuscula(titulo);

    // Localiza o exemplar pelo título
    idx_exemplar = localizacaoDeExemplares(titulo);
    if (idx_exemplar < 0) {
        printf("\nO livro %s não existe!\n", titulo);
        return;
    }

    // Verifica se o exemplar está emprestado
    if (vetor_exemplares[idx_exemplar].status == true) {
        printf("\nO livro %s já está disponivel na biblioteca!\n", titulo);
        return;
    }

    // Procura o empréstimo associado a esse exemplar
    for (idx_emprestimo = 0; idx_emprestimo < qtd_emprestimos; idx_emprestimo++) {
        if (strcmp(vetor_emprestimos[idx_emprestimo].livro_titulo, titulo) == 0) {
            vetor_exemplares[idx_exemplar].status = true;

            for (int i = idx_emprestimo; i < qtd_emprestimos - 1; i++) {
                vetor_emprestimos[i] = vetor_emprestimos[i + 1];
            }
            qtd_emprestimos--;

            printf("\nDevolucao realizada com sucesso!\n");
            return;
        }
    }

    printf("\nEmprestimo nao encontrado para o livro %s.\n", titulo);
}

// Função para cadastrar novos exemplares
struct exemplares cadastrarNovosExemplares()
{
    struct exemplares novo;

    fflush(stdin);

    printf("\nCADASTRAR EXEMPLAR:\n");
    printf("========================\n");

    printf("Titulo do livro: ");
    fgets(novo.titulo, STR_TAM, stdin);
    retirar_enter_string(novo.titulo);
    formatar_maiuscula(novo.titulo);

    printf("Editora do livro: ");
    fgets(novo.editora, STR_TAM, stdin);
    retirar_enter_string(novo.editora);
    formatar_maiuscula(novo.editora);

    printf("Ano de publicacao: ");
    fgets(novo.ano_publicacao, STR_TAM, stdin);
    retirar_enter_string(novo.ano_publicacao);
    formatar_maiuscula(novo.ano_publicacao);

    printf("Autor do livro: ");
    fgets(novo.autor, STR_TAM, stdin);
    retirar_enter_string(novo.autor);
    formatar_maiuscula(novo.autor);

    printf("Numero de paginas: ");
    fgets(novo.num_paginas, STR_TAM, stdin);
    retirar_enter_string(novo.num_paginas);
    formatar_maiuscula(novo.num_paginas);

    printf("Edicao do livro: ");
    fgets(novo.edicao, STR_TAM, stdin);
    retirar_enter_string(novo.edicao);
    formatar_maiuscula(novo.edicao);

    printf("Local de publicacao: ");
    fgets(novo.local_publicacao, STR_TAM, stdin);
    retirar_enter_string(novo.local_publicacao);
    formatar_maiuscula(novo.local_publicacao);

    printf("Palavras-chave do livro: ");
    fgets(novo.palavras_chave, STR_TAM, stdin);
    retirar_enter_string(novo.palavras_chave);
    formatar_maiuscula(novo.palavras_chave);
    
    printf("Quantidade de exemplares: ");
    scanf("%i", &novo.qtd_exemplar);
    getchar();

    novo.status = true;

    return novo;
}

// Função para cadastrar novos usuários
struct usuarios cadastrarNovosUsuarios()
{
    struct usuarios novo;

    fflush(stdin);

    printf("\nCADASTRAR USUARIO:\n");
    printf("========================\n");

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

    printf("Endereco: ");
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

// Função para dar baixa em um exemplar
void baixaDeExemplares(int posicao) 
{
    if (vetor_exemplares[posicao].qtd_exemplar > 0) {
        vetor_exemplares[posicao].qtd_exemplar--;
        if (vetor_exemplares[posicao].qtd_exemplar == 0) {
            vetor_exemplares[posicao].status = false; 
        }
        printf("\nBaixa realizada com sucesso! Exemplares restantes: %i\n", vetor_exemplares[posicao].qtd_exemplar);
    } else {
        printf("\nNão há mais exemplares disponíveis para baixa.\n");
    }
}

// Função para localizar exemplares por título, palavra-chave ou autor
int localizacaoDeExemplares(string chave)
{
    int i;

    for (i = 0; i < qtd_exemplares; i++) {
        if (strstr(vetor_exemplares[i].titulo, chave) != NULL ||
            strstr(vetor_exemplares[i].palavras_chave, chave) != NULL ||
            strstr(vetor_exemplares[i].autor, chave) != NULL) {
            return i;  
        }
    }

    return -1;
}

// Função para localizar usuários
int localizacaoDeUsuarios(string nome)
{
    int i;

    for(i = 0; i < qtd_usuarios; i++){
        if(strcmp(vetor_usuarios[i].nome, nome) == 0){
            return i;
        }
    }
    return -1;
}

// Função para os dados dos usuários
void dadosUsuarios(int posicao)
{
    printf("\nNome: %s\n", vetor_usuarios[posicao].nome);
    printf("Email: %s\n", vetor_usuarios[posicao].email);
    printf("Telefone: %s\n", vetor_usuarios[posicao].telefone);
    printf("Endereco: %s\n", vetor_usuarios[posicao].endereco);
    printf("CPF: %s\n", vetor_usuarios[posicao].cpf);
}

// Função para exibir usuários
void relatorioUsuarios()
{
    int i;

    for(i = 0; i < qtd_usuarios; i++){
        dadosUsuarios(i);
    }
}

// Função para exibir exemplares
void relatorioAcervo()
{
   int i;

    for(i = 0; i < qtd_exemplares; i++){
        dadosExemplares(i);
    } 
}

// Função para dados de exemplares
void dadosExemplares(int posicao)
{
    printf("\nTitulo: %s\n", vetor_exemplares[posicao].titulo);
    printf("Editora: %s\n", vetor_exemplares[posicao].editora);
    printf("Ano de publicacao: %s\n", vetor_exemplares[posicao].ano_publicacao);
    printf("Autor: %s\n", vetor_exemplares[posicao].autor);
    printf("Numero de paginas: %s\n", vetor_exemplares[posicao].num_paginas);
    printf("Edicao: %s\n", vetor_exemplares[posicao].edicao);
    printf("Local de publicacao: %s\n", vetor_exemplares[posicao].local_publicacao);
    printf("Palavras-chave: %s\n", vetor_exemplares[posicao].palavras_chave);
    printf("Quantidade: %i\n", vetor_exemplares[posicao].qtd_exemplar);
    printf("Status: %s\n", (vetor_exemplares[posicao].status)? "Disponivel" : "Emprestado");
}

// Função para relatório de empréstimos
void relatorioEmprestimos()
{
    int i;

    for(i = 0; i < qtd_emprestimos; i++){
        printf("\nID do cliente: %i\n", vetor_emprestimos[i].id_usuario);
        printf("Titulo do livro: %s\n", vetor_emprestimos[i].livro_titulo);
        printf("Quantidade de dias: %i\n", vetor_emprestimos[i].qtd_dias);
    }
}

// Função para relatório de pendências (livros emprestados e ainda não devolvidos na data prevista de devolução)
void relatorioPendencias() {
    int i;

    printf("\nRELATORIO DE PENDENCIAS:\n");
    printf("========================\n");

    for (i = 0; i < qtd_emprestimos; i++) {
        int idx_exemplar = localizacaoDeExemplares(vetor_emprestimos[i].livro_titulo);
        if (idx_exemplar >= 0 && vetor_exemplares[idx_exemplar].status == false) {
            printf("ID do usuario: %i\n", vetor_emprestimos[i].id_usuario);
            printf("Titulo do livro: %s\n", vetor_emprestimos[i].livro_titulo);
            printf("Dias de emprestimo: %i\n\n", vetor_emprestimos[i].qtd_dias);
        }
    }
}

// Função para relatório de livros editados em determinada faixa de ano
void relatorioLivrosEditados()
{
    int i, ano_inicial, ano_final;

    printf("\nDigite o ano inicial: ");
    scanf("%i", &ano_inicial);
    printf("Digite o ano final: ");
    scanf("%i", &ano_final);

    printf("\nLivros publicados entre %i e %i:\n", ano_inicial, ano_final);

    for(i = 0; i < qtd_exemplares; i++){
        if(vetor_exemplares[i].ano_publicacao >= ano_inicial && vetor_exemplares[i].ano_publicacao <= ano_final){
            dadosExemplares(i);
            printf("\n");
        } else {
            printf("Nenhum livro encontrado.\n");
        }
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