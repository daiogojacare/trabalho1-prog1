/*Considere que você foi contratado por uma empresa para desenvolver um sistema de controle de acervo de
livros. Esta empresa possui uma vasta biblioteca que é utilizada pelos seus funcionários. No entanto, todo o
controle sobre empréstimos, novas aquisições e baixa de exemplares é realizado de forma manual. O
responsável pela biblioteca precisa que você desenvolva um sistema para gerenciar o acervo de livros da
empresa. O sistema deverá permitir que sejam feitas as seguintes operações:
• Cadastro de novos exemplares;
• Cadastro de usuários da biblioteca;
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
• Relatório de usuários;
• Relatório de empréstimos;
• Relatório de pendências (livros emprestados e ainda não devolvidos na data prevista de devolução);
• Relatório de livros editados em uma determinada faixa de ano (Ex. 2020 a 2024).*/

#include <stdio.h>
#include <string.h>

//Cabeçalho das subrotinas (funções auxiliares)

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

//Função principal
int main() 
{
    int opcao;

    do { 
        printf("1. Cadastrar novos exemplares\n");
        printf("2. Cadastrar novo usuário\n");
        printf("3. Controle de empréstimo e devolução\n");
        printf("4. Baixa de exemplares\n");
        printf("5. Localizar exemplares por título, palavras-chave ou autor\n");
        printf("6. Localização de usuários por nome\n");
        printf("7. Relatórios\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

     
    } while (opcao != 0);

    return 0;
}

//Implementação de subrotinas

void cadastrarNovosExemplares()
{
    // Implementar a função para cadastrar novos exemplares
}

void cadastrarNovoUsuario()
{
    // Implementar a função para cadastrar novos usuários
}

void controleEmprestimoDevolucao()
{
    // Implementar a função para controle de empréstimo e devolução
}

void baixaDeExemplares()
{
    // Implementar a função para baixa de exemplares
}

void localizacaoDeExemplares()
{
    // Implementar a função para localização de exemplares
}

void localizacaoDeUsuarios()
{
    // Implementar a função para localização de usuários
}

void relatorioAcervo()
{
    // Implementar a função para gerar o relatório de acervo
}

void relatorioUsuarios()
{
    // Implementar a função para gerar o relatório de usuários
}

void relatorioEmprestimos()
{
    // Implementar a função para gerar o relatório de empréstimos
}

void relatorioPendencias()
{
    // Implementar a função para gerar o relatório de pendências
}

void relatorioLivrosEditados()
{
    // Implementar a função para gerar o relatório de livros editados
}