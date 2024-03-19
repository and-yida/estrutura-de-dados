#include <stdio.h>
#include <stdlib.h>

// ----IMPLEMENTAÇÃO ESTÁTICA----

#define MAX 100

struct no{
    int elem;
    int prox;
};

typedef struct lista{
    struct no vetor[MAX];
    int prim;
    int dispo;
} Lista;

Lista* inicializa(){
    Lista* L;
    int i = 1;
    int i;
    for(i = 0; i<MAX-1; i++){     // prepara o encadeamento até o penúltimo elemento
        L->vetor[i].prox = i+1;
    }
    L->vetor[i].prox = -1;      // último elemento não possui próximo
    L->prim = -1;       // atualiza os campos prim e dispo da lista
    L->dispo = 0;
}

void imprime(Lista* L){
    int atual = L->prim;
    if(atual == -1) printf("\nLista vazia!"); 
    while(atual != -1){
        printf("\n %d", L->vetor[atual].elem);
        atual = L->vetor[atual].prox;
    }
}

// Escreva uma rotina recursiva para determinar o número de elementos de uma lista.
int quantidade_elementos(Lista* L, int quantidade, int posicao){
    int q, atual = L->prim;
    if(atual == -1) return quantidade;
    else{
        q++;
        atual++;
        quantidade_elementos(L, q, atual); 
    }
}

// Escreva uma rotina que receba uma lista e um número X e retorne o número de nós da lista que possuem o número X.
int busca_valor(Lista* L, int valor){
    int atual = L->prim;
    if(atual == -1) return 0;
    int contador = 0;
    while(atual != -1){
        if(L->vetor[atual].elem == valor){
            contador++;
        }
        atual = L->vetor[atual].prox;
    }
    return contador;
}

// Escreva uma rotina que receba uma lista e um número X e retorne o número de nós da lista que possuem valores menores do que o número X.
int busca_menores_valores(Lista* L, int valor){
    int atual = L->prim;
    int elemento = L->vetor[atual].elem;
    if(atual == -1) return 0;
    int contador = 0;
    while(atual != -1 && elemento < valor){
        contador++;
        atual = L->vetor[atual].prox;
        elemento = L->vetor[atual].elem;
    }
    return contador;
}

// Escreva uma rotina que receba uma lista e um número X e retorne o número de nós da lista que possuem valores maiores do que o número X.
int busca_maiores_valores(Lista* L, int valor){
    int atual = L->prim;
    if(atual == -1) return 0;
    int contador = 0;
    while(atual != -1){
        if(L->vetor[atual].elem > valor){
            contador++;
        }
        atual = L->vetor[atual].prox;
    }
    return contador;
}

// Escreva uma rotina que receba uma lista e retorne duas listas onde uma possui os valores impares e a outra os valores pares da lista.
void lista_pares_impares(Lista* L, Lista* P, Lista* I){
    int atual = L->prim;
    if(atual == -1) return 0;
    while(atual != -1){
        if((L->vetor[atual].elem % 2) == 0){
            P->vetor[P->dispo] = L->vetor[atual];     // copia o elemento para a posição disponível em P
            P->dispo = P->vetor[P->dispo].prox;       // incrementa dispo
        }
        else{
            I->vetor[I->dispo] = L->vetor[atual];     // copia o elemento para a posição disponível em I
            I->dispo = I->vetor[I->dispo].prox;       // incrementa dispo            
        }
        atual = L->vetor[atual].prox;
    }
}

// Escreva uma rotina que receba uma lista e um número X e retorne duas listas onde uma possui valores menores do que o número X e a outra valores maiores do que X.
void lista_maiores_menores(Lista* L, Lista* Ma, Lista* Me, int valor){
    int atual = L->prim;

    if(atual == -1) printf("\nLista vazia!");

    int i, flag = 0;    // flag indicador de elemento repetido

    while(atual != -1){
        flag = 0;
        if(L->vetor[atual].elem < valor){       // se menor, testa se este valor já se encontra na lista de menores
            for(i = 0; i<=MAX; i++){
                if(Me->vetor[i].elem == L->vetor[atual].elem){
                    flag = 1;
                }
            }
            if(!flag){      // se não, adiciona e incrementa o contador
                Me->vetor[Me->dispo].elem = L->vetor[atual].elem;
                Me->dispo = Me->vetor[Me->dispo].prox;
                }
        }
        flag = 0;
        if(L->vetor[atual].elem > valor){       // se maior, testa se este valor já se encontra na lista de maiores
            for(i = 0; i<=MAX; i++){
                if(Ma->vetor[i].elem == L->vetor[atual].elem){
                    flag = 1;
                }
            }
            if(!flag){      // se não, adiciona e incrementa o contador
                Ma->vetor[Ma->dispo].elem = L->vetor[atual].elem;
                Ma->dispo = Ma->vetor[Ma->dispo].prox;
            }
        }
        atual = L->vetor[atual].prox;
    }
}

// Escreva uma rotina que receba uma lista e um número X e um Y e troque todas as ocorrências do
// número X pelo número Y. Retorne a lista modificada e a quantidade de vezes que houve troca.
int troca_valores(Lista* L, int x, int y){
    int atual = L->prim;
    int contador = 0;
    if(atual == -1) printf("\nLista vazia!");
    while(atual != -1){
        if(L->vetor[atual].elem == x){
            L->vetor[atual].elem = y;
            contador++;
        }
        atual = L->vetor[atual].prox;
    }

    printf("\nNovo vetor:\n");
    imprime(L);

    return contador;
}

// Dada uma lista e um elemento, escreva uma rotina que remova da lista todas as ocorrências do elemento.
void remove_valor(Lista* L, int x){
    int atual = L->prim;
    int anterior, dispo;

    while(atual != -1 && (L->vetor[atual].elem != x)){
        anterior = atual;
        atual = L->vetor[atual].prox;
    }
    if(atual == -1){        // se a lista estiver vazia ou se chegar ao fim sem encontrar o elemento
        return;
    }
    
    L->vetor[anterior].prox = L->vetor[atual].prox;
    L->dispo = anterior;
    remove_valor(L, x);     // função se repete até que todas as ocorrências sejam eliminadas
    return;
}

// Escreva uma rotina para remover o n-ésimo elemento de uma lista

void remove_posicao(Lista* L, int posicao){
    int atual = L->prim;
    int anterior, dispo;

    if(posicao = L->prim){      // se remoção do primeiro elemento
        L->prim = L->vetor[L->prim].prox;
    }

    while(atual != -1 && atual < posicao){
        anterior = atual;
        atual = L->vetor[atual].prox;
    }
    if(atual == -1){        // se a lista estiver vazia ou se chegar ao fim sem encontrar o elemento
        return;
    }

    L->vetor[anterior].prox = L->vetor[atual].prox;
    L->dispo = anterior;
}

// Escreva uma rotina que retorne o conteúdo do primeiro nó de uma lista.
int primeiro_no(Lista* L){
    int primeiro = L->vetor[0].elem;
    return primeiro;
}

// Escreva uma rotina que retorne conteúdo do último nó de uma lista.
int ultimo_no(Lista* L){
    int anterior;
    int atual = L->prim;
    if(atual = -1) return -1;       // retorna -1 se a lista estiver vazia
    while (atual != -1){
        anterior = L->vetor[atual].elem;
        atual = L->vetor[atual].prox;
    }
    return anterior;
}

// Escreva uma rotina que retorne um ponteiro para o último nó de uma lista.
struct no* ponteiro_ultimo_no(Lista* L){
    struct no *anterior;
    int atual = L->prim;
    if(atual = -1) return -1;       // retorna -1 se a lista estiver vazia
    while (atual != -1){
        *anterior = L->vetor[atual];
        atual = L->vetor[atual].prox;
    }
    return anterior;
}

// Escreva uma rotina para inserir um elemento antes do n-ésimo elemento de uma lista.
int insere_antes_pos(Lista* L, int posicao, struct no novo){        // posicao: n-ésimo elemento
    int atual = L->prim;
    int anterior;
    if(atual == -1){
        printf("\nLista vazia!");
        return -1;
    }
    if(posicao > MAX || posicao < 0){
        printf("\nPosição inválida!");
        return -1;        
    }
    while(atual != -1 && atual < posicao){
        anterior = atual;
        atual = L->vetor[atual].prox;
    }

    // se não encontrou posição entre os elementos encadeados
    if(atual == -1){
        printf("\nPosição não encontrada - posição excede a quantidade de elementos inseridos!");
        return -1;
    }

    if(anterior == L->prim){        // inserção na primeira posição, atualiza prim
        L->prim = L->dispo;
    }

    L->vetor[L->dispo].elem = novo.elem;
    L->vetor[L->dispo].prox = atual;

    L->vetor[anterior].prox = L->dispo;

    L->dispo = L->vetor[L->dispo].prox;

    printf("\nElemento inserido com sucesso!");
    return 0;
}

// Escreva uma rotina para inserir um elemento depois do n-ésimo elemento de uma lista.
int insere_depois_pos(Lista* L, int posicao, struct no novo){   // posicao: n-ésimo elemento
    int atual = L->prim;
    if(atual == -1){
        printf("\nLista vazia!");
        return -1;
    }
    if(posicao > MAX || posicao < 0){
        printf("\nPosição inválida!");
        return -1;        
    }
    while(atual != -1 && atual < posicao){
        atual = L->vetor[atual].prox;
    }

    // se não encontrou posição entre os elementos encadeados
    if(atual == -1){
        printf("\nPosição não encontrada - posição excede a quantidade de elementos inseridos!\n");
    }

    L->vetor[L->dispo].elem = novo.elem;
    L->vetor[L->dispo].prox = L->vetor[atual].prox;

    L->vetor[atual].prox = L->dispo;

    L->dispo = L->vetor[L->dispo].prox;

    printf("\nElemento inserido com sucesso!");
    return 0;
}


void main(){

    Lista* L = inicializa();

    Lista* P = inicializa();        // lista elementos pares
    Lista* I = inicializa();        // lista elementos ímpares

    Lista* Ma = inicializa();       // lista elementos maiores
    Lista* Me = inicializa();       // lista elementos menores

}