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

// função para verificar se é uma árvore binária de busca
int verifica_ArvoreBB(Arvore *raiz) {
    // caso árvore vazia ou inexistente
    if (raiz == NULL || *raiz == NULL) {
        printf("Árvore vazia!");
        return 0;
    }
    return testa_subarvore(raiz);
}

int testa_subarvore(struct No* no) {
    if (no == NULL) {
        return 1;
    }

    if(no->esq != NULL && no->esq->dado >= no->dado) {
        // filho esquerdo é maior ou igual ao pai
        return 0;
    }

    if (no->dir != NULL && no->dir->dado <= no->dado) {
        // filho direito é menor ou igual ao pai
        return 0;
    }

    // verifica recursivamente os nós filhos
    return testa_subarvore(no->esq) && testa_subarvore(no->dir);
}


// função para verificar se é uma árvore estritamente binária
int verifica_ArvoreEB(Arvore *raiz) {
    // caso árvore vazia ou inexistente
    if (raiz == NULL || *raiz == NULL) {
        printf("Árvore vazia!");
        return 0;
    }
    return testa_subarvoreEB(raiz);
}

int testa_subarvoreEB(struct No* no) {
    if (no == NULL) {
        return 1;
    }

    if ((no->esq == NULL && no->dir != NULL) || (no->esq != NULL && no->dir == NULL)){
        return 0;
    }

    // verifica recursivamente os nós filhos
    return testa_subarvoreEB(no->esq) && testa_subarvoreEB(no->dir);
}


int altura(Arvore *raiz){
    if (raiz == NULL || *raiz == NULL)
        return 0;
    int alt_esq = altura(&((*raiz)->esq));
    int alt_dir = altura(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return(alt_esq + 1);
    else
        return(alt_dir + 1);
}

int testa_balanceamento(Arvore *raiz) {
    if (raiz == NULL) {
        return 1;
    }

    int altura_esq = altura(&((*raiz)->esq));
    int altura_dir = altura(&((*raiz)->dir));

    if (abs(altura_esq - altura_dir) > 1) {
        return 0;
    }

    return testa_balanceamento(&((*raiz)->esq)) && testa_balanceamento(&((*raiz)->dir));
}

// função para verificar se é uma árvore AVL
int verifica_ArvoreAVL(Arvore* raiz) {
    if (raiz == NULL || *raiz == NULL) {
        return 0;
    }

    if (!verifica_ArvoreBB(raiz)) {
        return 0;
    }

    return testa_balanceamento(*raiz);
}
