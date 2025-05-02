#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Cliente {
    char nome[100];
    int idade;
    char email[100];
    char telefone[30];
};

int main() {
    struct Cliente clientes[100];
    char linha[300];
    int i = 0, j, total = 0;
    FILE *arquivo;

    arquivo = fopen("clientes.csv", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    while (fgets(linha, 300, arquivo)) {
        char *parte;

        parte = strtok(linha, ",");
        strcpy(clientes[i].nome, parte);

        parte = strtok(NULL, ",");
        clientes[i].idade = atoi(parte);

        parte = strtok(NULL, ",");
        strcpy(clientes[i].email, parte);

        parte = strtok(NULL, ",");
        if (parte != NULL) {
            int len = strlen(parte);
            if (parte[len - 1] == '\n') {
                parte[len - 1] = '\0';
            }
            strcpy(clientes[i].telefone, parte);
        }

        i++;
        total++;
    }

    fclose(arquivo);

    int opcao;
    printf("1 - Nome\n2 - Idade\n3 - Email\nEscolha para ordenar: ");
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > 3) {
        printf("OpÃ§Ã£o invÃ¡lida!\n");
        return 1;
    }

    for (i = 0; i < total - 1; i++) {
        for (j = i + 1; j < total; j++) {
            int trocar = 0;

            if (opcao == 1 && strcmp(clientes[i].nome, clientes[j].nome) > 0) {
                trocar = 1;
            } else if (opcao == 2 && clientes[i].idade > clientes[j].idade) {
                trocar = 1;
            } else if (opcao == 3 && strcmp(clientes[i].email, clientes[j].email) > 0) {
                trocar = 1;
            }

            if (trocar) {
                struct Cliente temp = clientes[i];
                clientes[i] = clientes[j];
                clientes[j] = temp;
            }
        }
    }

    char nomeArquivo[100];
    printf("Digite nome do arquivo de saÃ­da: ");
    scanf("%s", nomeArquivo);

    FILE *saida = fopen(nomeArquivo, "w");
    if (saida == NULL) {
        printf("Erro ao criar o arquivo\n");
        return 1;
    }

    for (i = 0; i < total; i++) {
        fprintf(saida, "%s,%d,%s,%s\n", clientes[i].nome, clientes[i].idade, clientes[i].email, clientes[i].telefone);
    }

    fclose(saida);

    printf("Arquivo salvo!\n");

    return 0;
}
