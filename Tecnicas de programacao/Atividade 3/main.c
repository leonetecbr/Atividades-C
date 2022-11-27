#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct {
    char nome[31];
    unsigned int ano;
    unsigned int gastos;
} Cliente;

void mostrarCliente(Cliente cliente, int indice, bool quebraDeLinha){
    printf("Cliente %d\n", indice + 1);
    printf("    Nome: %s\n", cliente.nome);
    printf("    Ano: %d\n", cliente.ano);
    printf("    Gastos: %d\n", cliente.gastos);

    if(quebraDeLinha) printf("\n");

    return;
}

void melhorComprador(Cliente clientes[], int tamanho){
    int maiorValor = 0;
    int indice = 0;

    if (clientes[0].ano == 0) printf("\nNao ha clientes cadastrados!");

    for (int i = 0; i < tamanho; ++i) {
        if (clientes[i].ano == 0) break;
        if (clientes[i].gastos > maiorValor){
            maiorValor = clientes[i].gastos;
            indice = i;
        }
    }

    printf("O melhor comprador e: \n");
    printf("\n");
    mostrarCliente(clientes[indice], indice, false);

    return;
}

void zerarGastos(Cliente clientes[], int tamanho){
    for (int i = 0; i < tamanho; ++i) {
        if (clientes[i].ano != 0) clientes[i].gastos = 0;
        else break;
    }

    printf("\nGastos dos clientes zerados com sucesso!");

    return;
}

void listarClientes(Cliente clientes[], int tamanho) {
    for (int i = 0; i < tamanho; i++) mostrarCliente(clientes[i], i, i != tamanho - 1);

    return;
}

void preencherClientes(Cliente clientes[], int tamanho) {
    for (int i = tamanho - 1; i >= tamanho - 10; i--) {
        strcpy(clientes[i].nome, "NULL");
        clientes[i].ano = 0;
        clientes[i].gastos = 0;
    }

    return;
}

bool validaCliente(Cliente clientes[],int tamanho, int indice) {
    if (indice > tamanho -1 || clientes[indice].ano == 0){
        printf("\nCliente %d nao existe", indice + 1);
        return false;
    }

    return true;
}

void alterarCliente(Cliente clientes[], int tamanho, int indice){
    if (!validaCliente(clientes, tamanho, indice)) return;

    printf("\nDigite o novo montante de gastos do cliente: "); scanf("%d", &clientes[indice].gastos);
    printf("\nCliente %d alterado com sucesso", indice + 1);

    return;
}

void removerCliente(Cliente clientes[], int tamanho, int indice) {
    if (!validaCliente(clientes, tamanho, indice)) return;

    if (indice + 2 != tamanho && clientes[indice + 1].ano != 0) {
        for (int i = indice; i < tamanho; i++){
            if (i + 2 != tamanho) clientes[i] = clientes[i + 1];
            else {
                strcpy(clientes[i].nome, "NULL");
                clientes[i].ano = 0;
                clientes[i].gastos = 0;
            }
        }
    } else {
        strcpy(clientes[indice].nome, "NULL");
        clientes[indice].ano = 0;
        clientes[indice].gastos = 0;
    }

    printf("\nCliente %d removido com sucesso!", indice + 1);

    return;
}

void inserirCliente(Cliente clientes[], int *tamanho) {
    if (clientes[*tamanho - 1].ano != 0){
        *tamanho += 10;
        clientes = realloc(clientes, sizeof(Cliente) * *tamanho);
        preencherClientes(clientes, *tamanho);
    }

    Cliente cliente;
    printf("Nome:"); scanf("%s", cliente.nome);
    printf("Ano:"); scanf("%d", &cliente.ano);
    printf("Gastos:"); scanf("%d", &cliente.gastos);

    for (int i = 0; i < *tamanho; i++) {
        if (clientes[i].ano == 0) {
            clientes[i] = cliente;
            break;
        }
    }

    printf("\nCliente inserido com sucesso!");

    return;
}

int question(void) {
    int opcao = 0;

    printf("O que voce deseja fazer ?\n\n1 - Cadastrar um cliente\n2 - Listar clientes cadastrados"
           "\n3 - Remover um cliente\n4 - Alterar gastos de um cliente\n5 - Zerar montante de gastos"
           "\n6 - Mostra o melhor comprador\n7 - Exibir gastos de um cliente\n8 - Sair\n\n");

    while (!(opcao == 1 || opcao == 2 || opcao == 3 || opcao == 4 || opcao == 5 || opcao == 6 || opcao == 7 || opcao == 8)) {
        printf("Digite uma opcao valida:"); scanf("%d", &opcao);
    }

    return opcao;
}

int main(void) {
    setlocale(LC_ALL, "");

    bool continuar = true;
    int tamanho = 10, opcao;
    Cliente *clientes;

    clientes = malloc(tamanho * sizeof(Cliente));
    preencherClientes(clientes, tamanho);

    printf("============================================ Clientes ============================================\n");

    while (continuar) {
        opcao = question();
        printf("\n");

        int indice;

        switch (opcao) {
            case 1:
                inserirCliente(clientes, &tamanho);
                break;
            case 2:
                listarClientes(clientes, tamanho);
                break;
            case 3:
                printf("Digite o id do cliente que deseja remover:"); scanf("%d", &indice);
                removerCliente(clientes, tamanho, indice - 1);
                break;
            case 4:
                printf("Digite o id do cliente que deseja alterar:"); scanf("%d", &indice);
                alterarCliente(clientes, tamanho, indice - 1);
                break;
            case 5:
                zerarGastos(clientes, tamanho);
                break;
            case 6:
                melhorComprador(clientes, tamanho);
                break;
            case 7:
                printf("Digite o id do cliente que deseja exibir:"); scanf("%d", &indice);
                printf("\n");
                mostrarCliente(clientes[indice - 1], indice - 1, false);
                break;
            case 8:
                printf("Ate mais! ;)");
                continuar = false;
                break;
        }

        printf("\n================================================================================================\n");
    }

    return 0;
}
