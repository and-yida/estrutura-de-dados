// 1. Escreva uma rotina que retorne o número de elementos de uma lista.

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

int quantidade_elementos(Lista* L, int quantidade, int posicao){
    int q, atual = L->prim;
    if(atual == -1) return quantidade;
    else{
        q++;
        atual++;
        quantidade_elementos(L, q, atual); 
    }
}

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

void lista_pares_impares(Lista* L, Lista* P, Lista* I){
    int atual = L->prim;
    if(atual == -1) return 0;
    int cp = 0;     // contador para iteração sobre lista pares P
    int ci = 0;     // contador para iteração sobre lista ímpares I
    while(atual != -1){
        if((L->vetor[atual].elem % 2) == 0){
            P->vetor[cp] = L->vetor[atual];     // copia o elemento para a posição disponível em P
            cp++;       // incrementa o contador para indicar a próxima posição disponível
        }
        else{
            I->vetor[ci] = L->vetor[atual];     // copia o elemento para a posição disponível em P
            ci++;       // incrementa o contador para indicar a próxima posição disponível            
        }
        atual = L->vetor[atual].prox;
    }
}

void lista_maiores_menores(Lista* L, Lista* Ma, Lista* Me, int valor){
    int atual = L->prim;
    if(atual == -1) printf("Lista vazia!");
    // flag indicador de elemento repetido; cma contador para indicar próxima posição disponível da lista de elementos maiores,
    // cme contador para indicar próxima posição disponível da lista de elementos menores.
    int i, flag = 0, cma = 0, cme = 0;
    while(atual != -1){
        flag = 0;
        if(L->vetor[atual].elem < valor){       // se menor, testa se este valor já se encontra na lista de menores
            for(i = 0; i<=cme; i++){
                if(Me->vetor[i].elem == L->vetor[atual].elem){
                    flag = 1;
                }
            }
            if(!flag){      // se não, adiciona e incrementa o contador
                Me->vetor[cme].elem = L->vetor[atual].elem;
                cme++;
                }
        }
        flag = 0;
        if(L->vetor[atual].elem > valor){       // se maior, testa se este valor já se encontra na lista de maiores
            for(i = 0; i<=cma; i++){
                if(Ma->vetor[i].elem == L->vetor[atual].elem){
                    flag = 1;
                }
            }
            if(!flag){      // se não, adiciona e incrementa o contador
                Ma->vetor[cma].elem = L->vetor[atual].elem;
                cma++;
            }
        }
        atual = L->vetor[atual].prox;
    }
}

int troca_valores(Lista* L, int x, int y){
    int atual = L->prim;
    int contador = 0;
    if(atual == -1) printf("Lista vazia!");
    while(atual != -1){
        if(L->vetor[atual].elem == x){
            L->vetor[atual].elem = y;
            contador++;
        }
        atual = L->vetor[atual].prox;
    }
    return contador;
}

void remove_valor(Lista* L, int x){
    int atual = L->prim;
    int anterior;
    while(atual != -1 && (L->vetor[atual].elem != x)){
        anterior = atual;
        atual = L->vetor[atual].prox;
    }
    if(atual == -1){        // se a lista estiver vazia ou se chegar ao fim sem encontrar o elemento
        return;
    }
    L->vetor[anterior].prox = -1;
    remove_valor(L, x);     // função se repete até que todas as ocorrências sejam eliminadas
    return;
}

/*
void remove_posicao(Lista* L, int posicao){
    int atual = L->prim;
    int anterior;
    while(atual != -1 && atual < posicao){
        anterior = atual;
        atual = L->vetor[atual].prox;
    }
    if(atual == -1){        // se a lista estiver vazia ou se chegar ao fim sem encontrar o elemento
        return;
    }

}*/

int primeiro_no(Lista* L){
    int primeiro = L->vetor[0].elem;
    return primeiro;
}

int ultimo_no(Lista* L){
    int ultimo = 0;
    int atual = L->prim;
    if(atual = -1) return -1;       // retorna -1 se a lista estiver vazia
    while (atual != -1){
        ultimo++;
        atual = L->vetor[atual].prox;
    }
    return ultimo;
}

int insere_antes_pos(Lista* L, int posicao, struct no novo){
    int atual = L->prim;
    int anterior;
    if(atual == -1){
        printf("Lista vazia!");
        return -1;
    }
    if(posicao > MAX || posicao < 0){
        printf("Posição inválida!");
        return -1;        
    }
    while(atual != -1 && atual < posicao){
        anterior = atual;
        atual = L->vetor[atual].prox;
    }

    if(atual == 1){
        printf("Posição não encontrada - posição excede a quantidade de elementos inseridos!");
        return -1;
    }

    L->vetor[atual].elem = novo.elem;
    novo.prox = L->vetor[atual].prox;

    printf("Elemento inserido com sucesso!");
    return 0;
}

int insere_depois_pos(Lista* L, int posicao, struct no novo){
    int atual = L->prim;
    if(atual == -1){
        printf("Lista vazia!");
        return -1;
    }
    if(posicao > MAX || posicao < 0){
        printf("Posição inválida!");
        return -1;        
    }
    while(atual != -1 && atual < posicao){
        atual = L->vetor[atual].prox;
    }

    if(atual == 1){
        printf("Posição não encontrada - posição excede a quantidade de elementos inseridos!");
    }

    L->vetor[atual+1].elem = novo.elem;
    novo.prox = L->vetor[atual].prox;
    L->vetor[atual].prox = atual+1;

    printf("Elemento inserido com sucesso!");
    return 0;
}


void main(){

    Lista* L = inicializa();

    Lista* P = inicializa();        // lista elementos pares
    Lista* I = inicializa();        // lista elementos ímpares

    Lista* Ma = inicializa();       // lista elementos maiores
    Lista* Me = inicializa();       // lista elementos menores

}