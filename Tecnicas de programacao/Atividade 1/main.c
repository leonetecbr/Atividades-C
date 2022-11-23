#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

typedef struct {
    char marca[10];
    char modelo[10];
    unsigned int ano;
    char placa[9];
} Veiculo;

void mostrarVeiculo(Veiculo veiculo, int indice) {
    printf("Veiculo %d\n", indice);
    printf("    Marca: %s\n", veiculo.marca);
    printf("    Modelo: %s\n", veiculo.modelo);
    printf("    Ano: %d\n", veiculo.ano);
    printf("    Placa: %s\n", veiculo.placa);

    if (indice != 9) printf("\n");
}

void listarVeiculosPorModelo(Veiculo veiculos[10], char modelo[10]) {
    for (int i = 0; i < 10; i++) {
        if (veiculos[i].modelo == modelo) mostrarVeiculo(veiculos[i], i);
    }
}

void listarVeiculosAPartirDoAno(Veiculo veiculos[10], int ano) {
    for (int i = 0; i < 10; i++) {
        if (veiculos[i].ano >= ano) mostrarVeiculo(veiculos[i], i);
    }
}

void listarVeiculosPorAno(Veiculo veiculos[10], int ano) {
    for (int i = 0; i < 10; i++) {
        if (veiculos[i].ano == ano) mostrarVeiculo(veiculos[i], i);
    }
}

void inserirVeiculo(Veiculo carros[10]) {
    Veiculo carro;
    printf("Marca:"); scanf("%s", carro.marca);
    printf("Modelo:"); scanf("%s", carro.modelo);
    printf("Ano:"); scanf("%d", &carro.ano);
    printf("Placa:"); scanf("%s", carro.placa);

    for (int i = 0; i < 10; ++i) {
        if (carros[i].ano == 0) {
            carros[i] = carro;
            break;
        } else if (carros[i].modelo > carro.modelo) {
            int j = i;

            while (carros[i + j].ano != 0) j++;
            for (; j > 0; j--) carros[i + j] = carros[i + j - 1];

            carros[i] = carro;
            break;
        }
    }

    printf("\nVeiculo inserido com sucesso!");
}

void listarVeiculos(Veiculo veiculos[10]) {
    for (int i = 0; i < 10; i++) mostrarVeiculo(veiculos[i], i);
}

int question(void) {
    int opcao = 0;

    printf("O que voce deseja fazer ?\n\n1 - Listar veiculos cadastrados\n2 - Cadastrar veiculo\n"
           "3 - Filtrar veiculos por ano\n4 - Filtrar veiculos a partir de x ano\n"
           "5 - Filtrar veiculos por modelo\n6 - Sair\n\n");

    while (!(opcao == 1 || opcao == 2 || opcao == 3 || opcao == 4 || opcao == 5 || opcao == 6)) {
        printf("Digite uma opcao valida:"); scanf("%d", &opcao);
    }

    return opcao;
}

int main(void) {
    setlocale(LC_ALL, "");

    int opcao;
    bool continuar = true;
    Veiculo carros[10];

    for (int i = 0; i < 10; i++) {
        strcpy(carros[i].modelo, "NULL");
        carros[i].ano = 0;
        strcpy(carros[i].marca, "NULL");
        strcpy(carros[i].placa, "NULL");
    }

    printf("============================================ Veiculos ============================================\n");

    while (continuar) {
        opcao = question();
        printf("\n");
        int ano;

        switch (opcao) {
            case 1:
                listarVeiculos(carros);
                break;
            case 2:
                if (carros[9].ano != 0) printf("Não é possível inserir mais veículos.\n");
                else inserirVeiculo(carros);
                break;
            case 3:
                printf("Digite o ano:"); scanf("%d", &ano);
                listarVeiculosPorAno(carros, ano);
                break;
            case 4:
                printf("Digite o ano:"); scanf("%d", &ano);
                listarVeiculosAPartirDoAno(carros, ano);
                break;
            case 5:
                printf("Digite o modelo:"); char modelo[10]; scanf("%s", modelo);
                listarVeiculosPorModelo(carros, modelo);
                break;
            case 6:
                printf("Ate mais! ;)");
                continuar = false;
                break;
        }

        printf("\n================================================================================================\n");
    }

    return 0;
}