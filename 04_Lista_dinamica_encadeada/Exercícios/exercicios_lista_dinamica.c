// 1. Escreva uma rotina que retorne o número de elementos de uma lista.

#include <stdio.h>
#include <stdlib.h>

// ----IMPLEMENTAÇÃO DINÂMICA----

struct aluno{
    int matricula;
    char nome[30];
    float nota;
};

typedef struct elem{
    struct aluno dados;
    struct elem *prox;
} Elem;

typedef Elem* Lista;        // ponteiro de ponteiro para endereço do primeiro elemento da lista


void imprime(Lista* L){
    if(L == NULL) printf("\nLista vazia!");
    Elem* no = *L; 
    while(no != NULL){
        printf("\nMatricula: %d",no->dados.matricula);
        printf("\nNome: %s",no->dados.nome);
        printf("\nNota: %f\n",no->dados.nota);
        no = no->prox;
    }
}


void main(){

    Lista* L;

}