#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>


#define STR_T   80
#define T       30


typedef char string[STR_T];

struct carro {
  string marca;
  string modelo;
  int ano_fabricacao;
  float vlr_aluguel;
  bool status;   // false - se alugado; true - se dispon�vel
};

struct cliente {
    int id;
    string nome;
    string telefone;
    string endereco;
    string cpf;
};

struct aluguel {
  int id_cliente;
  string carro_modelo;
  int qtd_dias;
  float vlr_aluguel;
};

// Vari�veis globais
struct carro vetor_carros[T];
struct cliente vetor_clientes[T];
struct aluguel vetor_alugueis[T];

int qtd_clientes = 0, qtd_carros = 0, qtd_alugueis = 0;

// Cabe�alho das fun��es auxiliares
char menu();
struct carro criar_novo_carro();
struct cliente criar_novo_cliente();
void listar_carros_cadastrados();
void listar_clientes_cadastrados();
int localizar_carro_por_modelo(string modelo);
int localizar_cliente_por_nome(string nome);
void mostrar_dados_carro(int posicao);
void mostrar_dados_cliente(int posicao);
void retirar_enter_string(string str);
void formatar_maiuscula(string str);
struct aluguel alugar_veiculo(int pos_cliente, int pos_veiculo, int qtd_dias);
void mostrar_alugueis();


int main()
{
    char opcao;
    string modelo, nome;
    int idx, carro_idx, cliente_idx, qtd_dias;

    do {
        opcao = menu();

        switch (opcao) {
            case 'a':
            case 'A': vetor_carros[qtd_carros] = criar_novo_carro();
                      qtd_carros++;
                      break;

            case 'b':
            case 'B': listar_carros_cadastrados();
                      break;

            case 'c':
            case 'C': vetor_clientes[qtd_clientes] = criar_novo_cliente();
                      qtd_clientes++;
                      break;

            case 'd':
            case 'D': listar_clientes_cadastrados();
                      break;

            case 'e':
            case 'E': printf("Qual o modelo do carro que vc procura? ");
                      fgets(modelo, STR_T, stdin);
                      retirar_enter_string(modelo);
                      formatar_maiuscula(modelo);

                      idx = localizar_carro_por_modelo(modelo);
                      if (idx < 0) {
                        printf("O veiculo %s nao foi encontrado!\n", modelo);
                      }
                      else {
                        mostrar_dados_carro(idx);
                      }

                      break;

            case 'f':
            case 'F': printf("Qual o nome do cliente? ");
                      fgets(nome, STR_T, stdin);
                      retirar_enter_string(nome);
                      formatar_maiuscula(nome);

                      idx = localizar_cliente_por_nome(nome);

                      if (idx < 0) {
                        printf("O cliente %s nao foi encontrado\n", nome);
                      }
                      else {
                        mostrar_dados_cliente(idx);
                      }

                      break;

            case 'g':
            case 'G': printf("Qual o modelo de veiculo que quer locar? ");
                      fgets(modelo, STR_T, stdin);
                      retirar_enter_string(modelo);
                      formatar_maiuscula(modelo);

                      carro_idx = localizar_carro_por_modelo(modelo);
                      if (carro_idx < 0) {
                        printf("O veiculo %s nao existe!\n", modelo);
                      }
                      else {
                        if (vetor_carros[carro_idx].status == true) {
                            printf("Qual o nome do cliente? ");
                            fgets(nome, STR_T, stdin);
                            retirar_enter_string(nome);
                            formatar_maiuscula(nome);

                            cliente_idx = localizar_cliente_por_nome(nome);

                            if (cliente_idx < 0) {
                                printf("O cliente %s n�o existe!\n", nome);
                            }
                            else {
                                printf("Por quantos dias vai alugar o carro %s?\n", modelo);
                                scanf("%i", &qtd_dias);
                                vetor_alugueis[qtd_alugueis] = alugar_veiculo(cliente_idx, carro_idx, qtd_dias);
                                qtd_alugueis++;
                            }

                        }
                        else {
                            printf("O veiculo %s nao esta disponivel para aluguel!\n", modelo);
                        }
                      }

                      break;

            case 'h':
            case 'H': mostrar_alugueis();
                      break;

            case 'x':
            case 'X': printf("Tchau!");
                      break;

            default: printf("Opcao invalida!!!\n\n");

        }

    } while (opcao != 'x' && opcao != 'X');

    return 0;
}


// Implementa��o das fun��es auxiliares
char menu()
{
    char opc;

    printf("[a] - Incluir novo veiculo\n");
    printf("[b] - Mostrar veiculos cadastrados\n");
    printf("[c] - Incluir novo cliente\n");
    printf("[d] - Mostrar clientes cadastrados\n");
    printf("[e] - Localizar carro por modelo\n");
    printf("[f] - Localizar cliente por nome\n");
    printf("[g] - Alugar veiculo\n");
    printf("[h] - Mostrar alugueis\n");
    printf("[x] - Sair do programa\n");
    printf(":: ");
    fflush(stdin);
    scanf("%c", &opc);
    getchar();

    return opc;
}

struct carro criar_novo_carro()
{
    struct carro novo;

    fflush(stdin);

    printf("Marca do carro.............: ");
    fgets(novo.marca, STR_T, stdin);
    retirar_enter_string(novo.marca);
    formatar_maiuscula(novo.marca);


    printf("Modelo do carro............: ");
    fgets(novo.modelo, STR_T, stdin);
    retirar_enter_string(novo.modelo);
    formatar_maiuscula(novo.modelo);

    printf("Ano de fabricacao..........: ");
    scanf("%i", &novo.ano_fabricacao);

    printf("Valor da diaria............: ");
    scanf("%f", &novo.vlr_aluguel);

    novo.status = true;

    return novo;
}

struct cliente criar_novo_cliente()
{
    struct cliente novo;

    fflush(stdin);

    printf("Nome do cliente............: ");
    fgets(novo.nome, STR_T, stdin);
    retirar_enter_string(novo.nome);
    formatar_maiuscula(novo.nome);


    printf("Telefone...................: ");
    fgets(novo.telefone, STR_T, stdin);
    retirar_enter_string(novo.telefone);
    formatar_maiuscula(novo.telefone);


    printf("Endereco...................: ");
    fgets(novo.endereco, STR_T, stdin);
    retirar_enter_string(novo.endereco);
    formatar_maiuscula(novo.endereco);

    printf("CPF........................: ");
    fgets(novo.cpf, STR_T, stdin);
    retirar_enter_string(novo.cpf);
    formatar_maiuscula(novo.cpf);

    novo.id = qtd_clientes + 1;

    return novo;
}

void listar_carros_cadastrados()
{
    int i;

    for (i = 0; i < qtd_carros; i++) {
        mostrar_dados_carro(i);
    }
}

void listar_clientes_cadastrados()
{
    int i;

    for (i = 0; i < qtd_clientes; i++) {
        mostrar_dados_cliente(i);
    }
}

int localizar_carro_por_modelo(string modelo)
{
    int i;

    for (i = 0; i < qtd_carros; i++) {
        if (strcmp(vetor_carros[i].modelo, modelo) == 0) {
            return i;
        }
    }

    return -1;
}

void mostrar_dados_carro(int posicao)
{
    printf("Marca do carro.....: %s\n", vetor_carros[posicao].marca);
    printf("Modelo do carro....: %s\n", vetor_carros[posicao].modelo);
    printf("Ano de fabricacao..: %i\n", vetor_carros[posicao].ano_fabricacao);
    printf("Valor da diaria....: %.2f\n", vetor_carros[posicao].vlr_aluguel);
    printf("Status.............: %i\n\n", vetor_carros[posicao].status);
}

void retirar_enter_string(string str)
{
    int tamanho;

    tamanho = strlen(str);

    str[tamanho - 1] = '\0';
}

void formatar_maiuscula(string str)
{
    int i;

    for (i = 0; i < strlen(str); i++) {
        str[i] = toupper(str[i]);
    }
}

int localizar_cliente_por_nome(string nome)
{
    int i;

    for (i = 0; i < qtd_clientes; i++) {
        if (strcmp(vetor_clientes[i].nome, nome) == 0) {
            return i;
        }
    }

    return -1;
}


void mostrar_dados_cliente(int posicao)
{
    printf("ID do cliente....: %i\n", vetor_clientes[posicao].id);
    printf("Nome do cliente..: %s\n", vetor_clientes[posicao].nome);
    printf("Telefone.........: %s\n", vetor_clientes[posicao].telefone);
    printf("Endereco.........: %s\n", vetor_clientes[posicao].endereco);
    printf("CPF..............: %s\n\n", vetor_clientes[posicao].cpf);
}

struct aluguel alugar_veiculo(int pos_cliente, int pos_veiculo, int qtd_dias)
{
    struct aluguel novo;

    strcpy(novo.carro_modelo, vetor_carros[pos_veiculo].modelo);
    novo.id_cliente     = vetor_clientes[pos_cliente].id;
    novo.qtd_dias       = qtd_dias;
    novo.vlr_aluguel    = qtd_dias * vetor_carros[pos_veiculo].vlr_aluguel;

    vetor_carros[pos_veiculo].status = false;  // Indica que o carro est� alugado

    return novo;
}

void mostrar_alugueis()
{
    int i;
    for (i = 0; i < qtd_alugueis; i++) {
        printf("Modelo do carro............: %s\n", vetor_alugueis[i].carro_modelo);
        printf("Identificacao do cliente...: %d\n", vetor_alugueis[i].id_cliente);
        printf("Quantidade de dias alugado.: %d\n", vetor_alugueis[i].qtd_dias);
        printf("Valor total do aluguel.....: %2.f\n", vetor_alugueis[i].vlr_aluguel);
    }
}