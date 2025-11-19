#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 50
#define TAM_CPF 15

// Estrutura do paciente
typedef struct Paciente {
    int id;
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    int idade;
    struct Paciente *prox;
} Paciente;

Paciente *inicio = NULL;  // ponteiro inicial da lista

// Função para criar um novo paciente
Paciente* criarPaciente(int id, char nome[], char cpf[], int idade) {
    Paciente *novo = (Paciente*) malloc(sizeof(Paciente));
    if (novo == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novo->id = id;
    strcpy(novo->nome, nome);
    strcpy(novo->cpf, cpf);
    novo->idade = idade;
    novo->prox = NULL;
    return novo;
}

// Inserir paciente no final da lista
void incluirPaciente(int id, char nome[], char cpf[], int idade) {
    Paciente *novo = criarPaciente(id, nome, cpf, idade);

    if (inicio == NULL) {
        inicio = novo;
    } else {
        Paciente *atual = inicio;
        while (atual->prox != NULL)
            atual = atual->prox;
        atual->prox = novo;
    }
    printf("Paciente cadastrado com sucesso!\n");
}

// Listar todos os pacientes
void listarPacientes() {
    if (inicio == NULL) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    Paciente *atual = inicio;
    printf("\n=== LISTA DE PACIENTES ===\n");
    while (atual != NULL) {
        printf("ID: %d\n", atual->id);
        printf("Nome: %s\n", atual->nome);
        printf("CPF: %s\n", atual->cpf);
        printf("Idade: %d\n", atual->idade);
        printf("---------------------------\n");
        atual = atual->prox;
    }
}

// Consultar paciente pelo ID
Paciente* buscarPaciente(int id) {
    Paciente *atual = inicio;
    while (atual != NULL) {
        if (atual->id == id)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}

// Alterar dados do paciente
void alterarPaciente(int id) {
    Paciente *pac = buscarPaciente(id);
    if (pac == NULL) {
        printf("Paciente não encontrado!\n");
        return;
    }

    printf("Digite o novo nome: ");
    fflush(stdin);
    fgets(pac->nome, TAM_NOME, stdin);
    pac->nome[strcspn(pac->nome, "\n")] = '\0';

    printf("Digite o novo CPF: ");
    fgets(pac->cpf, TAM_CPF, stdin);
    pac->cpf[strcspn(pac->cpf, "\n")] = '\0';

    printf("Digite a nova idade: ");
    scanf("%d", &pac->idade);

    printf("Dados atualizados com sucesso!\n");
}

// Remover paciente pelo ID
void removerPaciente(int id) {
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    Paciente *atual = inicio, *anterior = NULL;

    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Paciente não encontrado.\n");
        return;
    }

    if (anterior == NULL) {
        inicio = atual->prox; // removendo o primeiro
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Paciente removido com sucesso!\n");
}

// Menu principal
void menu() {
    int opcao, id, idade;
    char nome[TAM_NOME], cpf[TAM_CPF];

    do {
        printf("\n=== SISTEMA HOSPITALAR ===\n");
        printf("1 - Incluir paciente\n");
        printf("2 - Listar pacientes\n");
        printf("3 - Consultar paciente\n");
        printf("4 - Alterar paciente\n");
        printf("5 - Remover paciente\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // consome o '\n'

        switch (opcao) {
            case 1:
                printf("ID: ");
                scanf("%d", &id);
                getchar();
                printf("Nome: ");
                fgets(nome, TAM_NOME, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("CPF: ");
                fgets(cpf, TAM_CPF, stdin);
                cpf[strcspn(cpf, "\n")] = '\0';
                printf("Idade: ");
                scanf("%d", &idade);
                incluirPaciente(id, nome, cpf, idade);
                break;

            case 2:
                listarPacientes();
                break;

            case 3:
                printf("Digite o ID para consulta: ");
                scanf("%d", &id);
                {
                    Paciente *p = buscarPaciente(id);
                    if (p != NULL) {
                        printf("Nome: %s\nCPF: %s\nIdade: %d\n", p->nome, p->cpf, p->idade);
                    } else {
                        printf("Paciente não encontrado.\n");
                    }
                }
                break;

            case 4:
                printf("Digite o ID para alterar: ");
                scanf("%d", &id);
                getchar();
                alterarPaciente(id);
                break;

            case 5:
                printf("Digite o ID para remover: ");
                scanf("%d", &id);
                removerPaciente(id);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

// Função principal
int main() {
    menu();
    return 0;
}

