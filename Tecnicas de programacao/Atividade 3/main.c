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

int main(void) {
    setlocale(LC_ALL, "");

    int tamanho = 10;
    Cliente *clientes;

    clientes = malloc(tamanho * sizeof(Cliente));

    return 0;
}
