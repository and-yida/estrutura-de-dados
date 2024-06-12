#include <stdio.h>
#define MAX 100

typedef int tipoelem;

// estrutura de cada nó da lista: elemento e índice do próximo
struct no {
    tipoelem elem;
    int prox;
};

// estrutura da lista: vetor de nós, índice do primeiro nó e do primeiro disponível
struct lista {
    struct no vetor[MAX];
    int prim;
    int dispo;
};

// inicializa a lista, configurando os índices de início e disponíveis
void InicializaLista(struct lista *L) {
    L->prim = -1;       //lista vazia, então o índice do primeiro elemento é -1
    L->dispo = 0;       // o primeiro espaço disponível é o índice 0
    // encadeamento dos elementos
    for (int i = 0; i < MAX-1; i++) {
        L->vetor[i].prox = i + 1;       // cada nó aponta para o próximo
        
    }
    L->vetor[MAX-1].prox = -1;      // o último elemento da lista aponta para -1
}

// insere elemento na lista de forma ordenada
void InsercaoLista(struct lista *L, tipoelem elem) {
    int aux, atual, anterior = -1;
    // verifica se há espaço disponível para inserção
    if (L->dispo != -1) {
        aux = L->dispo;
        L->vetor[aux].elem = elem;      // insere o elemento na posição dispo
        L->dispo = L->vetor[aux].prox;      // atualiza dispo
        L->vetor[aux].prox = -1;        // define o próximo do novo elemento como -1 (final)

        // se a lista está vazia, insere o elemento no início
        if (L->prim == -1) {
            L->prim = aux;
        } else {
            // caso contrário, encontra a posição correta para inserção ordenada
            atual = L->prim;
            while (atual != -1 && L->vetor[atual].elem < elem) {
                anterior = atual;
                atual = L->vetor[atual].prox;
            }
            // insere no início se necessário
            if (anterior == -1) {
                L->vetor[aux].prox = L->prim;
                L->prim = aux;
            } else {
                // ou no meio/fim, ajustando os ponteiros adequadamente
                L->vetor[aux].prox = L->vetor[anterior].prox;
                L->vetor[anterior].prox = aux;
            }
        }
    }
}

// remove um elemento específico da lista
void RemocaoLista(struct lista *L, tipoelem elem) {
    int atual = L->prim, anterior = -1;
    // procura pelo elemento a ser removido, mantendo o controle do anterior
    while (atual != -1 && L->vetor[atual].elem != elem) {
        anterior = atual;
        atual = L->vetor[atual].prox;
    }

    if (atual != -1) {
        if (anterior == -1) {       // remoção do primeiro elemento
            L->prim = L->vetor[atual].prox;
        } else {        // demais casos
            L->vetor[anterior].prox = L->vetor[atual].prox;
        }
        // índice do elemento removido passa a ser disponível
        L->vetor[atual].prox = L->dispo;
        L->dispo = atual;
    }
}

// imprime todos os elementos da lista.
void ImpressaoLista(struct lista *L) {
    int atual = L->prim;

    if (atual == -1) {
        printf("Lista vazia\n");
    }

    while (atual != -1) {
        printf("%d ", L->vetor[atual].elem);
        atual = L->vetor[atual].prox;
    }
    printf("\n");
}

// conta quantidade de elementos da lista
int ContaElementosLista(struct lista *L) {
    int contador = 0;
    int atual = L->prim;

    if (atual == -1) {
        printf("Lista vazia\n");
        printf("\n");
        return contador;
    }

    while (atual != -1) {
        contador++;
        atual = L->vetor[atual].prox;
    }
    printf("A lista possui %d elementos\n", contador);
    return contador;
}


// função principal: exibe um menu para operações na lista
int main() {
    struct lista L;
    int escolha;
    tipoelem elem;

    InicializaLista(&L);

    while(1) {
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Imprimir\n");
        printf("4 - Contar elementos\n");
        printf("5 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch(escolha) {
            case 1:     // inserção.
                printf("Elemento a inserir: ");
                scanf("%d", &elem);
                InsercaoLista(&L, elem);
                break;
            case 2:     // remoção
                printf("Elemento a remover: ");
                scanf("%d", &elem);
                RemocaoLista(&L, elem);
                break;
            case 3:     // impressão
                ImpressaoLista(&L);
                break;
            case 4:     // contagem
                ContaElementosLista(&L);
                break;   
            case 5:     // saída.
                return 0;
            default:
                printf("Opção inválida!\n");
        }
    }

    return 0;
}