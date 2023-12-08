#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char proprietario[50];
    char combustivel[20];
    char modelo[50];
    char cor[20];
    char chassi[20];
    int ano;
    char placa[8];
} Veiculo;

typedef struct Node {
    Veiculo veiculo;
    struct Node* proximo;
} Node;

Node* inicializarLista() {
    return NULL;
}

Node* adicionarVeiculo(Node* lista, Veiculo novoVeiculo) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória para o novo veículo.\n");
        exit(EXIT_FAILURE);
    }

    novoNo->veiculo = novoVeiculo;
    novoNo->proximo = lista;

    return novoNo;
}

void listarProprietariosDiesel2010(Node* lista) {
    printf("\nProprietarios de carros do ano de 2010 ou posterior e movidos a diesel:\n");
    while (lista != NULL) {
        if (lista->veiculo.ano >= 2010 && strcmp(lista->veiculo.combustivel, "diesel") == 0) {
            printf("%s\n", lista->veiculo.proprietario);
        }
        lista = lista->proximo;
    }
}

void listarPlacasJ(Node* lista) {
    printf("\nPlacas que comecam com J e terminam com 0, 2, 4 ou 7, junto com seus proprietarios:\n");
    while (lista != NULL) {
        if (lista->veiculo.placa[0] == 'J' &&
            (lista->veiculo.placa[6] == '0' || lista->veiculo.placa[6] == '2' || lista->veiculo.placa[6] == '4' || lista->veiculo.placa[6] == '7')) {
            printf("Placa: %s, Proprietario: %s\n", lista->veiculo.placa, lista->veiculo.proprietario);
        }
        lista = lista->proximo;
    }
}

void listarModeloCorVogalSomaPar(Node* lista) {
    printf("\nModelo e cor dos veiculos com placas que tem como segunda letra uma vogal e cuja soma dos valores numericos e par:\n");
    while (lista != NULL) {
        char segundaLetraPlaca = lista->veiculo.placa[1];
        int somaDigitos = 0;
        for (int i = 0; i < 7; i++) {
            if (isdigit(lista->veiculo.placa[i])) {
                somaDigitos += lista->veiculo.placa[i] - '0';
            }
        }

        if ((segundaLetraPlaca == 'A' || segundaLetraPlaca == 'E' || segundaLetraPlaca == 'I' || segundaLetraPlaca == 'O' || segundaLetraPlaca == 'U') &&
            somaDigitos % 2 == 0) {
            printf("Modelo: %s, Cor: %s\n", lista->veiculo.modelo, lista->veiculo.cor);
        }
        lista = lista->proximo;
    }
}

void trocarProprietarioSemZero(Node* lista, char chassiTroca[], char novoProprietario[]) {
    while (lista != NULL) {
        if (strcmp(lista->veiculo.chassi, chassiTroca) == 0) {
            int temZero = 0;
            for (int i = 0; i < 7; i++) {
                if (lista->veiculo.placa[i] == '0') {
                    temZero = 1;
                    break;
                }
            }

            if (!temZero) {
                strcpy(lista->veiculo.proprietario, novoProprietario);
                printf("Proprietario do veiculo com chassi %s alterado para %s.\n", chassiTroca, novoProprietario);
            } else {
                printf("Troca de proprietario nao permitida para veiculos com placas que possuam dígito zero.\n");
            }
            return;
        }
        lista = lista->proximo;
    }

    printf("Veiculo com chassi %s nao encontrado.\n", chassiTroca);
}


void liberarLista(Node* lista) {
    Node* atual = lista;
    while (atual != NULL) {
        Node* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}

int main() {
    Node* listaVeiculos = inicializarLista();

    Veiculo veiculo1 = {"Proprietario1", "diesel", "Modelo1", "Cor1", "Chassi1", 2012, "JAB1234"};
    Veiculo veiculo2 = {"Proprietario2", "gasolina", "Modelo2", "Cor2", "Chassi2", 2015, "JCD5678"};
    Veiculo veiculo3 = {"Proprietario3", "diesel", "Modelo3", "Cor3", "Chassi3", 2010, "JEF9870"};

    listaVeiculos = adicionarVeiculo(listaVeiculos, veiculo1);
    listaVeiculos = adicionarVeiculo(listaVeiculos, veiculo2);
    listaVeiculos = adicionarVeiculo(listaVeiculos, veiculo3);

    listarProprietariosDiesel2010(listaVeiculos);

    listarPlacasJ(listaVeiculos);

    listarModeloCorVogalSomaPar(listaVeiculos);

    char chassiTroca[20];
    char novoProprietario[50];

    printf("\nDigite o chassi do veiculo para a troca de proprietario: ");
    scanf("%s", chassiTroca);
    printf("Digite o novo proprietario: ");
    scanf("%s", novoProprietario);

    trocarProprietarioSemZero(listaVeiculos, chassiTroca, novoProprietario);

    liberarLista(listaVeiculos);

    return 0;
}
