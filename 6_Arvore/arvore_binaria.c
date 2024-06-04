#include <stdio.h>
#include <stdlib.h>

struct No{
    int dado;
    struct No *esq;
    struct No *dir;
};

// ponteiro para a raiz da árvore
typedef struct No* Arvore;

Arvore* cria_arvore(){
    Arvore* raiz = (Arvore*) malloc(sizeof(Arvore));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void main(){

    // ponteiro de ponteiro para a raiz
    Arvore* raiz = cria_arvore();

}